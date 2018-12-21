#include <iostream>
#include <thread>
#include "Lexer.h"
#include "BigLexer.h"
#include "SmallLexer.h"
#include "DataReaderServer.h"
#include "Parser.h"
#include "SymbolTable.h"

using namespace std;

void func(int id) {
    for (int i = 0; i < 100; i++) {
        if (id == 1) {
            cout << "hello, this is the NUMBER ONE thread" << endl;
        } else {
            cout << "i am not the number one..." << endl;
        }
    }
}

void *pthreadFunc(void *arg) {
    int *idPtr = (int *) arg;
    int id = *idPtr;
    for (int i = 0; i < 100; i++) {
        if (id == 1) {
            cout << "hello, this is the NUMBER ONE thread" << endl;
        } else {
            cout << "i am not the number one..." << endl;
        }
    }

    pthread_exit(0); // the thread which runs this func finishes.
}


int main() {

    /**
     * Thread try:
     */
//    thread th1(func, 1); // thread 1 runs with its message.
//    thread th2(func, 2); // thread 2 runs with the other message.
//    th1.join();
//    th2.join();

    /**
     * Pthread try:
     */
//    // create 1st thread
//     pthread_t threadID;
//     pthread_attr_t attr;
//     pthread_attr_init(&attr);
//     int valueForFunc = 1;
//     pthread_create(&threadID, &attr, pthreadFunc, &valueForFunc);
//
//     // create 2nd thread
//    pthread_t thread2ID;
//    pthread_attr_t attr2;
//    pthread_attr_init(&attr2);
//    int secondValue = 2;
//    pthread_create(&thread2ID, &attr2, pthreadFunc, &secondValue);
//
//     pthread_join(threadID, nullptr); // wait for thread to join.
//    pthread_join(thread2ID, nullptr); // wait for thread to join.


/**
 * 2nd Pthread try
 */

//DataReaderServer dataReaderServer;
//
//    // create 1st thread.
//     pthread_t threadID;
//     pthread_attr_t attr;
//     pthread_attr_init(&attr);
//     int valueForFunc = 1;
//
//    void *(DataReaderServer::*func)(void*);
//    func = &DataReaderServer::listen;
//
//     pthread_create(&threadID, &attr, func, &valueForFunc);
//
//
//
//     // create 2nd thread.
//    pthread_t thread2ID;
//    pthread_attr_t attr2;
//    pthread_attr_init(&attr2);
//    int secondValue = 2;
//    pthread_create(&thread2ID, &attr2, pthreadFunc, &secondValue);
//
//     pthread_join(threadID, nullptr); // wait for thread to join.
//    pthread_join(thread2ID, nullptr); // wait for thread to join.


    /**
     * Lexer try:
     */

// BigLexer lexer1;
//    string str;
//    vector<string> vec;
//
//    getline(cin, str); // client input will be sent to lexer function to receive string array.
//    vec = lexer1.lexer(str);
//    for (int i  =0; i < vec.size(); i++) {
//        cout << vec.at(i) << "\n";
//    }


/**
 * "REAL" main
 * this main simulates the real main used for the flight simulator.
 */

    SymbolTable st;
    Parser parser(&st); // parser gets a pointer to the shared symbol table.
    BigLexer bl;
    string clientInput;

    while (true) {
        getline(cin, clientInput);
        // if the client wanted to print done and quit the simulator.
        if (clientInput == "print \"done\"") {
            cout << "done";
            break;
        }
        parser.parse(bl.lexer(clientInput));
    }

    return 0;
}