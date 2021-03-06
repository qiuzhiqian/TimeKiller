#include "task.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Task::Task()
{
    m_startTime = QDateTime::currentDateTime();
    m_endTime = QDateTime::currentDateTime().addSecs(60);
}

Task::Task(const QString& name)
{
    m_name = name;
    m_startTime = QDateTime::currentDateTime();
    m_endTime = QDateTime::currentDateTime().addSecs(60);
}

void Task::setName(const QString &name){
    m_name = name;
}

void Task::setTheme(const QString &theme){
    m_theme = theme;
}

void Task::setStart(QDateTime time){
    m_startTime = time;
}

void Task::setEnd(QDateTime time){
    m_endTime = time;
}

QString Task::getName(){
    return m_name;
}

QString Task::getTheme(){
    return m_theme;
}

QDateTime Task::getStart(){
    return m_startTime;
}

QDateTime Task::getEnd(){
    return m_endTime;
}

QList<Task>& TaskList::getData(){
    return m_taskList;
}

bool TaskList::importTask(){
    QFile file("task.json");
    if(file.open(QIODevice::ReadWrite)){
        QByteArray ba = file.readAll();
        QJsonParseError err;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(ba,&err);
        if(jsonDoc.isObject()){
            QJsonObject obj = jsonDoc.object();
            QJsonValue val = obj.value("task");
            if(val.isArray()){
                QJsonArray arry = val.toArray();
                for(auto item:arry){
                    if(item.isObject()){
                        Task tk;
                        QJsonObject themeObj = item.toObject();
                        QJsonValue name = themeObj.value("name");
                        QJsonValue theme = themeObj.value("theme");
                        QJsonValue start = themeObj.value("start");
                        QJsonValue end = themeObj.value("end");

                        tk.setName(name.toString());
                        tk.setTheme(theme.toString());
                        tk.setStart(QDateTime::fromString(start.toString(),Qt::ISODate));
                        tk.setEnd(QDateTime::fromString(end.toString(),Qt::ISODate));
                        m_taskList.append(tk);
                    }
                }
            }
        }
        file.close();
        return true;
    }
    return false;
}

bool TaskList::exportTask(){
    QJsonArray array;
    for(auto& item:m_taskList){
        QJsonObject taskObj;
        taskObj.insert("name",item.getName());
        taskObj.insert("theme",item.getTheme());
        taskObj.insert("start",item.getStart().toString(Qt::ISODate));
        taskObj.insert("end",item.getEnd().toString(Qt::ISODate));
        array.append(taskObj);
    }

    QJsonObject jsonObj;
    jsonObj.insert("task",array);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Indented);

    QFile file("task.json");
    if(file.open(QIODevice::ReadWrite|QIODevice::Truncate)){
        file.write(byteArray);
        file.close();
    }
    return true;
}
