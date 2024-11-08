// include/Transaction.h

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <sstream>

// Class representing a financial transaction
class Transaction {
public:
    std::string sender;       // Sender's name
    std::string receiver;     // Receiver's name
    float amount;             // Amount transferred
    std::string timestamp;    // Time of transaction

    // Constructor to initialize transaction with sender, receiver, amount, and current timestamp
    Transaction(std::string sender, std::string receiver, float amount) 
        : sender(sender), receiver(receiver), amount(amount) {
        // Set timestamp to the current time
        std::time_t now = std::time(nullptr);
        std::stringstream ss;
        ss << std::asctime(std::localtime(&now));
        timestamp = ss.str();
    }

    // Method to serialize transaction details
    std::string serialize() const {
        return sender + receiver + std::to_string(amount) + timestamp;
    }

    // Define equality operator to allow comparison between transactions
    bool operator==(const Transaction& other) const {
        return sender == other.sender &&
               receiver == other.receiver &&
               amount == other.amount &&
               timestamp == other.timestamp;
    }
};

#endif // TRANSACTION_H
