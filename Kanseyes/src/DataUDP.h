#ifndef DATAUDP_H
#define DATAUDP_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include "Data.h"
#include <QTime>

class DataUDP : public QObject, public Data
{
    Q_OBJECT
public:
    explicit DataUDP(QObject *parent = 0);
    virtual ~DataUDP();
    void bind(quint16 port);
    void setSender(const QHostAddress& sender);
protected:
    virtual void parse(char* samples, int size) = 0;
    QTime beginTime;
signals:
    void samplesHasChanged();
    void abort();
    void bound();
private slots:
    void cameNewSamples();
private:
    QUdpSocket* receiver;
    QHostAddress sender;    
};

#endif // DATAUDP_H
