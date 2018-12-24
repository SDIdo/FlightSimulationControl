/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Number.h"
#include <string>
#include <iostream>
using namespace std;

Number::Number(string newValue){
    value = stod(newValue);
    cout << "[Number] value is now: " << value << "\n";
}
double Number::calculate(){
//    cout << "$$Got into calculate self\n";
    return value;
}