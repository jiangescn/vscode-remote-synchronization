/*
 * 文件：gconsolewindow.cpp
 * ------------------------
 * 此文件实现 gconsolewindow.h 接口。
 *
 * @author Marty Stepp
 * @version 2019/04/25
 * - 添加 hasInputScript
 * @version 2019/04/16
 * - 修复 Mac 深色模式下文本颜色错误的问题
 * @version 2019/04/10
 * - 支持使用图标条图像中的图标创建工具栏
 * @version 2019/04/09
 * - 修复输入脚本/比较输出窗口过早弹出的错误
 * - 将 Mac 默认字体从 Menlo 改为 Courier New
 * @version 2018/12/27
 * - 修复打印文本导致 waitForEvent 对排队事件无限等待的错误
 *   输出到控制台（Keith Schwarz 报告的问题）
 * @version 2018/10/11
 * - 修复关闭标志、输入脚本快捷键（例如 Ctrl+1）的错误
 * @version 2018/10/04
 * - 将默认自动换行改为 true
 * @version 2018/09/27
 * - 修复打印含换行符的字符串（移除 \r，优先使用 \n）
 * @version 2018/09/23
 * - 添加 getFont
 * - 修复加载输入脚本的错误
 * - 修复 Mac 上默认字体的错误
 * @version 2018/09/18
 * - 修复窗口大小/位置
 * @version 2018/09/17
 * - 修复 Mac OS X 上等宽字体的问题
 * @version 2018/08/23
 * - 初始版本，从 console.cpp 中分离
 */

#include "gconsolewindow.h"
#include <cstdio>
#include <QAction>
#include <QTextDocumentFragment>
#include "error.h"
#include "exceptions.h"
#include "filelib.h"
#include "gclipboard.h"
#include "gcolor.h"
#include "gcolorchooser.h"
#include "gfilechooser.h"
#include "gfont.h"
#include "gfontchooser.h"
#include "goptionpane.h"
#include "gthread.h"
#include "os.h"
#include "qtgui.h"
#include "private/static.h"
#include "private/version.h"

void setConsolePropertiesQt();

/*静态*/ const bool GConsoleWindow::ALLOW_RICH_INPUT_EDITING = true;
/*静态*/ const double GConsoleWindow::DEFAULT_WIDTH = 900;
/*静态*/ const double GConsoleWindow::DEFAULT_HEIGHT = 550;
/*静态*/ const double GConsoleWindow::DEFAULT_X = 10;
/*静态*/ const double GConsoleWindow::DEFAULT_Y = 40;
/*静态*/ const std::string GConsoleWindow::CONFIG_FILE_NAME = "spl-jar-settings.txt";
/*静态*/ const std::string GConsoleWindow::DEFAULT_FONT_FAMILY = "Monospace";
/*静态*/ const std::string GConsoleWindow::DEFAULT_FONT_WEIGHT = "";
/*静态*/ const int GConsoleWindow::DEFAULT_FONT_SIZE = 12;
/*静态*/ const int GConsoleWindow::MIN_FONT_SIZE = 4;
/*静态*/ const int GConsoleWindow::MAX_FONT_SIZE = 255;
/*静态*/ const std::string GConsoleWindow::DEFAULT_ERROR_COLOR = "#cc0000";
/*静态*/ const std::string GConsoleWindow::DEFAULT_ERROR_COLOR_DARK_MODE = "#f47862";
/*静态*/ const std::string GConsoleWindow::DEFAULT_USER_INPUT_COLOR = "#0000cc";
/*静态*/ const std::string GConsoleWindow::DEFAULT_USER_INPUT_COLOR_DARK_MODE = "#2c90e5";
/*静态*/ GConsoleWindow* GConsoleWindow::_instance = nullptr;
/*静态*/ bool GConsoleWindow::_consoleEnabled = false;

/*静态*/ bool GConsoleWindow::consoleEnabled() {
    return _consoleEnabled;
}

/*静态*/ std::string GConsoleWindow::getDefaultFont() {
    if (OS::isMac()) {
        // 出于某种原因，在 Mac 测试中使用“Monospace”对我不起作用
        return "Courier New-"
                + std::to_string(DEFAULT_FONT_SIZE + 1)
                + (DEFAULT_FONT_WEIGHT.empty() ? "" : ("-" + DEFAULT_FONT_WEIGHT));
    } else {
        return DEFAULT_FONT_FAMILY
                + "-" + std::to_string(DEFAULT_FONT_SIZE)
                + (DEFAULT_FONT_WEIGHT.empty() ? "" : ("-" + DEFAULT_FONT_WEIGHT));
    }
}

/*静态*/ GConsoleWindow* GConsoleWindow::instance() {
    if (!_instance) {
        // 初始化 Qt 系统和 Qt Console 窗口
        GThread::runOnQtGuiThread([]() {
            if (!_instance) {
                QtGui::instance()->initializeQt();
                _instance = new GConsoleWindow();
                setConsolePropertiesQt();
            }
        });
    }
    return _instance;
}

/*静态*/ bool GConsoleWindow::isInitialized() {
    return _instance != nullptr;
}

/*静态*/ void GConsoleWindow::setConsoleEnabled(bool enabled) {
    _consoleEnabled = enabled;
}

GConsoleWindow::GConsoleWindow()
        : GWindow(/* 可见 */ false),
          _textArea(nullptr),
          _clearEnabled(true),
          _echo(false),
          _locationSaved(false),
          _locked(false),
          _promptActive(false),
          _shutdown(false),
          _commandHistoryIndex(-1),
          _errorColor(""),
          _outputColor(""),
          _userInputColor(""),
          _inputBuffer(""),
          _lastSaveFileName(""),
          _cinout_new_buf(nullptr),
          _cerr_new_buf(nullptr),
          _cin_old_buf(nullptr),
          _cout_old_buf(nullptr),
          _cerr_old_buf(nullptr) {
    _initMenuBar();
    _initWidgets();
    _initStreams();
    loadConfiguration();
}

