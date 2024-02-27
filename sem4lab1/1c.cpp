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

// добавление в конец
void insertEnd(struct node** head, const char* data) {
	struct node* newNode = createNode(data);
	if (newNode) {
		if (*head == NULL) {
			*head = newNode; // голову на новое значение
		}
		else {
			struct node* current = *head;
			while (current->next != NULL) { // проходимся по списку
				current = current->next;
			}
			current->next = newNode; // добавляем
		}
	}
}