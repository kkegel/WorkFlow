#include <QApplication>
#include "../../header/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationDomain("kegel.developement.de");
    a.setApplicationName("WorkFlow_pmplusvx");

    MainWindow w;
    w.show();

    return a.exec();
}