void GConsoleWindow::_initMenuBar() {
    addToolbar();

    // 文件菜单
    addMenu("&File");
    addMenuItem("File", "&Save", QPixmap(":/save"),
                [this]() { this->save(); })
                ->setShortcut(QKeySequence::Save);

    addMenuItem("File", "Save &As...", QPixmap(":/save_as"),
                [this]() { this->saveAs(); })
                ->setShortcut(QKeySequence::SaveAs);
    addMenuSeparator("File");

    addMenuItem("File", "&Print", QPixmap(":/print"),
                [this]() { this->showPrintDialog(); })
                ->setShortcut(QKeySequence::Print);
    setMenuItemEnabled("File", "Print", false);
    addMenuSeparator("File");

    addMenuItem("File", "&Quit", QPixmap(":/quit"),
                [this]() { this->close(); /* TODO：退出应用程序 */ })
                ->setShortcut(QKeySequence::Quit);

    // 编辑菜单
    addMenu("&Edit");
    addMenuItem("Edit", "Cu&t", QPixmap(":/cut"),
                [this]() { this->clipboardCut(); })
                ->setShortcut(QKeySequence::Cut);
    //   Console 没有可用的剪切操作，不添加到工具栏

    addMenuItem("Edit", "&Copy", QPixmap(":/copy"),
                [this]() { this->clipboardCopy(); })
                ->setShortcut(QKeySequence::Copy);
    addToolbarItem("Copy", QPixmap(":/copy"),
                       [this]() { this->clipboardCopy(); });

    addMenuItem("Edit", "&Paste", QPixmap(":/paste"),
                [this]() { this->clipboardPaste(); })
                ->setShortcut(QKeySequence::Paste);
    addToolbarItem("Paste", QPixmap(":/paste"),
                       [this]() { this->clipboardPaste(); });

    addMenuItem("Edit", "Select &All", QPixmap(":/select_all"),
                [this]() { this->selectAll(); })
                ->setShortcut(QKeySequence::SelectAll);

    addMenuItem("Edit", "C&lear Console", QPixmap(":/clear_console"),
                [this]() { this->clearConsole(); })
                ->setShortcut(QKeySequence(QString::fromStdString("Ctrl+L")));
    addToolbarItem("Clear Console", QPixmap(":/clear_console"),
                       [this]() { this->clearConsole(); });
    addToolbarSeparator();

    // 选项菜单
    addMenu("&Options");
    addMenuItem("Options", "&Font...", QPixmap(":/font"),
                [this]() { this->showFontDialog(); });
    addToolbarItem("Font...", QPixmap(":/font"),
                       [this]() { this->showFontDialog(); });

    addMenuItem("Options", "&Background Color...", QPixmap(":/background_color"),
                [this]() { this->showColorDialog(/* 背景 */ true); });
    addToolbarItem("Background Color...", QPixmap(":/background_color"),
                       [this]() { this->showColorDialog(/* 背景 */ true); });

    addMenuItem("Options", "&Text Color...", QPixmap(":/text_color"),
                [this]() { this->showColorDialog(/* 背景 */ false); });
    addToolbarItem("Text Color...", QPixmap(":/text_color"),
                       [this]() { this->showColorDialog(/* 背景 */ false); });
    addToolbarSeparator();

    // 帮助菜单
    addMenu("&Help");
    addMenuItem("Help", "&About...", QPixmap(":/about"),
                [this]() { this->showAboutDialog(); })
                ->setShortcut(QKeySequence::HelpContents);
    addToolbarItem("About...", QPixmap(":/about"),
                       [this]() { this->showAboutDialog(); });

}

void GConsoleWindow::_initStreams() {
    // 缓冲 C 风格 stderr
    static char stderrBuf[BUFSIZ + 10] = {'\0'};
    std::ios::sync_with_stdio(false);
    setbuf(stderr, stderrBuf);

    // 重定向 cin/cout/cerr
    _cinout_new_buf = new stanfordcpplib::qtgui::ConsoleStreambufQt();
    _cerr_new_buf = new stanfordcpplib::qtgui::ConsoleStreambufQt(/* isStderr */ true);
    _cin_old_buf = std::cin.rdbuf(_cinout_new_buf);
    _cout_old_buf = std::cout.rdbuf(_cinout_new_buf);
    _cerr_old_buf = std::cerr.rdbuf(_cerr_new_buf);
}

void GConsoleWindow::_initWidgets() {
    _textArea = new GTextArea();
    _outputColor = _textArea->getColor();

    // BUG 修复：使用操作系统默认背景色/前景色（有助于 Mac 深色模式）
    _textArea->setBackground(GWindow::getDefaultInteractorBackgroundColorInt());
    _textArea->setColor(GWindow::getDefaultInteractorTextColorInt());
    _textArea->setContextMenuEnabled(false);
    _textArea->setLineWrap(true);
    _textArea->setFont(getDefaultFont());
    QTextEdit* rawTextEdit = static_cast<QTextEdit*>(_textArea->getWidget());
    rawTextEdit->setTabChangesFocus(false);
    _textArea->setKeyListener([this](GEvent event) {
        if (event.getEventType() == KEY_PRESSED) {
            this->processKeyPress(event);
        } else if (event.getEventType() == KEY_RELEASED
                   || event.getEventType() == KEY_TYPED) {
            event.ignore();
        }
    });
    _textArea->setMouseListener([](GEvent event) {
        // 禁用基于鼠标的操作：
        // - 通过右键单击弹出上下文菜单
        // - Linux 风格的复制/粘贴操作：选择后单击中键
        if (event.getButton() > 1
                || event.getEventType() == MOUSE_RELEASED) {
            event.ignore();
        }
    });
    addToRegion(_textArea, "Center");

    // 让窗口关闭时自行退出
    setWindowListener([this](GEvent event) {
        if (event.getEventType() == WINDOW_CLOSING) {
            shutdown("Close");
        }
    });

    setTitle(QCoreApplication::applicationName().toStdString() + " Console");
    setCloseOperation(GWindow::CLOSE_HIDE);
    setLocation(DEFAULT_X, DEFAULT_Y);
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setVisible(true);
}


