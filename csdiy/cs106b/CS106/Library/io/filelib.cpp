/*
 * 文件：filelib.cpp
 * -----------------
 * 此文件实现 filelib.h 接口。
 * 平台相关函数通过 filelib_* 函数处理
 * 定义于 filelibunix.cpp 和 filelibwindows.cpp。
 * 
 * @version 2016/11/20
 * - 修复 readEntireStream 方法中的小错误（对非文本文件失败）
 * @version 2016/11/12
 * - 添加 fileSize、readEntireStream
 * @version 2016/08/12
 * - 添加接受 path 参数的第二个 openFileDialog 重载
 * @version 2015/07/05
 * - 移除全局静态 Platform 变量，改为在需要时调用 getPlatform
 * - 将 appendSpace 函数移至 simpio
 * @version 2015/04/12
 * - 添加不带流参数的 promptUserForFile 重载
 * @version 2014/10/19
 * - 按字母顺序排列函数声明
 * - 为提高效率，将许多函数的参数由 string 改为 const string&
 * - 添加返回 Vector 的 listDirectory 重载
 * @version 2014/10/08
 * - 移除“using namespace”语句
 */

#include "filelib.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include "simpio.h"
#include "strlib.h"
#include "private/filelibunix.cpp"
#include "private/filelibwindows.cpp"

/* 函数原型 */

static void splitPath(const std::string& path, Vector<std::string> list);
static bool recursiveMatch(const std::string& str, int sx, const std::string& pattern, int px);

/* 实现 */

void createDirectory(const std::string& path) {
    return platform::filelib_createDirectory(expandPathname(path));
}

void createDirectoryPath(const std::string& path) {
    size_t cp = 0;
    if (path == "") return;
    std::string expandedPath = expandPathname(path);
    char sep = getDirectoryPathSeparator()[0];
    if (expandedPath.substr(1, 2) == ":\\") { // Windows 驱动器号后跟 ':\\'
        cp = 2;
    }
    while ((cp = expandedPath.find(sep, cp + 1)) != std::string::npos) {
       createDirectory(expandedPath.substr(0, cp));
    }
    createDirectory(expandedPath);
}

std::string defaultExtension(const std::string& filename, const std::string& ext) {
    std::string extCopy = ext;
    bool force = (extCopy[0] == '*');
    if (force) extCopy = extCopy.substr(1);
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.') dot = i;
        if (ch == '/' || ch == '\\') dot = -1;
    }
    if (dot == -1) {
        force = true;
        dot = len;
    }
    if (force) {
        return filename.substr(0, dot) + extCopy;
    } else {
        return filename;
    }
}

void deleteFile(const std::string& filename) {
    platform::filelib_deleteFile(expandPathname(filename));
}

std::string expandPathname(const std::string& filename) {
    return platform::filelib_expandPathname(filename);
}

bool fileExists(const std::string& filename) {
    return platform::filelib_fileExists(filename);
}

int fileSize(const std::string& filename) {
    std::ifstream input;
    input.open(filename.c_str(), std::ifstream::binary);
    if (input.fail()) {
        return -1;
    } else {
        input.seekg(0, std::ifstream::end);
        return (int) input.tellg();
    }
}

std::string findOnPath(const std::string& path, const std::string& filename) {
    std::ifstream stream;
    std::string result = openOnPath(stream, path, filename);
    if (result != "") stream.close();
    return result;
}

std::string getAbsolutePath(const std::string& path) {
    return platform::filelib_getAbsolutePath(path);
}

std::string getCurrentDirectory() {
    return platform::filelib_getCurrentDirectory();
}

std::string getDirectoryPathSeparator() {
    return platform::filelib_getDirectoryPathSeparator();
}

std::string getExtension(const std::string& filename) {
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.') dot = i;
        if (ch == '/' || ch == '\\') dot = -1;
    }
    if (dot == -1) {
        return "";
    } else {
        return filename.substr(dot);
    }
}

std::string getHead(const std::string& filename) {
    size_t slash = std::string::npos;
    size_t len = filename.length();
    for (size_t i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '/' || ch == '\\') slash = i;
    }
    if (slash == std::string::npos) {
        return "";
    } else if (slash == 0) {
        return "/";
    } else {
        return filename.substr(0, slash);
    }
}

std::string getRoot(const std::string& filename) {
    int dot = -1;
    int len = filename.length();
    for (int i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '.') dot = i;
        if (ch == '/' || ch == '\\') dot = -1;
    }
    if (dot == -1) {
        return filename;
    } else {
        return filename.substr(0, dot);
    }
}

