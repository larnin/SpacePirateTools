#include "UI/mainwindow.h"
#include "ProjectInfos/configs.h"
#include "ProjectInfos/projectinfos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto returnValue(a.exec());

    if(returnValue == 0)
    {
        ProjectInfos::instance().save();
        Configs::instance().save();
    }

    return returnValue;
}
