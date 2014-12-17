#include "HeaderDelegate.h"

HeaderDelegate::HeaderDelegate(QWidget* parent) :
    QItemDelegate(parent)
{
}

#include <QLineEdit>
QWidget* HeaderDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return new QLineEdit(parent);
}

void HeaderDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QLineEdit* delegate = static_cast<QLineEdit*>(editor);
    delegate->setText(index.data().toString());
    delegate->selectAll();
}
