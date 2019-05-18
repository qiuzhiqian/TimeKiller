#include "boxdelegate.h"
#include <QComboBox>

BoxDelegate::BoxDelegate(QObject *parent): QItemDelegate(parent)
{

}

QWidget *BoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    editor->addItems(m_enum);
    editor->setCurrentText(value);
    return editor;
}
void BoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *boxEdit = static_cast<QComboBox*>(editor);

    boxEdit->setCurrentText(value);
}
void BoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    QComboBox *boxEdit = static_cast<QComboBox*>(editor);
    QString value = boxEdit->currentText();
    model->setData(index,value,Qt::EditRole);
}
void BoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void BoxDelegate::setItemEnum(const QStringList& strList){
    m_enum = strList;
}
