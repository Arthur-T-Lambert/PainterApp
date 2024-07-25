#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
<<<<<<< HEAD
// #include <QGraphicsPixmapItem>
#include <QPixmap>
// #include <QGraphicsScene>
// #include "draggablepixmapitem.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QDrag>
=======
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QColorDialog>
//#include <QMimeData>
>>>>>>> penClass

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    board = new Board(this);
    ui->widget->setLayout(new QVBoxLayout);
    ui->widget->layout()->addWidget(board);

    setAcceptDrops(true);
<<<<<<< HEAD
    ui->Ellipse->setAcceptDrops(true);
    ui->Rectangle->setAcceptDrops(true);

    QPixmap ellipsePixmap(":/images/ellipse.png");
    QPixmap scaledEllipsePixmap = ellipsePixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Ellipse->setPixmap(scaledEllipsePixmap);
    ui->Ellipse->setFixedSize(100, 50) ;
    ui->Ellipse->move(10, 10);
    ui->Ellipse->show();
    ui->Ellipse->setAttribute(Qt::WA_DeleteOnClose);

    QPixmap rectanglePixmap(":/images/rectangle.png");
    QPixmap scaledRectanglePixmap = rectanglePixmap.scaled(50, 50);
    ui->Rectangle->setPixmap(scaledRectanglePixmap);
    ui->Rectangle->setFixedSize(100, 50) ;
    // ui->Rectangle->move(10, 10);
    ui->Rectangle->show();
   // ui->Rectangle->setAttribute(Qt::WA_DeleteOnClose);


