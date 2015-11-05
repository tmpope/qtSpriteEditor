#include "canvaswidget.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QRgb>
#include "sprite.h"

CanvasWidget::CanvasWidget(QWidget *widget) : QWidget(widget)
{
    currentTool = PENCIL;
    lastTool = ERASER;

    currentColor = QColor::fromRgb(255, 255, 255);
}

CanvasWidget::~CanvasWidget(){

    // TODO: I attempted to call the destructor on the currentSprite, but this throws a compiler
    // error when it's uncommented. We need to figure out what the problem is.
//    if(currentSprite != nullptr)
//        delete currentSprite;
}


void CanvasWidget::setSpriteDimensions(int width, int height)
{
    spriteWidth = width;
    spriteHeight = height;
}

/* Indicates to the model what's the haps */
void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton && event->button() != Qt::RightButton)
        return;

    clickedButton = event->button();

    if(event->button() == Qt::RightButton){
        possible_tool_t temp = currentTool;
        currentTool = ERASER;
        lastTool = temp;

        std::cout << "Right click; handling as eraser!" << std::endl;
    }

    int x = event->x();
    int y = event->y();

    int gridX = x * spriteWidth / width();
    int gridY = y * spriteHeight / height();

    std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;
    int *r, *g, *b, *a;
    currentColor.getRgb(r, g, b, a);
    currentSprite->setPixel(gridX, gridY, currentFrame, *r, *g, *b, *a);


    lastX = gridX;
    lastY = gridY;

}

/* Indicates to the model what's the haps */
void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
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

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton && event->button() != Qt::RightButton)
        return;

    if(event->button() == Qt::RightButton){
        currentTool = lastTool;
        std::cout << "End of right click; no longer erasing!" << std::endl;
    }
}

void CanvasWidget::paintEvent(QPaintEvent *paintEvent)
{
    // TODO: Request information from the model to handle this
//    if(currentSprite == nullptr)
//        return;

    // HOW TO DO: Simply get the lastX and lastY from the model, and only update that one.
    // You don't want to redraw everything over and over. The only exception is when a
    // sprite is pulled up. Then you'll want to redraw everything. Maybe have a variable
    // that handles when that happens.
    QPainter painter(this);
    double singleWidth = width() / (double)spriteWidth;
    double singleHeight = height() / (double)spriteHeight;

    for(int row = 0; row < spriteHeight; row++)
        for(int col = 0; col < spriteWidth; col++){
            int x = singleWidth * col + 0 /*singleWidth / 2*/;
            int y = singleHeight * row + 0 /*singleHeight / 2*/;

            QRect rect(x, y, singleWidth, singleHeight);
            QColor color(0, 0, 0);
            painter.drawRect(rect);

            if(row == 0 && col == 0){
                std::cout << width() << " " << height() << std::endl;
            }
        }
}

void CanvasWidget::setCurrentTool(possible_tool_t tool)
{
    lastTool = currentTool;
    currentTool = tool;
}

void CanvasWidget::setCurrentColor(int r, int g, int b, int a){
    currentColor.setRgb(r, g, b, a);
}



