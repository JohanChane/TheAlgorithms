#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "skiplist.h"
#include "test_utils/utils.h"

const int array_size = 1 * 10000;

static void print_skiplist(SkipList* skiplist) {
  for (int i = skiplist->level; i >= 0; i--) {
    SkipNode* cur_node = skiplist->header->forward[i];

    printf("level %d: ", i);
    while (cur_node) {
      printf("%d\t", cur_node->key);
      cur_node = cur_node->forward[i];
    }
    printf("\n");
  }
}

// 不完全检测是否是 skiplist
bool check_skiplist(SkipList* skiplist) {
  SkipNode* cur_node = skiplist->header;
  for (int i = skiplist->level; i >= 0; i--) {
    if (!cur_node || !cur_node->forward[i]) {
      cur_node = skiplist->header;
      continue;
    }

    if (cur_node->key > cur_node->forward[i]->key) {
      return false;
    }

    cur_node = cur_node->forward[i];
  }

  return true;
}

static void test_skiplist() {
  int array[array_size];
  genRandomNumsNotSame(array, array_size, 100, array_size + 999);
  //printArray(array, array_size);

  clock_t start, end;
  start = getTime();

  SkipList* skiplist = create_skiplist(10, 0.5);

  for (int i = 0; i < array_size; i++) {
    insert_element(array[i], skiplist);
    if (!check_skiplist(skiplist)) {
      fprintf(stderr, "check_skiplist failed.");
      exit(EXIT_FAILURE);
    }
  }
  print_skiplist(skiplist);

  SkipNode* n = find_element(array[500], skiplist);
  if (n) {
    printf("find_element: %d\n", n->key);
  }

  for (int i = array_size - 1; i >= 10; i--) {
    delete_element(array[i], skiplist);
    if (!check_skiplist(skiplist)) {
      fprintf(stderr, "check_skiplist failed.");
      exit(EXIT_FAILURE);
    }
  }
  print_skiplist(skiplist);

  destroy_skiplist(skiplist);

  end = getTime();
  printf("duration = %lfs\n", calcDuration(start, end));
}

int main() {
  test_skiplist();
  return 0;
}
