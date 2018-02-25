#include "UI/mainwindow.h"
#include "ProjectInfos/configs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto returnValue(a.exec());

    if(returnValue == 0)
        Configs::instance().save();

    return returnValue;
}
