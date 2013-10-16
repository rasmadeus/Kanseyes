#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBasicTimer>
#include <QAbstractSocket>
class Data;
class Plots;
class DataUDP;
class Settings;
class Headers;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
private slots:
    void timerEvent(QTimerEvent* evt);
    void abort();
    void bound();
private slots:
    void save();
    void read();
private:
    Ui::MainWindow *ui;
    Plots* plots;
    DataUDP* data;
    QBasicTimer* timer;
    Settings* settings;
    Headers* headers;
};

#endif // MAINWINDOW_H
