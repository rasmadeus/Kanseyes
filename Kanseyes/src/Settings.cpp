#include "Settings.h"
#include "ui_Settings.h"

#include "DataUDP.h"
#include "Plots.h"
#include "MainWindow.h"
Settings::Settings(DataUDP* data, Plots* plots, QBasicTimer* timer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings),
    data(data),
    plots(plots),
    timer(timer)
{
    mw = static_cast<MainWindow*>(parent);

    ui->setupUi(this);

    ui->port->setInputMask("00000;#");


    connect(ui->pointCount, SIGNAL(valueChanged(int)), SLOT(setLabelPointCount(int)));
    connect(ui->updateFrequency, SIGNAL(valueChanged(int)), SLOT(setLabelUpdateFrequency(int)));

    connect(ui->pointCount, SIGNAL(valueChanged(int)), plots, SLOT(setMaxSize(int)));
    connect(ui->updateFrequency, SIGNAL(valueChanged(int)), SLOT(updateTimerFrequency(int)));

    connect(ui->connect, SIGNAL(clicked()), SLOT(bind()));
    connect(ui->insert, SIGNAL(clicked()), plots, SLOT(insert()));
    connect(ui->tile, SIGNAL(clicked()), plots, SLOT(tileSubWindows()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::start()
{
    timer->start(ui->updateFrequency->value(), mw);
}

#include "PlotCurve.h"
void Settings::curveCreated(PlotCurve* curve)
{
    curve->setMaxSize(ui->pointCount->value());
}

void Settings::setLabelPointCount(int value)
{
    ui->labelPointCount->setText(tr("Points count %1").arg(value));
}

void Settings::setLabelUpdateFrequency(int value)
{
    ui->labelUpdateFrequency->setText(tr("Update frequency %1 ms").arg(value));
}

#include "MainWindow.h"
void Settings::updateTimerFrequency(int value)
{
    bool active = timer->isActive();
    timer->stop();
    if(active){
        timer->start(value, mw);
    }
}

void Settings::bind()
{
    data->setSender(QHostAddress(ui->host->text()));
    data->bind(ui->port->text().toInt());
}

void Settings::save(QSettings& s) const
{
    s.beginGroup("Settings");
        s.setValue("host", ui->host->text());
        s.setValue("port", ui->port->text());
        s.setValue("pointCount", ui->pointCount->value());
        s.setValue("updateFrequency", ui->updateFrequency->value());
    s.endGroup();
}

void Settings::read(QSettings& s)
{
    s.beginGroup("Settings");
        ui->host->setText(s.value("host", "127.0.0.1").toString());
        ui->port->setText(s.value("port", "27015").toString());
        ui->pointCount->setValue(s.value("pointCount").toInt());
        ui->updateFrequency->setValue(s.value("updateFrequency").toInt());
    s.endGroup();
}
