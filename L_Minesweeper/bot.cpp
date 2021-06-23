#include <QDebug>
#include "bot.h"
#include "dot.h"



Bot::Bot(Field *m)
{
    field = m;
    m_n = field->is_m_n();
    m_mineNumber = field->is_m_mineNumber();
}

void Bot::Step()
{

    //qDebug() << "click but";

    if(field->m_isGameActive != true)           //Если игровое поле неактивно, то возврат
    {
        return;
    }
    //const int Flag_C = 65535;
    //const int Closed_C = 65534;

    /*auto CountDot = [&](int i, int j) -> int
    {
        if(i == 0 || j == 0)
        {
            if ((i == 0 && j == 0) || (i == m_n && j == m_n) || (i == 0 && j == m_n) || (i == m_n && j == 0))//углы
              return 3;
            else
              return 5;
        }
        return 8;//центр
    };*/

    auto Lambda_ValidCoord = [=](int i, int j) -> bool
    {
        return i >= 0 && j >= 0 && i < m_n && j < m_n;
    };

   /* for (int i = 0; i < m_n; ++i)           //Проставление вероятности 0 по всему полю
        for (int j = 0; j < m_n; ++j)
            verDot[i][j] = 0;*/

    //вероятность на всем поле
 /*   for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
        {

            if(!(field->Dot_isOpen(i,j)) && field->Dot_isFlag(i,j) == notF)
            {
                bool oneS = true;
                auto LambdaO = [m_n = this->m_n](int i, int j) -> bool
                {
                    return i >= 0 && j >= 0 && i < m_n && j < m_n;
                };
                auto LambdaF = [&](int i, int j, int x, int y)
                {
                    if(field->Dot_isOpen(i,j))
                    {
                        if(verDot[i][j] > 0 && verDot[i][j] < 10)
                        {
                            if(oneS)
                            {
                                verDot[x][y] = 0;
                                oneS = false;
                            }
                            verDot[x][y] += 100;
                        }
                    }
                    else
                    {
                        if(oneS)
                        {
                            verDot[x][y] = 0;
                            oneS = false;
                        }
                        verDot[x][y]+=100;

                    }
                };
                if (LambdaO(i - 1, j - 1))     LambdaF(i - 1, j - 1,i,j);
                if (LambdaO(i - 1, j))         LambdaF(i - 1, j,i,j);
                if (LambdaO(i - 1, j + 1))     LambdaF(i - 1, j + 1,i,j);
                if (LambdaO(i, j - 1))         LambdaF(i, j - 1,i,j);
                if (LambdaO(i, j + 1))         LambdaF(i, j + 1,i,j);
                if (LambdaO(i + 1, j - 1))     LambdaF(i + 1, j - 1,i,j);
                if (LambdaO(i + 1, j))         LambdaF(i + 1, j,i,j);
                if (LambdaO(i + 1, j + 1))     LambdaF(i + 1, j + 1,i,j);
            }
        }

    for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
        {
            if(i == 0 || j == 0 || i == (m_n-1) || j == (m_n-1))
            {
                if ((i == 0 && j == 0) || (i == (m_n-1) && j == (m_n-1)) ||
                    (i == 0 && j == (m_n-1)) || (i == (m_n-1) && j == 0))//углы
                  verDot[i][j] += 500;
                else
                  verDot[i][j] += 300;
            }
            if(field->Dot_isOpen(i,j))
                verDot[i][j] = field->Dot_isValue(i,j);
            if(field->Dot_isFlag(i,j))
                verDot[i][j] = 65535;
        }
*/
    //инфа сотка бомба
    for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
        {
            if(field->Dot_isOpen(i,j)  &&  field->Dot_isValue(i,j) != 0)
            {
                //подсчет флагов
                int tmpZnach = 0;
                auto LambdaF1 = [&](int i, int j)
                {
                    if(field->Dot_isFlag(i,j) == flagF)
                        tmpZnach++;

                };
                if (Lambda_ValidCoord(i - 1, j - 1))     LambdaF1(i - 1, j - 1);
                if (Lambda_ValidCoord(i - 1, j))         LambdaF1(i - 1, j);
                if (Lambda_ValidCoord(i - 1, j + 1))     LambdaF1(i - 1, j + 1);
                if (Lambda_ValidCoord(i, j - 1))         LambdaF1(i, j - 1);
                if (Lambda_ValidCoord(i, j + 1))         LambdaF1(i, j + 1);
                if (Lambda_ValidCoord(i + 1, j - 1))     LambdaF1(i + 1, j - 1);
                if (Lambda_ValidCoord(i + 1, j))         LambdaF1(i + 1, j);
                if (Lambda_ValidCoord(i + 1, j + 1))     LambdaF1(i + 1, j + 1);

                //подсчет закрытых клеток
                int i_c = 0, j_c = 0, c_c = 0;
                auto LambdaF2 = [&](int i, int j)
                {
                    if(!(field->Dot_isOpen(i,j)) && field->Dot_isFlag(i,j) == notF)
                    {
                        c_c++;
                        i_c = i;
                        j_c = j;
                    }

                };
                if (Lambda_ValidCoord(i - 1, j - 1))     LambdaF2(i - 1, j - 1);
                if (Lambda_ValidCoord(i - 1, j))         LambdaF2(i - 1, j);
                if (Lambda_ValidCoord(i - 1, j + 1))     LambdaF2(i - 1, j + 1);
                if (Lambda_ValidCoord(i, j - 1))         LambdaF2(i, j - 1);
                if (Lambda_ValidCoord(i, j + 1))         LambdaF2(i, j + 1);
                if (Lambda_ValidCoord(i + 1, j - 1))     LambdaF2(i + 1, j - 1);
                if (Lambda_ValidCoord(i + 1, j))         LambdaF2(i + 1, j);
                if (Lambda_ValidCoord(i + 1, j + 1))     LambdaF2(i + 1, j + 1);

                if(c_c >= 1 &&  ((field->Dot_isValue(i,j) - tmpZnach) == c_c))
                {
                    //инфа сотка бомба
                    qDebug() << "Flag:  " << i<< j;
                    field->Dot_VirtualEvent(i_c,j_c, rightV);
                    return;
                }
                else
                {
                    if(c_c >= 1 &&  field->Dot_isValue(i,j) == tmpZnach)
                    {
                        //инфа сотка пустая клетка
                        qDebug() << "Click: " << i<< j << " /top";
                        field->Dot_VirtualEvent(i_c,j_c, leftV);
                        return;
                    }
                }
                //qDebug() << "\n\r";
            }
        }
    qDebug() << "Click: ";
    {
        int j_t;
        int i_t;

        do
        {
            j_t = qrand() % m_n;
            i_t = qrand() % m_n;

        }
        while(field->Dot_isFlag(i_t,j_t) || field->Dot_isOpen(i_t,j_t));

        qDebug() << "Click: " << i_t << j_t << " /rand";
        field->Dot_VirtualEvent(i_t, j_t, leftV);
        return;
    }
    //верятность вокруг флага
 /*  for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
        {
            if(!(field->Dot_isOpen(i,j)))
            {
                if(field->Dot_isFlag(i,j) == flagF)
                {

                    auto LambdaF = [&](int i, int j)
                    {
                        if(verDot[i][j] < 10 && field->Dot_isOpen(i,j))
                            verDot[i][j]  -= 1;
                        if(verDot[i][j] > 100 && !field->Dot_isOpen(i,j))
                        {
                            if(i == 0 || j == 0 || i == (m_n-1) || j == (m_n-1))
                            {
                                if ((i == 0 && j == 0) || (i == (m_n-1) && j == (m_n-1)) || (i == 0 && j == (m_n-1)) || (i == (m_n-1) && j == 0))//углы
                                  verDot[i][j] -= 266;
                                else
                                  verDot[i][j] -= 160;
                            }

                            verDot[i][j]  -= 100;
                        }
                    };
                    if (Lambda_ValidCoord(i - 1, j - 1))     LambdaF(i - 1, j - 1);
                    if (Lambda_ValidCoord(i - 1, j))         LambdaF(i - 1, j);
                    if (Lambda_ValidCoord(i - 1, j + 1))     LambdaF(i - 1, j + 1);
                    if (Lambda_ValidCoord(i, j - 1))         LambdaF(i, j - 1);
                    if (Lambda_ValidCoord(i, j + 1))         LambdaF(i, j + 1);
                    if (Lambda_ValidCoord(i + 1, j - 1))     LambdaF(i + 1, j - 1);
                    if (Lambda_ValidCoord(i + 1, j))         LambdaF(i + 1, j);
                    if (Lambda_ValidCoord(i + 1, j + 1))     LambdaF(i + 1, j + 1);

                }
            }
        }*/

    //отчет
    for (int i = 0; i < m_n; ++i)
    {
        QString a;
        for (int j = 0; j < m_n; ++j)
            a += ' ' + QString::number(verDot[i][j]);
        qDebug() << a;
    }
    qDebug() << "\n\r";


    //проклик
    //прокликивает клетки нулевой вероятности если они закрыты
  /*  for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
            if(verDot[i][j] <= 0 && !(field->Dot_isOpen(i,j)) && field->Dot_isFlag(i,j) == notF)
            {
                qDebug() << "Click: " << i<< j << " /zero";
                field->Dot_VirtualEvent(i,j, leftV);
                return;
            }*/

    qDebug() << "\n\r";
    //ищет min на поле
/*    int i_1 = 0;
    int j_1 = 0;
    int verDot_1 = 655353;
    for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
            if(verDot[i][j] < verDot_1 && verDot[i][j] >= 100 && field->Dot_isFlag(i,j) == notF && !(field->Dot_isOpen(i,j)))
            {
                verDot_1 = verDot[i][j];
                i_1 = i;
                j_1 = j;
            }
    qDebug() << "min a: " << i_1 << j_1 << verDot_1;

    //ищет max на поле
    int i_2 = 0;
    int j_2 = 0;
    int verDot_2 = -65535;
    for (int i = 0; i < m_n; ++i)
        for (int j = 0; j < m_n; ++j)
            if(verDot[i][j] > verDot_2 && verDot[i][j] >= 100  && field->Dot_isFlag(i,j) == notF && !(field->Dot_isOpen(i,j)))
            {
                verDot_2 = verDot[i][j];
                i_2 = i;
                j_2 = j;
            }
    qDebug() << "max a: " << i_2 << j_2 << verDot_2;

    //ищет min в секторе max
    int i_3 = i_2;
    int j_3 = j_2;
    int verDot_3 = verDot_2;
    for (int i = (i_2 > 0? i_2-1:j_2); i < (i_2 < m_n-1? i_2+1+1:i_2+1); ++i)
    {
        //QString a;
        for (int j = (j_2 > 0? j_2-1:j_2); j < (j_2 < m_n-1? j_2+1+1:j_2+1); ++j)
        {
            if(verDot[i][j] < verDot_3 && verDot[i][j] >= 100  && field->Dot_isFlag(i,j) == notF && !(field->Dot_isOpen(i,j)))
            {
                verDot_3 = verDot[i][j];
                i_3 = i;
                j_3 = j;
            }
            //a += ' ' + QString::number(verDot[i][j]);
        }
        //qDebug() << a;
    }
    qDebug() << "min s: " << i_3 << j_3 << verDot_3;


    //принимает решение
    if(( i_2 == i_3 &&  j_2 == j_3) || (i_1 == 0 && j_1 == 0 && verDot_1 != 800))
    {
        int j_t;
        int i_t;

        do
        {
            j_t = qrand() % m_n;
            i_t = qrand() % m_n;

        }
        while(field->Dot_isFlag(i_t,j_t) || field->Dot_isOpen(i_t,j_t));

        qDebug() << "Click: " << i_t << j_t << " /rand";
        field->Dot_VirtualEvent(i_t, j_t, leftV);
        return;
    }

    if(verDot_3 >= 600 //если min слишком велик
        || (i_3 == i_2 && j_3 == j_2) //max и min сектора равны
            )
    {
        qDebug() << "Click: " << i_1<< j_1 << " /min a";
        field->Dot_VirtualEvent(i_1, j_1, leftV);
        return;
    }

    qDebug() << "Click: " << i_3 << j_3 << " /min s";
    field->Dot_VirtualEvent(i_3, j_3, leftV);*/
    return;
}
