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

    




https://github.com/user-attachments/assets/3d356771-aa8e-486d-8072-0aa3db030d60



https://github.com/user-attachments/assets/8c19fd06-b90e-45c9-9667-52260c9ce2b6




https://github.com/user-attachments/assets/dbd53a5e-ceb5-4018-bb7d-c3833141f594



https://github.com/user-attachments/assets/54cd93e7-16ca-43b2-bfab-7d15502a0908



