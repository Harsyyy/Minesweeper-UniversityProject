#include "field.h"
#include "dot.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

int Field::is_m_n()
{
    return m_n;
}

int Field::is_m_mineNumber()
{
    return m_mineNumber;
}
int Field::Dot_isFlag(int i, int j)
{
    return m_field[i][j]->isFlag();
}
bool Field::Dot_isOpen(int i, int j)
{
    return m_field[i][j]->isOpen();
}
int Field::Dot_isValue(int i, int j)
{
    return m_field[i][j]->isValue();
}
void Field::Dot_VirtualEvent(int i, int j, int e)
{
    m_field[i][j]->VirtualEvent(e);
}
int Field::get_m_n()        //Возвращает размеры поля
{
    return m_n;
}
int Field::get_m_mineNumber()   //Возвращает количество мин
{
    return m_mineNumber;
}

int Field::get_c_Bomb()     //Возвращает кол-во мин (Счетчик)
{
    return count_Bomb;
}


void Field::set_c_Bomb(int a)       //Устанавливает начальное значение
{
    count_Bomb = a;
}

bool Field::isValidCoord(int i, int j) {           //Проверка выхода за пределы поля (исп в открытии близлежащих)
  return i >= 0 && j >= 0 && i < m_n && j < m_n;
}

bool Field::is_win() {                      //Проверка выигрыша (пока не открыты все клетки, кроме мин)
  int n = m_n * m_n - m_mineNumber;         //n = кол-во клеток - число мин
  for (int i = 0; i < m_n; ++i)
    for (int j = 0; j < m_n; ++j)
      n -= m_field[i][j]->isOpen();         //Пока n не равно числу открытых клеток
  return 0 == n;
}

void Field::openDot(int i, int j) {         //Открытие клеткки
  if (false == isValidCoord(i, j)) return;
  Dot *p = m_field[i][j];                   //Кор-ды открываемой клетки
  if (p->isOpen())                          //Если открыта
    return;
  p->setOpen();                             //Открываем клетку
  if (p->value() != 0) return;              //Если клетка пустая, то открываем близлижащие
  openDot(i - 1, j); openDot(i + 1, j);
  openDot(i, j - 1); openDot(i, j + 1);
  openDot(i - 1, j - 1); openDot(i + 1, j + 1);
  openDot(i + 1, j - 1); openDot(i - 1, j + 1);
}

void Field::on_DotClickedRight() {              //Обработка нажатия правой кнопки мыши
  if (false == m_isGameActive) return;          //Проверка активности игрового поля
  Dot *t = reinterpret_cast<Dot*>(sender());
  if (t->isOpen()) return;                      //Проверка состояния клетки
  t->swapFlag();                                //Смена флага (Флажок, знак вопроса)
  if (t->isFlag() == 1)                         //Если флаг то вычесть 1 из счетчика
      --count_Bomb;
  if (t->isFlag() == 2)                         //Если вопрос, то прибавить обратно
      ++count_Bomb;
  QString a;
  a = ' ' + QString::number(count_Bomb);
  qDebug() << a;
}

void Field::on_DotClickedLeftRight() {          //Обработка двойного нажатия
    if (false == m_isGameActive) return;        //Проверка активности игрового поля
    Dot *t = reinterpret_cast<Dot*>(sender());
    int i = t->i();                             //Координаты открытой клетки
    int j = t->j();
    Dot *p = m_field[i][j];                     //Кор-ды открываемой клетки
    if (p->isOpen()){                           //Если клетка открыта
        if(m_field[i][j]->isFlag() == notF) m_field[i][j]->VirtualEvent(leftV); //Открытие клеток по кр
            if (isValidCoord(i - 1, j - 1) && m_field[i - 1][j - 1]->isFlag() == notF)    m_field[i - 1][j - 1]->VirtualEvent(leftV);
            if (isValidCoord(i - 1, j) && m_field[i - 1][j]->isFlag() == notF)            m_field[i - 1][j]->VirtualEvent(leftV);
            if (isValidCoord(i - 1, j + 1) && m_field[i - 1][j + 1]->isFlag() == notF)    m_field[i - 1][j + 1]->VirtualEvent(leftV);
            if (isValidCoord(i, j - 1) && m_field[i][j - 1]->isFlag() == notF)            m_field[i][j - 1]->VirtualEvent(leftV);
            if (isValidCoord(i, j + 1) && m_field[i][j + 1]->isFlag() == notF)            m_field[i][j + 1]->VirtualEvent(leftV);
            if (isValidCoord(i + 1, j - 1) && m_field[i + 1][j - 1]->isFlag() == notF)    m_field[i + 1][j - 1]->VirtualEvent(leftV);
            if (isValidCoord(i + 1, j) && m_field[i + 1][j]->isFlag() == notF)            m_field[i + 1][j]->VirtualEvent(leftV);
            if (isValidCoord(i + 1, j + 1) && m_field[i + 1][j + 1]->isFlag() == notF)    m_field[i + 1][j + 1]->VirtualEvent(leftV);
    }

}

