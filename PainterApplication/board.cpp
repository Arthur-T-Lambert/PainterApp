#include "board.h"

//------------------------------------------------------------------------------------------
/** Brief Constructeur de la classe Board
 *  \param parent Pointeur sur le widget parent
 *  \param ui Association du user interface
 *  \param zoomVal Valeur par défaut du zoom, définit à 1.0
 */
Board::Board(QWidget *parent) : QWidget(parent), ui(new Ui::Board)
{
    zoomVal = 1.0;
    translateWidget = {0,0};
    lastMousePosition = {0,0};
    brush.setColor(QColor(0,255,0));
    brush.setStyle(Qt::Dense5Pattern);

    //Test avec un rectangle
    shapes.append(QRect(10, 10, 50, 50));

    ui->setupUi(this);
}

//------------------------------------------------------------------------------------------
/** Brief Déstructeur de la classe Board */
Board::~Board()
{
    delete ui;
}

//------------------------------------------------------------------------------------------
/** Brief Fonction de gestion du rendu graphique
 *  \param event Pointeur sur les évènements récupérés
*/
void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Affichage du background
    setBrush(Qt::Dense3Pattern, Qt::yellow);
    painter.setBrush(brush);
    painter.drawRect(rect());

    // Gestion des dimensions en fonction du zoom et de la translation
    updateDimensionAndPosition(painter);

    // Affichage de la grille
    drawGrid(painter);

    // Affichage d'un rectangle
    setBrush(Qt::Dense5Pattern, Qt::green);
    painter.setBrush(brush);
    for (const QRect &shape : shapes) {
        painter.drawRect(shape);
    }
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
/** Brief Fonction paramétrage du brush
 *  \param style style du brush
 *  \param color Couleur du brush
*/
void Board::setBrush(Qt::BrushStyle style, QColor color)
{
    brush.setColor(color);
    brush.setStyle(style);
    refresh();
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
/** Brief Fonction permettant de checker si la position de la souris est dans une forme.
 *  Si le clique souris est dedans, l'id de la forme est retourné
 *  \param pos Position du clic
 *  \return -1 si le clique n'est pas dans une forme, et l'id de la forme dans le cas contraire
 */
int Board::indexOfShapeSelected(const QPoint &pos)
{
    // Mise a jour des coordonnées en fonction de la translation et du zoom
    QPoint transformedPos = (pos - translateWidget) / zoomVal;

    for (int i = 0; i < shapes.size(); ++i)
    {
        if (shapes[i].contains(transformedPos))
            return i;
    }
    return -1;
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
        indexShapeSelected = indexOfShapeSelected(lastMousePosition); // Check si le clique est fait dans une forme
    }
}

//------------------------------------------------------------------------------------------
/** Brief Gestion des mouvements de la souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = (event->pos() - lastMousePosition);

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

        lastMousePosition = event->pos();
        refresh();
    }
}

//------------------------------------------------------------------------------------------
/** Gestion des relâchements de clic de souris
 *  \param event Pointeur sur les évènements souris récupérés
*/
void Board::mouseReleaseEvent(QMouseEvent *event)
{
    indexShapeSelected = -1; // Reset de l'index de la forme séléctionné
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
