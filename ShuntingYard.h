//
// Created by issa on 12/13/18.
//
#pragma once

#ifndef PROJECT_SHUNTINGYARD_H
#define PROJECT_SHUNTINGYARD_H
#include <vector>
#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
#include "Expression.h"
#include "Expression.h"
#include "Plus.h"
#include "Number.h"
#include "Minus.h"
#include "Div.h"
#include "Mul.h"

using namespace std;
class ShuntingYard {
public:
    static bool isLeftParen(string st);
    static bool isRightParen(string st);
    static Expression* calc(Expression *left, Expression *right, string st);
    static bool isOperator(string st);
    static bool isNumber(string st);
    static int precedence(string st);
    static string toString(int num);
    static vector<string> toPostfix(vector<string> ex);
    static void stackOperations(string op, vector<string> &ex, stack<string> &stack1, bool neg);
    static Expression* evaluate(vector<string> ex);
    static bool moreThan2(stack<Expression*> s);
};


#endif //PROJECT_SHUNTINGYARD_H