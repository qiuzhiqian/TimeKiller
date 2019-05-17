#ifndef ROUNDPROGRESS_H
#define ROUNDPROGRESS_H

#include <QWidget>

#include <QTimer>

#include <QMouseEvent>
#include <QPoint>

class RoundProgress : public QWidget
{
    Q_OBJECT
public:
    explicit RoundProgress(QWidget *parent = nullptr);
    ~RoundProgress();

protected:
    //void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void drawProgress(QPainter *painter);
private:
    int m_lineWidth;          //线条宽度
    QColor m_lineColor;       //线条颜色
    int m_borderWidth;        //边框宽度
    QColor m_borderColor;     //边框颜色
    QColor m_bgColor;         //背景颜色
    double m_value;           //当前值

    bool m_isPressed;
    QPoint m_mousePos;
public:
    //int getLineWidth()      const;
    //QColor getLineColor()   const;
    //int getBorderWidth()    const;
    //QColor getBorderColor() const;
    //int getBorderRadius()   const;
    //QColor getBgColor()     const;
    //QSize sizeHint()        const;
    //QSize minimumSizeHint() const;
    void setValue(int val);
    //设置线条宽度+颜色
    void setLineWidth(int lineWidth);
    void setLineColor(const QColor &lineColor);
    //设置边框宽度+颜色
    void setBorderWidth(int borderWidth);
    void setBorderColor(const QColor &borderColor);
    //设置圆角角度+背景颜色
    //void setBorderRadius(int borderRadius);
    void setBgColor(const QColor &bgColor);
private slots:
    //void progress();
public Q_SLOTS:
    //设置线条宽度+颜色
    //void setLineWidth(int lineWidth);
    //void setLineColor(const QColor &lineColor);
    //设置边框宽度+颜色
    //void setBorderWidth(int borderWidth);
    //void setBorderColor(const QColor &borderColor);
    //设置圆角角度+背景颜色
    //void setBorderRadius(int borderRadius);
    //void setBgColor(const QColor &bgColor);
Q_SIGNALS:
    //void valueChanged(int value);
    void sgn_drag(int x,int y);
    void sgn_rightClicked(QPoint);

public slots:
};

#endif // ROUNDPROGRESS_H
