#include <QCoreApplication>
#include <QThread>
#include "../../src/Data.h"
#include <QDebug>

class Thread: public QThread
{
public:
    Thread(Data* data):
        data(data)
    {
    }

    ~Thread()
    {
        terminate();
        while(isRunning());
    }

protected:
    Data* data;
};

class ThreadForRead: public Thread
{
public:
    ThreadForRead(Data* data):
        Thread(data)
    {
    }
protected:
    void run()
    {
        forever{
            for(int i = 0; i < data->size(); ++i){
                qDebug() << "ThreadForRead: " << data->sample(i, i);
            }
            sleep(2);
        }
    }
};

class ThreadForWrite: public Thread
{
public:
    ThreadForWrite(Data* data):
        Thread(data)
    {
    }
protected:
    void run()
    {
        forever{
            for(int i = 0; i < data->size(); ++i){
                qreal val = rand() % 255;
                qDebug() << "ThreadForWrite: " << val;
                data->setSample(i, val);
            }
            sleep(3);
        }
    }
};

class TestData: public Data
{
public:
    int size() const
    {
        return 1;
    }

    QString header(int i) const
    {
        Q_UNUSED(i)
        return "Header";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
        TestData testData;
        testData.init();
        ThreadForRead read(&testData);
        ThreadForWrite write(&testData);
        read.start();
        write.start();
    return a.exec();
}
