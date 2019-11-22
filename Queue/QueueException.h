//
// Created by altair on 20.11.2019.
//

#ifndef STACKIMP_QUEUEEXCEPTION_H
#define STACKIMP_QUEUEEXCEPTION_H
#include <string>

using namespace std;

class QueueException {
public:
    QueueException(string err) {

        error = err;
    }

    string error;
};
#endif //STACKIMP_QUEUEEXCEPTION_H
