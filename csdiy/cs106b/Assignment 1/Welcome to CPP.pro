###############################################################################
# CS106B/X 学生程序的项目文件
#
# @version 2021 秋季学期，适用于 Qt 6
# @author Julie Zelenski
#   使用已安装的静态库构建客户端程序
###############################################################################

SPL_VERSION = 2021.1
SPL_URL = https://web.stanford.edu/dept/cs_edu/qt

TEMPLATE    =   app
QT          +=  core gui widgets network
CONFIG      +=  silent debug         # 始终使用静默构建和调试符号
CONFIG      -=  depend_includepath   # 库头文件不会变化，不添加依赖关系

###############################################################################
#       查找/使用已安装版本的 cs106 库及头文件                #
###############################################################################

# 库通过 QtStandardPaths 安装到每个用户可写的数据位置
win32|win64     { QTP_EXE = qtpaths.exe } else { QTP_EXE = qtpaths }
USER_DATA_DIR   =   $$system($$[QT_INSTALL_BINS]/$$QTP_EXE --writable-path GenericDataLocation)

SPL_DIR         =   $${USER_DATA_DIR}/cs106
STATIC_LIB      =   $$system_path($${SPL_DIR}/lib/libcs106.a)
SPL_VERSION_FILE =  $$system_path($${SPL_DIR}/lib/version$${SPL_VERSION})

# 构建前使用额外目标作为先决条件，确认库是否存在
check_lib.target    =  "$${STATIC_LIB}"
check_lib.commands  =  $(error No CS106 library found. Install CS106 package following instructions at $${SPL_URL})
QMAKE_EXTRA_TARGETS +=  check_lib
PRE_TARGETDEPS       +=  $${check_lib.target}

# 确认当前库版本
check_version.target    =  "$${SPL_VERSION_FILE}"
check_version.commands  =  $(error Cannot find version $${SPL_VERSION} of CS106 library. Install CS106 package following instructions at $${SPL_URL})
QMAKE_EXTRA_TARGETS +=  check_version
PRE_TARGETDEPS       +=  $${check_version.target}

# 链接 libcs106.a，并将库头文件目录加入搜索路径
# libcs106 依赖 libpthread，在此添加链接选项
LIBS            +=  -lcs106 -lpthread
QMAKE_LFLAGS    =   -L$$shell_quote($${SPL_DIR}/lib)
# 将 PWD 放在搜索列表首位，以便在需要时由本地副本覆盖
INCLUDEPATH     +=  $$PWD "$${SPL_DIR}/include"

###############################################################################
#       使用自定义设置配置项目                                #
###############################################################################

# 移除目标可执行文件名中的空格，以提高 Windows 兼容性
TARGET      =   $$replace(TARGET, " ", _)

# 将 DESTDIR 设为项目根目录；可执行文件/应用会部署并在此运行
DESTDIR     =   $$PWD

# 学生编写普通的 main() 函数，但它必须在一个
# 负责库初始化/清理的包装 main()。重命名学生的
# 用于区分两个 main() 函数并避免符号冲突
# 若想知道为什么是 main->qMain->studentMain，请询问 Julie
DEFINES     +=  main=qMain qMain=studentMain

###############################################################################
#       收集要显示在 Qt Creator 项目浏览器中的文件           #
###############################################################################

# 设置诱饵项，使 Qt Creator 允许全局通配文件与用户添加的文件共存
# Qt 查找第一行“SOURCES *=”，并在此列出用户添加的 .cpp/.h 文件。
# 随后我们自行使用通配方式将文件添加到 SOURCES。运算符 *= 会去重
# 条目，因此无需担心重复项
SOURCES         *=  ""
HEADERS         *=  ""

# 收集项目文件夹内的所有 .cpp 或 .h 文件（学生代码/起始代码）。
# 第二个参数 true 表示递归搜索
SOURCES         *=  $$files(*.cpp, true)
HEADERS         *=  $$files(*.h, true)

# 从 res 目录收集资源文件（图像/声音等），并列在“其他文件”下
OTHER_FILES     *=  $$files(res/*, true)
# 从根目录或任意子目录递归收集文本文件
OTHER_FILES     *=  $$files(*.txt, true)

###############################################################################
#       配置编译器和编译选项                                     #
###############################################################################

# 配置 C++ 编译器选项
# （通常会启用许多警告/错误，以加强编译期检查。
# 为避免混淆，关闭了少数过于苛刻或容易误解的错误。）

CONFIG          +=  sdk_no_version_check   # 消除 Mac OS X 上的无意义警告

# MinGW 编译器支持较滞后，为稳妥起见，在所有平台上都使用 C++11
# 而不是进行特殊处理
CONFIG          +=  c++11

# WARN_ON 包含 -Wall -Wextra，并增删少量特定警告
QMAKE_CXXFLAGS_WARN_ON      +=  -Werror=return-type
QMAKE_CXXFLAGS_WARN_ON      +=  -Werror=uninitialized
QMAKE_CXXFLAGS_WARN_ON      +=  -Wunused-parameter
QMAKE_CXXFLAGS_WARN_ON      +=  -Wmissing-field-initializers
QMAKE_CXXFLAGS_WARN_ON      +=  -Wno-old-style-cast
QMAKE_CXXFLAGS_WARN_ON      +=  -Wno-sign-compare
QMAKE_CXXFLAGS_WARN_ON      +=  -Wno-sign-conversion
QMAKE_CXXFLAGS_WARN_ON      +=  -Wno-unused-const-variable

*-clang { # clang 专用警告选项
    QMAKE_CXXFLAGS_WARN_ON  +=  -Wempty-init-stmt
    QMAKE_CXXFLAGS_WARN_ON  +=  -Wignored-qualifiers
}

*-g++ {   # g++ 专用警告选项
    QMAKE_CXXFLAGS_WARN_ON  +=  -Wlogical-op
}

###############################################################################
#       检测/报告项目结构中的错误                             #
###############################################################################

# 若直接从 ZIP 压缩包内部打开项目，则报错（Windows 上的常见错误）
win32|win64 {
    contains(PWD, .*\.zip.*) | contains(PWD, .*\.ZIP.*) {
        message( "*******************************************************************" )
        message( "*** ERROR: You are trying to open this project from within a ZIP archive." )
        message( "*** You must first extract the files then open in Qt Creator." )
        message( "*** In File Explorer open the ZIP and choose to Extract All." )
        message( "*******************************************************************" )
        error( Exiting. Extract project from ZIP first.)
    }
}

# 若目录名包含可能给 qmake/make/shell 带来问题的字符，则报错
PROJECT_DIR = $$basename(PWD)
FOUND  = $$PROJECT_DIR
FOUND ~= s|[a-z A-Z 0-9 _.+-]||   # 可以使用空格和有限的标点；$、%、& 可能有风险
!isEmpty(FOUND) {
    message( "*******************************************************************" )
    message( "*** ERROR: The name of your project directory has disallowed characters." )
    message( "*** The allowed characters are letters, numbers, and simple punctuation." )
    message( "*** Your directory is named $$PROJECT_DIR which contains the" )
    message( "*** disallowed characters: $$FOUND" )
    message( "*** Please rename to a simple name such as Assignment_1 that contains" )
    message( "*** no disallowed characters." )
    message( "*******************************************************************" )
    error(Exiting. Rename project directory to remove disallowed characters. )
}