std::string getSearchPathSeparator() {
    return platform::filelib_getSearchPathSeparator();
}

std::string getTail(const std::string& filename) {
    size_t slash = std::string::npos;
    size_t len = filename.length();
    for (size_t i = 0; i < len; i++) {
        char ch = filename[i];
        if (ch == '/' || ch == '\\') slash = i;
    }
    if (slash == std::string::npos) {
        return filename;
    } else {
        return filename.substr(slash + 1);
    }
}

std::string getTempDirectory() {
    return platform::filelib_getTempDirectory();
}

bool isDirectory(const std::string& filename) {
    return platform::filelib_isDirectory(expandPathname(filename));
}

bool isFile(const std::string& filename) {
    return platform::filelib_isFile(expandPathname(filename));
}

bool isSymbolicLink(const std::string& filename) {
    return platform::filelib_isSymbolicLink(filename);
}

void listDirectory(const std::string& path, Vector<std::string>& list) {
    list.clear();
    return platform::filelib_listDirectory(expandPathname(path), list);
}

Vector<std::string> listDirectory(const std::string& path) {
    Vector<std::string> vec;
    listDirectory(path, vec);
    return vec;
}

bool matchFilenamePattern(const std::string& filename, const std::string& pattern) {
    return recursiveMatch(filename, 0, pattern, 0);
}

bool openFile(std::ifstream& stream, const std::string& filename) {
    stream.clear();
    stream.open(expandPathname(filename).c_str());
    return !stream.fail();
}

bool openFile(std::ofstream& stream, const std::string& filename) {
    stream.clear();
    stream.open(expandPathname(filename).c_str());
    return !stream.fail();
}

std::string openFileDialog(std::ifstream& stream) {
    return openFileDialog(stream, "Open File", "");
}

std::string openFileDialog(std::ifstream& stream,
                           const std::string& title) {
    return openFileDialog(stream, title, "");
}

std::string openFileDialog(std::ifstream& stream,
                           const std::string& title,
                           const std::string& path) {
    std::string filename = platform::file_openFileDialog(title, "load", path);
    if (filename == "") return "";
    stream.open(filename.c_str());
    return (stream.fail()) ? "" : filename;
}

std::string openFileDialog(const std::string& title,
                           const std::string& path) {
    std::string filename = platform::file_openFileDialog(title, "load", path);
    if (filename == "") return "";
    return (fileExists(filename)) ? filename : "";
}

std::string openFileDialog(std::ofstream& stream) {
    return openFileDialog(stream, "Open File", "");
}

std::string openFileDialog(std::ofstream& stream,
                           const std::string& title) {
    return openFileDialog(stream, title, "");
}

std::string openFileDialog(std::ofstream& stream,
                           const std::string& title,
                           const std::string& path) {
    std::string filename = platform::file_openFileDialog(title, "save", path);
    if (filename == "") return "";
    stream.open(filename.c_str());
    return (stream.fail()) ? "" : filename;
}

std::string openOnPath(std::ifstream& stream,
                       const std::string& path,
                       const std::string& filename) {
    Vector<std::string> paths;
    splitPath(path, paths);
    for (std::string dir : paths) {
        std::string pathname = dir + "/" + filename;
        if (openFile(stream, pathname)) return pathname;
    }
    return "";
}

std::string openOnPath(std::ofstream& stream,
                       const std::string& path,
                       const std::string& filename) {
    Vector<std::string> paths;
    splitPath(path, paths);
    for (std::string dir : paths) {
        std::string pathname = dir + "/" + filename;
        if (openFile(stream, pathname)) return pathname;
    }
    return "";
}

std::string promptUserForFile(std::ifstream& stream,
                              const std::string& prompt,
                              const std::string& reprompt) {
    std::string promptCopy = prompt;
    std::string repromptCopy = reprompt;
    if (reprompt == "") {
        repromptCopy = "Unable to open that file.  Try again.";
    }
    appendSpace(promptCopy);
    while (true) {
        std::cout << promptCopy;
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            openFile(stream, filename);
            if (!stream.fail()) return filename;
            stream.clear();
        }
        std::cout << repromptCopy << std::endl;
        if (promptCopy == "") promptCopy = "Input file: ";
    }
}

std::string promptUserForFile(std::ofstream& stream,
                              const std::string& prompt,
                              const std::string& reprompt) {
    std::string promptCopy = prompt;
    std::string repromptCopy = reprompt;
    if (reprompt == "") {
        repromptCopy = "Unable to open that file.  Try again.";
    }
    appendSpace(promptCopy);
    while (true) {
        std::cout << promptCopy;
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            openFile(stream, filename);
            if (!stream.fail()) return filename;
            stream.clear();
        }
        std::cout << repromptCopy << std::endl;
        if (promptCopy == "") promptCopy = "Output file: ";
    }
}

