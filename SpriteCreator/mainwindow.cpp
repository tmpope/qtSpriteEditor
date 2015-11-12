#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "sprite.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <iomanip>
#include <QTimer>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::string file = "";

<<<<<<< HEAD
    canvas = new CanvasWidget(this); // ~ACL: This is the line that solved our save problem. Why? I have no fetching clue.
    
    // each call to canvas->something needs to be either in the mainwindow.cpp or
    // those methods need to be in SLOT form.
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveSprite()));
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(loadSprite()));
    connect(ui->penButton, SIGNAL(clicked()), this, SLOT(setPen()));
    connect(ui->eyeDropperButton, SIGNAL(clicked()), this, SLOT(setEyeDropper()));
    connect(ui->actionExport, SIGNAL(triggered(bool)), this, SLOT(exportGif()));
    connect(ui->actionImport, SIGNAL(triggered(bool)), this, SLOT(importGif()));
    connect(ui->actionNewFrame, SIGNAL(triggered(bool)), this, SLOT(newFrame()));
    connect(ui->actionColorSelect, SIGNAL(toggled(bool)), this, SLOT(setColor()));
    connect(ui->actionNewSprite, SIGNAL(triggered(bool)), this, SLOT(newSprite()));
    connect(ui->cloneFrameButton, SIGNAL(clicked()), this, SLOT(cloneFrame()));
    connect(ui->onionSkinButton, SIGNAL(clicked()), this, SLOT(onionSkin()));
=======
    colorDialog = new QColorDialog();

    playbackTimer = new QTimer();
    playbackTimer->setInterval(1000 / ui->fpsSlider->value());
    playbackTimer->start();

    playbackFrame = 0;

    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(saveSprite()));
    connect(ui->actionLoad, SIGNAL(triggered(bool)), this, SLOT(loadSprite()));
//    connect(ui->penButton, SIGNAL(clicked(bool)), this, SLOT());
//    connect(ui->eyeDropperButton, SIGNAL(clicked(bool)), this, SLOT());
    connect(ui->fpsSlider, SIGNAL(sliderMoved(int)), this, SLOT(setFramesPerSecond()));
    connect(playbackTimer, SIGNAL(timeout()), this, SLOT(updatePlaybackWidget()));
    connect(ui->colorSelectorButton, SIGNAL(clicked(bool)), this, SLOT(showColorDialog()));
    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(colorDialogColorSelected()));
    connect(ui->penButton, SIGNAL(clicked(bool)), this, SLOT(ui->canvas->setCurrentTool(PENCIL);));
    connect(ui->eyeDropperButton, SIGNAL(clicked(bool)), this, SLOT(ui->canvas->setCurrentTool(EYE_DROPPER);));
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a
}

MainWindow::~MainWindow()
{
    delete ui;
    delete playbackTimer;
    delete colorDialog;
}

<<<<<<< HEAD
void MainWindow::newFrame()
{
    canvas->getSprite()->addFrame();
}

void MainWindow::setEyeDropper()
{
    canvas->setCurrentTool(EYE_DROPPER);
}

void MainWindow::setPen()
{
    canvas->setCurrentTool(PENCIL);
}

void MainWindow::cloneFrame()
{
    Sprite currentSprite = canvas->getSprite();
    currentSprite->addFrame();
    //backend needs functionality to add a sprite with a frame.

}

void MainWindow::onionSkin()
{

}

void MainWindow::newSprite()
{
    //getting the size of sprite could pose a problem here.
    canvas->sprite = new Sprite();
}

void MainWindow::exportGif()
{
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".ssp");
    QString QfileName = dialog.getSaveFileName(
                this, tr("Save Project"), "C://",
                "Sprite Sheet Project(*.ssp);;Text File(*.txt)");
    file = QfileName.toStdString().c_str();
    //canvas->getSprite()->exportToGif(file, ui->horizontalSlider->value());
}

void MainWindow::setColor()
{
    //how the crap do i get a color from the action color select?!?
    //canvas->setCurrentColor(ui->actionColorSelect->);
}

void MainWindow::importGif()
{
    QString QfileName = QFileDialog::getOpenFileName(
                this, tr("Open Project"), "C://",
                "(*.ssp *.txt)");
    file = QfileName.toStdString();

    std::string ext = "";
    if(file.find_last_of(".") !=  std::string::npos)
    {
        ext = file.substr(file.find_last_of(".") + 1);
    }
    if(ext == "gif")
    {
        //I'm pretty sure we need to call the sprite constructor for gifs here.
        //maybe we can overload loadSpriteFromString.
        //canvas->loadSpriteFromString(/*file name, gif extension*/);
    }
    else if(ext != "ssp" && ext != "txt")
    {
        QMessageBox::critical(this, tr("Gif Load Failed"), tr("Wrong Extension!"));
    }
    try
    {
        //I'm pretty sure we need to call the sprite constructor for gifs here.
        //maybe we can overload loadSpriteFromString.
       canvas->loadSpriteFromString(file);
    }
    catch(...)
    {
        QMessageBox::critical(this, tr("Gif Load Failed"), tr("Gif Load Failed!"));
    }
    QMessageBox::information(this, tr("Gif Load"), tr("Gif Loaded!"));
}

