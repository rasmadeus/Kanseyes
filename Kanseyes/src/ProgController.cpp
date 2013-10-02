#include "ProgController.h"

ProgController::ProgController(QObject *parent) :
    DataUDP(parent)
{

}

int ProgController::size() const
{
    return 33;
}

#include "HeadersModel.h"
QString ProgController::header(int i) const
{
    if(!i){
        return tr("time");
    }
    return HeadersModel::getInstance()->getHeader(i - 1);
}

#include <QDataStream>
static void fill(float* dst, char* src, int dstSize)
{
    const int n  = sizeof(float);
    for(int i = 0; i < dstSize; ++i){
        memcpy(dst + i, src + i * n, n);
    }
}

void ProgController::parse(QByteArray* samples)
{
    int ms = QTime::currentTime().msecsTo(beginTime);
    float relativeTime = - ms * 0.001;
    setSample(0, relativeTime);

    float buf[size()];
    fill(buf, samples->data(), size());
    for(int i = 1; i < size(); ++i){
        setSample(i, buf[i-1]);
    }
}
