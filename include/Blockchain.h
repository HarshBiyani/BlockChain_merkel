// include/Blockchain.h

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "Transaction.h"
#include "MerkleTree.h"
using namespace std;
// Class representing a block in the blockchain
class Block {
public:
    
    Block(int idx, const string& prevHash, const vector<Transaction>& txs);
    string hash() const;

    // Add these setter methods
    void setHash(const string& hash);
    void setTimestamp(const string& timestamp);

    
    int index;
    string previousHash;
    string merkleRoot;
    string timestamp;
    int nonce;
    vector<Transaction> transactions;

private:
    string blockHash; // To store the block's hash directly
};


// Class representing the blockchain
class Blockchain {
public:
    vector<Block> chain; // Vector to hold all blocks in the blockchain

    Blockchain(); // Constructor to create the genesis block
    void addBlock(const vector<Transaction>& transactions); // Add a block to the chain
    bool validateChain() const; // Validate the blockchain
    void saveToFile(const string& filename) const;   // Save blockchain to file
    void loadFromFile(const string& filename); 
};

#endif // BLOCKCHAIN_H
