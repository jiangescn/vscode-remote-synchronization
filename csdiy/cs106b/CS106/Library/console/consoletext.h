/*
 * 文件：consoletext.h
 * -------------------
 * 此文件提供一种使用 console.h 中函数的方式
 * 而不强制使用 Stanford C++ 库的
 * 图形控制台窗口。
 * 
 * @author Marty Stepp
 * @version 2018/08/31
 * - 初始版本
 */

#define __DONT_ENABLE_QT_GRAPHICAL_CONSOLE
#include "console.h"
#undef __DONT_ENABLE_QT_GRAPHICAL_CONSOLE
