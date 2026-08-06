#include "GVector.h"
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

/* 底层角度。 */
double angleOf(const GVector& v) {
    return atan2(v.y, v.x);
}

/* 可直接通过正弦和余弦计算单位向量。 */
GVector unitToward(double theta) {
    return { cos(theta), sin(theta) };
}

/* 点积。 */
double dot(const GVector& a, const GVector& b) {
    return a.x * b.x + a.y * b.y;
}

/* 向量投影。 */
GVector project(const GVector& vector, const GVector& onto) {
    return onto * dot(vector, onto) / dot(onto, onto);
}

/* 流打印。 */
ostream& operator<< (ostream& out, const GVector& v) {
    ostringstream builder;
    builder << "(" << v.x << ", " << v.y << ")";
    return out << builder.str();
}



GVector operator* (const GMatrix& m, const GVector& v) {
    return { m.a * v.x + m.b * v.y, m.c * v.x + m.d * v.y };
}
GPoint operator* (const GMatrix& m, const GPoint& v) {
    return { m.a * v.x + m.b * v.y, m.c * v.x + m.d * v.y };
}

GMatrix operator* (const GMatrix& m, const GMatrix& n) {
    return { m.a * n.a + m.b * n.c, m.a * n.b + m.a * n.d ,
             m.c * n.a + m.d * n.c, m.c * n.b + m.d * n.d };
}
GMatrix operator* (const GMatrix& m, double scalar) {
    return { m.a * scalar, m.b * scalar, m.c * scalar, m.d * scalar };
}
GMatrix operator/ (const GMatrix& m, double scalar) {
    return { m.a / scalar, m.b / scalar, m.c / scalar, m.d / scalar };
}

GMatrix& operator*= (GMatrix& m, const GMatrix& n) {
    m = (m * n);
    return m;
}
GMatrix& operator*= (GMatrix& m, double scalar) {
    m = (m * scalar);
    return m;
}
GMatrix& operator/= (GMatrix& m, double scalar) {
    m = (m / scalar);
    return m;
}

double det(const GMatrix& m) {
    return m.a * m.d - m.b * m.c;
}

GMatrix inverse(const GMatrix& m) {
    return GMatrix{ m.d, -m.b, -m.c, m.a } / det(m);
}

GMatrix rotation(double theta) {
    return { cos(theta), -sin(theta), sin(theta), cos(theta) };
}

ostream& operator<< (ostream& out, const GMatrix& m) {
    ostringstream builder;
    builder << "[[" << m.a << ", " << m.b << "][" << m.c << ", " << m.d << "]]";
    return out << builder.str();
}
