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
    QPointF result(d->samples[iX], d->samples[iY]);
    d->lastPoint = result;
    return result;
}

void Data::setSample(int i, float sample)
{
    d->samples[i] = sample;
}

void Data::init()
{
    d->samples.reserve(size());
    d->samples.resize(size());
}

void Data::clear()
{
    d->samples.clear();
    init();
}
