#include "time_calculate.h"

time_t rawtime;
//define the 
struct tm *info;
int time_start = 0;
int time_end = 0;
/*This function prints the time now*/
void time_now()
{
	printf("the time now is : %s \n", asctime(info));
}
/*This function calculates the time of the beggining the game*/
void start_time()
{
	time(&rawtime);

	info = localtime(&rawtime);

	//convert the time to sec;
	time_start = (info->tm_hour)*(60 * 60) + info->tm_min * 60 + info->tm_sec;
}
/*This function calculates the time of the ending the game*/
void start_end()
{
	time(&rawtime);

	info = localtime(&rawtime);
	//convert the time to sec;
	time_end = (info->tm_hour)*(60 * 60) + info->tm_min * 60 + info->tm_sec;
}
/*This function calculates the time of the whole game*/
int sum_the_time()
{
	return  time_end - time_start;
}