#ifndef PROGCONTROLLER_H
#define PROGCONTROLLER_H

#include "DataUDP.h"
#include <QSettings>

class ProgController : public DataUDP
{
    Q_OBJECT
public:
    explicit ProgController(QObject *parent = 0);
    int size() const;
    QString header(int i) const;
protected:
    void parse(char* samples, int size);
};

#endif // PROGCONTROLLER_H
