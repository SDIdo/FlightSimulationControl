////
//// Created by roy on 12/25/18.
////
//
//#include <iostream>
//#include "VarCommand.h"
//
//VarCommand::VarCommand(string varName, string equalSign, string valueString, string pathString,
//                       DataReaderServer dataReaderServer) {
//    this->varName = varName;
//    this->equalSign = equalSign;
//    this->valueString = valueString;
//    this->pathString = pathString;
//    this->dataReaderServer = dataReaderServer;
//}
//
//int VarCommand::execute() {
//    // from the likes of var x = 8 / var x = bind "path".
//
//    // if the var command is bind command.
//    if ((this->equalSign == "=") && (this->valueString == "bind")) {
////                cout << "Time to update bind map!\n";
//        this->dataReaderServer.setBind(this->varName, this->pathString);
//    }
//        // else, the var command is a input command.
//    else {
//        string expressionAfterEquation = this->util.shuntingYard(this->smallLexer.lexer(this->valueString));
//        char charAfterEquation = expressionAfterEquation.at(0);
//        if (this->equalSign == "=" && isdigit(charAfterEquation)) {
//            cout << "Detected var x = " << expressionAfterEquation << "\n";
//
//            cout << "Now check whether it's binded with the simulator..\n";
//
//            if (this->dataReaderServer.isInBindMap(this->varName)) {
//                cout << "Hmm so this x is binded!\n";
//                string address = stringVector.at(this->dataReaderServer.getFromBindValues(this->varName));
//                string update = " " + this->valueString;
//                string updatedAddress = address + update;
//
//                char toSend[256];
//                strcpy(toSend, updatedAddress.c_str());
//
//                this->dataSender.sendCommand(toSend);
//            } else {
//                symbolTable->set(this->varName, stod(expressionAfterEquation));
//                cout << "Now let's see.. " << symbolTable->get("x") << "\n";
//            }
//        }
//    }
//}