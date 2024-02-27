#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Структура элемента хэш-таблицы для подсчета частоты
struct HashTableEntry {
    int key;
    int frequency;
    struct HashTableEntry* next;
};

// Структура хэш-таблицы
struct HashTable {
    struct HashTableEntry* table[TABLE_SIZE];
};

// Функция для вычисления хэш-кода
unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

// Функция для создания новой хэш-таблицы
struct HashTable* createHashTable() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Функция для увеличения частоты элемента или добавления его в хэш-таблицу
void incrementFrequency(struct HashTable* ht, int key) {
    unsigned int index = hash(key);
    struct HashTableEntry* entry = ht->table[index];
    while (entry != NULL) {
        if (entry->key == key) {
            // Элемент уже присутствует в хэш-таблице увеличиваем его частоту
            entry->frequency++;
            return;
        }
        entry = entry->next;
    }

    // Элемент не найден создаем новую запись
    struct HashTableEntry* newEntry = (struct HashTableEntry*)malloc(sizeof(struct HashTableEntry));
    newEntry->key = key;
    newEntry->frequency = 1;
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry;
}

// Функция для вывода частоты элементов
void printFrequency(struct HashTable* ht) {
    printf("Element Frequency\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct HashTableEntry* entry = ht->table[i];
        while (entry != NULL) {
            printf("%6d %9d\n", entry->key, entry->frequency);
            entry = entry->next;
        }
    }
}

int main() {
    int data[] = { 1, 3, 5, 3, 7, 9, 5, 3, 1, 5, 7 }; // Пример данных

    struct HashTable* frequencyTable = createHashTable();

    // Подсчет частоты встречаемости элементов
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        incrementFrequency(frequencyTable, data[i]);
    }

    // Вывод частоты встречаемости элементов
    printFrequency(frequencyTable);

    return 0;
}