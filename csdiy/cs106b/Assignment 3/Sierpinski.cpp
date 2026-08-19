#include "Sierpinski.h"
#include "error.h"
using namespace std;

/**
 * 在指定窗口中绘制具有指定顶点的三角形。你可以自由
 * 按你认为合适的方式编辑此函数，以更改颜色、填充样式等
 * 等等，按你希望的任何方式！
 *
 * @param window 绘制三角形的窗口。
 * @param x0 y0 三角形的第一个顶点。
 * @param x1 y1 三角形的第二个顶点。
 * @param x2 y2 三角形的第三个顶点。
 */
void drawTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2) {
    window.setColor("black");
    window.fillPolygon({ x0, y0, x1, y1, x2, y2 });
}

/* TODO：有关此函数应执行什么操作的更多信息，请参阅 Sierpinski.h。
 * 然后删除此注释。
 */
void drawSierpinskiTriangle(GWindow& window,
                            double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int order) {
    /* TODO：删除此注释、下面这些代码行，并实现此函数。 */
    if (order < 0)
    {
        error("Order cannot be negative.");
    }

    if(order == 0)
    {
        drawTriangle(window, x0, y0, x1, y1, x2, y2);
        return;
    }
    double x01 = (x0 + x1) / 2.0;
    double y01 = (y0 + y1) / 2.0;

    double x12 = (x1 + x2) / 2.0;
    double y12 = (y1 + y2) / 2.0;

    double x02 = (x0 + x2) / 2.0;
    double y02 = (y0 + y2) / 2.0;

    drawSierpinskiTriangle(window, x1, y1, x01, y01, x12, y12, order - 1);
    drawSierpinskiTriangle(window, x01, y01, x0, y0, x02, y02, order - 1);
    drawSierpinskiTriangle(window, x12, y12, x02, y02, x2, y2, order - 1);
    return;
}
