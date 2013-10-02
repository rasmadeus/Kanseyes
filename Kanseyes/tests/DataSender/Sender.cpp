#include "Sender.h"
#include "ui_Sender.h"

Sender::Sender(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sender)
{
    time = 0;
    ui->setupUi(this);
    timer = new QBasicTimer();
    sender = new QUdpSocket();
//  ui->host->setInputMask("000.000.000.000;#");
//  ui->port->setInputMask("0000;#");
    connect(ui->bind, SIGNAL(clicked()), SLOT(bind()));
    connect(ui->amplitude, SIGNAL(valueChanged(int)), SLOT(setAmplitude(int)));
    connect(ui->frequency, SIGNAL(valueChanged(int)), SLOT(setFrequency(int)));
    load();
}

Sender::~Sender()
{
    save();
    delete ui;
    timer->stop();
    delete timer;
    delete sender;
}

#include <QHostInfo>
void Sender::bind()
{
    timer->stop();
        this->port = ui->port->text().toUInt();
    timer->start(10, this);
}

void Sender::setAmplitude(int A)
{
    this->A = A;
}

void Sender::setFrequency(int f)
{
    this->f = f;
}

#include <QSettings>
void Sender::save()
{
    QSettings settings("Settings.ini", QSettings::IniFormat);
    settings.beginGroup("Sender");
        settings.setValue("geometry", saveGeometry());
        settings.setValue("port", ui->port->text());
        settings.setValue("A", ui->amplitude->value());
        settings.setValue("f", ui->frequency->value());
    settings.endGroup();
}

void Sender::load()
{
    QSettings settings("Settings.ini", QSettings::IniFormat);
    settings.beginGroup("Sender");
        restoreGeometry(settings.value("geometry").toByteArray());
        ui->port->setText(settings.value("port", "5000").toString());
        ui->amplitude->setValue(settings.value("A", 10).toInt());
        ui->frequency->setValue(settings.value("f", 10).toInt());
    settings.endGroup();
}

static void fill(char* dst, float* src, int srcSize)
{
    const int n = sizeof(float);
    for(int i = 0; i < srcSize; ++i){
        memcpy(dst + i * n, src + i, n);
    }
}

#include <qmath.h>
void Sender::send()
{
    char data[56];
    float mas[7];
    mas[0] = time;
    mas[1] = A * qSin(time * f);
    mas[2] = 1;
    mas[3] = -1;
    mas[4] = 5;
    mas[5] = -5;
    mas[6] = 12.7;
    fill(data, mas, 7);
    sender->writeDatagram(data, sizeof(data), QHostAddress::Broadcast, 5000);
}

void Sender::timerEvent(QTimerEvent* evt)
{
    if(evt->timerId() == timer->timerId()){
        time += 0.1;
        if(time > 10000){
            time = 0;
        }
        send();
    }
    else{
        QDialog::timerEvent(evt);
    }
}
