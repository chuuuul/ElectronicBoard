#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    void setColor(QColor selectedColor);
    void setPenSize(int selectedSize);
    void clearAll();

    QImage getImage();

private:
    //Canvas
    QImage canvasImage;
    QPoint point;
    QColor penColor;
    int penSize;
    bool drawingActive;
    bool initFlag=false;

};

#endif // CANVASWIDGET_H
