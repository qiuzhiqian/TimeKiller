#include "setting.h"
#include "ui_setting.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QFileDialog>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    m_rp = new RoundProgress(ui->tab_2);
    m_rp->setValue(120);
    m_rp->setGeometry(380,10,150,150);

    loadThemeJson();

    for(auto& item:m_themeList){
        ui->cmb_themelist->addItem(item.getName());
    }

    themeLoad(m_themeList.at(0));

    connect(ui->cmb_themelist,SIGNAL(currentIndexChanged(int)),this,SLOT(slt_themeChanged(int)));
}

Setting::~Setting()
{
    delete ui;
}

bool Setting::loadThemeJson(){
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
    //                             "./",
    //                             tr("Json (*.json)"));
    QFile file("theme.json");
    if(file.open(QIODevice::ReadWrite)){
        QByteArray ba = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(ba);
        if(jsonDoc.isObject()){
            QJsonObject obj = jsonDoc.object();
            QJsonValue val = obj.value("theme");
            if(val.isArray()){
                QJsonArray arry = val.toArray();
                for(auto item:arry){
                    if(item.isObject()){
                        Theme th;
                        QJsonObject themeObj = item.toObject();
                        QJsonValue name = themeObj.value("name");
                        QJsonValue lineWidth = themeObj.value("lineWidth");
                        QJsonValue lineColor = themeObj.value("lineColor");
                        QJsonValue borderWidth = themeObj.value("borderWidth");
                        QJsonValue borderColor = themeObj.value("borderColor");
                        QJsonValue bgColor = themeObj.value("bgColor");

                        th.setName(name.toString());
                        th.setLineWidth(lineWidth.toInt());
                        th.setLineColor(QColor(lineColor.toString()));
                        th.setBorderWidth(borderWidth.toInt());
                        th.setBorderColor(QColor(borderColor.toString()));
                        th.setBgColor(QColor(bgColor.toString()));
                        m_themeList.append(th);
                    }
                }
            }
        }
        return true;
    }
    return true;
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
    themeLoad(m_themeList.at(index));
}