GConsoleWindow::~GConsoleWindow() {
    // TODO：删除？
    _cinout_new_buf = nullptr;
    _cerr_new_buf = nullptr;
    _cin_old_buf = nullptr;
    _cout_old_buf = nullptr;
    _cerr_old_buf = nullptr;
}


void GConsoleWindow::clearConsole() {
    std::string msg = "==================== (console cleared) ====================";
    if (_clearEnabled) {
        // 打印到标准控制台（不是 Stanford 图形控制台）
        printf("%s\n", msg.c_str());

        // 清空图形控制台窗口
        _coutMutex.lock();
        _textArea->clearText();
        _coutMutex.unlock();
    } else {
        // 不要真正清空窗口，只在其上显示“已清空”消息
        println(msg);
    }
}

void GConsoleWindow::clipboardCopy() {
    std::string selectedText = _textArea->getSelectedText();
    if (!selectedText.empty()) {
        GClipboard::set(selectedText);
    }
}

void GConsoleWindow::clipboardCut() {
    if (_shutdown || !_promptActive || !ALLOW_RICH_INPUT_EDITING) {
        return;
    }

    // 如果选区完全位于用户输入区域内，则从用户输入区域剪切
    int userInputStart = getUserInputStart();
    int userInputEnd   = getUserInputEnd();
    int selectionStart = _textArea->getSelectionStart();
    int selectionEnd = _textArea->getSelectionEnd();
    if (selectionEnd > selectionStart
            && selectionStart >= userInputStart
            && selectionEnd <= userInputEnd) {
        // 选区完全是用户输入！剪切它！
        QTextFragment frag = getUserInputFragment();
        if (frag.isValid()) {
            std::string selectedText = _textArea->getSelectedText();
            QTextEdit* textArea = static_cast<QTextEdit*>(this->_textArea->getWidget());
            QTextCursor cursor(textArea->textCursor());

            int indexStart = selectionStart - userInputStart;
            int selectionLength = _textArea->getSelectionLength();
            _cinMutex.lockForWrite();
            _inputBuffer.erase(indexStart, selectionLength);
            cursor.beginEditBlock();
            cursor.removeSelectedText();
            cursor.endEditBlock();
            textArea->setTextCursor(cursor);
            _cinMutex.unlock();
            GClipboard::set(selectedText);
        }
    }
}

void GConsoleWindow::clipboardPaste() {
    if (_shutdown) {
        return;
    }

    _textArea->clearSelection();
    if (!isCursorInUserInputArea()) {
        _textArea->moveCursorToEnd();
    }

    std::string clipboardText = GClipboard::get();
    for (int i = 0; i < (int) clipboardText.length(); i++) {
        if (clipboardText[i] == '\r') {
            continue;
        } else if (clipboardText[i] == '\n') {
            processUserInputEnterKey();
        } else {
            processUserInputKey(clipboardText[i]);
        }
    }
}

void GConsoleWindow::close() {
    shutdown("Close");
    GWindow::close();   // 调用父类实现
}

std::string GConsoleWindow::getBackground() const {
    return _textArea->getBackground();
}

int GConsoleWindow::getBackgroundInt() const {
    return _textArea->getBackgroundInt();
}

std::string GConsoleWindow::getColor() const {
    return getOutputColor();
}

int GConsoleWindow::getColorInt() const {
    return GColor::convertColorToRGB(getOutputColor());
}

std::string GConsoleWindow::getErrorColor() const {
    if (!_errorColor.empty()) {
        return _errorColor;
    } else {
        return GWindow::isDarkMode() ? DEFAULT_ERROR_COLOR_DARK_MODE : DEFAULT_ERROR_COLOR;
    }
}

std::string GConsoleWindow::getFont() const {
    return _textArea->getFont();
}

std::string GConsoleWindow::getForeground() const {
    return getOutputColor();
}

int GConsoleWindow::getForegroundInt() const {
    return GColor::convertColorToRGB(getOutputColor());
}

std::string GConsoleWindow::getOutputColor() const {
    return _outputColor.empty() ? GWindow::getDefaultInteractorTextColor() : _outputColor;
}

std::string GConsoleWindow::getUserInputColor() const {
    if (!_userInputColor.empty()) {
        return _userInputColor;
    } else {
        return GWindow::isDarkMode() ? DEFAULT_USER_INPUT_COLOR_DARK_MODE : DEFAULT_USER_INPUT_COLOR;
    }
}

