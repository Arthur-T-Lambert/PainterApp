#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>

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
 * /!\ Note that the redo() method is called when the QUndoAction is pushed in the QUndoStack /!\
 * Then, it can be undone/redone by calling QUndoStack undo/redo slot (this does not trigger a redraw).
 */

/**
 * \class UndoAddCommand
 * \brief QUndoCommand for undoing Dessin being added to the board.
 *
 * /!\ Note that the redo() method is called when the QUndoAction is pushed in the QUndoStack /!\
 */
class UndoAddCommand : public QUndoCommand
{
public:
    /**
     * \brief UndoAddCommand constructor.
     * \param drawing_list The list of dessins from wich dessin has been added to.
     * \param dessin A pointer to the dessin that has been moved.
     */
    UndoAddCommand(QList<Dessin*> &drawing_list, Dessin* dessin);
    virtual ~UndoAddCommand();
    /**
     * \brief undo method.
     */
    void undo() override;
    /**
     * \brief redo method.
     */
    void redo() override;

private:
    QList<Dessin*> &_drawing_list;  /*!< Reference to the list of dessins displayed in board*/
    Dessin* _dessin;                /*!< Pointer to the dessin*/
};

/**
 * \class UndoRemoveCommand
 * \brief QUndoCommand for undoing Dessin being removed from the board.
 *
 * /!\ Note that the redo() method is called when the QUndoAction is pushed in the QUndoStack /!\
 */
class UndoRemoveCommand : public QUndoCommand
{
public:
    /**
     * \brief UndoRemoveCommand constructor.
     * \param drawing_list The list of dessins from wich dessin has been removed from.
     * \param dessin A pointer to the dessin that has been moved.
     */
    UndoRemoveCommand(QList<Dessin*> &drawing_list, Dessin* dessin);
    virtual ~UndoRemoveCommand();
    /**
     * \brief undo method.
     */
    void undo() override;
    /**
     * \brief redo method.
     */
    void redo() override;

private:
    QList<Dessin*> &_drawing_list;  /*!< Reference to the list of dessins displayed in board*/
    Dessin* _dessin;                /*!< Pointer to the dessin*/
};

/**
 * \class UndoMoveCommand
 * \brief QUndoCommand for undoing Dessin being moved on the board.
 *
 * /!\ Note that the redo() method is called when the QUndoAction is pushed in the QUndoStack /!\
 */
class UndoMoveCommand : public QUndoCommand
{
public:
    /**
     * \brief UndoMoveCommand constructor.
     * \param dessin A pointer to the dessin that has been moved.
     * \param old_pos The old position of the dessin.
     */
    UndoMoveCommand(Dessin* dessin, QPoint old_pos);
    virtual ~UndoMoveCommand();
    /**
     * \brief undo method.
     */
    void undo() override;
    /**
     * \brief redo method.
     */
    void redo() override;

private:
    Dessin* _dessin;    /*!< Pointer to the dessin*/
    QPoint _old_pos;    /*!< Liste des morceaux*/
    QPoint _new_pos;    /*!< Liste des morceaux*/
};

/**
 * \class UndoResizeCommand
 * \brief QUndoCommand for undoing Dessin being resized.
 *
 * /!\ Note that the redo() method is called when the QUndoAction is pushed in the QUndoStack /!\
 */
class UndoResizeCommand : public QUndoCommand
{
public:
    /**
     * \brief UndoResizeCommand constructor.
     * \param dessin A pointer to the dessin that has been resized.
     * \param size_factor The multiplicative factor for the resize.
     */
    UndoResizeCommand(Dessin* dessin, float size_factor);

    virtual ~UndoResizeCommand();
    /**
     * \brief undo method.
     */
    void undo() override;
    /**
     * \brief redo method.
     */
    void redo() override;

private:
    Dessin* _dessin;    /*!< Pointer to the dessin*/
    float _size_factor; /*!< The size factor by wich the old size has been multiply to get the current size*/
};


#endif // UNDOCOMMAND_H
