#ifndef TASK_H
#define TASK_H

#include <QtCore>
#include <QDateTime>

class Task
{
public:
    Task();
    Task(const QString& name);

    void setName(const QString& name);
    void setTheme(const QString& theme);
    void setStart(QDateTime time);
    void setEnd(QDateTime time);

    QString getName();
    QString getTheme();
    QDateTime getStart();
    QDateTime getEnd();

private:
    QString m_name;
    QString m_theme;
    QDateTime m_startTime;
    QDateTime m_endTime;
};

class TaskList{
public:
    TaskList(){}

    QList<Task>& getData();

    bool importTask();
    bool exportTask();

private:
    QList<Task> m_taskList;
};

#endif // TASK_H
