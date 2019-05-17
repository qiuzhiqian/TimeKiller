#include "roundprogress.h"

#include <QPainter>
#include <QtDebug>
#include <QGuiApplication>
#include <QScreen>

RoundProgress::RoundProgress(QWidget *parent) : QWidget(parent),
  m_lineWidth(10),
  m_lineColor(QColor(165, 220, 62,255)),
  m_borderWidth(5),
  m_borderColor(QColor(215, 215, 215,255)),
  m_bgColor(QColor(51, 152, 219,255)),
  m_value(0),
  m_isPressed(false)
{
    setMinimumSize(100, 100);
}

RoundProgress::~RoundProgress(){
}

void RoundProgress::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawProgress(&painter);
}
void RoundProgress::drawProgress(QPainter *painter)
{
    painter->save();
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int radius = 99 - m_borderWidth;
    //绘制外圆
    QPen pen;
    pen.setWidth(m_borderWidth);
    pen.setColor(m_borderColor);
    painter->setPen(m_borderWidth > 0 ? pen : Qt::NoPen);
    painter->setBrush(m_bgColor);
    //平移坐标轴中心,等比例缩放
    int x = this->width()/2;
    int y = this->height()/2;
    radius = side/2 - m_borderWidth;
    //qDebug()<<"radius:"<<radius;
    QRect rectCircle(x-radius, y-radius, radius * 2, radius * 2);
    //painter->translate(width / 2, height / 2);
    //painter->scale(side / 200.0, side / 200.0);
    painter->drawEllipse(rectCircle);
    //绘制圆弧进度
    pen.setWidth(m_lineWidth);
    pen.setColor(m_lineColor);
    painter->setPen(pen);
    int offset = radius - m_lineWidth - 5;
    //qDebug()<<"offset:"<<offset;
    QRectF rectArc(x-offset, y-offset, offset * 2, offset * 2);
    int startAngle = offset * 16;
    int spanAngle = static_cast<int>(-m_value * 16);
    painter->drawArc(rectArc, startAngle, spanAngle);
    //绘制进度文字
    QFont font;
    font.setPixelSize(offset - 15);
    painter->setFont(font);
    QString strValue = QString("%1%").arg(static_cast<int>(m_value  * 100 / 360));
    painter->drawText(rectCircle, Qt::AlignCenter, strValue);
    painter->restore();
}

void RoundProgress::setValue(int val){
    if(val>360){
        val = 360;
    }
    m_value = val;
    this->update();
}

void RoundProgress::setLineWidth(int lineWidth){
    m_lineWidth = lineWidth;
}

void RoundProgress::setLineColor(const QColor &lineColor){
    m_lineColor = lineColor;
}

void RoundProgress::setBorderWidth(int borderWidth){
    m_borderWidth = borderWidth;
}

void RoundProgress::setBorderColor(const QColor &borderColor){
    m_borderColor = borderColor;
}

void RoundProgress::setBgColor(const QColor &bgColor){
    m_bgColor = bgColor;
}

void RoundProgress::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_mousePos =  event->globalPos();
        m_isPressed = true;
    }
    else if(event->button() == Qt::RightButton){
        emit sgn_rightClicked(event->globalPos());
    }
}

void RoundProgress::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_mousePos =  event->globalPos();
        m_isPressed = false;
    }
}

void RoundProgress::mouseMoveEvent(QMouseEvent *event){
    if(m_isPressed){
        QPoint tempPos = event->globalPos();
        int xDelt = tempPos.x()-m_mousePos.x();
        int yDelt = tempPos.y()-m_mousePos.y();
        emit sgn_drag(xDelt,yDelt);
    }
    m_mousePos =  event->globalPos();
}

