#include "taskmodel.h"

TaskModel::TaskModel(QObject *parent):QAbstractTableModel(parent)
{
    m_hHeader << "Name" <<"Theme"<<"Start"<<"End"<<"";
}

TaskModel::TaskModel(TaskList* list,QObject *parent):QAbstractTableModel(parent),m_taskList(list)
{
    m_hHeader << "Name" <<"Theme"<<"Start"<<"End"<<"";
}

int TaskModel::rowCount(const QModelIndex &parent) const
{
    return m_taskList->getData().size();
}

int TaskModel::columnCount(const QModelIndex &parent) const
{
    return 5;//
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())        //安全判断
    {
        return QVariant();
    }
    if(Qt::TextAlignmentRole == role)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else if(Qt::DisplayRole == role | Qt::EditRole == role)            //这里这样写是为了过滤掉其他role(例如过滤掉checkBox)
    {
        Task& tempTask = const_cast<Task&>(m_taskList->getData().at(index.row()));
        switch(index.column()){
        case 0:{
            return tempTask.getName();//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 1:{
            return tempTask.getTheme();//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 2:{
            return tempTask.getStart().toString(Qt::ISODate);//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 3:{
            return tempTask.getEnd().toString(Qt::ISODate);//在所有的index中显示1(当然也可以根据index的不同显示不同的值)
        }
        case 4:{
            break;
        }
        }

    }
    return QVariant();
}

QVariant TaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayRole != role)
    {
        return QVariant();
    }
    if(orientation == Qt::Horizontal)       //横向头
    {
        return m_hHeader.at(section);//横向头一次递增
    }
    else if(orientation == Qt::Vertical)    //纵向头
    {
        return section + 1;//纵向头依次递增
    }
    return QVariant();
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole && value.isValid() && m_taskList!=nullptr){
        Task& tempTask = const_cast<Task&>(m_taskList->getData().at(index.row()));
        switch(index.column()){
        case 0:{
            tempTask.setName(value.toString());
            break;
        }
        case 1:{
            tempTask.setTheme(value.toString());
            break;
        }
        case 2:{
            QString str = value.toString();
            tempTask.setStart(QDateTime::fromString(str,Qt::ISODate));
            break;
        }
        case 3:{
            QString str = value.toString();
            tempTask.setEnd(QDateTime::fromString(str,Qt::ISODate));
            break;
        }
        }
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

Qt::ItemFlags TaskModel::flags(const QModelIndex &index) const{
    Qt::ItemFlags flag = QAbstractTableModel::flags(index);
    flag |= Qt::ItemIsEditable;
    return flag;
}

bool TaskModel::insertRows(int row, int count, const QModelIndex &parent){
    beginInsertRows(parent,row,row);

    for(int i=0;i<count;i++){
        Task tempTask("Day1");
        tempTask.setTheme("default");
        tempTask.setStart(QDateTime::currentDateTime());
        tempTask.setEnd(QDateTime::currentDateTime().addSecs(60*60*12));
        m_taskList->getData().insert(row+i,tempTask);
    }
    endInsertRows();
    return true;
}
