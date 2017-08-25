#include "general.h"
#include "files.h"
/*This function checks if the str received has char characters
if yes-it returns -1
if no- it returns the numbers(the str)
*/
long inputCheck(char* str)
{
	int i;
	long num = 0;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] >= '0'&&str[i] <= '9') num = num * 10 + str[i] - 48;
		else return -1;
	}
	if (strlen(str) > 10) return -1;
	return num;
}
/*This function checks(with inputCheck function) if the str receives include only numbers
if it doesn't- it gives the user trying again*/
long whileNotInt(char* str)
{
	long num = inputCheck(str);
	char *arr = (char*)malloc(sizeof(1));
	while (num == -1)
	{
		printf("Try again. Wrong input\n");
		scanf("%s", arr);
		num = inputCheck(arr);
	}
	free(arr);
	return num;
}
//This function checks if the user sure of doing the action
int rUsure()
{
	char x;
	while (1)
	{
		fflush(stdin);
		printf("Are you sure? (enter y if yes, n if no)\n");
		scanf("%c", &x);
		if (x == 'y' || x == 'Y') return 1;
		if (x == 'n' || x == 'N') return 0;
		printf("Wrong input. Try again\n");
	}
}
//This function prints the user received
int printUser(user unit)
{
	char x[80];
	int i;
	if (unit.userType == 0) strcpy(x,"student");
	else if (unit.userType == 1) strcpy(x, "editor");
	else strcpy(x, "guide");
	printf("first name: %s\n", unit.firstName);
	printf("last name: %s\n", unit.lastName);
	printf("ID: %s\n", unit.ID);
	printf("user type: %s\n", x);
	if (unit.userType == student)
	{
		printf("games played: %d\n", unit.gamesPlayed);
		printf("average: %d\n", unit.average);
		printf("high score: %d\n", unit.highScore);
		if (unit.gamesPlayed)
		{
			printf("Score List:\n");
			for (i = 0; i < unit.gamesPlayed; i++) printf("%d) %d\n", i + 1, unit.scoreList[i]);
		}
	}
	return 1;
}
//This function prints the student received
int printStudent(user unit)
{
	int i;
	printf("first name: %s\n", unit.firstName);
	printf("last name: %s\n", unit.lastName);
	printf("ID: %s\n", unit.ID);
	printf("games played: %d\n", unit.gamesPlayed);
	printf("average: %d\n", unit.average);
	printf("high score: %d\n", unit.highScore);
	if (unit.gamesPlayed)
	{
		printf("Score List:\n");
		for (i = 0; i < unit.gamesPlayed; i++) printf("%d) %d\n", i + 1, unit.scoreList[i]);
	}
	return 1;
}
//This function prints the list of the users received according the amount
void printUserList(user* list, int size)
{
	int i,print;
	system("cls");
	printf("List of users:\n");
	for (i = 0; i < size; i++)
	{
		print=printUser(list[i]);
		printf("*******************************\n");
	}
	if (size) free(list);
}
//This function prints the list of the students received according the amount
void printStudentList(user *list, int size)
{
	int i,cnt=0,print;
	system("cls");
	printf("List of users:\n");
	for (i = 0; i < size; i++)
	{
		if (list[i].userType == student)
		{
			cnt++;
			print=printUser(list[i]);
			printf("*******************************\n");
		}
	}
	if (!cnt) printf("No students in database\n");
	if (size) free(list);
	return;
}
//This function prints the question received
int printQuestion(question q)
{
	printf("ID: %d\n\n", q.ID);
	printf("Level: %d\n", q.level);
	printf("%s\n", q.str);
	printf("Correct Answer: %s\n", q.answer);
	return 1;
}
//This function prints the list of the questions received according the amount
void printQuestionList(question* list, int size)
{
	int i,prt;
	if (list == NULL)
	{
		printf("No questions to display\n");
		return;
	}
	printf("List of questions:\n************\n");
	for (i = 0; i < size; i++)
	{
		prt=printQuestion(list[i]);
		printf("************\n");
	}
	if (size) free(list);
	return;
}

