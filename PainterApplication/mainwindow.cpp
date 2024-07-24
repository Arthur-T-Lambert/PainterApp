#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
//#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    draggedShape(nullptr){ // à deplacer sur class board
    ui->setupUi(this);
    setAcceptDrops(true);
    setupShapes();
    QGraphicsScene * scene(new QGraphicsScene(this));// use smart pointer
    ui->libraryView->setScene(scene);

    // Load icons from resources and create QGraphicsPixmapItem for each icon
    QPixmap pixmap1(":/images/ellipse.png");
    QPixmap pixmap2(":/images/rectangle.png");
    QPixmap pixmap3(":/images/quick.png");
    QPixmap pixmap4(":/images/star.png");

    QGraphicsPixmapItem *item1 = new QGraphicsPixmapItem(pixmap1);// use smart pointer
    QGraphicsPixmapItem *item2 = new QGraphicsPixmapItem(pixmap2);// use smart pointer
    QGraphicsPixmapItem *item3 = new QGraphicsPixmapItem(pixmap3);// use smart pointer
    QGraphicsPixmapItem *item4 = new QGraphicsPixmapItem(pixmap4);// use smart pointer

    // Optionally, set the position of each item
    item1->setPos(0, 0);    // Position of the first item (Ellipse)
    item2->setPos(80, 0);   // Position of the second item (Rectangle)
    item3->setPos(0, 80);  // Position of the third item (Quick)
    item4->setPos(80, 80);  // Position of the fourth item (Star)

    item1->setScale(0.15);
    item2->setScale(0.15);
    item3->setScale(0.15);
    item4->setScale(0.15);


    // Add the QGraphicsPixmapItem to the scene with different positions
    scene->addItem(item1);
    scene->addItem(item2);
    scene->addItem(item3);
    scene->addItem(item4);
}

MainWindow::~MainWindow() {
    delete ui;
    qDeleteAll(shapes);
}

void MainWindow::setupShapes() {
    QPen pen(Qt::black, 4, Qt::DotLine);
    QBrush ellipseBrush(Qt::gray);
    shapes.append(new Ellipse(QRect(450, 450, 100, 50)));
    shapes.last()->setProperties(pen, ellipseBrush);

    QBrush rectBrush(Qt::red);
    shapes.append(new Rectangle(QRect(600, 250, 150, 75)));
    shapes.last()->setProperties(pen, rectBrush);

    QBrush starBrush(Qt::magenta);
    shapes.append(new Star(QPoint(350, 150), 50));
    shapes.last()->setProperties(pen, starBrush);

    shapes.append(new ImageQuick(QRect(300, 300, 50, 50), ":/images/quick.png"));
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this); // to replace this
    for (Shapes *shape : shapes) {
        shape->draw(&painter);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    lastMousePosition = event->pos();
    for (Shapes *shape : shapes) {
        if (shape->contains(event->pos())) {
            draggedShape = shape;
            break;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (draggedShape) {
        QPoint delta = event->pos() - lastMousePosition;
        draggedShape->move(delta);
        lastMousePosition = event->pos();
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    draggedShape = nullptr;
}

// void MainWindow::dragEnterEvent(QDragEnterEvent *event)
// {
//     if (event->mimeData()->hasImage()) {
//         event->acceptProposedAction();
//     }
// }

// void MainWindow::dropEvent(QDropEvent *event)
// {
//     QGraphicsScene * scene(new QGraphicsScene(this));
//     QGraphicsView * view(new QGraphicsView(this));
//     if (event->mimeData()->hasImage()) {
//         QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
//         QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);

//        // Convertir les coordonnées du drop en coordonnées de la scène
//         QPoint viewPos = view->mapFrom(this, event->pos());
//         QPointF scenePos = view->mapToScene(viewPos);

//         item->setPos(scenePos);
//         item->setScale(0.15);  // Ajustez l'échelle si nécessaire
//         scene->addItem(item);
//         event->acceptProposedAction();
//     }
// }

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

