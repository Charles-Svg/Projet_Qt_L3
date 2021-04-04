#include "notchartwidget.h"
#include <QPainter>
#include <QDebug>

NotChartWidget::NotChartWidget(QWidget *parent)
    : QWidget(parent),_chart(16666,16666)
{


    setMinimumSize(300,300);

    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    _chart.fill(QColorConstants::DarkCyan);

}


void NotChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,_chart);
}
