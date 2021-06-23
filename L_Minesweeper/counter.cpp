#include <QTimer>
#include "counter.h"

Counter::Counter(QWidget *parent, Field *a)
  :QLCDNumber(parent) {
  setSegmentStyle(Flat);
  b = a;                            //Получение начальных значений
  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(on_tick()));
  m_timer->start(100);             //Частота обновления



  setFixedSize(100, 30);        //Установка фиксированных размеров виджета
}

void Counter::on_tick() {
    display(b->get_c_Bomb());   //Вывод кол-ва бомб
}


void Counter::stop() { m_timer->stop(); }                         //Слот остановки счетчика