/*This function search a user according the ID received.
If it finds it- returns the user
If not- returns user with id=-1*/
user searchUser(char *id)
{
	int i, size = 0,j;
	user error, *list = getUsers(&size),found;
	error.average = -1;
	error.gamesPlayed = 0;
	for (i = 0; i < size; i++)
	{
		if (!strcmp(list[i].ID, id))
		{
			found = list[i];
			if (list[i].gamesPlayed) found.scoreList = (int*)malloc(sizeof(int)*list[i].gamesPlayed);
			else found.scoreList = NULL;
			for (j = 0; j < size; j++) if (list[j].gamesPlayed) free(list[j].scoreList);
			free(list);
			return found;
		}
	}
	if (size) free(list);
	return error;
}
//This function add the user received to the users exist with using the functions set&get users
int addUser(user newUser)
{
	int size = 0, i, setOK;
	user *list = getUsers(&size),*newList;
	char fname[80];
	if (size)
	{
		newList = (user*)malloc(sizeof(user)*(size + 1));
		for (i = 0; i < size; i++) newList[i] = list[i];
		free(list);
	}
	
	else newList = (user*)malloc(sizeof(user));
	newList[size] = newUser;
	setOK=setUsers(newList, size + 1);
	if (setOK)
	{
		printf("User added succesfully\n");
		return 1;
	}
}

