#ifndef BOARD_H
#define BOARD_H

/*!\file board.h
 *
 * \brief Classe Board gérant le widget d'affichage des formes et dessins
 * \auteur : Nehari Mohamed
 */

#include <QWidget>

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void draw();
};

#endif // BOARD_H
