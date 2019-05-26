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
    ui(new Ui::Setting),
    m_rp(nullptr)
{
    init();
}

Setting::Setting(ThemeList* tl, TaskList *tkl, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Setting),
    m_rp(nullptr){
    m_themeList = tl;
    m_taskList = tkl;
    init();
}

void Setting::init(){
    ui->setupUi(this);

    QList<Theme*>& thList = m_themeList->getData();
    for(auto item: thList){
        ui->cmb_themelist->addItem(item->getName());
    }

    slt_themeChanged(0);

    connect(ui->cmb_themelist,SIGNAL(currentIndexChanged(int)),this,SLOT(slt_themeChanged(int)));
    connect(ui->btn_addTask,SIGNAL(clicked(bool)),this,SLOT(slt_addTask()));

    QStringList enumList;
    BoxDelegate *boxDelegate = new BoxDelegate();
    for(auto& item:m_themeList->getData()){
        enumList.append(item->getName());
    }
    boxDelegate->setItemEnum(enumList);
    ui->taskList->setItemDelegateForColumn(1,boxDelegate);

    TimeDelegate *timeDelegate_start = new TimeDelegate();
    TimeDelegate *timeDelegate_end = new TimeDelegate();
    ui->taskList->setItemDelegateForColumn(2, timeDelegate_start);
    ui->taskList->setItemDelegateForColumn(3, timeDelegate_end);

    ButtonDelegate *btnDeletage = new ButtonDelegate();
    ui->taskList->setItemDelegateForColumn(4, btnDeletage);
    connect(btnDeletage,SIGNAL(sgn_clicked(int,int)),this,SLOT(slt_removeTask(int,int)));

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

void Setting::themeLoad(Theme* th){
    const std::type_info& ti = typeid(*th);
    if(ti == typeid (BallTheme)){
        ui->cmb_style->setCurrentIndex(0);
        BallTheme* tempTheme = (BallTheme*)th;
        ui->btn_linecolor->setStyleSheet("background-color: "+tempTheme->getLineColor().name(QColor::HexArgb));
        ui->btn_bordercolor->setStyleSheet("background-color: "+tempTheme->getBorderColor().name(QColor::HexArgb));
        ui->btn_bgcolor->setStyleSheet("background-color: "+tempTheme->getBgColor().name(QColor::HexArgb));
        ui->le_linewidth->setText(QString::number(tempTheme->getLineWidth()));
        ui->le_borderwidth->setText(QString::number(tempTheme->getBorderWidth()));

        if(m_rp!=nullptr){
            delete m_rp;
        }
        m_rp = new RoundProgress(ui->page_round);
        RoundProgress* tempRP = (RoundProgress*)m_rp;
        tempRP->setValue(120);
        tempRP->setGeometry(250,60,150,150);
        tempRP->setVisible(true);
        //qDebug()<<"round theme";

        tempRP->setLineWidth(tempTheme->getLineWidth());
        tempRP->setLineColor(tempTheme->getLineColor());
        tempRP->setBorderWidth(tempTheme->getBorderWidth());
        tempRP->setBorderColor(tempTheme->getBorderColor());
        tempRP->setBgColor(tempTheme->getBgColor());
        tempRP->update();

        ui->stackedWidget->setCurrentIndex(0);
        ui->page_round->update();
    }
    else if(ti == typeid (WaterTheme)){
        ui->cmb_style->setCurrentIndex(1);
        WaterTheme* tempTheme = (WaterTheme*)th;
        ui->le_waterDensity->setText(QString::number(tempTheme->getWaterDensity()));
        ui->le_waterHeight->setText(QString::number(tempTheme->getWaterHeight()));
        ui->le_waterborderWidth->setText(QString::number(tempTheme->getBorderWidth()));
        ui->btn_usedcolor->setStyleSheet("background-color: "+tempTheme->getUsedColor().name(QColor::HexArgb));
        ui->btn_unUsedcolor->setStyleSheet("background-color: "+tempTheme->getUnUsedColor().name(QColor::HexArgb));
        ui->btn_textcolor->setStyleSheet("background-color: "+tempTheme->getTextColor().name(QColor::HexArgb));

        if(m_rp!=nullptr){
            delete m_rp;
        }
        m_rp = new ProgressBarWater(ui->page_water);
        ProgressBarWater* tempRP = (ProgressBarWater*)m_rp;
        tempRP->setValue(400);
        tempRP->setGeometry(250,60,150,150);
        tempRP->setVisible(true);
        //qDebug()<<"water theme";

        tempRP->setWaterDensity(tempTheme->getWaterDensity());
        tempRP->setWaterHeight(tempTheme->getWaterHeight());
        tempRP->setBorderWidth(tempTheme->getBorderWidth());
        tempRP->setUsedColor(tempTheme->getUsedColor());
        tempRP->setUnUsedColor(tempTheme->getUnUsedColor());
        tempRP->setTextColor(tempTheme->getTextColor());
        tempRP->update();

        ui->stackedWidget->setCurrentIndex(1);
        ui->page_water->update();
    }
}

void Setting::slt_styleChanged(int index){
    //if()
}

void Setting::slt_themeChanged(int index){
    Theme* tempTheme = m_themeList->getData().at(index);
    themeLoad(tempTheme);
}

void Setting::slt_addTask(){
    ui->taskList->model()->insertRow(ui->taskList->model()->rowCount(QModelIndex()));
}

void Setting::slt_removeTask(int row,int column){
    if(column == 4){
        ui->taskList->model()->removeRow(row);
    }
}
