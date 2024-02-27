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