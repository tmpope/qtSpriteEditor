#include <QWidget>

#ifndef CANVASWIDGET
#define CANVASWIDGET
class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    CanvasWidget(QWidget* parent = 0);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:


};

#endif // CANVASWIDGET

