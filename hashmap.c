#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t createHash(const char *key, size_t size) {
  size_t hash = 0;
  int c;
  while ((c = *key++))
    hash = c + (hash << 6) + (hash << 16) - hash;
  return hash % size;
}

typedef struct Item {
  char *key;
  double value;
  struct Item *next;
} Item;

Item *createItem(const char *key, double value) {
  Item *item = (Item *)malloc(sizeof(Item));
  item->key = (char *)malloc(strlen(key) + 1);
  strcpy(item->key, key);
  item->value = value;
  item->next = NULL;
  return item;
}

typedef struct {
  size_t size;
  size_t count;
  Item **items;
} HashMap;

HashMap *createHashMap(size_t size) {
  HashMap *hashmap = (HashMap *)malloc(sizeof(HashMap));
  hashmap->size = size;
  hashmap->items = (Item **)malloc(sizeof(Item *) * size);

  for (int i = 0; i < size; i++)
    hashmap->items[i] = NULL;

  return hashmap;
}

Item *getHead(HashMap *hashmap, const char *key) {
  size_t index = createHash(key, hashmap->size);
  return hashmap->items[index];
}

double get(HashMap *hashmap, const char *key) {
  Item *head = getHead(hashmap, key);
  while (head != NULL) {
    if (strcmp(head->key, key) == 0)
      return head->value;
    head = head->next;
  }
  fprintf(stderr, "HashMap: get: Key not found: %s\n", key);
  exit(-1);
}

Item *set(Item *item, double value) {
  item->value = value;
  return item;
}

Item *put(HashMap *hashmap, const char *key, double value) {
  size_t index = createHash(key, hashmap->size);
  Item *head = hashmap->items[index];

  if (head == NULL) {
    hashmap->count++;
    return hashmap->items[index] = createItem(key, value);
  }

  for (;;) {
    if (head == NULL)
      break;
    if (strcmp(head->key, key) == 0)
      return set(head, value);
    if (head->next == NULL)
      break;
  }

  hashmap->count++;
  return head->next = createItem(key, value);
}

void print(HashMap *hashmap) {
  for (int i = 0; i < hashmap->size; i++) {
    Item *head = hashmap->items[i];
    if (head == NULL)
      continue;
    printf("%d: ", i);
    while (head != NULL) {
      printf("%s: %f, ", head->key, head->value);
      head = head->next;
    }
    printf("\n");
  }
}

Item **getItems(HashMap *hashmap) {
  Item **items = (Item **)malloc(sizeof(Item *) * hashmap->count);

  int j = 0;
  for (int i = 0; i < hashmap->size; i++) {
    Item *head = hashmap->items[i];
    while (head != NULL) {
      items[j++] = head;
      head = head->next;
    }
  }

  return items;
}

void freeItem(Item *item) {
  if (item == NULL)
    return;
  free(item->key);
  freeItem(item->next);
  free(item);
}

void freeHashMap(HashMap *hashmap) {
  for (int i = 0; i < hashmap->size; i++)
    freeItem(hashmap->items[i]);
  free(hashmap->items);
  free(hashmap);
}

int main() {
  HashMap *hashmap = createHashMap(20);

  put(hashmap, "a", 10.0);
  put(hashmap, "b", 20.0);
  put(hashmap, "bcd", 30.0);
  put(hashmap, "dcb", 40.0);

  print(hashmap);

  freeHashMap(hashmap);

  return 0;
}
