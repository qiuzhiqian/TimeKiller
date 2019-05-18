#include "timerkiller.h"
#include "ui_timerkiller.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QScreen>

#include "setting.h"

TimerKiller::TimerKiller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerKiller)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);//设置窗体无边框
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明

    QList<QScreen *> screenList = QGuiApplication::screens();
    if(screenList.size()==0){
        return;
    }
    QRect screenRect = screenList.at(0)->availableGeometry();

    setGeometry(screenRect.width()-150,250,150,150);

    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(QIcon(":/resources/time4.png"));
    m_systemTray->setToolTip("TimeKiller");

    showAction = new QAction(this);
    showAction->setText(tr("主界面"));
    //showAction->setIcon(QIcon(":/icons/min.bmp"));
    connect(showAction,SIGNAL(triggered()),this,SLOT(slt_show()));

    setAction = new QAction(this);
    setAction->setText(tr("设置"));
    //setAction->setIcon(QIcon(":/icons/restore.bmp"));
    connect(setAction,SIGNAL(triggered()),this,SLOT(slt_setting()));

    closeAction = new QAction(this);
    closeAction->setText(tr("退出"));
    //closeAction->setIcon(QIcon(":/icons/shutdown03.jpg"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(slt_close()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(setAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(closeAction);

    m_systemTray->setContextMenu(trayIconMenu);
    m_systemTray->show();

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);

    m_themes.importTheme();
    m_tasks.importTask();

    m_rp = new RoundProgress(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_rp);
    connect(m_rp,SIGNAL(sgn_drag(int,int)),this,SLOT(slt_drag(int,int)));
    m_rp->setToolTip(tr("this is tool tip"));
    connect(m_rp,SIGNAL(sgn_rightClicked(QPoint)),this,SLOT(slt_rightClicked(QPoint)));

    sectimer = new QTimer();
    sectimer->setInterval(500);
    connect(sectimer,SIGNAL(timeout()),this,SLOT(timerProgress()));

    if(m_tasks.getData().size()>0){
        Task& currentTask = const_cast<Task&>(m_tasks.getData().at(0));
        QString themeStr = currentTask.getTheme();
        int themeIndex = -1;
        for(int i=0;i<m_themes.getData().size();i++){
            if(m_themes.getData()[i].getName() == themeStr){
                themeIndex = i;
                break;
            }
        }

        if(themeIndex>=0){
            Theme& currentTheme = const_cast<Theme&>(m_themes.getData().at(themeIndex));
            m_rp->setLineWidth(currentTheme.getLineWidth());
            m_rp->setLineColor(currentTheme.getLineColor());
            m_rp->setBorderWidth(currentTheme.getBorderWidth());
            m_rp->setBorderColor(currentTheme.getBorderColor());
            m_rp->setBgColor(currentTheme.getBgColor());
            m_rp->update();

            startTime = currentTask.getStart();
            endTime = currentTask.getEnd();
            qDebug()<<"start time:"<<startTime.toString(Qt::ISODate);
            qDebug()<<"end time:"<<endTime.toString(Qt::ISODate);

            if(endTime<startTime){
                endTime = startTime;
            }
            sectimer->start();
        }
        else{
            //退出
        }
    }
    else{
        //退出
    }
}

TimerKiller::~TimerKiller()
{
    delete ui;

    if(sectimer->isActive()){
        sectimer->stop();
    }
}

void TimerKiller::timerProgress(){
    QDateTime nowTime = QDateTime::currentDateTime();
    //qDebug()<<"nowTime:"<<nowTime.toString(Qt::ISODate);
    if(endTime>startTime && nowTime>=startTime && nowTime<=endTime){
        qint64 sumVal = endTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();
        qint64 usedVal = nowTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();

        double val = (double(usedVal) / sumVal)*360.0;
        //qDebug()<<"sumVal:"<<sumVal<<" usedVal:"<<usedVal<<" val:"<<val<<" db:"<<db*360;
        m_rp->setValue(val);
    }
    else if(endTime>startTime && nowTime>endTime){
        m_rp->setValue(360);
    }
}

void TimerKiller::slt_show(){

}

void TimerKiller::slt_setting(){
    Setting* setwidget = new Setting(&m_themes,&m_tasks);
    setwidget->setWindowModality(Qt::ApplicationModal);
    setwidget->setAttribute(Qt::WA_DeleteOnClose);
    setwidget->show();
}

void TimerKiller::slt_close(){
    close();
}

void TimerKiller::slt_drag(int x,int y){
    QList<QScreen *> screenList = QGuiApplication::screens();
    if(screenList.size()==0){
        return;
    }
    QRect screenRect = screenList.at(0)->availableGeometry();

    QPoint currentPoint = this->pos();

    int newX;
    if(currentPoint.x()+x<0){
        newX = 0;
    }
    else if(currentPoint.x()+this->width()+x>screenRect.width()){
        newX = screenRect.width() - this->width();
    }
    else{
        newX = currentPoint.x()+x;
    }

    int newY;
    if(currentPoint.y()+y<0){
        newY = 0;
    }
    else if(currentPoint.y()+this->height()+y>screenRect.height()){
        newY = screenRect.height() - this->height();
    }
    else{
        newY = currentPoint.y()+y;
    }

    this->setGeometry(newX,newY,this->width(),this->height());
}

void TimerKiller::slt_rightClicked(QPoint pos){
    trayIconMenu->exec(pos);
}

