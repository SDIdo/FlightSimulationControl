//
// Created by roy on 12/21/18.
//

#ifndef PROJECTPART1_SYMBOLTABLE_H
#define PROJECTPART1_SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <mutex>
#include <iostream>

using namespace std;

/**
 * This class is responsible for the storage of the variables which have
 * assigned (double) values, both binded variables and local variables.
 */
class SymbolTable {
    unordered_map<string, double> symbols;
    mutex m;

public:
    /**
     * This method checks if a given symbol string is valid in
     * symbol map, and returns the fitting double value.
     * @param symbolString given string to search in map.
     * @return double value of the given string.
     */
    double get(string symbolString) {
        lock_guard<mutex> guard(this->m);
        return symbols.at(symbolString);
    }

    /**
     * This method checks if a variable is in the map and returns the answer.
     * @param varName variable name for the check.
     * @return true if in map, else false.
     */
    bool isInMap(string varName) {
        lock_guard<mutex> guard(this->m);
        for (unordered_map<string, double>::iterator it = symbols.begin(); it != symbols.end(); ++it) {
            if (it->first == varName) {
                return true;
            }
        }
        return false;
    }

    /**
     * This method sets given symbol and value to the symbol map.
     * @param symbolString string of the given symbol.
     * @param symbolValue value of the symbol.
     */
    void set(string symbolString, double symbolValue) {
        lock_guard<mutex> guard(this->m);
        this->symbols[symbolString] = symbolValue;
    }

};

#endif //PROJECTPART1_SYMBOLTABLE_H
