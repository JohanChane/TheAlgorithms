#pragma once

typedef struct SkipNode {
  int key;
  struct SkipNode** forward;
} SkipNode;

typedef struct SkipList {
  int max_level;        // level <= max_level
  int level;            // current level: [0, -]
  SkipNode* header;
  float p;              // 增加一层的概率。上层比下层的节点应该更少, 如果是 0.5 则上层和下层的节点数量比例为 1:2。
} SkipList;

SkipList* create_skiplist(int max_level, float p);
void insert_element(int key, SkipList* skiplist);
SkipNode* find_element(int key, SkipList* skiplist);
void delete_element(int key, SkipList* skiplist);
void destroy_skiplist(SkipList* skiplist);

static inline int max(int a, int b) {
  return a > b ? a : b;
}

