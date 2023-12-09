#include <graphics.h>  // 引入绘图库
#include <math.h>       // 引入数学库
#include <conio.h>     // 引入控制台输入输出库
#include <time.h>       // 引入时间库
#define PI acos(-1)    // 定义PI为π的近似值

int r;                   //半径
int timeR;
double factor = 0.0015;   // 浮点数变量factor，factor*i表示线条末端 端点 序号 与 始端 的序号 的倍数关系
double factor1 = 0.0015;  // 同上（隔离，用于第二种绘制方式）
double speed = 0.00005;   // 浮点数speed，用于factor的自增
double speed1 = 0.000005; // 隔离，用于第二种绘制模式


bool drawDots = false;    // 定义布尔变量drawDots，表示初始状态下 不用 点模拟线 这一方式绘制
bool toggleFactor = true; // 定义布尔变量toggleFactor，表示初始状态下 没有按下H，在动态绘制
int CircleNum = 1;//定义整型变量，表示圈数
int total = 200; // 总点数
char key;
bool wheelMoved = false; // 用于跟踪鼠标滚轮是否已经移动
int wheelDelta = 0; // 用于存储鼠标滚轮事件的滚动值
//初始化图形界面
void startup()
{
    initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); // 初始化图形窗口
    HWND hwnd = GetHWnd(); // 获取窗口句柄
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION); // 移除窗口标题栏
    SetWindowPos(hwnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW); // 设置窗口位置和大小



    r = getheight(); // 计算半径大小

    setorigin(getwidth() / 2, getheight() / 2); // 设置坐标原点为屏幕中心
}
//根据q/e来增加/减少圈数
void increaseCircleNum() //增加圈数函数
{
    CircleNum++;
}
void decreaseCircleNum() //减少圈数函数
{
    if (CircleNum > 1) {
        CircleNum--;
    }
}
//判断是否按下shift/ctrl和h，
void ifsc()//判断是否按下shift/ctrl和h，
{
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


// 定义一个结构体POINT，表示一个二维点
POINT getVector(int index, double total) {
    double angle = index * 2 * PI / total + PI; // 计算角度
    POINT v;
    v.x = static_cast<int>(cos(angle) * r); // 计算x坐标
    v.y = static_cast<int>(sin(angle) * r); // 计算y坐标
    return v;
}

// 绘制带有点的线条
void drawLineBetweenDots(POINT start, POINT end, int numDots) {
    int dx = end.x - start.x; // 计算x方向的差值
    int dy = end.y - start.y; // 计算y方向的差值
    double stepX = static_cast<double>(dx) / numDots; // 计算x方向的步进值（Xn - Xn-1），除以numdots，将其细分，以此近似像素点坐标
    double stepY = static_cast<double>(dy) / numDots; // 计算y方向的步进值

    for (int i = 0; i < numDots; i++) {
        int x = static_cast<int>(start.x + i * stepX); // 计算x坐标，并且强制转换为整数
        int y = static_cast<int>(start.y + i * stepY); // 计算y坐标，并且强制转换为整数

        if (drawDots) {
            setcolor(BLACK); // 设置点的颜色
            putpixel(x, y, getcolor()); // 在指定位置绘制点
            ifsc();
        }
    }

    if (!drawDots) {
        setcolor(BLACK); // 设置线条颜色
        line(start.x, start.y, end.x, end.y); // 绘制线条（例：连接x1，y1和x2，y2）
        ifsc();
        }
    
}
//字幕1
void line1()
{
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    settextstyle(60, 0, _T("微软雅黑"));
    outtextxy(-280, -100, _T("按H切换自动/手动绘制"));
    outtextxy(-330, 0, _T("手动下按Shift/Ctrl前进后退"));
    outtextxy(-240, 130, _T("按X切换点/线绘制"));
    Sleep(7000);
}
//字幕2
void line2() {
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    settextstyle(60, 0, _T("微软雅黑"));
    outtextxy(-360, -100, _T("Presented Proudly by 解方程组"));
    Sleep(5000);
    cleardevice();
}
//主字幕
void linemain()
{
    TCHAR c[80]; // 定义字符串数组
    swprintf_s(c, _T("%hs"), "C     A     R     D     I     O     I     D");
    setcolor(BLACK);
    AddFontResourceEx(L"D:/CODING/repo/exam1/exam1/font.ttf", FR_PRIVATE, NULL);
    settextstyle(48, 0, L"Futurist Fixed-width");
    outtextxy(-820, -20, c);
    
}
//检测q/e/x/h是否被按下
void detectkey() {
    if (_kbhit()) {
        key = _getch();
        if (key == 'x' || key == 'X') {
            drawDots = !drawDots; // 切换是否绘制点
        }

        if (key == 'h' || key == 'H') {
            toggleFactor = !toggleFactor; // 切换因子计算方式
        }
    }
    if (GetAsyncKeyState('Q') & 0x8000) {
        increaseCircleNum();
        Sleep(100); // 防止快速连续按键
    }
    if (GetAsyncKeyState('E') & 0x8000) {
        decreaseCircleNum();
        Sleep(100); // 防止快速连续按键
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
        timeR = r / 7;
        // 根据鼠标滚轮方向更新半径大小
        if (wheelDelta > 0) {
            r += timeR; // 增加半径
        }
        else {
            r -= timeR; // 减小半径
        }

        // 限制半径大小的范围，确保不小于最小值
        if (r < 5) {
            r = 5; // 最小半径为5
        }

        wheelMoved = false; // 重置鼠标滚轮状态
    }
}
// 主函数
int main() {
    
    startup();
    //前置字幕循环
    while (true) {
        line1();//字幕1
        line2();//字幕2
        linemain();//输出 "cardioid"
        Sleep(5000);
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }
        break;
    }
    //主循环
    while (true)
    {
        detectkey();//检测各种按键
        BeginBatchDraw();//批量绘制
        setbkcolor(WHITE);
        cleardevice();
        //输出 "cardioid"
        linemain();

        for (int i = 0; i < CircleNum*total; i++) {
            POINT a = getVector(i, total);
            POINT b = getVector(i * factor, total);
            drawLineBetweenDots(a, b, 200);//将标号为i的点与标号为i*factor的点连线，如i和2*i连就是标准心型线
        }


        FlushBatchDraw();
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }
    }
    closegraph(); // 关闭图形窗口
    return 0; // 返回0表示程序正常结束
}