#include <QApplication>
#include "../../src/Plot.h"
#include "../../src/Data.h"

class TestData: public Data
{
public:
    int size() const
    {
        return 3;
    }
    QString header(int i) const
    {
        return QString("Header №%1").arg(i);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Data* data = new TestData();
    Plot plot(data);
        plot.show();
    return a.exec();
}
