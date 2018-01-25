#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"deck.h"

static time_t seed=0;

void shuffle(deck_type *pdeck)
{
	int drawn[DECKSIZE] = {0};	//keep track of what numbers have been used
	int i;
	//one time initialiation of rand
	if (seed == 0)
	{
		seed = time(NULL);
		srand(seed);
	}
	
	for (i=0; i<DECKSIZE; i++)
	{
		int value = -1;
		do
		{
			value = rand() % DECKSIZE;
		}
		while(drawn[value] != 0);
		drawn[value] = 1;	//mark value as used
		//debug statement
		printf("number %i = %i \n", i, value);
		pdeck->card[i] = value;
	}
	pdeck->dealt = 0;
	return;
}