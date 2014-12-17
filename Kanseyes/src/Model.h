#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include "global.h"
#include <qwt_plot.h>
#include <QSettings>
class Data;
class Curves;
class PlotCurve;
class Headers;

class Model : public QAbstractTableModel
{
    Q_OBJECT
    PRIVATE_DATA
public:
    Model(Data* data, QwtPlot* owner);
    ~Model();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void update();
    void setMaxSize(int maxSize);
    void clear();
    void remove();
    void save(QSettings& s) const;
    void read(QSettings& s);
signals:
    void curveCreated(PlotCurve* curve);
};

#endif // MODEL_H
