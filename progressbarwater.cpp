#include "progressbarwater.h"

#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QDebug>

ProgressBarWater::ProgressBarWater(QWidget *parent) : QWidget(parent),
    m_value(0),
    m_minValue(0),
    m_maxValue(1000),
    m_waterDensity(2),
    m_waterHeight(0.03),
    m_offset(3),
    m_borderWidth(3),
    m_usedColor(QColor("#FF0363BA")),
    m_unUsedColor(QColor("#AAAAE0A7")),
    m_textColor(QColor("#FF6D32A3"))
{
    m_timer = new QTimer(this);
    m_timer->setInterval(10);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(progress()));
    m_timer->start();
}

void ProgressBarWater::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawValue(&painter);
}

void ProgressBarWater::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_mousePos =  event->globalPos();
        m_isPressed = true;
    }
    else if(event->button() == Qt::RightButton){
        emit sgn_rightClicked(event->globalPos());
    }
}

void ProgressBarWater::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_mousePos =  event->globalPos();
        m_isPressed = false;
    }
}

void ProgressBarWater::mouseMoveEvent(QMouseEvent *event){
    if(m_isPressed){
        QPoint tempPos = event->globalPos();
        int xDelt = tempPos.x()-m_mousePos.x();
        int yDelt = tempPos.y()-m_mousePos.y();
        emit sgn_drag(xDelt,yDelt);
    }
    m_mousePos =  event->globalPos();
}

void ProgressBarWater::drawValue(QPainter *painter)
{
    int height = this-> height();
    int width = this->width();
    int side = qMin(width, height);

    //计算当前值所占百分比
    double percent = 1 - (double)(m_value - m_minValue) / (m_maxValue - m_minValue);

    //正弦曲线公式 y = A * sin(ωx + φ) + k

    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double w = (m_waterDensity * M_PI)/width;

    //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比
    double A = height * m_waterHeight;

    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比
    double k = height * percent;

    //第一条波浪路径集合
    QPainterPath waterPath1;
    //第二条波浪路径集合
    QPainterPath waterPath2;

    QPainterPath hightPath;

    //移动到左上角起始点
    waterPath1.moveTo(0, height);
    waterPath2.moveTo(0, height);

    hightPath.moveTo(0,0);

    for(int x = 0; x <= width; x++) {
        //第一条波浪Y轴
        double waterY1 = (double)(A * qSin(w * x + m_offset)) + k;

        //第二条波浪Y轴
        double waterY2 = (double)(A * qSin(w * x + m_offset + (width / 2 * w))) + k;

        //如果当前值为最小值则Y轴为高度
        if (this->m_value == m_minValue) {
            waterY1 = height;
            waterY2 = height;
        }

        //如果当前值为最大值则Y轴为0
        if (this->m_value == m_maxValue) {
            waterY1 = 0;
            waterY2 = 0;
        }

        double hightY = qMin(waterY1,waterY2);

        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);

        hightPath.lineTo(x,hightY);
    }

    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(width, height);
    waterPath2.lineTo(width, height);

    hightPath.lineTo(width,0);

    //大路径
    QPainterPath bigPath;

    side = side - m_borderWidth * 2;
    bigPath.addEllipse((width - side) / 2, m_borderWidth, side, side);

    painter->save();

    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;

    painter->setPen(Qt::NoPen);
    QColor waterColor1 = m_usedColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = m_usedColor;
    waterColor2.setAlpha(180);

    //第一条波浪挖去后的路径
    path = bigPath.intersected(waterPath1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);

    //第二条波浪挖去后的路径
    path = bigPath.intersected(waterPath2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_unUsedColor);
    path = bigPath.intersected(hightPath);
    painter->drawPath(path);

    //绘制进度文字
    QPainterPath textPath;
    QFont font;
    QRect rect(0,0,side,side);
    font.setPixelSize(52);
    //painter->setFont(font);
    painter->setBrush(m_textColor);
    QString strValue = QString("%1%").arg((m_value - m_minValue)*100 / (m_maxValue - m_minValue));
    textPath.addText(side/3,side*2/3,font,strValue);
    painter->drawPath(textPath);

    painter->restore();
}

void ProgressBarWater::progress(){
    //if(value<maxValue)
    //{
    //    value++;
    //}
    m_offset += 0.04;
    if (m_offset > (this->width() / 2)) {
        m_offset = 0;
    }

    this->update();
}

void ProgressBarWater::setValue(int val){
    m_value = val;
}

void ProgressBarWater::setWaterDensity(double val){
    m_waterDensity = val;
}

void ProgressBarWater::setWaterHeight(double val){
    m_waterHeight = val;
}

void ProgressBarWater::setBorderWidth(int borderWidth){
    m_borderWidth = borderWidth;
}

void ProgressBarWater::setUsedColor(const QColor &clr){
    m_usedColor = clr;
}

void ProgressBarWater::setUnUsedColor(const QColor &clr){
    m_unUsedColor = clr;
    //qDebug()<<"set unused:"<<m_unUsedColor.name(QColor::HexArgb);
}

void ProgressBarWater::setTextColor(const QColor &clr){
    m_textColor = clr;
}

int ProgressBarWater::getValue(){
    return m_value;
}


