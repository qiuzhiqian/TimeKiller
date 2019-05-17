#include "theme.h"

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
