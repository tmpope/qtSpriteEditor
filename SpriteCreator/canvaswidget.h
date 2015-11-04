#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>

class CanvasWidget : public QWidget
{
    /* The width and height of the sprite */
    int spriteWidth;
    int spriteHeight;

    /* The last points that were used */
    int lastX, lastY;


public:
    /**
     * @brief CanvasWidget
     *
     * Creates a canvas widget. Requires a sprite width and height to start.
     */
    CanvasWidget(QWidget *);
    ~CanvasWidget();

    /**
     * @brief setSpriteDimensions
     *
     * Sets the sprite dimensions. Must be a width and height greater than 1!
     *
     * @param width of the sprite
     * @param height of the sprite
     */
    void setSpriteDimensions(int, int);




protected:

    /**
     * Mouse Event handlers
     *
     * This is basically how we figure out where we need to draw what.
     */
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;


    /**
     * I guess we need to override the paintEvent as well. This is what draws stuff
     * to the widget.
     */
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    // TODO: Resize listener?
};

#endif // CANVASWIDGET_H
