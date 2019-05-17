#ifndef THEME_H
#define THEME_H

#include <QtCore>

#include <QColor>

class Theme
{
public:
    Theme();
    Theme(const QString& name);

    void setName(const QString& name);
    //设置线条宽度+颜色
    void setLineWidth(int lineWidth);
    void setLineColor(const QColor &lineColor);
    //设置边框宽度+颜色
    void setBorderWidth(int borderWidth);
    void setBorderColor(const QColor &borderColor);
    //设置圆角角度+背景颜色
    //void setBorderRadius(int borderRadius);
    void setBgColor(const QColor &bgColor);

    QString getName();
    //设置线条宽度+颜色
    int getLineWidth();
    QColor getLineColor();
    //设置边框宽度+颜色
    int getBorderWidth();
    QColor getBorderColor();
    //设置圆角角度+背景颜色
    QColor getBgColor();

private:
    QString m_name;
    int m_lineWidth;          //线条宽度
    QColor m_lineColor;       //线条颜色
    int m_borderWidth;        //边框宽度
    QColor m_borderColor;     //边框颜色
    QColor m_bgColor;         //背景颜色
};

#endif // THEME_H
