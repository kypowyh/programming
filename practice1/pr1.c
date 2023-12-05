#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 256 // Размер хэш-таблицы
#define SET_SIZE 256 // Размер множества
#define STACK_SIZE 256 // Размер стэка
#define QUEUE_SIZE 256 // Размер очереди

// Структура для хранения элемента в хэш-таблице
struct HashTableEntry {
    char* key;
    char* value;
    struct HashTableEntry* next;
};

// Структура для хэш-таблицы
struct HashTable {
    struct HashTableEntry* table[TABLE_SIZE];
};

// Функция для вычисления хэш-кода
unsigned int hash(char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = hash * 31 + key[i];
    }
    return hash % TABLE_SIZE;
}

// Функция для создания новой хэш-таблицы
struct HashTable* createHashTable() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void HSET(struct HashTable* ht, char* key, char* value) {
    unsigned int index = hash(key);
    // Проверка наличия элемента с таким же ключом в ячейке хеш-таблицы.
    struct HashTableEntry* current = ht->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("Key '%s' already exists in the hash table.\n", key);
            return; // Элемент с таким ключом уже существует.
        }
        current = current->next;
    }
    struct HashTableEntry* newEntry = (struct HashTableEntry*)malloc(sizeof(struct HashTableEntry));
    newEntry->key = _strdup(key);
    newEntry->value = _strdup(value);
    newEntry->next = NULL;
    if (ht->table[index] == NULL) { // если индекс свободен
        ht->table[index] = newEntry; // сохраняем 
    }
    else {
        // Если в ячейке уже есть элементы, добавляем в следующий
        newEntry->next = ht->table[index]; // иначе сохраняем в виде связного списка
        ht->table[index] = newEntry;
    }
}

// Функция для поиска элемента по ключу
char* HGET(struct HashTable* ht, char* key) {
    unsigned int index = hash(key);
    struct HashTableEntry* entry = ht->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) { // если совпадает возвращаем
            return entry->value;
        }
        entry = entry->next; // иначе идем по списку
    }
    return NULL;
}

// Функция для удаления элемента по ключу
void HDEL(struct HashTable* ht, char* key) {
    unsigned int index = hash(key);
    struct HashTableEntry* entry = ht->table[index];
    struct HashTableEntry* prev = NULL; // указатель на предыдущий элемент
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) { // если значение нашлось 
            if (prev == NULL) { // если оно первое в списке 
                ht->table[index] = entry->next; // начало цепочки на следующий элемент 
            }
            else {
                prev->next = entry->next; // обновляем указатель на предыдущий элемент 
            }
            free(entry->key);
            free(entry->value); // освобождаем значения 
            free(entry);
            return;
        }
        prev = entry; // перемещаемся на следующий элемент
        entry = entry->next;
    }
}


struct HashSet {
    char* elements[SET_SIZE];
    int size;
};


struct HashSet* createHashSet() {
    struct HashSet* set = (struct HashSet*)malloc(sizeof(struct HashSet));
    for (int i = 0; i < SET_SIZE; i++) {
        set->elements[i] = NULL; // инициализация 
    }
    set->size = 0;
    return set;
}

const char* SADD(struct HashSet* set, const char* element) {
    unsigned int index = hash(element); // вычисление хэша
    if (set->size >= SET_SIZE) { // сет переполнен
        printf("Set is full. Cannot push more elements.\n");
        return;
    }

    if (set->elements[index] == NULL) { // если пуст
        set->elements[index] = _strdup(element); // добавляем значение 
        set->size++;
    }
    else {
        if (strcmp(set->elements[index], element) == 0) { // если элемент уже существует 
            printf("Value '%s' already exists in the set.\n", element);
        }
        else {
            for (int i = index; i < SET_SIZE; i++) { // от индекса к концу 
                if (set->elements[i] == NULL) { // находим пустое 
                    set->elements[i] = _strdup(element);
                    set->size++;// добавляем 
                }
            }
            printf("Unable to add value '%s' due to collision.\n", element);
        }
    }

    return;
}

int SISMEMBER(struct HashSet* set, const char* element) {
    unsigned int index = hash(element); // хэшируем идекс

    if (set->elements[index] == NULL) { // если индекс пуст
        return 0; // Элемент не найден
    }
    else {
        for (int i = index; i < SET_SIZE; i++) {
            if (set->elements[i] == NULL) { // если элемент пуст
                return 0; // Элемент не найден
            }
            if (strcmp(set->elements[i], element) == 0) { // если значение совпало
                return 1; // Элемент найден
            }
        }
    }

    return 0; // Элемент не найден
}

