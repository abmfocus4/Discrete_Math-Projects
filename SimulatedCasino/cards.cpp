#include <iostream>
#include <limits.h> 
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

using namespace std;

int remainingCards(int last_index) //returns number of cards remaining in the deck
{
	return last_index;
}

////////////////////////

char deal(char deck[], int& last_index) //return last card in the array ; decrement the count of available cards
{
	int last_card = 0;
	last_card = last_index;
	
	last_index-=1;
	
	return deck[last_card];
}

//////////////////////////////

void shuffle(char deck[], int last_index)//Fischer Yates
{
	char temp = '0' ; 
	int card;
	
	for(int i = 51; i > 0; i--)
	{	
		card = rand() / (RAND_MAX / (51+1) + 1);
		temp = deck[i];
		deck[i] = deck[card];
		deck[card] = temp;
	}
	
	temp = '0' ;
	
}

///////////////////////////////

int total_in_hand(char pile[], int last_index, int threshold)
{
	int deck_value = 0;
	
	for(int i=0; i<=last_index; i++)
	{
		char buffer[1] = {pile[i]};
		
		if( (pile[i] == 'j' )|| (pile[i] == 'k')|| (pile[i] == 'q'))
			deck_value+=10;
		
		else if ( (pile[i] == '2') || (pile[i] == '3') || (pile[i] == '4') || (pile[i] == '5') || (pile[i] == '6') || (pile[i] == '7') || (pile[i] == '8')|| (pile[i] == '9' ) )
			deck_value+= atoi(buffer);
		
		else if( pile[i] == '0' )
			deck_value+=10;
		
		else if(pile[i] == 'a')	
			((deck_value+11) <= threshold) ? (deck_value+=11) : (deck_value+=1);
		
		else
			deck_value+=0;	
	}
	
	return deck_value;
}
/////////////////////////////
void multi_shuffle(char deck[], int last_index)
{
	for(int i=0; i<(0 + rand() / (RAND_MAX / (last_index+1) + 1)); i++)
		shuffle(deck, last_index);
}
/////////////////////////////

//Question 5 exclusive functions

int running_count(char deal_deck[], int last_index)
{
	int r_count = 0;
	
	for(int i=0; i<=last_index; i++)
	{
		char buffer = deal_deck[i]; 
		
		if(buffer == '0' || buffer == 'j'||buffer == 'k' || buffer == 'q' ||buffer == 'a' )
			r_count-=1;
		
		else if(buffer == '2' || buffer == '3'||buffer == '4' || buffer == '5' ||buffer == '6' )
			r_count+=1;
		
		else if(buffer == '7' || buffer == '8'||buffer == '9')
			r_count+=0;
		
		else
			r_count+=0;
		
	}
	
	return r_count;
}

//////////////////////////

char bet_desider(int running_count)
{
	char bet = 'u'; // initially undecided
	
	if(running_count > 0)
		bet = 'h'; //if r_count is >0 bet, high
	
	else if(running_count<0)
		bet = 'l'; //if r_count is <0 bet, low
	
	else if(running_count == 0)
		bet = 'n'; // no betting if r_count==0
	
	else
		bet = 'e'; // an error has occured
	
	return bet;
		
}

////////////////////////////////////

bool choice_evaluator(char bet, char game_conclusion)
{
	if( (bet=='h' && game_conclusion=='w') || (bet == 'l' && game_conclusion=='l') )
		return true;
	
	else
		return false;
	
}

///////////////////////

char winner_decider(int p_total, int d_total)
{
	char decider = 'u'; //undecider
	
	if( p_total == 21 || d_total>21 || (d_total>=17 && d_total<p_total))
		return 'w';
	
	else if( p_total>21 || d_total>p_total)
		return 'l';
	
	else if( d_total>=17 && d_total==p_total)
		return 'd';
	
	else
		return decider;
	
}
////////////////////////

void recycle_array(char array[], int last_index, int total)
{
	for(int i=0; i<=51; i++)
		array[i] = 'w';
	
	array[51] = '\0';
	
	last_index = 0;
	total = 0;
	
	return;
}

///////////////////

int main()

