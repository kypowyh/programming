#include <stdio.h>

#define STACK_SIZE 100

// Структура стека
typedef struct Stack {
    char data[STACK_SIZE];
    int top;
} Stack;

// Инициализация стека
void initStack(Stack* stack) {
    stack->top = -1;
}

// Помещение элемента в стек
void push(Stack* stack, char value) {
    if (stack->top == STACK_SIZE - 1) {
        printf("Стек полон\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// Извлечение элемента из стека
char pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Стек пуст\n");
        return '\0';
    }
    return stack->data[stack->top--];
}

void functionD(Stack* stack) {
    printf("function D\n");
    push(stack, 'D');
}

void functionC(Stack* stack) {
    printf("function C\n");
    push(stack, 'C');

    // Вызываем функцию D
    functionD(stack);
}

void functionB(Stack* stack) {
    printf("function B\n");
    push(stack, 'B');

    // Вызываем функцию C
    functionC(stack);
}

void functionA(Stack* stack) {
    printf("function A\n");
    push(stack, 'A');

    // Вызываем функцию B
    functionB(stack);
}

int main() {
    Stack callStack;
    initStack(&callStack);

    // Начинаем с вызова функции A
    functionA(&callStack);

    // Выводим стек вызовов
    printf("Stack:\n");
    while (callStack.top != -1) {
        printf("%c\n", pop(&callStack));
    }

    return 0;
}

