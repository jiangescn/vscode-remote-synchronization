#include "Demos/MazeGenerator.h"
#include "GUI/SimpleTest.h"
using namespace std;

/* 将此常量改为包含你的姓名（以及搭档姓名，如果你
 * 两人一组完成）。
 *
 * 警告：一旦设置了此常量并开始探索迷宫，
 * 不要编辑 MyName 的值。更改 MyName 会改变你获得的迷宫
 * 取回的内容可能会使你之前的所有工作失效！
 *
 * 你可能会疑惑——为什么我们使用奇怪的类型 "const char MyName[]"
 * 而不是 "const string MyName"？两者均可，但我们使用的版本
 * 这里创建一个包含你姓名的原始字符数组，从而消除
 * 编译器警告消息。如想了解更多，请在 EdStem 上联系我们
 * 有关此内容的更多信息！
 */
const char MyName[] = "TODO: Replace this string with your name.";

/* 将这些常量改为包含迷宫出口路径。 */
const char ThePathOutOfMyMaze[] = "TODO: Replace this string with your path out of the normal maze.";
const char ThePathOutOfMyTwistyMaze[] = "TODO: Replace this string with your path out of the twisty maze.";

PROVIDED_TEST("Escape from the labyrinth!") {
    /* 供你逃脱的迷宫。该迷宫将针对你个性化生成
     * 基于常量 MyName。
     *
     * 不要在此行设置断点。应在以下位置之前设置：
     * 下方的 EXPECT 语句。
     */
    MazeCell* startLocation = mazeFor(MyName);

    /* 在下一行设置断点。提醒一下，你正在处理的迷宫
     * 获得的迷宫将针对你个性化，因此不要开始探索
     * 除非你已编辑常量 MyName 以包含你的姓名！
     * 否则，你会逃离错误的迷宫。
     *
     * 这是你将在里程碑二中逃离的迷宫。该迷宫
     * 将呈规则网格形状，指针指向
     * 你预期它们指向的方向。
     */
    EXPECT(isPathToFreedom(startLocation, ThePathOutOfMyMaze));

    /* 我们知道没有释放此迷宫中分配的任何内存，
     * 从而造成内存泄漏。由于这完全用于教学目的，
     * 这次我们会暂且接受，但通常不应编写这样的代码
     * 如下所示。
     */
}





PROVIDED_TEST("Escape from the twisty labyrinth!") {
    /* 不要在此处设置断点；请在 EXPECT 语句处设置。 */
    MazeCell* startLocation = twistyMazeFor(MyName);

    /* 此测试用例用于里程碑 3。
     *
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *  >>>> 在阅读以下内容之前，不要开始此部分：                 <<<<
     *  >>>> 里程碑 3 的说明，即讨论以下内容的部分：               <<<<
     *  >>>> 曲折迷宫（迷宫并非规则的                             <<<<
     *  >>>> 单元格网格。这里的迷宫具有不同结构                   <<<<
     *  >>>> 里程碑 2 中的迷宫，逃离它需要一套                    <<<<
     *  >>>> 不同的一组技能。                                     <<<<
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *
     * 这是你将在里程碑三中逃离的迷宫。
     * 迷宫不一定是矩形网格，并且每个单元格中的指针
     * 迷宫单元格的指针方向不一定与其标签所示方向一致。
     * 不过，你可以依赖这样一个事实：如果一个 MazeCell 链接到另一个
     * 第二个（以某种方式）直接链接回第一个。
     */
    EXPECT(isPathToFreedom(startLocation, ThePathOutOfMyTwistyMaze));

    /* 我们知道没有释放此迷宫中分配的任何内存，
     * 从而造成内存泄漏。由于这完全用于教学目的，
     * 这次我们会暂且接受，但通常不应编写这样的代码
     * 如下所示。
     */
}
