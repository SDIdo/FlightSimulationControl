/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Parser.h
 * Author: idox
 *
 * Created on December 24, 2018, 10:10 AM
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
using namespace std;

class Parser{
    virtual void parse(vector<string>) = 0;
};

#endif /* PARSER_H */

