#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#define PI acos(-1)
int r;
double factor = 0;

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

        setcolor(BLACK);

        // 绘制一个小点
        putpixel(x, y, getcolor());
    }
}

int main() {
    initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    r = getheight() / 2 - 16;

    int total = 200;

    setorigin(getwidth() / 2, getheight() / 2);

    // 初始化随机数生成器
    srand(time(NULL));

    while (!_kbhit()) { // 循环绘制直到按下键盘按键
        factor += 0.0015;

        BeginBatchDraw();

        // 清空画布
        setbkcolor(WHITE);
        cleardevice();

        for (int i = 0; i < total; i++) {
            POINT a = getVector(i, total);
            POINT b = getVector(i * factor, total);

            // 绘制线的效果，使用100个小点来模拟
            drawLineWithDots(a, b, 100);
        }

        FlushBatchDraw();
    }

    closegraph();
    return 0;
}