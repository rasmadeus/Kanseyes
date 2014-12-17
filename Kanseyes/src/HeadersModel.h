#ifndef HEADERSMODEL_H
#define HEADERSMODEL_H

class Data;
#include "global.h"

#include <QAbstractListModel>
#include <QSettings>

class HeadersModel : public QAbstractListModel
{
    Q_OBJECT
    PRIVATE_DATA
    Q_DISABLE_COPY(HeadersModel)
    explicit HeadersModel(QObject* parent = 0);
    static HeadersModel* instance;
public:
    static HeadersModel* getInstance(QObject* parent = 0);
    ~HeadersModel();
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;
    void save(QSettings& s) const;
    void read(QSettings& s);
    QString getHeader(int i) const;
signals:
    void headerChanged(int i, QString header);

};

#endif // HEADERSMODEL_H
