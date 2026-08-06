/*
 * 文件：version.h
 * ---------------
 * 版本消息报告
 * Stanford C++ 库。
 *
 */

#ifndef _version_h
#define _version_h
#include <string>

namespace version {

    std::string getLibraryInfoPanelMessage();
    std::string getLibraryVersion();
}

#endif // _version_h