=======
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a
void MainWindow::saveSprite()
{
    QFileDialog dialog(this);
    dialog.setDefaultSuffix(".ssp");
<<<<<<< HEAD
    QString QfileName = dialog.getSaveFileName(
                this, tr("Save Project"), "C://",
                "Sprite Sheet Project(*.ssp);;Text File(*.txt)");

    QFile outputFile(QfileName);
    outputFile.open(QIODevice::WriteOnly);
    if(!outputFile.isOpen()){
        QMessageBox::critical(this, tr("File Save Failed"), tr("Failed to write to file."));
    }

    //this chuck saves the Sprite into a .ssp or .txt file.
    QTextStream outStream(&outputFile);
=======
    QString QfileName = dialog.getSaveFileName( this, tr("Save Project"), "C://", "Sprite Sheet Project(*.ssp);;Text File(*.txt)");

    ui->canvas->save(QfileName.toStdString());
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a

    //Sprite* sprite = canvas->getSprite(); // <---- This line right here. gave us so much trouble...
        std::string s = canvas->getSprite()->toString();
        outStream << s.c_str();
        outputFile.close();

<<<<<<< HEAD
        file = QfileName.toStdString();

        if(QfileName.isNull())
        {
            QMessageBox::critical(this, tr("File Save Failed"), tr("File is Null"));
        }
    QMessageBox::information(this, tr("File"), tr("File Saved!"));
=======
    if(QfileName.isNull())
    {
        QMessageBox::critical(this, tr("File Save Failed"), tr("File is Null"));
    }
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a
    std::cout << file << std::endl;
}

void MainWindow::loadSprite(){
<<<<<<< HEAD
    QString QfileName = QFileDialog::getOpenFileName(
                this, tr("Open Project"), "C://",
                "(*.ssp *.txt)");

    //std::cout << "File name: " << QfileName.toStdString() << std::endl;
    // this chunk of code gets our file, and makes sure it has the correct extension.
    QFile inputFile;
    inputFile(QfileName);
=======
    QString QfileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "C://", "Sprite Sheet Project(*.ssp);;Text Files(*.txt)");
    std::cout << "File name: " << QfileName.toStdString() << std::endl;
    QFile inputFile(QfileName);
>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a

    std::string file = QfileName.toStdString();
    std::string ext = "";
    if(file.find_last_of(".") !=  std::string::npos)
    {
        ext = file.substr(file.find_last_of(".") + 1);
    }
<<<<<<< HEAD
    if(ext != "ssp" && ext != "txt")
    {
        QMessageBox::critical(this, tr("File Load Failed"), tr("Wrong extension!"));
    }
    else
    {
        QMessageBox::information(this, tr("File Load"), tr("File Loaded!"));
        return;
    }

    // Here we read the file and put it into a std::string for the new sprite.
    // Here's where things get funky - I hope I'm doing this right.

    std::stringstream ss;

    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        ss << in.readAll().toStdString();
    }
    inputFile.close();

    std::cout << "Here's the file: " << ss.str() << std::endl;
    canvas->loadSpriteFromString(ss.str());
    //ui->canvas->loadSpriteFromString(ss.str());
}
=======

    else
    {
        QMessageBox::critical(this, tr("File Load Failed"), tr("An extension could not be found for the file!"));
        return;
    }

    FILE* f;
    f = fopen(file.c_str(),"r");
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    rewind(f);
    char* buffer = reinterpret_cast<char*>(malloc(sizeof(char)*filesize));
    fread(buffer, 1, filesize, f);
    std::string str(buffer);
    free(buffer);
    fclose(f);

    ui->canvas->loadSpriteFromString(str);
}


void MainWindow::updatePlaybackWidget()
{
    if(++playbackFrame >= ui->canvas->getSprite()->getFrameCount())
        playbackFrame = 0;

    Sprite* sprite = ui->canvas->getSprite();

    QPixmap pixmap(sprite->getWidth(), sprite->getHeight());
    pixmap.fill(QColor("transparent"));

    QPainter painter(&pixmap);

    for(int xPos = 0; xPos < sprite->getWidth(); xPos++)
    {
        for(int yPos = 0; yPos < sprite->getHeight(); yPos++)
        {
            QRect rect(xPos, yPos, 1, 1);
            struct Sprite::color pixelColor = sprite->getPixel(xPos, yPos, playbackFrame);
            QColor color(pixelColor.r, pixelColor.g, pixelColor.b);
            painter.setPen(color);
            painter.fillRect(rect, color);
        }
    }

    ui->playbackLabel->setPixmap(pixmap);
}

void MainWindow::setFramesPerSecond()
{
    if(ui->fpsSlider->value() == 0)
        playbackTimer->setInterval(0);
    else
        playbackTimer->setInterval(1000 / ui->fpsSlider->value());
    std::cout << "Set the fps: " << ui->fpsSlider->value() << std::endl;
}

void MainWindow::showColorDialog(){
    // Get a selected color from the user
    std::cout << "Showing color dialog." << std::endl;
    colorDialog->show();
}

void MainWindow::colorDialogColorSelected()
{
    colorDialog->hide();

    // Get the selected color
    QColor selectedColor = colorDialog->selectedColor();
    int *r = new int(0);
    int *g = new int(0);
    int *b = new int(0);
    int *a = new int(0);

    selectedColor.getRgb(r, g, b, a);

    ui->canvas->setCurrentColor(*r, *g, *b, *a);
}


















>>>>>>> 1241f70b068295bb8a2000290e52a341b0ad042a
