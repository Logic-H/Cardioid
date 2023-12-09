#include <graphics.h>
#include <cmath>
#include<conio.h>

#define PI  acos(-1)
int r;


POINT getVector(int index, int total) {
    double angle = (index % total) * 2 * PI / total + PI;
    POINT v;
    v.x = static_cast<int>(cos(angle) * r);
    v.y = static_cast<int>(sin(angle) * r);
    return v;
}

int main() {
    initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    r = getheight() / 2 - 16;

    int total = 200;

    setorigin(getwidth() / 2, getheight() / 2);

    while (!_kbhit()) { // 循环绘制直到按下键盘按键


        BeginBatchDraw();

        // 清空画布
        setbkcolor(WHITE);
        cleardevice();



        // 设置线条宽度
        setlinecolor(BLACK);

        for (int i = 0; i < total; i++) {
            POINT a = getVector(i, total);
            POINT b = getVector(i * 2, total);
            line(a.x, a.y, b.x, b.y);
        }

        FlushBatchDraw();
    }

    closegraph();
    return 0;
}