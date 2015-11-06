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
    sprite = new Sprite(5, 5);

    currentColor = QColor::fromRgb(255, 0, 0);
}

CanvasWidget::~CanvasWidget(){

    if(sprite != NULL)
        delete sprite;
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

    int gridX = x * sprite->getWidth() / width();
    int gridY = y * sprite->getHeight() / height();

    std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;
//    int *r, *g, *b, *a;
//    currentColor.getRgb(r, g, b, a);
    struct Sprite::color pixel(255, 0, 0, 0);
    switch(currentTool) {
        case PENCIL:
            sprite->setPixel(gridX, gridY, currentFrame, pixel);
            std::cout << "Pencil drawing " << pixel.toString() << " to (" << gridX << ", " <<  gridY << ")" << std::endl;
        break;
        default:
        break;

    }

    // TODO: This throws a compiler error as well.
//    int *r, *g, *b, *a;
//    currentColor.getRgb(r, g, b, a);
//    currentSprite->setPixel(gridX, gridY, currentFrame, *r, *g, *b, *a);


    lastX = gridX;
    lastY = gridY;
    repaint();
}

/* Indicates to the model what's the haps */
void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int gridX = x * sprite->getWidth() / width();
    int gridY = y * sprite->getHeight() / height();

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
    double singleWidth = width() / (double)sprite->getWidth();
    double singleHeight = height() / (double)sprite->getHeight();

    for(int row = 0; row < sprite->getHeight(); row++)
        for(int col = 0; col < sprite->getWidth(); col++){
            int x = singleWidth * col + 0 /*singleWidth / 2*/;
            int y = singleHeight * row + 0 /*singleHeight / 2*/;

            QRect rect(x, y, singleWidth, singleHeight);
            struct Sprite::color pixelColor = sprite->getPixel(col, row, currentFrame);
            QColor color(pixelColor.r, pixelColor.g, pixelColor.b);//pixelColor.r, pixelColor.g, pixelColor.b);
            painter.setPen(color);
            painter.fillRect(rect, color);

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



