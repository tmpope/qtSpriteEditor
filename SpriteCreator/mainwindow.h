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

public slots:
    /**
     * Saves a Sprite to either a .ssp or .txt file
     * @return the string it will use to save the Sprite
     */
    std::string Save();
    /**
     * Loads a Sprite either from a .ssp or a .txt file
     * @return the Sprite that is loaded
     */
    Sprite* Load();

private:
    Ui::MainWindow *ui;
    std::string file;
};

#endif // MAINWINDOW_H
