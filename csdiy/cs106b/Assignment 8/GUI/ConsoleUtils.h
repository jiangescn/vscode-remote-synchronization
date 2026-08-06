/**
 * 用于构建控制台程序的实用工具。
 */
#pragma once

#include "vector.h"
#include "simpio.h"
#include <string>
#include <vector>

/* 给定选项列表，反复提示用户直到其选择一个选项，然后
 * 返回所选项的索引。
 */
int makeSelectionFrom(const std::string& title, const Vector<std::string>& options);
int makeSelectionFrom(const std::string& title, const std::vector<std::string>& options);

/* 提示用户从给定目录中选择文件。 */
std::string makeFileSelection(const std::string& suffix, const std::string& directory = "res/");
