#define _CRT_SECURE_NO_WARNINGS
#ifndef _files
#define _files
#include "general.h"

int setUsers(user*, int);

user* getUsers(int*);

int resetUsers();

int setQuestions(question*, int);

question* getQuestions(int*);

int resetQuestions();

int setFakeAnswers(fakeAnswer*, int);

fakeAnswer* getFakeAnswers(int*);

int setMessages(message*, int);

message* getMessages(int*);

int setBest(best*, int);

best* getBest(int*);

int setInstructions(char *msg);

char* getInstructions();

int setCommentsForDev(char *msg);

int resetAll();

#endif _files