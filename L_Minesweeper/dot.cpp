#include "dot.h"
#include <QPainter>
#include <QMouseEvent>

Dot::Dot(int i, int j, QWidget *parent)
  : QPushButton(parent), m_i(i), m_j(j), m_value(0), m_isMine(false)
  , m_isOpen(false), m_isFlag(notF)
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //Параметр позиционирования на поле
  setFixedSize(30, 30);                            //Задание размеров кнопки
}

int Dot::i() { return m_i; }        //Возвращение координат клетки
int Dot::j() { return m_j; }

int Dot::isValue()
{
    return m_value;
}
int Dot::value() { return m_value; }    //Возвращает число в клетке
void Dot::incValue() { ++m_value; }     //Функция увеличения числа в клетке

bool Dot::isMine() { return m_isMine; }     //Возвращает является ли клетка миной
void Dot::setMine() { m_isMine = true; repaint(); }     //Установка мины (Repaint - переотрисовка клетка)

bool Dot::isOpen() { return m_isOpen; }             //Возвращает значени об открытости или закрытости клетки
void Dot::setOpen() { m_isOpen = true; repaint(); } //ОТКРОЙСЯ!

void Dot::swapFlag() {                      //Смена флага, вопроса
    if (++m_isFlag > interF)
          m_isFlag = notF;
    repaint();
}

int Dot::isFlag()
{
    return m_isFlag;
}

void Dot::VirtualEvent(int e)           //Получает число сопоставленное слову
{
    switch(e)
    {
        case 1:emit clicked_left(); break;      //Имитация нажатия левой клавиши мыши
        case 2:emit clicked_right(); break;     //Имитация нажатия правой клавиши мыши
        case 3:emit clicked_leftRight(); break; //Имитация нажатие обоих клавишей
    }
}


 void Dot::paintEvent(QPaintEvent *event) {     //Покраска клетки
  QPushButton::paintEvent(event);
  QPainter p(this);         //Кто вызвал того и красим

  if (isOpen())
  {
    if (isMine())
    {
      p.setBrush(QBrush(Qt::red, Qt::SolidPattern));        //Закраска взорвавшейся мины
      p.drawEllipse(2, 2, width() - 4, height() - 4);
      return;
    }
    else
        if (0 == m_value)
        {
            this->setDisabled(1);           //Деактивация клетки
            return;
        }
        else
        {
            setText(QString::number(m_value));  //Запись цифры в клетку
            return;
        }
  }
  else
      switch(m_isFlag)
      {
        case notF: break;
        case flagF:
          p.setBrush(QBrush(Qt::blue, Qt::SolidPattern));       //Закраска, если стоит флаг
          p.drawRect(2, 2, width() - 4, height() - 4);
/*          p.drawLine(2, 2, width() - 4, height()/2 );
          p.drawLine(2, height() - 4, width() - 4, height()/2 );
          p.drawLine(2, 2, 2, height() - 4);*/
          break;
        case interF:
          p.setBrush(QBrush(Qt::green, Qt::SolidPattern));      //Закраска, если стоит вопрос
          p.drawRect(2, 2, width() - 4, height() - 4);
          break;
      }
}

/*virtual*/ void Dot::mouseReleaseEvent(QMouseEvent *e) {       //Обработка нажатий клавиш мыши
  if (e->button() == Qt::LeftButton) emit clicked_leftRight();
  if (e->button() == Qt::LeftButton) emit clicked_left();
  if (e->button() == Qt::RightButton) emit clicked_right();
}
