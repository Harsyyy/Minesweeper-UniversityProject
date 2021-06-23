#include "God.h"
#include "field.h"
#include "clock.h"
#include "counter.h"
#include <QGridLayout>

God::God()            //Конcтруктор класс God
{
  m_layout = new QGridLayout;   //Создание сетки виджетов
  setLayout(m_layout);          //Используем созданную сетку для окна
  //on_gameEasy();   //Запуск игры на легком уровне
}
void God::on_gamebot()
{
    if (m_bot)
        m_bot->Step();
}
void God::on_gameRestart()      //Метод перезапуска игры
{
    if (m_field)     //Проверка наличия поля
        on_game((*m_field).get_m_n(),(*m_field).get_m_mineNumber()); //Действия при наличии поля
}
void God::on_gameEasy() //Запуск игры на легком уровне
{
    on_game(10,10);
}
void God::on_gameMedium()  //Запуск игры на среднем уровне
{
    on_game(15,30);
}
void God::on_gameHard()     //Запуск игры на сложном уровне
{
    on_game(20,60);
}
void God::on_game(int _m_n, int _m_mineNumber) {    //Метод запуска игры (Размеры поля, Кол-во мин)
  if (m_field) delete m_field;                      //Если поле существовало, то удалить его
  if (m_bot) delete m_bot;
  if (m_time) delete m_time;                        //Если таймер существовал, то удалить его
  if (m_counter) delete m_counter;
  m_time = new Clock(this);                         //Создать новый таймер
  m_field = new Field(this, _m_n, _m_mineNumber);   //Создать поле с заданными параметрами
  m_bot = new Bot(m_field);
  m_counter = new Counter (this, m_field);
  connect(m_field, SIGNAL(finished()), m_time, SLOT(stop())); //Если игра завершена, остановить таймер
  connect(m_field, SIGNAL(finished()), m_counter, SLOT(stop())); //Если игра завершена остановить счетчик мин
  m_layout->addWidget(m_time, 0, 0, 1, 1, Qt::AlignRight);  //Добавление таймера
  m_layout->addWidget(m_counter, 0, 0, 1, 1, Qt::AlignLeft); //Добавление счетчика мин
  m_layout->addWidget(m_field, 1, 0, 1, 1);                 //Добавление поля
}
