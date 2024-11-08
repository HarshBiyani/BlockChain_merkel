// include/Transaction.h

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

// Class representing a financial transaction
class Transaction {
public:
    std::string sender;       // Sender's name
    std::string receiver;     // Receiver's name
    float amount;             // Amount transferred
    std::string timestamp;    // Time of transaction

    // Constructor to initialize transaction with sender, receiver, and amount
    Transaction(const std::string& sender, const std::string& receiver, float amount);

    // Method to serialize transaction details
    std::string serialize() const;

    // Equality operator to allow comparison between transactions
    bool operator==(const Transaction& other) const;
};

#endif // TRANSACTION_H
