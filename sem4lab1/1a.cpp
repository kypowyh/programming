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

