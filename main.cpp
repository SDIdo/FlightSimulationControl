#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include "BigLexer.h"
#include "SmallLexer.h"
#include "DataReaderServer.h"
#include "LineParser.h"
#include "SymbolTable.h"
#include "BlockParser.h"
#include "DataSender.h"

using namespace std;

// create mutex lock.
mutex mutex1;

void shared_print(string toPrint, int id) {
    mutex1.lock();
    cout << toPrint << endl;
    mutex1.unlock();
}

void *pthreadFunc(void *arg) {
    int *idPtr = (int *) arg;
    int id = *idPtr;
    for (int i = 0; i < 1000; i++) {
        if (id == 1) {
            shared_print("hello, this is the NUMBER ONE thread", 1);
        } else {
            shared_print("i am not the number one...", 2);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    pthread_exit(nullptr); // the thread which runs this func finishes.
}


int main() {

    /**
     * Pthread try:
     *  this try is using mutex in order to lock data usage from other threads.
     */

//    // create 1st thread
//    pthread_t threadID;
//    pthread_attr_t attr;
//    pthread_attr_init(&attr);
//    int valueForFunc = 1;
//    pthread_create(&threadID, &attr, pthreadFunc, &valueForFunc);
//
//    // create 2nd thread
//    pthread_t thread2ID;
//    pthread_attr_t attr2;
//    pthread_attr_init(&attr2);
//    int secondValue = 2;
//    pthread_create(&thread2ID, &attr2, pthreadFunc, &secondValue);
//
//    pthread_join(threadID, nullptr); // wait for thread to join.
//    pthread_join(thread2ID, nullptr); // wait for thread to join.


/**
 * 2nd Pthread try:
 * this try is trying to use thread on a class method.
 */

//    DataReaderServer dataReaderServer;
//    dataReaderServer.threadListen();

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
 * "REAL" main for sending commands.
 * this main simulates the real main used for the flight simulator.
 */

    SymbolTable st;
    LineParser lineParser(&st); // parser gets a pointer to the shared symbol table.
    BlockParser blockParser(&st); // block parser gets a pointer to the shared symbol table.
    BigLexer bl;
    string userInput;
    vector<string> stringVector;

    while (true) {
        getline(cin, userInput);
        stringVector = bl.lexer(userInput);

        if (userInput == "print \"done\"") {
            cout << "done" << "\n";
            break;
        }
            // if command is block command.
        else if (stringVector.at(0) == "while" || stringVector.at(0) == "if") {
            string blockString = userInput.substr(0, userInput.length() - 2); // exclude curly bracket.
            // get all of the user input until the end of the if/while statement.
            int openedBrackets = 1;
            while (openedBrackets != 0) {
                getline(cin, userInput);
                if (userInput.back() == '}') {
                    openedBrackets -= 1;
                    continue;
                } else if (userInput.back() == '{') {
                    openedBrackets += 1;
                }
                blockString += userInput;
            }

            stringVector = bl.lexer(blockString);
            blockParser.parse(stringVector);
        }
            // command was a line command.
        else {
            lineParser.parse(bl.lexer(userInput), 0);
        }
    }

/**
 * Test with Ido (worked open server).
 *
 * And now also the client can connect to the flight simulator with it's own pthread.
 * After it connects it can send commands to the simulator.
 */

//    DataReaderServer dataReaderServer;
//    pthread_t t1ID;
//    pthread_create(&t1ID, NULL, &DataReaderServer::runOpen, &dataReaderServer);
//
//    dataReaderServer.set("5402", "10");
//
//    // unconnected print...
//    cout << "parallel activity" << endl;
//
//    DataSender dataSender;
//    pthread_t t2ID;
//    pthread_create(&t2ID, NULL, &DataReaderServer::runOpen, &dataSender);
//
//    sleep(18);
//
//    dataSender.set("127.0.0.1", "5401");
//    dataSender.openPipe();
//
//    sleep(18);
//    dataSender.sendCommand("ls");
//
//
//
//
//    // unconnected print...
//    cout << "parallel activity" << endl;
//
//    pthread_join(t1ID, nullptr); // wait for thread to join.
//    pthread_join(t2ID, nullptr); // wait for thread to join.

    return 0;
}