int SREM(struct HashSet* set, const char* element) {
    unsigned int index = hash(element);

    if (set->size == 0) { // стэк пуст
        printf("Set is empty. Cannot pop.\n");
        return;
    }

    if (set->elements[index] == NULL) { // если элемент пуст
        return 0; // Элемент не найден
    }
    else {
        for (int i = index; i < SET_SIZE; i++) {
            if (set->elements[i] == NULL) {
                return 0; // Элемент не найден
            }
            if (strcmp(set->elements[i], element) == 0) {
                free(set->elements[i]); // Освободим память
                set->elements[i] = NULL; // Установим элемент в NULL
                set->size--;
                return 1; // Элемент успешно удален
            }
        }
    }

    return 0; // Элемент не найден
}


// Структура для стэка
struct StackNode {
    char* data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    int size;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void SPUSH(struct Stack* stack, const char* value) {
    if (stack->size >= STACK_SIZE) { // стэк переполнен
        printf("Stack is full. Cannot push more elements.\n");
        return;
    }

    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = _strdup(value); // копируем значение 
    newNode->next = stack->top; 
    stack->top = newNode; // добавляем на вершину стэка 
    stack->size++; // увеличиваем размер
}


void SPOP(struct Stack* stack, char** value) {
    if (stack->size == 0) { // стэк пуст
        printf("Stack is empty. Cannot pop.\n");
        *value = NULL;
        return;
    }

    struct StackNode* topNode = stack->top; // получение значение из вершины
    *value = topNode->data; 
    stack->top = topNode->next; // перемещаем вершину на следующий 
    free(topNode); // освобождение памяти 
    stack->size--; // уменьшение размера
}

// Структура для очереди
struct QueueNode {
    char* data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
    int size;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}


void QPUSH(struct Queue* queue, const char* value) {
    if (queue->size >= QUEUE_SIZE) { // очередь переполнена 
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }

    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = _strdup(value);
    newNode->next = NULL;

    if (queue->size == 0) { // если очередь пуста
        queue->front = newNode; // добавляем в начало
    }
    else {
        queue->rear->next = newNode; // иначе в конец
    }

    queue->rear = newNode;
    queue->size++; // увеличиваем размерность
}

void QPOP(struct Queue* queue, char** value) {
    if (queue->size == 0) { // очередь пуста 
        printf("Queue is empty. Cannot dequeue.\n");
        *value = NULL;
        return;
    }

    struct QueueNode* frontNode = queue->front;
    *value = frontNode->data; // значение равно начальному элементу 
    queue->front = frontNode->next; // перемещаем следующее значение в начало

    if (queue->front == NULL) { // если начало пусто
        queue->rear = NULL; // Установка задней части в NULL, если очередь пуста.
    }

    free(frontNode);  // освобождаем память
    queue->size--; // уменьшаем размер 
}

void writeStackToFile(FILE* file, struct StackNode* node) {
    if (node == NULL) {
        return;
    }
    writeStackToFile(file, node->next);
    fprintf(file, "Stack: %s\n", node->data);
}

// Функция для рекурсивного чтения данных стека из файла

void writeDataToFile(const char* filename, struct HashTable* ht, struct HashSet* mySet, struct Stack* myStack, struct Queue* myQueue) {
    if (ht == NULL || mySet == NULL || myStack == NULL || myQueue == NULL) {
        printf("Invalid input. Cannot write data to file.\n");
        return;
    }

    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("Unable to open the file for writing.\n");
        return;
    }

    // Запись данных из хэш-таблицы в файл
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashTableEntry* entry = ht->table[i];
        while (entry != NULL) {
            fprintf(file, "Hash Table: %s %s\n", entry->key, entry->value);
            entry = entry->next;
        }
    }

    for (int i = 0; i < SET_SIZE; i++) {
        if (mySet->elements[i] != NULL) {
            fprintf(file, "Set: %s\n", mySet->elements[i]);
        }
    }

    writeStackToFile(file, myStack->top);

    struct QueueNode* queueNode = myQueue->front;
    while (queueNode != NULL) {
        fprintf(file, "Queue: %s\n", queueNode->data);
        queueNode = queueNode->next;
    }

    fclose(file);
}

