#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>

#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow
     * MainWindow is the main widget of the application. It has a unique instance,
     * which is the first to appear and the last to disappear. It is the uppermost
     * container of all the widgets, as well as a lot of code.
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief getcurrentPen()
     *     An accessor to the current QPen property
     *     (The outline for the new Shapes created)
     * @return the current QPen
     */
    const QPen& getcurrentPen() const
    {
        return _currentPen;
    }

    /**
     * @brief getcurrentBrush()
     *     An accessor to the current QBrush property
     *     (The filling for the new Shapes created)
     * @return
     */
    const QBrush& getcurrentBrush() const
    {
        return _currentBrush;
    }

private slots:

    /**
     * @brief on_actionQuit_triggered
     * slot called when action "Quit" is triggered
     */
    void on_actionQuit_triggered();

    /**
     * @brief on_penColorPB_clicked
     * slot triggered when pressing on the pen color button
     */
    void on_penColorPB_clicked();

    /**
     * @brief on_penWidthSB_valueChanged
     * slot triggered when using the pen width spinbox
     * @param width
     * the width value selected
     */
    void on_penWidthSB_valueChanged(int width);

    /**
     * @brief on_penStyleCB_currentIndexChanged
     * slot triggered when changing the pen style combobox
     * @param index
     * index of the style selected (0 to 3)
     */
    void on_penStyleCB_currentIndexChanged(int index);

private:
    /**
     * @brief on_directColor_clicked
     * slot called when one of the direct pen color button
     * is clicked. As this can be called by numerous buttons,
     * it is not actually a slot and connected through a lambda.
     */
    void on_directColor_clicked(const QColor&);

private slots:
    /**
     * @brief on_fillColorPB_clicked
     * slot triggered when clicking on the fill color button
     */
    void on_fillColorPB_clicked();

    /**
     * @brief on_fillStyleCB_currentIndexChanged
     * slot triggered when changing the pen style combobox
     * @param index
     * index of the style selected (0 to 6)
     */
    void on_fillStyleCB_currentIndexChanged(int index);

    /**
     * @brief on_actionSelect_triggered
     * slot triggered when choosing the "Select" mode
     * @param checked
     * is the action checked or not (useful for radiobutton behavior) ?
     */
    void on_actionSelect_triggered(bool checked);

    /**
     * @brief on_actionRectangle_triggered
     * slot triggered when choosing the "Rectangle" mode
     * @param checked
     * is the action checked or not (useful for radiobutton behavior) ?
     */
    void on_actionRectangle_triggered(bool checked);

    /**
     * @brief on_actionPen_triggered
     * slot triggered when choosing the "Pen" mode
     * @param checked
     * is the action checked or not (useful for radiobutton behavior) ?
     */
    void on_actionPen_triggered(bool checked);

    /**
     * @brief on_actionEraser_triggered
     * slot triggered when choosing the "Eraser" mode
     * @param checked
     * is the action checked or not (useful for radiobutton behavior) ?
     */
    void on_actionEraser_triggered(bool checked);

    /**
     * @brief on_actionEllipse_triggered
     * slot triggered when choosing the "Ellipse" mode
     * @param checked
     * is the action checked or not (useful for radiobutton behavior) ?
     */
    void on_actionEllipse_triggered(bool checked);

    /**
     * @brief on_actionStar_triggered
     * slot triggered when choosing the "Star" mode
     * @param checked
     * is the action checked or not (useful for radiobutton behavior) ?
     */
    void on_actionStar_triggered(bool checked);

    /**
     * @brief on_actionSave_triggered
     * slot triggered when clicking on "Save"
     */
    void on_actionSave_triggered();

    /**
     * @brief on_actionLoad_triggered
     * slot triggered when clicking on "Load"
     */
    void on_actionLoad_triggered();

private:
    Ui::MainWindow *ui;

    QPen _currentPen;
    QBrush _currentBrush;

    /**
     * @brief board
     * Pointer to the board, the cutsom widget wher the actual drawing takes place.
     */
    Board *board;
};
#endif // MAINWINDOW_H
