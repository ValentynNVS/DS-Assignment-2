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
Stack* InitializeStack(void);
Queue* InitializeQueue(void);

/* create stack and implement push
pop, peek, isEmpty fucns for it*/
/* create queue and impplement enqueue,
dequeue, peek, isEpmty*/
#pragma warning(disable:4996)


int main(void) {

	Stack* backStack = InitializeStack();
	Queue* forwardQueue = InitializeQueue();
	int userChoice = 0;
	char urlLink[kMaxCharSize] = "";

	while (1) {
		printf("Menu:\n1. Visit New Web Page\n2. Navigate Backward\n\
3. Navigate Forward\n4. Display Current Page and History\n5. Exit\n");
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

			push(backStack, urlLink);
			while (!isEmptyQueue(forwardQueue)) {
				free(dequeue(forwardQueue));
			}
			printf("Visited: %s\n", urlLink);
			continue;
		}
		else if (userChoice == 2) {
			if (isEmptyStack(backStack) || backStack->top->next == NULL) {
				printf("No previous page.\n");
			}
			else {
				char* currentUrl = pop(backStack);
				enqueue(forwardQueue, currentUrl);
				printf("Previous page: %s\n", peek(backStack));
			}
		}
		else if (userChoice == 3) {
			if (isEmptyQueue(forwardQueue)) {
				printf("No next page.\n");
			}
			else {
				char* nextUrl = dequeue(forwardQueue);
				push(backStack, nextUrl);
				printf("Next page: %s\n", nextUrl);
			}
		}
		else if (userChoice == 4) {
			printf("Current Page: %s\n", backStack->top ? backStack->top->url : "None");
			printf("Backward History:\n");
			StackNode* tempStack = backStack->top;
			tempStack = tempStack->next;
			int count = 1;
			while (tempStack) {
				printf("%d. %s\n", count++, tempStack->url);
				tempStack = tempStack->next;
			}
			printf("Forward History:\n");
			QueueNode* tempQueue = forwardQueue->front;
			count = 1;

			// Use an array to temporarily store the URLs from the forward queue
			int queueSize = 0;
			tempQueue = forwardQueue->front;
			while (tempQueue) {
				queueSize++;
				tempQueue = tempQueue->next;
			}

			// Allocate an array to hold the URLs
			char** urlArray = (char**)malloc(queueSize * sizeof(char*));

			// Fill the array with URLs
			tempQueue = forwardQueue->front;
			for (int i = 0; i < queueSize; i++) {
				urlArray[i] = tempQueue->url;
				tempQueue = tempQueue->next;
			}

			// Print the URLs in reverse order
			for (int i = queueSize - 1; i >= 0; i--) {
				printf("%d. %s\n", count++, urlArray[i]);
			}

			// Free the allocated memory
			free(urlArray);
		}
		else if (userChoice == 5) {
			printf("Thank you for using the web browser. Goodbye!\n");
			// Free allocated memory
			while (!isEmptyStack(backStack)) {
				free(pop(backStack));
			}
			while (!isEmptyQueue(forwardQueue)) {
				free(dequeue(forwardQueue));
			}
			break;
		}
		else {
			printf("Invalid entry, try again.");
			break;
		}
	}

	return 0;

}


Stack* InitializeStack(void) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;
	return stack;
}

Queue* InitializeQueue(void) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) {
		printf("No Memory");
		exit(EXIT_FAILURE);
	}
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}
/*
Function: createStackNode
Parameters: char* url - pointer to the URL string for the new stack node
Description: This function creates a new stack node with the given URL.
Return value: StackNode* - pointer to the newly created stack node
*/
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

/*
Function: createQueue
Parameters: char* url - pointer to the URL string for the new queue node
Description: This function creates a new queue node with the given URL.
Return value: QueueNode* - pointer to the newly created queue node
*/
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

/*
Function: push
Parameters: Stack* stack - pointer to the stack
			char* newUrl - pointer to the new URL string to be added
Description: This function adds a new URL to the top of the stack.
Return value: void
*/
void push(Stack* stack, char* newUrl) {

	StackNode* newStack = createStackNode(newUrl);
	newStack->next = stack->top;
	stack->top = newStack;


}

/*
Function: pop
Parameters: Stack* stack - pointer to the stack
Description: This function removes and returns the URL from the top of the stack.
Return value: char* - the URL from the top of the stack
*/
char* pop(Stack* stack) {

	if (isEmptyStack(stack)) {
		printf("Stack underflow");
		return NULL;
	}

	StackNode* temp = stack->top;
	stack->top = stack->top->next;
	char* url = temp->url;
	free(temp);
	return url;

}

/*
Function: peek
Parameters: Stack* stack - pointer to the stack
Description: This function returns the URL from the top of the stack without removing it.
Return value: char* - the URL from the top of the stack
*/
char* peek(Stack* stack) {
	if (stack->top == NULL) {
		return NULL;
	}
	else {
		return stack->top->url;
	}

}

/*
Function: isEmptyStack
Parameters: Stack* stack - pointer to the stack
Description: This function checks if the stack is empty.
Return value: bool - true if the stack is empty, false otherwise
*/
bool isEmptyStack(Stack* stack) {
	if (stack->top == NULL) {
		return true;
	}
	else {
		return false;
	}
	
}

/*
Function: enqueue
Parameters: Queue* queue - pointer to the queue
			char* newUrl - pointer to the new URL string to be added
Description: This function adds a new URL to the rear of the queue.
Return value: void
*/
void enqueue(Queue* queue, char* newUrl) {

	QueueNode* newNode = createQueue(newUrl);
	if (queue->rear == NULL) {
		queue->front = queue->rear = newNode;
		return;
	}
	queue->rear->next = newNode;
	queue->rear = newNode;

}

/*
Function: dequeue
Parameters: Queue* queue - pointer to the queue
Description: This function removes and returns the URL from the front of the queue.
Return value: char* - the URL from the front of the queue
*/
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

/*
Function: peek
Parameters: Queue* queue - pointer to the queue
Description: This function returns the URL from the front of the queue without removing it.
Return value: char* - the URL from the front of the queue
*/
char* peek(Queue* queue) {
	if (queue->front == NULL) {
		return NULL;
	}
	return queue->front->url;
}

/*
Function: isEmptyQueue
Parameters: Queue* queue - pointer to the queue
Description: This function checks if the queue is empty.
Return value: bool - true if the queue is empty, false otherwise
*/
bool isEmptyQueue(Queue* queue) {
	return queue->front == NULL;
}