#ifndef DOT_H
# define DOT_H
# include <QPushButton>     //Класс кнопки

enum Flag       //Сопопставляем цифре слово
{
    notF = 0,   //Флаг отсутствует
    flagF = 1,  //Есть флаг
    interF = 2, //Знак вопроса
};
enum VirtEvent
{
    leftV = 1,          //Левая клаваиша
    rightV = 2,         //Правая клавиша
    leftRightV = 3,     //Двойное нажатие
};

class Dot : public QPushButton {    //Одна клетка наследуемая от класса кнопки
  Q_OBJECT
public:
  Dot(int i, int j, QWidget *parent = nullptr);
  int  isValue();           // возвращает счетчик мин
  int i();                  // возвращает индекс строки клетки
  int j();                  // возвращает индекс столбца клетки
  bool isMine();            // проверяет есть ли в клетке мина
  void setMine();           // ставит в клетку мину
  void incValue();          // увеличивает счетчик мин
  int value();              // возвращает счетчик мин
  void setOpen();           // открывает клетку
  bool isOpen();            // проверяет открыта ли клетка
  void swapFlag();          // изменить флаг
  int isFlag();             // является ли клетка миной
  void VirtualEvent(int);   // Эмулятор событий
signals:
  void clicked_left();      // Сигнал клика левой кнопки мыши
  void clicked_right();     // Сигнал клика правой кнопки мыши
  void clicked_leftRight(); // Сигнал клика левой и правой мыши
protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent *e);

  int m_i, m_j;             // координаты клетки
  int m_value;              // значение, хранимое в клетке
  bool m_isMine;            // является ли клетка миной?
  bool m_isOpen;            // открыта ли клетка?
  int m_isFlag;             // является клетка флагом
};


#endif // DOT_H
