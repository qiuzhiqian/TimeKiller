#ifndef THEME_H
#define THEME_H

#include <QtCore>

#include <QColor>

class Theme:public QObject{
public:
    explicit Theme(const QString& name = "default");

    void setName(const QString& name);
    QString getName();
private:
    QString m_name;
};

class BallTheme :public Theme
{
public:
    BallTheme(const QString& name = "default");

    //设置线条宽度+颜色
    void setLineWidth(int lineWidth);
    void setLineColor(const QColor &lineColor);
    //设置边框宽度+颜色
    void setBorderWidth(int borderWidth);
    void setBorderColor(const QColor &borderColor);
    //设置圆角角度+背景颜色
    //void setBorderRadius(int borderRadius);
    void setBgColor(const QColor &bgColor);

    //设置线条宽度+颜色
    int getLineWidth();
    QColor getLineColor();
    //设置边框宽度+颜色
    int getBorderWidth();
    QColor getBorderColor();
    //设置圆角角度+背景颜色
    QColor getBgColor();

private:
    int m_lineWidth;          //线条宽度
    QColor m_lineColor;       //线条颜色
    int m_borderWidth;        //边框宽度
    QColor m_borderColor;     //边框颜色
    QColor m_bgColor;         //背景颜色
};

class WaterTheme :public Theme{
public:
    WaterTheme(const QString& name = "default");

    void setWaterDensity(double val);
    void setWaterHeight(double val);
    void setBorderWidth(int borderWidth);
    void setUsedColor(const QColor &clr);
    void setUnUsedColor(const QColor &clr);
    void setTextColor(const QColor &clr);

    double getWaterDensity();
    double getWaterHeight();
    int getBorderWidth();
    QColor getUsedColor();
    QColor getUnUsedColor();
    QColor getTextColor();

private:
    double m_waterDensity;
    double m_waterHeight;

    int m_borderWidth;
    QColor m_usedColor;
    QColor m_unUsedColor;
    QColor m_textColor;
};

class ThemeList{
public:
    ThemeList(){}
    QList<Theme*>& getData();

    bool importTheme();
    bool exportTheme();

private:
    QList<Theme*> m_themeList;
};

#endif // THEME_H
