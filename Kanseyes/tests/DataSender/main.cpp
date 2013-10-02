#include <QApplication>
#include "Sender.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        Sender sender;
        sender.show();
    return a.exec();
}
