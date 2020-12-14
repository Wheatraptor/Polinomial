
#ifndef _Polinomial_H_
#define _Polinomial_H_

#include "Monom.h"


class TPolinomial
{
protected:
    TMonom* monom;

public:
    TPolinomial()
    {
        monom = 0;
    }
    TPolinomial(TPolinomial& _v);
    ~TPolinomial();
    TMonom* getMonom();
    void setMonom(TMonom* _monom);
    TPolinomial& operator = (TPolinomial & _v);
    TPolinomial& operator += (TMonom & _v);
    //TPolinomial operator* (TPolinomial& _v);
    TPolinomial operator + (TPolinomial & _v);
    //TPolinomial operator - (TPolinomial & _v);
    friend ostream& operator<<(ostream& ostr, const TPolinomial& _v);
    friend istream& operator>>(istream& istr, TPolinomial& _v);
};


TPolinomial::TPolinomial(TPolinomial& _v)//Стеценко
{
    if (_v.monom == nullptr)
        monom = nullptr;
    else
    {
        monom = new TMonom(*_v.monom);
        TMonom* tmp = monom;
        TMonom* tmp2 = _v.monom;
        while (tmp2->getNext())
        {
            tmp->setNext(new TMonom(*(tmp2->getNext())));
            tmp = tmp->getNext();
            tmp2 = tmp2->getNext();
        }

    }
}


TPolinomial::~TPolinomial()//Ростов
{
    TMonom* tmp = monom;
    while (tmp != nullptr)
    {
        TMonom* copy = tmp;
        tmp = tmp->getNext();
        delete copy;
    }
    monom = nullptr;
}

TMonom* TPolinomial::getMonom() {
    return monom;
}

void TPolinomial::setMonom(TMonom* _monom) {
    monom = _monom;
}

TPolinomial& TPolinomial::operator = (TPolinomial& _v)//Бекетов
{
    if (monom != nullptr)
    {
        TMonom* tmp = monom;
        while (tmp != nullptr)
        {
            TMonom* copy = tmp;
            tmp = tmp->getNext();
            delete copy;
        }
        monom = nullptr;

        if (_v.monom == nullptr)
        {
            monom = nullptr;
        }
        else
        {
            monom = new TMonom(*_v.monom);
            TMonom* tmp = monom;
            TMonom* tmp2 = _v.monom;
            while (tmp2->getNext())
            {
                tmp->setNext(new TMonom(*(tmp2->getNext())));
                tmp = tmp->getNext();
                tmp2 = tmp2->getNext();
            }
        }
        return *this;
    }
}


TPolinomial& TPolinomial::operator += (TMonom & _v)
{
  TMonom* p = monom;
  if (monom != nullptr)
  {
    while (p->getNext() != 0)
    {
      if (*p == _v)
      {
        p->setK(p->getK() + _v.getK());
        return (*this);
      }
      else if (*p < _v)
      {
        TMonom* cop = new TMonom(_v);
        cop->setPrev(p->getPrev());
        cop->setNext(p);
        p->getPrev()->setNext(cop);
        p->setPrev(cop);
        return (*this);
      }
    }
    TMonom* cop = new TMonom(_v);
    cop->setPrev(p);
    p->setNext(cop);
    }
    else {
      monom = new TMonom(_v);
    }
    return (*this);
 }



//TPolinomial& TPolinomial::operator* (TPolinomial & _v)//Манухов
//{  //(a + b) * (c + d) = a*c + a*d + b*c + b*d
//  if (monom != nullptr && _v.monom != nullptr)
//  {
//    TPolinomial temp;
//    TMonom* tmp_0 = monom;
//    while (tmp_0 != nullptr)
//    {
//      TMonom* tmp_1 = _v.monom;
//      while (tmp_1 != nullptr)
//      {
//        temp.monom += (*tmp_0) * (*tmp_1);
//        tmp_1 = tmp_1->getNext();
//      }
//      tmp_0 = tmp_0->getNext();
//    }
//    return temp;
//  }
//  else
//  {
//    throw - 1;
//  }
//}


TPolinomial TPolinomial::operator + (TPolinomial & _v)//Калашников
{
  TMonom* tmp1 = monom;
  TMonom* tmp2 = _v.monom;
  TMonom* tmp3;
  TPolinomial res;
  if (monom != nullptr && _v.monom != nullptr)
  {
    if (*tmp1 > *tmp2)
      {
        tmp3 = tmp1;
        tmp1 = tmp1->getNext();
      }
    else
      {
        tmp3 = tmp2;
        tmp2 = tmp2->getNext();
      }
    res += *tmp3;
    tmp3 = res.monom;
    while (tmp1 != nullptr && tmp2 != nullptr)
    {
      if (*tmp1 == *tmp2)
      {
        tmp3->setNext(new TMonom(tmp1->getK() + tmp2->getK(), tmp1->getA(), tmp1->getB(), tmp1->getC()));
        tmp1 = tmp1->getNext();
        tmp2 = tmp2->getNext();
        tmp3 = tmp3->getNext();
      }
      else if (*tmp1 > *tmp2)
      {
        tmp3->setNext(new TMonom(*tmp1));
        tmp1 = tmp1->getNext();
        tmp3 = tmp3->getNext();
      }
      else if (*tmp1 < *tmp2)
      {
        tmp3->setNext(new TMonom(*tmp2));
        tmp2 = tmp2->getNext();
        tmp3 = tmp3->getNext();
      }
    }
    if (tmp1 != nullptr)
    {
      while (tmp1 != nullptr)
      {
        tmp3->setNext(new TMonom(*tmp1));
        tmp1 = tmp1->getNext();
        tmp3 = tmp3->getNext();
      }
    }
    if (tmp2 != nullptr)
    {
      while (tmp2 != nullptr)
      {
        tmp3->setNext(new TMonom(*tmp2));
        tmp2 = tmp1->getNext();
        tmp3 = tmp3->getNext();
      }
    }
  }
  return res;
}


inline ostream& operator<<(ostream& ostr, TPolinomial& _v)
{
    TPolinomial* tmp = new TPolinomial(_v);
    if (tmp->getMonom() != nullptr)    
        while (tmp->getMonom()->getNext() != nullptr) {
            ostr << *(tmp->getMonom()) << '+';
            tmp->setMonom(tmp->getMonom()->getNext());
        }
    return ostr;
}

inline istream& operator>>(istream& istr, TPolinomial& _v)
{
    TPolinomial tmp = _v;
    TMonom* tmp2;
    TMonom tmp3;
    int n;
    tmp2 = new TMonom();
    tmp.setMonom(tmp2);
    std::cout << "Input n: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        std::cout << "Input monom: ";
        cin >> tmp3;
        //tmp.setMonom(&tmp2);
        if (tmp2 == nullptr)
            tmp2 = new TMonom();
        *tmp2 = tmp3;
        tmp2->setNext(new TMonom());
        tmp2 = tmp2->getNext();
    }
    _v = tmp;
    return istr;
}

#endif    