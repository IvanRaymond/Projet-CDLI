QT += widgets
requires(qtConfig(treeview))
qtHaveModule(printsupport): QT += printsupport
#unix:qtHaveModule(dbus): QT += dbus widgets

HEADERS += printview.h spreadsheet.h spreadsheetdelegate.h spreadsheetitem.h \
    datapreprocessor.h \
    imputerstrategy.h \
    operation.h \
    parser.h
SOURCES += main.cpp \
           datapreprocessor.cpp \
           imputerstrategy.cpp \
           operation.cpp \
           parser.cpp \
           printview.cpp \
           spreadsheet.cpp \
           spreadsheetdelegate.cpp \
           spreadsheetitem.cpp
RESOURCES += spreadsheet.qrc

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/spreadsheet
INSTALLS += target

