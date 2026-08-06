/*
 * 文件：filelib.h
 * ---------------
 * 此文件导出一组用于处理
 * 文件。该库至少在以下平台之间提供一定可移植性：
 * 三个受支持平台使用的文件系统：Mac OSX、
 * Windows 和 Linux。目录路径和搜索路径允许
 * 包含任意受支持样式的分隔符，这通常
 * 使同一代码可在不同平台上使用。
 *
 * @version 2018/10/23
 * - 添加 getAbsolutePath
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2016/11/12
 * - 添加 fileSize、readEntireStream
 * @version 2016/08/12
 * - 添加接受 path 参数的第二个 openFileDialog 重载
 * @version 2015/04/12
 * - 添加不带流参数的 promptUserForFile 重载
 * @version 2014/10/19
 * - 按字母顺序排列函数声明
 * - 为提高效率，将许多函数的参数由 string 改为 const string&
 * - 添加返回 Vector 的 listDirectory 重载
 */


#ifndef _filelib_h
#define _filelib_h

#include <iostream>
#include <fstream>
#include <string>

#include "vector.h"

/**
 * 为指定路径创建新目录。该
 * 如果以下情况发生，<code>createDirectory</code> 函数不会报告错误：
 * 目录已存在。与 <code>createDirectoryPath</code> 不同，
 * <code>createDirectory</code> 不会创建缺失的目录
 * 沿路径。
 * @throw 如果 <code>path</code> 的某个组成部分不存在，则抛出 ErrorException
 */
void createDirectory(const std::string& path);

/**
 * 为指定路径创建新目录。如果中间目录
 * 如果 <code>path</code> 的组成部分不存在，此函数会创建
 * 按需使用它们。
 */
void createDirectoryPath(const std::string& path);

/**
 * 如果文件名尚无扩展名，则为其添加扩展名。如果
 * <code>extension</code> 参数以开头的 <code>*</code> 起始，
 * <code>filename</code> 中的任何现有扩展名会被替换为
 * <code>ext</code>。
 */
std::string defaultExtension(const std::string& filename, const std::string& ext);

/**
 * 删除指定文件。
 * @throw 如果文件不存在或无法删除，则抛出 ErrorException
 */
void deleteFile(const std::string& filename);

/**
 * 将文件名扩展为平台的规范名称。
 */
std::string expandPathname(const std::string& filename);

/**
 * 如果指定文件存在，则返回 <code>true</code>。
 */
bool fileExists(const std::string& filename);

/**
 * 返回给定文件的字节大小。
 * 如果文件不存在或无法读取，则返回 -1。
 */
int fileSize(const std::string& filename);

/**
 * 返回使用搜索路径找到的文件的规范名称。
 * <code>findOnPath</code> 函数类似于
 * 与 <code>openOnPath</code> 相同，但它实际上不会
 * 返回打开的流。如果找不到匹配文件，
 * <code>findOnPath</code> 返回空字符串。
 */
std::string findOnPath(const std::string& path, const std::string& filename);

/**
 * 返回给定文件或目录的绝对文件名。
 * 例如，此转换会将 "temp/foo.txt" 转换为 "/Users/jsmith12/Documents/temp/foo.txt"。
 */
std::string getAbsolutePath(const std::string& path);

/**
 * 返回当前目录的绝对文件名。
 */
std::string getCurrentDirectory();

/**
 * 返回此平台使用的标准目录路径分隔符。
 */
std::string getDirectoryPathSeparator();

/**
 * 返回 <code>filename</code> 的扩展名。扩展名
 * 由分隔点及其后的所有字符组成。
 * 如果最后一个路径组件中不存在点号，<code>getExtension</code>
 * 返回空字符串。这些语义确保连接
 * 根和扩展名，并始终返回原始文件名。
 */
std::string getExtension(const std::string& filename);

/**
 * 返回路径名除最后一个组件外的所有部分。各组件
 * 路径名的各部分可以使用任意目录路径分隔符分隔
 * 分隔符（正斜杠或反斜杠）。特殊情况包括
 * 如下例所示：
 *
 *<pre>
 *    getHead("a/b")  = "a"     getTail("a/b")   = "b"
 *    getHead("a")    = ""      getTail("a")     = "a"
 *    getHead("/a")   = "/"     getTail("/a")    = "a"
 *    getHead("/")    = "/"     getTail("/")     = ""
 *</pre>
 */
