#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *inverse_message(char message[], int size)
{
	int len = strlen(message);
	int i = 0;
	int tmp = len - 1;
	char message2[size];
	while (i < tmp)
	{
		char temp1 = message[i];
		char temp2 = message[tmp];
		message2[i] = temp2;
		message2[tmp] = temp1;
		i++;
		tmp--;
	}
	if (len % 2 == 1)
	{
		message2[i] = message[i];
	}
	message2[len] = '\0';
	return message2;
}

int main()
{
	int p[2];
	int p1[2];
	pipe(p);
	pipe(p1);
	if (fork() == 0)
	{
		char message2[25];
		close(p[1]);
		read(p[0], message2, 25);
		close(p[0]);
		printf("message from father : %s\n", message2);
		char inversed_message[25];
		strcpy(inversed_message, inverse_message(message2, 25));
		close(p1[0]);
		write(p1[1], inversed_message, 25);
		close(p1[1]);
	}
	else
	{
		char message[25];
		char message1[25];
		printf("Type a message : ");
		scanf("%s", message);
		close(p[0]);
		write(p[1], message, 25);
		close(p[1]);
		close(p1[1]);
		read(p1[0], message1, 25);
		close(p1[0]);
		printf("message from the son : %s\n", message1);
	}
	return 0;
}
