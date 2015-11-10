#include "canvaswidget.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QRgb>
#include <string>
#include "sprite.h"

CanvasWidget::CanvasWidget(QWidget *widget) : QWidget(widget)
{
    currentTool = PENCIL;
    lastTool = ERASER;
    Csprite = new Sprite(4, 4);

    currentColor = QColor::fromRgb(255, 25, 25);
    currentFrame = 0;
}

CanvasWidget::~CanvasWidget(){
    if(Csprite != NULL)
        delete Csprite;
}

std::string CanvasWidget::getSprite()
{
    std::cout << "trying sprite->toString() from canvasWidget" << std::endl;
    std::cout << Csprite->SpritetoString();    //this is throwing the error...
    //std::string s = sprite->toString().c_str();
    std::cout << "hello from after sprite->toString()" << std::endl;
    //std::cout << "Grid coordinates: (" << ", " << ")" << sprite->toString() << std::endl;
    return "hello";
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

    int gridX = x * Csprite->getWidth() / width();
    int gridY = y * Csprite->getHeight() / height();
    if (gridX >= Csprite->getWidth())
        gridX = Csprite->getWidth() - 1;
    if (gridY >= Csprite->getHeight())
        gridY = Csprite->getHeight() - 1;
    if (gridX < 0)
        gridX = 0;
    if(gridY < 0)
        gridY = 0;

    //std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << sprite->toString() << std::endl;

    colorSelectedPixel(gridX, gridY);

    lastX = gridX;
    lastY = gridY;
    repaint();
}

/* Indicates to the model what's the haps */
void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    int gridX = x * Csprite->getWidth() / width();
    int gridY = y * Csprite->getHeight() / height();
    if (gridX >= Csprite->getWidth())
        gridX = Csprite->getWidth() - 1;
    if (gridY >= Csprite->getHeight())
        gridY = Csprite->getHeight() - 1;
    if (gridX < 0)
        gridX = 0;
    if(gridY < 0)
        gridY = 0;

    if(gridX != lastX || gridY != lastY){

        //std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;
        colorSelectedPixel(gridX, gridY);
        repaint();

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
    if(Csprite == NULL)
        return;

    QPainter painter(this);
    double singleWidth = width() / (double)Csprite->getWidth();
    double singleHeight = height() / (double)Csprite->getHeight();

    for(int row = 0; row < Csprite->getHeight(); row++)
        for(int col = 0; col < Csprite->getWidth(); col++){
            int x = singleWidth * col;
            int y = singleHeight * row;

            QRect rect(x, y, singleWidth, singleHeight);
            struct Sprite::color pixelColor = Csprite->getPixel(col, row, currentFrame);
            QColor color(pixelColor.r, pixelColor.g, pixelColor.b);
            painter.setPen(color);
            painter.fillRect(rect, color);

            if(row == 0 && col == 0){
               //std::cout << width() << " " << height() << std::endl;
            }
        }
}

void CanvasWidget::setCurrentTool(possible_tool_t tool)
{
    lastTool = currentTool;
    currentTool = tool;
}

void CanvasWidget::setCurrentColor(int r, int g, int b, int a)
{
    currentColor.setRgb(r, g, b, a);
}

void CanvasWidget::colorSelectedPixel(int xPos, int yPos){
    int *r = new int(0);
    int *g = new int(0);
    int *b = new int(0);
    int *a = new int(0);

    currentColor.getRgb(r, g, b, a);
    struct Sprite::color pixel(*r, *g, *b, *a);

    delete r;
    delete g;
    delete b;
    delete a;

    switch(currentTool) {
        case PENCIL:
            Csprite->setPixel(xPos, yPos, currentFrame, pixel);
            std::cout << "Pencil drawing " << pixel.toString() << " to (" << xPos << ", " <<  yPos << ")" << std::endl;
        break;

        case ERASER:
            pixel = Sprite::color(255, 255, 255, 255);
            Csprite->setPixel(xPos, yPos, currentFrame, pixel);
            std::cout << "Erasing pixel at (" << xPos << ", " << yPos << ")" << std::endl;
        break;

        case BUCKET:
            Csprite->fillPixel(xPos, yPos, currentFrame, pixel);
            std::cout << "Filling pixels at (" << xPos << ", " << yPos << ")" << std::endl;
        break;

        case EYE_DROPPER:
            pixel = Csprite->getPixel(xPos, yPos, currentFrame);
            currentColor.setRgb(pixel.r, pixel.g, pixel.b, pixel.a);
            // TODO: Change tool back to pencil here?
//            setCurrentTool(PENCIL);
        break;

        default:
        break;

    }
}



