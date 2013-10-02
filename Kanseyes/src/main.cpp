#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication Kanseyes(argc, argv);
    QApplication::setOrganizationName("Fakel");
    QApplication::setApplicationName("Kanseyes");
    QApplication::setApplicationVersion("1.0");
        MainWindow view;
        view.show();
    return Kanseyes.exec();
}
