#include "GeneralView.h"

bool getBooleanValueUI(const char* message)
{
	int input;

	do
	{
		printf("%s (0 for No, 1 for Yes): ", message);
		scanf("%d", &input);
		if (input != 0 && input != 1)
		{
			printf("Invalid input. Please enter 0 for No or 1 for Yes.\n");
		}
	} while (input != 0 && input != 1);

	return input != 0;
}

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {} // Clear up to the end of line or EOF
}
