#include "HeadersModel.h"

HeadersModel* HeadersModel::instance = 0;

HeadersModel* HeadersModel::getInstance(QObject* parent)
{
    if(!instance){
        instance = new HeadersModel(parent);
    }
    return instance;
}

#include <QStringList>
class HeadersModel::PrivateData
{
public:
    QStringList headers;

    PrivateData()
    {
        for(int i = 0; i < 32; ++i){
            headers << QObject::tr("Float %1").arg(i);
        }
    }
};

HeadersModel::HeadersModel(QObject* parent) :
    QAbstractListModel(parent)
{

    d = new PrivateData();
}

HeadersModel::~HeadersModel()
{
    delete d;
}

int HeadersModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 32;
}

QVariant HeadersModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole){
        return d->headers[index.row()];
    }
    return QVariant();
}

bool HeadersModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(role != Qt::EditRole){
        return false;
    }
    d->headers[index.row()] = value.toString();
    emit headerChanged(index.row(), value.toString());
    return true;
}

Qt::ItemFlags HeadersModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
#include <QDebug>
void HeadersModel::save(QSettings& s) const
{
    s.beginGroup("HeadersModel");
        for(int i = 0; i<d->headers.size(); ++i){
            s.setValue(QString("%1").arg(i), d->headers[i]);
        }
    s.endGroup();
}

#include <QStringList>
void HeadersModel::read(QSettings& s)
{
    beginResetModel();
        s.beginGroup("HeadersModel");
        foreach(QString i, s.childKeys()){
            d->headers[i.toInt()] = s.value(i).toString();
        }
        s.endGroup();
    endResetModel();
}

QString HeadersModel::getHeader(int i) const
{
    return d->headers[i];
}
