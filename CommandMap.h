//
// Created by roy on 12/18/18.
//

#ifndef PROJECTPART1_COMMANDMAP_H
#define PROJECTPART1_COMMANDMAP_H

#include <string>
#include <unordered_map>
using namespace std;

// enum for valid commands.
enum Commands {InValid, OpenDataServer, Connect, Var, Bind, Equal, While, If, Print, Sleep};

class CommandMap {
    // initialize the map of the commands.
    unordered_map<string,Commands> commands = {{"openDataServer" ,OpenDataServer}, {"connect" ,Connect},
                                 {"var" ,Var}, {"bind" ,Bind}, {"=" ,Equal}, {"while" ,While},
                                 {"sleep" ,Sleep}, {"if" ,If}, {"print" ,Print}};

public:
    /**
     * This function checks if a given command string is valid in
     * command map, and returns the fitting command.
     * @param commandString given string to search in map.
     * @return command of the given string.
     */
    Commands getCommand(string const commandString) const {
        // if the key was not found in map, returns invalid command.
        if (commands.find(commandString) == commands.end()) {
            return InValid;
        }
        // else, returns the fitting command.
        else {
            return commands.at(commandString);
        }
    }
};

#endif //PROJECTPART1_COMMANDMAP_H