std::string getHead(const std::string& filename);

/**
 * 返回 <code>filename</code> 的根名。根名由以下内容组成
 * <code>filename</code> 中最后一个点号之前的所有内容，以及
 * 后续扩展名。如果最终组成部分中没有点号
 * 文件名；<code>getRoot</code> 返回完整名称。
 */
std::string getRoot(const std::string& filename);

/**
 * 返回此平台使用的标准搜索路径分隔符。
 */
std::string getSearchPathSeparator();

/**
 * 返回路径名的最后一个组件。路径的各组件
 * 路径名可以使用任意目录路径分隔符分隔
 * （正斜杠或反斜杠）。有关其解释的详细信息，
 * 特殊情况见 <code>getHead</code> 函数的注释。
 */
std::string getTail(const std::string& filename);

/**
 * 返回操作系统的“temp”文件夹。
 * 如果程序需要存储临时文件，这会很有用。
 */
std::string getTempDirectory();

/**
 * 如果指定文件是目录，则返回 <code>true</code>。
 */
bool isDirectory(const std::string& filename);

/**
 * 如果指定文件是常规文件，则返回 <code>true</code>，
 * 不是符号链接或目录。
 */
bool isFile(const std::string& filename);

/**
 * 如果指定文件是符号链接，则返回 <code>true</code>。
 */
bool isSymbolicLink(const std::string& filename);

/**
 * 按字母顺序添加指定目录中的文件列表
 * 添加到字符串 Vector <code>list</code> 中。此列表不包括
 * 名称为 <code>.</code> 和 <code>..</code> 的条目。
 */
void listDirectory(const std::string& path, Vector<std::string>& list);

/**
 * 按字母顺序添加指定目录中的文件列表
 * 添加到 Vector <code>list</code> 中。此列表不包括
 * 名称为 <code>.</code> 和 <code>..</code> 的条目。
 */
void listDirectory(const std::string& path, Vector<std::string>& list);

/**
 * 按字母顺序添加指定目录中的文件列表
 * 添加到返回的 Vector 中。此列表不包括
 * 名称为 <code>.</code> 和 <code>..</code> 的条目。
 */
Vector<std::string> listDirectory(const std::string& path);

/**
 * 确定文件名是否匹配指定模式。
 * 模式字符串的解释方式与 Unix shell 非常相似
 * 扩展文件名并支持以下通配符选项：
 *
 *<pre>
 *    ?      匹配任意单个字符
 *    *      匹配任意字符序列
 *    [...]  匹配任意指定字符
 *    [^...] 匹配指定字符<i>以外</i>的任意字符
 *</pre>
 *
 * 最后两个选项允许在
 * 形式 <code>a-z</code>。
 */
bool matchFilenamePattern(const std::string& filename, const std::string& pattern);

/**
 * 使用指定的参数打开文件输入流 <code>stream</code>
 * 文件名开头。此函数类似于 <code>open</code>
 * 与流类的方法相同，但使用 C++ <code>string</code>
 * 对象，而不是较旧的 C 风格字符串。如果该操作
 * 成功时，<code>openFile</code> 返回 <code>true</code>；
 * 若失败，<code>openFile</code> 会在以下对象中设置失败标志：
 * 流并返回 <code>false</code>。
 */
bool openFile(std::ifstream& stream, const std::string& filename);

/**
 * 使用指定的参数打开文件输出流 <code>stream</code>
 * 文件名开头。此函数类似于 <code>open</code>
 * 与流类的方法相同，但使用 C++ <code>string</code>
 * 对象，而不是较旧的 C 风格字符串。如果该操作
 * 成功时，<code>openFile</code> 返回 <code>true</code>；
 * 若失败，<code>openFile</code> 会在以下对象中设置失败标志：
 * 流并返回 <code>false</code>。
 */
bool openFile(std::ofstream& stream, const std::string& filename);

/**
 * 打开一个允许用户选择要读取文件的对话框。
 * 对话框从当前目录开始。
 */
std::string openFileDialog(std::ifstream& stream);

