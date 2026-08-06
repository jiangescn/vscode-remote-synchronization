/*
 * 文件：direction.h
 * -----------------
 * 此文件导出名为 <code>Direction</code> 的枚举类型
 * 其元素为四个罗盘方向：<code>NORTH</code>、
 * <code>EAST</code>、<code>SOUTH</code> 和 <code>WEST</code>。
 *
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 */


#ifndef _direction_h
#define _direction_h

#include <iostream>
#include <string>

/**
 * 此枚举类型用于表示四个罗盘方向。
 */
enum Direction { NORTH, EAST, SOUTH, WEST };

/**
 * 返回参数左侧的方向。
 */
Direction leftFrom(Direction dir);

/**
 * 返回参数右侧的方向。
 */
Direction rightFrom(Direction dir);

/**
 * 返回与参数相反的方向。
 */
Direction opposite(Direction dir);

/**
 * 以字符串返回方向名称。
 */
std::string directionToString(Direction dir);

/**
 * 重载 <code>&lt;&lt;</code> 运算符，使其能够
 * 显示 <code>Direction</code> 值。
 */
std::ostream& operator <<(std::ostream& os, const Direction& dir);

/**
 * 重载 <code>&gt;&gt;</code> 运算符，使其能够
 * 读取 <code>Direction</code> 值。
 */
std::istream& operator >>(std::istream& os, Direction& dir);

/**
 * 重载 <code>++</code> 运算符的后缀版本，以
 * 处理 <code>Direction</code> 值。此项的唯一目的
 * 该定义用于支持以下惯用写法：
 *
 *<pre>
 *    for (Direction dir = NORTH; dir &lt;= WEST; dir++) ...
 *</pre>
 */
Direction operator ++(Direction& dir, int);

#endif // _direction_h
