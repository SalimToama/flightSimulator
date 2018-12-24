//
// Created by issa on 12/12/18.
//

#include "whileCommand.h"

int whileCommand::doCommand(vector<string> &text,int index) {
    iterator1++; // Now stands on expression part.
    vector<string> conditionVec, commandsVec;
    while (*iterator1 != "{") {
        conditionVec.push_back(*iterator1);
        iterator1++;
    }

    int braks = 0;
    iterator1++; // Now stands on commands.
    while (!(*iterator1 == "}" && braks == 0)) {
        if (*iterator1 == "{")
            braks++;
        if (*iterator1 == "}")
            braks--;
        commandsVec.push_back(*iterator1);
        iterator1++;
    }

    while (condition(conditionVec)){
        Parser pars(commandsVec);
        pars.createCommand();
    }
    iterator1++;
}

whileCommand::whileCommand(vector<string>::iterator &iterator1): iterator1(iterator1) {}
