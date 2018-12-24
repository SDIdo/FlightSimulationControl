//
// Created by roy on 12/24/18.
//

#include "Utilities.h"
#include "BinaryExpression.h"
#include <map>
#include <stack>
#include <iostream>
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
    stack<string> operators_stack;
    stack<string> values_stack;
    cout << "Welcome to Shunting_Yard :: Start read instream\n";
    for (std::vector<string>::iterator it = instream.begin(); it != instream.end(); ++it) {
        std::cout << "current iter is " << *it << "\n";
        if (operators[*it] != nullptr){
            cout << "a. Found an operator! " << *it << "\n";
            while (!operators_stack.empty() && !precedence(*it)){
                cout << "1. So operator stack is not empty and " << *it << " is less or equal to whatever is in stack\n";
                string right_val = values_stack.top();
                values_stack.pop();
                string left_val = values_stack.top();
                values_stack.pop();

                cout << "Show me two operands.. " << left_val << " | " << right_val << "\n";

                BinaryExpression* currentOperation = operators[operators_stack.top()];
                currentOperation->set(new Number(left_val), new Number(right_val));
                values_stack.push(to_string(currentOperation->calculate()));
                cout << "Show me current sol in values stack : " << values_stack.top();
                operators_stack.pop();
            }
            cout << "2. Now put " << *it << " in stack because *it* is grater or stack is empty..\n";
            operators_stack.push(*it);
        }
        else if (*it == "("){
            cout << "Yeah.. detected left parenthesis\n";
            operators_stack.push(*it);
        }
        else if (*it == ")"){
            cout << "Yeah.. detected right parenthesis\n";
            while (operators_stack.top() != "("){       //I'm tempted to think there is a need for another precedency here.

                string right_val = values_stack.top();
                values_stack.pop();
                string left_val = values_stack.top();
                values_stack.pop();

                cout << "Show me two operands.. " << left_val << " | " << right_val << "\n";

                BinaryExpression* currentOperation = operators[operators_stack.top()];
                currentOperation->set(new Number(left_val), new Number(right_val));

                cout << "Passed the set\n";

                values_stack.push(to_string(currentOperation->calculate()));

                cout << "Managed to calculate? " << values_stack.top() << "\n";

                cout << "Show me current sol in values stack : " << values_stack.top() << "\n";
                operators_stack.pop();
                cout << "Managed to pop\n";

            }
            cout << "only way to get out of this loop it by left parenthesis\n";
            operators_stack.pop();
        }
        else if (isdigit((*it).at(0))){
            operators.erase(*it);
            cout << "b. That's a number! " << *it << "\n";
            values_stack.push(*it);
        }
        else{
            cout << "That should be a var.. get it's value from the symbol table.. IF YOU CAN!\n";
            values_stack.push(to_string(symbols->get(*it)));
        }
    }
    cout << "************************\n";
    cout << "Stage 1 Complete | Stage 2 Starts\n";
    cout << "************************\n";
    while (!operators_stack.empty()) {
        string right_val = values_stack.top();
        values_stack.pop();
        string left_val = values_stack.top();
        values_stack.pop();

        cout << "Show me two operands.. " << left_val << " | " << right_val << "\n";
        cout << "Show me the operator " << operators_stack.top() << "\n";
        BinaryExpression* currentOperation = operators.at(operators_stack.top());

        cout << "Passed\n";
        Number left(left_val);
        Number right(right_val);
        currentOperation->set(&left, &right);

        cout << "Passed\n";

        currentOperation->calculate();

        cout << "Passo!X3\n";
        values_stack.push(to_string(currentOperation->calculate()));
        cout << "Passed\n";
        cout << "Show me current sol in values stack : " << values_stack.top();
        operators_stack.pop();
    }
    cout << "Shunting Done.\n" << endl;
    return to_string((int)stod(values_stack.top()));
}
int Utilities::precedence(string currentOper){
    if (currentOper == "+" || currentOper == "-"){
        return 0;
    }
    if (currentOper == "*" || currentOper == "/"){
        return 1;
    }
}