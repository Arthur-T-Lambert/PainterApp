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
    int  indexOfShapeSelected(const QPoint &pos);
    void updateDimensionAndPosition(QPainter &painter);
    void drawGrid(QPainter &painter);
    void setBrush(Qt::BrushStyle style, QColor color);
    void refresh();
    void zoomPlus();
    void zoomMoins();

private:
    Ui::Board *ui;
    float zoomVal;
    QPoint lastMousePosition;
    QPoint translateWidget;
    QBrush brush;
    QList<QRect> shapes;
    int indexShapeSelected;
};

#endif // BOARD_H
