/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Utilities.h"
#include "BinaryExpression.h"
#include <map>
#include <stack>
#include <iostream>
#include <queue>
#include "Div.h"
#include "Mult.h"
#include "Plus.h"
#include "Minus.h"
#include "Number.h"

Utilities::Utilities() {
    operators["+"] = new Plus();
    operators["-"] = new Minus();
    operators["*"] = new Mult();
    operators["/"] = new Div();
}

void Utilities::set(SymbolTable* newSymbols){
    symbols = newSymbols;
}
string Utilities::shuntingYard(vector<string> instream) {
    stack<string> operationStack;
    queue<string> outPutQueue;
    cout << "Welcome to Shunting_Yard :: Start read instream\n";
    for (std::vector<string>::iterator it = instream.begin(); it != instream.end(); ++it) {
        std::cout << "current iter is " << *it << "\n";
        if (operators[*it] != nullptr){
            cout << "a. Found an operator! " << *it << "\n";
            while (!operationStack.empty() && operators[operationStack.top()] != nullptr && !precedence(*it)){
            cout << "1. So operator stack is not empty and " << *it << " is less or equal to whatever is in stack\n";
            std::cout << "Poping operator to outPut Queue" << operationStack.top() << std::endl;
            string oper = operationStack.top();
            outPutQueue.push(oper);
            operationStack.pop();
            }
            cout << "This : " << *it << " is grater then what's inside push to operations\n";
            operationStack.push(*it);
        }
        else if (*it == "("){
            cout << "Yeah.. detected left parenthesis push to stack\n";
            operationStack.push(*it);
        }
        else if (*it == ")"){
            cout << "Yeah.. detected right parenthesis\n";
            while (operationStack.top() != "("){       //I'm tempted to think there is a need for another precedency here.
                std::cout << "[due to ( and then )]Poping from operations to output queue\n";
                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }
            cout << "only way to get out of this loop it by left parenthesis\n";
            operationStack.pop();
        }
        else if (isdigit((*it).at(0))){
            operators.erase(*it);
            cout << "b. That's a number! add to outputqueue " << *it << "\n";
            outPutQueue.push(*it);
        }
        else{
            cout << "That should be a var.. get it's value from the symbol table.. IF YOU CAN!\n";
            outPutQueue.push(to_string(symbols->get(*it)));
        }
    }
    while (!operationStack.empty()) {
        
        outPutQueue.push(operationStack.top());
        operationStack.pop();
    }
    cout << "************************\n";
    cout << "Stage 1 Complete | Stage 2 Starts\n";
    cout << "************************\n";
    std::cout << "[Stage2] Show current infix to postfix\n";
    while(!outPutQueue.empty()){
        std::cout << outPutQueue.front() << std::endl;
        string token = outPutQueue.front();
        outPutQueue.pop();
        
        if (isdigit(token.at(0))){
            cout << "[Stage2] Alright found a number\n";
            operationStack.push(token);
        }
        else{
            cout << "[Stage2] This has to be an operator..\n";
            string right = operationStack.top();
            operationStack.pop();
            string left = operationStack.top();
            operationStack.pop();
            
            cout << "[Stage2] Current right and left are: " << right << " " << token << " " << right << "\n";
            BinaryExpression* oper = operators[token];
            oper->set(new Number(left), new Number(right));
            string sol = to_string(oper->calculate());
            cout << "[Stage2] And sol is now.. " << sol << "\n";
            operationStack.push(sol);
        }
    }
    return operationStack.top();
}
int Utilities::precedence(string currentOper){
    if (currentOper == "+" || currentOper == "-"){
        return 0;
    }
    if (currentOper == "*" || currentOper == "/"){
        return 1;
    }
}