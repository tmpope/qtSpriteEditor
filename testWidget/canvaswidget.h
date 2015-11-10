#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "sprite.h"

class CanvasWidget : public QWidget
{
public:
    /**
     * @brief The current_tool_t enum
     *
     * Represents what tool is currently being used on the CanvasWidget.
     */
    enum possible_tool_t { EYE_DROPPER, PENCIL, ERASER, BUCKET };

private:

    /* The width and height of the sprite */

    /* The last points that were used */
    int lastX, lastY;

    /* What the current tool that is being used is */
    possible_tool_t currentTool;
    possible_tool_t lastTool;

    /* The button that was clicked last. This helps us handle eraser stuff */
    Qt::MouseButton clickedButton;

    /* The current color that we are drawing with. */
    QColor currentColor;

    /* What the current sprite is - the model. */
    Sprite *sprite;

    /* The current frame of the sprite that we are drawing to. */
    int currentFrame;

public:
    Sprite* getSprite();
    /**
     * @brief CanvasWidget
     *
     * Creates a canvas widget. Requires a sprite width and height to start.
     */
    CanvasWidget(QWidget *);
    ~CanvasWidget();

    /**
     * @brief setCurrentTool
     *
     * Set the current tool. The list of tools is provided above as an enum.
     */
    void setCurrentTool(possible_tool_t);

    /**
     * @brief setCurrentColor
     *
     * Set the current drawing color of the canvas widget.
     *
     * @param r - red
     * @param g - green
     * @param b - blue
     * @param a - alpha
     */
    void setCurrentColor(int r, int g, int b, int a);

//    /**
//     * @brief getCurrentSprite
//     * @return Sprite
//     */
//    Sprite* getCurrentSprite();

//    /**
//     * @brief setCurrentSprite
//     *
//     * Set a new sprite to this one.
//     *
//     * @param otherSprite
//     */
//    void setCurrentSprite(Sprite *otherSprite);

protected:

    /**
     * Mouse Event handlers
     *
     * If a mouse button is pressed and it is NOT a left click or a right click,
     * these methods do nothing.
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    /**
     * I guess we need to override the paintEvent as well. This is what draws stuff
     * to the widget.
     */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    // TODO: Resize listener?

private:
    /**
     * @brief colorSelectedPixel
     *
     * Helper method that colors the selected pixel according to whatever tool is
     * currently selected. If the xPos or yPos does not exist in the sprite, this
     * method does nothing.
     *
     * @param xPos
     * @param yPos
     */
    void colorSelectedPixel(int xPos, int yPos);
};

#endif // CANVASWIDGET_H
