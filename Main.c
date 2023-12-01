#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookId;
    char title[50];
    char author[50];
    struct Book* next;
};

struct Queue {
    struct Book* front;
    struct Book* rear;
};

void initializeQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(struct Queue* queue, int bookId, const char* title, const char* author) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->bookId = bookId;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newBook;
    } else {
        queue->rear->next = newBook;
        queue->rear = newBook;
    }

    printf("Book with ID %d enqueued successfully.\n", bookId);
}

void dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. No book to dequeue.\n");
        return;
    }

    struct Book* temp = queue->front;
    queue->front = temp->next;
    free(temp);

    printf("Book dequeued successfully.\n");
}

void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Book* current = queue->front;
    printf("Books in the queue:\n");

    while (current != NULL) {
        printf("Book ID: %d, Title: %s, Author: %s\n", current->bookId, current->title, current->author);
        current = current->next;
    }
}

void freeQueue(struct Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

int main() {
    struct Queue bookstoreQueue;
    initializeQueue(&bookstoreQueue);

    int choice, bookId;
    char title[50], author[50];

    do {
        printf("\nBookstore Management Menu:\n");
        printf("1. Enqueue a Book\n");
        printf("2. Dequeue a Book\n");
        printf("3. Display Books in the Queue\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &bookId);
                printf("Enter Book Title: ");
                scanf("%s", title);
                printf("Enter Author: ");
                scanf("%s", author);
                enqueue(&bookstoreQueue, bookId, title, author);
                break;

            case 2:
                dequeue(&bookstoreQueue);
                break;

            case 3:
                displayQueue(&bookstoreQueue);
                break;

            case 4:
                printf("Exiting the program. Freeing memory...\n");
                freeQueue(&bookstoreQueue);
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}
