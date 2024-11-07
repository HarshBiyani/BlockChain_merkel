// include/MerkleTree.h

#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <memory>
#include <string>
#include <vector>
#include "Transaction.h"

// Class representing a node in the Merkle tree
class MerkleNode {
public:
    std::string hash; // Hash of the node
    std::shared_ptr<MerkleNode> left; // Left child
    std::shared_ptr<MerkleNode> right; // Right child

    MerkleNode(const std::string& hash);
};

// Class representing the Merkle tree
class MerkleTree {
public:
    std::shared_ptr<MerkleNode> root; // Root node of the Merkle tree

    MerkleTree(const std::vector<Transaction>& transactions);
    std::shared_ptr<MerkleNode> buildTree(const std::vector<Transaction>& transactions);
    std::string hash(const std::string& data) const; // Method to compute hash
    std::string getRootHash() const; // Get the root hash of the tree
};

#endif // MERKLETREE_H
