#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractTableModel>

#include "task.h"

class TaskModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TaskModel(QObject* parent = nullptr);
    TaskModel(TaskList* list,QObject* parent = nullptr);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    TaskList* m_taskList;
    QStringList m_hHeader;
};

#endif // TASKMODEL_H
