#include "Data.h"

#include <QVector>
#include <QMutex>
class Data::PrivateData
{
public:
    QVector<float> samples;
    QMutex mutex;
    QPointF lastPoint;
};

Data::Data()
{
    d = new PrivateData();
}

Data::~Data()
{
    delete d;
}

QPointF Data::sample(int iX, int iY)
{
    if(!d->mutex.tryLock()){
        return d->lastPoint;
    }
    QPointF result(d->samples[iX], d->samples[iY]);
    d->mutex.unlock();
    d->lastPoint = result;
    return result;
}

void Data::setSample(int i, float sample)
{
    if(!d->mutex.tryLock()){
        return;
    }
    d->samples[i] = sample;
    d->mutex.unlock();
}

void Data::init()
{
    d->samples.reserve(size());
    d->samples.resize(size());
}

void Data::clear()
{
    if(!d->mutex.tryLock()){
        return;
    }
    d->samples.clear();
    init();
    d->mutex.unlock();
}
