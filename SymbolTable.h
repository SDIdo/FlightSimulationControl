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

class SymbolTable {
    unordered_map<string, double> symbols;
    mutex m;

public:
    /**
     * This function checks if a given symbol string is valid in
     * symbol map, and returns the fitting double value.
     * @param symbolString given string to search in map.
     * @return double value of the given string.
     */
    double get(string symbolString) {
        lock_guard<mutex> guard(this->m);
        cout << "[SymbolTable] looking for " << symbolString << " in the map\n";
        return symbols.at(symbolString);
    }

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
     * This function sets given symbol and value to the symbol map.
     * @param symbolString string of the given symbol.
     * @param symbolValue value of the symbol.
     */
    void set(string symbolString, double symbolValue) {
        lock_guard<mutex> guard(this->m);
        this->symbols[symbolString] = symbolValue;
    }

};

#endif //PROJECTPART1_SYMBOLTABLE_H
