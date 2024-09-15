#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct Node {
  int key;
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node **arr;
  int size;
} Map;

Node *node_create(int key, int value, Node *next) {
  Node *node = malloc(sizeof(Node));
  node->key = key;
  node->value = value;
  node->next = next;
  return node;
}

Node *node_find(Node *head, int key) {
  Node *current = head;
  if (!current)
    return NULL;
  while (current->next && current->key != key)
    current = current->next;
  return current->key == key ? current : NULL;
}

Node *node_insert(Node *head, int key, int value) {
  Node *current = head;
  if (!current)
    return NULL;
  while (current->next)
    current = current->next;

  Node *node = node_create(key, value, NULL);
  current->next = node;
  return node;
}

Map map_create(int size) {
  Map map = {.arr = malloc(size * sizeof(Node *)), .size = size};
  for (int i = 0; i < size; i++)
    map.arr[i] = NULL;
  return map;
}

Node *map_get(Map map, int key) {
  if (map.arr[abs(key % map.size)])
    return node_find(map.arr[abs(key % map.size)], key);
  else
    return NULL;
}

void map_insert(Map map, int key, int value) {
  if (!map.arr[abs(key % map.size)])
    map.arr[abs(key % map.size)] = node_create(key, value, NULL);
  else
    node_insert(map.arr[abs(key % map.size)], key, value);
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *result = malloc(2 * sizeof(int));
  *returnSize = 2;

  Map map = map_create(numsSize);
  for (int i = 0; i < numsSize; i++) {
    map_insert(map, nums[i], i);
  }

  for (int i = 0; i < numsSize; i++) {
    Node *node = map_get(map, target - nums[i]);
    if (node && node->value != i) {
      result[0] = i;
      result[1] = node->value;
      break;
    }
  }

  return result;
}

int main() {
  // test
  int nums[] = {3, 2, 95, 4, -3};
  int target = 92;
  int returnSize;
  int *result = twoSum(nums, 5, target, &returnSize);

  for (int i = 0; i < returnSize; i++)
    printf("%d ", result[i]);
  printf("\n");
}
