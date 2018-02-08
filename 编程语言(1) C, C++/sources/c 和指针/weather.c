#include <stdio.h>
#include <string.h>

int main ()
{
	char precipitating[16];
	int temperature;
	while (1)
	{
		printf("precipitating? ");
		scanf("%s", precipitating);
		printf("temperature? ");
		scanf("%d", &temperature);

		if (strcmp(precipitating, "yes") == 0)
		{	
			if (temperature >= 32)
				printf("raining\n");
			else
				printf("snowing\n");
		}
		else if (strcmp(precipitating, "no") == 0)
		{	
			if (temperature >= 60)
				printf("warm\n");
			else
				printf("cold\n");
		}
		else
			printf("wrong\n");
	}
}