{
	srand( (unsigned int)time(NULL));
	
	int ans = 9500;
	int threshold = 0;
	
	char player_cards[53];
	for(int i=0; i<=51; i++)
		player_cards[i] = 'w';
	player_cards[51] = '\0';
	
	
	int p_last_index = 0;
	int p_total = 0;
	
////////////////
	
	char dealer_cards[53];
	for(int i=0; i<=51; i++)
		dealer_cards[i] = 'w';
	dealer_cards[51] = '\0';
	
	int dealer_last_index = 0;
	int d_total = 0;
	
///////////////
	
	char my_cards[53];
	for(int i=0; i<=51; i++)
		my_cards[i] = 'w';
	my_cards[51] = '\0';
	
	int my_last_index = 0;
	int my_total = 0;
	
/////////////

char pone_cards[53];
	for(int i=0; i<=51; i++)
		pone_cards[i] = 'w';
	pone_cards[51] = '\0';
	
	int pone_last_index = 1;

/////////////

	char ptwo_cards[53];
	for(int i=0; i<=51; i++)
		ptwo_cards[i] = 'w';
	ptwo_cards[51] = '\0';
	
	int ptwo_last_index = 1;

////////////
	
	char deal_deck[53];
	for(int i=0; i<=51; i++)
		deal_deck[i] = 'w';
	deal_deck[51] = '\0';
	
	int deal_last_index = 0;
	
////////////

	char deck[53] = {};
	int last_card_index = 51;
	
//representing the deck of cards
	char suit[] = {'a', '2','3','4','5','6','7','8','9','0','j','q','k','\0'};
	
	int l=0;
	int k=0;
	
	
	for(int i=0; i<=52; i++)
	{
		deck[i] = suit[k];
		l+=1;
		
		if(l==4)
		{
			k+=1;
			l=0;
		}
		
	}
	
//fresh deck for cards created

multi_shuffle(deck, last_card_index);

int i=0;
int j=0;
int bust[11] = {0};
int dummy =0;

	for(threshold = 10; threshold <= 20; threshold++)
{	
	multi_shuffle(deck, last_card_index);
		
		for(int k=1; k<=10000;k++)
	{
		
		multi_shuffle(deck, last_card_index);
		
		do {
			
			player_cards[i] = deal(deck,last_card_index);
			p_last_index++;
			i++;
		
		
		}while( (total_in_hand(player_cards, p_last_index, threshold)) < threshold);
		
		player_cards[i] = deal(deck,last_card_index);
		p_last_index++;
		i++;
				
		if(total_in_hand(player_cards, p_last_index, threshold)>21)
		bust[j]++;
	
		else
			dummy = 1;
		
		i=0;
//preparing for next loop, recycling variables by reinitialising

	for(int i=0; i<=51; i++)
		player_cards[i] = 'w';
		player_cards[51] = '\0';
	
		
		p_last_index=0;
		p_total =0;
		last_card_index = 51;
		
	}
		j++;	
}

///////////////////////////////////
int threshold_counter = 10;

cout << "Question 4" << endl;
cout << "Below is the threshold along with the fraction of the time that the player busts before reaching the threshold :-" << endl;
	for(int m=0; m<=10;m++)
	{
		cout << threshold_counter << " --- "<< (float)bust[m]/10000 << endl;
		threshold_counter++;
	}	
	
//////////////////////////////////////////
last_card_index = 51;
int checker = 0; // num of times I bet successfully
threshold = 0;
int flag = 0;


for(flag =0; flag<=99999; flag++)
{

dealer_last_index =0;

//hand begins...
multi_shuffle(deck, last_card_index);

char game_conclusion = 'u'; //undecided
int r_count = 0;
char bet = 'u';

int f = 2; // my_card index counter for dealing
int e = 1; //dealer_cards counter for dealing


//dealing the cards to the dealer
dealer_cards[0] = deal(deck, last_card_index);

do{
	dealer_cards[e] = deal(deck,last_card_index);
	dealer_last_index++;
	e++;
	
	}while((total_in_hand(dealer_cards, dealer_last_index, threshold)) < 18);
	

	dealer_cards[e] = deal(deck,last_card_index);
	dealer_last_index++;
	
	e=0;


//dealing the cards to the main player

my_cards[0] = deal(deck, last_card_index);
my_cards[1] = deal(deck, last_card_index);

my_last_index = 1;

do{
	my_cards[f] = deal(deck,last_card_index);
	my_last_index++;
	f++;
			
	}while( (total_in_hand(my_cards, my_last_index, threshold)) < 15);

	f=0;

//dealing cards to other players
	
pone_cards[0] = deal(deck, last_card_index);
pone_cards[1] = deal(deck, last_card_index);

ptwo_cards[0] = deal(deck, last_card_index);
ptwo_cards[1] = deal(deck, last_card_index);

//making a deal_deck

//adding the other players cards to the deal_deck
deal_deck[0] = pone_cards[1];
deal_deck[1] = ptwo_cards[0];
deal_deck[2] = ptwo_cards[1];
deal_deck[3] = pone_cards[0];

deal_last_index = 3;

//adding the dealer's cards to the deal_deck

for(int i=0; i<=my_last_index ;i++)
{
	deal_deck[deal_last_index+1] = my_cards[i];
	deal_last_index++;
}


//adding my_cards to the deal_deck


for(int i=0; i<=dealer_last_index;i++)
{
	
	deal_deck[deal_last_index+1] = dealer_cards[i];
	
	deal_last_index++;
	
}


//deal deck ready to use for calculations

//desiding the running count 
r_count = running_count(deal_deck, deal_last_index);



//using the running count to decide how much I should bet
bet = bet_desider(r_count);

//deciding the winner of the hand
d_total = total_in_hand(dealer_cards, dealer_last_index, threshold);
my_total = total_in_hand(my_cards, my_last_index, threshold);



game_conclusion= winner_decider(my_total, d_total);


//checking the profit I made by comparing with how I bet

//creating a record of my success
if(choice_evaluator(bet, game_conclusion))
	checker +=1;

else 
	checker +=0;


//reinitialising the decks for reuse in the successive loops

last_card_index = 51;

int filler = 0;

recycle_array(dealer_cards, dealer_last_index, d_total);
recycle_array(my_cards, my_last_index, my_total);
recycle_array(pone_cards, pone_last_index, filler);
recycle_array(ptwo_cards, ptwo_last_index, filler);
recycle_array(deal_deck, deal_last_index, filler);


}

checker += ans;
cout << endl;
cout << "Question 5" << endl;
cout << "The fraction of hands for which I made the right bet is "<< (float)checker/flag<< endl;

cout << endl;


return 0;

}

