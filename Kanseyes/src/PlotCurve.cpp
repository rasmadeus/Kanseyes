#include "PlotCurve.h"
#include <qwt_plot.h>
class PlotCurve::PrivateData
{
public:
    QwtPlot* owner;
    PlotCurve* curve;
    int maxSize;
    QVector<QPointF> samples;


    PrivateData(QwtPlot* owner):
        owner(owner),
        maxSize(100)
    {
    }

    void append(const QPointF& point)
    {
        if(point == QPointF()){
            return;
        }
        if(samples.size() == maxSize){
            samples.remove(0);
        }
        samples.push_back(point);
    }

    void setMaxSize(int maxSize)
    {
        if(maxSize < samples.size()){
            samples.remove(0, samples.size() - maxSize);
        }
        this->maxSize = maxSize;
    }

    void clear()
    {
        samples.clear();        
    }

    void update()
    {
        curve->setSamples(samples);
    }
};

PlotCurve::PlotCurve(const QString& title, QwtPlot* owner):
    QwtPlotCurve(title)
{
    d = new PrivateData(owner);
    d->curve = this;
    setPen(QPen(QColor(rand() % 255, rand() % 255, rand() % 255), 2));
    attach(owner);
    owner->updateLayout();    
}

PlotCurve::~PlotCurve()
{
    delete d;
}

void PlotCurve::setPenColor(const QColor& color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    setPen(pen);
    d->owner->replot();
}

void PlotCurve::setPenWidth(int width)
{
    QPen pen = this->pen();
    pen.setWidth(width);
    setPen(pen);
    d->owner->replot();
}

void PlotCurve::append(const QPointF& point)
{
    d->append(point);
    d->update();
}

void PlotCurve::setMaxSize(int maxSize)
{
    d->setMaxSize(maxSize);
    d->update();
}

void PlotCurve::clear()
{
    d->samples.clear();
    d->update();
}
