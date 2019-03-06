#include <stdio.h>

typedef struct VM{
	enum OPPCODES{
		OP_BR = 0, /* branch */
		OP_ADD,    /* add  */
		OP_LD,     /* load */
		OP_ST,     /* store */
		OP_JSR,    /* jump register */
		OP_AND,    /* bitwise and */
		OP_LDR,    /* load register */
		OP_STR,    /* store register */
		OP_RTI,    /* unused */
		OP_NOT,    /* bitwise not */
		OP_LDI,    /* load indirect */
		OP_STI,    /* store indirect */
		OP_JMP,    /* jump */
		OP_RES,    /* reserved (unused) */
		OP_LEA,    /* load effective address */
		OP_TRAP    /* execute trap */
	};

	enum REGISTERS {

	};
	
}VM;


typedef struct s_Node {
	struct s_Node *next;
	void* value;
}Node;

typedef struct s_List {
	int size;
	Node * head;
	Node * tail;
}List;

typedef struct Stack {
	List* list;
}Stack;

List*createList() {
	List*list = malloc(sizeof(List));
	list->size = 0;
	list->head = NULL;
	list->tail = list->head;
	return list;
}

#pragma region NIKOLAYS

void AnotherPush(List *list, void *value) {
	Node*node = malloc(sizeof(Node));
	node->value = value;
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	}
	else {
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

void* AnotherPop(List*list){
	if (list->size == NULL) return NULL;
	Node *node = list->tail;
	void*ret_val = node->value;
	if (list->tail == list->head) {
		free(list->tail);
		list->head = NULL;
		list->tail = NULL;
		list->size--;
	}
	else
	{
		Node* temp = list->head;
		for (int i = 0; i < list->size-2; i++) {
			temp = temp->next;
		}
		temp->next = NULL;
		free(list->tail);
		list->tail = temp;
		list->size--;
	}
	return ret_val;
}

#pragma endregion

void listPush(List*list, void *value) {
	Node *node = malloc(sizeof(Node));
	if(list->size==NULL){
		node->value = value;
		node->next = list->head;
		list->tail = node;
		list->head = node;
	}
	else {
		node->value = value;
		node->next = list->head;
		list->head = node;
	}
	list->size++;
}

void * listPop(List*list) {
	if (list->size==NULL) return NULL;
	Node*node = list->head;
	void * ret_val = node->value;
	list->size--;
	list->head = node->next;
	free(node);
	if(list->size == NULL) {
		list->head = NULL;
		list->tail = NULL;
	}
	return ret_val;
}

void listPushBack(List*list, void*value) {
	Node*node = malloc(sizeof(Node));
	node->value = value;
	list->tail->next=node;
	list->tail = node;
	list->size++;
}

void * listPeek(List*list) {
	if (list->size == NULL) return NULL;
	return list->head->value;
}

void listFree(List*list) {
	for (int i = 0; list->size; i++)
		listPop(list);
	free(list);
}

Stack* createStack() {
	Stack*stack = malloc(sizeof(Stack));
	stack->list = createList();
	return stack;
}

void stackPush(Stack*stack, void*value) {
	listPush(stack->list, value);
}

void* stackPeek(Stack*stack) {
	if (stack->list->size == NULL) return NULL;
	return stack->list->head->value;
}

void *stackPop(Stack*stack) {
	return listPop(stack->list);
}

int stackCount(Stack*stack) {
	return stack->list->size;
}

int main() {
	Stack*stack = createStack();
	stackPush(stack, 5);
	stackPush(stack, 10);
	stackPush(stack, 50);
	printf("%d ", (int)stackPop(stack));
	printf("%d ", (int)stackPop(stack));
	printf("%d ", (int)stackPop(stack));
	system("pause");
	return 0;
}

