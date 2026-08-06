#ifndef GVector_Included
#define GVector_Included

#include "gobjects.h"
#include <ostream>

/* 表示二维向量的类型。 */
struct GVector {
    double x, y;
};

/* 两个点相减得到向量。 */
GVector operator- (const GPoint& p1, const GPoint& p2);

/* 两个向量相减得到向量。 */
GVector operator- (const GVector& v1, const GVector& v2);
GVector& operator-= (GVector& lhs, const GVector& rhs);

/* 点与向量相加得到点。 */
GPoint  operator+  (const GVector& v, const GPoint& p);
GPoint  operator+  (const GPoint& p, const GVector& v);
GPoint& operator+= (GPoint& lhs, const GVector& rhs);

GPoint  operator-  (const GPoint& p, const GVector& v);
GPoint& operator-= (GPoint& lhs, const GVector& rhs);

/* 两个向量相加得到向量。 */
GVector  operator+ (const GVector& v1, const GVector& v2);
GVector& operator+= (GVector& lhs, const GVector& rhs);

/* 缩放向量会按比例缩放其分量。 */
GVector  operator* (const GVector& v, double scalar);
GVector  operator* (double scalar, const GVector& v);
GVector& operator*= (GVector& v, double scalar);

GVector  operator/ (const GVector& v, double scalar);
GVector& operator/= (GVector& lhs, double scalar);

/* 大小和归一化。 */
double magnitudeOf(const GVector& v);
GVector normalizationOf(const GVector& v);

/* 按弧度角旋转。 */
GVector rotate(const GVector& v, double theta);

/* 底层角度。 */
double angleOf(const GVector& v);

/* 向量投影。 */
double dot(const GVector& a, const GVector& b);
GVector project(const GVector& vector, const GVector& onto);

/* 获取指向给定方向的单位向量。
 *
 * 请注意：这返回笛卡尔空间中该角度的向量，而不是
 * 在图形坐标空间中！可能需要适当调整角度。
 */
GVector unitToward(double theta);

std::ostream& operator<< (std::ostream& out, const GVector& v);

/* 表示二维矩阵的类型：
 *
 * |a b|
 * |c d|
 */
struct GMatrix {
    double a, b, c, d;

    GMatrix() = default;
    GMatrix(double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {}
    GMatrix(const GVector& col1, const GVector& col2): a(col1.x), b(col2.x), c(col1.y), d(col2.y) {}
};

GVector operator* (const GMatrix& m, const GVector& v);
GPoint  operator* (const GMatrix& m, const GPoint& v);
GMatrix operator* (const GMatrix& m, const GMatrix& n);
GMatrix operator* (const GMatrix& m, double scalar);
GMatrix& operator*= (GMatrix& m, const GMatrix& n);
GMatrix& operator*= (GMatrix& m, double scalar);

GMatrix  operator/ (const GMatrix& m, double scalar);
GMatrix& operator/=(GMatrix& m, double scalar);

GMatrix rotation(double theta);
double det(const GMatrix& m);
GMatrix inverse(const GMatrix& m);

std::ostream& operator<< (std::ostream& out, const GMatrix& m);

#endif
