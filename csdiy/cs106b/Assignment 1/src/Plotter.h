/******************************************************************************
 * 文件：Plotter.h
 * 作者：Keith Schwarz（htiek@cs.stanford.edu）
 *
 * Plotter 作业使用的类型和函数。请勿修改
 * 完成作业时使用此文件。
 */

#ifndef Plotter_Included
#define Plotter_Included

#include <istream>
#include <string>

/* 类型：PenStyle
 *
 * 包含画笔属性信息的结构。你应当
 * 不要修改此结构。如果需要存储有关以下对象的更多信息
 * 画笔，你需要找到其他方法实现。
 */
struct PenStyle {
    double width;
    std::string color;
};



/**
 * 使用指定画笔在两个指定点之间绘制线段
 * 样式。
 * <p>
 * 线段中不在方框 [-1, 1] x [-1, 1] 内的任何部分都不会
 * 被绘制。
 *
 * @param x0 线段起点的 x 坐标。
 * @param y0 线段起点的 y 坐标。
 * @param x1 线段终点的 x 坐标。
 * @param y1 线段终点的 y 坐标。
 * @param style 关于画笔当前样式的信息。
 */
void drawLine(double x0, double y0, double x1, double y1, PenStyle info);



/**
 * 运行给定输入流中包含的 plotter 脚本。此函数
 * 假定输入脚本格式正确，不对以下内容作任何保证：
 * 如果情况并非如此，会发生什么。
 *
 * @param input 包含要运行脚本的输入流。
 */
void runPlotterScript(std::istream& input);

#endif
