//
// Created by roy on 12/21/18.
//

#ifndef PROJECTPART1_SYMBOLTABLE_H
#define PROJECTPART1_SYMBOLTABLE_H

#include <map>
#include <string>

using namespace std;

class SymbolTable {
    map<string, double> symbols;

public:
    /**
     * This function checks if a given symbol string is valid in
     * symbol map, and returns the fitting double value.
     * @param symbolString given string to search in map.
     * @return double value of the given string.
     */
    double get(string const symbolString) const {
        return symbols.at(symbolString);
    }

    bool isInMap(string varName) {
        for (std::map<string, double>::iterator it = symbols.begin(); it != symbols.end(); ++it) {
            if (it->first == varName) {
                return true;
            }
        }
        return false;
    }

    unsigned long size(){
        return symbols.size();
    }

    /**
     * This function sets given symbol and value to the symbol map.
     * @param symbolString string of the given symbol.
     * @param symbolValue value of the symbol.
     */
    void set(string symbolString, double symbolValue) {
        this->symbols[symbolString] = symbolValue;
    }

};

#endif //PROJECTPART1_SYMBOLTABLE_H