/**
 * 打开一个允许用户选择要读取文件的对话框。
 * <code>title</code> 参数显示在对话框标题中。
 * 对话框从当前目录开始。
 */
std::string openFileDialog(std::ifstream& stream,
                           const std::string& title);

/**
 * 打开一个允许用户选择要读取文件的对话框。
 * <code>title</code> 参数显示在对话框标题中。
 * <code>path</code> 参数用于设置工作目录。
 */
std::string openFileDialog(std::ifstream& stream,
                           const std::string& title,
                           const std::string& path);

/**
 * 打开一个允许用户选择要写入文件的对话框。
 * 对话框从当前目录开始。
 */
std::string openFileDialog(std::ofstream& stream);

/**
 * 打开一个允许用户选择要写入文件的对话框。
 * <code>title</code> 参数显示在对话框标题中。
 * 对话框从当前目录开始。
 */
std::string openFileDialog(std::ofstream& stream,
                           const std::string& title);

/**
 * 打开一个允许用户选择要写入文件的对话框。
 * <code>title</code> 参数显示在对话框标题中。
 * <code>path</code> 参数用于设置工作目录。
 */
std::string openFileDialog(std::ofstream& stream,
                           const std::string& title,
                           const std::string& path);

/**
 * 打开一个对话框，让用户选择要读取或写入的文件名。
 * <code>title</code> 参数显示在对话框标题中。
 * <code>path</code> 参数用于设置工作目录。
 * 如果省略 <code>path</code>，对话框将从当前目录开始。
 */
std::string openFileDialog(const std::string& title = "Open File ...",
                           const std::string& path = "");

/**
 * 使用搜索路径打开文件进行读取。如果 <code>openOnPath</code>
 * 成功时，返回搜索路径中第一个满足条件的路径名
 * 直到 <code>stream.open</code> 成功。<code>path</code>
 * 参数由一组目录组成，这些目录会添加到以下内容之前：
 * 文件名；除非 <code>filename</code> 以绝对路径的
 * 目录标记，例如 <code>/</code> 或 <code>~</code>。
 * 搜索路径中的目录可以由以下任一种方式分隔
 * 使用冒号（Unix 或 Mac OS）或分号（Windows）分隔。若文件
 * 无法打开时，会在 <code>stream</code> 中设置失败位
 * 参数，并且 <code>openOnPath</code> 函数返回
 * 空字符串。
 */
std::string openOnPath(std::ifstream& stream,
                       const std::string& path,
                       const std::string& filename);

/**
 * 使用搜索路径打开文件进行写入。如果 <code>openOnPath</code>
 * 成功时，返回搜索路径中第一个满足条件的路径名
 * 直到 <code>stream.open</code> 成功。<code>path</code>
 * 参数由一组目录组成，这些目录会添加到以下内容之前：
 * 文件名；除非 <code>filename</code> 以绝对路径的
 * 目录标记，例如 <code>/</code> 或 <code>~</code>。
 * 搜索路径中的目录可以由以下任一种方式分隔
 * 使用冒号（Unix 或 Mac OS）或分号（Windows）分隔。若文件
 * 无法打开时，会在 <code>stream</code> 中设置失败位
 * 参数，并且 <code>openOnPath</code> 函数返回
 * 空字符串。
 */
std::string openOnPath(std::ofstream& stream,
                       const std::string& path,
                       const std::string& filename);

/**
 * 询问用户要读取的文件名。
 * 使用引用参数 <code>stream</code> 打开文件。
 * 函数返回文件名。
 * 若无法打开请求的文件，则允许用户再次尝试
 * 输入有效文件名。
 *
 * 可选的 <code>prompt</code> 参数提供输入提示
 * 供用户使用。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 当用户输入不存在的文件时，每次都显示。
 * 若未传入值，则默认为“无法打开该文件，请重试。”。
 */
std::string promptUserForFile(std::ifstream& stream,
                              const std::string& prompt = "",
                              const std::string& reprompt = "");

/**
 * 询问用户要读取的文件名。
 * 使用引用参数 <code>stream</code> 打开文件。
 * 函数返回文件名。
 * 若无法打开请求的文件，则允许用户再次尝试
 * 输入有效文件名。
 *
 * 可选的 <code>prompt</code> 参数提供输入提示
 * 供用户使用。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 当用户输入不存在的文件时，每次都显示。
 * 若未传入值，则默认为“无法打开该文件，请重试。”。
 */
