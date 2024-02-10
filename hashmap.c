#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

unsigned long hash(const char *str) {
  unsigned long i = 0;
  for (int j = 0; str[j]; j++)
    i += str[j];
  return i % SIZE;
}

typedef struct Item {
  char *key;
  int value;
} Item;

typedef struct HashTable {
  Item **items;
  int size;
  int count;
} HashTable;

Item *createItem(const char *key, int value) {
  Item *item = (Item *)malloc(sizeof(Item));

  item->key = (char *)malloc(strlen(key) + 1);
  strcpy(item->key, key);

  item->value = value;
  return item;
}

HashTable *createHashTable(int size) {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  table->size = size;
  table->count = 0;
  table->items = (Item **)calloc(size, sizeof(Item *));

  for (int i = 0; i < table->size; i++)
    table->items[i] = NULL;

  return table;
}

void printHashTable(HashTable *table) {
  for (int i = 0; i < table->size; i++) {
    Item *item = table->items[i];
    if (item != NULL)
      printf("Index = %d, Key = %s, Value = %d\n", i, item->key, item->value);
  }
}

void freeItem(Item *item) {
  free(item->key);
  free(item);
}

void freeHashTable(HashTable *table) {
  for (int i = 0; i < table->size; i++) {
    Item *item = table->items[i];
    if (item != NULL)
      freeItem(item);
  }

  free(table->items);
  free(table);
}

void insert(HashTable *table, const char *key, int value) {
  int index = hash(key);
  Item* new_item = createItem(key, value);
  Item* item = table->items[index];

  if (item == NULL) {
    table->items[index] = new_item;
    table->count++;
    return;
  }
}

int main() { 

  // Create a new hash table
  // Insert some values
  // Print the hash table
  // Free the hash table
  
  HashTable *table = createHashTable(SIZE);

  insert(table, "a", 1);
  insert(table, "b", 2);
  insert(table, "c", 3);

  printHashTable(table);

  freeHashTable(table);

  return 0; 
}
