#pragma once

#ifndef _arithmetic_H_
#define _arithmetic_H_

#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

//1 класс чисел - его задача - получить строку и превратить в число
//Колосова
//int isdigit( int character );
//double atof(const char *str)
class TNumber
{
    double num;
public:

    TNumber(double _num)
    {
        num = _num;
    }


    TNumber(char* s)
    {
        bool isNum = false;
        int i = 0;
        while (isdigit(s[i]))
            i++;
        if (s[i] != 0) throw - 1;
        num = atof(s);
    }
    double getNum()
    {
        return num;
    }
};

class TOperation
{
private:
    char znak;
public:
    TOperation(char _znak)
    {
        if (znak != '+' || znak != '-')
            throw "exception";
        znak = _znak;
    }
    TNumber Calculation(TNumber& a, TNumber& b)
    {
        if (znak == '+')
        {
            TNumber res(a.getNum() + b.getNum());
            return res;
        }
        if (znak == '-')
        {
            TNumber res(a.getNum() - b.getNum());
            return res;
        }
    }
};

class TArithmetic
{

    char** Razbienie(char* s, int& n);//разбивает входную строку на лексемы

public:
    double Calc(char* s);
};

char** TArithmetic::Razbienie(char* s, int& n)//разбивает входную строку на лексемы
{//
    int l = strlen(s);
    n = 0;
    for (int i = 0; i < l; i++)
    {
        if (isdigit(s[i]) == 0)
            n++;
    }
    n++;
    n = n * 2;
    char** res = new char* [n];
    int start = 0;
    int j = 0;
    for (int i = 0; i < l; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            int l2 = i - start + 1;
            res[j] = new char[l2];
            for (int k = 0; k < l2 - 1; k++)
            {
                res[j][k] = s[start + k];
            }
            res[j][l2 - 1] = 0;
            start = i + 1;
            j++;
            res[j] = new char[1];
            res[j][0] = s[i];
            j++;
        }
    }

    int l2 = l - start + 1;
    res[j] = new char[l2];
    for (int k = 0; k < l2 - 1; k++)
    {
        res[j][k] = s[start + k];
    }
    res[j][l2 - 1] = 0;

    return res;
}


double TArithmetic::Calc(char* s)
{///производит вычисления
    int n;
    char** c = Razbienie(s, n);
    TNumber res(c[0]);
    for (int i = 1; i < n; i += 2)
    {
        TNumber tmp(c[i + 1]);
        TOperation op(c[i]);
        res = op.Calculation(res, tmp);
    }

    return res.getNum();
}

#endif    //_arithmetic_H_