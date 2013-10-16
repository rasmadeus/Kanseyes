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

void ProgController::parse(char* samples, int size)
{
    int ms = QTime::currentTime().msecsTo(beginTime);
    float relativeTime = - ms * 0.001;
    setSample(0, relativeTime);


    const int n = size < this->size() ? size : this->size();
    for(int i = 1; i <= n; ++i){
        float buf;
        memcpy(&buf, samples + (i - 1) * 4, 4);
        setSample(i, buf);
    }

}
