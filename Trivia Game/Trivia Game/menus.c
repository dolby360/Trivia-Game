#include "menus.h"
/*This function represents the first menu for the user
It includes choosing of the user type*/
void first_menu()
{
	system("cls");
	int i = 0,res;
	char get_choose[MAX_SIZE],ch;

	while (get_choose[0] != 'e')
	{
		printf("Hello. Select one of the followig options:\n");
		printf("a) Editor\n");
		printf("b) Guide\n");
		printf("c) Student\n");
		printf("e) Exit\n");
		fflush(stdin);
		scanf("%s", get_choose);

		//im checking here if the user enters just one letter;
		if (get_choose[1] == '\0')
		{
			switch (get_choose[0])
			{
			case 'a':
				loginORregister(editor);
				break;
			case 'b':
				loginORregister(guide);
				break;
			case 'c':
				loginORregister(student);
				break;
			case 'd':
				fflush(stdin);
				printf("1 - reset Users. 2 - reset Questions. 3 - reset All. 4 - set created questions\n");
				scanf("%c", &ch);
				fflush(stdin);
				if (ch == '1'&&rUsure()) 
					res=resetUsers();
				if (ch == '2'&&rUsure()) 
					res=resetQuestions();
				if (ch == '3'&&rUsure()) res=resetAll();
				if (ch == '4'&&rUsure()) testQuestions();
				break;
			case 'e':
				system("cls");
				return;
			default:
				printf("you entered illegal letter\n");
				break;
			}
		}
		//if the user entered illegal sentence I clear the array;
		else
		{
			printf("Wrong input. Try again\n");
			for (i = 0; i < MAX_SIZE; i++)
			{
				get_choose[i] = '\0';
			}
		}
		printf("Press any key to continue\n");
		_getch();
		//clean screen;
		system("cls");
	}
}
/*This function represents The option the the user after choosing user type*/
void loginORregister(type uType)
{
	char temp[80];
	long selection;
	while (1)
	{
		fflush(stdin);
		system("cls");
		printf("Please select to login or register:\n");
		printf("1) Login\n");
		printf("2) Register\n");
		printf("3) Back\n");
		printf("4) Exit\n");
		do{
			scanf("%s", temp);
			selection = whileNotInt(temp);
			if (selection < 1 || selection>4) printf("Wrong input. Try again\n");
		} while (selection < 1 || selection>4);
		switch (selection)
		{
		case 1:
			loginScreen(uType);
			break;
		case 2:
			registerScreen(uType);
			break;
		case 3:
			return;
			break;
		case 4:
			printf("Have a nice day\n");
			exit(0);
		}
	}
}
/*This function is the login option- the user has 3 attemps
If he won't success- it will back the previous screen*/
void loginScreen(type uType)
{
	int attempts = 0;
	user found;
	char ID[80], UT[80], pass[80];
	if (uType == student) strcpy(UT, "Student");
	else if (uType == editor) strcpy(UT, "Editor");
	else strcpy(UT, "Guide");
	system("cls");
	fflush(stdin);
	printf("*********%s Log in***********\n", UT);
	printf("you have 3 attempts\n", UT);
	while (attempts < 3)
	{
		printf("Enter ID:\n");
		scanf("%s", ID);
		found = searchUser(ID);
		if (found.average != -1 && found.userType == uType) break;
		if (found.gamesPlayed) free(found.scoreList);
		attempts++;
		printf("\nNo such ID. Try again please\n");
		fflush(stdin);
	}
	if (found.average == -1 || found.userType != uType)
	{
		printf("Failed to enter correct ID\n");
		_getch();
		return;
	}
	attempts = 0;
	while (attempts < 3)
	{
		printf("Enter password:\n");
		scanf("%s", pass);
		if (!strcmp(found.password, pass)) break;
		attempts++;
		if (attempts != 3) printf("Wrong password. Try again please\n");
		fflush(stdin);
	}
	if (strcmp(found.password, pass))
	{
		printf("Failed to enter correct password\n");
		_getch();
		return;
	}
	if (uType == student) student_menu(found);
	else if (uType == editor) editor_menu(found);
	else guide_menu(found);

	return;
}
/*This function is the register option- 
If the user exists there is a message
If the user doesn't exist - the user will be add the users exist*/
void registerScreen(type uType)
{
	user newUser, found;
	char UT[80], ID[80];
	int ch;
	if (uType == student) strcpy(UT, "Student");
	else if (uType == editor) strcpy(UT, "Editor");
	else strcpy(UT, "Guide");
	system("cls");
	fflush(stdin);
	printf("*********%s Register***********\n", UT);
	printf("Enter ID: ");
	scanf("%s", ID);
	found = searchUser(ID);
	if (found.average != -1)
	{
		printf("User already exists\n");
		printf("Press any key to continue\n");
		_getch();
		return;
	}
	strcpy(newUser.ID, ID);
	printf("First name: ");
	scanf("%s", newUser.firstName);
	fflush(stdin);
	printf("Last name: ");
	scanf("%s", newUser.lastName);
	fflush(stdin);
	printf("Password: ");
	scanf("%s", newUser.password);
	fflush(stdin);
	newUser.userType = uType;
	newUser.gamesPlayed = 0;
	newUser.average = 0;
	newUser.highScore = 0;
	newUser.scoreList = NULL;
	ch=addUser(newUser);
	printf("Press any key to continue\n");
	_getch();

	if (uType == student)
	{
		student_menu(newUser);
	}
	else if (uType == editor)
	{
		editor_menu(newUser);
	}
	else
	{
		guide_menu(newUser);
	}
}