=======

    QGraphicsScene * scene(new QGraphicsScene(this));// use smart pointer
    ui->libraryView->setScene(scene);

    //_currentPen.setColor(Qt::black);
    //_currentPen.setWidth(2);
    //_currentPen.setStyle(Qt::SolidLine);
    ui->penColorPB->setStyleSheet(QString("background-color : %1").arg(board->pen->getColor().name()));

    _currentBrush.setColor(Qt::black);
    _currentBrush.setStyle(Qt::SolidPattern);
    ui->fillColorPB->setStyleSheet(QString("background-color : %1").arg(_currentBrush.color().name()));

    ui->penDirectColor1->setFixedSize(QSize(24, 24));
    ui->penDirectColor2->setFixedSize(QSize(24, 24));
    ui->penDirectColor3->setFixedSize(QSize(24, 24));
    ui->penDirectColor4->setFixedSize(QSize(24, 24));
    ui->penDirectColor5->setFixedSize(QSize(24, 24));
    ui->penDirectColor6->setFixedSize(QSize(24, 24));
    ui->penDirectColor7->setFixedSize(QSize(24, 24));
    ui->penDirectColor8->setFixedSize(QSize(24, 24));
    ui->penDirectColor9->setFixedSize(QSize(24, 24));
    ui->penDirectColor10->setFixedSize(QSize(24, 24));
    ui->penDirectColor11->setFixedSize(QSize(24, 24));
    ui->penDirectColor12->setFixedSize(QSize(24, 24));
    ui->penDirectColor13->setFixedSize(QSize(24, 24));
    ui->penDirectColor14->setFixedSize(QSize(24, 24));
    /* First row */
    ui->penDirectColor1->setStyleSheet(QString("background-color : %1").arg("#ffffff"));
    connect(ui->penDirectColor1, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#ffffff"));});
    ui->penDirectColor2->setStyleSheet(QString("background-color : %1").arg("#ffff00"));
    connect(ui->penDirectColor2, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#ffff00"));});
    ui->penDirectColor3->setStyleSheet(QString("background-color : %1").arg("#00ff00"));
    connect(ui->penDirectColor3, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#00ff00"));});
    ui->penDirectColor4->setStyleSheet(QString("background-color : %1").arg("#00ffff"));
    connect(ui->penDirectColor4, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#00ffff"));});
    ui->penDirectColor5->setStyleSheet(QString("background-color : %1").arg("#0000ff"));
    connect(ui->penDirectColor5, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#0000ff"));});
    ui->penDirectColor6->setStyleSheet(QString("background-color : %1").arg("#ff00ff"));
    connect(ui->penDirectColor6, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#ff00ff"));});
    ui->penDirectColor7->setStyleSheet(QString("background-color : %1").arg("#ff0000"));
    connect(ui->penDirectColor7, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#ff0000"));});
    /* Secoond row */
    ui->penDirectColor8->setStyleSheet(QString("background-color : %1").arg("#000000"));
    connect(ui->penDirectColor8, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#000000"));});
    ui->penDirectColor9->setStyleSheet(QString("background-color : %1").arg("#c0c000"));
    connect(ui->penDirectColor9, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#c0c000"));});
    ui->penDirectColor10->setStyleSheet(QString("background-color : %1").arg("#00c000"));
    connect(ui->penDirectColor10, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#00c000"));});
    ui->penDirectColor11->setStyleSheet(QString("background-color : %1").arg("#00c0c0"));
    connect(ui->penDirectColor11, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#00c0c0"));});
    ui->penDirectColor12->setStyleSheet(QString("background-color : %1").arg("#0000c0"));
    connect(ui->penDirectColor12, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#0000c0"));});
    ui->penDirectColor13->setStyleSheet(QString("background-color : %1").arg("#c000c0"));
    connect(ui->penDirectColor13, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#c000c0"));});
    ui->penDirectColor14->setStyleSheet(QString("background-color : %1").arg("#c00000"));
    connect(ui->penDirectColor14, &QPushButton::clicked, this, [=](){ this->on_directColor_clicked(QColor("#c00000"));});

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

    scene->addItem(item1);
    scene->addItem(item2);
    scene->addItem(item3);
    scene->addItem(item4);
>>>>>>> penClass

    //Paramétrage de la ScrollArea
    ui->scrollArea->setWidget(board);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}


MainWindow::~MainWindow() {
    delete ui;
}


<<<<<<< HEAD
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->position().toPoint() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::CopyAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child)
        return;

    QPixmap pixmap = child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(/*event->position().toPoint() - */child->pos());


    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

=======
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
>>>>>>> penClass

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
<<<<<<< HEAD
=======

void MainWindow::on_penColorPB_clicked()
{
    QColor color = QColorDialog::getColor(_currentPen.color(), this);

    if ( color.isValid() ) {
        //_currentPen.setColor(color);
        board->pen->setColor(color);
        ui->penColorPB->setStyleSheet(QString("background-color : %1").arg(color.name()));
    }
}

void MainWindow::on_penWidthSB_valueChanged(int value)
{
    //_currentPen.setWidth(value);
    board->pen->setWidth(value);
}

void MainWindow::on_penStyleCB_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        //_currentPen.setStyle(Qt::SolidLine);
        board->pen->setStyle(Qt::SolidLine);
        break;
    case 1:
        //_currentPen.setStyle(Qt::DashLine);
        board->pen->setStyle(Qt::DashLine);
        break;
    case 2:
        //_currentPen.setStyle(Qt::DotLine);
        board->pen->setStyle(Qt::DotLine);
        break;
    case 3:
        //_currentPen.setStyle(Qt::DashDotLine);
        board->pen->setStyle(Qt::DashDotLine);
        break;
    default:
        break;
    }
}

void MainWindow::on_directColor_clicked(const QColor& color)
{
    //_currentPen.setColor(color);
    board->pen->setColor(color);
    ui->penColorPB->setStyleSheet(QString("background-color : %1").arg(color.name()));
}

void MainWindow::on_fillColorPB_clicked()
{
    QColor color = QColorDialog::getColor(_currentBrush.color(), this);

    if ( color.isValid() ) {
        _currentBrush.setColor(color);
        ui->fillColorPB->setStyleSheet(QString("background-color : %1").arg(color.name()));
    }
}

void MainWindow::on_fillStyleCB_currentIndexChanged(int index)
{
    switch(index) {
    case 0: // Solid
        _currentBrush.setStyle(Qt::SolidPattern);
        break;
    case 1: // Dense
        _currentBrush.setStyle(Qt::Dense4Pattern);
        break;
    case 2:
        _currentBrush.setStyle(Qt::HorPattern);
        break;
    case 3:
        _currentBrush.setStyle(Qt::VerPattern);
        break;
    case 4:
        _currentBrush.setStyle(Qt::CrossPattern);
        break;
    case 5:
        _currentBrush.setStyle(Qt::NoBrush);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionPen_triggered()
{
    board->setMode(MODE::DESSIN_LIBRE);
}


void MainWindow::on_actionSelect_triggered()
{
    board->setMode(MODE::SELECT);
}

>>>>>>> penClass
