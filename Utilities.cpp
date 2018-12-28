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

void Utilities::set(SymbolTable *newSymbols) {
    symbols = newSymbols;
}

string Utilities::shuntingYard(vector<string> instream) {
//    cout << "Hello and welcome to shuntingYard!\n";
    stack<string> operationStack;
    queue<string> outPutQueue;
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
                   "(") {       //I'm tempted to think there is a need for another precedency here.

                string oper = operationStack.top();
                outPutQueue.push(oper);
                operationStack.pop();
            }

            operationStack.pop();
        } else if (isdigit((*it).at(0))) {
            operators.erase(*it);

            outPutQueue.push(*it);
        } else {
            cout << "[ShuntingYard] That's a variable get it from the symbolTable " << *it << "\n";
            cout << "[ShuntingYard] Wants to open the symbolTable\n";
            outPutQueue.push(to_string(symbols->get(*it)));
            cout << "[ShuntingYard] Got it from the symbolTable " << symbols->get(*it) << "\n";
        }
    }
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
        if (token.at(0) == '-'){
            cout << "Ohhh! that's a minus!\n";
            i = 1;
        }
        if (isdigit(token.at(i))) {     //SCAT!
            cout << "[ShuntingYard] It is a digit " << token.at(0) << "\n";
            operationStack.push(token);
        } else {
            cout << "This should be the right element: " << operationStack.top() << "\n";
            string right = operationStack.top();

            operationStack.pop();
            string left = "0";
            if (!operationStack.empty()) {
                left = operationStack.top();
                operationStack.pop();
            }

            BinaryExpression *oper = operators[token];
            oper->set(new Number(left), new Number(right));
            string sol = to_string(oper->calculate());
            operationStack.push(sol);
        }
    }
    cout << "From the factory of shinting yard::: " << operationStack.top() << endl;
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