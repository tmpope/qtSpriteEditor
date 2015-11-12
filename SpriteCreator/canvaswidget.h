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

    /* Indicates whether or not the onion skin is enabled */
    bool onionSkinEnabled;

public:
    /**
     * @brief getSprite
     *
     * Returns the sprite this canvas widget holds onto.
     *
     * @return pointer to the sprite that this canvas widget contains.
     */
    Sprite* getSprite();

    /**
     * @brief createNewSprite
     *
     * Loads up a sprite from an ssp string that has been pulled up from a file.
     *
     * @param sspString
     */
    void loadSpriteFromString(std::string sspString);

    /**
     * @brief loadSpriteFromGif
     *
     * Creates a new sprite from the gif passed.
     *
     * @param gifFilePath
     * @param isGif
     */
    void loadSpriteFromGif(std::string gifFilePath, bool isGif);

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

    /**
     * @brief save
     *
     * Saves the sprite using the save function in Sprite.cpp
     *
     * @param s The whole sprite as a string
     */
    void save(std::string s);

    /**
     * @brief createNewSprite
     *
     * Creates a sprite. Whooda thunk.
     */
    void createNewSprite(int, int);

    /**
     * @brief getCurrentFrame
     *
     * Returns the current frame that is being worked on.
     *
     * @return the current frame that is being shown.
     */
    int getCurrentFrame();

    /**
     * @brief setCurrentFrame
     *
     * Sets the current frame to be edited.
     */
    void setCurrentFrame(int);

    /**
     * @brief toggleOnionSkin
     *
     * Toggles onion skin on or off.
     */
    void toggleOnionSkin();

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

#endif
