#include <iostream>
#include <limits.h> 
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>

using namespace std;

int main() {

	srand( (unsigned int)time(NULL));
	
int roll_ten[6] = {0};
int roll_k[6] = {0};
int roll_hund_k[6] = {0};
int roll_hund[6] = {0};	
int roll_snake[11] = {0};
int equals = 0;
int num_high_hund = 0;
int num_low_hund = 0;

int loop_result = 0;

	for(int i=1; i<=10; i++)
	{ 
		loop_result = 1 + rand() / (RAND_MAX / 6 + 1);
		
		roll_ten[loop_result-1]++;
		
		loop_result = 0;
		
	}
	
loop_result = 0;

//repeating the process of rolling a die hundred times for 10000 times
for(int i=0; i<=10000; i++)
{
	loop_result = 0;
	for(int i=0; i<=5; i++)
		roll_hund[i] = 0;
	
	num_high_hund = 0;
	num_low_hund = 0;
	
	//rolling a die 100 times
	for(int i=1; i<=100; i++)
		{ 
			loop_result = 1 + rand() / (RAND_MAX / 6 + 1);
		
			roll_hund[loop_result-1]++;
		
			loop_result = 0;
		}
		
	num_high_hund = roll_hund[0] + roll_hund[1] + roll_hund[2];
	
	num_low_hund = roll_hund[3] + roll_hund[4] + roll_hund[5];
	
	if (num_high_hund == num_low_hund)
		equals++;
}
	

	
loop_result = 0;
	
	for(int i=1; i<=1000; i++)
	{ 
		loop_result = 1 + rand() / (RAND_MAX / 6 + 1);
		
		roll_k[loop_result-1]++;
		
		loop_result = 0;
	}

loop_result = 0;
	
	for(int i=1; i<=100000; i++)
	{ 
		loop_result = 1 + rand() / (RAND_MAX / 6 + 1);
		
		roll_hund_k[loop_result-1]++;
		
		loop_result = 0;
	}	
	
loop_result = 0;

	for(int i=0; i<=10000; i++)
	{
		loop_result = 2 + rand() / (RAND_MAX / 11 + 1);
		
		roll_snake[loop_result-1]++;
		
		loop_result=0;
	}

cout << "Question 1:" << endl;

cout<< "This is the result of the die rolled 10 times." << endl;
for(int i = 1; i<=6; i++)
{
	cout << i << ": "<< (float)(roll_ten[i-1])/10 << endl; 	
}


cout<< "This is the result of the die rolled 1000 times." << endl;
for(int i = 1; i<=6; i++)
{
	cout << i << ": "<< (float)(roll_k[i-1])/1000 << endl; 	
}


cout<< "This is the result of the die rolled 100000 times." << endl;
for(int i = 1; i<=6; i++)
{
	cout << i << ": "<< (float)(roll_hund_k[i-1]) /100000 << endl; 	
}

cout << endl;

cout << "Question 2:" << endl;
cout <<"The fraction of times the number of high rolls is equal to the number of low rolls is " << (float)equals/10000 <<"."<<endl;

cout <<endl;

cout<<"Question 3:" <<endl;
for(int i = 2; i<=12; i++)
{
	cout << i << ": "<< (float)(roll_snake[i-2])/10000 << endl; 	
}


return 0;

}