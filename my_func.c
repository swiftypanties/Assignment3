#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TXT 1024
#define WORD 30

char word[WORD];
char text[TXT];



//this function calculates the gematric value of the letters in the array
int wordGemCalc(char vals[TXT]){
    int wordSum=0,temp=0;
    for(int i=0; vals[i]!= '\0'; i++){
        if(vals[i]>=65 && vals[i]<=90){
            temp = (int)(vals[i] - 65)+1;
            wordSum+=temp;
        }
        if(vals[i]>=97 && vals[i]<=122){
            temp = (int)(vals[i] - 97)+1;  
            wordSum+=temp;
        }
    }
    return wordSum;
}

void buildWord(){
	char input;
	int i=0;
	input = getchar();
	while(input != ' ' && input != '\n' && input != '\t'){
		word[i]= input;
		i++;
		input = getchar();
	}
	word[i]='\0';
    // int sum = wordGemCalc(word);
    // printf("%s", word);
    // printf("\n%d\n", sum);
}

void buildText(){
    char input;
	int i=0;
	input = getchar();
	while(input != '~'){
		text[i]= input;
		i++;
		input = getchar();
	}
	text[i]='\0';
    //printf("%s", text);
}
int isMinimal(char text[TXT]){
    if((text[0]==' ') || (text[strlen(text)-1] ==' ')){
        return 0;
    }
    return 1;
}

//swap code inspired from class
void swap(char *a, char *b ){
    char temp = *a;
    *a = *b;
    *b = temp;
}
//sort code inspired from geeksforgeeks.com
void sort(char *word){
    for (unsigned int i = 0; i < strlen(word) - 1; i++)
        for (unsigned int j = i + 1; j < strlen(word); j++)
            if (word[i] > word[j])
                swap(&word[i], &word[j]); // simply swap the characters
}

void gematria(){
	int sum=wordGemCalc(word);
    //printf("%d\n", sum);
    int tempSum=0;
    int i=0, j=0, ansCounter=0, tempCounter=0;
	char answer[TXT];

	for(i; text[i]!='\0'; i++){
	// o(n*(n-1)/2)=o(n^2) running on each letter (n-1) times to check all possibilities
		while(tempSum < sum && text[j] != '\0'){
			if(text[j]>=65 && text[j]<=90){
                tempSum += (text[j]-65)+1;
            }
			else if(text[j]>=97 && text[j]<=122){
                tempSum += (text[j]-97)+1;
            }	
			else if(tempSum == 0){break;} 
			j++;	
		}

		if(sum==tempSum){
		   //insert the answer if sum matching
			for(tempCounter=i; tempCounter<j; tempCounter++){
				answer[ansCounter]=text[tempCounter];
				ansCounter++;
			}	
			answer[ansCounter++]='~';
		}
        j=i+1;
		tempSum=0;
	}
	answer[ansCounter-1]='\0';
    printf("Gematria Sequences: ");
	printf("%s\n", answer);
}

void anagram(){
    char tempWord[TXT] ={'\0'}, tempWordCopy[TXT]={'\0'}, localWord[WORD]={'\0'}, answer[TXT]={'\0'};

    for(int i=0; word[i]!= '\0'; i++){
        localWord[i]=word[i];
    }

    sort(localWord);

    int wordC=0, index=0, j=0, ans=0;

    for(int i=0; text[i]!='\0'; i++){
        while(text[j]!='\0'){

            if(text[j]==' '){

                if(index>0){

                    tempWord[index++]=' ';
                    j++;
                }
                    // wordC=0;
                    // index=0;
                    // int n=0;
                    // while(tempWord[n]!='\0'){
                    //     tempWord[n]='\0';
                    //     n++
                    // }
                    // j=i+1;
            }
            else if(strchr(word, text[j])){
                //if the letter is in the word we insert in the temporary word
                tempWord[index]=text[j];
                wordC+=1;
                index+=1;
                if(wordC==strlen(word) && isMinimal(tempWord)){

                    for(int n=0; tempWord[n]!='\0'; n++){
                        tempWordCopy[n]=tempWord[n];
                    }

                    sort(tempWordCopy);
                    int boolean =1;

                    for(int n=0; n<strlen(word); n++){
                        if(localWord[n]!=tempWordCopy[n]){
                            int boolean=0;
                            break;
                        }
                    }

                    if(boolean==1){//insert to answer
                        for(int n=0; tempWord[n]!='\0'; n++){
                            answer[ans++] = tempWord[n];
                        }
                        answer[ans]='~';
                    }

                    wordC=0;
                    index=0;
                    int n=0;
                    while(tempWord[n]!='\0'){
                        tempWord[n]='\0';
                        n++;
                    }
                }
            }
            else{
                wordC=0;
                index=0;
                int n=0;
                while(tempWord[n]!='\0'){
                    tempWord[n]='\0';
                    n++;
                }
                i++;
                j++;
            }
            
        }
    }
    answer[ans-1]='\0';
    printf("Anagram Sequences: ");
	printf("%s\n", answer);
}