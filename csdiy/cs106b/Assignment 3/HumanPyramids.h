#ifndef HumanPyramids_Included
#define HumanPyramids_Included

/**
 * 给定每个人恰好重 160 磅的人体金字塔，
 * 返回指定行和列处人员背部承受的重量
 * 人体金字塔中的列。行和列从零开始，因此，
 * 例如，weightOnBackOf(2, 0) 会给出以下人员背上的重量：
 * 金字塔从上往下第二行最左边的人。
 *
 * 如果参数超出范围，此函数应调用 error() 来
 * 报告错误。
 *
 * @param row 金字塔中该人员所在的从零开始的行。
 * @param col 金字塔中该人员所在的从零开始的列。
 * @param pyramidHeight 金字塔的高度。
 * @return 该人员背后的权重。
 */
double weightOnBackOf(int row, int col, int pyramidHeight);

#endif
