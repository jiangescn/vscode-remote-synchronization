#include "ExploreArrays.h"
#include "GUI/MiniGUI.h"
#include "ginteractors.h"
#include "random.h"
using namespace std;
using namespace MiniGUI;

namespace {
    /* 给用户的消息。 */
    const string kMessage = "Make sure you're running your code in debug mode before "
                            "hitting the 'Go!' button below. Otherwise, you won't be "
                            "able to do the array exploration you need to do.";
    const string kBackgroundColor = "white";

    const Font kMessageFont(FontFamily::SERIF, FontStyle::ITALIC, 24, "#400080");

    /* 用随机值填充大型栈帧的实用函数。这
     * 用于让未来调用中的局部变量值看起来更加
     * 比原本可能的值更随机。:-)
     */
    const int kLargeSize = 1024;
    int floodTheStack() {
        char buffer[kLargeSize];
        for (int i = 0; i < kLargeSize; i++) {
            buffer[i] = randomInteger(0, 255);
        }

        int result = 0;
        for (int i = 0; i < kLargeSize; i++) {
            result += buffer[i];
        }

        return result;
    }

    class ArrayExploreGUI: public ProblemHandler {
    public:
        ArrayExploreGUI(GWindow& window);

        void actionPerformed(GObservable* source) override;

    protected:
        void repaint() override;

    private:
        Temporary<GButton> mOutOfBounds,
                           mUninitializedPointer,
                           mDeallocatedPointer;
    };

    ArrayExploreGUI::ArrayExploreGUI(GWindow& window) : ProblemHandler(window) {
        mOutOfBounds          = make_temporary<GButton>(window, "SOUTH", "Go!");
    }

    void ArrayExploreGUI::actionPerformed(GObservable* source) {
        (void) floodTheStack();
        if (source == mOutOfBounds) {
            exploreArrays();
        }
    }

    void ArrayExploreGUI::repaint() {
        clearDisplay(window(), kBackgroundColor);
        try {
            auto render = TextRender::construct(kMessage, {
                                                    0, 0,
                                                    window().getCanvasWidth(), window().getCanvasHeight()
                                                }, kMessageFont);
            render->alignCenterVertically();
            render->alignCenterHorizontally();
            render->draw(window());
        } catch (...) {
            /* 糟糕，没有空间！*/
        }
    }
}

GRAPHICS_HANDLER("Explore Arrays", GWindow& window) {
    return make_shared<ArrayExploreGUI>(window);
}
