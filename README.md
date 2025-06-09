# Bank Management System (C Language)
    This is a simple command-line Bank Management System implemented in C, developed as part of a class assignment.
    
    The system simulates core banking functionalities using linked lists and custom structs to manage customer accounts and financial transactions.

Features
    Customer Management
    
    Create new customers with randomly generated Customer & Transaction IDs
    
    Password-protected account deletion (only if balance is zero)
    
    XOR-based simple password encryption
    
    Transaction Processing
    
    Supports deposit and transfer transactions
    
    Verifies source account, balance sufficiency, and password
    
    Groups transactions in blocks of 5 (basic blockchain-style structure)
    
    Data Structures
    
    Singly linked list to manage customer accounts
    
    Custom TransactionBlock structure for handling grouped transactions

Technologies Used
    Language: C
    
    Concepts: Pointers, Structs, Linked Lists, Input Handling, Random ID Generation, Basic Encryption

 Compilation

    gcc -o bank bank.c
    ./bank

