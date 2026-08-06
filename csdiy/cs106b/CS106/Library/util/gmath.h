/*
 * 文件：gmath.h
 * -------------
 * 此文件导出若干用于处理图形
 * 几何信息以及数学常量 <code>PI</code>
 * 以及 <code>E</code>。
 */


#ifndef _gmath_h
#define _gmath_h

#include <cmath>
#include <limits>
#include "gtypes.h"


/**
 * 数学常数 pi，即圆周长与
 * 圆的直径。
 */
extern const double PI;

/**
 * 常量：E
 * -----------
 * 数学常数 e，即自然对数的底数。
 */
extern const double E;

/**
 * 返回 <code>angle</code> 的三角余弦值，其中 angle
 * 以角度表示。
 */
double cosDegrees(double angle);

/**
 * 如果给定两个浮点数“相等”，则返回 true。
 * 浮点相等判断很棘手，因为舍入误差可能导致
 * 这些数字应非常接近但不完全相同。
 * 此比较用于测试两个数之差是否在机器
 * epsilon。
 */
bool floatingPointEqual(double f1, double f2);
bool floatingPointEqual(float f1, float f2);

/**
 * 返回 <code>angle</code> 的三角正弦值，其中 angle
 * 以角度表示。
 */
double sinDegrees(double angle);

/**
 * 返回 <code>angle</code> 的三角正切值，其中 angle
 * 以角度表示。
 */
double tanDegrees(double angle);

/**
 * 将角度从弧度转换为度。
 */
double toDegrees(double radians);

/**
 * 将角度从度转换为弧度。
 */
double toRadians(double degrees);

/**
 * 返回从原点到指定点的角度（以度为单位）。
 * 此函数考虑了图形坐标系具有以下特点这一事实：
 * 坐标系在 <i>y</i> 方向上相对于传统坐标系进行了翻转
 * 笛卡尔平面。
 */
double vectorAngle(double x, double y);

/**
 * 返回从原点到指定点的角度（以度为单位）。
 * 此函数考虑了图形坐标系具有以下特点这一事实：
 * 坐标系在 <i>y</i> 方向上相对于传统坐标系进行了翻转
 * 笛卡尔平面。
 */
double vectorAngle(const GPoint& pt);

/**
 * 计算原点与指定点之间的距离。
 */
double vectorDistance(double x, double y);

/**
 * 计算原点与指定点之间的距离。
 */
double vectorDistance(const GPoint& pt);

#endif // _gmath_h
