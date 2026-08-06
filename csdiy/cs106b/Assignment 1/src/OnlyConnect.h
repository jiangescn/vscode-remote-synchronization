/******************************************************************************
 * 文件：OnlyConnect.h
 * 作者：Keith Schwarz（htiek@cs.stanford.edu）
 *
 * 作业中 Only Connect 部分的头文件。你不应
 * 修改此文件。
 */

#ifndef OnlyConnect_Included
#define OnlyConnect_Included

#include <string>

/**
 * 给定字符串，通过删除所有以下内容将其转换为 Only Connect 谜题：
 * 处理非辅音，并将所有字符转为大写。
 *
 * @param phrase 要转换的短语。
 * @return 将该字符串渲染为 Only Connect 谜题后的结果。
 */
std::string onlyConnectize(std::string phrase);

#endif
