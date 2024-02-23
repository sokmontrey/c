#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  double value;
  struct Node *next;
} Node;

Node *createNode(double value) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->value = value;
  node->next = NULL;

  return node;
}

void freeLinkedList(Node *head) {
  while (head->next != NULL) {
    Node *temp = head;
    head = head->next;
    free(temp);
  }
  free(head);
}

void freeNode(Node* node) {
  free(node);
}

void pushBack(Node *head, Node *new_node) {
  Node *node = head;
  while (node->next != NULL)
    node = node->next;
  node->next = new_node;
}

void addEnd(Node *head, double value) { pushBack(head, createNode(value)); }

int main() { return 0; }
