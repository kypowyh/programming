#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>

CRITICAL_SECTION myMutex; // инициализируем мьютекс

#pragma comment(lib, "ws2_32.lib")

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

int HSET(struct HashTable* ht, char* key, char* value) {
    unsigned int index = hash(key);
    // Проверка наличия элемента с таким же ключом в ячейке хеш-таблицы.
    struct HashTableEntry* current = ht->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return 0; // Элемент с таким ключом уже существует.
        }
        current = current->next;
    }
    struct HashTableEntry* newEntry = (struct HashTableEntry*)malloc(sizeof(struct HashTableEntry));
    newEntry->key = _strdup(key);
    newEntry->value = _strdup(value);
    newEntry->next = NULL;
    if (ht->table[index] == NULL) { // если индекс свободен лобавляем элемент
        ht->table[index] = newEntry;
    }
    else {
        // Если в ячейке уже есть элементы, добавляем в следующий
        newEntry->next = ht->table[index]; // иначе в виде связного списка сохраняем
        ht->table[index] = newEntry;
    }
    return 1;
}

// Функция для поиска элемента по ключу
char* HGET(struct HashTable* ht, char* key) {
    unsigned int index = hash(key);
    struct HashTableEntry* entry = ht->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value; // возвращает значение 
        }
        entry = entry->next; // иначе ищет в списке
    }
    return NULL;
}

// Функция для удаления элемента по ключу
void HDEL(struct HashTable* ht, char* key) {
    unsigned int index = hash(key); // вычисляем хэш ключа
    struct HashTableEntry* entry = ht->table[index];
    struct HashTableEntry* prev = NULL; // указатель на предыдущий элемент
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) { // если значение нашлось 
            if (prev == NULL) { // если значение первое в списке
                ht->table[index] = entry->next; // начало цепочки на следующий элемент
            }
            else {
                prev->next = entry->next; // иначе обновляем указатель на предыдущий элемент
            }
            free(entry->key);
            free(entry->value);
            free(entry);
            return;
        }
        prev = entry; // перемещение на следующий элемент
        entry = entry->next;
    }
}


struct HashSet {
    char* elements[SET_SIZE];
};


struct HashSet* createHashSet() {
    struct HashSet* set = (struct HashSet*)malloc(sizeof(struct HashSet));
    for (int i = 0; i < SET_SIZE; i++) {
        set->elements[i] = NULL; // инициализация массива элементов
    }
    return set;
}

