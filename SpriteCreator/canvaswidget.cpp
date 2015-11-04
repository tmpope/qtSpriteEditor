#include "canvaswidget.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *widget) : QWidget(widget)
{

}

CanvasWidget::~CanvasWidget(){

}


void CanvasWidget::setSpriteDimensions(int width, int height){
    spriteWidth = width;
    spriteHeight = height;
}

/* Indicates to the model what's the haps */
void CanvasWidget::mousePressEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();

    int gridX = x * spriteWidth / width();
    int gridY = y * spriteHeight / height();

//    std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;

    lastX = gridX;
    lastY = gridY;
}

/* Indicates to the model what's the haps */
void CanvasWidget::mouseMoveEvent(QMouseEvent *event){
        int x = event->x();
        int y = event->y();

        int gridX = x * spriteWidth / width();
        int gridY = y * spriteHeight / height();

        if(gridX != lastX || gridY != lastY){

//        std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;
        lastX = gridX;
        lastY = gridY;
    }
}

void CanvasWidget::paintEvent(QPaintEvent *paintEvent){

    // TODO: Request information from the model to handle this
    QPainter painter(this);
    double singleWidth = width() / (double)spriteWidth;
    double singleHeight = height() / (double)spriteHeight;

    for(int row = 0; row < spriteHeight; row++)
        for(int col = 0; col < spriteWidth; col++){
            int x = singleWidth * col + singleWidth / 2;
            int y = singleWidth * row + singleHeight / 2;

            QRect rect(x, y, singleWidth, singleHeight);
            QColor color(0, 0, 0);
            painter.drawRect(rect);

            if(row == 0){
                std::cout << x << " " << y << std::endl;
            }
        }
}





