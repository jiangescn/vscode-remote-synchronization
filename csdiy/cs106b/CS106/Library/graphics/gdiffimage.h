/*
 * 文件：gdiffimage.h
 * ------------------
 * 
 * @author Marty Stepp
 * @version 2018/10/12
 * - 添加“用颜色突出显示差异”复选框及功能
 * @version 2018/09/15
 * - 初始版本，由 Java 后端 DiffImage 类转换而来
 */


#ifndef _gdiffimage_h
#define _gdiffimage_h

#include <string>
#include <QWidget>
#include <QSplitter>

#include "gbutton.h"
#include "gcanvas.h"
#include "gcheckbox.h"
#include "ginteractor.h"
#include "glabel.h"
#include "gslider.h"
#include "gwindow.h"

/**
 * GDiffImage 是显示两幅图像差异的图形窗口
 * 图像。此类用于实现“比较图形输出”
 * 图形程序的特性，以及各种自动评分器比较。
 *
 * @private
 * TODO：编写文档
 */
class GDiffImage {
public:
    static const std::string HIGHLIGHT_COLOR_DEFAULT;

    static void showDialog(const std::string& name1,
                           GCanvas* image1,
                           const std::string& name2,
                           GCanvas* image2);

    static void showDialog(const std::string& name1,
                           const std::string& imageFile1,
                           const std::string& name2,
                           const std::string& imageFile2);

private:
    GDiffImage(const std::string& name1,
               GCanvas* image1,
               const std::string& name2,
               GCanvas* image2);   // 禁止构造
    virtual ~GDiffImage();

    Q_DISABLE_COPY(GDiffImage)

    void chooseHighlightColor();
    void drawImages();
    std::string getPixelString(GImage* image, int x, int y) const;

    GWindow* _window;
    GSlider* _slider;
    GCheckBox* _highlightDiffsBox;
    GButton* _colorButton;
    GLabel* _diffPixelsLabel;
    GLabel* _imageLabel1;
    GLabel* _imageLabel2;
    GLabel* _southPixelLabel;
    GImage* _image1;
    GImage* _image2;
    GImage* _imageDiffs;
    std::string _highlightColor;

    friend class GImage;
};

#endif // _gdiffimage_h
