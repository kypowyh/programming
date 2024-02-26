#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

struct HashTableEntry {
    int key;
    unsigned long long value; // результат факториала
    struct HashTableEntry* next;
};

struct HashTable {
    struct HashTableEntry* table[TABLE_SIZE];
};

unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

struct HashTable* createHashTable() {
    struct HashTable* ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Функция для вычисления факториала
unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

// Функция для получения значения из кэша или вычисления и кэширования
unsigned long long getFactorial(struct HashTable* ht, int n) {

    unsigned int index = hash(n);
    struct HashTableEntry* entry = ht->table[index];
    while (entry != NULL) {
        if (entry->key == n) {
            // Значение уже закэшировано
            printf("*");
            return entry->value;
        }
        entry = entry->next;
    }

    // Значение не найдено в кэше, вычисляем факториал и кэшируем результат
    unsigned long long result = factorial(n);

    // Создаем новую запись в кэше
    struct HashTableEntry* newEntry = (struct HashTableEntry*)malloc(sizeof(struct HashTableEntry));
    newEntry->key = n;
    newEntry->value = result;
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry;

    return result;
}

int main() {
    struct HashTable* cache = createHashTable();

    // Пример использования кэша для вычисления факториалов
    int numbers[] = { 5, 3, 7, 5, 3, 10 }; // Пример чисел, для которых мы хотим вычислить факториал

    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        int num = numbers[i];
        unsigned long long result = getFactorial(cache, num);
        printf("Factorial %d: %llu\n", num, result);
    }

    return 0;
}