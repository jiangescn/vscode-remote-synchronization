#include "Demos/GVector.h"
#include <cmath>
#include <sstream>
using namespace std;

/* 两个点相减得到向量。 */
GVector operator- (const GPoint& p1, const GPoint& p2) {
    return { p1.x - p2.x, p1.y - p2.y };
}

/* 两个向量相减得到向量。 */
GVector operator- (const GVector& v1, const GVector& v2) {
    return { v1.x - v2.x, v1.y - v2. y };
}
GVector& operator-= (GVector& lhs, const GVector& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

/* 点与向量相加得到点。 */
GPoint  operator+ (const GVector& v, const GPoint& p) {
    return { v.x + p.x, v.y + p.y };
}
GPoint  operator+ (const GPoint& p, const GVector& v) {
    return v + p;
}
GPoint& operator+= (GPoint& lhs, const GVector& rhs) {
    lhs = (lhs + rhs);
    return lhs;
}

GPoint  operator- (const GPoint& p, const GVector& v) {
    return { p.x - v.x, p.y - v.y };
}
GPoint& operator-= (GPoint& lhs, const GVector& rhs) {
    lhs = (lhs - rhs);
    return lhs;
}

/* 两个向量相加得到向量。 */
GVector  operator+ (const GVector& v1, const GVector& v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}
GVector& operator+= (GVector& lhs, const GVector& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

/* 缩放向量会按比例缩放其分量。 */
GVector  operator* (const GVector& v, double scalar) {
    return { v.x * scalar, v.y * scalar };
}
GVector  operator* (double scalar, const GVector& v) {
    return v * scalar;
}
GVector& operator*= (GVector& v, double scalar) {
    v.x *= scalar;
    v.y *= scalar;
    return v;
}

GVector  operator/ (const GVector& v, double scalar) {
    return v * (1.0 / scalar);
}
GVector& operator/= (GVector& lhs, double scalar) {
    return lhs *= (1.0 / scalar);
}

/* 大小和归一化。 */
double magnitudeOf(const GVector& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}
GVector normalizationOf(const GVector& v) {
    return v / magnitudeOf(v);
}

/* 按弧度角旋转。 */
GVector rotate(const GVector& v, double theta) {
    /* 旋转矩阵为
     *
     *   | cos T  -sin T |
     *   | sin T   cos T |
     *
     * 因此，将向量 v 旋转角度 theta 可得
     *
     *   | cos T  -sin T | |x|   | x cos T - y sin T |
     *   | sin T   cos T | |y| = | x sin T + y cos T |
     */
    return {
        v.x * cos(theta) - v.y * sin(theta),
        v.x * sin(theta) + v.y * cos(theta)
    };
}

/* 可直接通过正弦和余弦计算单位向量。 */
GVector unitToward(double theta) {
    return { cos(theta), sin(theta) };
}

ostream& operator<< (ostream& out, const GVector& v) {
    ostringstream builder;
    builder << "(" << v.x << ", " << v.y << ")";
    return out << builder.str();
}
