#-------------------------------------------------
#
# Project created by QtCreator 2012-11-04T11:49:17
#
#-------------------------------------------------

QT       += core gui

win32 {
    LIBS += -lshlwapi
}

TARGET = sg2ps_gui
TEMPLATE = app


SOURCES += main.cpp\
    InputWidget.cpp \
    SettingsWidget.cpp \
    MainWindow.cpp \
    OptionWidget.cpp \
    Runner.cpp \
    ProcessManager.cpp \
    GUISettings.cpp \
    GlobalSettings.cpp \
    ErrorMsg.cpp \
    ResolveExitCode.cpp \
    Option.cpp \
    Launcher.cpp

HEADERS  += \
    InputWidget.hpp \
    LayoutConstants.hpp \
    SettingsWidget.hpp \
    MainWindow.hpp \
    OptionWidget.hpp \
    Option.hpp \
    Runner.hpp \
    ProcessManager.hpp \
    ExitStatus.hpp \
    GUISettings.hpp \
    GlobalSettings.hpp \
    ErrorMsg.hpp \
    ResolveExitCode.hpp \
    Launcher.hpp

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    images/insert_table48.png \
    images/package_internet48.png \
    images/acroread48.png \
    images/document_import48.png \
    images/spreadsheet48.png \
    images/spreadsheetB48.png \
    images/document_new48.png
