#include <stdio.h>

typedef struct s_Node {
	struct s_Node *next;
	void* value;
}Node;

typedef struct s_List {
	int size;
	Node * head;
	Node * tail;
}List;

List*createList() {
	List*list = malloc(sizeof(List));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void Push(List *list, void *value) {
	Node*node = malloc(sizeof(Node));
	node->value = value;
	node->next = list->head;
	list->head = node;
	list->size++;
}

void* Pop(List*list){
	if (list->size == NULL) return NULL;
	Node*node = list->head;
	int ret_val = node->value;
	list->size--;
	list->head = node->next;
	free(node);
	if (list->size == 0) {
		list->head = NULL;
		list->tail = NULL;
	}

	return ret_val;
}


void Free(List*list) {
	for (int i = 0; list->size; i++)
		Pop(list);
	free(list);
}


int main() {
	List* list = createList();
	Push(list, 5);
	printf("%d", (int)Pop(list));
	Free(list);
	system("pause");
	return 0;
}