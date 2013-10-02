#include "Plots.h"

#include "Data.h"
Plots::Plots(Data* data, QWidget *parent) :
    QMdiArea(parent),
    data(data)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

int Plots::size() const
{
    return subWindowList().size();
}

#include "Plot.h"
#include <QMdiSubWindow>
void Plots::save(QSettings& s) const
{
    s.beginGroup("Plots");
    for(int i = 0; i < subWindowList().size(); ++i){
        s.beginGroup(QString("%1").arg(i));
            QWidget* subWindow = subWindowList()[i]->widget();
            static_cast<Plot*>(subWindow)->save(s);
        s.endGroup();
    }
    s.endGroup();
}

void Plots::read(QSettings& s)
{
    s.beginGroup("Plots");
    foreach(QString i, s.childGroups()){
        s.beginGroup(i);
            insert(s, true);
        s.endGroup();
    }
    s.endGroup();
}

void Plots::remove()
{
    foreach(QMdiSubWindow* subWindow, subWindowList()){
        static_cast<Plot*>(subWindow->widget())->remove();
        subWindow->close();
    }
}

void Plots::insert()
{
    QSettings s;
    insert(s);
}

void Plots::insert(QSettings& s, bool read)
{
    if(subWindowList().size() > 8){
        return;
    }
    QMdiSubWindow* subWindow = new QMdiSubWindow;
    Plot* plot = new Plot(data, subWindow);
    if(read){
        plot->read(s);
    }
    plot->connect(plot, SIGNAL(destroyed()), this, SLOT(tileSubWindows()));
    connect(plot, SIGNAL(curveCreated(PlotCurve*)), SIGNAL(curveCreated(PlotCurve*)));
    subWindow->setWidget(plot);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    addSubWindow(subWindow);
    subWindow->setWindowTitle(tr("Eye"));
    subWindow->setWindowIcon(QIcon(":/res/icon.ico"));
    subWindow->show();
    tileSubWindows();
}

void Plots::replot()
{
    foreach(QMdiSubWindow* subWindow, subWindowList()){
        static_cast<Plot*>(subWindow->widget())->replot();
    }
}

void Plots::updateCurves()
{
    foreach(QMdiSubWindow* subWindow, subWindowList()){
        static_cast<Plot*>(subWindow->widget())->updateCurves();
    }
}

void Plots::setMaxSize(int maxSize)
{
    foreach(QMdiSubWindow* subWindow, subWindowList()){
        static_cast<Plot*>(subWindow->widget())->setMaxSize(maxSize);
    }
}

void Plots::clear()
{
    foreach(QMdiSubWindow* subWindow, subWindowList()){
        static_cast<Plot*>(subWindow->widget())->clear();
    }
}
