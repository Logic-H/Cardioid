#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#define PI acos(-1)
int r;
double speed = 0.00005;
double speed1 = 0.000005;
double factor = 0.0015;
double factor1 = 0.0015;
bool drawDots = false;
bool toggleFactor = true;

POINT getVector(int index, int total) {
    double angle = (index % total) * 2 * PI / total + PI;
    POINT v;
    v.x = static_cast<int>(cos(angle) * r);
    v.y = static_cast<int>(sin(angle) * r);
    return v;
}

void drawLineWithDots(POINT start, POINT end, int numDots) {
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    double stepX = static_cast<double>(dx) / numDots;
    double stepY = static_cast<double>(dy) / numDots;

    for (int i = 0; i < numDots; i++) {
        int x = static_cast<int>(start.x + i * stepX);
        int y = static_cast<int>(start.y + i * stepY);

        if (drawDots) {
            int red = rand() % 256;
            int green = rand() % 256;
            int blue = rand() % 256;
            setcolor(RGB(red, green, blue));
            putpixel(x, y, getcolor());
            if (toggleFactor) {
                factor1 += speed1;
                factor = factor1;
            }
            else {
                factor = speed;
                bool isShiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;
                bool isCtrlPressed = GetAsyncKeyState(VK_CONTROL) & 0x8000;
                if (isShiftPressed) {
                    speed += 0.00001;
                }
                else if (isCtrlPressed) {
                    speed -= 0.00001;
                }
            }
        }
    }

    if (!drawDots) {
        setcolor(DARKGRAY);
        line(start.x, start.y, end.x, end.y);
        if (toggleFactor) {
            factor1 += speed1;
            factor = factor1;
        }
        else {
            factor = speed;
            bool isShiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;
            bool isCtrlPressed = GetAsyncKeyState(VK_CONTROL) & 0x8000;
            if (isShiftPressed) {
                speed += 0.00001;
            }
            else if (isCtrlPressed) {
                speed -= 0.00001;
            }
        }
    }
}

int main() {
    initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    HWND hwnd = GetHWnd();
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);

    r = getheight() / 2 - 16;

    int total = 200;
    setorigin(getwidth() / 2, getheight() / 2);
    srand(time(NULL));

    char key;
    bool wheelMoved = false; // 用于跟踪鼠标滚轮是否已经移动
    int wheelDelta = 0; // 用于存储鼠标滚轮事件的滚动值

    while (true) {
        if (_kbhit()) {
            key = _getch();
            if (key == 'x' || key == 'X') {
                drawDots = !drawDots;
            }
            if (key == 'h' || key == 'H') {
                toggleFactor = !toggleFactor;
            }
        }

        // 检测鼠标滚轮事件
        while (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_MOUSEWHEEL) {
                wheelMoved = true;
                wheelDelta = msg.wheel;
            }
        }

        if (wheelMoved) {
            // 根据鼠标滚轮方向更新半径大小
            if (wheelDelta > 0) {
                r += 1;
            } else {
                r -= 1;
            }

            // 限制半径大小的范围，确保不小于最小值
            if (r < 5) {
                r = 5;
            }

            wheelMoved = false; // 重置鼠标滚轮状态
        }

        BeginBatchDraw();

        setbkcolor(WHITE);
        cleardevice();

        for (int i = 0; i < total; i++) {
            POINT a = getVector(i, total);
            POINT b = getVector(i * factor, total);
            drawLineWithDots(a, b, 100);
        }

        FlushBatchDraw();
    }

    closegraph();
    return 0;
}