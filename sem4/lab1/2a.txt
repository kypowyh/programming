#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale>

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

// Проверка, является ли стек полным
int isFull(Stack* stack) {
    return stack->top == STACK_SIZE - 1;
}

// Проверка, является ли стек пустым
int isEmpty(Stack* stack) {
    return stack->top == -1;
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
        printf("null\n");
        return '\0'; // 
    }
    return stack->data[stack->top--];
}

int precedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

// Преобразование инфиксного выражения в постфиксное
void Postfix(char* infix, char* postfix) {
    Stack stack;
    initStack(&stack);

    int i = 0;
    int j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        }

        else if (infix[i] == '(') {
            push(&stack, infix[i]);
        }

        else if (infix[i] == ')') {

            while (!isEmpty(&stack) && stack.data[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (!isEmpty(&stack) && stack.data[stack.top] == '(') {
                pop(&stack);
            }
            else {
                printf("Некорректное выражение: пропущена открывающая скобка\n");
                exit(EXIT_FAILURE);

            }
        }
        else { // Если символ оператор
            while (!isEmpty(&stack) && precedence(infix[i]) <= precedence(stack.data[stack.top])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
        i++;
    }

    // Выталкиваем оставшиеся операторы из стека
    while (!isEmpty(&stack)) {
        if (stack.data[stack.top] == '(') {
            printf("Некорректное выражение: пропущена закрывающая скобка\n");
            exit(EXIT_FAILURE);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0'; // Добавляем завершающий нуль-символ
}

int poland(char* expression) {
    Stack stack;
    initStack(&stack);

    int i = 0;
    int numCount = 0;
    int opCount = 0;

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            // Если символ цифра помещаем ее в стек
            push(&stack, expression[i] - '0');
            numCount++;
        }
        else {
            // Если символ оператор извлекаем операнды из стека выполняем операцию и помещаем результат обратно в стек
            opCount++;
            if (opCount > numCount - 1) {
                printf("Ошибка: недостаточно операндов для операции\n");
                exit(EXIT_FAILURE);
            }
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (expression[i]) {
            case '+':
                push(&stack, operand1 + operand2);
                break;
            case '-':
                push(&stack, operand1 - operand2);
                break;
            case '*':
                push(&stack, operand1 * operand2);
                break;
            case '/':
                push(&stack, operand1 / operand2);
                break;
            default:
                printf("Ошибка: недопустимый оператор\n");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }

    // Результат вычисления будет на вершине стека
    if (numCount - opCount != 1) {
        printf("Ошибка: недостаточно операторов для операций\n");
        exit(EXIT_FAILURE);
    }
    return pop(&stack);
}


int main() {
    setlocale(LC_ALL, "rus");
    char infix[] = "12+4*3+";
    char postfix[STACK_SIZE];
    Postfix(infix, postfix);
    printf("Постфиксная запись: %s\n", postfix);
    int result = poland(postfix);
    printf("Результат: %d\n", result);
    return 0;
}