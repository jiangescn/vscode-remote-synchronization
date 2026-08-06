/*
 * 文件：filelibwindows.cpp
 * ------------------------
 * 此文件包含 filelib.h 基础功能的 Windows 实现。
 * 在 Java 后端退役之前，此代码位于 platform.cpp 中。
 *
 * @version 2018/10/23
 * - 添加 getAbsolutePath
 */

#include "filelib.h"

// 仅在 Windows 操作系统上定义以下全部内容
// （非 Windows 版本请参阅 filelibunix.cpp）
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#include <tchar.h>
#undef MOUSE_EVENT
#undef KEY_EVENT
#undef MOUSE_MOVED
#undef HELP_KEY
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ios>
#include <string>
#include "error.h"
#include "strlib.h"

namespace platform {

void filelib_createDirectory(const std::string& path) {
    std::string pathStr = path;
    if (endsWith(path, "\\")) {
        pathStr = path.substr(0, path.length() - 1);
    }
    if (CreateDirectoryA(path.c_str(), nullptr) == 0) {
        if (GetLastError() == ERROR_ALREADY_EXISTS && filelib_isDirectory(pathStr)) {
            return;
        }
        error("createDirectory: Can't create " + path);
    }
}

void filelib_deleteFile(const std::string& path) {
    if(filelib_isDirectory(path)) {
        RemoveDirectoryA(path.c_str());
    } else {
        DeleteFileA(path.c_str());
    }
}

std::string filelib_expandPathname(const std::string& filename) {
    if (filename.empty()) {
        return "";
    }
    std::string filenameStr = filename;
    for (int i = 0, len = filename.length(); i < len; i++) {
        if (filenameStr[i] == '/') {
            filenameStr[i] = '\\';
        }
    }
    return filenameStr;
}

bool filelib_fileExists(const std::string& filename) {
    return GetFileAttributesA(filename.c_str()) != INVALID_FILE_ATTRIBUTES;
}

std::string filelib_getAbsolutePath(const std::string& path) {
    char realpathOut[4096];
    if (_fullpath(realpathOut, path.c_str(), 4095)) {
        std::string absPath(realpathOut);
        return absPath;
    } else {
        return path;
    }
}

std::string filelib_getCurrentDirectory() {
    char path[MAX_PATH + 1];
    int n = GetCurrentDirectoryA(MAX_PATH + 1, path);
    return std::string(path, n);
}

std::string filelib_getDirectoryPathSeparator() {
    return "\\";
}

std::string filelib_getSearchPathSeparator() {
    return ";";
}

std::string filelib_getTempDirectory() {
    char path[MAX_PATH + 1];
    int n = GetTempPathA(MAX_PATH + 1, path);
    return std::string(path, n);
}

bool filelib_isDirectory(const std::string& filename) {
    DWORD attr = GetFileAttributesA(filename.c_str());
    return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY);
}

// https://msdn.microsoft.com/en-us/library/windows/desktop/gg258117(v=vs.85).aspx
bool filelib_isFile(const std::string& filename) {
    DWORD attr = GetFileAttributesA(filename.c_str());
    return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool filelib_isSymbolicLink(const std::string& filename) {
    DWORD attr = GetFileAttributesA(filename.c_str());
    return attr != INVALID_FILE_ATTRIBUTES
            && (attr & FILE_ATTRIBUTE_REPARSE_POINT);
}

void filelib_listDirectory(const std::string& path, Vector<std::string> & list) {
    std::string pathStr = path;
    if (pathStr == "") {
        pathStr = ".";
    }
    std::string pattern = pathStr + "\\*.*";
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern.c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) {
        error("listDirectory: Can't list directory \"" + pathStr + "\"");
    }
    list.clear();
    while (true) {
        std::string name = std::string(fd.cFileName);
        if (name != "." && name != "..") {
            list.add(name);
        }
        if (!FindNextFileA(h, &fd)) {
            break;
        }
    }
    FindClose(h);
    sort(list.begin(), list.end());
}

std::string file_openFileDialog(const std::string& /*标题*/,
                                const std::string& /*模式*/,
                                const std::string& /*路径*/) {
    // TODO（待办）
    return "";
}

void filelib_setCurrentDirectory(const std::string& path) {
    if (!filelib_isDirectory(path) || !SetCurrentDirectoryA(path.c_str())) {
        error("setCurrentDirectory: Can't change to " + path);
    }
}

} // 命名空间 platform

#endif // _WIN32
