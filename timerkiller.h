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
    QAction* closeAction;

public Q_SLOTS:
    void timerProgress();

    void slt_show();
    void slt_setting();
    void slt_close();

    void slt_drag(int x,int y);
    void slt_rightClicked(QPoint pos);

protected:
};

#endif // TIMERKILLER_H
