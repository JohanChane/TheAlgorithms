#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <stdbool.h>

typedef int Element;

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node {
    Element element;
    Position prev;
    Position next;
};

// 在 position 之后插入
void cirLinkedListInsertAfter(Element element, Position position, List list);
// 在 position 之前插入
void cirLinkedListInsertPrev(Element element, Position position, List list);
void cirLinkedListDelete(Element element, List list);
Position cirLinkedListFind(Element element, List list);
List cirLinkedListCreate();
void cirLinkedListDestroy(List list);
List cirLinkedListEmpty(List list);

inline bool cirLinkedListIsEmpty(List list) {
    return list->next == list;
}

#endif
