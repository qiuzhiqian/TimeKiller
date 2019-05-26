#include "timerkiller.h"
#include "ui_timerkiller.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QScreen>
#include <QMessageBox>

#include "setting.h"

TimerKiller::TimerKiller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerKiller),
    m_currentIndex(0),
    m_rp(nullptr)
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

    aboutAction = new QAction(this);
    aboutAction->setText(tr("关于"));
    //setAction->setIcon(QIcon(":/icons/restore.bmp"));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(slt_about()));

    closeAction = new QAction(this);
    closeAction->setText(tr("退出"));
    //closeAction->setIcon(QIcon(":/icons/shutdown03.jpg"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(slt_close()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(setAction);
    trayIconMenu->addAction(aboutAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(closeAction);

    m_systemTray->setContextMenu(trayIconMenu);
    m_systemTray->show();

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);

    m_themes.importTheme();
    m_tasks.importTask();

    sectimer = new QTimer();
    sectimer->setInterval(500);
    connect(sectimer,SIGNAL(timeout()),this,SLOT(timerProgress()));

    if(m_tasks.getData().size()>0){
        m_currentIndex = -1;
        slt_taskChange();

        m_loopTimer = new QTimer();
        m_loopTimer->setInterval(10*1000);
        connect(m_loopTimer,SIGNAL(timeout()),this,SLOT(slt_taskChange()));
        m_loopTimer->start();
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
    const std::type_info& ti = typeid (*m_rp);
    double showVal = 0;
    if(ti == typeid (RoundProgress)){
        if(endTime>startTime && nowTime>=startTime && nowTime<=endTime){
            qint64 sumVal = endTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();
            qint64 usedVal = nowTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();

            showVal = (double(usedVal) / sumVal)*360.0;
            //qDebug()<<"sumVal:"<<sumVal<<" usedVal:"<<usedVal<<" val:"<<val<<" db:"<<db*360;
        }
        else if(endTime>startTime && nowTime>endTime){
            showVal = 360;
        }
        RoundProgress* tempRp = (RoundProgress*)m_rp;
        tempRp->setValue(showVal);
    }
    else if(ti == typeid (ProgressBarWater)){
        if(endTime>startTime && nowTime>=startTime && nowTime<=endTime){
            qint64 sumVal = endTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();
            qint64 usedVal = nowTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch();

            showVal = (double(usedVal) / sumVal)*1000.0;
        }
        else if(endTime>startTime && nowTime>endTime){
            showVal = 1000;
        }
        ProgressBarWater* tempRp = (ProgressBarWater*)m_rp;
        tempRp->setValue(showVal);
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

void TimerKiller::slt_about(){
    QMessageBox msg;
    msg.setText(tr("TimeKiller v1.0.0"));
    msg.exec();
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

void TimerKiller::slt_taskChange(){
    if(m_currentIndex<m_tasks.getData().size()-1){
        m_currentIndex++;
    }
    else{
        m_currentIndex = 0;
    }

    Task& currentTask = const_cast<Task&>(m_tasks.getData().at(m_currentIndex));
    QString themeStr = currentTask.getTheme();
    int themeIndex = -1;
    for(int i=0;i<m_themes.getData().size();i++){
        if(m_themes.getData()[i]->getName() == themeStr){
            themeIndex = i;
            break;
        }
    }

    if(themeIndex>=0){
        sectimer->stop();

        Theme* tempTheme = m_themes.getData()[themeIndex];
        taskWedgitShow(tempTheme);
        m_rp->setToolTip(currentTask.getName());

        startTime = currentTask.getStart();
        endTime = currentTask.getEnd();
        //qDebug()<<"start time:"<<startTime.toString(Qt::ISODate);
        //qDebug()<<"end time:"<<endTime.toString(Qt::ISODate);

        if(endTime<startTime){
            endTime = startTime;
        }
        sectimer->start();
    }
}

void TimerKiller::taskWedgitShow(Theme* th){
    QHBoxLayout *layout = (QHBoxLayout *)this->layout();

    if(m_rp != nullptr){

        //delete m_rp;

        if(!layout->isEmpty()){
            layout->removeWidget(m_rp);
            m_rp->deleteLater();
        }
    }

    //QString className = typeid(*th).name();//th->metaObject()->className();
    const std::type_info& ti = typeid(*th);
    if(ti == typeid(BallTheme)){
        m_rp = new RoundProgress(this);
        RoundProgress* tempRP = (RoundProgress*)m_rp;
        layout->setMargin(0);
        layout->setSpacing(0);
        layout->addWidget(m_rp);
        connect(m_rp,SIGNAL(sgn_drag(int,int)),this,SLOT(slt_drag(int,int)));
        //m_rp->setToolTip(tr("this is tool tip"));
        connect(m_rp,SIGNAL(sgn_rightClicked(QPoint)),this,SLOT(slt_rightClicked(QPoint)));

        BallTheme* tempTheme = (BallTheme*)th;
        tempRP->setLineWidth(tempTheme->getLineWidth());
        tempRP->setLineColor(tempTheme->getLineColor());
        tempRP->setBorderWidth(tempTheme->getBorderWidth());
        tempRP->setBorderColor(tempTheme->getBorderColor());
        tempRP->setBgColor(tempTheme->getBgColor());
    }
    else if(ti == typeid(WaterTheme)){
        m_rp = new ProgressBarWater(this);
        ProgressBarWater* tempRP = (ProgressBarWater*)m_rp;
        layout->setMargin(0);
        layout->setSpacing(0);
        layout->addWidget(m_rp);
        connect(m_rp,SIGNAL(sgn_drag(int,int)),this,SLOT(slt_drag(int,int)));
        connect(m_rp,SIGNAL(sgn_rightClicked(QPoint)),this,SLOT(slt_rightClicked(QPoint)));

        WaterTheme* tempTheme = (WaterTheme*)th;
        tempRP->setWaterDensity(tempTheme->getWaterDensity());
        tempRP->setWaterHeight(tempTheme->getWaterHeight());
        tempRP->setBorderWidth(tempTheme->getBorderWidth());
        tempRP->setUsedColor(tempTheme->getUsedColor());
        tempRP->setUnUsedColor(tempTheme->getUnUsedColor());
        tempRP->setTextColor(tempTheme->getTextColor());
    }
    timerProgress();
}
