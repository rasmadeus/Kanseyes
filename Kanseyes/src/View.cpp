#include "View.h"
#include "ui_View.h"

#include <qwt_plot.h>
#include "Model.h"
#include "Data.h"
#include "HeaderDelegate.h"
#include "IntDelegate.h"
View::View(Data* data, QwtPlot* owner) :
    QDialog(owner),
    ui(new Ui::View),
    data(data),
    owner(owner)
{
    ui->setupUi(this);
    model = new Model(data, owner);
    ui->view->setModel(model);
    connect(ui->view, SIGNAL(clicked(QModelIndex)), ui->view, SLOT(edit(QModelIndex)));
    connect(ui->view, SIGNAL(clicked(QModelIndex)), SLOT(clickToView(QModelIndex)));
    connect(model, SIGNAL(curveCreated(PlotCurve*)), SIGNAL(curveCreated(PlotCurve*)));

    ui->view->setItemDelegateForColumn(3, new IntDelegate(ui->view));
}

#include <QColorDialog>
void View::clickToView(const QModelIndex& index)
{
    if(index.column() == 3 ){
        return;
    }

    ui->view->closePersistentEditor(index);

    if(index.column() == 0 || index.column() == 1){
        model->setData(index, QVariant(), Qt::EditRole);
    }
    if(index.column() == 2){
        const QColor currentColor = model->data(index, Qt::BackgroundRole).value<QColor>();
        const QColor color = QColorDialog::getColor(currentColor, this);
        if(color.isValid()){
            model->setData(index, color, Qt::EditRole);
        }
    }
}

View::~View()
{    
    delete ui;
    delete model;
}

void View::setMaxSize(int maxSize)
{
    model->setMaxSize(maxSize);
}

void View::clear()
{
    model->clear();
}

void View::remove()
{
    model->remove();
}

void View::updateCurves()
{
    model->update();
}

void View::save(QSettings& s) const
{
    s.beginGroup("View");
        model->save(s);
        s.setValue("geometry", saveGeometry());
    s.endGroup();
}

void View::read(QSettings& s)
{
    s.beginGroup("View");
        model->read(s);
        restoreGeometry(s.value("geometry").toByteArray());
    s.endGroup();
}
