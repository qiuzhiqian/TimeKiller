#include "theme.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Theme::Theme(const QString& name):m_name(name){
}

void Theme::setName(const QString &name){
    m_name = name;
}

QString Theme::getName(){
    return m_name;
}

BallTheme::BallTheme(const QString& name) :
    Theme(name),
    m_lineWidth(10),
    m_lineColor(QColor(165, 220, 62,255)),
    m_borderWidth(5),
    m_borderColor(QColor(215, 215, 215,255)),
    m_bgColor(QColor(51, 152, 219,255))
{
}

void BallTheme::setLineWidth(int lineWidth){
    m_lineWidth = lineWidth;
}

void BallTheme::setLineColor(const QColor &lineColor){
    m_lineColor = lineColor;
}

void BallTheme::setBorderWidth(int borderWidth){
    m_borderWidth = borderWidth;
}

void BallTheme::setBorderColor(const QColor &borderColor){
    m_borderColor = borderColor;
}

void BallTheme::setBgColor(const QColor &bgColor){
    m_bgColor = bgColor;
}

int BallTheme::getLineWidth(){
    return m_lineWidth;
}

QColor BallTheme::getLineColor(){
    return m_lineColor;
}

int BallTheme::getBorderWidth(){
    return m_borderWidth;
}

QColor BallTheme::getBorderColor(){
    return m_borderColor;
}

QColor BallTheme::getBgColor(){
    return m_bgColor;
}

WaterTheme::WaterTheme(const QString& name):
    Theme(name),
    m_waterDensity(2),
    m_waterHeight(0.03),
    m_borderWidth(3),
    m_usedColor(QColor("#FF0363BA")),
    m_unUsedColor(QColor("#AAAAE0A7")),
    m_textColor(QColor("#FF6D32A3")){
}

void WaterTheme::setWaterDensity(double val){
    m_waterDensity = val;
}

void WaterTheme::setWaterHeight(double val){
    m_waterHeight = val;
}

void WaterTheme::setBorderWidth(int borderWidth){
    m_borderWidth = borderWidth;
}

void WaterTheme::setUsedColor(const QColor &clr){
    m_usedColor = clr;
}

void WaterTheme::setUnUsedColor(const QColor &clr){
    m_unUsedColor = clr;
}

void WaterTheme::setTextColor(const QColor &clr){
    m_textColor = clr;
}

double WaterTheme::getWaterDensity(){
    return m_waterDensity;
}

double WaterTheme::getWaterHeight(){
    return m_waterHeight;
}

int WaterTheme::getBorderWidth(){
    return m_borderWidth;
}

QColor WaterTheme::getUsedColor(){
    return m_usedColor;
}

QColor WaterTheme::getUnUsedColor(){
    return m_unUsedColor;
}

QColor WaterTheme::getTextColor(){
    return m_textColor;
}

QList<Theme*>& ThemeList::getData(){
    return m_themeList;
}

bool ThemeList::importTheme(){
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
                        QJsonObject themeObj = item.toObject();
                        QString theme = themeObj.value("style").toString();
                        //Theme* th;
                        if(theme == "round"){
                            QJsonValue name = themeObj.value("name");
                            QJsonValue lineWidth = themeObj.value("lineWidth");
                            QJsonValue lineColor = themeObj.value("lineColor");
                            QJsonValue borderWidth = themeObj.value("borderWidth");
                            QJsonValue borderColor = themeObj.value("borderColor");
                            QJsonValue bgColor = themeObj.value("bgColor");

                            BallTheme* tempTheme = new BallTheme(name.toString());
                            tempTheme->setName(name.toString());
                            tempTheme->setLineWidth(lineWidth.toInt());
                            tempTheme->setLineColor(QColor(lineColor.toString()));
                            tempTheme->setBorderWidth(borderWidth.toInt());
                            tempTheme->setBorderColor(QColor(borderColor.toString()));
                            tempTheme->setBgColor(QColor(bgColor.toString()));
                            m_themeList.append(tempTheme);
                        }
                        else if(theme == "water"){
                            QJsonValue name = themeObj.value("name");
                            QJsonValue waterDensity = themeObj.value("waterDensity");
                            QJsonValue waterHeight = themeObj.value("waterHeight");
                            QJsonValue borderWidth = themeObj.value("borderWidth");
                            QJsonValue usedColor = themeObj.value("usedColor");
                            QJsonValue UnUsedColor = themeObj.value("unUsedColor");
                            QJsonValue textColor = themeObj.value("textColor");

                            WaterTheme* tempTheme = new WaterTheme(name.toString());
                            tempTheme->setName(name.toString());
                            tempTheme->setWaterDensity(waterDensity.toDouble());
                            tempTheme->setWaterHeight(waterHeight.toDouble());
                            tempTheme->setBorderWidth(borderWidth.toInt());
                            tempTheme->setUsedColor(QColor(usedColor.toString()));
                            tempTheme->setUnUsedColor(QColor(UnUsedColor.toString()));
                            tempTheme->setTextColor(QColor(textColor.toString()));
                            m_themeList.append(tempTheme);
                        }
                    }
                }
            }
        }
        return true;
    }
    return true;
}

bool ThemeList::exportTheme(){
    QJsonArray array;
    for(auto iter=m_themeList.begin();iter!=m_themeList.end();++iter){
        const std::type_info& ti = typeid(*(*iter));
        if( ti == typeid(BallTheme) ){
            BallTheme* item = (BallTheme*)(*iter);

            QJsonObject themeObj;
            themeObj.insert("style","round");
            themeObj.insert("name",item->getName());
            themeObj.insert("lineWidth",item->getLineWidth());
            themeObj.insert("lineColor",item->getLineColor().name(QColor::HexArgb));
            themeObj.insert("borderWidth",item->getBorderWidth());
            themeObj.insert("borderColor",item->getBorderColor().name(QColor::HexArgb));
            themeObj.insert("bgColor",item->getBgColor().name(QColor::HexArgb));
            array.append(themeObj);
        }
        else if(ti == typeid(WaterTheme)){
            WaterTheme* item = (WaterTheme*)(*iter);

            QJsonObject themeObj;
            themeObj.insert("style","water");
            themeObj.insert("name",item->getName());
            themeObj.insert("waterDensity",item->getWaterDensity());
            themeObj.insert("waterHeight",item->getWaterHeight());
            themeObj.insert("borderWidth",item->getBorderWidth());
            themeObj.insert("usedColor",item->getUsedColor().name(QColor::HexArgb));
            themeObj.insert("unUsedColor",item->getUnUsedColor().name(QColor::HexArgb));
            themeObj.insert("textColor",item->getTextColor().name(QColor::HexArgb));
            array.append(themeObj);
        }
    }

    QJsonObject jsonObj;
    jsonObj.insert("theme",array);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObj);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Indented);

    QFile file("theme.json");
    if(file.open(QIODevice::ReadWrite|QIODevice::Truncate)){
        file.write(byteArray);
        file.close();
    }
    return true;
}