QTextFragment GConsoleWindow::getUserInputFragment() const {
    if (!_inputBuffer.empty()) {
        QTextEdit* textArea = static_cast<QTextEdit*>(this->_textArea->getWidget());
        QTextBlock block = textArea->document()->end().previous();
        while (block.isValid()) {
            QTextBlock::iterator it;
            for (it = block.begin(); !(it.atEnd()); ++it) {
                QTextFragment frag = it.fragment();
                if (frag.isValid()) {
                    std::string fragText = frag.text().toStdString();

                    // 查看它是否为给定用户输入
                    if (fragText == _inputBuffer) {
                        return frag;
                    }
                }
            }
            block = block.previous();
        }
    }

    // 未找到片段；这将返回一个“无效”片段
    QTextFragment notFound;
    return notFound;
}

int GConsoleWindow::getUserInputStart() const {
    QTextFragment frag = getUserInputFragment();
    if (frag.isValid()) {
        return frag.position();
    } else if (_promptActive) {
        // 位于文本末尾
        return (int) _textArea->getText().length();
    } else {
        return -1;
    }
}

int GConsoleWindow::getUserInputEnd() const {
    QTextFragment frag = getUserInputFragment();
    if (frag.isValid()) {
        return frag.position() + frag.length();
    } else if (_promptActive) {
        // 位于文本末尾
        return (int) _textArea->getText().length();
    } else {
        return -1;
    }
}

bool GConsoleWindow::isClearEnabled() const {
    return _clearEnabled;
}

bool GConsoleWindow::isCursorInUserInputArea() const {
    int cursorPosition = _textArea->getCursorPosition();
    int userInputStart = getUserInputStart();
    int userInputEnd   = getUserInputEnd();
    return _promptActive
            && userInputStart <= cursorPosition
            && cursorPosition <= userInputEnd;
}

bool GConsoleWindow::isEcho() const {
    return _echo;
}

bool GConsoleWindow::isLocationSaved() const {
    return _locationSaved;
}

bool GConsoleWindow::isLocked() const {
    return _locked;
}

bool GConsoleWindow::isSelectionInUserInputArea() const {
    int userInputStart = getUserInputStart();
    int userInputEnd   = getUserInputEnd();
    int selectionStart = _textArea->getSelectionStart();
    int selectionEnd = _textArea->getSelectionEnd();
    return userInputStart >= 0 && userInputEnd >= 0
            && selectionStart >= userInputStart
            && selectionEnd <= userInputEnd;
}

void GConsoleWindow::loadConfiguration() {
    std::string configFile = getTempDirectory() + "/" + CONFIG_FILE_NAME;
    if (fileExists(configFile)) {
        std::ifstream infile;
        infile.open(configFile.c_str());
        if (!infile) {
                return;
        }
        std::string line;
        while (getline(infile, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') {
                continue;
            }
            Vector<std::string> tokens = stringSplit(line, "=");
            if (tokens.size() < 2) {
                continue;
            }
            std::string key   = toLowerCase(tokens[0]);
            std::string value = tokens[1];
            if (key == "font") {
                setFont(value);
            } else if (key == "background") {
                setBackground(value);
            } else if (key == "foreground") {
                setForeground(value);
            }
        }
    }
}



void GConsoleWindow::print(const std::string& str, bool isStdErr) {
    if (_echo) {
        fflush(isStdErr ? stdout : stderr);
        fflush(isStdErr ? stderr : stdout);
        fprintf(isStdErr ? stderr : stdout, "%s", str.c_str());
        if (str.find("\n") != std::string::npos) {
            fflush(isStdErr ? stderr : stdout);
            fflush(isStdErr ? stdout : stderr);
        }
    }

    // 清理换行符（移除 \r）
    std::string strToPrint = str;
    stringReplaceInPlace(strToPrint, "\r\n", "\n");
    stringReplaceInPlace(strToPrint, "\r", "\n");

    GThread::runOnQtGuiThread([this, strToPrint, isStdErr]() {
        _coutMutex.lock();
        _allOutputBuffer << strToPrint;
        if (!this->_textArea) {
            return;
        }
        this->_textArea->setEventsEnabled(false);
        this->_textArea->appendFormattedText(strToPrint, isStdErr ? getErrorColor() : getOutputColor());
        this->_textArea->moveCursorToEnd();
        this->_textArea->scrollToBottom();
        this->_textArea->setEventsEnabled(true);
        _coutMutex.unlock();
    });
}

void GConsoleWindow::println(bool isStdErr) {
    print("\n", isStdErr);
}

void GConsoleWindow::println(const std::string& str, bool isStdErr) {
    print(str + "\n", isStdErr);
}

