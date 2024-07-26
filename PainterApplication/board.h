/*!\file board.h
 *
 * \brief Classe Board gérant le widget d'affichage des formes et dessins
 * \auteur : Nehari Mohamed
 */

#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPoint>
#include <QColor>
#include <QBrush>
#include <QList>
#include <QDropEvent>
#include <QUndoStack>

#include "ui_board.h"
#include "ui_board.h"
#include "Shapes.h"
#include "dessin.h"
#include "pen.h"
#include "undoCommand.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Board;
}
QT_END_NAMESPACE

enum class MODE{DESSIN_LIBRE, DRAG_AND_DROP, GOMME, SELECT, FORMES};
enum class FORME{ELLIPSE, RECTANGLE, STAR};

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void updateDimensionAndPosition(QPainter &painter);
    void drawGrid(QPainter &painter);
    void drawBackground(QPainter &painter, const Qt::BrushStyle brushStyle, const Qt::GlobalColor &brushColor);
    void setMode(MODE m);
    void setForme(FORME m);
    void showGrid(bool print);
    void setBrushStyle(const Qt::BrushStyle &brush);
    void setBrushColor(const QColor &color);
    MODE getMode();
    void refresh();
    void zoomPlus();
    void zoomMoins();
    Pen *pen;
    QBrush brush;

    void undo() { undo_stack->undo(); this->refresh(); }
    void redo() { undo_stack->redo(); this->refresh(); }

    void drawShape(const QPoint &start, const QPoint &end);
    void updateCursor();

    void addShape(Shapes *shape);

    enum Tool { None,Cursor, RectangleTool, EllipseTool, StarTool };
    Tool currentTool= None;

private:
    Shapes* createShape(const QPoint &start, const QPoint &end);

public slots:
    void setCurrentTool(Tool tool);

private:
    Ui::Board *ui;
    float zoomVal;
    QPoint lastMousePosition;
    QPointF translateWidget;
    // QList<QRectF> shapes; //Utilisation de QRectF car le déplacement des formes doit se faire en flottant et non en int
    int indexShapeSelected;

    QList<Dessin*> list_dessins;
    QUndoStack* undo_stack = nullptr;

    // QList<Shapes*> formes;
    Dessin *draggedShape;
    bool printGrid = true;

    void setupShapes();

    MODE mode;
    FORME forme;

    bool isDrawing =false;
};

#endif // BOARD_H
