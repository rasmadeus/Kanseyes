#include "Model.h"
#include "Data.h"
#include "Curves.h"
class Model::PrivateData
{
public:
    Data* data;
    Curves* curves;

    PrivateData(Data* data, QwtPlot* owner):
        data(data),
        owner(owner)
    {
        curves = new Curves(data, owner);
        boldFont.setBold(true);
    }

    ~PrivateData()
    {
        delete curves;
    }

    void setCurveColor(int i, const QColor& color)
    {
        if(curves->isY(i)){
            curves->setPenColor(i, color);
        }
    }

    void setCurvePenWidth(int i, int width)
    {
        if(curves->isY(i)){
            curves->setPenWidth(i, width);
        }
    }

    QVariant fontRole(const QModelIndex& index) const
    {
        const bool case0 = index.column() == 0 && curves->isX(index.row());
        const bool case1 = index.column() == 1 && curves->isY(index.row());
        return (case0 || case1) ? boldFont : QFont();
    }

    QVariant textColorRole(const QModelIndex& index) const
    {
        const bool case0 = index.column() == 0 && curves->isX(index.row());
        const bool case1 = index.column() == 1 && curves->isY(index.row());
        return QColor((case0 || case1) ? 255 : 0, 0, 0);
    }

    QVariant displayRole(const QModelIndex& index) const
    {
        switch(index.column()){
            case 0  : return is(curves->isX(index.row()));
            case 1  : return is(curves->isY(index.row()));
            case 3  : return curves->isY(index.row()) ? curves->getPenWidth(index.row()) : 2;
            default : return QVariant();
        }
    }

    QString header(int i) const
    {
        if(i && curves->isY(i)){
            return curves->getTitle(i);
        }
        return data->header(i);
    }

    QVariant backgroundRole(const QModelIndex& index) const
    {
        if(index.column() == 2){
            const int i    = index.row();
            const bool isY = curves->isY(i);
            return isY ? curves->getPenColor(i) : Qt::gray;
        }
        return QVariant();
    }

private:
    static QFont boldFont;
    QwtPlot* owner;

    QString is(bool is) const
    {
        return is ? tr("Yes") : tr("No");
    }
};

QFont Model::PrivateData::boldFont = QFont();

Model::Model(Data* data, QwtPlot* owner) :
    QAbstractTableModel(owner)
{
    d = new PrivateData(data, owner);
    connect(d->curves, SIGNAL(curveCreated(PlotCurve*)), SIGNAL(curveCreated(PlotCurve*)));
}

Model::~Model()
{
    delete d;
}

int Model::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d->data->size();
}

int Model::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation == Qt::Horizontal){
        switch(section){
            case 0 : return tr("Absciss");
            case 1 : return tr("Ordinate");
            case 2 : return tr("Color");
            case 3 : return tr("Width");
        }
        return QVariant();
    }
    return d->data->header(section);
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    switch(role){
        case Qt::FontRole       : return d->fontRole(index);
        case Qt::TextColorRole  : return d->textColorRole(index);
        case Qt::DisplayRole    : return d->displayRole(index);
        case Qt::BackgroundRole : return d->backgroundRole(index);
        default                 : return QVariant();
    }
}

bool Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(role != Qt::EditRole){
        return false;
    }
    switch(index.column()){
        case 0 : d->curves->setAbscissIndex(index.row());              return true;
        case 1 : d->curves->setOrdinateIndex(index.row());             return true;
        case 2 : d->setCurveColor(index.row(), value.value<QColor>()); return true;
        case 3 : d->setCurvePenWidth(index.row(), value.toInt());      return true;
    }
    return false;
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void Model::update()
{
    d->curves->update();
}

void Model::setMaxSize(int maxSize)
{
    d->curves->setMaxSize(maxSize);
}

void Model::clear()
{
    d->curves->clear();
}

void Model::remove()
{
    beginResetModel();
        d->curves->remove();
    endResetModel();
}

void Model::save(QSettings& s) const
{
    d->curves->save(s);
}

void Model::read(QSettings& s)
{
    beginResetModel();
        d->curves->read(s);
    endResetModel();
}
