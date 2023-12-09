#include <graphics.h>  // 引入绘图库
#include <cmath>       // 引入数学库
#include <conio.h>     // 引入控制台输入输出库
#include <cstdlib>     // 引入标准库
#include <ctime>       // 引入时间库
#include <windows.h>   // 引入Windows库

#define PI acos(-1)    // 定义PI为π的近似值
int r;                   // 定义整数变量r，用于表示半径
double speed = 0.00005;   // 定义浮点数变量speed，表示线条绘制的速度
double speed1 = 0.000005; // 定义浮点数变量speed1，表示线条绘制的速度（备用）
double factor = 0.0015;   // 定义浮点数变量factor，表示线条绘制的因子
double factor1 = 0.0015;  // 定义浮点数变量factor1，表示线条绘制的因子（备用）
bool drawDots = false;    // 定义布尔变量drawDots，表示是否绘制点
bool toggleFactor = true; // 定义布尔变量toggleFactor，用于切换因子计算方式
int k = 10;
int red = 255, green = 0, blue = 0;
int colorDelta = 1;



// 定义一个结构体POINT，表示一个二维点
POINT getVector(int index, int total) {
    double angle = (index % total) * 2 * PI / total + PI; // 计算角度
    POINT v;
    v.x = static_cast<int>(cos(angle) * r); // 计算x坐标
    v.y = static_cast<int>(sin(angle) * r); // 计算y坐标
    return v;
}

// 绘制带有点的线条
void drawLineWithDots(POINT start, POINT end, int numDots) {
    int dx = end.x - start.x; // 计算x方向的差值
    int dy = end.y - start.y; // 计算y方向的差值
    double stepX = static_cast<double>(dx) / numDots; // 计算x方向的步进值
    double stepY = static_cast<double>(dy) / numDots; // 计算y方向的步进值

    for (int i = 0; i < numDots; i++) {
        int x = static_cast<int>(start.x + i * stepX); // 计算x坐标
        int y = static_cast<int>(start.y + i * stepY); // 计算y坐标

        if (drawDots) {
            int red = rand() % 256; // 生成随机红色分量
            int green = rand() % 256; // 生成随机绿色分量
            int blue = rand() % 256; // 生成随机蓝色分量
            setcolor(DARKGRAY); // 设置点的颜色
            int K = rand() % 256;
            setbkcolor(RGB(0, 0, k));
            putpixel(x, y, getcolor()); // 在指定位置绘制点
            if (toggleFactor) {
                factor1 += speed1; // 更新因子1
                factor = factor1;
            }
            else {
                factor = speed; // 更新因子
                bool isShiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000; // 检测Shift键是否被按下
                bool isCtrlPressed = GetAsyncKeyState(VK_CONTROL) & 0x8000; // 检测Ctrl键是否被按下
                if (isShiftPressed) {
                    speed += 0.00001; // 增加速度
                }
                else if (isCtrlPressed) {
                    speed -= 0.00001; // 减小速度
                }
            }
        }
    }

    if (!drawDots) {
        setcolor(DARKGRAY); // 设置线条颜色
        line(start.x, start.y, end.x, end.y); // 绘制线条
        if (toggleFactor) {
            factor1 += speed1; // 更新因子1
            factor = factor1;
        }
        else {
            factor = speed; // 更新因子
            bool isShiftPressed = GetAsyncKeyState(VK_SHIFT) & 0x8000; // 检测Shift键是否被按下
            bool isCtrlPressed = GetAsyncKeyState(VK_CONTROL) & 0x8000; // 检测Ctrl键是否被按下
            if (isShiftPressed) {
                speed += 0.00001; // 增加速度
            }
            else if (isCtrlPressed) {
                speed -= 0.00001; // 减小速度
            }
        }
    }
}

// 主函数
int main() {
    initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); // 初始化图形窗口
    HWND hwnd = GetHWnd(); // 获取窗口句柄
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION); // 移除窗口标题栏
    SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW); // 设置窗口位置和大小



    r = getheight() / 2 - 16; // 计算半径大小

    int total = 200; // 总点数
    setorigin(getwidth() / 2, getheight() / 2); // 设置坐标原点为屏幕中心
    srand(time(NULL)); // 初始化随机数生成器

    char key;
    bool wheelMoved = false; // 用于跟踪鼠标滚轮是否已经移动
    int wheelDelta = 0; // 用于存储鼠标滚轮事件的滚动值

    while (true) {

        setbkcolor(WHITE);
        cleardevice();
        // 在左上角输出 "cardioid"
       /* TCHAR s[80]; // 定义字符串数组
        swprintf_s(c, _T("%hs"), "按H切换自动/手动绘制\n按shift/ctrl前进后退\n按X切换点/线绘制");*/
        setcolor(BLACK);
        settextstyle(60, 0, _T("微软雅黑"));
        outtextxy(-280, -100, _T("按H切换自动/手动绘制"));
        outtextxy(-330, 0, _T("手动下按Shift/Ctrl前进后退"));
        outtextxy(-240, 130, _T("按X切换点/线绘制"));
        Sleep(7000);
        setbkcolor(WHITE);
        cleardevice();
        
        setbkcolor(WHITE);
        cleardevice();

        setcolor(BLACK);
        settextstyle(60, 0, _T("微软雅黑"));
        outtextxy(-280, -100,_T("Presented by   解方程组"));
        Sleep(5000);
        cleardevice();
        TCHAR c[80]; // 定义字符串数组
        swprintf_s(c, _T("%hs"), "C     A     R     D     I     O     I     D");
        setcolor(BLACK);
        AddFontResourceEx(L"D:/CODING/repo/exam1/exam1/font.ttf", FR_PRIVATE, NULL);
        settextstyle(48, 0, L"Futurist Fixed-width");
        outtextxy(-820, -20, c);
        Sleep(5000);
        
        break;
    }
    while(true)
    {

        if (_kbhit()) {
            key = _getch();
            if (key == 'x' || key == 'X') {
                drawDots = !drawDots; // 切换是否绘制点
            }
            if (key == 'h' || key == 'H') {
                toggleFactor = !toggleFactor; // 切换因子计算方式
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
                r += 7; // 增加半径
            }
            else {
                r -= 7; // 减小半径
            }

            // 限制半径大小的范围，确保不小于最小值
            if (r < 5) {
                r = 5; // 最小半径为5
            }

            wheelMoved = false; // 重置鼠标滚轮状态
        }

            BeginBatchDraw();

            /* red += colorDelta;
             if (red >= 255) {
                 red = 255;
                 colorDelta = -1;
             }
             else if (red <= 0) {
                 red = 0;
                 colorDelta = 1;
             }
             green = 255 - red;
             blue = 255 - red;*/
            setbkcolor(WHITE);
            cleardevice();
            // 在左上角输出 "cardioid"
            TCHAR b[80]; // 定义字符串数组
            swprintf_s(b, _T("%hs"), "C     A     R     D     I     O     I     D");
            setcolor(BLACK);
            AddFontResourceEx(L"D:/CODING/repo/exam1/exam1/font.ttf", FR_PRIVATE, NULL);
            settextstyle(48, 0, L"Futurist Fixed-width");
            outtextxy(-820, -20, b);



        for (int i = 0; i < total; i++) {
            POINT a = getVector(i, total);
            POINT b = getVector(i * factor, total);
            drawLineWithDots(a, b, 200);
        }

       
        FlushBatchDraw();
    }





    closegraph(); // 关闭图形窗口
    return 0; // 返回0表示程序正常结束
}

