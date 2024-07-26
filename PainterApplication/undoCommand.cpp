#include "undoCommand.h"

UndoAddCommand::UndoAddCommand(QList<Dessin*> &drawing_list, Dessin* dessin) : _drawing_list(drawing_list), _dessin(dessin)
{
}

UndoAddCommand::~UndoAddCommand()
{
    // maybe do an undo
}

void UndoAddCommand::undo()
{
    _drawing_list.removeOne(_dessin);
}

void UndoAddCommand::redo()
{
    _drawing_list.append(_dessin);
}

//-----------------------------------------------------------------------------

UndoRemoveCommand::UndoRemoveCommand(QList<Dessin*> &drawing_list, Dessin* dessin) : _drawing_list(drawing_list), _dessin(dessin)
{
}

UndoRemoveCommand::~UndoRemoveCommand()
{
}

void UndoRemoveCommand::undo()
{
    _drawing_list.append(_dessin);
}
void UndoRemoveCommand::redo()
{
    _drawing_list.removeOne(_dessin);
}

//-----------------------------------------------------------------------------

UndoMoveCommand::UndoMoveCommand(Dessin* dessin, QPoint old_pos) : _dessin(dessin), _old_pos(old_pos), _new_pos(dessin->getPosition())
{
}

UndoMoveCommand::~UndoMoveCommand()
{
}

void UndoMoveCommand::undo()
{
    _dessin->SetPosition(_old_pos);
}

void UndoMoveCommand::redo()
{
    _dessin->SetPosition(_new_pos);
}

//-----------------------------------------------------------------------------

UndoResizeCommand::UndoResizeCommand(Dessin* dessin, float size_factor) : _dessin(dessin), _size_factor(size_factor)
{
}

UndoResizeCommand::~UndoResizeCommand()
{
}

void UndoResizeCommand::undo()
{
// apply 1/size_factor
}

void UndoResizeCommand::redo()
{
// apply size_factor
}
