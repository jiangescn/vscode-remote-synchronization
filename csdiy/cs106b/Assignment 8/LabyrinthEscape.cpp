#include "Demos/MazeGenerator.h"
#include "GUI/SimpleTest.h"
using namespace std;

/* 修改这个常量，填入你的姓名（如果是两人合作，还要填入搭档的姓名）。
 *
 * 警告：设置好这个常量并开始探索迷宫后，请不要再修改 MyName 的值。
 * 修改 MyName 会改变生成的迷宫，可能让你之前的所有努力全部失效！
 *
 * 你可能会疑惑：为什么这里使用看起来有些奇怪的类型
 * "const char MyName[]"，而不是 "const string MyName"？两种写法都可以，
 * 但这里采用的版本会创建一个存放姓名的原始字符数组，从而消除一条编译器
 * 警告。如果想进一步了解原因，欢迎在 EdStem 上联系我们！
 */
const char MyName[] = "Jianges";

/* 修改这些常量，填入逃出两个迷宫的路径。 */
const char ThePathOutOfMyMaze[] = "WSSSENSWNNEENSSENNSSWSE";
const char ThePathOutOfMyTwistyMaze[] = "SWSSWEWWSNEEWEW";

PROVIDED_TEST("Escape from the labyrinth!") {
    /* 这是一个需要你逃脱的迷宫。迷宫会根据常量 MyName 进行个性化生成。
     *
     * 不要在这一行设置断点；请把断点设置在下方 EXPECT 语句之前。
     */
    MazeCell* startLocation = mazeFor(MyName);

    /* 在下一行设置断点。再次提醒：生成的迷宫是为你个性化创建的，因此必须先
     * 修改常量 MyName，填入你们的姓名，然后才能开始探索迷宫！否则，你尝试
     * 逃脱的会是错误的迷宫。
     *
     * 这是你在里程碑 2 中需要逃脱的迷宫。它采用规则网格的形状，其中的指针
     * 会指向其标签所表示的正常方向。
     */
    EXPECT(isPathToFreedom(startLocation, ThePathOutOfMyMaze));

    /* 我们知道这里没有释放为迷宫分配的任何内存，因此会造成内存泄漏。
     * 由于这段代码只用于教学，我们暂时忽略这个问题；但通常不应编写这样的代码。
     */
}





PROVIDED_TEST("Escape from the twisty labyrinth!") {
    /* 不要在这里设置断点；请在 EXPECT 语句处设置断点。 */
    MazeCell* startLocation = twistyMazeFor(MyName);

    /* 这个测试用例用于里程碑 3。
     *
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *  >>>> 阅读里程碑 3 中关于扭曲迷宫的说明之前，请不要开始本节。   <<<<
     *  >>>> 扭曲迷宫并不是由单元格组成的规则网格，其结构与里程碑 2   <<<<
     *  >>>> 中的迷宫不同，因此逃脱它需要使用另一组技能。             <<<<
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
     *
     * 这是你在里程碑 3 中需要逃脱的迷宫。它不一定是矩形网格，而且每个
     * 迷宫单元格中的指针也不一定指向其标签所表示的方向。不过，可以确定：
     * 如果一个 MazeCell 连接到另一个 MazeCell，那么后者也会以某种方式
     * 直接连接回前者。
     */
    EXPECT(isPathToFreedom(startLocation, ThePathOutOfMyTwistyMaze));

    /* 我们知道这里没有释放为迷宫分配的任何内存，因此会造成内存泄漏。
     * 由于这段代码只用于教学，我们暂时忽略这个问题；但通常不应编写这样的代码。
     */
}
