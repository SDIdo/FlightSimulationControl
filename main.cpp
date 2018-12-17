/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: idox
 *
 * Created on December 17, 2018, 8:36 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "Expression.h"
#include "Number.h"
#include "Plus.h"
#include "Minus.h"
using namespace std;

void shunting_yard(vector<string> instream) {
    cout << "Welcome to shunting yard\n";
    //Do loop on the exp and pull out from the symbol table if it's a var
    //Stage 1//
    //Initialize a stack for the operators
    //Initialize a Queue for the numbers and with seniority of operators
    map<string, BinaryExpression*> operateTable; 
    operateTable["+"] = new Plus();
//    symbolTLB["-"] = new Minus();
//    symbolTLB["*"] = new Mult();
//    symbolTLB["/"] = new Div();
    
    stack<string> roll;
    queue<string> line;

//    for (std::vector<string>::iterator it = instream.begin(); it != instream.end(); ++it){
//        std::cout << "current iter on " << *it << "\n";
////        if (symbolTLB.at(*it) != nullptr){
////            cout << "Found an operator\n";
////        }
//        
//    }
    
    ///TEST ZONE//
    line.push(instream.at(0));
    roll.push(instream.at(1));
    line.push(instream.at(2));

    
    //  Finishes - moving what's in stack to line //

    while(!roll.empty()){
        line.push(roll.top());
        roll.pop();
    }
    
    cout << "Stage 1 complete: Finally line size is : " << line.size() << endl;

    //    //$$ Stage2: First assignment from queue to stack $$
    
    //    //isNumber whatever in the queue and put into stack
    //    //else use two last ins from stack to calc witht the operator
    
    cout << "Show me what's in Map.. " << operateTable["-"] << "\n";
    
    while((!line.empty())){
        cout << "line size is : " << line.size() << ", " << "stack size is: " << roll.size() << "\n";
        if (operateTable[line.front()] == 0){
            operateTable.erase(line.front()); //Upon checking map - has added it - so removing it!  
            cout << "We have a number then..\n";

            
            roll.push(line.front());
            line.pop();
            cout << "Currently line has " << line.size() << "\n";
        }
        else{
            cout << "That's an operator!\n";
            BinaryExpression* operate = operateTable.at(line.front());
            line.pop();
            
            cout << "Just got the operator!\n";
            
            Expression* right = new Number(roll.top());
            roll.pop();
            
            cout << "Got right from stack\n";
            
            Expression* left = new Number(roll.top());
            roll.pop();
            
            cout <<"Got left from stack\n";
            
            operate->set(left, right);
            roll.push(to_string(operate->calculate()));
        }
        cout << roll.top() << "\n";
//        
//        Expression* b = line.front();
//        line.pop();
    //    
    //    //Here I know that it's an operator so pulls the corresponding operator..
    //    
//        roll.push(line.front());
//        line.pop();
//        cout << line.front() << endl;
    }
    
//    line.pop();

//    cout << "Should be + " << line.front() << endl;
    
//    Plus *p = new Plus(a, b); //Fix here.. 
    //Number should be recognized as an expression

//    cout << p->calculate() << endl;

    //    BinaryExpression* t = new BinaryExpression(roll.top(), line.front(), roll.top());
//    line.pop();
//    line.push();
    //    cout << t->calculate() << endl;
};


/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Welcome to Dugma!\n";
    shunting_yard({"2", "+", "2"});
    
    return 0;
}

