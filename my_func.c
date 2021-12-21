#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

	for(i=0; text[i]!='\0'; i++){
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

void atbash(){
    // lines 115-135 are to translate the word to Atbash
    char atbashWord[WORD]= {'\0'};
    char atbashWordReversed[WORD]={'\0'};
    char tempC;
    int i=0, j=0, k=strlen(word)-1, temp=0;
        //translate word to atbash
    while(word[i]!='\0'){
		if(word[i]>=65 && word[i]<=90){// upercase
            temp = 155-word[i];
            tempC=(char)temp;
            atbashWord[j++]= tempC;
            atbashWordReversed[k--]=tempC;
            
        }
		else if(word[i]>=97 && word[i]<=122){// lower case
            temp = 219-word[i];
            tempC=(char)temp;
            atbashWord[j++]= tempC;
            atbashWordReversed[k--]=tempC;
            
        }else{
            atbashWord[j++]=word[i];
            atbashWordReversed[k--]=word[i];
        }
        i++;
	}
    

    //from here we will look for the occurence of the atbash word in the text

    i=0, j=0, k=0;
    int AC=0, ARC=0, tempWL=0, tempIndex=0, ans=0;

    char tempWord[WORD]={'\0'};
    char answer[TXT]={'\0'};


    while(text[i]!='\0'){

        if(text[i]== atbashWord[0] || text[i]== atbashWordReversed[0]){
            //while for the normal atbash
            j=i;
            while(text[j]!='\0'){
                if(text[j]==' '){
                    tempWord[tempIndex]=' ';
                    j++;
                    tempIndex++;
                }
                else if((text[j]==atbashWord[AC]) && (tempWL<strlen(atbashWord))){
                    tempWord[tempIndex]=text[j];
                    tempIndex++;
                    tempWL++;
                    AC++;
                    j++;
                    //insert answer
                    if(tempWL==strlen(atbashWord)){
                        int n=0;
                        while(tempWord[n]!='\0'){
                            answer[ans++]=tempWord[n];
                            tempWord[n++]='\0';
                        }
                        answer[ans++]='~';
                        tempIndex=0;
                        tempWL=0;
                        AC=0;
                        j=0;
                        break;
                        // reset all values and continue to next
                    }
                }
                else{
                    //not a correct symbol/letter we need to reset and try Reversed Version
                    for(int n=0; tempWord[n]!='\0'; n++){
                        tempWord[n]='\0';
                    }
                    tempIndex=0;
                    tempWL=0;
                    AC=0;
                    j=0;
                    break;
                }
            }

        }
        if(text[i]== atbashWord[0] || text[i]== atbashWordReversed[0]){

            //checking reversed version
            j=i;
            while(text[j]!='\0'){
                if(text[j]==' '){
                    tempWord[tempIndex]=' ';
                    j++;
                    tempIndex++;
                }
                else if((text[j]==atbashWordReversed[ARC]) && (tempWL<strlen(atbashWordReversed))){
                    tempWord[tempIndex]=text[j];
                    tempIndex++;
                    tempWL++;
                    ARC++;
                    j++;
                    //insert answer
                    if(tempWL==strlen(atbashWordReversed)){
                        int n=0;
                        while(tempWord[n]!='\0'){
                            answer[ans++]=tempWord[n];
                            tempWord[n++]='\0';
                        }
                        answer[ans++]='~';
                        tempIndex=0;
                        tempWL=0;
                        AC=0;
                        j=0;
                        break;
                        // reset all values and continue to next
                    }
                }
                else{
                    //not a correct symbol/letter we need to reset and try Reversed Version
                    for(int n=0; tempWord[n]!='\0'; n++){
                        tempWord[n]='\0';
                    }
                    tempIndex=0;
                    tempWL=0;
                    AC=0;
                    j=0;
                    break;
                }
            }

        }
        i++;
    }
    answer[ans-1]='\0';
    printf("Atbash Sequences: ");
    printf("%s\n", answer);
    
}

void anagram(){
    char tempWord[TXT] ={'\0'}, tempWordCopy[TXT]={'\0'}, sorted_word[WORD]={'\0'}, answer[TXT]={'\0'};

    for(int i=0; word[i]!= '\0'; i++){
        sorted_word[i]=word[i];
    }

    sort(sorted_word);

    int wordC=0, index=0, j=0, i=0, ans=0;

    while(text[i]!='\0'){
        while(text[j]!='\0'){

            if(text[j]==' '){
                tempWord[index]=' ';
                index++;
                j++;
            }
            else if(wordC<strlen(word)){
                tempWord[index]=text[j];
                wordC+=1;
                index+=1;
                j++;

                if(wordC==strlen(word)){

                    int boolean1=1, boolean2=1;
                    boolean2= isMinimal(tempWord);
                    int n=0, ind=0;
                    while(tempWord[n]!='\0'){
                        if(tempWord[n]!=' '){
                            tempWordCopy[ind++]=tempWord[n];
                        }
                        n++;
                    }

                    sort(tempWordCopy);
                    for(n=0; n<strlen(word); n++){
                            if(sorted_word[n]!=tempWordCopy[n]){
                                boolean1=0;
                                break;
                            }
                        }

                    if((boolean1==1) && (boolean2==1)){ //insert to answer
                        for(n=0; tempWord[n]!='\0'; n++){
                            answer[ans++] = tempWord[n];
                        }
                        answer[ans++]='~';
                    }

                    wordC=0;
                    index=0;
                    for(int k=0; k<TXT; k++){
                        tempWord[k]='\0';
                        tempWordCopy[k]='\0';
                    }
                    i++;
                    j=i;
                }
            }
            
        }
        i++;
    }
    answer[ans-1]='\0';
    printf("Anagram Sequences: ");
	printf("%s", answer);
}