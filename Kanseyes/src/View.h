#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
class QwtPlot;
class Data;
class Model;
class PlotCurve;

#include <QSettings>
namespace Ui {
class View;
}

class View : public QDialog
{
    Q_OBJECT
public:
     View(Data* data, QwtPlot* owner);
    ~View();
     void setMaxSize(int maxSize);
     void clear();
     void remove();
     void save(QSettings& s) const;
     void read(QSettings& s);
public slots:
     void updateCurves();
private slots:
    void clickToView(const QModelIndex& index);
signals:
    void curveCreated(PlotCurve*);
private:
    Ui::View *ui;
    Data* data;
    QwtPlot* owner;
    Model* model;
};

#endif // VIEW_H
