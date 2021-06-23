#ifndef FIELD_H
# define FIELD_H
# include <QWidget>


class Dot;

// игровое поле
class Field :public QWidget {
  Q_OBJECT
  public:
    bool m_isGameActive;    //состояние игрового поля
    int is_m_n();
    int is_m_mineNumber();
    int get_c_Bomb();
    void set_c_Bomb(int);
    int get_m_n();
    int get_m_mineNumber();
    int  Dot_isFlag(int, int);              // возвращаеет значения флага
    bool Dot_isOpen(int, int);              // проверяет открыта ли клетка
    int  Dot_isValue(int, int);             // возвращает счетчик мин
    void Dot_VirtualEvent(int, int , int);  // эмулирует события
    Field(QWidget *parent = nullptr, int _m_n = 0, int _m_mineNumber = 0);
protected:
  int count_Bomb;
  void openAll();                    // открывает все клетки поля
  bool isValidCoord(int i, int j);   // проверяет является ли i,j координатами
  void openDot(int i, int j);        // открывает клетку и все клетки вокруг
  bool is_win();                     // проверяет выигрыш
  int m_n = 0;                       // размер поля
  int m_mineNumber = 0;              // количество мин на поле
  Dot* m_field[20][20] = {};         // игровое поле
protected slots:
  void on_DotClickedLeft();          // слот обработки нажатия клетки левой кнопкой мыши
  void on_DotClickedRight();         // слот обработки нажатия клетки правой кнопкой мыши
  void on_DotClickedLeftRight();     // слот обработки нажатия клетки двух кнопкой мыши
signals:
  void finished();                   // сигнал завершения игры

};

#endif // FIELD_H
