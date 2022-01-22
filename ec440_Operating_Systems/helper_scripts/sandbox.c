#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
typedef struct jack{
	 int num;
	 char suit;
}Jack;
typedef struct jackbox{
	 Jack **pages;
}Jackbox;



int main(){
	Jackbox joke;
	//Jack *card = (Jack*)calloc(1, sizeof(Jack*));
	int i = 0; 
	char sit = 'a';
	joke.pages = (Jack**)calloc(3, sizeof(Jack**));
	Jack card;
	card.num = 0;
	card.suit = sit+card.num;
	Jack *s = &card;
	joke.pages[card.num] =s;
	Jack cards;
	cards.num = 1; 
	cards.suit = sit + cards.num;
	Jack *k = &cards;
	joke.pages[cards.num] =k;
	Jack cardss;
	cardss.num = 2; 
	cardss.suit = sit + cardss.num;
	Jack *j = &cardss;
	joke.pages[cardss.num] =j;
	
	Jack **p = joke.pages;
	for (i =0;i<3;i++){
		int n = p[i]->num; 
		int s = p[i]->suit; 
		printf("The card is %d and its a %c\n",n,s);
	}
	//free(card);
	free(joke.pages);
	return 0; 
}