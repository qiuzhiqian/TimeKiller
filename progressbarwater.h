#ifndef PROGRESSBARWATER_H
#define PROGRESSBARWATER_H

#include <QWidget>
#include <QColor>
#include <QTimer>

#include <QMouseEvent>
#include <QPoint>

class ProgressBarWater : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressBarWater(QWidget *parent = nullptr);
    void drawValue(QPainter *painter);

    void setValue(int val);
    void setWaterDensity(double val);
    void setWaterHeight(double val);
    void setBorderWidth(int borderWidth);
    void setUsedColor(const QColor &clr);
    void setUnUsedColor(const QColor &clr);
    void setTextColor(const QColor &clr);

    int getValue();
    double getWaterDensity();
    double getWaterHeight();
    int getBorderWidth();
    QColor getUsedColor();
    QColor getUnUsedColor();
    QColor getTextColor();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int m_value;
    int m_minValue;
    int m_maxValue;
    double m_waterDensity;
    double m_waterHeight;
    double m_offset;

    int m_borderWidth;
    QColor m_usedColor;
    QColor m_unUsedColor;
    QColor m_textColor;

    QTimer *m_timer;          //定时器实现动态水波

    bool m_isPressed;
    QPoint m_mousePos;

Q_SIGNALS:
    void sgn_drag(int x,int y);
    void sgn_rightClicked(QPoint);

public slots:
    void progress();
};

#endif // PROGRESSBARWATER_H
