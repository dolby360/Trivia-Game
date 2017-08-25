#include "test.h"
#include "files.h"

void testQuestions()
{
	question *list = (question*)malloc(sizeof(question)*QNUM);
	fakeAnswer *faList = (fakeAnswer*)malloc(sizeof(question)*QNUM);
	int i;
	char str[80];
	resetQuestions();
	for (i = 0; i < QNUM; i++)
	{
		strcpy(list[i].str, "Created question\n",i+1);
		strcpy(list[i].answer, "Created answer\n", i + 1);
		list[i].level = 1;
		list[i].answered = 0;
		faList[i].fakeAmount = 1;
		strcpy(faList[i].fakeList[0], "Created fake answer\n",i+1);
		addQuestion(list[i], faList[i]);
	}
}

