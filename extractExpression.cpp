//
// Created by issa on 12/18/18.
//

#include "extractExpression.h"

Expression *extractExpression::extract(vector<string>::iterator &it, vector<string> &vec) {
    vector<string> ex;
    map<string,double > symbols = SymbolTable::instance()->getMap();
    int counter = 1;
    //vector<string>::iterator it = vec.begin();
    int brac = 0;
    while (it != vec.end()) {
        if (isCommand(*it))
            break;
        // Numbers.
        if (ShuntingYard::isNumber(*it)) {
            if (counter != 0) {
                ex.push_back(*it);
                if (brac == 0)
                    counter--;
                it++;
                continue;
            }
            break;
        }
        // Brackets.
        if (ShuntingYard::isRightParen(*it)) {
            brac--;
            if (brac == 0) {
                counter--;
            }
            ex.push_back(*it);
            it++;
            continue;
        }
        if (ShuntingYard::isLeftParen(*it)) {
            if (counter == 0)
                break;
            brac++;
            ex.push_back(*it);
            it++;
            continue;
        }
        // Operators.
        if (ShuntingYard::isOperator(*it)) {
            if (!brac)
                counter++;
            ex.push_back(*it);
            it++;
            continue;
        }
            // Vars.
        else {
            if (counter) {
                ex.push_back(to_string(symbols[*it]));
                if (!brac)
                    counter--;
                it++;
                continue;
            }
            break;
        }
    }
    return ShuntingYard::evaluate(ex);
}

bool extractExpression::isCommand(string str) {
    if (str == "connect" || str == "var" || str == "openDataServer" || str == "print" || str == "sleep" ||
        str == "while"
        || str == "if") {
        return true;
    }
}