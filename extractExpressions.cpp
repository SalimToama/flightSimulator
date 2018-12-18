using namespace std;

#include <vector>
#include <string>
#include <list>
#include "shunting.cpp"

class ExtractExpressions {
public:
    static list<string> extract(vector<string> vec) {
        int counter = 1;
        list<string> ls;
        ostringstream ss;
        vector<string>::iterator it = vec.begin();
        int brac = 0;
        do {
            // Numbers.
            if (Shunting::isNumber(it->at(0))) {
                if (counter) {
                    ss << " " << *it;
                    if (!brac)
                        counter--;
                    continue;
                } else {
                    ls.push_back(ss.str());
                    ss.str(string());
                    ss << " " << *it;
                    continue;
                }
            }
            // Brackets.
            if (Shunting::isRightParen(it->at(0))) {
                counter--;
                brac--;
                ss << " " << *it;
                continue;
            }
            if (Shunting::isLeftParen(it->at(0))) {
                brac++;
                ss << " " << *it;
                continue;
            }
            // Operators.
            if (Shunting::isOperator(it->at(0))) {
                if (!brac)
                    counter++;
                ss << " " << *it;
                continue;
            }
            // Vars.
            else {
                if (counter) {
                    ss << " " << *it;
                    if (!brac)
                        counter--;
                    continue;
                } else {
                    ls.push_back(ss.str());
                    ss.str(string());
                    ss << " " << *it;
                    continue;
                }
            }
        } while (++it != vec.end());
        ls.push_back(ss.str());
        for (list<string>::iterator it = ls.begin(); it != ls.end(); it++)
            it->erase(0, 1);
        return ls;
    }
};

int main() {
    vector<string> vec = {"(", "4", "+", "5", ")", "+", "3", "12", "/", "3", "8 + Moti", "Salim"};
    list<string> exs = ExtractExpressions::extract(vec);
    for (list<string>::iterator it = exs.begin(); it != exs.end(); it++) {
        cout << *it << endl;
    }

}