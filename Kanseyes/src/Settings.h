#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

class DataUDP;
class Plots;
class MainWindow;
#include <QSettings>
#include <QBasicTimer>

namespace Ui {
class Settings;
}

class PlotCurve;

class Settings : public QWidget
{
    Q_OBJECT
    
public:
    Settings(DataUDP* data, Plots* plots, QBasicTimer* timer, QWidget *parent = 0);
    ~Settings();
    void save(QSettings& s) const;
    void read(QSettings& s);
public slots:
    void start();
    void curveCreated(PlotCurve* curve);
private slots:
    void setLabelPointCount(int value);
    void setLabelUpdateFrequency(int value);
    void updateTimerFrequency(int value);
    void bind();
private:
    Ui::Settings *ui;
    DataUDP* data;
    Plots* plots;
    QBasicTimer* timer;
    MainWindow* mw;
};

#endif // SETTINGS_H
