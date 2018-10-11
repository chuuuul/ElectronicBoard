#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>


class UndoCommand : public QUndoCommand
{
public:
    UndoCommand(QImage qimage, QUndoCommand *parent = nullptr);

    //void undo() override;
    //void redo() override;

private:
    QImage *myQImage;

};

#endif // UNDOCOMMAND_H
