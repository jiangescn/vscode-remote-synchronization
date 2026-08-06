#ifndef GUIMain_Included
#define GUIMain_Included

#include "ProblemHandler.h"
#include <memory>

/* 锁定/解锁所有演示选项按钮。只能从主 GUI 线程调用。 */
void setDemoOptionsEnabled(bool isEnabled);

/* 仅供内部使用。 */
namespace MiniGUI {
    namespace Detail {
        /* 设置当前活动演示。MiniGUI 客户端不应使用此函数。 */
        void setActiveDemo(std::shared_ptr<ProblemHandler> handler);

        /* 获取 MiniGUI 窗口。MiniGUI 客户端不应使用此函数。 */
        GWindow& graphicsWindow();

        /* 图形主循环。 */
        [[ noreturn ]] void graphicsMain(std::function<void()> initialDemo);
    }
}



#endif
