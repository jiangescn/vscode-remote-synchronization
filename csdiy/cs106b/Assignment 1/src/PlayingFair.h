/******************************************************************************
 * 文件：PlayingFair.h
 * 作者：Keith Schwarz（htiek@cs.stanford.edu）
 *
 * 作业中 Playing Fair 部分的头文件。你不应
 * 修改此文件。
 */

#ifndef PlayingFair_Included
#define PlayingFair_Included

#include <string>

/**
 * 给定数字 n，返回 n 阶 A 序列。如果 n 为负数，
 * 则此函数会通过调用 error() 函数报告错误。
 *
 * @param n 要生成的 A 序列的阶数。
 * @return n 阶 A 序列。
 */
std::string aSequenceOfOrder(int n);

/**
 * 给定数字 n，返回 n 阶 B 序列。如果 n 为负数，
 * 则此函数会通过调用 error() 函数报告错误。
 *
 * @param n 要生成的 B 序列的阶数。
 * @return n 阶 B 序列。
 */
std::string bSequenceOfOrder(int n);


#endif