void GConsoleWindow::processKeyPress(GEvent event) {
    char key = event.getKeyChar();
    int keyCode = event.getKeyCode();

    if (event.isCtrlOrCommandKeyDown()) {
        if (keyCode == Qt::Key_Plus || keyCode == Qt::Key_Equal) {
            // 增大字体大小
            event.ignore();
            QFont font = GFont::toQFont(_textArea->getFont());
            if (font.pointSize() + 1 <= MAX_FONT_SIZE) {
                font.setPointSize(font.pointSize() + 1);
                setFont(GFont::toFontString(font));
            }
        } else if (keyCode == Qt::Key_Minus) {
            // 减小字体大小
            event.ignore();
            QFont font = GFont::toQFont(_textArea->getFont());
            if (font.pointSize() - 1 >= MIN_FONT_SIZE) {
                font.setPointSize(font.pointSize() - 1);
                setFont(GFont::toFontString(font));
            }
        } else if (keyCode == Qt::Key_Insert) {
            // Ctrl+Ins => 复制
            event.ignore();
            clipboardCopy();
        } else if (keyCode == Qt::Key_0) {
            // 规范化字号
            event.ignore();
            setFont(DEFAULT_FONT_FAMILY + "-" + std::to_string(DEFAULT_FONT_SIZE));
        } else if (keyCode == Qt::Key_C) {
            event.ignore();
            clipboardCopy();
        } else if (event.isCtrlKeyDown() && keyCode == Qt::Key_D) {
            event.ignore();
            processEof();
        } else if (keyCode == Qt::Key_L) {
            event.ignore();
            clearConsole();
        } else if (keyCode == Qt::Key_Q || keyCode == Qt::Key_W) {
            event.ignore();
            close();
        } else if (keyCode == Qt::Key_S) {
            event.ignore();
            if (event.isShiftKeyDown()) {
                saveAs();
            } else {
                save();
            }
        } else if (keyCode == Qt::Key_V) {
            event.ignore();
            clipboardPaste();
        } else if (keyCode == Qt::Key_X) {
            event.ignore();
            clipboardCut();
        }
    }

    if (_shutdown) {
        return;
    }

    if (event.isCtrlOrCommandKeyDown() || event.isAltKeyDown()) {
        // 系统快捷键；让普通键盘处理程序处理此事件
        event.ignore();
        return;
    }

    switch (keyCode) {
        case GEvent::PAGE_UP_KEY:
        case GEvent::PAGE_DOWN_KEY:
            // 不要忽略事件
            break;
        case GEvent::BACKSPACE_KEY: {
            event.ignore();
            processBackspace(keyCode);
            break;
        }
        case GEvent::DELETE_KEY: {
            event.ignore();
            if (event.isShiftKeyDown()) {
                clipboardCut();   // Shift+Del => 剪切
            } else {
                processBackspace(keyCode);
            }
            break;
        }
        case GEvent::INSERT_KEY: {
            event.ignore();
            if (event.isShiftKeyDown()) {
                clipboardPaste();   // Shift+Ins => 粘贴
            }
            break;
        }
        case GEvent::HOME_KEY:
            if (ALLOW_RICH_INPUT_EDITING) {
                // 移动到输入缓冲区开头
                if (_promptActive) {
                    event.ignore();
                    int start = getUserInputStart();
                    if (start >= 0) {
                        _textArea->setCursorPosition(
                                start,
                                /* keepAnchor */ event.isShiftKeyDown() && isCursorInUserInputArea());
                    } else {
                        _textArea->moveCursorToEnd();
                    }
                }
            } else {
                event.ignore();
            }
            break;
        case GEvent::END_KEY:
            if (ALLOW_RICH_INPUT_EDITING) {
                // 移动到输入缓冲区末尾
                if (_promptActive) {
                    event.ignore();
                    int end = getUserInputEnd();
                    if (end >= 0) {
                        _textArea->setCursorPosition(
                                end,
                                /* keepAnchor */ event.isShiftKeyDown() && isCursorInUserInputArea());
                    } else {
                        _textArea->moveCursorToEnd();
                    }
                }
            } else {
                event.ignore();
            }
            break;
        case GEvent::LEFT_ARROW_KEY: {
            // 若提示处于活动状态，则限制在用户输入区域内
            if (ALLOW_RICH_INPUT_EDITING) {
                if (isCursorInUserInputArea()) {
                    int cursorPosition = _textArea->getCursorPosition();
                    int userInputStart = getUserInputStart();
                    if (cursorPosition <= userInputStart) {
                        event.ignore();
                        if (!event.isShiftKeyDown()) {
                            _textArea->clearSelection();
                        }
                    }
                }
            } else {
                event.ignore();
            }
            break;
        }
        case GEvent::RIGHT_ARROW_KEY:
            // 若提示处于活动状态，则限制在用户输入区域内
            if (ALLOW_RICH_INPUT_EDITING) {
                if (isCursorInUserInputArea()) {
                    int cursorPosition = _textArea->getCursorPosition();
                    int userInputEnd   = getUserInputEnd();
                    if (cursorPosition >= userInputEnd) {
                        event.ignore();
                        if (!event.isShiftKeyDown()) {
                            _textArea->clearSelection();
                        }
                    }
                }
            } else {
                event.ignore();
            }
            break;
        case GEvent::UP_ARROW_KEY:
            if (isCursorInUserInputArea()) {
                event.ignore();
                processCommandHistory(/* 增量 */ -1);
            }
            break;
        case GEvent::DOWN_ARROW_KEY:
            if (isCursorInUserInputArea()) {
                event.ignore();
                processCommandHistory(/* 增量 */ 1);
            }
            break;
        case GEvent::TAB_KEY:
            // TODO：Tab 补全？
        case GEvent::CLEAR_KEY:
            break;
        case GEvent::F1_KEY: {
            event.ignore();
            showAboutDialog();
            break;
        }
        case GEvent::F2_KEY:
        case GEvent::F3_KEY:
        case GEvent::F4_KEY:
        case GEvent::F5_KEY:
        case GEvent::F6_KEY:
        case GEvent::F7_KEY:
        case GEvent::F8_KEY:
        case GEvent::F9_KEY:
        case GEvent::F10_KEY:
        case GEvent::F11_KEY:
        case GEvent::F12_KEY:
        case GEvent::HELP_KEY: {
            // 各种控制键/修饰键：不执行任何操作 / 消耗事件
            event.ignore();
            break;
        }
        case GEvent::SHIFT_KEY:
        case GEvent::CTRL_KEY:
        case GEvent::ALT_KEY:
        case GEvent::PAUSE_KEY:
        case GEvent::CAPS_LOCK_KEY:
        case GEvent::ESCAPE_KEY:
        case GEvent::NUM_LOCK_KEY:
        case GEvent::SCROLL_LOCK_KEY:
        case GEvent::PRINT_SCREEN_KEY:
        case GEvent::META_KEY:
        case GEvent::WINDOWS_KEY:
        case GEvent::MENU_KEY: {
            // 其他各种控制键/修饰键：让操作系统处理事件（不要调用 ignore()）
            break;
        }
        case GEvent::RETURN_KEY:
        case GEvent::ENTER_KEY: {
            // \n 行结束
            event.ignore();
            processUserInputEnterKey();
            break;
        }
        default: {
            event.ignore();
            processUserInputKey(key);
            break;
        }
    }
}

