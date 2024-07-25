#include "board.h"

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

    ui->setupUi(this);
    setupShapes();
}

//------------------------------------------------------------------------------------------
/** Brief Déstructeur de la classe Board */
Board::~Board()
{
    delete ui;
    qDeleteAll(formes);
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
    drawGrid(painter);



    // Dessin des formes
    for (Shapes *shape : formes) {
        shape->draw(&painter);
    }

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
        lastMousePosition = event->pos();
        // Récupération de l'event clique sur une forme
        for (Shapes *shape : formes) {
            if (shape->contains(event->pos())) {
                draggedShape = shape;
                break;
            }
        }
    }

    // Récupération de l'event clique sur une forme
    // lastMousePosition = event->pos();
    // for (Shapes *shape : formes) {
    //     if (shape->contains(event->pos())) {
    //         draggedShape = shape;
    //         break;
    //     }
    // }
}

//------------------------------------------------------------------------------------------
/** Brief Gestion des mouvements de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = (event->pos() - lastMousePosition);

        if (draggedShape) {
            //QPoint delta = event->pos() - lastMousePosition;
            draggedShape->move(delta);
            lastMousePosition = event->pos();
            update();
        }
/*
        // Si une forme est séléctionnée, on la déplace en tenant compte du zoom
        if (indexShapeSelected != -1)
        {

            shapes[indexShapeSelected].moveLeft(shapes[indexShapeSelected].left() + delta.x() / zoomVal);
            shapes[indexShapeSelected].moveTop(shapes[indexShapeSelected].top() + delta.y() / zoomVal);
        }

        // Sinon, on déplace le widget en vue panoramique
        else
        {
            translateWidget += delta / zoomVal;
        }
*/

        // translateWidget += delta / zoomVal;
        // lastMousePosition = event->pos();
        // refresh();
    }
}

//------------------------------------------------------------------------------------------
/** Gestion des relâchements de clic de souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{
    //indexShapeSelected = -1; // Reset de l'index de la forme séléctionné
    Q_UNUSED(event);
    draggedShape = nullptr;
}

//------------------------------------------------------------------------------------------
/** Gestion des évènements de la molette souris
 *  \param event Pointeur sur les évènements molettes récupérés
*/
void Board::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        zoomPlus();
    else
        zoomMoins();
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
    formes.append(new Ellipse(QRect(450, 450, 100, 50)));
    formes.last()->setProperties(pen, ellipseBrush);

    QBrush rectBrush(Qt::red);
    formes.append(new Rectangle(QRect(600, 250, 150, 75)));
    formes.last()->setProperties(pen, rectBrush);

    QBrush starBrush(Qt::magenta);
    formes.append(new Star(QPoint(350, 150), 50));
    formes.last()->setProperties(pen, starBrush);

    formes.append(new ImageQuick(QRect(300, 300, 50, 50), ":/images/quick.png"));
}
