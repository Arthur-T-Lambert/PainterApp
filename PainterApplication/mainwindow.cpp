#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    board = new Board(this);
    ui->widget->setLayout(new QVBoxLayout);
    ui->widget->layout()->addWidget(board);

    setAcceptDrops(true);
    ui->Ellipse->setAcceptDrops(true);
    ui->Rectangle->setAcceptDrops(true);

    QPixmap ellipsePixmap(":/images/ellipse.png");
    QPixmap scaledEllipsePixmap = ellipsePixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->Ellipse->setPixmap(scaledEllipsePixmap);
    ui->Ellipse->setFixedSize(100, 50) ;
    ui->Ellipse->move(10, 10);
    ui->Ellipse->show();
    ui->Ellipse->setAttribute(Qt::WA_DeleteOnClose);
    ui->Ellipse->setObjectName("Ellipse"); // Ajouter un nom d'objet

    QPixmap rectanglePixmap(":/images/rectangle.png");
    QPixmap scaledRectanglePixmap = rectanglePixmap.scaled(50, 50);
    ui->Rectangle->setPixmap(scaledRectanglePixmap);
    ui->Rectangle->setFixedSize(50, 50);
    ui->Rectangle->show();
    ui->Rectangle->setAttribute(Qt::WA_DeleteOnClose);

    QPixmap starPixmap(":/images/star.png");
    QPixmap scaledStarPixmap = starPixmap.scaled(50, 50);
    ui->Star->setPixmap(scaledStarPixmap);
    ui->Star->setFixedSize(50, 50);
    ui->Star->show();
    ui->Star->setAttribute(Qt::WA_DeleteOnClose);

    QPixmap quickPixmap(":/images/quick.png");
    QPixmap scaledQuickPixmap = quickPixmap.scaled(50, 50);
    ui->Quick->setPixmap(scaledQuickPixmap);
    ui->Quick->setFixedSize(50, 50);
    ui->Quick->show();
    ui->Quick->setAttribute(Qt::WA_DeleteOnClose);

    //Paramétrage de la ScrollArea
    ui->scrollArea->setWidget(board);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


    connect(ui->actionSelect, &QAction::triggered, this, [this]() { board->setCurrentTool(Board::Cursor);});
    connect(ui->actionRectangle, &QAction::triggered, this, [this](){ board->setCurrentTool(Board::RectangleTool); });
    connect(ui->actionEllipse, &QAction::triggered, this, [this](){ board->setCurrentTool(Board::EllipseTool); });
    connect(ui->actionStar, &QAction::triggered, this, [this](){ board->setCurrentTool(Board::StarTool); });
}



MainWindow::~MainWindow() {
    delete ui;
}


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
        qDebug()<<"ofsset: "<<offset<<"\n";
        QPoint dropPos = event->position().toPoint() ;

        Shapes *shape = nullptr;
        QString shapeType = event->mimeData()->text();
        if (shapeType == "Ellipse") {
            shape = new Ellipse(QRect(dropPos, QSize(100, 50)));
        } else if (shapeType == "Rectangle") {
            shape = new Rectangle(QRect(dropPos, QSize(100, 50)));
        }
        if (shapeType == "Star") {
            shape = new Star(dropPos, 50);
        } else if (shapeType == "Quick") {

            shape = new ImageQuick(QRect(dropPos, QSize(100, 100)), ":/images/quick.png");
        }


        if (shape) {
            QPen pen(Qt::black, 4, Qt::DotLine);
            QBrush brush(Qt::gray);
            shape->setProperties(pen, brush);
            board->addShape(shape); // Ajoutez la forme au tableau
        }

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

    if (child == ui->Ellipse) {
        mimeData->setText("Ellipse");
    }
    if (child == ui->Rectangle) {
        mimeData->setText("Rectangle");
    }
    if(child == ui->Star) {
        mimeData->setText("Star");
    } else if (child == ui->Quick) {
        mimeData->setText("Quick");
    }

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(/*event->position().toPoint() -*/ child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));//couleur par defaut
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
