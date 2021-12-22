﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) 
    : Size{s}, StartIndex{si}
{
    if ((Size <= 0) || (Size > MAX_VECTOR_SIZE))
        throw Size;
    if ((StartIndex < 0) || (StartIndex > MAX_VECTOR_SIZE))
        throw StartIndex;

    pVector = new ValType[Size];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
    : Size{v.Size}, StartIndex{v.StartIndex}
{
    pVector = new ValType[Size];
    for (int i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if (pos - StartIndex < 0 || pos - StartIndex >= Size)
        throw pos;

    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (v.Size != Size)
        return false;

    for (int i = 0; i < Size; ++i)
        if (pVector[i] != v.pVector[i])
            return false;

    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this != &v) {
        if (Size != v.Size) {
            Size = v.Size;
            StartIndex = v.StartIndex;
            delete[] pVector;
            pVector = new ValType[v.Size];
        }

        for (int i = 0; i < Size; i++) {
            pVector[i] = v.pVector[i];
        }
    }

    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] + val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] - val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] * val;
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw Size;

    TVector<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] + v.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw Size;

    TVector<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] - v.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw Size;

    ValType sum = pVector[0] * v.pVector[0];
    for (int i = 1; i < Size; i++)
        sum = sum + pVector[i] * v.pVector[i];
    return sum;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  TMatrix operator*(const TMatrix& mt);     // Умножение

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s)
    : TVector<TVector<ValType> >(s)
{
    if (Size <= 0 || Size > MAX_MATRIX_SIZE)
        throw Size;

    for (int i = 0; i < Size; ++i) {
        TVector<ValType> v(Size - i, i);
        pVector[i] = v;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt)
    : TVector<TVector<ValType> >(mt) {}  // Явно вызываем кон-р коп-я вектора, взаместо кон-ра коп-я по умолчанию

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt)
    : TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (Size != mt.Size)
        return false;

    for (int i = 0; i < Size; i++) 
        if (pVector[i] != mt.pVector[i])
            return false;

    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this != &mt) {
        if (Size != mt.Size) {
            delete[] pVector;
            Size = mt.Size;
            pVector = new TVector<ValType>[Size];
        }

        for (int i = 0; i < Size; i++) {
            pVector[i] = mt.pVector[i];
        }
    }

    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw Size;

    TMatrix<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] + mt.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw Size;

    TMatrix<ValType> tmp(Size);
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = pVector[i] - mt.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/


// Умножение
template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix<ValType>& mt)
{
    if (Size != mt.Size)
        throw Size;

    TMatrix<ValType> tmpM(Size);
    TVector<ValType> tmpV1(Size), tmpV2(Size);

    for (int i = 0; i < Size; ++i) {
        for (int j = i; j < Size; ++j)   // переписываем в вектор tmpV1 строку первой матрицы
            tmpV1[j] = pVector[i][j];

        for (int k = 0; k < Size; k++)  // зануляем tmpV2
            tmpV2[k] = 0;

        for (int j = i; j < Size; ++j) {
             
            for (int k = 0; k <= j; ++k)    // переписываем в вектор tmpV2 столбец второй матрицы, оставляя нули на пробелах
                tmpV2[k] = mt.pVector[k][j];

            tmpM[i][j] = tmpV1 * tmpV2;
        }

        tmpV1[i] = 0; // дописываем ноль к следующей строке
    }

    return tmpM;
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
