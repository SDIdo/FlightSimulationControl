#include "Utilities.h"
#include "BinaryExpression.h"
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

void Utilities::set(SymbolTable *newSymbols, DataReaderServer * newDataServer) {
    symbols = newSymbols;
    dataServer = newDataServer;
}

string Utilities::shuntingYard(vector<string> instream) {
    cout << "[ShuntingYard] Hello and welcome to shuntingYard with: \n";
    for (string s : instream){
        cout << s << ", ";
    }
    stack<string> operationStack;
    queue<string> outPutQueue;
    string left;
    for (std::vector<string>::iterator it = instream.begin(); it != instream.end(); ++it) {
        if (operators[*it] != nullptr) {
            while (!operationStack.empty() && operators[operationStack.top()] != nullptr && !precedence(*it)) {
                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }
            operationStack.push(*it);
        } else if (*it == "(") {

            operationStack.push(*it);
        } else if (*it == ")") {

            while (operationStack.top() !=
                   "(") {

                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }

            operationStack.pop();
            //number situation
        } else if (isdigit((*it).at(0))) {
            cout << "[SuntingYard] yeah that's a number: " << *it << "\n";
            operators.erase(*it);

            outPutQueue.push(*it);
            //variable situation
        } else if (this->dataServer->isInBindMap(*it)){
            string address = this->dataServer->getBindAddress(*it);
            cout << "[ShuntingYard] That's a global variable get it from the symbolTable: " << *it << "\n";
            cout << "[ShuntingYardSmart] get it's address: " << address << "\n";
            double value = this->symbols->get(address);
            cout << "[ShuntingYardSmart] get it's value: " << value << "\n";
            outPutQueue.push(to_string(value));
            cout << "[ShuntingYardSmart] Got it from the symbolTable " << outPutQueue.back() << "\n";
        }
        else {
            cout << "this has to be a local var or we are going to crash\n";
            outPutQueue.push(to_string(symbols->get(*it)));
            cout << "[ShuntingYard] Got it from the symbolTable " << outPutQueue.back() << "\n";
        }
    }

    //Second Stage//
    while (!operationStack.empty()) {
        cout << "[Shunting Yard ]Whats being transfered? : " << operationStack.top() << "\n";
        outPutQueue.push(operationStack.top());
        operationStack.pop();
    }

    while (!outPutQueue.empty()) {
        std::cout << "[Shunting Yard ] show what's on queue " << outPutQueue.front() << std::endl;
        string token = outPutQueue.front();
        outPutQueue.pop();
        int i = 0;
        if (token != "-" && token.at(0) == '-'){
            cout << "Ohhh! that's a negative number!\n";
            i = 1;
        }
        if (isdigit(token.at(i))) {     //SCAT!
            cout << "[ShuntingYard] It is a digit " << token.at(0) << "\n";
            operationStack.push(token);
        } else {
            cout << "This should be the right element: " << operationStack.top() << "\n";
            string right = operationStack.top();

            operationStack.pop();
            if (operationStack.empty()) {
                left = "0";
            }
            else{
                left = operationStack.top();
                operationStack.pop();
            }

            BinaryExpression *oper = operators[token];
            oper->set(new Number(left), new Number(right));
            string sol = to_string(oper->calculate());
            operationStack.push(sol);
        }
    }
    cout << "From the factory of shunting yard::: " << operationStack.top() << endl;
    return operationStack.top();
}

int Utilities::precedence(string currentOper) {
    if (currentOper == "+" || currentOper == "-") {
        return 0;
    }
    if (currentOper == "*" || currentOper == "/") {
        return 1;
    }
}