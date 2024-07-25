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

    enum Tool { None,Cursor, RectangleTool, EllipseTool, StarTool };



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

    void drawShape(const QPoint &start, const QPoint &end);// pas sure
    Shapes* createShape(const QPoint &start, const QPoint &end);
    //void drawStar(QPainter &painter, const QRect &rect);//pas sure

    Tool currentTool= None;//private
    void updateCursor();
public slots:
    void setCurrentTool(Tool tool);
    // void setPenColor(const QColor &color);//pas sure
    // void setPenWidth(int width);//pas sure


// protected:
        //void dragEnterEvent(QDragEnterEvent *event) override;
        //void dropEvent(QDropEvent *event) override;
public:
      void addShape(Shapes *shape);
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
    bool isDrawing =false;
};

#endif // BOARD_H