std::string promptUserForFile(const std::string& prompt,
                              const std::string& reprompt) {
    std::string promptCopy = prompt;
    std::string repromptCopy = reprompt;
    if (reprompt == "") {
        repromptCopy = "Unable to open that file.  Try again.";
    }
    appendSpace(promptCopy);
    while (true) {
        std::cout << promptCopy;
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            std::ifstream stream;
            openFile(stream, filename);
            if (!stream.fail()) {
                stream.close();
                return filename;
            }
        }
        std::cout << repromptCopy << std::endl;
        if (promptCopy == "") promptCopy = "Input file: ";
    }
}

void readEntireFile(std::istream& is, Vector<std::string>& lines) {
    lines.clear();
    while (true) {
        std::string line;
        getline(is, line);
        if (is.fail()) break;
        lines.add(line);
    }
}

std::string readEntireFile(const std::string& filename) {
    std::string out;
    if (readEntireFile(filename, out)) {
        return out;
    } else {
        error(std::string("input file not found or cannot be opened: ") + filename);
        return "";
    }
}

bool readEntireFile(const std::string& filename, std::string& out) {
    std::ifstream input;
    input.open(filename.c_str());
    if (input.fail()) {
        return false;
    }
    readEntireStream(input, out);
    input.close();
    return true;
}

std::string readEntireStream(std::istream& input) {
    std::string out;
    readEntireStream(input, out);
    return out;
}

void readEntireStream(std::istream& input, std::string& out) {
    std::ostringstream output;
    while (true) {
        int ch = input.get();
        if (input.fail()) {
            break;
        }
        output.put(ch);
    }
    out = output.str();
}

void renameFile(const std::string& oldname, const std::string& newname) {
    std::string oldExpand = expandPathname(oldname);
    std::string newExpand = expandPathname(newname);
    rename(oldExpand.c_str(), newExpand.c_str());
}

void rewindStream(std::istream& input) {
    input.clear();                  // 移除当前所有 EOF/失败标志
    input.seekg(0, std::ios::beg);  // 指示流定位回开头
}

void setCurrentDirectory(const std::string& path) {
    return platform::filelib_setCurrentDirectory(path);
}

bool writeEntireFile(const std::string& filename,
                     const std::string& text,
                     bool append) {
    std::ofstream output;
    if (append) {
        output.open(filename.c_str(), std::ios_base::out | std::ios_base::app);
    } else {
        output.open(filename.c_str());
    }
    if (output.fail()) {
        return false;
    }
    output << text;
    output.close();
    return !output.fail();
}

/* 私有函数 */

static void splitPath(const std::string& path, Vector<std::string> list) {
    char sep = (path.find(';') == std::string::npos) ? ':' : ';';
    std::string pathCopy = path + sep;
    size_t start = 0;
    while (true) {
        size_t finish = pathCopy.find(sep, start);
        if (finish == std::string::npos) break;
        if (finish > start + 1) {
            list.add(pathCopy.substr(start, finish - start - 1));
        }
        start = finish + 1;
    }
}

static bool recursiveMatch(const std::string& str, int sx, const std::string& pattern, int px) {
    int slen = str.length();
    int plen = pattern.length();
    if (px == plen) return (sx == slen);
    char pch = pattern[px];
    if (pch == '*') {
        for (int i = sx; i <= slen; i++) {
            if (recursiveMatch(str, i, pattern, px + 1)) return true;
        }
        return false;
    }
    if (sx == slen) return false;
    char sch = str[sx];
    if (pch == '[') {
        bool match = false;
        bool invert = false;
        px++;
        if (px == plen) {
            error("matchFilenamePattern: missing ]");
        }
        if (pattern[px] == '^') {
            px++;
            invert = true;
        }
        while (px < plen && pattern[px] != ']') {
            if (px + 2 < plen && pattern[px + 1] == '-') {
                match |= (sch >= pattern[px] && sch <= pattern[px + 2]);
                px += 3;
            } else {
                match |= (sch == pattern[px]);
                px++;
            }
        }
        if (px == plen) {
            error("matchFilenamePattern: missing ]");
        }
        if (match == invert) return false;
    } else if (pch != '?') {
        if (pch != sch) return false;
    }
    return recursiveMatch(str, sx + 1, pattern, px + 1);
}
