#ifndef DRAGGABLEPIXMAPITEM_H
#define DRAGGABLEPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

class DraggablePixmapItem : public QGraphicsPixmapItem
{
public:
    DraggablePixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
        : QGraphicsPixmapItem(pixmap, parent)
    {
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
        setAcceptedMouseButtons(Qt::LeftButton);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            dragStartPosition = event->pos();
        }
        QGraphicsPixmapItem::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (!(event->buttons() & Qt::LeftButton)) {
            return;
        }
        if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
            return;
        }

        // Utiliser nullptr ou QApplication::widgetAt()
        QDrag *drag = new QDrag(nullptr);
        // Ou
        // QDrag *drag = new QDrag(QApplication::widgetAt(QCursor::pos()));

        QMimeData *mime = new QMimeData;
        drag->setMimeData(mime);

        mime->setImageData(pixmap());

        QPixmap dragPixmap = pixmap().scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        drag->setPixmap(dragPixmap);
        drag->setHotSpot(QPoint(dragPixmap.width()/2, dragPixmap.height()/2));

        drag->exec();
    }

private:
    QPointF dragStartPosition;
};

#endif // DRAGGABLEPIXMAPITEM_H
