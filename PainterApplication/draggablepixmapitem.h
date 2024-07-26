// #ifndef DRAGGABLEPIXMAPITEM_H
// #define DRAGGABLEPIXMAPITEM_H

// #include <QGraphicsPixmapItem>
// #include <QGraphicsSceneDragDropEvent>
// #include <QDrag>
// #include <QMimeData>

// class DraggablePixmapItem : public QGraphicsPixmapItem
// {
// public:
//     enum ShapeType { Ellipse, Rectangle, Star, Quick };
//     DraggablePixmapItem(const QPixmap &pixmap, ShapeType type, QGraphicsItem *parent = nullptr);

// protected:
//     void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//     void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
//     void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

// private:
//     ShapeType m_shapeType;
//     QPointF m_dragStartPosition;
//     bool m_isDragging;

// };

// #endif // DRAGGABLEPIXMAPITEM_H
