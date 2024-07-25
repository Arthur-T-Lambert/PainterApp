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
#include "ui_board.h"
#include "pen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Board;
}
QT_END_NAMESPACE

enum class MODE{DESSIN_LIBRE, DRAG_AND_DROP, EFFACER, SELECT, FORMES};

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
    MODE getMode();
    void refresh();
    void zoomPlus();
    void zoomMoins();
    Pen *pen;

private:
    Ui::Board *ui;
    float zoomVal;
    QPoint lastMousePosition;
    QPointF translateWidget;
    QList<QRectF> shapes; //Utilisation de QRectF car le déplacement des formes doit se faire en flottant et non en int
    int indexShapeSelected;
    MODE mode;
};

#endif // BOARD_H
