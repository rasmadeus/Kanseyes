#include "Headers.h"
#include "ui_Headers.h"

#include "HeadersModel.h"
#include "HeaderDelegate.h"
Headers::Headers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Headers)
{
    ui->setupUi(this);
    ui->view->setModel(HeadersModel::getInstance(ui->view));
    ui->view->setItemDelegateForColumn(0, new HeaderDelegate(ui->view));
    connect(ui->view, SIGNAL(clicked(QModelIndex)), ui->view, SLOT(edit(QModelIndex)));
}

Headers::~Headers()
{
    delete ui;
    delete HeadersModel::getInstance();
}

void Headers::save(QSettings& s) const
{
    s.beginGroup("Headers");
        HeadersModel::getInstance()->save(s);
    s.endGroup();
}

void Headers::read(QSettings& s)
{
    s.beginGroup("Headers");
        HeadersModel::getInstance()->read(s);
    s.endGroup();
}
