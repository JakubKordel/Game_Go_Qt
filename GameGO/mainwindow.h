#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <stonegraphics.h>
#include "goscene.h"
#include "customgameview.h"
#include "goenginecontroller.h"
#include "msglabel.h"
#include "gamebutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void closeApplication();
    void setGameView();
    void setAboutGameView();
    void setMainMenuView();
private:

    Ui::MainWindow *ui;

    GoScene * gameScene;

    GoEngineController * goController;
};

#endif // MAINWINDOW_H
