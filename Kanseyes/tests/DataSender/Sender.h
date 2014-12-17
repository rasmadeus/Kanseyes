#ifndef SENDER_H
#define SENDER_H

#include <QDialog>
#include <QBasicTimer>
#include <QUdpSocket>
namespace Ui {
class Sender;
}

class Sender : public QDialog
{
    Q_OBJECT
    
public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();
protected:
    void timerEvent(QTimerEvent* evt);
private slots:
    void bind();
    void setAmplitude(int A);
    void setFrequency(int f);
private:
    double time;
    void save();
    void load();
    void send();
    Ui::Sender *ui;
    QBasicTimer* timer;
    QHostAddress host;
    quint16 port;
    QUdpSocket* sender;
    int A;
    int f;
};

#endif // SENDER_H
