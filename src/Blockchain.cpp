// src/Blockchain.cpp

#include "Blockchain.h"
#include <ctime>

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
