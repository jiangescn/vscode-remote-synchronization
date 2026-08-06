#ifndef EmptyProblemHandler_Included
#define EmptyProblemHandler_Included

#include "ProblemHandler.h"

/* 一个问题处理程序，仅提示用户选择要解决的问题。此处理程序
 * 在没有其他内容可显示时安装。
 */
class EmptyProblemHandler: public ProblemHandler {
public:
    EmptyProblemHandler(GWindow& window): ProblemHandler(window) {}

protected:
    void repaint() override;
};



#endif
