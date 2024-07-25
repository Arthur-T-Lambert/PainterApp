#include "board.h"


#include <QMimeData>
//------------------------------------------------------------------------------------------
/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 *  \param ui Association du user interface
 */
Board::Board(QWidget *parent) : QWidget(parent), ui(new Ui::Board),
    draggedShape(nullptr){

    zoomVal = 1.0;
    translateWidget = {0,0};
    lastMousePosition = {0,0};

    mode = MODE::SELECT;
    pen = new Pen(this);
    ui->setupUi(this);
    //setupShapes();
}

//------------------------------------------------------------------------------------------
/** Brief Déstructeur de la classe Board */
Board::~Board()
{
    delete ui;
    qDeleteAll(formes);
    delete pen;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion du rendu graphique
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Affichage du background
    drawBackground(painter, Qt::SolidPattern , Qt::yellow); //Valeur à remplacer dynamiquement

    // Gestion des dimensions en fonction du zoom et de la translation
    updateDimensionAndPosition(painter);

    // Affichage de la grille
    if(printGrid)
        drawGrid(painter);

    // Dessin des formes
    for (Shapes *shape : formes) {
        shape->draw(&painter);
    }

    //Appel de la fonction de dessin du pen, en lui donnant en argument le painter du board
    pen->paintEvent(event, painter);
}

//------------------------------------------------------------------------------------------
/** Brief Fonction d'affichage du background
 *  \param painter Pointeur sur le canva painter
 *  \param brushStyle Style dy brush
 *  \param color Couleur du brush
 */
void Board::drawBackground(QPainter &painter, const Qt::BrushStyle brushStyle, const Qt::GlobalColor &brushColor)
{
    QBrush brush;
    brush.setColor(brushColor);
    brush.setStyle(brushStyle);
    painter.setBrush(brush);
    painter.drawRect(rect());
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter du mode courant
 *  \param m Mode choisi
*/
void Board::setMode(MODE m)
{
    this->mode = m;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la forme à dessiner
 *  \param m Forme choisie
*/
void Board::setForme(FORME m)
{
    this->forme = m;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de l'affichage de la grille
 *  \param bool true pour l'afficher, et false pour la désactiver
*/
void Board::showGrid(bool print)
{
    this->printGrid = print;
    refresh();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter du brush
 *  \param brush Type de brush
 */
void Board::setBrushStyle(const Qt::BrushStyle &brush)
{
    this->brush.setStyle(brush);
}

//------------------------------------------------------------------------------------------
/** Brief Fonction setter de la couleur du brush
 *  \param color Couleur du brush
 */
void Board::setBrushColor(const QColor &color)
{
    brush.setColor(color);
}

//------------------------------------------------------------------------------------------
/** Brief Fonction getter du mode courant
 *  \return Retourne le mode courant
*/
MODE Board::getMode()
{
    return this->mode;
}


//------------------------------------------------------------------------------------------
/** Brief Fonction d'affichage de la grille en background
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::drawGrid(QPainter &painter)
{
    int gridSpacing = 30;
    QPen pen(Qt::gray, 1, Qt::SolidLine);
    painter.setPen(pen);

    int width = this->width();
    int height = this->height();

    // Lignes verticales
    for (int x = 0; x < width; x += gridSpacing) {
        painter.drawLine(x, 0, x, height);
    }
    // Lignes horizontales
    for (int y = 0; y < height; y += gridSpacing) {
        painter.drawLine(0, y, width, y);
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction dynamique de gestion du zoom et de la translation du widget
 *  \param painter Pointeur sur le canva painter
 */
void Board::updateDimensionAndPosition(QPainter &painter)
{
    // Application de la transformation pour la translation et le zoom
    painter.setTransform(QTransform().translate(translateWidget.x(), translateWidget.y()).scale(zoomVal, zoomVal));
}


//------------------------------------------------------------------------------------------
/** Brief Gestion des cliques de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mousePressEvent(QMouseEvent *event)
{
    // Récupération de l'event clique gauche
    if (event->button() == Qt::LeftButton)
    {
        if(mode == MODE::FORMES)
        {
            if(forme == FORME::ELLIPSE)
            {
                formes.append(new Ellipse(QRect(event->pos().x(), event->pos().y(), 100, 50)));
            }
            if(forme == FORME::RECTANGLE)
            {
                formes.append(new Rectangle(QRect(event->pos().x(), event->pos().y(), 150, 75)));
            }
            if(forme == FORME::STAR)
            {
                formes.append(new Star(QPoint(event->pos().x(), event->pos().y()), 50));
            }

            formes.last()->setProperties(pen->pen, brush);
            pen->setEraseMode((false));
            pen->setDrawingMode(false);
            refresh();
        }
        if(mode == MODE::SELECT)
        {
            lastMousePosition = event->pos();
            // Récupération de l'event clique sur une forme
            for (Shapes *shape : formes)
            {
                if (shape->contains(event->pos()))
                {
                    draggedShape = shape;
                    break;
                }
            }
        }

        if(mode == MODE::DESSIN_LIBRE)
        {
            pen->setDrawingMode(true);
            pen->setEraseMode((false));
            pen->mousePressEvent(event);
        }

        if(mode == MODE::GOMME)
        {
            pen->setEraseMode((true));
            pen->setDrawingMode(false);
            pen->mousePressEvent(event);
        }
    }
}

//------------------------------------------------------------------------------------------
/** Brief Gestion des mouvements de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {

        if(mode ==MODE::FORMES)
        {

        }

        if(mode == MODE::DESSIN_LIBRE && pen->isDrawing() == true)
        {
            pen->mouseMoveEvent(event);
        }

        if(mode == MODE::SELECT)
        {
            QPoint delta = (event->pos() - lastMousePosition);
            if (draggedShape)
            {
                //QPoint delta = event->pos() - lastMousePosition;
                draggedShape->move(delta);
                lastMousePosition = event->pos();
                update();
            }
            else
            {
                /*
                // Translation du board
                QPoint delta = (event->pos() - lastMousePosition);
                translateWidget += delta / zoomVal;
                lastMousePosition = event->pos();
                */
            }
        }

        if (mode == MODE::GOMME)
        {
            pen->mouseMoveEvent(event);
        }

        refresh();
    }
}

