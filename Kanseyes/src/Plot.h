#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <qwt_plot.h>
#include "global.h"
class Data;
class PlotCurve;

#include <QSettings>

class Plot : public QwtPlot
{
    Q_OBJECT
    PRIVATE_DATA
public:
    explicit Plot(Data* data, QWidget *parent = 0);
    ~Plot();
    void replot();
    void setMaxSize(int maxSize);
    void clear();
    void remove();
    void save(QSettings& s) const;
    void read(QSettings& s);
public slots:
    void updateCurves();
signals:
    void curveCreated(PlotCurve*);
protected:
    void mousePressEvent(QMouseEvent* evt);
};

#endif // PLOTWIDGET_H
