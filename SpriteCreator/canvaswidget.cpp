#include "canvaswidget.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>

CanvasWidget::CanvasWidget(int width, int height)
{
    spriteWidth = width;
    spriteHeight = height;

    painter = new QPainter();
}

CanvasWidget::~CanvasWidget(){
    delete painter;
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

    std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;

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

        std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;
        lastX = gridX;
        lastY = gridY;
    }
}

void CanvasWidget::drawGrid(){
    // TODO: Setup a painter object and have that draw the grid here
}
