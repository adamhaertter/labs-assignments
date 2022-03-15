/* CSC111: Computer Science II
 * Remind: remindv3.c
 * Programmer: Andrew Kress & Adam Haertter
 * Professor: Dr. Lee
 * File Created: 10/22/19
 * File Modified: 10/22/19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REMIND 50                                    //max num of reminders
#define MSG_LEN 60                                        //max length of msg

int read_line(char str[], int n);

int main() {
    char *reminders[MAX_REMIND];
    char day_str[3], msg_str[MSG_LEN + 1];
    int day, i, j, num_remind = 0;

    for (;;) {
        if (num_remind == MAX_REMIND) {                    //Checks if the user has met the maximum amount of reminders
            printf("-- No Space Left --\n");
            break;
        }

        printf("Enter day and reminder: ");                //Asks user to enter the day and reminder
        scanf("%2d", &day);
        if (day == 0)                                    //Detects if the user inputed a 0 the terminate
            break;
        sprintf(day_str, "%2d", day);
        read_line(msg_str, MSG_LEN);
        
        for (i = 0; i < num_remind; i++)                //Reorders the reminders
            if (strncmp(day_str, reminders[i], 3) < 0)
                break;
        for (j = num_remind; j > i; j--)
            reminders[j] = reminders[j - 1];
		
		reminders[i] = malloc(2 + strlen(msg_str) + 1);
		if (reminders[i] == NULL) {
			printf("-- No Space Left --\n");
			break;
		}

        strncpy(reminders[i], day_str, 3);
        strncat(reminders[i], msg_str, MSG_LEN);
        
        num_remind++;
    }
    
    printf("\nDay Reminder\n");                            //Prints the reminders in order
    for (i = 0; i < num_remind; i++)
        printf(" %s\n", reminders[i]);

    return 0;
}

int read_line(char *str, int n) {
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}
