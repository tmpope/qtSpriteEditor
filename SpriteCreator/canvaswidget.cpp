#include "canvaswidget.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QRgb>
#include <string>
#include "sprite.h"
#include <cassert>

CanvasWidget::CanvasWidget(QWidget *widget) : QWidget(widget)
{
    std::cout << "CanvasWidget constructor was called." << std::endl;
    currentTool = PENCIL;
    lastTool = ERASER;
    sprite = new Sprite(32, 32);

    currentColor = QColor::fromRgb(255, 25, 25);
    currentFrame = 0;
}

CanvasWidget::~CanvasWidget(){
    std::cout << "CanvasWidget destructor was called." << std::endl;
    if(sprite != NULL)
        delete sprite;
}

Sprite* CanvasWidget::getSprite()
{
    sprite;
    sprite->toString();
    assert(sprite);

    return sprite;
}

void CanvasWidget::loadSpriteFromString(std::string sspString)
{
    sprite = new Sprite(sspString);
    repaint();
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
    if (gridX >= sprite->getWidth())
        gridX = sprite->getWidth() - 1;
    if (gridY >= sprite->getHeight())
        gridY = sprite->getHeight() - 1;
    if (gridX < 0)
        gridX = 0;
    if(gridY < 0)
        gridY = 0;

//    std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << sprite->toString() << std::endl;

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

    int gridX = x * sprite->getWidth() / width();
    int gridY = y * sprite->getHeight() / height();
    if (gridX >= sprite->getWidth())
        gridX = sprite->getWidth() - 1;
    if (gridY >= sprite->getHeight())
        gridY = sprite->getHeight() - 1;
    if (gridX < 0)
        gridX = 0;
    if(gridY < 0)
        gridY = 0;

    if(gridX != lastX || gridY != lastY){

        std::cout << "Grid coordinates: (" << gridX << ", " << gridY << ")" << std::endl;
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
    // TODO: Onion skin stuff
    if(sprite == NULL)
        return;

    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.drawRect(0, 0, width() - 1, height() - 1);

    double singleWidth = width() / (double)sprite->getWidth();
    double singleHeight = height() / (double)sprite->getHeight();

    for(int row = 0; row < sprite->getHeight(); row++){
        for(int col = 0; col < sprite->getWidth(); col++){
            int x = singleWidth * col;
            int y = singleHeight * row;

            QRect rect(x, y, singleWidth, singleHeight);
            struct Sprite::color pixelColor;
            if(onionSkinEnabled && currentFrame != 0 && sprite->getPixel(col, row, currentFrame).a == 0){
                pixelColor = sprite->getPixel(col, row, currentFrame - 1);
                pixelColor.a = pixelColor.a * 0.65;
                std::cout << "We're printing an onion skin pixel1" << std::endl;
            }
            else
                pixelColor = sprite->getPixel(col, row, currentFrame);
//            pixelColor = sprite->getPixel(col, row, currentFrame);
            QColor color(pixelColor.r, pixelColor.g, pixelColor.b, pixelColor.a);
            painter.setPen(color);
            painter.fillRect(rect, color);

            if(row == 0 && col == 0){
                std::cout << width() << " " << height() << std::endl;
            }
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
            sprite->setPixel(xPos, yPos, currentFrame, pixel);
            std::cout << "Pencil drawing " << pixel.toString() << " to (" << xPos << ", " <<  yPos << ")" << std::endl;
        break;

        case ERASER:
            pixel = Sprite::color(255, 255, 255, 0);
            sprite->setPixel(xPos, yPos, currentFrame, pixel);
            std::cout << "Erasing pixel at (" << xPos << ", " << yPos << ")" << std::endl;
        break;

        case BUCKET:
            sprite->fillPixel(xPos, yPos, currentFrame, pixel);
            std::cout << "Filling pixels at (" << xPos << ", " << yPos << ")" << std::endl;
        break;

        case EYE_DROPPER:
            std::cout << "Using eye dropper; grabbed a color." << std::endl;
            pixel = sprite->getPixel(xPos, yPos, currentFrame);
            currentColor.setRgb(pixel.r, pixel.g, pixel.b, pixel.a);
            std::cout << "Current color: " << pixel.r  << " " << pixel.g << " " << pixel.b << " " << std::endl;
            setCurrentTool(PENCIL);
        break;

        default:
        break;

    }
}

void CanvasWidget::save(std::string s)
{
    sprite->save(s);
}

void CanvasWidget::loadSpriteFromGif(std::string gifFilePath, bool isGif)
{
    sprite = new Sprite(gifFilePath, isGif);
}

void CanvasWidget::createNewSprite(int width, int height)
{
    sprite = new Sprite(width, height);
}

int CanvasWidget::getCurrentFrame()
{
    return currentFrame;
}

void CanvasWidget::setCurrentFrame(int frame)
{
    currentFrame = frame;
    repaint();
}

void CanvasWidget::toggleOnionSkin()
{
    onionSkinEnabled = !onionSkinEnabled;
    repaint();
    std::cout << "Onion skin on: " << onionSkinEnabled << std::endl;
}