std::string promptUserForFile(std::ofstream& stream,
                              const std::string& prompt = "",
                              const std::string& reprompt = "");

/**
 * 询问用户要读取的文件名。
 * 函数返回文件名。
 * 若无法打开请求的文件，则允许用户再次尝试
 * 输入有效文件名。
 *
 * 可选的 <code>prompt</code> 参数提供输入提示
 * 供用户使用。
 *
 * 可选的 <code>reprompt</code> 参数用于提供输出消息
 * 当用户输入不存在的文件时，每次都显示。
 * 若未传入值，则默认为“无法打开该文件，请重试。”。
 */
std::string promptUserForFile(const std::string& prompt = "",
                              const std::string& reprompt = "");

/**
 * 将指定输入流的全部内容读取到
 * 字符串向量 <code>lines</code>。客户端负责
 * 打开和关闭流。
 */
void readEntireFile(std::istream& is, Vector<std::string>& lines);

/**
 * 将指定输入流的全部内容读取到
 * 字符串向量 <code>lines</code>。客户端负责
 * 打开和关闭流。
 */
void readEntireFile(std::istream& is, Vector<std::string>& lines);

/**
 * readEntireFile 的重载，直接将整个文件作为一个很长的内容返回
 * 一个长的单一字符串，而不是行向量。
 * @throw 如果找不到文件或无法读取，则抛出 ErrorException。
 */
std::string readEntireFile(const std::string& filename);

/**
 * readEntireFile 的重载，将整个文件读取为一个很长的
 * 一个长的单一字符串，而不是行向量。
 *
 * 此版本将读取的文本填入一个输出引用。
 * 如果读取成功则返回 true；如果文件未找到则返回 false
 * 或无法打开进行读取。
 */
bool readEntireFile(const std::string& filename, std::string& out);

/**
 * 读取给定流直到末尾，并将内容作为
 * 一个字符串。
 */
std::string readEntireStream(std::istream& input);

/**
 * 读取给定流直到末尾，并将内容存储
 * 通过引用写入给定字符串 'out'。
 */
void readEntireStream(std::istream& input, std::string& out);

/**
 * 重命名文件。
 * @throw 如果旧文件不存在、无法读取，
 *        新文件名已存在，
 *        或旧文件无法以其他方式重命名为新文件名
 */
void renameFile(const std::string& oldname, const std::string& newname);

/**
 * 将给定输入流移回开头，以便可以
 * 从头到尾再次读取。
 */
void rewindStream(std::istream& input);

/**
 * 将当前目录更改为指定路径。
 */
void setCurrentDirectory(const std::string& path);

/**
 * 打开给定文件并将给定文本写入其中。
 * 通常此函数会替换文件之前的所有内容，但
 * 如果传入可选的 'append' 参数，则给定文本会被添加
 * 添加到文件末尾，并保留之前的所有内容。
 * 如果写入成功则返回 true；如果文件无法写入则返回 false
 * 以写入方式打开。
 */
bool writeEntireFile(const std::string& filename,
                     const std::string& text,
                     bool append = false);

/**
 * 因操作系统而异的平台相关函数。
 * @private
 */
namespace platform {
    std::string file_openFileDialog(const std::string& title, const std::string& mode, const std::string& path);
    void filelib_createDirectory(const std::string& path);
    void filelib_deleteFile(const std::string& path);
    std::string filelib_expandPathname(const std::string& filename);
    bool filelib_fileExists(const std::string& filename);
    std::string filelib_getAbsolutePath(const std::string& path);
    std::string filelib_getCurrentDirectory();
    std::string filelib_getDirectoryPathSeparator();
    std::string filelib_getSearchPathSeparator();
    std::string filelib_getTempDirectory();
    bool filelib_isDirectory(const std::string& filename);
    bool filelib_isFile(const std::string& filename);
    bool filelib_isSymbolicLink(const std::string& filename);
    void filelib_listDirectory(const std::string& path, Vector<std::string>& list);
    void filelib_setCurrentDirectory(const std::string& path);
}

#endif // _filelib_h
