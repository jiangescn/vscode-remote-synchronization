/*
 * 文件：HanoiGraphics.h
 * --------------
 * 此文件定义图形版汉诺塔函数的接口。
 */

#ifndef HanoiGraphics_Included
#define HanoiGraphics_Included

#include "gwindow.h"

enum class AnimationSpeed {
    MOLASSES,
    CHEETAH,
    PEREGRINE_FALCON
};

/*
 * 函数：initHanoiDisplay
 * 用法：initHanoiDisplay(5, AnimationSpeed::MOLASSES);
 * -------------------------------
 * 初始化图形窗口并绘制起始配置
 * 用于 n 个圆盘的汉诺塔问题。速度由以下参数决定：
 * 最后一个参数。
 */

void initHanoiDisplay(int n, AnimationSpeed speed = AnimationSpeed::MOLASSES);

/*
 * 函数：moveSingleDisk
 * 用法：moveSingleDisk(char start, char finish);
 * -----------------------------------------------
 * 将一个圆盘从起始塔移动到目标塔
 * 塔。如果起始塔
 * 为空，或移动违反汉诺塔规则
 * 将较大圆盘放在较小圆盘上会违反谜题规则。
 */

void moveSingleDisk(char start, char finish);

int solveTowersOfHanoi(int numDisks, char start, char finish, char temp);

#endif
