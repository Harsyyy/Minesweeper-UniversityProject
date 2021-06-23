#ifndef FIELDWRAPPER_H
# define FIELDWRAPPER_H
# include <QWidget>
# include <QLabel>
#include "bot.h"

class QGridLayout;  //Объявление классов
class Clock;
class Field;
class Counter;

// посредник между полем и таймером
class God :public QWidget {
  Q_OBJECT                   //Пишется тогда, когда в классе есть сигналы или слоты
  void on_game(int, int);    //Запуск игры
public:
  God();
public slots:
  void on_gameRestart();
  void on_gameEasy();
  void on_gameMedium();
  void on_gameHard();
  void on_gamebot();
protected:
  Field *m_field = nullptr;     // игровое поле

  Clock *m_time = nullptr;  // отображает время игры
  Counter *m_counter = nullptr;
  QGridLayout *m_layout = nullptr;  // раскладка виджета
  Bot *m_bot = nullptr;
};

#endif // FIELDWRAPPER_H
