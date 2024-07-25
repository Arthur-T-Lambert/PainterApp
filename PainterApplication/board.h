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
#include "ui_board.h"
//#include "draggablepixmapitem.h"

#include "Shapes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Board;
}
QT_END_NAMESPACE

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
    void refresh();
    void zoomPlus();
    void zoomMoins();

// protected:
        //void dragEnterEvent(QDragEnterEvent *event) override;
        //void dropEvent(QDropEvent *event) override;

private:
    Ui::Board *ui;
    float zoomVal;
    QPoint lastMousePosition;
    QPointF translateWidget;
    QList<QRectF> shapes; //Utilisation de QRectF car le déplacement des formes doit se faire en flottant et non en int
    int indexShapeSelected;



    QList<Shapes*> formes;
    Shapes *draggedShape;

    void setupShapes();
   // Shapes* createShapeFromType(DraggablePixmapItem::ShapeType type, const QPoint& pos, const QSize& size);
};

#endif // BOARD_H
