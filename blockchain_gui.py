import hashlib
import json
import time
from typing import List, Optional
import tkinter as tk
from tkinter import messagebox

# Transaction class (updated to match C++ logic)
class Transaction:
    def __init__(self, sender: str, receiver: str, amount: float):
        self.sender = sender
        self.receiver = receiver
        self.amount = amount
        # Set timestamp to the current time in ISO 8601 format
        self.timestamp = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())

    def serialize(self) -> str:
        # Serializes the transaction to a string (similar to C++ implementation)
        return f"{self.sender}{self.receiver}{self.amount}{self.timestamp}"

    def __eq__(self, other: object) -> bool:
        # Equality operator for comparing transactions
        if isinstance(other, Transaction):
            return (self.sender == other.sender and
                    self.receiver == other.receiver and
                    self.amount == other.amount and
                    self.timestamp == other.timestamp)
        return False

# MerkleNode class (similar to C++ structure)
class MerkleNode:
    def __init__(self, hash: str):
        self.hash = hash
        self.left: Optional[MerkleNode] = None
        self.right: Optional[MerkleNode] = None

# MerkleTree class (builds the tree from a list of transactions)
class MerkleTree:
    def __init__(self, transactions: List[Transaction]):
        self.root = self.build_tree(transactions)

    def build_tree(self, transactions: List[Transaction]) -> Optional[MerkleNode]:
        nodes = [MerkleNode(self.hash(transaction.serialize())) for transaction in transactions]

        while len(nodes) > 1:
            new_level = []
            for i in range(0, len(nodes), 2):
                if i + 1 < len(nodes):
                    combined_hash = nodes[i].hash + nodes[i + 1].hash
                    new_node = MerkleNode(self.hash(combined_hash))
                    new_node.left = nodes[i]
                    new_node.right = nodes[i + 1]
                    new_level.append(new_node)
                else:
                    new_level.append(nodes[i])  # Handle odd number of nodes
            nodes = new_level  # Move to the next level

        return nodes[0] if nodes else None  # Return root node

    # SHA-256 hash function
    def hash(self, data: str) -> str:
        return hashlib.sha256(data.encode()).hexdigest()

    def get_root_hash(self) -> str:
        return self.root.hash if self.root else ""

# Block class (represents a single block in the blockchain)
class Block:
    def __init__(self, index: int, previous_hash: str, transactions: List[Transaction], merkle_tree: MerkleTree):
        self.index = index
        self.previous_hash = previous_hash
        self.transactions = transactions
        self.timestamp = str(int(time.time()))
        self.merkle_tree = merkle_tree
        self.merkle_root = self.merkle_tree.get_root_hash()
        self.block_hash = self.calculate_hash()

    def calculate_hash(self) -> str:
        block_data = f"{self.index}{self.previous_hash}{self.merkle_root}{self.timestamp}"
        return hashlib.sha256(block_data.encode()).hexdigest()

    def get_hash(self) -> str:
        return self.block_hash

# Blockchain class (for managing the blockchain)
class Blockchain:
    def __init__(self):
        self.chain = []
        self.pending_transactions = []

    def add_transaction(self, transaction: Transaction):
        self.pending_transactions.append(transaction)

    def add_block(self):
        if self.pending_transactions:
            block_index = len(self.chain)
            previous_block = self.chain[-1] if self.chain else None
            previous_hash = previous_block.get_hash() if previous_block else "0"
            merkle_tree = MerkleTree(self.pending_transactions)
            new_block = Block(block_index, previous_hash, self.pending_transactions, merkle_tree)
            self.chain.append(new_block)
            self.pending_transactions.clear()

    def validate_chain(self):
        for i in range(1, len(self.chain)):
            current_block = self.chain[i]
            previous_block = self.chain[i - 1]
            if current_block.previous_hash != previous_block.get_hash():
                return False
            if current_block.merkle_root != current_block.merkle_tree.get_root_hash():
                return False
        return True

    def find_transaction(self, transaction: Transaction) -> bool:
        for block in self.chain:
            if transaction in block.transactions:
                return True
        return False

