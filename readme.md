# Blockchain with Merkle Trees

This project implements a simple blockchain in C++ using Merkle trees for secure and efficient transaction verification. The blockchain supports the addition of new blocks containing multiple transactions, and each block’s integrity is verified by hashing the transactions into a Merkle root.

---

## Table of Contents

- [Features](#features)
- [Project Structure](#project-structure)
- [Setup and Compilation](#setup-and-compilation)
- [Usage](#usage)
- [Example](#example)
- [References](#references)

---

## Features

- **Blockchain and Block Classes**: Manages the linked blocks of the blockchain.
- **Merkle Tree Implementation**: Constructs a Merkle tree for transaction validation.
- **Standalone SHA-256 Hashing**: Utilizes a custom SHA-256 hashing algorithm.
- **Transaction Verification**: Each transaction in the blockchain is verified using Merkle trees.
- **User Options**: View, add, and verify transactions in the blockchain.

---

## Project Structure

The project has the following structure:

```plaintext
project-folder/
├── include/
│   ├── Blockchain.h       # Blockchain class definition
│   ├── Block.h            # Block class definition
│   ├── MerkleTree.h       # Merkle Tree class definition
│   ├── Transaction.h      # Transaction class definition
│   └── sha256.h           # Standalone SHA-256 implementation header
├── src/
│   ├── Blockchain.cpp     # Blockchain class implementation
│   ├── Block.cpp          # Block class implementation
│   ├── MerkleTree.cpp     # Merkle Tree class implementation
│   ├── Transaction.cpp    # Transaction class implementation
│   ├── sha256.cpp         # Standalone SHA-256 implementation source
│   └── main.cpp           # Main entry point
└── README.md              # Project README file

---

## Setup and Compilation

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed, such as `g++` (included with MinGW on Windows).
- **Command Line**: Use the terminal on Linux/Mac or Command Prompt/PowerShell on Windows.

### Compilation

1. **Clone the repository** (if not done already) or create the project folder.
2. **Compile** the project by navigating to the root directory and running the following command:

   ```bash
   g++ src/*.cpp -o blockchainApp
   ```

3. **Run** the executable:

   ```bash
   ./blockchainApp   # On Linux/Mac
   blockchainApp.exe # On Windows
   ```

---

## Usage

Upon running, the application will prompt you with options to:

1. **View Blockchain**: Displays all blocks in the blockchain, including transaction details.
2. **Add a New Transaction**: Adds a new transaction between a sender and receiver.
3. **Add a Block**: Adds a new block containing pending transactions to the blockchain.
4. **Verify a Transaction**: Verifies the presence of a transaction in the blockchain using the Merkle root.
5. **Validate Blockchain**: Checks the integrity of the blockchain.

Use these options to interact with the blockchain and perform operations. 

---

## Example

1. **Start the Application**:
   ```bash
   ./blockchainApp
   ```

2. **Add Transactions**: You can add multiple transactions specifying sender, receiver, and amount.

3. **Add Block**: After adding transactions, you can create a new block that incorporates the transactions using a Merkle root for verification.

4. **Verify Blockchain**: After adding blocks, use this option to ensure the blockchain is valid and each block’s hash is correctly calculated.

### Sample Output

Below is an example of the output when running the application:

```plaintext
Welcome to the Blockchain App!
1. View Blockchain
2. Add Transaction
3. Add Block
4. Verify Transaction
5. Validate Blockchain
Choose an option: 
```

---

## References

1. **Merkle Tree** - [Wikipedia](https://en.wikipedia.org/wiki/Merkle_tree)
2. **Blockchain Basics** - [Investopedia](https://www.investopedia.com/terms/b/blockchain.asp)
3. **SHA-256 Algorithm** - [SHA-2 Wikipedia](https://en.wikipedia.org/wiki/SHA-2)

---
