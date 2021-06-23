#ifndef COUNTER_H
#define COUNTER_H
# include <QLCDNumber>
#include <QTime>
#include "field.h"


class Counter :public QLCDNumber        // класс отображения цифрового счетчика
{
    Q_OBJECT
public:
  Counter (QWidget *parent = nullptr, Field *a = nullptr);
private slots:
  void on_tick();       //обновление
  void stop();          //слот остановки
protected:
  Field *b;
  QTimer *m_timer;
};
#endif // COUNTER_H
