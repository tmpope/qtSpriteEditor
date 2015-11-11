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
    void saveSprite();
    void loadSprite();
    void updatePlaybackWidget();
    void setFramesPerSecond();
    void showColorDialog();
    void colorDialogColorSelected();

private:
    Ui::MainWindow *ui;
    std::string file;
};

#endif // MAINWINDOW_H
