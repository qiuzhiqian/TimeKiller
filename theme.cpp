#include "theme.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Theme::Theme() :
    m_lineWidth(10),
    m_lineColor(QColor(165, 220, 62,255)),
    m_borderWidth(5),
    m_borderColor(QColor(215, 215, 215,255)),
    m_bgColor(QColor(51, 152, 219,255))
{

}

Theme::Theme(const QString& name) :
    m_lineWidth(10),
    m_lineColor(QColor(165, 220, 62,255)),
    m_borderWidth(5),
    m_borderColor(QColor(215, 215, 215,255)),
    m_bgColor(QColor(51, 152, 219,255))
{
    m_name = name;
}

void Theme::setName(const QString &name){
    m_name = name;
}

void Theme::setLineWidth(int lineWidth){
    m_lineWidth = lineWidth;
}

void Theme::setLineColor(const QColor &lineColor){
    m_lineColor = lineColor;
}

void Theme::setBorderWidth(int borderWidth){
    m_borderWidth = borderWidth;
}

void Theme::setBorderColor(const QColor &borderColor){
    m_borderColor = borderColor;
}

void Theme::setBgColor(const QColor &bgColor){
    m_bgColor = bgColor;
}

QString Theme::getName(){
    return m_name;
}

int Theme::getLineWidth(){
    return m_lineWidth;
}

QColor Theme::getLineColor(){
    return m_lineColor;
}

int Theme::getBorderWidth(){
    return m_borderWidth;
}

QColor Theme::getBorderColor(){
    return m_borderColor;
}

QColor Theme::getBgColor(){
    return m_bgColor;
}

QList<Theme>& ThemeList::getData(){
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

bool ThemeList::exportTheme(){
    QJsonArray array;
    for(auto& item:m_themeList){
        QJsonObject themeObj;
        themeObj.insert("name",item.getName());
        themeObj.insert("lineWidth",item.getLineWidth());
        themeObj.insert("lineColor",item.getLineColor().name(QColor::HexArgb));
        themeObj.insert("borderWidth",item.getBorderWidth());
        themeObj.insert("borderColor",item.getBorderColor().name(QColor::HexArgb));
        themeObj.insert("bgColor",item.getBgColor().name(QColor::HexArgb));
        array.append(themeObj);
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
