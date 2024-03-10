#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 51

// Struct to store information about a customer
typedef struct {
    char name[MAX_NAME_LENGTH];
    int tickets;
    int arrival_time;
} Customer;

// Struct for a linked list node of customers
typedef struct Node {
    Customer *data;
    struct Node *next;
} Node;

// Struct for a queue of customers
typedef struct {
    Node *front;
    Node *back;
    int size;
} Queue;

// Function to create a customer using dynamic memory allocation
Customer* createCustomer(char name[], int tickets, int arrival_time) {
    Customer *customer = (Customer *)malloc(sizeof(Customer));
    if (customer != NULL) {
        strcpy(customer->name, name);
        customer->tickets = tickets;
        customer->arrival_time = arrival_time;
    }
    return customer;
}

// Function to create a node for a linked list of customers
Node* createNode(Customer *customer) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = customer;
        node->next = NULL;
    }
    return node;
}

// Function to initialize a queue
Queue* initializeQueue() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue != NULL) {
        queue->front = NULL;
        queue->back = NULL;
        queue->size = 0;
    }
    return queue;
}

// Function to enqueue a customer into the queue
void enqueue(Queue *queue, Customer *customer) {
    Node *node = createNode(customer);
    if (node != NULL) {
        if (queue->back == NULL) {
            queue->front = node;
            queue->back = node;
        } else {
            queue->back->next = node;
            queue->back = node;
        }
        queue->size++;
    }
}

// Function to dequeue a customer from the queue
Customer* dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    Node *temp = queue->front;
    Customer *customer = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->back = NULL;
    }
    free(temp);
    queue->size--;
    return customer;
}

// Function to check if the queue is empty
int isEmpty(Queue *queue) {
    return queue->size == 0;
}

// Function to get the size of the queue
int getSize(Queue *queue) {
    return queue->size;
}

int main() {
    int n, b;
    scanf("%d %d", &n, &b);

    // Initialize queues for each booth
    Queue *booths[12];
    for (int i = 0; i < 12; i++) {
        booths[i] = initializeQueue();
    }

    // Read customer information and enqueue them based on the given rules
    for (int i = 0; i < n; i++) {
        char name[MAX_NAME_LENGTH];
        int tickets, arrival_time;
        scanf("%s %d %d", name, &tickets, &arrival_time);
        Customer *customer = createCustomer(name, tickets, arrival_time);
        int booth_index = i % b; // Calculate booth index based on customer index
        enqueue(booths[booth_index], customer);
    }

    // Process customers by booths
    for (int i = 0; i < b; i++) {
        printf("Booth %d\n", i + 1);
        while (!isEmpty(booths[i])) {
            Customer *customer = dequeue(booths[i]);
            int processing_time = 30 + customer->tickets * 5; // Calculate processing time
            int checkout_time = customer->arrival_time + processing_time;
            printf("%s from line %d checks out at time %d.\n", customer->name, i + 1, checkout_time);
            free(customer); // Free memory for the customer
        }
        printf("\n");
    }

    // Free memory for queues
    for (int i = 0; i < 12; i++) {
        while(!isEmpty(booths[i]));
        free(booths[i]);
    }

    return 0;
}
