#ifndef PLOTS_H
#define PLOTS_H

#include <QMdiArea>
#include <QSettings>
class Data;
class PlotCurve;

class Plots : public QMdiArea
{
    Q_OBJECT
public:
    explicit Plots(Data* data, QWidget *parent = 0);
    int size() const;
    void save(QSettings& s) const;
    void read(QSettings& s);
    void remove();
public slots:
    void insert();
    void replot();
    void updateCurves();
    void setMaxSize(int maxSize);
    void clear();    
signals:
    void curveCreated(PlotCurve*);
private:
    void insert(QSettings& s, bool read = false);
    Data* data;
};

#endif // PLOTS_H
