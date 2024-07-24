#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>

/*
 * Each time a action is executed, it should add a corresponding command to a QUndoStack (stack->push(command);).
 * Then, it can be undone/redone by calling QUndoStack undo/redo slot
 */

class UndoAddCommand : public QUndoCommand
{
public:
    UndoAddCommand();
    virtual ~UndoAddCommand();

    void undo() override;
    void redo() override;

private:
};

class UndoRemoveCommand : public QUndoCommand
{
public:
    UndoRemoveCommand();
    virtual ~UndoRemoveCommand();
    void undo() override;
    void redo() override;

};

class UndoMoveCommand : public QUndoCommand
{
public:
    UndoMoveCommand();
    virtual ~UndoMoveCommand();
    void undo() override;
    void redo() override;

};

class UndoResizeCommand : public QUndoCommand
{
public:
    UndoResizeCommand();
    virtual ~UndoResizeCommand();
    void undo() override;
    void redo() override;

};


#endif // UNDOCOMMAND_H