int SADD(struct HashSet* set, const char* element) {
    unsigned int index = hash(element);

    if (set->elements[index] == NULL) { // если индекс пуст копируем значение 
        set->elements[index] = _strdup(element);
        return 1;
    }
    else {
        if (strcmp(set->elements[index], element) == 0) { // проверяем на совпадение 
            return 0;
        }
        else {
            for (int i = index; i < SET_SIZE; i++) { // иначе добавляем 
                if (set->elements[i] == NULL) {
                    set->elements[i] = _strdup(element);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int SISMEMBER(struct HashSet* set, const char* element) {
    unsigned int index = hash(element);

    if (set->elements[index] == NULL) {
        return 0; // Элемент не найден
    }
    else {
        for (int i = index; i < SET_SIZE; i++) {
            if (set->elements[i] == NULL) {
                return 0; // Элемент не найден
            }
            if (strcmp(set->elements[i], element) == 0) {
                return 1; // Элемент найден
            }
        }
    }

    return 0; // Элемент не найден
}

int SREM(struct HashSet* set, const char* element) {
    unsigned int index = hash(element);

    if (set->elements[index] == NULL) {
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
    if (stack->size >= STACK_SIZE) {
        printf("Stack is full. Cannot push more elements.\n");
        return;
    }

    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = _strdup(value);
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}


void SPOP(struct Stack* stack, char** value) {
    if (stack->size == 0) {
        printf("Stack is empty. Cannot pop.\n");
        *value = NULL;
        return;
    }

    struct StackNode* topNode = stack->top;
    *value = topNode->data;
    stack->top = topNode->next;
    free(topNode);
    stack->size--;
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
    if (queue->size >= QUEUE_SIZE) {
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }

    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = _strdup(value);
    newNode->next = NULL;

    if (queue->size == 0) {
        queue->front = newNode;
    }
    else {
        queue->rear->next = newNode;
    }

    queue->rear = newNode;
    queue->size++;
}

void QPOP(struct Queue* queue, char** value) {
    if (queue->size == 0) {
        printf("Queue is empty. Cannot dequeue.\n");
        *value = NULL;
        return;
    }

    struct QueueNode* frontNode = queue->front;
    *value = frontNode->data;
    queue->front = frontNode->next;

    if (queue->front == NULL) {
        queue->rear = NULL; // Установка задней части в NULL, если очередь пуста.
    }

    free(frontNode);
    queue->size--;
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
    EnterCriticalSection(&myMutex);

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
    LeaveCriticalSection(&myMutex);
}

void readDataFromFile(const char* filename, struct HashTable* ht, struct HashSet* mySet, struct Stack* myStack, struct Queue* myQueue) {
    EnterCriticalSection(&myMutex); // открытие критической области

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
    LeaveCriticalSection(&myMutex); // закрытие критической области 
}

char* processQuery(struct HashTable* ht, struct Set* mySet, struct Stack* myStack, struct Queue* myQueue, const char* query) {
    EnterCriticalSection(&myMutex);

    char* result = NULL;
    char* command = NULL;
    char* token = NULL;
    char* context = NULL;

    command = strtok_s(query, " ", &context);

    if (command == NULL) {
        result = _strdup("Invalid query format.");
    }
    else if (strcmp(command, "SADD") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            int saddResult = SADD(mySet, token);
            if (saddResult == 1) {
                result = _strdup("The operation is completed!");
            }
            else if (saddResult == 0) {
                result = _strdup("Value already exists in the set.");
            }
        }
        else {
            result = _strdup("Invalid SADD format.");
        }
    }
    else if (strcmp(command, "SREM") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            SREM(mySet, token);
            result = _strdup("The operation is completed!");
        }
        else {
            result = _strdup("Invalid SREM format.");
        }
    }
    else if (strcmp(command, "SISMEMBER") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            int res = SISMEMBER(mySet, token);
            if (res) {
                result = _strdup("The element is a member.");
            }
            else {
                result = _strdup("The element is not a member.");
            }
        }
        else {
            result = _strdup("Invalid SISMEMBER format.");
        }
    }
    else if (strcmp(command, "SPUSH") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            SPUSH(myStack, token);
            result = _strdup("The operation is completed!");
        }
        else {
            result = _strdup("Invalid SPUSH format.");
        }
    }
    else if (strcmp(command, "SPOP") == 0) {
        char* value = NULL;
        SPOP(myStack, &value);
        if (value != NULL) {
            result = value;
        }
    }
    else if (strcmp(command, "QPUSH") == 0) {
        token = strtok_s(NULL, " ", &context);
        if (token != NULL) {
            QPUSH(myQueue, token);
            result = _strdup("The operation is completed!");
        }
        else {
            result = _strdup("Invalid QPUSH format.");
        }
    }
    else if (strcmp(command, "QPOP") == 0) {
        char* value = NULL;
        QPOP(myQueue, &value);
        if (value != NULL) {
            result = value;
        }
    }
    else if (strcmp(command, "HSET") == 0) {
        char* key = strtok_s(NULL, " ", &context);
        char* value = strtok_s(NULL, " ", &context);
        if (key != NULL && value != NULL) {
            int hsetResult = HSET(ht, key, value);
            if (hsetResult == 1) {
                result = _strdup("The operation is completed!");
            }
            else if (hsetResult == 0) {
                result = _strdup("Key already exists in the hash table.");
            }
        }
        else {
            result = _strdup("Invalid HSET format.");
        }
    }
    else if (strcmp(command, "HGET") == 0) {
        char* key = strtok_s(NULL, " ", &context);
        if (key != NULL) {
            char* value = HGET(ht, key);
            if (value != NULL) {
                result = value;
            }
            else {
                result = _strdup("Key not found in the hash table.");
            }
        }
        else {
            result = _strdup("Invalid HGET format.");
        }
    }
    else if (strcmp(command, "HDEL") == 0) {
        char* key = strtok_s(NULL, " ", &context);
        if (key != NULL) {
            HDEL(ht, key);
            result = _strdup("The operation is completed!");
        }
        else {
            result = _strdup("Invalid HDEL format.");
        }
    }
    else {
        result = _strdup("Unknown command.");
    }

    LeaveCriticalSection(&myMutex);

    return result;
}


DWORD WINAPI Client(LPVOID Param) { // функция обрабатывается в новом потоке

    SOCKET ClientConn = *((SOCKET*)Param); // извлечение сокета из параметра 
    free(Param); // освобождение параметра 

    struct HashTable* myHt = createHashTable();
    struct Set* mySet = createHashSet();
    struct Stack* myStack = createStack();
    struct Queue* myQueue = createQueue();

    char* responseBuffer = (char*)malloc(100); // Выделяем память для строки запроса 

    int erStat = recv(ClientConn, responseBuffer, 100, 0); // принимаем строку запроса 

    if (erStat > 0) {
        responseBuffer[erStat] = '\0';
        printf("\nClient answer: %s \n", responseBuffer); // выводим запрос 
    }
    else if (erStat == 0) {
        printf("Connection closed\n");
    }
    else {
        printf("Error #%d\n", WSAGetLastError());
    }

    const char* filename = "output.txt";
    const char* query = responseBuffer;

    readDataFromFile(filename, myHt, mySet, myStack, myQueue);

    // Вызов функции для выполнения запроса
    const char* result = processQuery(myHt, mySet, myStack, myQueue, query);
    printf("Process result: %s", result);

    // Запись данных обратно в файл
    writeDataToFile(filename, myHt, mySet, myStack, myQueue);

    send(ClientConn, result, strlen(result), 0); // отправляем ответ на запрос клиенту 

    // Освобождение памяти, выделенной для контейнеров
    free(myHt);
    free(mySet);
    free(myStack);
    free(myQueue);

    closesocket(ClientConn); // закрытие сокета клиента

    return 0;
}

int main() {
    WSADATA wsData;
    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData); // получение версии сокетов

    if (erStat != 0) { // обработка ошибок
        printf("Error WinSock version initialization\n");
        WSAGetLastError();
        return 1;
    }
    else
        printf("WinSock initialization is OK\n");

    SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0); // создание серверного сокета 

    if (ServSock == INVALID_SOCKET) { // обработка ошибок
        printf("Error initialization socket\n");
        WSAGetLastError();
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        printf("Server socket initialization is OK\n");

    struct in_addr ip_to_num; // Создаем структуру адреса
    erStat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num); // перевод ip адреса в числовой формат
    if (erStat <= 0) { // обработка ошибки 
        printf("Error in IP translation to special numeric format");
        return 1;
    }

    struct sockaddr_in servInfo; // информация о сервере 
    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(6379);

    erStat = bind(ServSock, (struct sockaddr*)&servInfo, sizeof(servInfo)); // Биндим сокет по указанной структуре
    if (erStat != 0) { // обработка ошибки
        printf("Error Socket binding to server info. Error #%d\n", WSAGetLastError());
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        printf("Binding socket to Server info is OK\n");

    erStat = listen(ServSock, SOMAXCONN); // прослушка запроса 

    if (erStat != 0) {
        printf("Can't start to listen to. Error #\n");
        WSAGetLastError();
        closesocket(ServSock);
        WSACleanup();
        return NULL;
    }
    else {
        printf("Listening...");
    }

    struct sockaddr_in clientInfo;
    ZeroMemory(&clientInfo, sizeof(clientInfo)); // информация о клиенте

    int clientInfo_size = sizeof(clientInfo);

    InitializeCriticalSection(&myMutex); // для одного потока

    while (1) { // бесконечный цикл для постоянной работы сервера
        SOCKET ClientConn = accept(ServSock, (struct sockaddr*)&clientInfo, &clientInfo_size); // принятие соединения

        if (ClientConn == INVALID_SOCKET) { // обработка ошибок
            printf("Error accepting connection. Error #%d\n", WSAGetLastError());
            closesocket(ServSock);
            WSACleanup();
            return 1;
        }
        else {
            printf("\n\nConnection to a client established successfully\n");
            char clientIP[22];

            inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN); // получение ip клиента

            printf("Client connected with IP address %s\n", clientIP); // вывод ip клиента 
        }

        SOCKET* ClientSocket = (SOCKET*)malloc(sizeof(SOCKET)); // выделяем память под сокет для передачи в поток
        *ClientSocket = ClientConn;

        HANDLE Thread = CreateThread(NULL, 0, Client, ClientSocket, 0, NULL); // создаем поток для обработки запроса

        CloseHandle(Thread); // освобождение ресурсов потока
    }

    closesocket(ServSock); // закрытие сокета сервера 
    WSACleanup();

    DeleteCriticalSection(&myMutex);

    return 0;
}