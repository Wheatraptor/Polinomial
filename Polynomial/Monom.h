#pragma once

#ifndef _MONOM_H_
#define _MONOM_H_

#include "ListElem.h"

///k*x^a*y^b*z^c
class TMonom
{
protected:
    TMonom* next, * prev;
    double k;
    int a, b, c;
public:
    TMonom();
    TMonom(double k, int a, int b, int c);
    TMonom(const TMonom& _v);
    ~TMonom();
    TMonom* getNext();
    TMonom* getPrev();
    double getK() const;
    double getA() const;
    double getB() const;
    double getC() const;
    void setNext(TMonom* next);
    void setPrev(TMonom* prev);
    void setK(double _k);
    void setA(int _a);
    void setB(int _b);
    void setC(int _c);
    TMonom operator+(const TMonom& _v);
    TMonom operator-(const TMonom& _v);
    TMonom operator*(const TMonom& _v);
    TMonom& operator=(const TMonom& _v);
    bool operator>(const TMonom& _v);
    bool operator<(const TMonom& _v);
    bool operator==(const TMonom& _v);
    bool operator!=(const TMonom& _v);
    friend ostream& operator<<(ostream& ostr, const TMonom& _v);
    friend istream& operator>>(istream& istr, TMonom& _v);
};

TMonom::TMonom() : k(0), a(0), b(0), c(0) {}

TMonom::TMonom(double k, int a, int b, int c)
{
    this->k = k;
    this->a = a;
    this->b = b;
    this->c = c;
}


TMonom::TMonom(const TMonom& _v)
{
    k = _v.k;
    a = _v.k;
    b = _v.k;
    c = _v.k;
    next = _v.next;
    prev = _v.prev;
}

TMonom::~TMonom() {
    TMonom* tmp = this;
    TMonom* del = this;
    while (tmp->next != nullptr){
        del = tmp;
        tmp = tmp->getNext();
        delete del;
    }
}

TMonom* TMonom::getNext()
{
    return next;
}

TMonom* TMonom::getPrev()
{
    return prev;
}


double TMonom::getK() const
{
    return k;
}

double TMonom::getA() const
{
    return a;
}


double TMonom::getB() const
{
    return b;
}

double TMonom::getC() const
{
    return c;
}


void TMonom::setNext(TMonom* next)
{
    this->next = next;
}

void  TMonom::setPrev(TMonom* prev) 
{
    this->prev = prev;
}


void TMonom::setK(double _k)
{
    k = _k;
}


void TMonom::setA(int _a)
{
    a = _a;
}



void TMonom::setB(int _b)
{
    b = _b;
}



void TMonom::setC(int _c)
{
    c = _c;
}


TMonom  TMonom::operator+(const TMonom& _v)
{
    if (*this != _v)
        throw - 1;
    TMonom res(*this);
    res.k += _v.k;
    return res;
}


TMonom TMonom::operator-(const TMonom& _v)
{
    if (*this != _v)
        throw - 1;
    TMonom temp(*this);
    temp.k = k - _v.k;
    return temp;
}


TMonom TMonom::operator*(const TMonom& _v)
{
    if (*this != _v)
        throw - 1;
    TMonom res(*this);
    res.k *= _v.k;
    res.a += _v.a;
    res.b += _v.b;
    res.c += _v.c;
    return res;
}


TMonom& TMonom::operator=(const TMonom& _v)
{
    k = _v.getK();
    a = _v.getK();
    b = _v.getK();
    c = _v.getK();
    next = _v.next;
    prev = _v.prev;
    return *this;
}


bool TMonom::operator>(const TMonom& _v)
{
    if (a > _v.a) return true;
    else if (a == _v.a);
    {
        if (b > _v.b)return true;
        else if (b == _v.b)
            if (c < _v.c)return true;
        return false;
    }
    return false;

}


bool TMonom::operator<(const TMonom& _v)
{
    if (a < _v.a) return true;
    else if (a == _v.a)
    {
        if (b < _v.b) return true;
        else if (b == _v.b)
            if (c < _v.c) return true;
        return false;
    }
    return false;
}


bool TMonom::operator==(const TMonom& _v)
{
    return  (a == _v.a && b == _v.b && c == _v.c);
}


bool TMonom::operator!=(const TMonom& _v)
{
    return !(*this == _v);
}

inline ostream& operator<<(ostream& ostr, const TMonom& _v)
{
    ostr << _v.getK() << "x^" << _v.getA() << "y^" << _v.getB() << "z^" << _v.getC();
    return ostr;
}

inline istream& operator>>(istream& istr, TMonom& _v)
{
    int a, b, c;
    double k;
    TMonom tmp;
    tmp.setNext(nullptr);
    istr >> k;
    tmp.setK(k);
    istr >> a;
    tmp.setA(a);
    istr >> b;
    tmp.setB(b);
    istr >> c;
    tmp.setC(c);
    _v = tmp;
    return istr;
}

#endif