#include "undocommand.h"
#include <QtWidgets>


UndoCommand::UndoCommand(QImage qImage,QUndoCommand *parent) : QUndoCommand (parent)
{
    QImage myQImage = qImage;

}

/*
void UndoCommand::undo()
{
    myQImage-> addItem
    myGraphicsScene->update();
}

void UndoCommand::redo()
{
    myGraphicsScene->addItem(myDiagramItem);
    myDiagramItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}
*/
