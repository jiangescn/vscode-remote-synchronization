#include <iostream>
#include "TowersOfHanoi.h"
using namespace std;

/* 常量：kPauseTime
 *
 * 开始汉诺塔动画时暂停的时间。
 */
const double kPauseTime = 500;

/* 此函数改编自教材第 8.1 章中的函数。如果你
 * 如果你还没有读过那一章，建议先阅读再开始
 * 这个问题。
 */
void moveTower(int numDisks, char start, char finish, char temp, int& totalMoves) {
    if (numDisks != 0) {
        moveTower(numDisks - 1, start, temp, finish, totalMoves);
        moveSingleDisk(start, finish);
        totalMoves++;
        moveTower(numDisks - 1, temp, finish, start, totalMoves);
    }
}

int solveTowersOfHanoi(int numDisks, char start, char finish, char temp) {
    /* 想让它慢下来？尝试为最后一个参数使用以下其他选项：
     *
     *   AnimationSpeed::MOLASSES         （极慢）
     *   AnimationSpeed::CHEETAH          （正常）
     *   AnimationSpeed::PEREGRINE_FALCON （极快）
     */
    initHanoiDisplay(numDisks, AnimationSpeed::CHEETAH);
    pause(kPauseTime);

    int totalMoves = 0;
    moveTower(numDisks, start, finish, temp, totalMoves);
    return totalMoves;
}
