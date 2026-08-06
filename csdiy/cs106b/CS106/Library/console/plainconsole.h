/*
 * 文件：plainconsole.h
 * --------------------
 * 此文件声明用于为
 * C++ 纯文本控制台流：cin/cout/cerr。
 * 每个函数的实现见 plainconsole.cpp。
 *
 * @author Marty Stepp
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2015/10/21
 * @since 2015/10/21
 */


#ifndef _plainconsole_h
#define _plainconsole_h

namespace plainconsole {
/**
 * 设置 cout 控制台：如果打印字符数超过给定数量，则抛出错误
 * 总共曾向其中输出的字符数。
 * 这可用于停止试图无限输出的学生程序。
 */
void setOutputLimit(int limit);

/**
 * 设置从 cin 读取的用户输入值是否回显到 cout。
 * 这在捕获输出对话框以进行比较/diff 时很有用。
 */
void setEcho(bool value);
} // 命名空间 plainconsole

#endif // _plainconsole_h
