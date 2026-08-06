/*
 * 文件：mainwrapper.cpp
 * ---------------------
 * 此文件包含一个 `main` 函数定义，用于初始化
 * Stanford C++ 库，然后运行学生的 main 函数
 * 在其自己的线程中。这是 Qt 版本库正常运行所必需的
 * 函数正常工作。
 *
 * @version 2018/10/18
 * - 多 main 初始实现
 * @version 2018/10/07
 * - 修复自动评分器模式中的错误
 * @version 2018/09/23
 * - 修复 Windows Qt main 包装器中的错误
 * @version 2018/09/17
 * - 初始版本
 */

// 将 main 包装函数移动到独立模块，以便
// 当且仅当最终链接满足以下条件时，链接器才会引入此模块
// 可执行文件缺少 main/qMain 定义。通常这会
// 通过一些预处理器技巧发生，原本的内容
// 学生编写的 main() 将被重命名为 studentMain()，从而导致
// 使 main 未定义，并链接此版本，它将调用
// libraryMain() 执行设置，然后调用 studentMain。

int libraryMain(int, char **);

int main(int argc, char **argv)
{
    return libraryMain(argc, argv);
}

// Windows 启动时，入口点名为 qMain()
// 两者都能供应，另一个闲置也没关系
int qMain(int argc, char **argv)
{
    return libraryMain(argc, argv);
}
