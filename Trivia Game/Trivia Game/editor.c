#include "editor.h"
/*This function print the menu for an editor and calls functions according the option the editor enterd*/
void editor_menu(user edit)
{
	char temp[80];
	int selection;
	type utype = editor;
	while (1)
	{
		system("cls");
		printf("***********Editor: %s %s***************\n", edit.firstName, edit.lastName);
		printf("Select one of the following options\n");
		printf("1) Play game\n");
		printf("2) Add a question\n");
		printf("3) Delete a question\n");
		printf("4) View student score\n");
		printf("5) View student data\n");
		printf("6) View general average\n");
		printf("7) Change a question\n");
		printf("8) Log off\n");
		printf("9) Quit\n");
		do{ 
			scanf("%s", temp);
			selection = whileNotInt(temp);
			if (selection < 1 || selection>9) printf("Wrong input. Try again\n");
		} while (selection < 1 || selection>9);
		switch (selection)
		{
		case 1:
			start_to_play(editor);
			break;
		case 2:
			menu_addQuestion();
			break;
		case 3:
			menu_deleteQuestion();
			break;
		case 4:
			menu_studentScore();
			break;
		case 5:
			menu_userData();
			break;
		case 6:
			menu_average();
			break;
		case 7:
			menu_changeQuestion();
			break;
		case 8:
			return;
		case 9:
			printf("Have a nice day\n");
			exit(0);
		}
	}
}
/*Adding a question-The user will enter the attributes of a question he wants to add and it will send be to the function addQuestion*/
void menu_addQuestion()
{
	question q;
	fakeAnswer fa;
	char temp[80],ch,str[1000];
	int i = 0,ptr;
	long level,amount;
	system("cls");
	printf("*****************Add Question*******************\n");
	printf("Select level of question from 1 to 10 (1 is the easiest, 10 is the hardest)\n");
	do{
		fflush(stdin);
		scanf("%s", temp);
		level = whileNotInt(temp);
		if (level < 1 || level>10) printf("Wrong input. Try again\n");
	} while (level < 1 || level>10);
	q.level = (int)level;
	q.answered = 0;
	while (1)
	{
		printf("Write the question:\n");
		strcpy(q.str, scanSentence());
		if (rUsure()) break;
	}
	printf("Enter correct answer: ");
	strcpy(q.answer, scanSentence());
	printf("How many fake answers do you wish to give? (no more than 5)\n");
	do{
		scanf("%s", temp);
		amount = whileNotInt(temp);
		if (amount < 1 || amount > 5) printf("Wrong input. Try again\n");
	} while (amount < 1 || amount > 5);
	fa.fakeAmount = (int)amount;
	for (i = 0; i < amount; i++)
	{
		printf("Enter fake answer number %d: ", i + 1);
		do{
			strcpy(fa.fakeList[i],scanSentence());
			if (!strcmp(q.answer, fa.fakeList[i])) printf("That is the correct answer. Try again\n");
		} while (!strcmp(q.answer, fa.fakeList[i]));
	}
	fflush(stdin);
	ptr=addQuestion(q, fa);
	_getch(); 
	return;
}
/*deleting a question-The user will enter the attributes of question he wants to delete and it will be send to the function removeQuestion*/
void menu_deleteQuestion()
{
	question remove,*list;
	char temp[80];
	long selection,id;
	int size;
	system("cls");
	printf("*****************Delete Question*******************\n");
	printf("Select one of the following options\n");
	printf("1) Search a question using ID\n");
	printf("2) Select a question from list\n");
	do{
		fflush(stdin);
		scanf("%s", temp);
		selection = whileNotInt(temp);
		if (selection < 1 || selection>2) printf("Wrong input. Try again\n");
	} while (selection < 1 || selection>2);
	switch (selection)
	{
	case 1:
		printf("Enter ID of a question to search\n");
		fflush(stdin);
		scanf("%s", temp);
		id = whileNotInt(temp);
		remove = searchQuestion(id);
		if (remove.ID == -1) printf("Question doesn't exist\n");
		else
		{
			removeQuestion(remove);
			printf("Question removed. Press any key to continue\n");
		}
		_getch();
		break;
	case 2:
		list = getQuestions(&size);
		printQuestionList(list, size);
		printf("Enter ID of a question to remove\n");
		fflush(stdin);
		scanf("%s", temp);
		id = whileNotInt(temp);
		remove = searchQuestion(id);
		if (remove.ID == -1) printf("Question doesn't exist\n");
		else
		{
			removeQuestion(remove);
			printf("Question removed. Press any key to continue\n");
		}
		_getch();
	}
}
//This function prints the list of the student's best result
void menu_studentScore()
{
	int i,size=0;
	best *list = getBest(&size);
	user current;
	system("cls");
	printf("*****************Student Score*******************\n");
	if (size == 0) printf("No scores to show\n");
	else
	{
		printf("List of student's Best Results:\n\n");
		for (i = 0; i < size; i++)
		{
			current = searchUser(list[i].ID);
			printf("First Name: %s\n", current.firstName);
			printf("Last Name: %s\n", current.lastName);
			printf("ID: %s\n", current.ID);
			printf("Best Result: %d\n", list[i].bestResult);
			printf("*****************************\n");
		}
	}
	printf("Press any key to continue\n");
	_getch();
	if (size) free(list);
	return;
}
//This function prints the data of the users exist
void menu_userData()
{
	printf("*****************Student data list*******************\n");
	int size = 0;
	user *list = getUsers(&size);
	printStudentList(list, size);
	printf("Press any key to continue\n");
	_getch();
}
/*This function prints the average of the users exist.
It also has the option of reset the scores*/
void menu_average()
{
	float avg = getAverage();
	char ch;
	system("cls");
	printf("*****************General Average*******************\n");
	if (avg == 0) printf("No average to show. No games played yet\n");
	else
	{
		printf("General average: %.2f\n\n", avg);
	}
	if (avg)
	{
		printf("Enter 0 if you wish to erase all game data from all students and reset scores.\n");
		printf("To quit enter anything else\n");
		fflush(stdin);
		scanf("%c", &ch);
		if (ch == '0' && rUsure())
		{
			resetScores();
			printf("Operation completed successfully\n");
		}
	}
	fflush(stdin);
	printf("Press any key to continue\n");
	_getch();
	return;
}
/*changeQuestion- If the question's id the user entered exists it will be send to changeQuestion
There is also an option of search question from list */
void menu_changeQuestion()
{
	question change, *list;
	char temp[80];
	long selection, id;
	int size;
	system("cls");
	printf("*****************Change Question*******************\n");
	printf("Select one of the following options\n");
	printf("1) Search a question using ID\n");
	printf("2) Select a question from list\n");
	do{
		fflush(stdin);
		scanf("%s", temp);
		selection = whileNotInt(temp);
		if (selection < 1 || selection>2) printf("Wrong input. Try again\n");
	} while (selection < 1 || selection>2);
	switch (selection)
	{
	case 1:
		printf("Enter ID of a question to change\n");
		fflush(stdin);
		scanf("%s", temp);
		id = whileNotInt(temp);
		change = searchQuestion(id);
		if (change.ID == -1) printf("Question doesn't exist\n");
		else
		{
			changeQuestion(change);
			printf("Question removed. Press any key to continue\n");
		}
		_getch();
		break;
	case 2:
		system("cls");
		list = getQuestions(&size);
		printQuestionList(list, size);
		printf("Enter ID of a question to change\n");
		fflush(stdin);
		scanf("%s", temp);
		id = whileNotInt(temp);
		change = searchQuestion(id);
		if (change.ID == -1) printf("Question doesn't exist\n");
		else
		{
			changeQuestion(change);
			printf("Question removed. Press any key to continue\n");
		}
		_getch();
	}
}