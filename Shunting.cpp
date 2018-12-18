#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

class Shunting {
    /*
    static string toPostFix(string st) {
        stack<string> stack;
        string output;

    } */
    static bool isLeftParen(string st) {
        return st.at(0) == '(';
    }
    static bool isRightParen(string st) {
        return st.at(0) == ')';
    }
    static bool isPair(string left, string right) {

    }
    static bool isOperator(string st) {
        char ch = st.at(0);
        switch (ch){
            case '+':
                return true;
                break;
            case '-':
                return true;
                break;
            case '*':
                return true;
                break;
            case '/':
                return true;
                break;
            case '%':
                return true;
                break;
            default:
                return false;
                break;
        }
    }
    static bool isNumber(string st) {
        for (int i = 0; i < st.length(); i++) {
            if (st.at(i) < '0' || st.at(i) > '9')
                return false;
        }
    }
    int precedence(string op) {
        switch (op.at(0)) {
            case '(':
                return 0;
                break;
            case '+':
                return 1;
                break;
            case '-':
                return 1;
                break;
            case '*':
                return 2;
                break;
            case '/':
                return 2;
                break;
            case '%':
                return 2;
                break;
            case ')':
                return 3;
                break;
            default:
                return -1;
                break;
        }
    }
    static string toString(int num) {
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    static void spacer(string &st) {
        for (int i = 0; i < st.length(); i++) {
            // Spaces.
            if (st[i] == ' ')
                continue;
            // Operators.
            if (isOperator("" + st[i])) {
                if (st[i + 1] != ' ' && i + 1 != st.length())
                {
                    st.replace(i + 1, 1, " " + st[i + 1]);
                    i += 2;
                }
                continue;
            }
            // Numbers.
            if (isNumber("" + st[i])) {
                while (i != st.length()) {
                    i++;
                    if (!isNumber("" + st[i])) {
                        if (st[i] != ' ')
                        {
                            st.replace(i, 1, " " + st[i]);
                            i += 2;
                        }
                        break;
                    }
                }
                continue;
            }
                // Vars.
            else {
                while (i != st.length()) {
                    i++;
                    if (!isOperator("" + st[i])) {
                        if (st[i] != ' ') {
                            st.replace(i, 1, " " + st[i]);
                            i += 2;
                        }
                        break;
                    }
                }
                continue;
            }
        }
        return;
    }
    int main() {
        string husni = "12/4569-husnui3 +    12";
        //12 / 4569 - husnui3 +     12
        cout << husni << endl;
        return 1;
    }
};//
// Created by jokereed on 12/17/18.
//

#include "Shunting.h"
