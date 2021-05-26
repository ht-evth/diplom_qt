QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseMetricsTree.cpp \
    BaseScanner.cpp \
    BaseSyntax.cpp \
    BlockMetricsTree.cpp \
    BlockScanner.cpp \
    BlockSyntax.cpp \
    ClassMetricsTree.cpp \
    ClassScanner.cpp \
    ClassSyntax.cpp \
    CyclesMetricsTree.cpp \
    CyclesScanner.cpp \
    CyclesSyntax.cpp \
    NameMetricsTree.cpp \
    NameScanner.cpp \
    NameSyntax.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BaseMetricsTree.h \
    BaseScanner.h \
    BaseSyntax.h \
    BlockMetricsTree.h \
    BlockScanner.h \
    BlockSyntax.h \
    ClassMetricsTree.h \
    ClassScanner.h \
    ClassSyntax.h \
    CyclesMetricsTree.h \
    CyclesScanner.h \
    CyclesSyntax.h \
    NameMetricsTree.h \
    NameScanner.h \
    NameSyntax.h \
    Node.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
