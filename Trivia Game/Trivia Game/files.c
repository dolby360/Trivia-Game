#include "files.h"
//This function prints to the file "users.txt" the list received according the amount received
/*
If the file won't open - it returns 0
If the printing will success- it returns 1
*/
int setUsers(user *list, int size)
{
	int i, j;
	char path[16] = "data/users.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%d\n", size);
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%s\n", list[i].firstName);
		fprintf(fp, "%s\n", list[i].lastName);
		fprintf(fp, "%s\n", list[i].ID);
		fprintf(fp, "%s\n", list[i].password);
		fprintf(fp, "%d\n", list[i].userType);
		fprintf(fp, "%d\n", list[i].gamesPlayed);
		fprintf(fp, "%d\n", list[i].average);
		fprintf(fp, "%d\n", list[i].highScore);
		for (j = 0; j < list[i].gamesPlayed; j++) fprintf(fp, "%d\n", list[i].scoreList[j]);
		fprintf(fp, "$\n");
	}
	fclose(fp);
	for (i = 0; i < size; i++)
	{
		if (list[i].gamesPlayed) free(list[i].scoreList);
	}
	if (size) free(list);
	//return;
	return 1;
}
//This function scans from the file "users.txt" a list of users
/*
If the file won't open - it will return NULL
If the scanning will success- it will return the list
*/
user* getUsers(int *size)
{
	int i, j, *scoreList;
	char path[16] = "data/users.txt", ch='\0';
	FILE *fp = fopen(path, "r");
	if (!fp)
	{
		printf("Unable to open file\n");
		return NULL;
	}
	user *list;
	fscanf(fp, "%d", size);
	if (*size == 0) list = NULL;
	else list = (user*)malloc(sizeof(user)*(*size));
	for (i = 0; i < *size; i++)
	{
		ch = '\0';
		fscanf(fp, "%s", list[i].firstName);
		fscanf(fp, "%s", list[i].lastName);
		fscanf(fp, "%s", list[i].ID);
		fscanf(fp, "%s", list[i].password);
		fscanf(fp, "%d", &list[i].userType);
		fscanf(fp, "%d", &list[i].gamesPlayed);
		fscanf(fp, "%d", &list[i].average);
		fscanf(fp, "%d", &list[i].highScore);
		scoreList = (int*)malloc(sizeof(int)*list[i].gamesPlayed);
		list[i].scoreList = scoreList;
		for (j = 0; j < list[i].gamesPlayed; j++) fscanf(fp, "%d", &list[i].scoreList[j]);
		while (ch != '$') fscanf(fp, "%c", &ch);
	}
	fclose(fp);
	return list;
}
/*
This function reset the file users.txt and their attributes from bestResult.txt,messages.txt
If one of the files wont open- It will return 0
If the reseting will success- it will return 1
*/
int resetUsers()
{
	char path[80] = "data/users.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp,"0");
	fclose(fp);
	strcpy(path, "data/bestResult.txt");
	fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "0");
	fclose(fp);
	strcpy(path, "data/messages.txt");
	fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "0");
	fclose(fp);
	return 1;
}
/*
This function prints to the file "questions.txt" the list received according the amount received
If the file won't open - it returns 0
If the printing will success- it returns 1
*/
int setQuestions(question *list, int size)
{
	int i;
	char path[19] = "data/questions.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%d\n", size);
	for (i = 0; i < size; i++)
	{
		if (list[i].str) fprintf(fp, "%s\n", list[i].str);
		else fprintf(fp, "None\n");
		if (list[i].answer) fprintf(fp, "%s\n", list[i].answer);
		else fprintf(fp, "None\n");
		fprintf(fp, "%d\n", list[i].ID);
		fprintf(fp, "%d\n", list[i].level);
		fprintf(fp, "%d\n", list[i].answered);
		fprintf(fp, "$\n");
	}
	fclose(fp);
	if (size) free(list);
	return 1;
}

//This function scans from the file "questions.txt" a list of users
/*
If the file won't open - it will return NULL
If the scanning will success- it will return the list
*/
question* getQuestions(int *size)
{
	int i;
	question* list;
	list = NULL;
	char path[19] = "data/questions.txt", ch='\0';
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return list;
	
	fscanf(fp, "%d", size);
	if (*size == 0) list = NULL;
	else list = (question*)malloc(sizeof(question)*(*size));
	for (i = 0; i < *size; i++)
	{
		ch = '\0';
		strcpy(list[i].str, fscanfSentence(fp));
		strcpy(list[i].answer, fscanfSentence(fp));
		fscanf(fp, "%d", &list[i].ID);
		fscanf(fp, "%d", &list[i].level);
		fscanf(fp, "%d", &list[i].answered);
		while (ch != '$') fscanf(fp, "%c", &ch);
	}
	fclose(fp);
	return list;
}
/*
This function reset the file question.txt and their attributes from fakeAnswers.txt
If one of the files wont open- It will return 0
If the reseting will success- it will return 1
*/
int resetQuestions()
{
	char path[80] = "data/questions.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "0");
	fclose(fp);
	strcpy(path, "data/fakeAnswers.txt");
	fp = fopen(path, "w");
	fprintf(fp, "0");
	fclose(fp);
	return 1;
}
/*
This function prints to the file "fakeAnswers.txt" the list received according the amount received
If the file won't open - it returns 0
If the printing will success- it returns 1
*/
int setFakeAnswers(fakeAnswer *list, int size)
{
	int i, j;
	char path[21] = "data/fakeAnswers.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%d\n", size);
	for (i = 0; i < size; i++)
	{
		if (list[i].ID) fprintf(fp, "%d\n", list[i].ID);
		fprintf(fp, "%d\n", list[i].fakeAmount);
		for (j = 0; j < list[i].fakeAmount; j++)
		{
			if (list[i].fakeList[j]) fprintf(fp, "%s\n", list[i].fakeList[j]);
			else fprintf(fp, "None\n");
		}
		fprintf(fp, "$\n");
	}
	fclose(fp);
	if (size) free(list);
	return 1;
}

