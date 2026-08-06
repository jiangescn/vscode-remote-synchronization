/*
 * 文件：os.cpp
 * ------------
 * 此文件实现 os.h 中声明的 OS 类。
 * 
 * @author Marty Stepp
 * @version 2018/11/22
 * - 添加无界面（非 Qt）模式支持
 * @version 2018/09/23
 * - 修复 isMac 的错误
 * @version 2018/09/17
 * - 初始版本
 */

#include "os.h"
#ifndef SPL_HEADLESS_MODE
#include <QString>
#include <QSysInfo>
#endif // SPL_HEADLESS_MODE
#include "strlib.h"

#if !defined(SPL_HEADLESS_MODE) && QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
/*静态*/ std::string OS::getName() {
    std::string productName = QSysInfo::prettyProductName().toStdString();
    return productName;
}

/*静态*/ std::string OS::getVersion() {
    std::string productVersion = QSysInfo::productVersion().toStdString();
    return productVersion;
}

bool OS::isLinux() {
    std::string kernelType = toLowerCase(QSysInfo::kernelType().toStdString());
    std::string productType = toLowerCase(QSysInfo::productType().toStdString());
    return kernelType == "linux" || productType == "linux";
}

bool OS::isMac() {
    std::string kernelType = toLowerCase(QSysInfo::kernelType().toStdString());
    std::string productType = toLowerCase(QSysInfo::productType().toStdString());
    return stringContains(kernelType, "apple")
            || stringContains(kernelType, "darwin")
            || stringContains(kernelType, "mac")
            || stringContains(kernelType, "ios")
            || stringContains(productType, "apple")
            || stringContains(productType, "ios")
            || stringContains(productType, "mac")
            || stringContains(productType, "osx");
}

bool OS::isWindows() {
    std::string kernelType = toLowerCase(QSysInfo::kernelType().toStdString());
    std::string productType = toLowerCase(QSysInfo::productType().toStdString());
    return stringContains(kernelType, "windows")
            || stringContains(productType, "windows");
}
#else
/*静态*/ std::string OS::getName() {
    return "unknown";
}

/*静态*/ std::string OS::getVersion() {
    return "unknown";
}

bool OS::isLinux() {
    return false;
}

bool OS::isMac() {
    return false;
}

bool OS::isWindows() {
    return true;   // 大多数旧版 Qt 出现在旧 Windows 安装中
}
#endif // QT_VERSION

OS::OS() {
    // 空
}
