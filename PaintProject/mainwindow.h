#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <QUndoGroup>
#include <QUndoStack>



#include "canvaswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void colorSelectGroup_clicked(QAbstractButton* button);     // color
    void on_penSizeSlide_sliderMoved(int position);             // slider
    void on_penSizeSlide_sliderReleased();
    void on_penSizeSlide_valueChanged(int value);
    void on_clearButton_clicked();                              // clear

    QUndoStack *undoStack;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