void readDataFromFile(const char* filename, struct HashTable* ht, struct HashSet* mySet, struct Stack* myStack, struct Queue* myQueue) {
    if (ht == NULL || mySet == NULL || myStack == NULL || myQueue == NULL) {
        printf("Invalid input. Cannot read data from file.\n");
        return;
    }

    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Unable to open the file for reading.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Hash Table:", 11) == 0) {
            char key[256];
            char value[256];
            if (sscanf_s(line, "Hash Table: %s %s", key, sizeof(key), value, sizeof(value)) == 2) {
                HSET(ht, key, value);
            }
        }
        else if (strncmp(line, "Set:", 4) == 0) {
            char element[256];
            if (sscanf_s(line, "Set: %s", element, sizeof(element)) == 1) {
                SADD(mySet, element);
            }
        }
        else if (strncmp(line, "Stack:", 6) == 0) {
            char value[256];
            if (sscanf_s(line, "Stack: %s", value, sizeof(value)) == 1) {
                SPUSH(myStack, value);
            }
        }
        else if (strncmp(line, "Queue:", 6) == 0) {
            char value[256];
            if (sscanf_s(line, "Queue: %s", value, sizeof(value)) == 1) {
                QPUSH(myQueue, value);
            }
        }
    }

    fclose(file);
}

void processQuery(struct HashTable* ht, struct Set* mySet, struct Stack* myStack, struct Queue* myQueue, const char* query) {
    char* command = NULL;
    char* token = NULL;
    char* context = NULL;

    // Используем strtok_s для безопасного разделения строки
    command = strtok_s(query, " ", &context);

    if (command == NULL) {
        printf("Invalid query format.\n");
        return;
    }

    if (strcmp(command, "SADD") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            SADD(mySet, token);
            printf("The operation is completed!\n");
        }
        else {
            printf("Invalid SADD format.\n");
        }
    }
    else if (strcmp(command, "SREM") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            SREM(mySet, token);
            printf("The operation is completed!\n");
        }
        else {
            printf("Invalid SREM format.\n");
        }
    }
    else if (strcmp(command, "SISMEMBER") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            int result = SISMEMBER(mySet, token);
            printf("SISMEMBER result: %d\n", result);
        }
        else {
            printf("Invalid SISMEMBER format.\n");
        }
    }
    else if (strcmp(command, "SPUSH") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            SPUSH(myStack, token);
            printf("The operation is completed!\n");
        }
        else {
            printf("Invalid SPUSH format.\n");
        }
    }
    else if (strcmp(command, "SPOP") == 0) {
        char* value = NULL;
        SPOP(myStack, &value);
        if (value != NULL) {
            printf("SPOP result: %s\n", value);
            free(value);
        }
    }
    else if (strcmp(command, "QPUSH") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            QPUSH(myQueue, token);
            printf("The operation is completed!\n");
        }
        else {
            printf("Invalid QPUSH format.\n");
        }
    }
    else if (strcmp(command, "QPOP") == 0) {
        char* value = NULL;
        QPOP(myQueue, &value);
        if (value != NULL) {
            printf("QPOP result: %s\n", value);
            free(value);
        }
    }
    else if (strcmp(command, "HSET") == 0) {
        char* key = strtok_s(NULL, " ", &context);
        char* value = strtok_s(NULL, " ", &context);
        if (key != NULL && value != NULL) {
            HSET(ht, key, value);
            printf("The operation is completed!\n");
        }
        else {
            printf("Invalid HSET format.\n");
        }
    }
    else if (strcmp(command, "HGET") == 0) {
        char* key = strtok_s(NULL, " ", &context);
        if (key != NULL) {
            char* value = HGET(ht, key);
            if (value != NULL) {
                printf("HGET result: %s\n", value);
            }
            else {
                printf("Key '%s' not found in the hash table.\n", key);
            }
        }
        else {
            printf("Invalid HGET format.\n");
        }
    }
    else if (strcmp(command, "HDEL") == 0) {
        char* key = strtok_s(NULL, " ", &context);
        if (key != NULL) {
            HDEL(ht, key);
            printf("The operation is completed!\n");
        }
        else {
            printf("Invalid HDEL format.\n");
        }
    }
    else {
        printf("Unknown command: %s\n", command);
    }
}

int main(int argc, char* argv[]) {
    // Создание контейнеров
    struct HashTable* myHt = createHashTable();
    struct Set* mySet = createHashSet();
    struct Stack* myStack = createStack();
    struct Queue* myQueue = createQueue();

    // Проверка аргументов командной строки
    if (argc != 5) {
        printf("Usage: %s --file <filename> --query <query>\n", argv[0]);
        return 1;
    }

    // Получение имени файла и запроса
    const char* filename = argv[2];
    const char* query = argv[4];

    readDataFromFile(filename, myHt, mySet, myStack, myQueue);

    // Вызов функции для выполнения запроса
    processQuery(myHt, mySet, myStack, myQueue, query);

    // Запись данных обратно в файл
    writeDataToFile(filename, myHt, mySet, myStack, myQueue);

    // Освобождение памяти, выделенной для контейнеров
    free(myHt);
    free(mySet);
    free(myStack);
    free(myQueue);

    return 0;
}
