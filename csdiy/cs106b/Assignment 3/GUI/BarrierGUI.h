#pragma once

#include "MiniGUI.h"
#include <string>
#include <set>
#include <functional>

/* 运行给定文件中的所有测试。若全部通过，则使用
 * 指定工厂函数来创建 GUI。若未指定，则返回一个 GUI，该 GUI
 * 报告在所有测试通过前无法运行 GUI。
 */
std::function<std::shared_ptr<ProblemHandler>(GWindow&)>
ifPassedThen(const std::set<std::string>& filenames,
             std::function<std::shared_ptr<ProblemHandler>(GWindow&)> constructor);

/* ifPassedThen 的控制台版本。 */
std::function<void()>
ifPassedThen(const std::set<std::string>& filenames,
             std::function<void()> demo);
