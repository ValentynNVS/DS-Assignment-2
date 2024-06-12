#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int kMaxCharSize = 100;
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