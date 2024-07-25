// // #include "draggablepixmapitem.h"
// // #include <QGraphicsSceneMouseEvent>
// // #include <QApplication>
// // #include <QDrag>
// // #include <QMimeData>
// // #include <QPainter>
// // #include <QIODevice>

// // DraggablePixmapItem::DraggablePixmapItem(const QPixmap &pixmap, ShapeType type, QGraphicsItem *parent)
// //     : QGraphicsPixmapItem(pixmap, parent), m_shapeType(type), m_isDragging(false)
// // {
// //     setFlag(QGraphicsItem::ItemIsMovable);
// //     setFlag(QGraphicsItem::ItemSendsGeometryChanges);
// //     setAcceptedMouseButtons(Qt::LeftButton);
// // }

// // void DraggablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
// // {
// //     if (event->button() == Qt::LeftButton) {
// //         m_dragStartPosition = event->pos();
// //     }
// //     QGraphicsPixmapItem::mousePressEvent(event);
// // }

// // void DraggablePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
// // {
// //     if (!(event->buttons() & Qt::LeftButton)) {
// //         return;
// //     }
// //     if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
// //         return;
// //     }

// //     m_isDragging = true;

// //     // Utiliser nullptr comme parent pour QDrag
// //     QDrag *drag = new QDrag(nullptr);
// //     QMimeData *mime = new QMimeData;
// //     mime->setImageData(pixmap().toImage());
// //     drag->setMimeData(mime);

// //     // Add custom MIME data for shape type
// //     QByteArray itemData;
// //     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
// //     dataStream << static_cast<int>(m_shapeType);
// //     mime->setData("application/x-shape", itemData);

// //     drag->setMimeData(mime);
// //     // ...
// //     QPixmap dragPixmap = pixmap().scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
// //     drag->setPixmap(dragPixmap);
// //     drag->setHotSpot(QPoint(dragPixmap.width()/2, dragPixmap.height()/2));

// //     drag->exec();

// //     m_isDragging = false;



// // }

// // void DraggablePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
// // {
// //     if (!m_isDragging) {
// //         QGraphicsPixmapItem::mouseReleaseEvent(event);
// //     }
// // }


// #include "draggablepixmapitem.h"
// #include <QGraphicsSceneMouseEvent>
// #include <QApplication>
// #include <QDrag>
// #include <QMimeData>
// #include <QIODevice>

// DraggablePixmapItem::DraggablePixmapItem(const QPixmap &pixmap, ShapeType type, QGraphicsItem *parent)
//     : QGraphicsPixmapItem(pixmap, parent), m_shapeType(type), m_isDragging(false) {
//     setFlag(QGraphicsItem::ItemIsMovable);
//     setFlag(QGraphicsItem::ItemSendsGeometryChanges);
//     setAcceptedMouseButtons(Qt::LeftButton);
// }

// void DraggablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
//     if (event->button() == Qt::LeftButton) {
//         m_dragStartPosition = event->pos();
//     }
//     QGraphicsPixmapItem::mousePressEvent(event);
// }

// void DraggablePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//     if (!(event->buttons() & Qt::LeftButton)) {
//         return;
//     }
//     if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
//         return;
//     }

//     m_isDragging = true;

//     QDrag *drag = new QDrag(nullptr);
//     QMimeData *mime = new QMimeData;
//     mime->setImageData(pixmap().toImage());

//     QByteArray itemData;
//     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//     dataStream << static_cast<int>(m_shapeType);
//     mime->setData("application/x-shape", itemData);

//     drag->setMimeData(mime);
//     QPixmap dragPixmap = pixmap().scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//     drag->setPixmap(dragPixmap);
//     drag->setHotSpot(QPoint(dragPixmap.width()/2, dragPixmap.height()/2));

//     drag->exec();

//     m_isDragging = false;
// }

// void DraggablePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
//     if (!m_isDragging) {
//         QGraphicsPixmapItem::mouseReleaseEvent(event);
//     }
// }
