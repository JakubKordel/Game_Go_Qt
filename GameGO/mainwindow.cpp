#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMainMenuView();

    gameScene = new GoScene();

    ui->gameView->setScene(gameScene);

    ui->gameView->show();

    goController = new GoEngineController();

    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::closeApplication);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::setGameView);
    connect(ui->aboutGameButton, &QPushButton::clicked, this, &MainWindow::setAboutGameView);
    connect(ui->leaveGameButton, &QPushButton::clicked, this, &MainWindow::setMainMenuView);
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &MainWindow::setMainMenuView);
    connect(ui->passButton, &QPushButton::clicked, goController, &GoEngineController::pass);
    connect(ui->gameView, &CustomGameView::spotClicked, goController, &GoEngineController::move);
    connect(ui->resignButton, &QPushButton::clicked, goController, &GoEngineController::resign);
    connect(goController, &GoEngineController::blackToMove, ui->msgLabel, &MsgLabel::setBlackToMove);
    connect(goController, &GoEngineController::whiteToMove, ui->msgLabel, &MsgLabel::setWhiteToMove);
    connect(goController, &GoEngineController::blackWon, ui->msgLabel, &MsgLabel::setBlackWon);
    connect(goController, &GoEngineController::whiteWon, ui->msgLabel, &MsgLabel::setWhiteWon);
    connect(goController, &GoEngineController::arenaChanged, gameScene, &GoScene::updateMap);
    connect(goController, &GoEngineController::gameStarted, ui ->passButton, &GameButton::enableButton);
    connect(goController, &GoEngineController::gameEnded, ui ->passButton, &GameButton::disableButton);
    connect(goController, &GoEngineController::gameStarted, ui ->resignButton, &GameButton::enableButton);
    connect(goController, &GoEngineController::gameEnded, ui ->resignButton, &GameButton::disableButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeApplication(){
      QApplication::quit();
}

void MainWindow::setGameView(){
      goController->setEngine(new GoEngine());
      ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::setAboutGameView(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::setMainMenuView(){
    ui->stackedWidget->setCurrentIndex(0);
}


