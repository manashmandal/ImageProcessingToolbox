#include "toolboxmainwindow.h"
#include <QApplication>


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ToolboxMainWindow w;
    w.show();
    return app.exec();
}