void GConsoleWindow::processBackspace(int key) {
    if (_shutdown || !_promptActive) {
        return;
    }

    // 检查它是退格键还是删除键
    bool isBackspace = key == GEvent::BACKSPACE_KEY /* TODO：或者计算机是 Mac */;

    _cinMutex.lockForWrite();
    if (!_inputBuffer.empty()) {
        // 从屏幕文本编辑器中删除最后一个字符：
        // - 查找最后一个蓝色区域
        QTextFragment frag = getUserInputFragment();
        if (frag.isValid()) {
            // 从屏幕文档片段中删除最后一个字符
            QTextEdit* textArea = static_cast<QTextEdit*>(this->_textArea->getWidget());
            QTextCursor cursor(textArea->textCursor());

            int oldCursorPosition = cursor.position();
            int indexToDelete = (int) _inputBuffer.length() - 1;
            int userInputIndexMin = frag.position();
            int userInputIndexMax = frag.position() + frag.length() - (isBackspace ? 0 : 1);

            if (oldCursorPosition >= userInputIndexMin && oldCursorPosition < userInputIndexMax) {
                // 光标位于用户输入片段内；
                // 确定它位于哪个字符，以便删除该字符
                indexToDelete = oldCursorPosition - frag.position() - (isBackspace ? 1 : 0);
            } else {
                // 光标位于用户输入片段外；将其移动到那里
                cursor.setPosition(frag.position() + frag.length());
            }

            if (indexToDelete >= 0 && indexToDelete < (int) _inputBuffer.length()) {
                if (isBackspace || indexToDelete == (int) _inputBuffer.length() - 1) {
                    cursor.deletePreviousChar();
                } else {
                    cursor.deleteChar();   // 删除
                }

                // 从内部输入缓冲区删除最后一个字符
                _inputBuffer.erase(indexToDelete, 1);
            }
        }
    }
    _cinMutex.unlock();
}

void GConsoleWindow::processCommandHistory(int delta) {
    if (_shutdown) {
        return;
    }
    _cinMutex.lockForRead();
    std::string oldCommand = "";
    _commandHistoryIndex += delta;
    _commandHistoryIndex = std::max(-1, _commandHistoryIndex);
    _commandHistoryIndex = std::min(_commandHistoryIndex, _inputCommandHistory.size());
    if (0 <= _commandHistoryIndex && _commandHistoryIndex < _inputCommandHistory.size()) {
        oldCommand = _inputCommandHistory[_commandHistoryIndex];
    }
    _cinMutex.unlock();
    setUserInput(oldCommand);
}

void GConsoleWindow::processEof() {
    if (_shutdown) {
        return;
    }
    // 仅当输入缓冲区为空时设置 EOF；这是大多数 *nix 控制台的行为
    if (_inputBuffer.empty()) {
        std::cin.setstate(std::ios_base::eofbit);
    }
}

void GConsoleWindow::processUserInputEnterKey() {
    if (_shutdown) {
        return;
    }
    _cinMutex.lockForWrite();
    _cinQueueMutex.lockForWrite();
    _inputLines.enqueue(_inputBuffer);
    _inputCommandHistory.add(_inputBuffer);
    _commandHistoryIndex = _inputCommandHistory.size();
    _cinQueueMutex.unlock();
    _allOutputBuffer << _inputBuffer << std::endl;
    _inputBuffer = "";   // 清空输入缓冲区
    this->_textArea->appendFormattedText("\n", getUserInputColor());
    _cinMutex.unlock();
}

void GConsoleWindow::processUserInputKey(int key) {
    if (_shutdown) {
        return;
    }
    if (key != '\0' && isprint(key)) {
        // 普通按键：追加到用户输入缓冲区
        _cinMutex.lockForWrite();

        std::string keyStr = charToString((char) key);

        bool inserted = false;
        if (ALLOW_RICH_INPUT_EDITING && isCursorInUserInputArea()) {
            QTextFragment frag = getUserInputFragment();
            if (frag.isValid()) {
                QTextEdit* textArea = static_cast<QTextEdit*>(this->_textArea->getWidget());
                QTextCursor cursor(textArea->textCursor());

                // BUG 修复：如果存在任何选中文本，先将其移除
                int fragStart = frag.position();
                int selectionStart = cursor.selectionStart() - fragStart;
                int selectionEnd = cursor.selectionEnd() - fragStart;
                if (selectionEnd > selectionStart
                        && selectionStart >= 0
                        && selectionEnd <= (int) _inputBuffer.length()) {
                    cursor.removeSelectedText();
                    _inputBuffer.erase(selectionStart, selectionEnd - selectionStart);
                }

                int cursorPosition = cursor.position();
                int indexToInsert = cursorPosition - frag.position();
                if (indexToInsert == 0) {
                    // 在片段开头插入的特殊情况。
                    // 示例：fragment 为“abcde”，光标在开头，用户输入“x”。
                    // 如果只在文档中插入 "x"，它不会成为
                    // 同一片段，并且不会采用蓝色粗体格式。
                    // 我们的做法是暂时将它插入第一个字符之后，
                    // 然后删除第一个字符，使所有内容都位于
                    // 格式化跨度。
                    // “abcde”
                    //  ^
                    //   ^          向右移动 1
                    // “axabcde”    在索引 1 处插入“xa”
                    //     ^
                    //   ^          向左移动 2
                    // “xabcde”     删除索引 0 处前一个字符“a”
                    //  ^
                    //   ^          向右移动 1
                    cursor.beginEditBlock();

                    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);             // 移动到索引 1
                    cursor.insertText(QString::fromStdString(keyStr + _inputBuffer.substr(0, 1)));   // 插入新字符 + 原首字符
                    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);              // 删除第一个字符的旧副本
                    cursor.deletePreviousChar();
                    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);             // 移动到索引 1
                    cursor.endEditBlock();
                    textArea->setTextCursor(cursor);
                } else {
                    cursor.beginEditBlock();
                    cursor.insertText(QString::fromStdString(keyStr));
                    cursor.endEditBlock();
                    textArea->setTextCursor(cursor);
                }
                _inputBuffer.insert(indexToInsert, keyStr);
                inserted = true;
            }
        }

        if (!inserted) {
            // 追加到缓冲区/片段末尾
            _inputBuffer += keyStr;
            // 以蓝色高亮文本显示
            this->_textArea->appendFormattedText(keyStr, getUserInputColor(), "*-*-Bold");
        }

        _cinMutex.unlock();
    }
}

