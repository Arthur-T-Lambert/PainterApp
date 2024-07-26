#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QDrag>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
#include <QColorDialog>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <Qtranslator>

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
    ui->Rectangle->setFixedSize(100, 50) ;
    // ui->Rectangle->move(10, 10);
    ui->Rectangle->show();
   // ui->Rectangle->setAttribute(Qt::WA_DeleteOnClose);

    ui->penColorPB->setStyleSheet(QString("background-color : %1").arg(board->pen->getColor().name()));

    /*
     * The six "drawing mode" buttons have a radio-button behavior : this is
     * to ensure one of them is selected.
     */
    ui->actionSelect->setChecked(true);

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
    /* Second row */
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
    // QPixmap pixmap1(":/images/ellipse.png");
    // QPixmap pixmap2(":/images/rectangle.png");
    // QPixmap pixmap3(":/images/quick.png");
    // QPixmap pixmap4(":/images/star.png");

    // QGraphicsPixmapItem *item1 = new QGraphicsPixmapItem(pixmap1);// use smart pointer
    // QGraphicsPixmapItem *item2 = new QGraphicsPixmapItem(pixmap2);// use smart pointer
    // QGraphicsPixmapItem *item3 = new QGraphicsPixmapItem(pixmap3);// use smart pointer
    // QGraphicsPixmapItem *item4 = new QGraphicsPixmapItem(pixmap4);// use smart pointer

    // Optionally, set the position of each item
    // item1->setPos(0, 0);    // Position of the first item (Ellipse)
    // item2->setPos(80, 0);   // Position of the second item (Rectangle)
    // item3->setPos(0, 80);  // Position of the third item (Quick)
    // item4->setPos(80, 80);  // Position of the fourth item (Star)

    // item1->setScale(0.15);
    // item2->setScale(0.15);
    // item3->setScale(0.15);
    // item4->setScale(0.15);

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
        QPoint dropPos = QPoint(event->position().x()-ui->scrollArea->x()-50, event->position().y()-ui->scrollArea->y()-60);

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
            //QPen pen(Qt::black, 4, Qt::DotLine);
            //QBrush brush(Qt::gray);
            shape->setProperties(board->pen->pen, board->brush);
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

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(/*event->position().toPoint() - */child->pos());

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

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), board->brush.color());
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
    board->pen->setWidth(value);
}

void MainWindow::on_penStyleCB_currentIndexChanged(int index)
{
    qDebug() << index;
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
        qDebug() << "couleur";
        //_currentBrush.setColor(color);
        board->setBrushColor(color);
        ui->fillColorPB->setStyleSheet(QString("background-color : %1").arg(color.name()));
    }
}

void MainWindow::on_fillStyleCB_currentIndexChanged(int index)
{
    switch(index) {
    case 0: // Solid
        board->setBrushStyle(Qt::SolidPattern);
        break;
    case 1: // Dense
        board->setBrushStyle(Qt::Dense4Pattern);
        break;
    case 2:
        board->setBrushStyle(Qt::HorPattern);
        break;
    case 3:
        board->setBrushStyle(Qt::VerPattern);
        break;
    case 4:
        board->setBrushStyle(Qt::CrossPattern);
        break;
    case 5:
        board->setBrushStyle(Qt::NoBrush);
        break;
    default:
        break;
    }
}

void MainWindow::resetIconToolBar()
{
    ui->actionSelect->setIcon(QIcon(":images/cursor.png"));
    ui->actionPen->setIcon(QIcon(":images/pen_cursor.png"));
    ui->actionEllipse->setIcon(QIcon(":images/circle.png"));
    ui->actionRectangle->setIcon(QIcon(":images/rectangle1.png"));
    ui->actionEraser->setIcon(QIcon(":images/eraser.png"));
    ui->actionStar->setIcon(QIcon(":images/star_cursor.png"));
}

/** Brief Fonction slot, lié au spinBox d'affichage de la grille
*/
void MainWindow::on_showGrid_SpinBox_stateChanged(int arg1)
{
    board->showGrid(ui->showGrid_SpinBox->isChecked());
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "À Propos", "Application Paint \n\n Dévelopé par : \n\n François Roudier \n Arthur Lambert \n Yasmine Fatnassi \n Nehari Mohamed");
}

void MainWindow::on_actionUndo_triggered()
{
    board->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    board->redo();
}

void MainWindow::on_actionSelect_triggered(bool checked)
{
    /*
     * Radio button : if pressed, all the other buttons are unpressed
     * if unpressed, press it again.
     */
    if ( checked ) {
        board->setMode(MODE::SELECT);
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
        board->setMode(MODE::DESSIN_LIBRE);
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
        board->setMode(MODE::GOMME);
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
        board->setMode(MODE::FORMES);
        board->setForme(FORME::RECTANGLE);
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
        board->setMode(MODE::FORMES);
        board->setForme(FORME::ELLIPSE);
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
        board->setMode(MODE::FORMES);
        board->setForme(FORME::STAR);
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

void MainWindow::on_actionEnglish_triggered()
{
    QTranslator translator;
    translator.load(":/en_US.qm");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}


void MainWindow::on_actionFrancais_triggered()
{
    QTranslator translator;
    translator.load(":/fr_FR.qm");
    qApp->installTranslator(&translator);

    ui->retranslateUi(this);
}

