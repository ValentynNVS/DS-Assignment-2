#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int kMaxCharSize = 100;
typedef struct StackNode {
	char* url;
	struct StackNode* next;
} StackNode;

typedef struct Stack {
	struct StackNode* top;
}Stack;

typedef struct QueueNode {
	char* url;
	struct QueueNode* next;
} QueueNode;

typedef struct Queue {
	struct QueueNode* front;
	struct QueueNode* rear;
}Queue;

/*stack funcs*/
void push(Stack* stack, char* newUrl);
char* pop(Stack* stack);
char* peek(Stack* stack);
bool isEmptyStack(Stack* stack);
/*queue fucns*/
void enqueue(Queue* queue, char* newUrl);
char* dequeue(Queue* queue);
char* peek(Queue* queue);
bool isEmptyQueue(Queue* queue);
/*crate stuck/queue*/
StackNode* createStackNode(char* url);
QueueNode* createQueue(char* url);

/* create stack and implement push
pop, peek, isEmpty fucns for it*/
/* create queue and impplement enqueue,
dequeue, peek, isEpmty*/
#pragma warning(disable:4996)


int main(void) {

	int userChoice = 0;
	char urlLink[kMaxCharSize] = "";

	while (1) {
		printf("Menu:\n1. Visit New Web Page\n2. Navigate Backward\n\
3. Navigate Forward\n4. Display Current Page and History\n5. Exit");
		printf("Enter your choice: ");

		if (scanf("%d", &userChoice) == 1) {
			int returnValue = getchar();
		}
		else {
			printf("Wrong Input\n");
			continue;
		}

		if (userChoice == 1) {
			printf("Enter the URL of the web page: ");
			fgets(urlLink, kMaxCharSize, stdin);
			size_t len = strcspn(urlLink, "\n");
			urlLink[len] = '\0';

			printf("Visited: ");
			continue;
		}
		else if (userChoice == 2) {
			printf("Previous page: ");
			continue;
		}
		else if (userChoice == 3) {

		}
		else if (userChoice == 4) {

		}
		else if (userChoice == 5) {
			printf("Thank you for using the web browser. Goodbye!");
			/*free up all allocated memory*/
			break;
		}

	}

	return 0;

}

StackNode* createStackNode(char* url) {

	StackNode* newStack = (StackNode*)malloc(sizeof(StackNode));
	newStack->url = strdup(url);
	newStack->next = NULL;
	if (newStack->url == NULL) {
		printf("Coudl not allocate the memory");
		free(newStack->url);
		return NULL;
	}

	return newStack;
}
QueueNode* createQueue(char* url) {

	QueueNode* newQueue = (QueueNode*)malloc(sizeof(QueueNode));
	newQueue->next = NULL;
	newQueue->url = strdup(url);
	if (newQueue->url == NULL) {
		printf("couldnt allocate the memory");
		free(newQueue);
		return NULL;
	}

	return newQueue;
}
void push(Stack* stack, char* newUrl) {

	StackNode* newStack = createStackNode(newUrl);
	newStack->next = stack->top;
	stack->top = newStack;


}

char* pop(Stack* stack) {

	if (isEmptyStack(stack)) {
		printf("Stack underflow");
		return;
	}

	StackNode* temp = stack->top;
	stack->top = stack->top->next;
	char* url = temp->url;
	free(temp->url);
	free(temp->next);
	free(temp);
	return url;

}

char* peek(Stack* stack) {
	if (stack->top == NULL) {
		return NULL;
	}
	else {
		return stack->top->url;
	}

}

bool isEmptyStack(Stack* stack) {
	return stack->top == NULL;
}

void enqueue(Queue* queue, char* newUrl) {

	QueueNode* newNode = createQueue(newUrl);
	if (queue->rear == NULL) {
		queue->front = queue->rear = newNode;
		return;
	}
	queue->rear->next = newNode;
	queue->rear = newNode;

}
char* dequeue(Queue* queue) {

	if (queue->front == NULL) {
		return NULL;
	}
	QueueNode* temp = queue->front;
	queue->front = queue->front->next;
	if (queue->front == NULL) {
		queue->rear = NULL;
	}
	char* url = temp->url;
	free(temp->next);
	free(temp->url);
	free(temp);
	return url;

}
char* peek(Queue* queue) {
	if (queue->front == NULL) {
		return NULL;
	}
	return queue->front->url;
}
bool isEmptyQueue(Queue* queue) {
	return queue->front == NULL;
}