std::string GConsoleWindow::readLine() {
    // TODO：线程/锁
    // 等待队列中有可用的一行
    std::string line;
    if (_shutdown) {
        return line;
    }

    this->_textArea->moveCursorToEnd();
    this->_textArea->scrollToBottom();
    this->toFront();   // 提示输入时将窗口移到前面
    this->_textArea->requestFocus();

    _cinMutex.lockForWrite();
    _promptActive = true;
    _cinMutex.unlock();

    while (!_shutdown && !std::cin.eof()) {
        bool lineRead = false;
        if (!_inputScript.isEmpty()) {
            _cinQueueMutex.lockForWrite();
            line = _inputScript.dequeue();
            lineRead = true;
            _cinQueueMutex.unlock();

            // 回显用户输入，就像用户刚刚输入它一样
            GThread::runOnQtGuiThreadAsync([this, line]() {
                _coutMutex.lock();
                _allOutputBuffer << line << std::endl;
                _textArea->appendFormattedText(line + "\n", getUserInputColor(), "*-*-Bold");
                _coutMutex.unlock();
            });
        }

        if (!_inputLines.isEmpty()) {
            _cinQueueMutex.lockForWrite();
            if (!_inputLines.isEmpty()) {
                line = _inputLines.dequeue();
                lineRead = true;
            }

            _cinQueueMutex.unlock();
        }

        if (lineRead) {
            break;
        } else {
            sleep(20);
        }
    }

    _cinMutex.lockForWrite();
    _promptActive = false;
    _cinMutex.unlock();
    this->_textArea->scrollToBottom();

    if (_echo) {
        fprintf(stdout, "%s\n", line.c_str());
    }
    return line;
}

void GConsoleWindow::save() {
    saveAs(_lastSaveFileName);
}

void GConsoleWindow::saveAs(const std::string& filename) {
    std::string filenameToUse;
    if (filename.empty()) {
        filenameToUse = GFileChooser::showSaveDialog(
                /* 父级 */ this->getWidget(),
                /* 标题 */ "",
                getHead(_lastSaveFileName));
    } else {
        filenameToUse = filename;
    }
    if (filenameToUse.empty()) {
        return;
    }

    std::string consoleText = _textArea->getText();
    writeEntireFile(filenameToUse, consoleText);
    _lastSaveFileName = filenameToUse;
}

void GConsoleWindow::saveConfiguration(bool prompt) {
    if (prompt && !GOptionPane::showConfirmDialog(
            /* 父级  */  getWidget(),
            /* 消息 */  "Make this the default for future console windows?",
            /* 标题   */  "Save configuration?")) {
        return;
    }
    std::string configFile = getTempDirectory() + "/" + CONFIG_FILE_NAME;
    std::string configText = "# Stanford C++ library configuration file\n"
            "background=" + _textArea->getBackground() + "\n"
            "foreground=" + getOutputColor() + "\n"
            "font=" + _textArea->getFont() + "\n";
    writeEntireFile(configFile, configText);
}

void GConsoleWindow::selectAll() {
    _textArea->selectAll();
}

void GConsoleWindow::setBackground(int color) {
    GWindow::setBackground(color);   // 调用父类实现
    _textArea->setBackground(color);
}

void GConsoleWindow::setBackground(const std::string& color) {
    GWindow::setBackground(color);   // 调用父类实现
    _textArea->setBackground(color);
}

void GConsoleWindow::setClearEnabled(bool clearEnabled) {
    if (_locked || _shutdown) {
        return;
    }
    _clearEnabled = clearEnabled;
}

void GConsoleWindow::setConsoleSize(double width, double height) {
    // TODO：基于文本区域的首选大小 / 打包窗口
    // _textArea->setPreferredSize(width, height);
    // pack();
    setSize(width, height);
}

void GConsoleWindow::setColor(int color) {
    setOutputColor(color);
}

void GConsoleWindow::setColor(const std::string& color) {
    setOutputColor(color);
}

void GConsoleWindow::setEcho(bool echo) {
    if (_locked || _shutdown) {
        return;
    }
    _echo = echo;
}

void GConsoleWindow::setFont(const QFont& font) {
    GWindow::setFont(font);   // 调用父类实现
    _textArea->setFont(font);
}

void GConsoleWindow::setFont(const std::string& font) {
    GWindow::setFont(font);   // 调用父类实现
    _textArea->setFont(font);
}