//This function scans from the file "fakeAnswers.txt" a list of users
/*
If the file won't open - it will return NULL
If the scanning will success- it will return the list
*/
fakeAnswer* getFakeAnswers(int *size)
{
	int i, j;
	fakeAnswer* list;
	list = NULL;
	char path[21] = "data/fakeAnswers.txt", ch='\0';
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return list;
	
	fscanf(fp, "%d", size);
	if (*size == 0) list = NULL;
	else list = (fakeAnswer*)malloc(sizeof(fakeAnswer)*(*size));
	for (i = 0; i < *size; i++)
	{
		ch = '\0';
		fscanf(fp, "%d", &list[i].ID);
		fscanf(fp, "%d", &list[i].fakeAmount);
		for (j = 0; j < list[i].fakeAmount; j++) strcpy(list[i].fakeList[j], fscanfSentence(fp));
		while (ch != '$') fscanf(fp, "%c", &ch);
	}
	fclose(fp);
	return list;
}
/*
This function prints to the file "messages.txt" the list received according the amount received
If the file won't open - it returns 0
If the printing will success- it returns 1
*/
int setMessages(message *list, int size)
{
	int i;
	char path[18] = "data/messages.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%d\n", size);
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%s\n", list[i].ID);
		fprintf(fp, "%s\n", list[i].msg);
		fprintf(fp, "$\n");
	}
	fclose(fp);
	if (size) free(list);
	return 1;
}
//This function scans from the file "messages.txt" a list of users
/*
If the file won't open - it will return NULL
If the scanning will success- it will return the list
*/
message* getMessages(int *size)
{
	int i;
	message *list;
	list = NULL;
	char path[18] = "data/messages.txt", ch='\0';
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return list;
	
	fscanf(fp, "%d", size);
	if (*size == 0) list = NULL;
	else list = (message*)malloc(sizeof(message)*(*size));
	for (i = 0; i < *size; i++)
	{
		ch = '\0';
		fscanf(fp, "%s", list[i].ID);
		strcpy(list[i].msg, fscanfSentence(fp));
		while (ch != '$') fscanf(fp, "%c", &ch);
	}
	fclose(fp);
	return list;
}
/*
This function prints to the file "bestResult.txt" the list received according the amount received
If the file won't open - it returns 0
If the printing will success- it returns 1
*/
int setBest(best *list, int size)
{
	int i;
	char path[20] = "data/bestResult.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%d\n", size);
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%d\n", list[i].bestResult);
		fprintf(fp, "%s\n", list[i].ID);
		fprintf(fp, "$\n");
	}
	fclose(fp);
	if (size) free(list);
	return 1;
}
/*This function returns the list of the Best scores of the users according the amount received
if the file won't open- it will return NULL
if the scanning will sucesses it will return the list
*/
best* getBest(int *size)
{
	int i;
	char path[20] = "data/bestResult.txt", ch='\0';
	FILE *fp = fopen(path, "r");
	best *list;
	fscanf(fp, "%d", size);
	if (fp == NULL)
		return fp;
	if (*size == 0) list = NULL;
	else list = (best*)malloc(sizeof(best)*(*size));
	for (i = 0; i < *size; i++)
	{
		ch = '\0';
		fscanf(fp, "%d", &list[i].bestResult);
		fscanf(fp, "%s", list[i].ID);
		while (ch != '$') fscanf(fp, "%c", &ch);
	}
	fclose(fp);
	return list;
}
//This function prints to the file instructions.txt the msg received
/*
if the file wont open- it will return 0
if the printing will sucess it will return 1
*/
int setInstructions(char *msg)
{
	char path[22] = "data/instructions.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%s\n", msg);
	fclose(fp);
	return 1;
}
//This function scans from the file "instructions.txt" a msg
/*
If the file won't open - it will return NULL
If the scanning will success- it will return the msg
*/
char* getInstructions()
{
	char path[22] = "data/instructions.txt", msg[6400];
	FILE *fp = fopen(path, "r");
	if (fp==NULL)
		return fp;
	strcpy(msg, fscanfSentence(fp));
	fclose(fp);
	return msg;
}
//This function prints to the file comments_for_dev.txt the msg received
/*
if the file wont open- it will return 0
if the printing will sucess it will return 1
*/
int setCommentsForDev(char *msg)
{
	char path[26] = "data/comments_for_dev.txt";
	FILE *fp = fopen(path, "a");
	if (fp == NULL)
		return 0;
	fprintf(fp, "%s\n", msg);
	fprintf(fp, "$\n");
	fclose(fp);
	return 1;
}
/*
This function reset the file comments_for_dev.txt 
If the file wont open- It will return 0
If the reseting will success- it will return 1
*/
int resetAll()
{
	int res;
	char path[26] = "data/comments_for_dev.txt";
	FILE *fp = fopen(path, "w");
	if (fp == NULL)
		return 0;
	fprintf(fp, "");
	fclose(fp);
	res=resetUsers();
	if (res)
		res = resetQuestions();
	if(res)
		res=setInstructions("None");
	return 1;
}