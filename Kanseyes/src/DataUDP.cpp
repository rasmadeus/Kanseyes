#include "DataUDP.h"

DataUDP::DataUDP(QObject* parent) :
    QObject(parent)
{
    receiver = new QUdpSocket(this);
    connect(receiver, SIGNAL(readyRead()), SLOT(cameNewSamples()));
}

DataUDP::~DataUDP()
{
    delete receiver;
}

void DataUDP::bind(quint16 port)
{
    emit abort();
    receiver->abort();
    clear();
    if(receiver->bind(QHostAddress::Any, port)){
        beginTime = QTime::currentTime();
        emit bound();
    }
}

void DataUDP::setSender(const QHostAddress& sender)
{
    this->sender = sender;
}

void DataUDP::cameNewSamples()
{
    while(receiver->hasPendingDatagrams()){
        QByteArray samples;
        const quint64 n = receiver->pendingDatagramSize();
        samples.resize(n);
        QHostAddress host;
        quint16 port;        
        receiver->readDatagram(samples.data(), samples.size(), &host, &port);
        if(host == sender){
            parse(samples.data(), n/sizeof(float));
            emit samplesHasChanged();
        }

    }
}


