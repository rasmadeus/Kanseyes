#include "Curves.h"

#include <QHash>
#include "PlotCurve.h"
#include "Data.h"

class Curves::PrivateData
{
public:
    QwtPlot* owner;
    Data* data;
    int iX;
    QHash<int, PlotCurve*> curves;

    PrivateData(Data* data, QwtPlot* owner):
        owner(owner),
        data(data),
        iX(0)
    {
    }

    ~PrivateData()
    {
        qDeleteAll(curves);
    }

    void setAbscissHeader(int i)
    {
        QwtText text(data->header(i));
        text.setFont(QFont("Times", 8));
        owner->setAxisTitle(QwtPlot::xBottom, text);
    }

    void update()
    {
        if(curves.isEmpty()){
            return;
        }
        foreach(int iY, curves.keys()){
            curves.value(iY)->append(data->sample(iX, iY));
        }
        owner->setAxisScale(
            QwtPlot::xBottom,
            curves.values().first()->minXValue(), curves.values().last()->maxXValue()
        );
        owner->replot();
    }
};

#include "HeadersModel.h"
Curves::Curves(Data* data, QwtPlot* owner, QObject* parent):
    QObject(parent)
{
    d = new PrivateData(data, owner);
    connect(HeadersModel::getInstance(), SIGNAL(headerChanged(int,QString)), SLOT(setTitle(int,QString)));
}

Curves::~Curves()
{
    delete d;
}

void Curves::setAbscissIndex(int i)
{
    if(i != d->iX){
        foreach(PlotCurve* curve, d->curves){
            curve->clear();
            d->setAbscissHeader(i);
        }
        d->iX = i;
    }
}

void Curves::setOrdinateIndex(int i)
{
    if(d->curves.contains(i)){
        delete d->curves.take(i);
        d->owner->replot();
    }
    else{
        PlotCurve* curve = new PlotCurve(
            d->data->header(i),
            d->owner
        );
        d->curves[i] = curve;
        emit curveCreated(curve);
    }
}

void Curves::setPenColor(int i, const QColor& color)
{
    d->curves.value(i)->setPenColor(color);
}

QColor Curves::getPenColor(int i) const
{
    return d->curves.value(i)->pen().color();
}

void Curves::setPenWidth(int i, int width)
{
    d->curves.value(i)->setPenWidth(width);
}

int Curves::getPenWidth(int i) const
{
    return d->curves.value(i)->pen().width();
}

void Curves::setTitle(int i, const QString& title)
{
    if(d->curves.contains(i+1)){
        d->curves.value(i+1)->setTitle(title);
    }
    if(isX(i+1)){
        d->setAbscissHeader(i+1);
    }
}

QString Curves::getTitle(int i) const
{
    return d->curves.value(i)->title().text();
}

bool Curves::isX(int i) const
{
    return i == d->iX;
}

bool Curves::isY(int i) const
{
    return d->curves.contains(i);
}

void Curves::setMaxSize(int maxSize)
{
    foreach(PlotCurve* curve, d->curves){
        curve->setMaxSize(maxSize);
    }
}

void Curves::clear()
{
    foreach(PlotCurve* curve, d->curves){
        curve->clear();
    }
}

void Curves::remove()
{
    foreach (int key, d->curves.keys()) {
        delete d->curves.take(key);
    }
}

void Curves::save(QSettings& s) const
{
    s.beginGroup("Curves");
        s.setValue("iX", d->iX);
        foreach(int key, d->curves.keys()){
            s.beginGroup(QString("%1").arg(key));
                s.setValue("pen", d->curves.value(key)->pen());
                s.setValue("title", d->curves.value(key)->title().text());
            s.endGroup();
        }
    s.endGroup();
}

#include <QPen>
void Curves::read(QSettings& s)
{
    s.beginGroup("Curves");
        int iX = s.value("iX", 0).toInt();
        setAbscissIndex(iX);
        d->setAbscissHeader(iX);
        foreach(QString key, s.childGroups()){
            s.beginGroup(QString("%1").arg(key));
                const int i = key.toInt();
                setOrdinateIndex(i);
                QPen pen = s.value("pen").value<QPen>();
                d->curves.value(i)->setPen(pen);
                d->curves.value(i)->setTitle(s.value("title").toString());
            s.endGroup();
        }
    s.endGroup();
}

void Curves::update()
{
    d->update();
}
