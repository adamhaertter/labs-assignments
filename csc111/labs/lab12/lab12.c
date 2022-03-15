/* CSC111 Computer Science II
 * Lab 12 - Pig Latin Strings
 * Programmers: Adam Haertter, Yong Hang Lin, Austin Sheppard
 * Professor: Dr. Lee
 * File Created: Nov 11, 2019
 * File Updated: Nov 12, 2019
 */

#include "lab12.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100

int main() {
    char word[N];
    char orig[N];
    printf("Enter a string: ");					//Prompts user to enter a string
    scanf("%s", word);						//Assigns string to word
    strcpy(orig, word);						//Copies word to orig
    strcat(word, "-");						//Adds "-" to the end of word

    if(isVowel(word[0]))					//Rule 1
        strcat(word, "w");					//Adds "w" to the end of word if it starts with a vowel
    else if(hasVowel(word)){					//Rule 2
        char *hold = malloc(sizeof(word));			//Allocates memory for temporary string
        while(!isVowel(word[0])){
                strncat(hold, word, 1);				//Adds letters of word to hold until a vowel is hit
                strcpy(word, shift(word));			//Shifts word up by one letter until a vowel is hit
        }
        strcat(word, hold);					//Adds hold onto the end of word
    	free(hold);						//Frees hold from memory
    }
    else if(hasY(word)){					//Rule 3
        char *hold = malloc(sizeof(word));			//Allocates memory for temporary string
        while(!isY(word[0])){
                strncat(hold, word, 1);				//Adds letters of word to hold until a y is hit
                strcpy(word, shift(word));			//Shifts word up by one letter until a y is hit
        }
        strcat(word, hold);					//Adds hold onto the end of word
	free(hold);						//Frees hold from memory
    }
    else							//Rule 4
        strcat(word, "w");					//Adds "w" to the end of word if it doesn't begin with a letter
    strcat(word, "ay");						//Adds "ay" to the end of word
    printf("The pig Latin form of %s is: %s\n", orig, word);	//Prints final result

    return 0;
}
int hasVowel(char s[]) {					//Checks if string s contains a vowel
    for(int i=0; i<strlen(s); i++){				//Checks every letter in s
        if(s[i]=='a' || s[i]=='e' || s[i]=='i' || s[i]=='o' || s[i]=='u'
	|| s[i]=='A' || s[i]=='e' || s[i]=='I' || s[i]=='O' || s[i]=='U')
            return 1;						//Returns true if a, e, i, o, or u is hit
    }
    return 0;							//Returns false otherwise
}
int isVowel(char s) {						//Checks if character s is a vowel
        if(s=='a' || s=='e' || s=='i' || s=='o' || s=='u'
	|| s=='A' || s=='E' || s=='I' || s=='O' || s=='U')
            return 1;						//Returns true if a, e, i, o, or u is hit
    return 0;							//Returns false otherwise
}
int hasY(char s[]) {						//Checks if string s contains a y
    for(int i=0; i<strlen(s); i++){				//Checks every letter in s
        if(s[i]=='y')
            return 1;						//Returns true if y is hit
    }
    return 0;							//Returns false otherwise
}
int isY(char s) {						//Checks if character s is a y
        if(s=='y')
            return 1;						//Returns true if y is hit
    return 0;							//Returns false otherwise
}
char *shift(char s[]){						//Shifts every character in the string s up by one index
    for(int i=0; i<strlen(s); i++){
        s[i] = s[i+1];						//Moves s[i+1] to s[i] for all letters
    }
    s[strlen(s)+1] = '\0';					//Adds null character on the end
    return s;
}
