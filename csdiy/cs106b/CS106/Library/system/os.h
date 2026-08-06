/*
 * 文件：os.h
 * ----------
 * 此文件导出一个类，其中包含与
 * 当前操作系统。
 *
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/16
 * - 初始版本
 */


#ifndef _os_h
#define _os_h

#include <string>

/**
 * 此类包含一些有用的静态方法，用于查询正在运行的操作
 * 程序当前运行的系统。
 */
class OS {
public:
    /**
     * 返回表示当前操作系统名称的字符串。
     */
    static std::string getName();

    /**
     * 返回表示以下内容当前版本或发行版的字符串
     * 当前操作系统。
     */
    static std::string getVersion();

    /**
     * 如果当前操作系统看起来是 Linux，则返回 true。
     */
    static bool isLinux();

    /**
     * 如果当前操作系统看起来是 Mac OS X，则返回 true。
     */
    static bool isMac();

    /**
     * 如果当前操作系统看起来是 Windows，则返回 true。
     */
    static bool isWindows();

private:
    OS();   // 阻止构造
};

#endif // _os_h
