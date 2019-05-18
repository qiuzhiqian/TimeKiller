#ifndef TASK_H
#define TASK_H

#include <QtCore>

class Task
{
public:
    Task();

private:
    QString m_name;
    QString m_theme;
    QDateTime m_startTime;
    QDateTime m_endTime;
};

class TaskList{

};

#endif // TASK_H
