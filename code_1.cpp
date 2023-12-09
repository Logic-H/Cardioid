#include <graphics.h>
#include <math.h>
#include <conio.h>

int main() {
    initgraph(400, 400); // 创建一个400x400的窗口

    int centerX = 200; // 圆心横坐标
    int centerY = 200; // 圆心纵坐标
    int radius = 150;  // 圆的半径

    // 绘制圆
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    circle(centerX, centerY, radius);

    int pointSize = 6; // 设置点的大小
    int numPoints = 10; // 总点数

    // 计算并绘制十个均匀分布的点
    for (int i = 0; i < numPoints; i++) {
        double angle = 2 * 3.14159265 * i / numPoints; // 计算每个点的角度
        int x = centerX + static_cast<int>(radius * cos(angle)); // 计算点的横坐标
        int y = centerY - static_cast<int>(radius * sin(angle)); // 计算点的纵坐标

        // 绘制大点
        setfillcolor(BLACK);
        fillcircle(x, y, pointSize);

        // 计算要连接的点的索引
        int connectedIndex = (i * 2) % numPoints;

        // 连接点形成心形曲线
        int x2 = centerX + static_cast<int>(radius * cos(2 * 3.14159265 * connectedIndex / numPoints));
        int y2 = centerY - static_cast<int>(radius * sin(2 * 3.14159265 * connectedIndex / numPoints));
        line(x, y, x2, y2);
    }

    _getch(); 
    closegraph(); // 关闭绘图窗口

    return 0;
}