#ifndef Sierpinski_Included
#define Sierpinski_Included

#include "gwindow.h"

/**
 * 绘制具有指定顶点的谢尔宾斯基三角形。
 *
 * 0 阶谢尔宾斯基三角形只是普通填充三角形。n 阶谢尔宾斯基
 * 当 n > 0 时，该三角形由三个 n-1 阶的较小 Sierpinski 三角形组成，每个大小为一半
 * 与原三角形同宽同高，并使它们角对角相接。
 *
 * 所提供点的顺序无关紧要。
 *
 * 如果提供给此函数的阶数为负，此函数应调用 error() 报告
 * 一个错误。
 *
 * @param window 绘制三角形的窗口。
 * @param x0, y0 三角形第一个顶点的 x 和 y 坐标。
 * @param x1, y1 三角形第二个顶点的 x 和 y 坐标。
 * @param x2, y2 三角形第三个顶点的 x 和 y 坐标。
 * @param order 三角形的阶数，始终为非负数。
 */
void drawSierpinskiTriangle(GWindow& window,
                            double x0, double y0,
                            double x1, double y1,
                            double x2, double y2,
                            int order);

#endif
