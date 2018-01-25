#ifndef DECK_H
#define DECK_H

#define DECKSIZE 10

typedef struct deck_t
{
	int card[DECKSIZE];	//number of cards used
	int dealt;
}deck_type;

void shuffle(deck_type *pdeck);

#endif