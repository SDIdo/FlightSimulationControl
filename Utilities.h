/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ShuntingYard.h
 * Author: idox
 *
 * Created on December 18, 2018, 5:12 AM
 */

#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <string>
using namespace std;

class Utilities{
    int operatorComparator(string, string);
public:
    string shunting_yard(vector<string>);
};

#endif /* UTILITIES_H */