//This function add the question and fake answer received to those which exist with using the functions set&get questions+fakeAnswers
int addQuestion(question q, fakeAnswer fa)
{
	int size = 0, i, res;
	question *qList = getQuestions(&size), *newQ;
	fakeAnswer *faList = getFakeAnswers(&size), *newFA;
	if (size)
	{
		q.ID = qList[size - 1].ID + 1;
		fa.ID = faList[size - 1].ID + 1;
	}
	else
	{
		q.ID = 1;
		fa.ID = 1;
	}
	if (size)
	{
		newQ = (question*)malloc(sizeof(question)*(size + 1));
		for (i = 0; i < size; i++) newQ[i] = qList[i];
		newFA = (fakeAnswer*)malloc(sizeof(fakeAnswer)*(size + 1));
		for (i = 0; i < size; i++) newFA[i] = faList[i];
		free(qList);
		free(faList);
	}
	else
	{
		newQ = (question*)malloc(sizeof(question));
		newFA = (fakeAnswer*)malloc(sizeof(fakeAnswer));
	}
	newQ[size] = q;
	newFA[size] = fa;
	res = setQuestions(newQ, size + 1);
	if (res)
		res = setFakeAnswers(newFA, size + 1);
	if (res)
	{
		printf("Question added succesfully\n");
		return 1;
	}
	return 0;
}
//This function scan a sentence from the user until \0 or \n
char* scanSentence()
{
	char ch, str[1000];
	int i = 0;
	fflush(stdin);
	while (ch = getchar())
	{
		if (ch == '\n' || ch == '\0') break;
		else str[i++] = ch;
	}
	str[i] = '\0';
	return str;
}
//This function scan a sentence from the file received until \0 or \n 
char* fscanfSentence(FILE *fp)
{
	char ch, str[1000];
	int i = 0, first=1;
	fflush(stdin);
	while (fscanf(fp,"%c",&ch))
	{
		if (first && ch == '\n') fscanf(fp, "%c", &ch);
		first = 0;
		if (ch == '\n' || ch == '\0') break;
		else str[i++] = ch;
	}
	str[i] = '\0';
	return str;
}
/*This function search a question according the ID received.
If it finds it- returns the question
If not- returns question with id=-1*/
question searchQuestion(int id)
{
	int size,i;
	question *list = getQuestions(&size);
	question error,found;
	error.ID = -1;
	for (i = 0; i < size; i++)
	{
		if (list[i].ID == id)
		{
			found = list[i];
			free(list);
			return found;
		}
	}
	if (size) free(list);
	return error;
}
/*This function search a fakeAnswer according the ID received.
If it finds it- returns the fakeAnswer
If not- returns fakeAnswer with id=-1*/
fakeAnswer searchFakeAnswer(int id)
{
	int size,i;
	fakeAnswer *list = getFakeAnswers(&size),found;
	for (i = 0; i < size; i++)
	{
		if (list[i].ID == id)
		{
			found = list[i];
			free(list);
			return found;
		}
	}
}
/*This funtion remove a question received if it exists
If it success- it returns 1*/
void removeQuestion(question q)
{
	int size,i,j=0,res;
	question *list = getQuestions(&size), *newList = (question*)malloc(sizeof(question)*(size-1));
	fakeAnswer fa = searchFakeAnswer(q.ID),*newFA = (fakeAnswer*)malloc(sizeof(fakeAnswer)*(size-1));
	fakeAnswer *faList = getFakeAnswers(&size);
	for (i = 0; i < size; i++)
	{
		if (list[i].ID != q.ID)
		{
			newList[j] = list[i];
			newFA[j++] = faList[i];
		}
	}
	if (size > 1)
	{
		setQuestions(newList, size - 1);
		
		setFakeAnswers(newFA, size - 1);
	}
	else resetQuestions();
	if (size)
	{
		free(list);
		free(faList);
	}
	return 1;
}
/*This function calculates and returns the average of the users with type student 
If there are no students- it returns 0 
*/
int getAverage()
{
	int size = 0,i;
	user *list = getUsers(&size);
	float amount = 0,sum=0;
	for (i = 0; i < size; i++)
	{
		if (list[i].userType == student)
		{
			amount++;
			sum += list[i].average;
		}
	}
	if (!amount) return 0;
	if (size) free(list);
	return sum / amount;
}
/*This function reset the scores of the users*/
int resetScores()
{
	int res,size = 0, i, j;
	res = setBest(NULL, 0);
	if (res)
	{
		user *list = getUsers(&size);
		for (i = 0; i < size; i++)
		{
			list[i].average = 0;
			free(list[i].scoreList);
			list[i].gamesPlayed = 0;
			list[i].highScore = 0;
		}
		if (size) free(list);
		return 1;
	}
}
/*This function change the question received with using the functions removeQuestion and addQuestion*/
void changeQuestion(question q)
{
	int i,amount,prt;
	question nq;
	char temp[80];
	long level;
	fakeAnswer fa,f=searchFakeAnswer(q.ID);
	system("cls");
	printf("Current question information:\n");
	prt=printQuestion(q);
	printf("Fake answers:\n");
	for (i = 0; i < f.fakeAmount; i++) printf("%s\n", f.fakeList[i]);
	printf("************************\n");
	printf("Enter the changed question:\n");
	strcpy(nq.str, scanSentence());
	printf("Select level of question from 1 to 10 (1 is the easiest, 10 is the hardest)\n");
	do{
		fflush(stdin);
		scanf("%s", temp);
		level = whileNotInt(temp);
		if (level < 1 || level>10) printf("Wrong input. Try again\n");
	} while (level < 1 || level>10);
	nq.level = level;
	printf("Enter correct answer: ");
	strcpy(nq.answer, scanSentence());
	printf("How many fake answers do you wish to give? (no more than 5)\n");
	do{
		scanf("%s", temp);
		amount = whileNotInt(temp);
		if (amount < 1 || amount > 5) printf("Wrong input. Try again\n");
	} while (amount < 1 || amount > 5);
	fa.fakeAmount = amount;
	for (i = 0; i < amount; i++)
	{
		printf("Enter fake answer number %d: ", i + 1);
		do{
			strcpy(fa.fakeList[i], scanSentence());
			if (!strcmp(q.answer, fa.fakeList[i])) printf("That is the correct answer. Try again\n");
		} while (!strcmp(q.answer, fa.fakeList[i]));
	}
	fa.ID = q.ID;
	nq.ID = q.ID;
	nq.answered = 0;
	removeQuestion(q);
	prt=addQuestion(nq, fa);
	return; 
}
/*This function add the message received to those which exist with using the functions set&get messages*/
int addMessage(message m)
{
	int i, size = 0, j, res;
	message *list = getMessages(&size);
	message *nlist;
	for (i = 0; i < size; i++) if (!strcmp(m.ID, list[i].ID)) break;
	if (i == size)
	{
		nlist = (message*)malloc(sizeof(message)*(size + 1));
		for (j = 0; j < size; j++) nlist[j] = list[j];
		nlist[size] = m;
		free(list);
		res = setMessages(nlist, size + 1);
	}
	else
	{
		strcpy(list[i].msg, m.msg);
		res = setMessages(list, size);
	}
	if (res)
	{
		printf("Message added succesfully\n");
		return 1;
	}
	return 0;
}