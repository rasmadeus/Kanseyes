#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Plots.h"
#include "ProgController.h"
#include "Settings.h"
#include "Headers.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    headers = new Headers(this);
    ui->headers->setWidget(headers);

    data = new ProgController();
    data->init();
    connect(data, SIGNAL(abort()), SLOT(abort()));
    connect(data, SIGNAL(bound()), SLOT(bound()));

    plots = new Plots(data, this);
    setCentralWidget(plots);
    plots->show();

    timer = new QBasicTimer();

    settings = new Settings(data, plots, timer, this);
    ui->settings->setWidget(settings);
    connect(plots, SIGNAL(curveCreated(PlotCurve*)), settings, SLOT(curveCreated(PlotCurve*)));

    connect(ui->actionSave, SIGNAL(triggered()), SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(read()));
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete ui;
    delete data;
    delete settings;
}

void MainWindow::timerEvent(QTimerEvent* evt)
{
    if(evt->timerId() == timer->timerId()){
        plots->updateCurves();
    }
    QMainWindow::timerEvent(evt);
}

void MainWindow::abort()
{
    timer->stop();
    plots->clear();
}

void MainWindow::bound()
{
    plots->clear();
    settings->start();
}

#include <QSettings>
#include <QFileDialog>
void MainWindow::save()
{
    abort();

    QString path = QFileDialog::getSaveFileName(this, tr("Open settings..."), "settings", "*.ini");
    if(path.isEmpty()){
        return;
    }

    QSettings s(path, QSettings::IniFormat);
    s.clear();
    s.beginGroup("MainWindow");
        headers->save(s);
        plots->save(s);
        settings->save(s);
        s.setValue("geometry", saveGeometry());
        s.setValue("state", saveState());
    s.endGroup();
}

void MainWindow::read()
{
    abort();

    QString path = QFileDialog::getOpenFileName(this, tr("Open settings..."), "settings", "*.ini");
    if(path.isEmpty()){
        return;
    }

    plots->remove();

    QSettings s(path, QSettings::IniFormat);
    s.beginGroup("MainWindow");
        headers->read(s);
        plots->read(s);
        settings->read(s);
        restoreGeometry(s.value("geometry").toByteArray());
        restoreState(s.value("state").toByteArray());
    s.endGroup();
}
