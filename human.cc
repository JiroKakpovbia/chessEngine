#include <sstream>
#include <iostream>
#include "human.h"

std::vector<string> Human::getMove(Board &board) {
    string input;
    getline(cin, input);
    std::stringstream tokenize(input);
    std::vector<string> args;
    string arg;

    while (getline(tokenize, arg, ' ')) {
        args.push_back(arg);
    }
    
    return args;
}
