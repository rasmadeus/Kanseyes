#ifndef CURVES_H
#define CURVES_H

#include <QObject>
#include "global.h"
#include <qwt_plot.h>
#include <QSettings>
class PlotCurve;
class Data;
class Headers;

class Curves: public QObject
{
    Q_OBJECT
    PRIVATE_DATA
public:
    Curves(Data* receiver, QwtPlot* owner, QObject* parent = 0);
    ~Curves();
    void setAbscissIndex(int i);
    void setOrdinateIndex(int i);
    void setPenColor(int i, const QColor& color);
    QColor getPenColor(int i) const;
    void setPenWidth(int i, int width);
    int getPenWidth(int i) const;
    QString getTitle(int i) const;
    bool isX(int i) const;
    bool isY(int i) const;
    void setMaxSize(int maxSize);
    void clear();
    void remove();
    void save(QSettings& s) const;
    void read(QSettings& s);
signals:
    void curveCreated(PlotCurve*);
public slots:
    void update();
    void setTitle(int i, const QString& title);
};

#endif // CURVES_H
