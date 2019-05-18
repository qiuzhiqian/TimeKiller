#ifndef TIMEDELEGATE_H
#define TIMEDELEGATE_H

#include <QItemDelegate>

class TimeDelegate : public QItemDelegate
{
public:
    TimeDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TIMEDELEGATE_H
