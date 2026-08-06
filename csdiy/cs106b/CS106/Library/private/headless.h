/*
 * 文件：headless.h
 * ----------------
 * 此文件包含一些用于在无 GUI 的“无头”模式下运行的代码。
 *
 * @version 2018/11/22
 * - 初始版本
 */


#ifndef _headless_h
#define _headless_h

#ifdef SPL_HEADLESS_MODE

// 构造一个 Qt 版本号
#define QT_VERSION 5110

// 让 Qt 版本宏生成低于此值的版本
#define QT_VERSION_CHECK(a, b, c) 5090

#endif // SPL_HEADLESS_MODE

#endif // _headless_h
