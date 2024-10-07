// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v)//copy constructor
  {
      this->sz = v.sz;
      this->pMem = new T[sz];
      for (int i = 0; i < this->sz; i++) this->pMem[i] = v.pMem[i];
  }

  TDynamicVector(TDynamicVector&& v) noexcept//move constructor
  {
      this->sz = v.sz;
      this->pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }

  ~TDynamicVector()//destructor
  {
      delete[] pMem;
      sz = 0;
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) return *this;
      this->sz = v.sz;
      this->pMem = new T[sz];
      for (int i = 0; i < sz; i++) this->pMem[i] = v.pMem[i];
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this == &v) return *this;

      this->sz = v.sz;
      v.sz = 0;
      this->pMem = v.pMem;
      v.pMem = nullptr;

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  { 
      return this->sz;
  }
  const T& operator[](size_t ind) const
  {
      return this->sz;
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) throw "incorrect index";
      return this->ind;
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw "incorrect index";
      return this->ind;
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz) return false;
      for (int i = 0; i < this->sz; i++) if (this->pMem[i] != v.pMem[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !((*this) == v);
  }

  // скалярные операции
  TDynamicVector operator+(double val)
  {
      TDynamicVector curr(this->sz);
      for (int i = 0; i < curr.sz; i++) curr.pMem[i] = this->pMem[i] + val;
      return curr;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector curr(this->sz);
      curr = (*this) + (-val);
      return curr;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector curr(this->sz);
      for (int i = 0; i < curr.sz; i++) curr.pMem[i] = this->pMem[i] * val;
      return curr;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      TDynamicVector curr(this->sz);
      for (int i = 0; i < curr.sz; i++) curr.pMem[i] = this->pMem[i] + v.pMem[i];
      return curr;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      TDynamicVector curr(this->sz);
      for (int i = 0; i < curr.sz; i++) curr.pMem[i] = this->pMem[i] - v.pMem[i];
      return curr;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      T res = 0;
      for (int i = 0; i < this->sz; i++) res += this->pMem[i] * v.pMem[i];
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
