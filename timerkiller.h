#ifndef TIMERKILLER_H
#define TIMERKILLER_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QPoint>

#include "roundprogress.h"

#include "theme.h"
#include "task.h"

namespace Ui {
class TimerKiller;
}

class TimerKiller : public QWidget
{
    Q_OBJECT

public:
    explicit TimerKiller(QWidget *parent = nullptr);
    ~TimerKiller();

private:
    Ui::TimerKiller *ui;
    QSystemTrayIcon* m_systemTray;

    RoundProgress* m_rp;
    QTimer* sectimer;

    QDateTime startTime;
    QDateTime endTime;

    QMenu* trayIconMenu;
    QAction* showAction;
    QAction* setAction;
    QAction* aboutAction;
    QAction* closeAction;

    ThemeList m_themes;
    TaskList m_tasks;

    int m_currentIndex;
    QTimer* m_loopTimer;

public Q_SLOTS:
    void timerProgress();

    void slt_show();
    void slt_setting();
    void slt_about();
    void slt_close();

    void slt_drag(int x,int y);
    void slt_rightClicked(QPoint pos);

    void slt_taskChange();

protected:
};

#endif // TIMERKILLER_H
