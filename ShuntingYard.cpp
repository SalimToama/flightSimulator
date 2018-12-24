
#include "ShuntingYard.h"


bool ShuntingYard::isLeftParen(string st) {
    char ch = st[0];
    return ch == '(';
}

bool ShuntingYard::isRightParen(string st) {
    char ch = st[0];
    return ch == ')';
}

Expression *ShuntingYard::calc(Expression *left, Expression *right, string st) {
    char op = st[0];
    switch (op) {
        case '+':
            return new Plus(left, right);
        case '-':
            return new Minus(left, right);
        case '*':
            return new Mul(left, right);
        case '/':
            return new Div(left, right);
        default:
            throw "Invalid Operator.";
    }
}

bool ShuntingYard::isOperator(string st) {
    if (st.length() != 1)
        return false;
    char ch = st[0];
    switch (ch) {
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        case '$':
            return true;
        default:
            return false;
    }
}

bool ShuntingYard::isNumber(string st) {
    double num;
    try {
        num = stoi(st);
        return true;
    }
    catch (exception e){
        return false;
    }
}

int ShuntingYard::precedence(string st) {
    char op = st[0];
    switch (op) {
        case '$':
            return 5;
        case '(':
            return 0;
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case ')':
            return 3;
        default:
            return -1;
    }
}

string ShuntingYard::toString(int num) {
    ostringstream ss;
    ss << num;
    return ss.str();
}

void ShuntingYard::stackOperations(string op, vector<string> &ex, stack<string> &stack1, bool neg) {
    if (op == "-" && neg)
        op = "$";
    // - ((x + y) / z)
    string popped;
    int pre = precedence(op);
    // "("
    if (pre == 0) {
        stack1.push(op);
        return;
    }
    // ")"
    if (pre == 3) {
        while (!stack1.empty()) {
            popped = stack1.top();
            stack1.pop();
            if (popped == "(")
                return;
            ex.push_back(popped);
        }
        throw "Invalid Expression.";
        // + , - , * , /
    } else {
        while (!stack1.empty()) {
            if (precedence(stack1.top()) < precedence(op)) {
                // found the proper place.
                break;
            }
            popped = stack1.top();
            stack1.pop();
            ex.push_back(popped);
        }
        stack1.push(op);
        return;
    }
}

vector<string> ShuntingYard::toPostfix(vector<string> ex) {
    stack<string> stack1;
    vector<string> postfix;
    bool neg = true;
    for (vector<string>::iterator itemp = ex.begin(); itemp != ex.end(); itemp++) {
        // Numbers.
        if (isNumber(*itemp)) {
            postfix.push_back(*itemp);
            neg = false;
            continue;
        }
        // Operators.
        if (isOperator(*itemp) || isLeftParen(*itemp) || isRightParen(*itemp)) {
            stackOperations(*itemp, postfix, stack1, neg);
            if (isRightParen(*itemp))
                neg = false;
            else
                neg = true;
        }
    }
    while (!stack1.empty()) {
        postfix.push_back(stack1.top());
        stack1.pop();
    }
    return postfix;
}

bool ShuntingYard::moreThan2(stack<Expression *> s) {
    int counter = 0;
    while (!s.empty() && counter != 2) {
        s.pop();
        counter++;
    }
    return counter == 2;
}

Expression *ShuntingYard::evaluate(vector<string> ex) {
    ex = toPostfix(ex);
    stack<Expression *> stack1;
    for (vector<string>::iterator itemp = ex.begin(); itemp != ex.end(); itemp++) {
        // Numbers.
        if (isNumber(*itemp)) {
            stack1.push(new Number(stoi(*itemp)));
            continue;
        }
        // Operators.
        if (isOperator(*itemp)) {
            if (!moreThan2(stack1) && *itemp != "$")
                throw "Invalid Number of Elements.";
            Expression *right = stack1.top();
            stack1.pop();
            Expression *left;
            if (*itemp != "$") {
                left = stack1.top();
                stack1.pop();
            } else {
                left = new Number(0);
                *itemp = "-";
            }

            stack1.push(calc(left, right, *itemp));
        }
    }
    if (stack1.empty())
        throw "Invalid Number of Elements.";
    cout << stack1.top()->calculate() << endl;

    return stack1.top();
}