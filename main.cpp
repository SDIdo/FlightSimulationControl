#include <iostream>
#include <thread>
#include "Lexer.h"

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

void* pthreadFunc(void* arg) {
    int *idPtr = (int*) arg;
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
     * Lexer try:
     */
// Lexer lexer1;
//    string str;
//    vector<string> vec;
//
//    getline(cin, str); // client input will be sent to lexer function to receive string array.
//    vec = lexer1.lexer(str);
//    cout << vec.at(1) << endl;





    return 0;
}