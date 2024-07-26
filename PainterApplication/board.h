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
//#include <QDropEvent>
#include "ui_board.h"
#include "Shapes.h"
#include "pen.h"

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
    /**
     * @brief Paint event handler for the Board class.
     * @param event Pointer to the QPaintEvent object.
     */
    void paintEvent(QPaintEvent *event) override;
    /**
     * @brief Handles the mouse press event.
     * @param event Pointer to the QMouseEvent object.
     */
    void mousePressEvent(QMouseEvent *event) override;
    /**
     * @brief Handles the mouse move event.
     * @param event Pointer to the QMouseEvent object.
     */
    void mouseMoveEvent(QMouseEvent *event) override;
    /**
     * @brief Handles the mouse release event.
     * @param event Pointer to the QMouseEvent object.
     */
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

    /**
     * @brief Draws a shape between the start and end points.
     * @param start The starting point of the shape.
     * @param end The ending point of the shape.
     */
    void drawShape(const QPoint &start, const QPoint &end);
    /**
     * @brief Creates a shape between the start and end points.
     * @param start The starting point of the shape.
     * @param end The ending point of the shape.
     * @return A pointer to the created shape.
     */
    Shapes* createShape(const QPoint &start, const QPoint &end);
    /**
     * @brief Updates the cursor based on the current tool.
     */
    void updateCursor();


    Pen *pen;
    QBrush brush;
    /**
     * @brief Enum representing the available drawing tools.
     */
    enum Tool {
        None, ///< No tool selected.
        Cursor, ///< Cursor tool for selecting and moving shapes.
        RectangleTool, ///< Tool for drawing rectangles.
        EllipseTool, ///< Tool for drawing ellipses.
        StarTool ///< Tool for drawing stars.
    };
    /**
     * @brief The current tool being used.
     */
    Tool currentTool= None;


public slots:
    /**
     * @brief Sets the current tool.
     * @param tool The tool to set as the current tool.
     */
    void setCurrentTool(Tool tool);

public:
    /**
     * @brief Adds a shape to the shapes list.
     * @param shape A pointer to the shape to be added.
     */
      void addShape(Shapes *shape);

private:
    Ui::Board *ui;
    float zoomVal;
    QPoint lastMousePosition;
    QPointF translateWidget;
    QList<Shapes*> formes;
    Shapes *draggedShape;
    bool printGrid = true;


    MODE mode;
    FORME forme;

    /**
     * @brief The flag to indicate whether a drawing operation is in progress.
     */

    bool isDrawing =false;
};

#endif // BOARD_H
