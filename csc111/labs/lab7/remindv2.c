/* CSC111 Computer Science II
   Lab 7 Reminder List Secure - remindv2.c
   Programmers: Adam Haertter & Tyler Owens
   Professor: Dr. Lee
   File Created: Oct 13, 2019
   File Updated: Oct 13, 2019
*/

#include <stdio.h>
#include <string.h>

#define MAX_REMIND 50						//Sets reminder limit at 50 entries
#define MSG_LEN 60						//Sets message length at 60 chars

int read_line(char str[], int n);				//Declares read_line method

int main()
{
   char reminders[MAX_REMIND][MSG_LEN+3]	;		//Sets up an array of strings according to the limits above
   char day_str[3], msg_str[MSG_LEN+1];				//Creates arrays for day and message entries
   int day, i, j, num_remind = 0;

   for(;;){
	if(num_remind == MAX_REMIND){
	   printf("-- No space left --\n");			//Prints "No space left" if max reminders reached
	   break;						//Breaks loop automaticcaly if max reminders reached
	}

	printf("Enter day and reminder: ");			//Prompts user to enter reminder and day
	scanf("%2d", &day);					//Scans solely for day
	if(day==0)
	   break;						//Breaks loop if 0 day is entered
	sprintf(day_str, "%2d", day);				//Prints day as a string from array day_str
	read_line(msg_str, MSG_LEN);				//Runs read_line function using the reminder message

	for(i = 0; i < num_remind; i++)
	   if(strncmp(day_str, reminders[i], 3) < 0)		//Compares the first 3 digits of day_str and reminders[i]
		break;						//Breaks nested loop if the day in day_str < day in reminders
	for(j = num_remind; j > i; j--)
	   strncpy(reminders[j], reminders[j-1], MSG_LEN+3);	//Shifts the reminders up one in the array if less than MSG_LEN+3

	strncpy(reminders[i], day_str, 3);			//Copies the day in day_str to reminders if under 3 chars
	strncat(reminders[i], msg_str, MSG_LEN+1);		//Adds the message to the end of the day text if under MSG_LEN+1

	num_remind++;
   }

   printf("\nDay Reminder\n");					//Prints heading
   for(i=0; i<num_remind; i++)
	printf(" %s\n", reminders[i]);				//Prints entries in reminders

   return 0;
}

int read_line(char str[], int n)
{
   int ch, i=0;

   while ((ch = getchar()) != '\n')				//Checks for line breaks
	if(i < n)						//Checks for message length limit
	   str[i++] = ch;					//Sets str entry to ch and post-increments i
   str[i] = '\0';						//Sets final char in str to null to terminate array
   return i;
}
