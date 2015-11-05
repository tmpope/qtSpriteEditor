#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"

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
    std::string Save(Sprite sprite);
    Sprite Load(std::string file);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
