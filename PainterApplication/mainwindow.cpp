#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
//#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    board = new Board(this);
    ui->widget->setLayout(new QVBoxLayout);
    ui->widget->layout()->addWidget(board);

    setAcceptDrops(true);

    QGraphicsScene * scene(new QGraphicsScene(this));// use smart pointer
    ui->libraryView->setScene(scene);

    /*
     * The six "drawing mode" buttons have a radio-button behavior : this is
     * to ensure one of them is selected.
     */
    ui->actionSelect->setChecked(true);

    /*
     * Sets the default values for the pen attributes
     */
    _currentPen.setColor(Qt::black);
    _currentPen.setWidth(2);
    _currentPen.setStyle(Qt::SolidLine);
    ui->penColorPB->setStyleSheet(QString("background-color : %1").arg(_currentPen.color().name()));

    /*
     * Sets the default values for the brush attributes
     */
    _currentBrush.setColor(Qt::black);
    _currentBrush.setStyle(Qt::SolidPattern);
    ui->fillColorPB->setStyleSheet(QString("background-color : %1").arg(_currentBrush.color().name()));

    /*
     * Redimension the direct pen coolor buttons to be square
     * (impossible to do in QtDesigner)
     */
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

    /*
     * Setting of the colors and connections of all the direct color buttons
     * (All the connections redirect to the same slot, only the color change).
     */
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

    //Paramétrage de la ScrollArea
    ui->scrollArea->setWidget(board);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_penColorPB_clicked()
{
    QColor color = QColorDialog::getColor(_currentPen.color(), this);

    if ( color.isValid() ) {
        _currentPen.setColor(color);
        ui->penColorPB->setStyleSheet(QString("background-color : %1").arg(color.name()));
    }
}

void MainWindow::on_penWidthSB_valueChanged(int value)
{
    _currentPen.setWidth(value);
}

void MainWindow::on_penStyleCB_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        _currentPen.setStyle(Qt::SolidLine);
        break;
    case 1:
        _currentPen.setStyle(Qt::DashLine);
        break;
    case 2:
        _currentPen.setStyle(Qt::DotLine);
        break;
    case 3:
        _currentPen.setStyle(Qt::DashDotLine);
        break;
    default:
        break;
    }
}

void MainWindow::on_directColor_clicked(const QColor& color)
{
    _currentPen.setColor(color);
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

void MainWindow::on_actionSelect_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        ui->actionPen->setChecked(false);
        ui->actionEraser->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionEllipse->setChecked(false);
        ui->actionStar->setChecked(false);
    }
    else {
        ui->actionSelect->setChecked(true);
    }
}

void MainWindow::on_actionPen_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        ui->actionSelect->setChecked(false);
        ui->actionEraser->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionEllipse->setChecked(false);
        ui->actionStar->setChecked(false);
    }
    else {
        ui->actionPen->setChecked(true);
    }
}

void MainWindow::on_actionEraser_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        ui->actionSelect->setChecked(false);
        ui->actionPen->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionEllipse->setChecked(false);
        ui->actionStar->setChecked(false);
    }
    else {
        ui->actionEraser->setChecked(true);
    }
}

void MainWindow::on_actionRectangle_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        ui->actionSelect->setChecked(false);
        ui->actionPen->setChecked(false);
        ui->actionEraser->setChecked(false);
        ui->actionEllipse->setChecked(false);
        ui->actionStar->setChecked(false);
    }
    else {
        ui->actionRectangle->setChecked(true);
    }
}

void MainWindow::on_actionEllipse_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        ui->actionSelect->setChecked(false);
        ui->actionPen->setChecked(false);
        ui->actionEraser->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionStar->setChecked(false);
    }
    else {
        ui->actionEllipse->setChecked(true);
    }
}

void MainWindow::on_actionStar_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        ui->actionSelect->setChecked(false);
        ui->actionPen->setChecked(false);
        ui->actionEraser->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionEllipse->setChecked(false);
    }
    else {
        ui->actionStar->setChecked(true);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save document"), QString(), "Paintings (*.pa)");

    if ( fileName.isEmpty() ) return;

    QFile file(fileName);

    file.open(QIODevice::WriteOnly);

    QDataStream stream(&file);
    stream << QString("PA");

    /*
     * THIS IS JUST FOR TESTING THE SAVE/LOAD FUNCTIONALITY
     */
    Ellipse ellipse(QRect(10, 10, 20, 20));
    ellipse.setProperties(_currentPen, _currentBrush);
    ellipse.save(stream);

    Rectangle rect(QRect(30, 40, 17, 34));
    rect.setProperties(_currentPen, _currentBrush);
    rect.save(stream);

    Star star(QPoint(100, 110), 50);
    star.setProperties(_currentPen, _currentBrush);
    star.save(stream);

    file.close();
}


void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open document"), QString(), "Paintings (*.pa)");

    if ( fileName.isEmpty() ) return;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QDataStream stream(&file);

    QString magic;
    stream >> magic;
    while ( !stream.atEnd() ) {
        /*
         * THIS IS JUST FOR TESTING THE SAVE/LOAD FUNCTIONALITY
         */
        QString shape;
        stream >> shape;
        qDebug() << shape;

        if ( shape == "Ellipse" ) {
            QRect rect;
            QPen pen;
            QBrush brush;
            stream >> rect >> pen >> brush;

            qDebug() << "Ellipse " << rect << pen << brush;
        }
        else if ( shape == "Rectangle" ) {
            QRect rect;
            QPen pen;
            QBrush brush;
            stream >> rect >> pen >> brush;

            qDebug() << "Rectangle " << rect << pen << brush;
        }
        else if ( shape == "Star" ) {
            QPoint center;
            int radius;
            QPen pen;
            QBrush brush;
            stream >> center >> radius >> pen >> brush;

            qDebug() << "Star " << center << radius << pen << brush;
        }
    }

    file.close();
}

