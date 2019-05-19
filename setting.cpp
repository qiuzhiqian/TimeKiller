#include "setting.h"
#include "ui_setting.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QFileDialog>

#include <QDebug>

#include "taskmodel.h"
#include "timedelegate.h"

#include "boxdelegate.h"
#include "buttondelegate.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    init();
}

Setting::Setting(ThemeList* tl, TaskList *tkl, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Setting){
    m_themeList = tl;
    m_taskList = tkl;
    init();
}

void Setting::init(){
    ui->setupUi(this);
    m_rp = new RoundProgress(ui->tab_2);
    m_rp->setValue(120);
    m_rp->setGeometry(380,10,150,150);

    QList<Theme>& thList = m_themeList->getData();
    for(auto& item: thList){
        ui->cmb_themelist->addItem(item.getName());
    }

    themeLoad(m_themeList->getData().at(0));

    connect(ui->cmb_themelist,SIGNAL(currentIndexChanged(int)),this,SLOT(slt_themeChanged(int)));
    connect(ui->btn_addTask,SIGNAL(clicked(bool)),this,SLOT(slt_addTask()));

    QStringList enumList;
    BoxDelegate *boxDelegate = new BoxDelegate();
    for(auto& item:m_themeList->getData()){
        enumList.append(item.getName());
    }
    boxDelegate->setItemEnum(enumList);
    ui->taskList->setItemDelegateForColumn(1,boxDelegate);

    TimeDelegate *timeDelegate_start = new TimeDelegate();
    TimeDelegate *timeDelegate_end = new TimeDelegate();
    ui->taskList->setItemDelegateForColumn(2, timeDelegate_start);
    ui->taskList->setItemDelegateForColumn(3, timeDelegate_end);

    ButtonDelegate *btnDeletage = new ButtonDelegate();
    ui->taskList->setItemDelegateForColumn(4, btnDeletage);

    TaskModel* taskmodel = new TaskModel(m_taskList);
    ui->taskList->setModel(taskmodel);

    ui->taskList->setColumnWidth(0,65);
    ui->taskList->setColumnWidth(1,85);
    ui->taskList->setColumnWidth(2,220);
    ui->taskList->setColumnWidth(3,220);
    ui->taskList->setColumnWidth(4,45);
}

Setting::~Setting()
{
    m_taskList->exportTask();
    m_themeList->exportTheme();
    delete ui;
}

void Setting::themeLoad(Theme th){
    ui->btn_linecolor->setStyleSheet("background-color: "+th.getLineColor().name(QColor::HexArgb));
    ui->btn_bordercolor->setStyleSheet("background-color: "+th.getBorderColor().name(QColor::HexArgb));
    ui->btn_bgcolor->setStyleSheet("background-color: "+th.getBgColor().name(QColor::HexArgb));
    ui->le_linewidth->setText(QString::number(th.getLineWidth()));
    ui->le_borderwidth->setText(QString::number(th.getBorderWidth()));

    m_rp->setLineWidth(th.getLineWidth());
    m_rp->setLineColor(th.getLineColor());
    m_rp->setBorderWidth(th.getBorderWidth());
    m_rp->setBorderColor(th.getBorderColor());
    m_rp->setBgColor(th.getBgColor());
    m_rp->update();
}

void Setting::slt_themeChanged(int index){
    themeLoad(m_themeList->getData().at(index));
}

void Setting::slt_addTask(){
    ui->taskList->model()->insertRow(ui->taskList->model()->rowCount(QModelIndex()));
}
