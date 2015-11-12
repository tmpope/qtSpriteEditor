#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"
#include <QtGui>
<<<<<<< HEAD
=======
#include <QColorDialog>
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a

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
    void saveSprite();
    void loadSprite();
<<<<<<< HEAD
    void exportGif();
    void importGif();
    void setColor();
    void newSprite();
    void onionSkin();
    void cloneFrame();
    void setPen();
    void setEyeDropper();
    void newFrame();

=======
    void updatePlaybackWidget();
    void setFramesPerSecond();
    void showColorDialog();
    void colorDialogColorSelected();
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a

private:
    Ui::MainWindow *ui;
    std::string file;
};

#endif // MAINWINDOW_H
