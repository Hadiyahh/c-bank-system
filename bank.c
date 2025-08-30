#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TRUE (1 == 1)
#define FALSE (!TRUE)

typedef struct
{
    char customerID[12];
    char transactionID[12];
    char firstName[50];
    char lastName[50];
    double balance;
    char password[50];
} Customer;

typedef struct Node
{
    Customer data;
    struct Node *next;
} Node;

typedef struct
{
    char sourceTransactionID[12];
    char destinationTransactionID[12];
    double amount;
} Transaction;

typedef struct TransactionBlock
{
    Transaction transactions[5];
    int numTransactions;
    struct TransactionBlock *next;
} TransactionBlock;

// Function prototypes
Node *newCustomerNode();
void generateCustomerID(char *customerID);
void generateTransactionID(char *transactionID);
void deleteCustomer(Node *customers, char *customerID);
void simpleEncryptDecrypt(char *input); // Simple XOR encryption for demonstration
void addTransaction(Node *customers, TransactionBlock *transactions);
int verifyPassword(char *wantPassword, char *inPassword);
Node *findCustomerByTransactionID(Node *customers, char *input);
int hasCustomers(Node *customers);

int main()
{
    int option = 0;
    Node *customers = (Node *)malloc(sizeof(Node));                                        // sentinel node (dummy customers)
    TransactionBlock *transactions = (TransactionBlock *)malloc(sizeof(TransactionBlock)); // sentinel node (dummy transactions)
    srand(time(NULL));

    while (option != 5)
    {
        printf("\nBank Menu:\n");
        printf("1 - Create new customer\n");
        printf("2 - Delete customer\n");
        printf("3 - Display customer\n");
        printf("4 - Insert transactions\n");
        printf("5 - Exit\n");
        printf("Please select an option: ");
        if (scanf("%d", &option) == EOF)
        {
            clearerr(stdin);
            return 0;
        }

        switch (option)
        {
        case 1:
        {
            Node *cur = customers;
            while (cur->next != NULL)
            {
                cur = cur->next;
            }
            cur->next = newCustomerNode();
            cur = cur->next;
            printf("Customer Successfully Saved with customer ID: %s\n", cur->data.customerID);

            break;
        }
        case 2:
        {
            if (!hasCustomers(customers))
            {
                printf("Error: No customers exist. Please create a customer first.\n");
                break;
            }
            char customerID[12];
            printf("Enter the customer ID to delete: ");
            if (scanf("%11s", customerID) == EOF)
            {
                clearerr(stdin);
                continue;
            }
            deleteCustomer(customers, customerID);
            break;
        }
        case 3:
        {
            if (!hasCustomers(customers))
            {
                printf("Error: No customers exist. Please create a customer first.\n");
                break;
            }
            Node *cur = customers->next;
            while (cur != NULL)
            {
                printf("Customer ID: %s\n", cur->data.customerID);
                printf("Name: %s %s\n", cur->data.firstName, cur->data.lastName);
                printf("Balance: $%.2f\n", cur->data.balance);
                printf("Secret Password: ************\n");
                printf("Transaction ID: %s\n", cur->data.transactionID);
                printf("\n");
                cur = cur->next;
            }
            break;
        }
        case 4:
        {
            if (!hasCustomers(customers))
            {
                printf("Error: No customers exist. Please create a customer first.\n");
                break;
            }
            addTransaction(customers, transactions);
            break;
        }
        case 5:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    // Free all nodes before exiting
    Node *current = customers;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

Node *newCustomerNode()
{
    char confirmpassword[50];

    Customer cust;
    if (!cust.customerID)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    printf("Enter first name: ");
    if (scanf("%49s", cust.firstName) == EOF)
    {
        clearerr(stdin);
        return NULL;
    }

    printf("Enter last name: ");
    if (scanf("%49s", cust.lastName) == EOF)
    {
        clearerr(stdin);
        return NULL;
    }

    printf("Enter initial balance: ");
    if (scanf("%lf", &cust.balance) == EOF)
    {
        clearerr(stdin);
        return NULL;
    }

    do
    {
        printf("Enter a secret password: ");
        if (scanf("%49s", cust.password) == EOF)
        {
            clearerr(stdin);
            return NULL;
        }

        printf("Confirm Password: ");
        if (scanf("%49s", confirmpassword) == EOF)
        {
            clearerr(stdin);
            return NULL;
        }
    } while ((strcmp(cust.password, confirmpassword) != 0));

    printf("Passwords match.\n");

    simpleEncryptDecrypt(cust.password);

    generateCustomerID(cust.customerID);
    generateTransactionID(cust.transactionID);

    Node *out = (Node *)malloc(sizeof(Node));
    out->data = cust;
    out->next = NULL;

    return out;
}

void generateCustomerID(char *customerid)
{
    for (int i = 0; i < 5; i++)
    {
        customerid[i] = 'A' + (rand() % 26); // random upercase letters,
    }
    customerid[5] = '-';

    for (int i = 6; i < 11; i++)
    {
        customerid[i] = '0' + (rand() % 10); // random digits from 0-9
    }

    customerid[11] = '\0'; // null to terminate the string
}

void generateTransactionID(char *transactionid)
{
    for (int i = 0; i < 5; i++)
    {
        transactionid[i] = 'A' + (rand() % 26);
    }
    transactionid[5] = '-';

    for (int i = 6; i < 11; i++)
    {
        transactionid[i] = '0' + (rand() % 10);
    }

    transactionid[11] = '\0';
}

void deleteCustomer(Node *customers, char *customerID)
{
    Node *cur = customers;
    while (cur->next != NULL && strcmp(cur->next->data.customerID, customerID) != 0)
    {
        cur = cur->next;
    }

    if (cur->next == NULL)
    {
        printf("Customer not found.\n");
        return;
    }

    if (cur->next->data.balance != 0)
    {
        printf("Cannot delete customer: balance is not zero.\n");
        return;
    }

    char enteredPassword[50];
    printf("Enter password to confirm deletion: ");
    if (scanf("%49s", enteredPassword) == EOF)
    {
        clearerr(stdin);
        return;
    }
    simpleEncryptDecrypt(enteredPassword);

    if (strcmp(cur->next->data.password, enteredPassword) != 0)
    {
        printf("Password incorrect. Cannot delete customer.\n");
        return;
    }

    Node *tmp = cur->next;
    cur->next = cur->next->next;
    free(tmp);
    printf("Customer deleted successfully.\n");
}

void simpleEncryptDecrypt(char *input)
{
    char key = 'K'; // Simple encryption key
    while (*input)
    {
        *input ^= key;
        input++;
    }
}

void addTransaction(Node *customers, TransactionBlock *transactions)
{
    TransactionBlock *blocks = (TransactionBlock *)malloc(sizeof(TransactionBlock));
    if (blocks == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    blocks->numTransactions = 0;
    int i = 0;
    char choice;
    
    do {
        if (i >= 5) {
            printf("Maximum number of transactions (5) reached in this block.\n");
            break;
        }
        
        printf("Enter source transaction ID: ");

        if (scanf("%11s", blocks->transactions[i].sourceTransactionID) == EOF)
        {
            clearerr(stdin);
            return;
        }

        Node *srcCustomer = findCustomerByTransactionID(customers, blocks->transactions[i].sourceTransactionID);
        if (srcCustomer == NULL && strcmp(blocks->transactions[i].sourceTransactionID, "Deposit") != 0)
        {
            printf("Cannot find inputted sourceID\n");
            continue;
        }

        printf("Enter transaction amount: ");
        if (scanf("%lf", &blocks->transactions[i].amount) == EOF)
        {
            clearerr(stdin);
            return;
        }

        printf("Enter destination transaction ID: ");
        if (scanf("%11s", blocks->transactions[i].destinationTransactionID) == EOF)
        {
            clearerr(stdin);
            return;
        }

        Node *dstCustomer = findCustomerByTransactionID(customers, blocks->transactions[i].destinationTransactionID);
        if (dstCustomer == NULL)
        {
            printf("Cannot find inputted destinationID\n");
            continue;
        }

        if (srcCustomer != NULL)
        {
            // We enter here if transaction is NOT Deposit.
            char inPassword[50];
            printf("Enter password: ");
            if (scanf("%49s", inPassword) == EOF)
            {
                clearerr(stdin);
                continue;
            }

            simpleEncryptDecrypt(inPassword);
            if (!verifyPassword(srcCustomer->data.password, inPassword))
            {
                printf("Incorrect password; voiding transaction :(\n");
                continue;
            }
        }

        if (srcCustomer != NULL)
        {
            srcCustomer->data.balance -= blocks->transactions[i].amount;
        }
        if (dstCustomer != NULL)
        {
            dstCustomer->data.balance += blocks->transactions[i].amount;
        }

        blocks->numTransactions++;
        printf("Transaction added successfully.\n");
        i++;
        
        printf("Do you want to add another transaction? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    free(blocks);
}

Node *findCustomerByTransactionID(Node *customers, char *input)
{
    Node *cur = customers;
    while (cur != NULL && strcmp(cur->data.transactionID, input) != 0)
    {

        cur = cur->next;
    }

    return cur;
}

int verifyPassword(char *wantPassword, char *inPassword)
{
    return strcmp(wantPassword, inPassword) == 0;
}

int hasCustomers(Node *customers)
{
    return customers->next != NULL;
}
