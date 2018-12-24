//
// Created by roy on 12/18/18.
//

#include <iostream>
#include <unistd.h>
#include <chrono>
#include "LineParser.h"
#include "IfCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "ExpressionCommand.h"

using namespace std;

/**
 * Constructor of LineParser, used for parsing single line.
 * @param symbolTable symbol table for variables access.
 */
LineParser::LineParser(SymbolTable *symbolTable) {
    this->symbolTable = symbolTable;
    ut.set(this->symbolTable);
}

void LineParser::parse(vector<string> stringVector) {
    string commandString = stringVector.at(0); // first string will represent the first command in line.
    Commands command = commandMap.getCommand(commandString);
    if (stringVector.at(1) == "="){
        command = Equal;
    }
    
    // Test Zone - Using a Map<str, Expression>
    
    //SCAT such map!
    cout << "[the SCAT test] we are here\n";
//    map<string, PrintCommand*> commandsTable;
//    commandsTable.insert(pair<string, PrintCommand*>("print", new PrintCommand()));
//    
//    commandsTable.at(stringVector.at(0))->setCommand(stringVector.at(1), this->symbolTable);
//    commandsTable.at(stringVector.at(0))->execute();
    
    
    

//     for each command option - execute the fitting operation:
    switch (command) {
        case OpenDataServer :
            
            string port = ut.shuntingYard(smallLexer.lexer(stringVector.at(1)));
            string herz = ut.shuntingYard(smallLexer.lexer(stringVector.at(2)));
            OpenServerCommand openServer(port, herz, this->dataReader);
            cout << "So let's see what's about to be opened " << port << ", " << herz << "\n";
            openServer.execute();
            // create port and hertz, and open data server.
//            openServer.execute(stringVector.at(1), stringVector.at(2));
            break;
        
        case Connect : //Is Complete
            ConnectCommand connect(stringVector.at(1), ut.shuntingYard(smallLexer.lexer(stringVector.at(2))), this->dataSender);
            connect.execute();
            break;
        
        case Var :
            // from the likes of var x = 8
            cout << "Here with " << stringVector.at(3) << "\n";
            
            if ((stringVector.at(2) == "=") && (stringVector.at(3) == "bind")) {
//                string expressionAfterEquation = ut.shuntingYard(smallLexer.lexer(stringVector.at(4)));
                cout << "Time to update bind map!\n";
                dataReader->setBind(stringVector.at(1), stringVector.at(4));
            }
            else{
                string expressionAfterEquation = ut.shuntingYard(smallLexer.lexer(stringVector.at(3)));
                char charAfterEquation = expressionAfterEquation.at(0);
                if (stringVector.at(2) == "=" && isdigit(charAfterEquation)){
                    cout << "Detected var x = " << expressionAfterEquation << "\n";
                    
                    cout << "Now check whether it's binded with the simulator..\n";
                    
//                    if (dataReader->isInBindMap(stringVector.at(1))){
//                        cout << "Hmm so this x is binded!\n";
//                        string address = stringVector.at(dataReader->getFromBindValues(stringVector.at(1)));
//                        string update = " " + to_string(stringVector.at(3));
//                        dataSender->sendCommand(address+update);
//                    }
//                    else{
                        symbolTable->set(stringVector.at(1), stod(expressionAfterEquation));
                        cout << "Now let's see.. " << symbolTable->get("x") << "\n";
//                    }
                }
            }            
//            symbolTable->set()
            // put value in symbol table (Or if BIND, then bind with the relative folder).
            break;
        
//
//        case Bind : // MAYBE ITS NOT EVEN A COMMAND.
//            // bind the variable to the next string.
//            break;

        case Equal :
            cout << "Here with " << stringVector.at(0) << "=" << stringVector.at(2) << "\n";
            //SCAT - have to initialize dataReader first?
//            if (dataReader){
//                if (dataReader->isInBindMap(stringVector.at(0))){  //SCAT like it is not there.. seg?
//                    cout << "[Line parser] Yep it is there. Updating server\n";
////                    dataReader->setBind(stringVector.at(0), stringVector.at(2)); //SCAT like no expressions yet
//                }
//            }
//            else{
                cout << "[Line Parser] No need to update in server that's a local var\n";
                symbolTable->set(stringVector.at(0), stod(stringVector.at(2)));
//            }
            cout << "Just want to see.. " << symbolTable->get("x");
            // input the next value to the previous value.
            break;
        

        case Print :{
            PrintCommand printIt();
            printIt.setCommand(stringVector.at(1), this->symbolTable);
            printIt.execute();
            break;
        }
        

        case Sleep :
            // sleeps for the given amount of time.
            double sleepTime = stod(ut.shuntingYard(this->smallLexer.lexer(stringVector.at(1))));
            sleep(sleepTime/1000);
            break;
//        
//
//            // if the command is invalid command, throw error message.
        default:
            throw "Non valid command";
    }

}