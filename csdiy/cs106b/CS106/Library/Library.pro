###############################################################################
# CS106B/X 库的项目文件
#
# @author Julie Zelenski
# @version 2021 秋季学期第 1 版，适用于 Qt 6
#    构建静态库并安装到用户数据目录
###############################################################################

TEMPLATE    =   lib
TARGET      =   cs106
CONFIG      +=  staticlib

SPL_VERSION         =   2021.1
REQUIRES_QT_VERSION =   6.1

###############################################################################
#       收集文件                                                          #
###############################################################################

LIB_SUBDIRS         =   collections console graphics io system util

for(dir, LIB_SUBDIRS) {
    PUBLIC_HEADERS  +=  $$files($${dir}/*.h)
    SOURCES         +=  $$files($${dir}/*.cpp)
}

PRIVATE_HEADERS     +=  $$files(private/*.h)
SOURCES             +=  $$files(private/*.cpp)
HEADERS             +=  $$PUBLIC_HEADERS $$PRIVATE_HEADERS

RESOURCES           =   images.qrc
OTHER_FILES         =   personaltypes.py
QMAKE_SUBSTITUTES   =   private/build.h.in

INCLUDEPATH         +=  $$LIB_SUBDIRS
QT                  +=  core gui widgets network

###############################################################################
#       构建设置                                                        #
###############################################################################

# MinGW 编译器支持较滞后，为稳妥起见，在所有平台上都使用 C++11
# 而不是进行特殊处理
CONFIG              +=  c++11

# 设置 develop_mode 以启用警告、弃用提示、细节检查等全部内容。
# 请注意并修复！库应无警告地编译。
# 为学生发布安静构建时禁用此模式。

develop_mode {
    CONFIG          +=  debug
    CONFIG          -=  silent
    CONFIG          +=  warn_on
    QMAKE_CXXFLAGS  +=  -Wall -Wextra
    QMAKE_CXXFLAGS  +=  -Wno-inconsistent-missing-override
    DEFINES         +=  QT_DEPRECATED_WARNINGS
} else {
    CONFIG          +=  warn_off
    CONFIG          +=  sdk_no_version_check
    CONFIG          +=  silent
    CONFIG          +=  release
}

###############################################################################
#       Make install                                                          #
###############################################################################

# 使用 makefile include 将默认目标设置为 install 目标
QMAKE_EXTRA_INCLUDES += $$relative_path($$absolute_path(assume_install.mk), $$OUT_PWD)

win32|win64 { QTP_EXE = qtpaths.exe } else { QTP_EXE = qtpaths }
USER_DATA_DIR = $$system($$[QT_INSTALL_BINS]/$$QTP_EXE --writable-path GenericDataLocation)
SPL_DIR = $${USER_DATA_DIR}/cs106

target.path         =   "$${SPL_DIR}/lib"
headers.files       =   $$PUBLIC_HEADERS
headers.path        =   "$${SPL_DIR}/include"
INSTALLS            +=  target headers debughelper versionfile

debughelper.files   =   personaltypes.py
mac         { debughelper.path = "$$(HOME)/Qt/Qt Creator.app/Contents/Resources/debugger" }
win32|win64 { debughelper.path = "C:\Qt\Tools\QtCreator\share\qtcreator\debugger" }
unix:!mac   { debughelper.path = "$$(HOME)/Qt/Tools/QtCreator/share/qtcreator/debugger" }
!build_pass:!exists($$debughelper.path) {
    warning("Debug helper: no such path $$debughelper.path")
    debughelper.path = "$${SPL_DIR}"
}

versionfile.files   =   "version$${SPL_VERSION}"
versionfile.path    =   "$${SPL_DIR}/lib"


###############################################################################
#       要求                                                          #
###############################################################################

!versionAtLeast(QT_VERSION, $$REQUIRES_QT_VERSION) {
    error(The CS106 library $$SPL_VERSION requires Qt version $$REQUIRES_QT_VERSION and\
         your computer has older Qt version $$[QT_VERSION]. You must uninstall Qt and install version $$REQUIRES_QT_VERSION or newer.)
}
