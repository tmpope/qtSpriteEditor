#include "canvaswidget.h"
#include <QMouseEvent>
#include <iostream>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent){
    setAttribute(Qt::WA_StaticContents); // I'm not entirely sure what this does
}

void CanvasWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPoint point = event->pos();
        std::cout << "(" << point.x() << ", " << point.y() << ")";
    }
}
void CanvasWidget::mouseMoveEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPoint point = event->pos();
        std::cout << "(" << point.x() << ", " << point.y() << ")";
    }
}
void CanvasWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPoint point = event->pos();
        std::cout << "(" << point.x() << ", " << point.y() << ")";
    }
}
void CanvasWidget::paintEvent(QPaintEvent *event){}
