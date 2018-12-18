#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
using namespace std;


class Shunting {
public:
    static bool isLeftParen(char ch) {
        return ch == '(';
    }

    static bool isRightParen(char ch) {
        return ch == ')';
    }

    static double calc(double left, double right, char op) {
        switch (op) {
            case '+':
                return left + right;
            case '-':
                return left - right;
            case '*':
                return left * right;
            case '/':
                return left / right;
            default:
                throw "Invalid Operator.";
        }
    }

    static bool isOperator(char ch) {
        switch (ch) {
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
            default:
                return false;
                break;
        }
    }

    static bool isNumber(char ch) {
        if (ch < '0' || ch > '9') {
            return false;
        }
        return true;
    }

    static int precedence(char op) {
        switch (op) {
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
            if (st[i] == ' ') {
                continue;
            }
            // Operators.
            if (isOperator(st[i]) || isLeftParen(st[i]) || isRightParen(st[i])) {
                if (st.length() != i + 1 && ' ' != st[i + 1]) {
                    string rep = " ";
                    rep.append(1, st[i + 1]);
                    st.replace(i + 1, 1, rep);
                }
                continue;
            }
            // Numbers.
            if (isNumber(st[i])) {
                while (++i != st.length()) {
                    if (!isNumber(st[i])) {
                        if (st[i] != ' ') {
                            string rep = " ";
                            rep.append(1, st[i]);
                            st.replace(i, 1, rep);
                        }
                        break;
                    }
                }
                continue;
            }
                // Vars.
            else {
                while (++i != st.length()) {
                    if (isOperator(st[i]) || st[i] == ' ') {
                        if (st[i] != ' ') {
                            string rep = " ";
                            rep.append(1, st[i]);
                            st.replace(i, 1, rep);
                        }
                        break;
                    }
                }
                continue;
            }
        }
        return;
    }

    static string toPostfix(string str) {
        stack<char> stack1;
        string output = "";
        for (int i = 0; i < str.length(); i++) {
            // Spaces.
            if (str[i] == ' ')
                continue;
            // Numbers.
            if (isNumber(str[i])) {
                if (output != "")
                    output.append(" ");
                while (i != str.length() && str[i] != ' ') {
                    output.append(1, str[i]);
                    i++;
                }
                i--;
                continue;
            }
            // Operators.
            if (isOperator(str[i]) || isLeftParen(str[i]) || isRightParen(str[i]))
                stackOperations(str[i], output, stack1);

        }
        while (!stack1.empty()){
            ostringstream ss;
            ss << stack1.top();
            stack1.pop();
            if (output != "")
                output.append(" ");
            output.append(ss.str());
        }
        return output;
    }

    static void stackOperations(char op, string &output, stack<char> &stack1) {
        char popped;
        ostringstream ss;
        ss << output;
        int pre = precedence(op);
        if (pre == 0) {
            stack1.push(op);
            return;
        }
        if (pre == 3) {
            while (!stack1.empty()) {
                popped = stack1.top();
                stack1.pop();
                if (popped == '('){
                    output = ss.str();
                    return;
                }
                if (ss.str() != "")
                    ss << " ";
                ss << popped;
            }
                throw "Invalid Expression.";
        } else {
            while (!stack1.empty()) {
                if (precedence(stack1.top()) < precedence(op)) {
                    // found the proper place.
                    break;
                }
                popped = stack1.top();
                stack1.pop();
                ss << " " << popped;
            }
            stack1.push(op);
            output = ss.str();
            return;
        }
    }
    static int evaluate(string str){
        stack<double> stack1;
        for (int i = 0; i < str.length(); i++){
            // Spaces.
            if (str[i] == ' ')
                continue;
            // Numbers.
            if (isNumber(str[i])){
                string num = "";
                while (i != str.length() && str[i] != ' ') {
                    ostringstream ss;
                    ss << str[i];
                    num.append(ss.str());
                    i++;
                }
                stack1.push(stoi(num));
                i--;
                continue;
            }
            // Operators.
            if (isOperator(str[i])){
                if (!moreThan2(stack1))
                    throw "Invalid Number of Elements.";
                double right = stack1.top();
                stack1.pop();
                double left = stack1.top();
                stack1.pop();
                stack1.push(calc(left, right, str[i]));
            }
        }
        if (stack1.empty())
            throw "Invalid Number of Elements.";
        return stack1.top();
    }
    static bool moreThan2(stack<double> s){
        int counter = 0;
        while (!s.empty() && counter != 2){
            s.pop();
            counter++;
        }
        return counter == 2;
    }
};

int main() {
    string husni = "4 * (30 - (10 - 2) *3)s";
    cout << husni << endl;
    Shunting::spacer(husni);
    husni = Shunting::toPostfix(husni);
    cout << husni << endl;
    cout << Shunting::evaluate(husni) << endl;
    return 1;
}
