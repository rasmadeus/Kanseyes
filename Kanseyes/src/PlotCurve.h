#ifndef PLOTCURVE_H
#define PLOTCURVE_H

#include <qwt_plot_curve.h>
#include "global.h"
#include "Command.h"


class PlotCurve : public QwtPlotCurve, public Command
{
    PRIVATE_DATA
public:
    PlotCurve(const QString& title, QwtPlot* owner);
    ~PlotCurve();
    void setPenColor(const QColor& color);
    void setPenWidth(int width);
    void append(const QPointF& point);
    void setMaxSize(int maxSize);
    void clear();
};

#endif // PLOTCURVE_H
