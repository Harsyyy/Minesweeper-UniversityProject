#include "clock.h"
#include <QTimer>

Clock::Clock(QWidget *parent)
  :QLCDNumber(parent), m_time(0, 0, 0) {
  setSegmentStyle(Flat);

  m_timer = new QTimer(this);                                   //Создание таймера
  connect(m_timer, SIGNAL(timeout()), this, SLOT(on_tick()));   //Соединение сигнала и слота
  m_timer->start(1000);                                         //Значение после которого будет переполнения

  display(m_time.toString("hh:mm:ss"));

  setFixedSize(150, 30);
}

void Clock::on_tick() {
  m_time = m_time.addSecs(1);                                   //Добавленеи секунды
  display(m_time.toString("hh:mm:ss"));                         //Тип форматирования текста
}

void Clock::stop() { m_timer->stop(); }                         //Слот остановки таймера
