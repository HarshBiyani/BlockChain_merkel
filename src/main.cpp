
#include <iostream>
#include "Blockchain.h"
#include "Transaction.h"

using namespace std;

void displayMenu() {
    cout << "\nBlockchain Menu Options:\n";
    cout << "1. Add a transaction\n";
    cout << "2. Add a new block\n";
    cout << "3. View all transactions\n";
    cout << "4. View the blockchain\n";
    cout << "5. Verify a transaction\n";
    cout << "6. Validate blockchain\n";
    cout << "7. Save blockchain to file\n";
    cout << "8. Load blockchain from file\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void displayTransactions(const vector<Transaction>& transactions) {
    if (transactions.empty()) {
        cout << "No transactions found.\n";
    } else {
        for (size_t i = 0; i < transactions.size(); ++i) {
            cout << "Transaction #" << (i + 1) << ": "
                 << transactions[i].sender << " -> " 
                 << transactions[i].receiver << ", Amount: " 
                 << transactions[i].amount << endl;
        }
    }
}

void displayBlockchain(const Blockchain& blockchain) {
    for (const auto& block : blockchain.chain) {
        cout << "Block #" << block.index << endl;
        cout << "Hash: " << block.hash() << endl;
        cout << "Previous Hash: " << block.previousHash << endl;
        cout << "Merkle Root: " << block.merkleRoot << endl;
        cout << "Timestamp: " << block.timestamp << endl;
        displayTransactions(block.transactions);
        cout << endl;
    }
}

int main() {
    Blockchain blockchain;
    vector<Transaction> transactionPool;
    int choice;


    blockchain.loadFromFile("blockchain_data.txt");

    while (true) {
        displayMenu();
        cin >> choice;
        cout << endl;

        if (choice == 0) {
            cout << "Exiting program." << endl;
            break;
        }

        switch (choice) {
            case 1: { // Add a transaction
                string sender, receiver;
                double amount;

                cout << "Enter sender name: ";
                cin >> sender;
                cout << "Enter receiver name: ";
                cin >> receiver;
                cout << "Enter amount: ";
                cin >> amount;

                Transaction newTransaction(sender, receiver, amount);
                transactionPool.push_back(newTransaction);
                cout << "Transaction added to the pool.\n";
                break;
            }

            case 2: { // Add a new block
                if (transactionPool.empty()) {
                    cout << "No transactions to add to a new block.\n";
                } else {
                    blockchain.addBlock(transactionPool);
                    transactionPool.clear();
                    cout << "New block added to the blockchain.\n";
                }
                break;
            }

            case 3: { // View all transactions in the pool
                cout << "Transactions in the pool:\n";
                displayTransactions(transactionPool);
                break;
            }

            case 4: { // View the blockchain
                cout << "Blockchain:\n";
                displayBlockchain(blockchain);
                break;
            }

            case 5: { // Verify a transaction
                if (blockchain.chain.empty()) {
                    cout << "Blockchain is empty.\n";
                } else {
                    string sender, receiver;
                    double amount;
                    bool found = false;

                    cout << "Enter sender name: ";
                    cin >> sender;
                    cout << "Enter receiver name: ";
                    cin >> receiver;
                    cout << "Enter amount: ";
                    cin >> amount;

                    Transaction transaction(sender, receiver, amount);

                    // Check each block for the transaction
                    for (const auto& block : blockchain.chain) {
                        for (const auto& tx : block.transactions) {
                            if (tx == transaction) {
                                found = true;
                                break;
                            }
                        }
                        if (found) break;
                    }

                    if (found) {
                        cout << "Transaction is part of the blockchain.\n";
                    } else {
                        cout << "Transaction not found in the blockchain.\n";
                    }
                }
                break;
            }

            case 6: { // Validate blockchain
                if (blockchain.validateChain()) {
                    cout << "Blockchain is valid.\n";
                } else {
                    cout << "Blockchain is invalid!\n";
                }
                break;
            }

            case 7: { // Save blockchain to file
                blockchain.saveToFile("blockchain_data.txt");
                break;
            }

            case 8: { // Load blockchain from file
                blockchain.loadFromFile("blockchain_data.txt");
                break;
            }

            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
