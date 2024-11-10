#include "Blockchain.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Constructor for Block
Block::Block(int idx, const string& prevHash, const vector<Transaction>& txs)
    : index(idx), previousHash(prevHash), transactions(txs), nonce(0) {
    // Compute the Merkle root for the transactions in this block
    merkleRoot = MerkleTree(transactions).getRootHash();
    // Set the timestamp to the current time
    timestamp = to_string(time(nullptr));
}

// Compute the hash of the block
string Block::hash() const {
    string blockData = to_string(index) + previousHash + merkleRoot + timestamp + to_string(nonce);
    return MerkleTree({Transaction("hash", blockData, 0)}).getRootHash(); // Reuse hashing for simplicity
}

// Constructor for Blockchain
Blockchain::Blockchain() {
    // Create the genesis block (first block in the chain)
    chain.emplace_back(0, "0", vector<Transaction>{});
}

// Add a block to the blockchain
void Blockchain::addBlock(const vector<Transaction>& transactions) {
    int index = chain.size(); // Get the current index
    string previousHash = chain.back().hash(); // Get the hash of the last block
    Block newBlock(index, previousHash, transactions); // Create a new block
    chain.push_back(newBlock); // Add it to the chain
}

// Validate the blockchain to ensure integrity
bool Blockchain::validateChain() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& current = chain[i]; // Current block
        const Block& previous = chain[i - 1]; // Previous block

        // Check if the hash and merkle root are correct
        if (current.previousHash != previous.hash() || 
            current.merkleRoot != MerkleTree(current.transactions).getRootHash()) {
            return false; // Chain is invalid
        }
    }
    return true; // Chain is valid
}
void Block::setHash(const std::string& hash) {
    blockHash = hash;
}

void Block::setTimestamp(const std::string& timestamp) {
    this->timestamp = timestamp;
}


// Save the blockchain to a file
void Blockchain::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Block& block : chain) {
            file << "Block " << block.index << "\n";
            file << block.previousHash << " " << block.hash() << " " << block.timestamp << "\n";
            file << block.transactions.size() << "\n"; // Number of transactions in the block
            for (const Transaction& txn : block.transactions) {
                file << txn.sender << " " << txn.receiver << " " << txn.amount << "\n";
            }
            file << "EndBlock\n";
        }
        file.close();
        cout << "Blockchain saved to " << filename << "\n";
    } else {
        cerr << "Failed to open file for saving blockchain.\n";
    }
}

// Load the blockchain from a file
void Blockchain::loadFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Could not open blockchain data file. Starting with an empty blockchain.\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        if (line.find("Block") != string::npos) {
            int idx;
            string prevHash, hash, timestamp, txLine;

            // Read block data
            infile >> idx >> prevHash >> hash >> timestamp;
            vector<Transaction> transactions;

            // Read transactions for the block
            while (getline(infile, txLine) && txLine.find("EndBlock") == string::npos) {
                istringstream txStream(txLine);
                string sender, receiver;
                double amount;

                txStream >> sender >> receiver >> amount;
                transactions.emplace_back(sender, receiver, amount);
            }

            // Recreate the block and set additional properties
            Block newBlock(idx, prevHash, transactions);
            newBlock.setHash(hash);
            newBlock.setTimestamp(timestamp);
            chain.push_back(newBlock);

            // Debug output for each loaded block
            cout << "Loaded Block #" << idx << "\n";
            cout << "Hash: " << hash << "\n";
            cout << "Previous Hash: " << prevHash << "\n";
            cout << "Timestamp: " << timestamp << "\n";
            cout << "Transactions:\n";
            for (const auto& tx : transactions) {
                cout << "  " << tx.sender << " -> " << tx.receiver << ", Amount: " << tx.amount << "\n";
            }
            cout << "End of Block\n\n";
        }
    }

    infile.close();
    cout << "Loaded blockchain from file.\n";
}
