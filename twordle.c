//Author: Morgan Malen
//Date: April 2026
//Purpose: Project 10

#include <stdio.h>

#define ROWS 7
#define COLUMNS 10
#define CORRECTWORD "word.txt"
#define CAP 25

int checkLetterCount(int wordPos, char userGuess[][COLUMNS]);
int checkAllLetters(int wordPos, char userGuess[][COLUMNS]);
void printTryAgain(int tooLong, int notLetters);
void uppercaseToLowercase(int rows, int columns, int wordPos, char userGuess[][COLUMNS]);
int exactMatch(int rows, int columns, int wordPos, char userGuess[][COLUMNS], char correctWordStr[CAP]);
void rightPosition(int rows, int columns, int wordPos, char userGuess[][COLUMNS], char correctWordStr[CAP], char hintsStr[][COLUMNS]);
void gameResults(int guessCheck, int wordPos, char correctWordStr[]);

int main(){
	int wordPos=0, tooLong, notLetters, guessCheck=0;
	char userGuess[ROWS][COLUMNS], hintsStr[ROWS][COLUMNS];
	char correctWordStr[CAP];
	
	FILE* correctWordPtr=fopen(CORRECTWORD, "r");
	
	if (correctWordPtr==NULL){
		printf("Could not open file!\n");
		return 0;
	}
	
	fgets(correctWordStr, CAP, correctWordPtr);
	
	while(guessCheck==0 && wordPos<6){
		wordPos++;
		switch (wordPos){
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				printf("GUESS %d! Enter your guess:", wordPos);
				break;
			case 6:
				printf("\n================================");
				printf("\nFINAL GUESS : ");
				break;
		}
		
		scanf("%s", userGuess[wordPos]);
		
		notLetters=checkAllLetters(wordPos, userGuess);
		tooLong=checkLetterCount(wordPos, userGuess);
		
		while (tooLong==1 || notLetters==1){
			printTryAgain(tooLong, notLetters);
			scanf("%s", userGuess[wordPos]);
			notLetters=checkAllLetters(wordPos, userGuess);
			tooLong=checkLetterCount(wordPos, userGuess);
		}
		
		uppercaseToLowercase(ROWS, COLUMNS, wordPos, userGuess);
		guessCheck=exactMatch(ROWS, COLUMNS, wordPos, userGuess, correctWordStr);
	
		rightPosition(ROWS, COLUMNS, wordPos, userGuess, correctWordStr, hintsStr);
		
		printf("\n================================\n");

		for (int i=0; i<wordPos+1; i++){
			printf("%s\n", userGuess[i]);
			printf("%s\n", hintsStr[i]);
		}	
	} 
	
	if (guessCheck==1 || wordPos==6){
		gameResults(guessCheck, wordPos, correctWordStr);
	}
	
	fclose(correctWordPtr);
	
	return 0;
}

int checkAllLetters(int wordPos, char userGuess[][COLUMNS]){
	int flag=0, i=0;
 	while((userGuess[wordPos][i]>='a' && userGuess[wordPos][i]<='z') || (userGuess[wordPos][i]>='A' && userGuess[wordPos][i]<='Z')){
 		i++;
	}
	
	if(userGuess[wordPos][i]=='\0'){
		flag=0;
	}
	
	else {
		flag=1;
	}
	return flag;
}

int checkLetterCount(int wordPos, char userGuess[][COLUMNS]){
	int length=0, flag=0;
	for (int i=0; userGuess[wordPos][i]!='\0'; i++){
		if ((userGuess[wordPos][i]>='a' && userGuess[wordPos][i]<='z') || (userGuess[wordPos][i]>='A' && userGuess[wordPos][i]<='Z')) {
		length++;
		}
	}
	
	if (length!=5){
		flag=1;
	}
	
	else{
		flag=0;
	}
	return flag;	
}
		
void printTryAgain(int tooLong, int notLetters){
	if (notLetters==1){
		printf("Your guess must contain only letters.");
		printf("\nPlease try again: ");
	}
	if (tooLong==1 && notLetters==0){
		printf("Your guess must be 5 letters long.");
		printf("\nPlease try again: ");
	}
}

void uppercaseToLowercase(int rows, int columns, int wordPos, char userGuess[][COLUMNS]){

  		for(int j = 0; userGuess[wordPos][j] != '\0'; j++){
			if (userGuess[wordPos][j]>='A' && userGuess[wordPos][j]<='Z'){
				userGuess[wordPos][j]+=32;
			}
		}
}

int exactMatch(int rows, int columns, int wordPos, char userGuess[][COLUMNS], char correctWordStr[CAP]){
	int matchCount=0, flag=0;
  		for(int j=0; correctWordStr[j]!='\0'; j++){
			if (userGuess[wordPos][j]==correctWordStr[j]){
				userGuess[wordPos][j]-=32;
				matchCount++;
			}
		}
		if (matchCount==5){
			flag=1;
		}
		else{
			flag=0;
		}
	return flag;
}
//check ascii table and 2d array display
void rightPosition(int rows, int columns, int wordPos, char userGuess[][COLUMNS], char correctWordStr[CAP], char hintsStr[][COLUMNS]){

	for (int i=0; i<5; i++){
		hintsStr[wordPos][i]=' ';
	}
	hintsStr[wordPos][5]='\0';
 	
  	for(int j = 0; correctWordStr[j]!='\0'; j++){
  		for(int k=0; correctWordStr[k]!='\0'; k++){
		if ((userGuess[wordPos][j]==correctWordStr[k]) && (userGuess[wordPos][j]>='a' && userGuess[wordPos][j]<='z')){
			hintsStr[wordPos][j]='^';
			}
		}
	}return;	
} 



//display results function (you lost/won)
void gameResults(int guessCheck, int wordPos, char correctWordStr[]){
	printf("\n%27s", correctWordStr);
	if (guessCheck==1){
		switch (wordPos){
			case 1:
				printf("        You won in 1 guess!\n");
				printf("                 GOATED!\n");			
				break;
			case 2:
			case 3:	
				printf("        You won in %d guesses!\n", wordPos);
				printf("		Amazing!\n");
				break;
			case 4:
			case 5:
				printf("        You won in %d guesses!\n", wordPos);
				printf("		Nice!\n");
				break;
			case 6:
				printf("        You won in 6 guesses!\n");
				break;
		}
	}
	else {
		printf("You lost, better luck next time!\n");
	}
	return;
}
			
