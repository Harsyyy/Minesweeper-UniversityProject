#include <QApplication>
#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include "God.h"

int main(int argc, char *argv[]) { //стандартная дичь
  QApplication a(argc, argv);

  QMainWindow mainWindow; // окно программы
  God field; // игровое поле
  mainWindow.setCentralWidget(&field);
  QMenuBar* menuBar = mainWindow.menuBar(); // Меню бар сверху
    QMenu* Game_Menu = new QMenu("Game");  //Создание экземпляра (кнопочки) с именем "Game"
    (*menuBar).addMenu(Game_Menu);  //Добавление кнопочки в меню

    QAction *newAct_Restart = new QAction(QObject::tr("&Restart"), &mainWindow); //Создает подпункт Кнопки "Game" с именем "Restart"
    QObject::connect(newAct_Restart, SIGNAL(triggered()), &field, SLOT(on_gameRestart()));    //Что необходимо сделать при нажатие клавиши "Restart"
    (*Game_Menu).addAction(newAct_Restart);  //Добавление кнопки в подпункт

    QAction *newAct_Easy = new QAction(QObject::tr("&Easy"), &mainWindow);  //Создает подпункт Кнопки "Game" с именем "Easy"
    QObject::connect(newAct_Easy, SIGNAL(triggered()), &field, SLOT(on_gameEasy()));    //Что необходимо сделать при нажатии клаваиши "easy"
    Game_Menu->addAction(newAct_Easy);  //Добавление кнопки в подпункт

    QAction *newAct_Medium = new QAction(QObject::tr("&Medium"), &mainWindow);     //Создает подпункт Кнопки "Game" с именем "Medium"
    QObject::connect(newAct_Medium, SIGNAL(triggered()), &field, SLOT(on_gameMedium()));     //Что необходимо сделать при нажатии клаваиши "Medium"
    Game_Menu->addAction(newAct_Medium);    //Добавление кнопки в подпункт

    QAction *newAct_Hard = new QAction(QObject::tr("&Hard"), &mainWindow);      //Создает подпункт Кнопки "Game" с именем "Hard"
    QObject::connect(newAct_Hard, SIGNAL(triggered()), &field, SLOT(on_gameHard()));    //Что необходимо сделать при нажатии клаваиши "Hard"
    Game_Menu->addAction(newAct_Hard);

  QAction *newAct_Bot = new QAction(QObject::tr("&Bot Step"), &mainWindow);    //Создание пункта "Bot step" в меню
  QObject::connect(newAct_Bot, SIGNAL(triggered()), &field, SLOT(on_gamebot()));        //Что необходимо сделать при нажатии клавиши
  menuBar->addAction(newAct_Bot);           //Добавление кнопки в меню

   mainWindow.show();       //Показ окна
  return a.exec();          //Возврат кода закрытия программы
}
