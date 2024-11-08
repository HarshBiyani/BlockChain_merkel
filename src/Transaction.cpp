// src/Transaction.cpp

#include "Transaction.h"
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Constructor implementation
Transaction::Transaction(const std::string& sender, const std::string& receiver, float amount) 
    : sender(sender), receiver(receiver), amount(amount) {
    // Set timestamp to the current time in ISO 8601 format
    time_t now = time(nullptr);
    stringstream ss;
    ss << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
}

// Serialize function implementation
std::string Transaction::serialize() const {
    return sender + receiver + to_string(amount) + timestamp;
}

// Equality operator implementation
bool Transaction::operator==(const Transaction& other) const {
    return sender == other.sender &&
           receiver == other.receiver &&
           amount == other.amount &&
           timestamp == other.timestamp;
}
