//
// Created by issa on 12/12/18.
//

#include "ifCommand.h"

int ifCommand::doCommand(vector<string> &text,int index) {
    iterator1++; // Now stands on expression part.
    vector<string> conditionVec, commandsVec;
    while (*iterator1++ != "{")
        conditionVec.push_back(*iterator1);
    iterator1++; // Now stands on commands.
    int braks = 0;
    while (!(*iterator1 == "}" && braks == 0)) {
        if (*iterator1 == "{")
            braks++;
        if (*iterator1 == "}")
            braks--;
        commandsVec.push_back(*iterator1);
    }

    if (condition(conditionVec)){
        Parser pars(commandsVec);
        pars.createCommand();
    }
    iterator1++;
}

ifCommand::ifCommand(vector<string>::iterator &iterator1): iterator1(iterator1) {}
