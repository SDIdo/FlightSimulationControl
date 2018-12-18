/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Utilities.h"
#include <stack>
#include <queue>
#include "BinaryExpression.h"
#include "Div.h"
#include "Plus.h"
#include "Minus.h"
#include "Mult.h"
#include "Number.h"
#include "Expression.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

int Utilities::operatorComparator(string oper1, string oper2) {
    if (oper1 == oper2) {
        return 1;
    }
    if (oper1 == "+" || oper1 == "-") {
        return 2;
    }
    if (oper1 == "*" || oper1 == "/") {
        return 1;
    }
}

string Utilities::shunting_yard(vector<string> instream) {
    cout << "Welcome to shunting yard\n";
    //Do loop on the exp and pull out from the symbol table if it's a var
    //Stage 1//
    //Initialize a stack for the operators
    //Initialize a Queue for the numbers and with seniority of operators
    map<string, BinaryExpression*> operateTable;
    operateTable["+"] = new Plus();
    operateTable["-"] = new Minus();
    operateTable["*"] = new Mult();
    operateTable["/"] = new Div();
    //    operateTable["("] = new OpenParen();
    //    operateTable[")"] = new CloseParen();

    stack<string> roll;
    queue<string> line;

    for (std::vector<string>::iterator it = instream.begin(); it != instream.end(); ++it) {
        std::cout << "current iter on " << *it << "\n";
        if (operateTable[*it] != nullptr) {
            cout << "Found an operator\n";

            if (!roll.empty()) {
                cout << "Check who comes first\n";
                cout << "well.. stack is not empty check operator comparator\n";
                if (operatorComparator(roll.top(), *it) == 1) {
                    line.push(roll.top());
                    roll.pop();
                    roll.push(*it);
                } else {
                    cout << "Put the new because it has better seniority\n";
                    roll.push(*it);
                }
            }
            //            
            roll.push(*it); //operator to roll
        } else {
            operateTable.erase(*it);
            line.push(*it); //number to queue
        }

    }
    //  Finishes - moving what's in stack to line //

    cout << "Stage 1.a : line size is : " << line.size() << ", " << "stack size is: " << roll.size() << "\n";

    while (!roll.empty()) {
        line.push(roll.top());
        roll.pop();
    }

    cout << "Stage 1 complete: Finally line size is : " << line.size() << endl;

    //    //$$ Stage2: First assignment from queue to stack $$

    //    //isNumber whatever in the queue and put into stack
    //    //else use two last ins from stack to calc witht the operator

    cout << "Show me what's in Map.. " << operateTable["-"] << "\n";

    while ((!line.empty())) {
        cout << "line size is : " << line.size() << ", " << "stack size is: " << roll.size() << "\n";
        if (operateTable[line.front()] == 0) {
            operateTable.erase(line.front()); //Upon checking map - has added it - so removing it!  
            cout << "We have a number then..\n";


            roll.push(line.front());
            line.pop();
            cout << "Currently line has " << line.size() << "\n";
        } else {
            cout << "That's an operator!\n";
            BinaryExpression* operate = operateTable.at(line.front());
            line.pop();

            cout << "Just got the operator!\n";

            Expression* right = new Number(roll.top());
            roll.pop();

            cout << "Got right from stack\n";

            Expression* left = new Number(roll.top());
            roll.pop();

            cout << "Got left from stack\n";

            operate->set(left, right);

            cout << "Y\n";
            roll.push(to_string(operate->calculate()));
            if (line.empty() && roll.size() == 1) {
                cout << "Got out\n";
                break;
            }
        }
    }
    return roll.top();
}