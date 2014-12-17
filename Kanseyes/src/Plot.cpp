#include "Plot.h"
#include <QApplication>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include "View.h"
class Plot::PrivateData
{
public:
    View* view;

    PrivateData(Data* data, QwtPlot* plot):
        plot(plot)
    {
        view = new View(data, plot);
    }    

    ~PrivateData()
    {
        delete view;
    }

    void setLookAndFeel()
    {
        setLookAndFeelFrame();
        createCanvas();
        createGrid();
        createLegend();
    }

private:
    QwtPlot* plot;

    void setLookAndFeelFrame()
    {
        plot->setAutoFillBackground(true);
        QFont small;
        small.setPointSize(8);
        plot->setAxisFont(QwtPlot::xBottom, small);
        plot->setAxisFont(QwtPlot::yLeft, small);
        plot->setMinimumSize(QSize(200, 200));
    }

    void createCanvas()
    {
        QwtPlotCanvas* canvas = new QwtPlotCanvas();
        canvas->setLineWidth(1);
        canvas->setFrameStyle(QFrame::Box | QFrame::Plain);
        canvas->setBorderRadius(10);
        canvas->setPalette(QPalette(Qt::white));
        plot->setCanvas(canvas);

    }

    void createGrid()
    {
        QwtPlotGrid* grid = new QwtPlotGrid();
        grid->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
        grid->setMinorPen(QPen(Qt::gray, 0, Qt::DotLine));
        grid->attach(plot);
    }

    void createLegend()
    {
        plot->insertLegend(new QwtLegend(), TopLegend);
    }
};

Plot::Plot(Data* data, QWidget *parent) :
    QwtPlot(parent)
{
    d = new PrivateData(data, this);
    d->setLookAndFeel();
    setAutoReplot(false);
    setAxisAutoScale(yLeft);
    connect(d->view, SIGNAL(curveCreated(PlotCurve*)), SIGNAL(curveCreated(PlotCurve*)));
}

Plot::~Plot()
{
    delete d;
}

void Plot::updateCurves()
{
    d->view->updateCurves();
}

void Plot::replot()
{
    QwtPlot::replot();
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
}

void Plot::setMaxSize(int maxSize)
{
    d->view->setMaxSize(maxSize);
}

void Plot::clear()
{
    d->view->clear();
}

void Plot::remove()
{
    d->view->remove();
}

void Plot::save(QSettings& s) const
{
    s.beginGroup("Plot");
        d->view->save(s);
    s.endGroup();
}

void Plot::read(QSettings& s)
{
    s.beginGroup("Plot");
        d->view->read(s);
    s.endGroup();
}

#include <QMouseEvent>
void Plot::mousePressEvent(QMouseEvent* evt)
{
    if(evt->button() == Qt::RightButton){
        d->view->show();
    }
    else{
        QwtPlot::mousePressEvent(evt);
    }
}

