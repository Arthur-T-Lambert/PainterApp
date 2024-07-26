#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>

#include "board.h"
#include "dessin.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class UndoAddCommand;
class UndoRemoveCommand;
class UndoMoveCommand;
class UndoResizeCommand;
}
QT_END_NAMESPACE

/*
 * Each time a action is executed, it should add a corresponding command to a QUndoStack (stack->push(command);).
 * Then, it can be undone/redone by calling QUndoStack undo/redo slot (this does not trigger a redraw).
 */

class UndoAddCommand : public QUndoCommand
{
public:
    UndoAddCommand(QList<Dessin*> &drawing_list, Dessin* dessin);
    virtual ~UndoAddCommand();

    void undo() override;
    void redo() override;

private:
    QList<Dessin*> &_drawing_list;
    Dessin* _dessin;
};

class UndoRemoveCommand : public QUndoCommand
{
public:
    UndoRemoveCommand(QList<Dessin*> &drawing_list, Dessin* dessin);
    virtual ~UndoRemoveCommand();
    void undo() override;
    void redo() override;

private:
    QList<Dessin*> &_drawing_list;
    Dessin* _dessin;
};

class UndoMoveCommand : public QUndoCommand
{
public:
    UndoMoveCommand(Dessin* dessin, QPoint old_pos);
    virtual ~UndoMoveCommand();
    void undo() override;
    void redo() override;

private:
    Dessin* _dessin;
    QPoint _old_pos;
    QPoint _new_pos;
};

class UndoResizeCommand : public QUndoCommand
{
public:
    UndoResizeCommand(Dessin* dessin, float size_factor);
    virtual ~UndoResizeCommand();
    void undo() override;
    void redo() override;

private:
    Dessin* _dessin;
    float _size_factor;
};


#endif // UNDOCOMMAND_H
