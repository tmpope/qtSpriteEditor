#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"
#include <QtGui>

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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveSprite();
    void loadSprite();
    void updatePlaybackWidget();
    void setFramesPerSecond();

private:
    Ui::MainWindow *ui;
    std::string file;
};

#endif // MAINWINDOW_H
