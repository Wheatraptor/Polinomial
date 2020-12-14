#pragma once
#ifndef _List_
#define _List_

#include "ListElem.h"
#include <cmath>

template <class T>
class TList
{
protected:
    TListElem<T>* root;
    TListElem<T>* end;
    int count;
public:
    TList();
    TList(TList<T>& _v);
    ~TList();

    TList<T>& operator =(TList<T>& _v);

    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TListElem<T>* e, T d);

    bool IsEmpty(void) const;

    bool IsFull(void) const;

    TListElem<T>* GetFirst();
    TListElem<T>* GetLast();

    void DelFirst();
    void DelLast();
    void Del(TListElem<T>* e);

    T geometricMean();
    T arithmeticMean();
    int lessThan(int a);
    int CountOfEvenElems();
    TList<T> ElemsFromAToB(int a, int b);
    TList<T> firstNElems(int count);
    TList<T> findElem(int N);

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TList<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TList<T1>& A);


};


template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1>& A) {

    TListElem<T1>* i = A.root;

    while (i != 0)
    {
        ostr << *i << endl;
        i = i->GetNext();
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1>& A) {
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        A.InsLast(d);
    }
    return istr;
}

template<class T>
inline TList<T>::TList()
{
    root = 0;
    end = 0;
    count = 0;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
    count = _v.count;

    TListElem<T>* i = _v.root;
    TListElem<T>* j = this->root;
    TListElem<T>* p = 0;

    while (i != 0)
    {
        j = new TListElem<T>(*i);
        j->SetNext(0);
        if (p != 0)
        {
            p->SetNext(j);
            j->SetPrev(p);
        }

        p = j;

        if (root == 0)
            root = j;

        end = j;

        i = i->next();
    }
}
template <class T>
TList<T>::~TList()
{
    if (this->root != 0)
    {
        TListElem<T>* i = this->root;
        TListElem<T>* p = 0;

        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }

        this->root = 0;
        this->end = 0;
        count = 0;
    }
}

template <class T>
TList<T>& TList<T>::operator =(TList<T>& _v)
{
    if (this == &_v)
        return *this;

    if (this->root != 0)
    {
        TListElem<T>* i = this->root;
        TListElem<T>* p = 0;

        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }

        this->root = 0;
        this->end = 0;
        count = 0;
    }

    count = _v.count;

    TListElem<T>* j = this->root;
    TListElem<T>* p = 0;

    while (i != 0)
    {
        j = new TListElem<T>(*i);
        j->SetNext(0);
        if (p != 0)
        {
            p->SetNext(j);
            j->SetPrev(p);
        }

        p = j;

        if (root == 0)
            root = j;

        end = j;

        i = i->next();
    }

}

template<class T>
inline void TList<T>::InsFirst(T d)
{
    TListElem<T>* tmp = new TListElem<T>(d);
    tmp->SetNext(root);
    root = tmp;
    if (end == 0)
        end = tmp;
    count++;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
    TListElem<T>* tmp = new TListElem<T>(d);
    end->SetNext(tmp);
    end = tmp;
    if (root == 0)
        root = tmp;
    count++;
}

template<class T>
inline void TList<T>::Ins(TListElem<T>* e, T d)
{
    TListElem<T>* tmp = new TListElem<T>(d);
    tmp->SetNext(e->GetNext());
    tmp->SetPrev(e);
    e->GetNext()->SetPrev(tmp);
    e->SetNext(tmp);
    count++;
}

template<class T>
inline bool TList<T>::IsEmpty(void) const
{
    return count == 0;
}

template<class T>
inline bool TList<T>::IsFull(void) const
{
    try
    {
        TListElem<T>* tmp = new TListElem<T>(0);
        delete tmp;
        return false;
    }
    catch (...)
    {
        return true;
    }

}


template<class T>
inline TListElem<T>* TList<T>::GetFirst()
{
    return root;
}

template<class T>
inline TListElem<T>* TList<T>::GetLast()
{
    return end;
}

template<class T>
inline void TList<T>::DelFirst()
{
    TListElem<T>* i = root;
    root = root->GetNext();
    count--;
    delete i;
}

template<class T>
inline void TList<T>::DelLast()
{
    TListElem<T>* i = end;
    end = end->GetPrev();
    count--;
    delete i;
}

template<class T>
inline void TList<T>::Del(TListElem<T>* e)
{
    e->GetPrev()->SetNext(e->GetNext());
    e->GetNext()->SetPrev(e->GetPrev());

    count--;
    delete e;

}

template<class T>
inline int TList<T>::GetCount()
{
    return count;
}


#endif
