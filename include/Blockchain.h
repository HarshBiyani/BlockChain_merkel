// include/Blockchain.h

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "Transaction.h"
#include "MerkleTree.h"

// Class representing a block in the blockchain
class Block {
public:
    int index; // Index of the block in the chain
    std::string previousHash; // Hash of the previous block
    std::vector<Transaction> transactions; // Transactions included in the block
    std::string merkleRoot; // Merkle root of the transactions
    std::string timestamp; // Time the block was created
    int nonce; // Nonce for proof of work

    Block(int idx, const std::string& prevHash, const std::vector<Transaction>& txs);
    std::string hash() const; // Method to compute block hash
};

// Class representing the blockchain
class Blockchain {
public:
    std::vector<Block> chain; // Vector to hold all blocks in the blockchain

    Blockchain(); // Constructor to create the genesis block
    void addBlock(const std::vector<Transaction>& transactions); // Add a block to the chain
    bool validateChain() const; // Validate the blockchain
};

#endif // BLOCKCHAIN_H
