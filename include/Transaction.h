// include/Transaction.h

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

// Class representing a financial transaction
class Transaction {
public:
    std::string sender;  // Sender's name
    std::string receiver; // Receiver's name
    float amount;        // Amount transferred
    std::string timestamp; // Time of transaction

    Transaction(std::string sender, std::string receiver, float amount);
    std::string serialize() const; // Method to serialize transaction details
};

#endif // TRANSACTION_H
