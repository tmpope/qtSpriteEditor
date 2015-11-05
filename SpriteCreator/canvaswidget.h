#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>

class CanvasWidget : public QWidget
{
public:
    /**
     * @brief The current_tool_t enum
     *
     * Represents what tool is currently being used on the CanvasWidget.
     */
    enum possible_tool_t { EYE_DROPPER, PENCIL, ERASER };

private:

    /* The width and height of the sprite */
    int spriteWidth;
    int spriteHeight;

    /* The last points that were used */
    int lastX, lastY;

    /* What the current tool that is being used is */
    possible_tool_t currentTool;
    possible_tool_t lastTool;

    /* The button that was clicked last. This helps us handle eraser stuff */
    Qt::MouseButton clickedButton;

    /* The current color that we are drawing with. */
    QColor currentColor;

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
};

#endif // CANVASWIDGET_H
