#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "skiplist.h"

const int min_key = INT_MIN;

static SkipNode* create_skipnode(int key, int level) {
  SkipNode* node = malloc(sizeof(SkipNode));
  node->key = key;
  size_t s = sizeof(SkipNode*) * (level + 1);
  node->forward = (SkipNode**)malloc(s);
  memset(node->forward, 0, s);
  return node;
}

static void destroy_skipnode(SkipNode* node) {
  free(node->forward);
  free(node);
}

static int random_level(SkipList* list) {
  float r = (float)rand() / RAND_MAX;
  int level = 0;
  while (r < list->p && level < list->max_level) {
    level++;
    r = (float)rand() / RAND_MAX;
  }

  return level;
}

SkipList* create_skiplist(int max_level, float p) {
  srand(time(NULL));

  SkipList* skiplist = malloc(sizeof(SkipList));
  skiplist->max_level = max_level;
  skiplist->p = p;
  skiplist->level = 0;
  skiplist->header = create_skipnode(min_key, max_level);

  return skiplist;
}

void insert_element(int key, SkipList* skiplist) {
  int rand_lvl = random_level(skiplist);    // 生成不高于 max_level 的随机 level

  // ## 记录将要插入的节点的每一层的左边的节点。
  SkipNode* update[max(skiplist->level, rand_lvl) + 1];
  SkipNode* cur_node = skiplist->header;
  for (int i = skiplist->level; i >= 0; i--) {
    while (cur_node->forward[i] && key > cur_node->forward[i]->key) {
      cur_node = cur_node->forward[i];
    }
    update[i] = cur_node;
  }

  // same key
  if (cur_node->forward[0] && cur_node->forward[0]->key == key) {
    return;
  }

  // 高于当前跳表的层的左边的节点则是 header.
  for (int i = rand_lvl; i > skiplist->level; i--) {
    update[i] = skiplist->header;
  }

  // ## 插入新节点
  SkipNode* new_node = create_skipnode(key, rand_lvl);
  for (int i = rand_lvl; i >= 0; i--) {
    new_node->forward[i] = update[i]->forward[i];       // 新插入节点链接右边的节点。
    update[i]->forward[i] = new_node;                   // 新插入节点的左边的节点链接新插入节点。
  }

  if (rand_lvl > skiplist->level) {
    skiplist->level = rand_lvl;
  }
}

void delete_element(int key, SkipList* skiplist) {
  SkipNode* update[skiplist->level + 1];
  SkipNode* cur_node = skiplist->header;
  for (int i = skiplist->level; i >= 0; i--) {
    while (cur_node->forward[i] && key > cur_node->forward[i]->key) {
      cur_node = cur_node->forward[i];
    }
    update[i] = cur_node;
  }

  cur_node = cur_node->forward[0];

  // ## not found
  if (!cur_node || cur_node->key != key) {
    return;
  }

  // ## found
  for (int i = 0; i <= skiplist->level; i++) {
    if (update[i]->forward[i] != cur_node) {
      break;
    }
    update[i]->forward[i] = cur_node->forward[i];
  }
  destroy_skipnode(cur_node);

  while (skiplist->level > 0 && !skiplist->header->forward[skiplist->level]) {
    skiplist->level--;
  }
}

SkipNode* find_element(int key, SkipList* skiplist) {
  SkipNode* cur_node = skiplist->header->forward[skiplist->level];
  if (!cur_node) {
    return NULL;
  }

  for (int i = skiplist->level; i >= 0; i--) {
    while (cur_node->forward[i] && key > cur_node->forward[i]->key) {
      cur_node = cur_node->forward[i];
    }

    if (cur_node->forward[0] && cur_node->forward[0]->key == key) {
      return cur_node->forward[0];
    }
  }

  return NULL;
}

void destroy_skiplist(SkipList* skiplist) {
  SkipNode* cur_node = skiplist->header;
  while (cur_node) {
    SkipNode* temp_node = cur_node;
    cur_node = cur_node->forward[0];
    destroy_skipnode(temp_node);
  }
  free(skiplist);
}
