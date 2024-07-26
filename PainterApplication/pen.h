/*!\file board.h
 *
 * \brief Classe Pen gérant le widget de dessin libre
 */

#ifndef PEN_H
#define PEN_H

#include <QWidget>
#include <QPen>
#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QList>
#include <QPainter>
#include <QPoint>
#include <QStack>

#include "dessin.h"

// Structure permettant d'enregistrer les informations de chaques points dessinés
struct DrawPoint {
    QList<QPoint> tabPoints;
    QPen pen;
};


class Pen : public QWidget, public Dessin
{
    Q_OBJECT

public:

    QPen pen;

    Pen(QWidget *parent = nullptr);
    Pen(Qt::PenStyle style, QColor color, int width);

    void setStyle(const Qt::PenStyle &style);
    void setColor(const QColor &color);
    void setWidth(int width);
    bool isDrawing();
    QColor getColor();
    void draw(QPainter *painter) override;
    void setDrawingMode(bool val);
    void setEraseMode(bool val);

    void move(const QPoint &delta) override { Q_UNUSED(delta); }
    bool contains(const QPoint &point) override { Q_UNUSED(point); return false; }

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void undo();
    void redo();

    void save(QDataStream& ) override;

private:
    QList<QPoint> currentPoints;  // Points du chemin en cours
    QList<DrawPoint> listPoints;  // Liste de tous les chemins dessinés
    bool _bdraw = false;
    bool erase = false;
    QPoint cursorPos;
    QColor color;
    bool clickLeft = false;
};

#endif // PEN_H
