#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{

    canvasImage = QImage( this->size() , QImage::Format_RGB32);
    //canvasImage.fill(QColor(255,255,0));
    //canvasImage.fill(Qt::blue);
    canvasImage.fill(Qt::white);
    drawingActive = false;
    penColor = Qt::black;
    penSize = 5;
}

CanvasWidget::~CanvasWidget()
{
}

void CanvasWidget::setColor(QColor selectedColor) {
    penColor = selectedColor;
}

void CanvasWidget::setBrushSize(int selectedSize) {
    penSize = selectedSize;
}

void CanvasWidget::clearAll()
{
    canvasImage = QImage(this->size(), QImage::Format_RGB32);
    canvasImage.fill(Qt::white);
    this->update();
}


void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), canvasImage, canvasImage.rect());

}


void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        point = event->pos();
        drawingActive = true;
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawingActive)
    {
        QPainter painter(&canvasImage);
        painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(point, event->pos());
        point = event->pos();
        this->update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        drawingActive = false;
    }
}
QImage CanvasWidget::getImage()
{
    return canvasImage;
}
