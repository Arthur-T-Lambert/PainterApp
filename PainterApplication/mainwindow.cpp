#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    draggedShape(nullptr) {
    ui->setupUi(this);
    setupShapes();
}

MainWindow::~MainWindow() {
    delete ui;
    qDeleteAll(shapes);
}

void MainWindow::setupShapes() {
    QPen pen(Qt::black, 4, Qt::DotLine);
    QBrush ellipseBrush(Qt::gray);
    shapes.append(new Ellipse(QRect(150, 150, 100, 50)));
    shapes.last()->setProperties(pen, ellipseBrush);

    QBrush rectBrush(Qt::red);
    shapes.append(new Rectangle(QRect(100, 250, 150, 75)));
    shapes.last()->setProperties(pen, rectBrush);

    QBrush starBrush(Qt::magenta);
    shapes.append(new Star(QPoint(350, 150), 50));
    shapes.last()->setProperties(pen, starBrush);

    shapes.append(new ImageQuick(QRect(50, 50, 100, 100), ":/images/quick.png"));
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
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

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

