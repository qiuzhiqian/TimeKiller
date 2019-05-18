#include "timedelegate.h"
#include <QDateTimeEdit>

TimeDelegate::TimeDelegate()
{

}

QWidget *TimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    //QSpinBox *editor = new QSpinBox(parent);
    //editor->setMinimum(1);
    //editor->setMaximum(100);
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    QDateTime timev = QDateTime::fromString(value,Qt::ISODate);
    QDateTimeEdit *editor = new QDateTimeEdit(timev,parent);
    editor->setCalendarPopup(true);
    editor->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    //editor->addItems(m_enum);
    return editor;
}
void TimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //int value = index.model()->data(index, Qt::EditRole).toInt();
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->setValue(value);
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QDateTime timev = QDateTime::fromString(value,Qt::ISODate);
    QDateTimeEdit *timeEditor = static_cast<QDateTimeEdit*>(editor);
    if(timeEditor != nullptr){
        //boxEdit->setValidator(m_valid);
        timeEditor->setDateTime(QDateTime(timev));
    }

    //boxEdit->setCurrentText(value);
}
void TimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const
{
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->interpretText();
    //int value = spinBox->value();
    //model->setData(index, value, Qt::EditRole);
    QDateTimeEdit *timeEditor = static_cast<QDateTimeEdit*>(editor);
    QString value = timeEditor->dateTime().toString(Qt::ISODate);
    model->setData(index,value,Qt::EditRole);
}
void TimeDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