//------------------------------------------------------------------------------------------
/** Gestion des relâchements de clic de souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(mode == MODE::SELECT)
    {
        draggedShape = nullptr;
    }
    if(mode == MODE::FORMES)
    {
        draggedShape = nullptr;
    }
    if(mode == MODE::DESSIN_LIBRE)
    {
        pen->mouseReleaseEvent(event);
    }
}

//------------------------------------------------------------------------------------------
/** Gestion des évènements de la molette souris
 *  \param event Pointeur sur les évènements molettes récupérés
*/
void Board::wheelEvent(QWheelEvent *event)
{
    /*
    if (event->angleDelta().y() > 0)
        zoomPlus();
    else
        zoomMoins();
    */
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de rafraichissement du widget */
void Board::refresh()
{
    update();
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de zoom avant du widget */
void Board::zoomPlus()
{
    if(zoomVal * 1.02 < 3)
    {
        zoomVal *= 1.02;
        refresh();
    }
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de zoom arrière du widget */
void Board::zoomMoins()
{
    if(zoomVal / 1.02 > 0.5)
    {
        zoomVal /= 1.02;
        refresh();
    }
}

void Board::setupShapes() {
    QPen pen(Qt::black, 4, Qt::DotLine);
    QBrush ellipseBrush(Qt::gray);
    formes.append(new Ellipse(QRect(10, 10, 100, 50)));
    formes.last()->setProperties(pen, ellipseBrush);

    QBrush rectBrush(Qt::red);
    formes.append(new Rectangle(QRect(600, 250, 150, 75)));
    formes.last()->setProperties(pen, rectBrush);

    QBrush starBrush(Qt::magenta);
    formes.append(new Star(QPoint(350, 150), 50));
    formes.last()->setProperties(pen, starBrush);

    formes.append(new ImageQuick(QRect(300, 300, 50, 50), ":/images/quick.png"));
}

// void Board::dropEvent(QDropEvent *event) {
//     if (event->mimeData()->hasFormat("application/x-shape") && event->mimeData()->hasImage()) {
//         QByteArray itemData = event->mimeData()->data("application/x-shape");
//         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
//         int shapeTypeInt;
//         dataStream >> shapeTypeInt;
//         DraggablePixmapItem::ShapeType shapeType = static_cast<DraggablePixmapItem::ShapeType>(shapeTypeInt);

//         QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
//         QPoint dropPos = event->pos();

//         Shapes* newShape = createShapeFromType(shapeType, dropPos, pixmap.size());

//         if (newShape) {
//             formes.append(newShape);
//             update();
//         }

//         event->acceptProposedAction();
//     }
// }

// void Board::dropEvent(QDropEvent *event)
// {
//     if (event->mimeData()->hasFormat("application/x-shape") && event->mimeData()->hasImage()) {
//         QByteArray itemData = event->mimeData()->data("application/x-shape");
//         QDataStream dataStream(&itemData, QIODevice::ReadOnly);
//         int shapeTypeInt;
//         dataStream >> shapeTypeInt;
//         DraggablePixmapItem::ShapeType shapeType = static_cast<DraggablePixmapItem::ShapeType>(shapeTypeInt);

//         QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
//         QPoint dropPos = event->pos();

//         Shapes* newShape = createShapeFromType(shapeType, dropPos, pixmap.size());

//         if (newShape) {
//             formes.append(newShape);
//             update();
//         }

//         event->acceptProposedAction();
//     }
// }

// Shapes* Board::createShapeFromType(DraggablePixmapItem::ShapeType type, const QPoint& pos, const QSize& size)
// {
//     QPen pen(Qt::black, 4, Qt::DotLine);
//     QBrush brush;

//     switch(type) {
//     case DraggablePixmapItem::Ellipse:
//         brush = QBrush(Qt::gray);
//         return new Ellipse(QRect(pos, size));
//     case DraggablePixmapItem::Rectangle:
//         brush = QBrush(Qt::red);
//         return new Rectangle(QRect(pos, size));
//     case DraggablePixmapItem::Star:
//         brush = QBrush(Qt::magenta);
//         return new Star(pos, std::min(size.width(), size.height()) / 2);
//     case DraggablePixmapItem::Quick:
//         return new ImageQuick(QRect(pos, size), ":/images/quick.png");
//     default:
//         return nullptr;
//     }
// }

