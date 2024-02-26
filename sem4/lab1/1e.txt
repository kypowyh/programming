
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    char* data;
    struct node* next;
};

struct node* createNode(const char* data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode) {
        newNode->data = _strdup(data);
        newNode->next = NULL;
    }
    return newNode;
}


void insertFront(struct node** head, const char* data) {
    struct node* newNode = createNode(data);
    if (newNode) {
        newNode->next = *head;
        *head = newNode;
    }
}

void insertEnd(struct node** head, const char* data) {
    struct node* newNode = createNode(data);
    if (newNode) {
        if (*head == NULL) {
            *head = newNode;
        }
        else {
            struct node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}

void insertIndex(struct node** head, const char* data, int index) {
    if (index < 0)
        return;

    if (index == 0) {
        insertFront(head, data);
        return;
    }

    struct node* newNode = createNode(data);
    if (newNode == NULL)
        return;

    struct node* current = *head;
    int i = 0;
    while (i < index - 1 && current != NULL) {
        current = current->next;
        i++;
    }

    if (current == NULL)
        return;

    newNode->next = current->next;
    current->next = newNode;
}

void deleteFront(struct node** head) {
    if (*head) {
        struct node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void deleteEnd(struct node** head) {
    if (*head) {
        if ((*head)->next == NULL) {
            free(*head);
            *head = NULL;
        }
        else {
            struct node* current = *head;
            while (current->next->next != NULL) {
                current = current->next;
            }
            free(current->next);
            current->next = NULL;
        }
    }
}

void deleteIndex(struct node** head, int index) {
    if (*head == NULL || index < 0)
        return;

    if (index == 0) {
        deleteFront(head);
        return;
    }

    struct node* current = *head;
    int i = 0;
    while (i < index - 1 && current != NULL) {
        current = current->next;
        i++;
    }

    if (current == NULL || current->next == NULL)
        return;

    struct node* temp = current->next;
    current->next = current->next->next;
    free(temp);
}


void printList(const struct node* head) {
    const struct node* current = head;
    while (current) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

char* findIndex(const struct node* head, int index) {
    const struct node* current = head;
    int i = 0;

    while (current != NULL && i != index) {
        current = current->next;
        i++;
    }

    char* result = current->data;

    return result;
}

void deleteByValue(struct node** head, const char* value) {
    if (*head == NULL)
        return;

    struct node* current = *head;
    struct node* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data, value) == 0) { // Если найдено значение для удаления
            if (previous == NULL) { // Если это первый элемент
                *head = current->next;
                free(current);
                current = *head;
            }
            else {
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
        }
        else {
            previous = current;
            current = current->next;
        }
    }
}

int main() {
    struct node* myList = NULL;

    // Вставляем элементы в конец списка
    insertEnd(&myList, "1");
    insertEnd(&myList, "2");
    insertEnd(&myList, "3");

    printf("Original List:\n");
    printList(myList);

    // Вставляем элемент в начало списка
    insertFront(&myList, "4");
    // Вставляем элемент по индексу
    insertIndex(&myList, "3", 2);
    printf("\nList after insertions:\n");
    printList(myList);

    // Удаляем первый элемент
    deleteFront(&myList);
    // Удаляем последний элемент
    deleteEnd(&myList);
    // Удаляем элемент по индексу
    deleteIndex(&myList, 2);
    printf("\nList after deletions end, front and in index 2:\n");
    printList(myList);

    // Удаляем все узлы со значением "3"
    deleteByValue(&myList, "3");
    printf("\nList after deleting nodes with value 3:\n");
    printList(myList);

    // Находим элемент по индексу
    char* result = findIndex(myList, 0);
    printf("\nData at index 0: %s\n", result);

    // Освобождение памяти
    free(myList);
  

    return 0;
}