// src/main.cpp

#include <iostream>
#include "Transaction.h"
#include "Blockchain.h"

using namespace std;

int main() {
    Blockchain blockchain; // Create a new blockchain

    // Create some transactions
    Transaction tx1("Alice", "Bob", 10); // Alice sends 10 to Bob
    Transaction tx2("Bob", "Charlie", 5); // Bob sends 5 to Charlie

    // Add transactions to a new block in the blockchain
    blockchain.addBlock({tx1, tx2});

    // Print blockchain information
    for (const auto& block : blockchain.chain) {
        cout << "Block #" << block.index << endl;
        cout << "Hash: " << block.hash() << endl;
        cout << "Previous Hash: " << block.previousHash << endl;
        cout << "Merkle Root: " << block.merkleRoot << endl;
        cout << "Timestamp: " << block.timestamp << endl;
        cout << endl;
    }

    // Validate the blockchain
    if (blockchain.validateChain()) {
        cout << "Blockchain is valid." << endl;
    } else {
        cout << "Blockchain is invalid!" << endl;
    }

    return 0; // End of the program
}
