// src/Transaction.cpp

#include "Transaction.h"

using namespace std;

// Constructor for Transaction
Transaction::Transaction(string sender, string receiver, float amount)
    : sender(sender), receiver(receiver), amount(amount) {
    // Set the timestamp to the current time
    timestamp = to_string(time(nullptr));
}

// Serialize transaction details into a string
string Transaction::serialize() const {
    return sender + receiver + to_string(amount) + timestamp;
}