# GUI for Blockchain System with integrated Merkle Tree functionality
class BlockchainGUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Blockchain System")
        self.geometry("600x700")
        self.configure(bg="#1f1f2e")

        self.blockchain = Blockchain()

        self.button_font = ("Helvetica", 12, "bold")
        self.text_font = ("Helvetica", 12)
        self.button_bg = "#4e73df"
        self.button_fg = "white"

        title_label = tk.Label(self, text="Blockchain System", font=("Helvetica", 18, "bold"), bg="#1f1f2e", fg="white")
        title_label.pack(pady=20)

        # Create the GUI buttons
        self.add_transaction_button = self.create_button("Add Transaction", self.add_transaction)
        self.add_block_button = self.create_button("Add Block", self.add_block)
        self.view_transactions_button = self.create_button("View Transactions", self.view_transactions)
        self.view_blockchain_button = self.create_button("View Blockchain", self.view_blockchain)
        self.verify_transaction_button = self.create_button("Verify Transaction", self.verify_transaction)
        self.validate_chain_button = self.create_button("Validate Blockchain", self.validate_chain)
        self.exit_button = self.create_button("Exit", self.exit_program)

        # Display area
        self.output_frame = tk.Frame(self)
        self.output_frame.pack(pady=10, expand=True, fill="both")
        self.output_display = tk.Text(self.output_frame, height=15, wrap="word", font=self.text_font, bg="#e9ecef", fg="#343a40", borderwidth=0, padx=10, pady=10)
        self.output_display.pack(side="left", expand=True, fill="both")
        self.scrollbar = tk.Scrollbar(self.output_frame, command=self.output_display.yview)
        self.scrollbar.pack(side="right", fill="y")
        self.output_display.config(yscrollcommand=self.scrollbar.set)
        self.output_display.insert("end", "Welcome to the Blockchain System\n")
        self.output_display.config(state=tk.DISABLED)

        # Status bar
        self.status_bar = tk.Label(self, text="Ready", bd=1, relief="sunken", anchor="w", bg="#1f1f2e", fg="white")
        self.status_bar.pack(side="bottom", fill="x")

    def create_button(self, text, command):
        button = tk.Button(self, text=text, command=command, font=self.button_font, bg=self.button_bg, fg=self.button_fg, width=20)
        button.pack(pady=5)
        button.bind("<Enter>", lambda e: button.config(bg="#2e59d9"))
        button.bind("<Leave>", lambda e: button.config(bg=self.button_bg))
        return button

    def update_status(self, message):
        self.status_bar.config(text=message)

    def add_transaction(self):
        add_txn_window = tk.Toplevel(self)
        add_txn_window.title("Add Transaction")
        add_txn_window.geometry("400x300")
        add_txn_window.configure(bg="#f1f1f1")

        sender_label = tk.Label(add_txn_window, text="Sender:", bg="#f1f1f1")
        sender_label.pack(pady=10)
        sender_entry = tk.Entry(add_txn_window, width=30)
        sender_entry.pack()

        receiver_label = tk.Label(add_txn_window, text="Receiver:", bg="#f1f1f1")
        receiver_label.pack(pady=10)
        receiver_entry = tk.Entry(add_txn_window, width=30)
        receiver_entry.pack()

        amount_label = tk.Label(add_txn_window, text="Amount:", bg="#f1f1f1")
        amount_label.pack(pady=10)
        amount_entry = tk.Entry(add_txn_window, width=30)
        amount_entry.pack()

        def submit_transaction():
            sender = sender_entry.get()
            receiver = receiver_entry.get()
            try:
                amount = float(amount_entry.get())
                if sender and receiver and amount:
                    transaction = Transaction(sender, receiver, amount)
                    self.blockchain.add_transaction(transaction)
                    self.output_display.config(state=tk.NORMAL)
                    self.output_display.insert("end", f"Transaction added: {sender} -> {receiver} : {amount}\n")
                    self.output_display.config(state=tk.DISABLED)
                    add_txn_window.destroy()
                    self.update_status("Transaction added successfully.")
                else:
                    raise ValueError
            except ValueError:
                messagebox.showerror("Invalid Input", "Please enter valid values.")

        submit_button = tk.Button(add_txn_window, text="Submit", command=submit_transaction, bg="#4e73df", fg="white", font=self.button_font)
        submit_button.pack(pady=20)

    def add_block(self):
        self.blockchain.add_block()
        self.output_display.config(state=tk.NORMAL)
        self.output_display.insert("end", f"Block {len(self.blockchain.chain) - 1} added to blockchain.\n")
        self.output_display.config(state=tk.DISABLED)
        self.update_status("Block added successfully.")

    def view_transactions(self):
        self.output_display.config(state=tk.NORMAL)
        self.output_display.delete(1.0, "end")
        self.output_display.insert("end", "Pending Transactions:\n")
        for txn in self.blockchain.pending_transactions:
            self.output_display.insert("end", f"{txn.sender} -> {txn.receiver} : {txn.amount} at {txn.timestamp}\n")
        self.output_display.config(state=tk.DISABLED)

    def view_blockchain(self):
        self.output_display.config(state=tk.NORMAL)
        self.output_display.delete(1.0, "end")
        self.output_display.insert("end", "Blockchain:\n")
        for block in self.blockchain.chain:
            self.output_display.insert("end", f"Block {block.index}: {block.block_hash}\n")
        self.output_display.config(state=tk.DISABLED)

    def verify_transaction(self):
        verify_txn_window = tk.Toplevel(self)
        verify_txn_window.title("Verify Transaction")
        verify_txn_window.geometry("400x200")
        verify_txn_window.configure(bg="#f1f1f1")

        sender_label = tk.Label(verify_txn_window, text="Sender:", bg="#f1f1f1")
        sender_label.pack(pady=10)
        sender_entry = tk.Entry(verify_txn_window, width=30)
        sender_entry.pack()

        receiver_label = tk.Label(verify_txn_window, text="Receiver:", bg="#f1f1f1")
        receiver_label.pack(pady=10)
        receiver_entry = tk.Entry(verify_txn_window, width=30)
        receiver_entry.pack()

        amount_label = tk.Label(verify_txn_window, text="Amount:", bg="#f1f1f1")
        amount_label.pack(pady=10)
        amount_entry = tk.Entry(verify_txn_window, width=30)
        amount_entry.pack()

        def submit_verification():
            sender = sender_entry.get()
            receiver = receiver_entry.get()
            try:
                amount = float(amount_entry.get())
                if sender and receiver and amount:
                    txn_to_verify = Transaction(sender, receiver, amount)
                    if self.blockchain.find_transaction(txn_to_verify):
                        self.output_display.config(state=tk.NORMAL)
                        self.output_display.insert("end", f"Transaction {sender} -> {receiver} : {amount} exists in blockchain.\n")
                        self.output_display.config(state=tk.DISABLED)
                        verify_txn_window.destroy()
                    else:
                        messagebox.showerror("Not Found", "Transaction not found in the blockchain.")
                else:
                    raise ValueError
            except ValueError:
                messagebox.showerror("Invalid Input", "Please enter valid values.")

        submit_button = tk.Button(verify_txn_window, text="Submit", command=submit_verification, bg="#4e73df", fg="white", font=self.button_font)
        submit_button.pack(pady=20)

    def validate_chain(self):
        if self.blockchain.validate_chain():
            messagebox.showinfo("Validation", "Blockchain is valid.")
        else:
            messagebox.showerror("Validation", "Blockchain is invalid!")

    def exit_program(self):
        self.quit()

# Main execution
if __name__ == "__main__":
    app = BlockchainGUI()
    app.mainloop()
