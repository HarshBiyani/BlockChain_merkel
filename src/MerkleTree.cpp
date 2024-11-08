#include "MerkleTree.h"
#include "sha256.h"  // Use your custom sha256 header

using namespace std;

// Constructor for MerkleNode
MerkleNode::MerkleNode(const string& hash) : hash(hash), left(nullptr), right(nullptr) {}

// Constructor for MerkleTree
MerkleTree::MerkleTree(const vector<Transaction>& transactions) {
    root = buildTree(transactions); // Build the tree from transactions
}

// Build the Merkle tree from the provided transactions
shared_ptr<MerkleNode> MerkleTree::buildTree(const vector<Transaction>& transactions) {
    vector<shared_ptr<MerkleNode>> nodes;

    // Create leaf nodes for each transaction
    for (const auto& tx : transactions) {
        nodes.push_back(make_shared<MerkleNode>(hash(tx.serialize())));
    }

    // Build the tree
    while (nodes.size() > 1) {
        vector<shared_ptr<MerkleNode>> newLevel;
        for (size_t i = 0; i < nodes.size(); i += 2) {
            // Combine pairs of nodes to create a new parent node
            if (i + 1 < nodes.size()) {
                string combinedHash = nodes[i]->hash + nodes[i + 1]->hash;
                newLevel.push_back(make_shared<MerkleNode>(hash(combinedHash)));
                newLevel.back()->left = nodes[i];
                newLevel.back()->right = nodes[i + 1];
            } else {
                newLevel.push_back(nodes[i]); // Handle odd number of nodes
            }
        }
        nodes = newLevel; // Move to the next level
    }
    return nodes.empty() ? nullptr : nodes[0]; // Return root node
}

// Compute the SHA256 hash of the given data using your custom calc_sha_256 function
string MerkleTree::hash(const string& data) const {
    uint8_t hash[SIZE_OF_SHA_256_HASH];  // Declare the hash array
    
    // Call the custom SHA-256 function
    calc_sha_256(hash, data.c_str(), data.size());

    // Convert hash to hexadecimal string
    stringstream ss;
    for (int i = 0; i < SIZE_OF_SHA_256_HASH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    
    return ss.str();
}

// Get the root hash of the Merkle tree
string MerkleTree::getRootHash() const {
    return root ? root->hash : ""; // Return empty if root is null
}