void GConsoleWindow::setForeground(int color) {
    setOutputColor(color);
}

void GConsoleWindow::setForeground(const std::string& color) {
    setOutputColor(color);
}

void GConsoleWindow::setLocationSaved(bool locationSaved) {
    _locationSaved = locationSaved;
}

void GConsoleWindow::setLocked(bool locked) {
    _locked = locked;
}

void GConsoleWindow::setErrorColor(const std::string& errorColor) {
    _errorColor = errorColor;
}

void GConsoleWindow::setOutputColor(int rgb) {
    setOutputColor(GColor::convertRGBToColor(rgb));
}

void GConsoleWindow::setOutputColor(const std::string& outputColor) {
    _outputColor = outputColor;
    _textArea->setForeground(outputColor);
    if (_shutdown) {
        return;
    }

    // 遍历所有过去片段并将其重新着色为此颜色

    // 选择之前所有文本并更改其颜色
    // （BUG？：还会把用户输入文本改成该颜色；这是预期行为吗？）
    QTextEdit* textArea = static_cast<QTextEdit*>(this->_textArea->getWidget());
    QTextCursor cursor = textArea->textCursor();
    cursor.beginEditBlock();
    cursor.setPosition(0);
    QTextCharFormat format = cursor.charFormat();
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    format.setForeground(QBrush(GColor::toQColor(outputColor)));
    textArea->setTextCursor(cursor);
    cursor.setCharFormat(format);
    cursor.endEditBlock();
    _textArea->moveCursorToEnd();
}

void GConsoleWindow::setSize(double width, double height) {
    if (isHighDpiScalingEnabled() && isHighDensityScreen()) {
        double ratio = getScreenDpiScaleRatio();
        width = std::min(getScreenWidth(), width * ratio);
        height = std::min(getScreenHeight(), height * ratio);;
    }

    // 调用父类实现
    GWindow::setSize(width, height);
}

void GConsoleWindow::setUserInput(const std::string& userInput) {
    if (_shutdown) {
        return;
    }
    _cinMutex.lockForWrite();
    QTextEdit* textArea = static_cast<QTextEdit*>(_textArea->getWidget());

    // 删除任何当前用户输入
    QTextFragment frag = getUserInputFragment();
    if (frag.isValid()) {
        QTextCursor cursor = textArea->textCursor();
        cursor.beginEditBlock();
        cursor.setPosition(frag.position(), QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, frag.length());
        cursor.removeSelectedText();
        cursor.endEditBlock();
        textArea->setTextCursor(cursor);
    }
    _inputBuffer.clear();
    _cinMutex.unlock();

    // 插入给定的用户输入
    for (int i = 0; i < (int) userInput.length(); i++) {
        processUserInputKey(userInput[i]);
    }
}

void GConsoleWindow::setUserInputColor(const std::string& userInputColor) {
    _userInputColor = userInputColor;
}

void GConsoleWindow::showAboutDialog() {
    // 此文本与旧版 spl.jar 消息中的文本大致匹配
    static const std::string ABOUT_MESSAGE = version::getLibraryInfoPanelMessage();
    GOptionPane::showMessageDialog(
                /* 父级 */   getWidget(),
                /* 消息 */  ABOUT_MESSAGE,
                /* 标题 */    "About Stanford C++ Library",
                /* 类型 */     GOptionPane::MESSAGE_ABOUT);
}

void GConsoleWindow::showColorDialog(bool background) {
    std::string color = GColorChooser::showDialog(
                /* 父级 */   getWidget(),
                /* 标题 */    "",
                /* 初始值 */  background ? _textArea->getBackground() : _textArea->getForeground());
    if (!color.empty()) {
        if (background) {
            setBackground(color);
        } else {
            setOutputColor(color);
        }
        saveConfiguration();   // 提示保存配置
    }
}

void GConsoleWindow::showFontDialog() {
    std::string font = GFontChooser::showDialog(
                /* 父级 */ getWidget(),
                /* 标题  */ "",
                /* initialFont */ _textArea->getFont());
    if (!font.empty()) {
        _textArea->setFont(font);
        saveConfiguration();   // 提示保存配置
    }
}

void GConsoleWindow::showPrintDialog() {
    // TODO（待办）
}

void GConsoleWindow::shutdown(const std::string& reason) {
    _shutdown = true;
    std::cout.flush();
    std::cerr.flush();

    // 恢复原来的 cin、cout、cerr
    if (_cin_old_buf) {
        _coutMutex.lock();
        std::cin.rdbuf(_cin_old_buf);
        std::cout.rdbuf(_cout_old_buf);
        std::cerr.rdbuf(_cerr_old_buf);
        _cin_old_buf = nullptr;
        _cout_old_buf = nullptr;
        _cerr_old_buf = nullptr;
        std::cout.flush();
        std::cerr.flush();
        _coutMutex.unlock();
    }

    _textArea->setEditable(false);
    std::string title = getTitle();
    if (title.find(reason) == std::string::npos) {
        setTitle(title + " [" + reason + "]");
    }

    // TODO：禁用某些菜单项
}

// ConsoleStreambufQt 使用的全局函数

namespace stanfordcpplib {
namespace qtgui {

void endLineConsoleQt(bool isStderr) {
    GConsoleWindow::instance()->println(isStderr);
}

std::string getLineConsoleQt() {
    return GConsoleWindow::instance()->readLine();
}

void putConsoleQt(const std::string& str, bool isStderr) {
    GConsoleWindow::instance()->print(str, isStderr);
}

} // namespace qtgui
} // namespace stanfordcpplib
