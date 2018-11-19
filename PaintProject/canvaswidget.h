#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QUndoStack>
#include <QUndoView>
#include <QUndoGroup>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QStack>

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();
    static bool isSave;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    void setColor(QColor selectedColor);
    void setPenSize(int selectedSize);
    void clearAll();
    void setImage(QImage &qImage);


    QColor getColor();
    QImage getImage();
    QImage canvasImage;

    QStack <QImage> undoStack;
    QStack <QImage> redoStack;
    void addUndoStack();


private:
    //Canvas

    QPoint point;
    QColor penColor;
    int penSize;
    bool drawingActive;
    bool initFlag=false;


};

#endif // CANVASWIDGET_H