void Field::openAll() {
  for (int i = 0; i < m_n; ++i)         //Идет по всему полю и открывает клетки
    for (int j = 0; j < m_n; ++j)
      m_field[i][j]->setOpen();
}

void Field::on_DotClickedLeft() {
  if (false == m_isGameActive)                      //Проверка активности игрового поля
    return;
  Dot *t = reinterpret_cast<Dot*>(sender());
  if (t->isOpen() || t->isFlag()== flagF)                                  //Если клетка открыта
    return;
  if (t->isMine()) {                                //Если в открытой клетке мина
    m_isGameActive = false;                         //Игровое поле неактивно
    emit finished();
    QMessageBox::information(nullptr, "Information", "Поражение");   //Вывод сообщения на экран
    openAll();                                      //Открытие всех клеток
    return;
  }
  openDot(t->i(), t->j());
  if (is_win()) {                                   //Если победа
    m_isGameActive = false;                         //Игровое поле неактивно
    emit finished();                                //Сигнал окончания игры
    QMessageBox::information(nullptr, "Information", "Победа");    //Вывод сообщения на экран
    openAll();                                      //Открытие всех клеток
  }
}

Field::Field(QWidget *parent, int _m_n, int _m_mineNumber)      //Создание поля
  : QWidget(parent) {
  count_Bomb = _m_mineNumber;
  if(_m_n != 0 && _m_mineNumber != 0)                           //Проверка входных данных
  {
      m_n = _m_n;
      m_mineNumber = _m_mineNumber;
  }
  m_isGameActive = true;                                        //Активация поля
  QGridLayout *layout = new QGridLayout(this);                  //Создаем сетку виджетов
  layout -> setHorizontalSpacing(0);                            //Минимальный зазор между кнопками
  layout -> setVerticalSpacing(0);
  for (int i = 0; i < m_n; ++i) {
    for (int j = 0; j < m_n; ++j) {
      m_field[i][j] = new Dot(i, j, this);                      //Создаем виджет клетку и передали ей ее корды
      layout->addWidget(m_field[i][j], i, j, 1, 1);             //Закрепляем кнопку в клетке
      connect(m_field[i][j], SIGNAL(clicked_left()), this, SLOT(on_DotClickedLeft()));          //Связание События и метода
      connect(m_field[i][j], SIGNAL(clicked_right()), this, SLOT(on_DotClickedRight()));
      connect(m_field[i][j], SIGNAL(clicked_leftRight()), this, SLOT(on_DotClickedLeftRight()));
    }
  }

  for (int i = 0; i < m_mineNumber;) {                      //Установка мин
    Dot *p = m_field[qrand() % m_n][qrand() % m_n];         //Чтобы не выйти за пределы поля
    if (p->isMine())
      continue;
    else {
      p->setMine();                                         //Установка мины
      ++i;
    }
  }

  for (int i = 0; i < m_n; ++i) {
    for (int j = 0; j < m_n; ++j) {
      if (m_field[i][j]->isMine()) {                                            //Если клетка мина
        if (isValidCoord(i - 1, j - 1)) m_field[i - 1][j - 1]->incValue();      //Изменяем цифры в близлежайщих клетках
        if (isValidCoord(i - 1, j)) m_field[i - 1][j]->incValue();
        if (isValidCoord(i - 1, j + 1)) m_field[i - 1][j + 1]->incValue();
        if (isValidCoord(i, j - 1)) m_field[i][j - 1]->incValue();
        if (isValidCoord(i, j + 1)) m_field[i][j + 1]->incValue();
        if (isValidCoord(i + 1, j - 1)) m_field[i + 1][j - 1]->incValue();
        if (isValidCoord(i + 1, j)) m_field[i + 1][j]->incValue();
        if (isValidCoord(i + 1, j + 1)) m_field[i + 1][j + 1]->incValue();
      }
    }
  }
}
