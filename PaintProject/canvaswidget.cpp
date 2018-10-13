#include "canvaswidget.h"

bool CanvasWidget::isSave = true;

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{

    canvasImage = QImage(this->size(), QImage::Format_RGB32);
    //canvasImage.fill(Qt::green);
    //canvasImage.fill(Qt::white);
    drawingActive = false;
    penColor = Qt::black;
    penSize = 5;
    QPainter canvasPainter(this);


}

CanvasWidget::~CanvasWidget(){}

void CanvasWidget::setColor(QColor selectedColor) {
    penColor = selectedColor;
}

QColor CanvasWidget::getColor() {
    return penColor;
}

void CanvasWidget::setPenSize(int selectedSize) {
    penSize = selectedSize;
}

void CanvasWidget::clearAll()
{
    canvasImage = QImage(this->size(), QImage::Format_RGB32);
    canvasImage.fill(Qt::white);
    this->update();

    addUndoStack();

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
        CanvasWidget::isSave = false;
        point = event->pos();
        drawingActive = true;
        QPainter painter(&canvasImage);
        painter.setPen(QPen(penColor, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawPoint(point);
        this->update();
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawingActive)
    {
        QPainter painter(&canvasImage);
        painter.setPen(QPen(penColor, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(point, event->pos());
        point = event->pos();
        this->update();

    }
}



void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        addUndoStack();
        drawingActive = false;
    }
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    if(initFlag == false )
    {
        canvasImage = QImage(this->size(), QImage::Format_RGB32);
        canvasImage.fill(Qt::white);
        initFlag = true;
        undoStack.push( canvasImage  );
    }
}
void CanvasWidget::setImage(QImage &qImage)
{
    canvasImage = qImage;
    QPainter canvasPainter(this);
    this->update();
}

void CanvasWidget::addUndoStack()
{

    undoStack.push( getImage() );
    redoStack.clear();
    redoStack.push( getImage() );

}

QImage CanvasWidget::getImage()
{
    return canvasImage;
}

