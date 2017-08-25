#include "student.h"
/*This function print the menu for a student and calls functions according the option the student enterd*/
void student_menu(user stud)
{
	char temp[80], con, msg[1000];
	int selection = 1, BestRes;
	strcpy(msg, getInstructions());
	if (strcmp(msg, "None"))
	{
		system("cls");
		printf("Instructions:\n");
		printf("%s\n\n", msg);
		printf("Press any key to continue\n");
		_getch();
	}
	while ((selection != 4) && (selection != 5))
	{
		system("cls");
		printf("***********Student: %s %s***************\n", stud.firstName, stud.lastName);
		printf("Select one of the following options\n");
		printf("1) Play game\n");
		printf("2) View current record\n");
		printf("3) Receive Message\n");
		printf("4) Log off\n");
		printf("5) Quit\n");
		do{
			scanf("%s", temp);
			selection = whileNotInt(temp);
			if (selection < 1 || selection>5) printf("Wrong input. Try again\n");
		} while (selection < 1 || selection>5);
		switch (selection)
		{
		case 1:
			student_menu_play_game(stud);
			break;
		case 2:
			BestRes = view_current_record(&stud.ID);
			if (BestRes == -1)
			{
				system("cls");
				printf("There is no record\n You have not played yet\nPress any key to continue");
				_getch();
			}
			else
			{
				system("cls");
				printf("Your record: %d\nTry to get a greater record with a new game! :)\nPress any key to continue\n", BestRes);
				_getch();
			}
			break;
		case 3:
			menu_receivemsg(stud.ID);
			break;
		case 4:
			return;
		case 5:
			printf("Have a nice day\n");
			exit(0);
		}
	}
}
/*The function plays game for student and then 
calculates the result into the score list of the user*/
void student_menu_play_game(user stud)
{
	int score = start_to_play(student),sum=0;
	int size = 0, i, j, *temp, bsize=0;
	user *list = getUsers(&size);
	best *blist,*tempList;
	for (i = 0; i < size; i++) if (!strcmp(list[i].ID, stud.ID)) break;
	if (stud.highScore < score)
	{
		printf("Congratulations. You set a new high score\n");
		printf("Press any key to continue\n");
		_getch();
		list[i].highScore = score;
		blist = getBest(&bsize);
		for (j = 0; j < bsize; j++) if (!strcmp(stud.ID, blist[j].ID)) break;
		if (j < bsize)
		{
			blist[j].bestResult = score;
			setBest(blist, bsize);
		}
		else
		{
			bsize++;
			tempList = (best*)malloc(sizeof(best)*bsize);
			for (j = 0; j < bsize - 1; j++)
			{
				tempList[j].bestResult = blist[j].bestResult;
				strcpy(tempList[j].ID, blist[j].ID);
			}
			tempList[j].bestResult = score;
			strcpy(tempList[j].ID, stud.ID);
			free(blist);
			setBest(tempList, bsize);
		}
	}
	list[i].gamesPlayed++;
	temp = (int*)malloc(sizeof(int)*list[i].gamesPlayed);
	for (j = 0; j < list[i].gamesPlayed - 1; j++) temp[j] = list[i].scoreList[j];
	temp[j] = score;
	free(list[i].scoreList);
	list[i].scoreList = (int*)malloc(sizeof(int)*list[i].gamesPlayed);
	for (j = 0; j < list[i].gamesPlayed; j++)
	{
		sum += temp[j];
		list[i].scoreList[j] = temp[j];
	}
	free(temp);
	list[i].average = sum / list[i].gamesPlayed;
	setUsers(list, size);
}

/*This function returns the record of the user received.
If it isn't exist- returns -1 check of the unit testing*/
int view_current_record(char* id_user)
{
	int size, i;
	best *list;
	list = getBest(&size);

	for (i = 0; i < size; i++)
	{
		if (!strcmp(list[i].ID, id_user)) return list[i].bestResult;
	}
	if (size) free(list);
	return -1;
}
/*This function represent the message the guide had write to the student with the id received*/
void menu_receivemsg(char* id)
{
	int size,i;
	message *list = getMessages(&size);
	for (i = 0; i < size; i++)
	{
		if (!strcmp(list[i].ID, id)) break;
	}
	system("cls");
	if (i == size) printf("No message to display\n");
	else
	{
		puts("Message from guide team:\n");
		printf("%s\n", list[i].msg);
	}
	printf("Press any key to continue\n");
	_getch();
	if (size) free(list);
	return;
}