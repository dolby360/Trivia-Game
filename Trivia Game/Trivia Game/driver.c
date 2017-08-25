#define _CRT_SECURE_NO_WARNINGS
#include "general.h"
#include "menus.h"
#include "play.h"
#include "student.h"
#include "MinUnit.h"

void runAllSuite()
{
	resetAll();
	MU_RUN_SUITE(test_ResultsFunction);
	MU_RUN_SUITE(test_MSG_firstFunctions);
	resetAll();
	MU_RUN_SUITE(test_UserFunctions);
	MU_RUN_SUITE(test_QuestionsFunctions);
	MU_RUN_SUITE(test_MSGFunctions);
	MU_RUN_SUITE(test_generalFunctions1);
	MU_RUN_SUITE(test_generalFunctions2);
	MU_RUN_SUITE(test_generalFunctions3);
	MU_RUN_SUITE(test_TimeCalculateFunctions);
	MU_RUN_SUITE(test_setUsersFunction);
	MU_RUN_SUITE(test_setQuestionsFunction);
	MU_RUN_SUITE(test_setFakeAnswersFunction);
	MU_RUN_SUITE(test_setMessagesFunction);
	resetAll();
}
void adding_users()
{
	user list_stu;
	user list_gu;
	user list_ed;
	best *stud=(best*)malloc(sizeof(best));
	strcpy(list_stu.ID, "1");
	list_stu.average = 12;
	strcpy(list_stu.firstName, "studentf");
	strcpy(list_stu.lastName, "studentl");
	list_stu.highScore = 12;
	strcpy(list_stu.password, "pass_s");
	list_stu.scoreList = malloc(sizeof(1));
	list_stu.scoreList[0] = 12;
	list_stu.userType = student;
	list_stu.gamesPlayed = 1;
	stud->bestResult = 12;
	strcpy(stud->ID, "1");
	addUser(list_stu);
	setBest(stud, 1);
	//**************************

	strcpy(list_gu.ID, "2");
	list_gu.average = 0;
	strcpy(list_gu.firstName, "guidef");
	strcpy(list_gu.lastName, "guidel");
	list_gu.highScore = 0;
	strcpy(list_gu.password, "pass_g");
	list_gu.userType = guide;
	list_gu.gamesPlayed = 0;
	addUser(list_gu);
//******************************

	strcpy(list_ed.ID, "3");
	list_ed.average = 0;
	strcpy(list_ed.firstName, "editorf");
	strcpy(list_ed.lastName, "editorl");
	list_ed.highScore = 0;
	strcpy(list_ed.password, "pass_e");
	list_ed.userType = editor;
	list_ed.gamesPlayed = 0;
	addUser(list_ed);

}
void running_unit_tests()
{
	int *sizeQ, res, *sizeFA;
	question* listQ;
	fakeAnswer* listFA;
	listQ = getQuestions(&sizeQ);
	listFA = getFakeAnswers(&sizeFA);
	runAllSuite();
	MU_REPORT();
	res = setQuestions(listQ, sizeQ);
	res = setFakeAnswers(listFA, sizeFA);
}

int main()
{
	int selection;
	//=====================
	//Running the project:
	//=====================
	printf("Enter 0 for test mode, anything else to start the program\n");
	scanf("%d", &selection);
	if (!selection)
	{
		running_unit_tests();
		adding_users();
		printf("Press any key to continue\n");
		_getch();
	}
	first_menu();
	printf("=============================\n");
	printf("bye bye enter any key to exit\n");
	printf("=============================\n");
	_getch();
	return 0;
}
