#ifndef DATA_H
#define DATA_H

#include "global.h"
#include <QPointF>

class Data
{
    PRIVATE_DATA
public:
    Data();
    virtual ~Data();
    QPointF sample(int iX, int iY);
    void setSample(int i, float sample);
    void init();
    void clear();

    virtual int size() const = 0;
    virtual QString header(int i) const = 0;
};

#endif // DATA_H
