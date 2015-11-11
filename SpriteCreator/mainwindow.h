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

    CanvasWidget *canvas;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void saveSprite();
    void loadSprite();

private:
    Ui::MainWindow *ui;
    std::string file;
};

#endif // MAINWINDOW_H
