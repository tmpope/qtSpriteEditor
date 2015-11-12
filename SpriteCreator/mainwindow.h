#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"
#include <QtGui>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    /**
     * @brief canvas
     *
     * What actually draws the thing.
     */
    CanvasWidget *canvas;


    /**
     * @brief playbackTimer
     *
     * Timer that changes what sprite image is being shown.
     */
    QTimer *playbackTimer;

    /**
     * @brief playbackFrame
     *
     * Keeps track of what frame we need to draw.
     */
    int playbackFrame;

    /**
     * @brief colorDialog
     *
     * Little menu that shows the color dialog window.
     */
    QColorDialog *colorDialog;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief saveSprite
     *
     * Saves a sprite
     */
    void saveSprite();

    /**
     * @brief loadSprite
     *
     * Loads a sprite.
     */
    void loadSprite();

    /**
     * @brief updatePlaybackWidget
     *
     * Updates the playback widget.
     */
    void updatePlaybackWidget();

    /**
     * @brief setFramesPerSecond
     *
     * Sets the FPS for the playback.
     */
    void setFramesPerSecond();

    /**
     * @brief showColorDialog
     *
     * Shows the color dialog screen.
     */
    void showColorDialog();

    /**
     * @brief colorDialogColorSelected
     *
     * Runs when a color is selected.
     */
    void colorDialogColorSelected();


    /**
     * @brief penToolSelected
     *
     * Selects the pen tool when the button is pressed.
     */
    void penToolSelected();


    /**
     * @brief eyeDropperSelected
     *
     * Sets the eye dropper tool when the button is pressed.
     */
    void eyeDropperSelected();

    /**
     * @brief paintBucketSelected
     *
     * Sets the paint bucket tool when the button is pressed.
     */
    void paintBucketSelected();

    /**
     * @brief exportGif
     *
     * Exports current sprite as a .gif file.
     */
    void exportGif();


    /**
     * @brief importGif
     *
     * Imports a .gif file as a sprite.
     */
    void importGif();


    /**
     * @brief newFrame
     *
     * Adds a new frame to the current sprite.
     */
    void newFrame();

    /**
     * @brief deleteFrame
     *
     * Deletes a frame from the current sprite.
     */
    void deleteFrame();

    /**
     * @brief newSprite
     *
     * Creates a new sprite.
     */
    void newSprite();


    /**
     * @brief cloneFrame
     *
     * Clones the current frame onto all other frames.
     */
    void cloneFrame();

    /**
     * @brief toggleOnionSkin
     *
     * Toggles onion skin on and off.
     */
    void toggleOnionSkin();

    /**
     * @brief showSelectedFrame
     *
     * Shows the frame that is selected.
     */
    void showSelectedFrame();

    /**
     * @brief undo
     *
     * Undoes previous action.
     */
    void undo();

    /**
     * @brief redo
     *
     * Redoes previous action.
     */
    void redo();

    /**
     * @brief previousFrame
     *
     * Shows the previous frame.
     */
    void previousFrame();

    /**
     * @brief nextFrame
     *
     * Shows the next frame.
     */
    void nextFrame();

private:
    Ui::MainWindow *ui;
    std::string file;
};

#endif // MAINWINDOW_H
