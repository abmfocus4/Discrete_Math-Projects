#include <iostream>
#include <limits.h> 
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <utility>

using namespace std;

//used to make matrices
int **relation_matrix(int height, int width)
{
	int **matrix = 0;
	matrix = new int*[height];
	
	for(int h=0; h< height; h++)
	{
		matrix[h] = new int[width];
		
		for(int w=0; w< width;w++)
		{
			matrix[h][w] = 0;
		}
	}
	
	return matrix;
}

//used for random line iterations(also clears the buffer)
string buffer_reset(int line_num, string input)
{
	cin.clear();
	for(int i=1; i<line_num-1;i++)
	{
		getline(cin,input);
	}
	
	return input;
}

/////////////////////////
int main(int argc, char* argv[])
{

	int num_users = 0;
	int num_content = 0;
	
	string input; //used for inputs form the file
//error checking for users heading
getline(cin, input);
	if (input != "#U")
	cerr << "Invalid file format - cannot find '#U'!!!" << endl;
	
//inputing number of users
	getline(cin,input);
	stringstream(input) >> num_users;
	
//Error checking for contents heading
getline(cin, input);
	if (input != "#C")
	cerr << "Invalid file format - cannot find '#C'!!!" << endl;

//inputting num_contents
	getline(cin,input);
	stringstream(input) >> num_content;

//creating relations skeleton
	int **ownership_matrix = relation_matrix(num_users, num_content);
	
	int **frienship_matrix = relation_matrix(num_users, num_users);
	
	int **likes_matrix = relation_matrix(num_users, num_content);
	
	int **similar_users_matrix = relation_matrix(num_users, num_users);
	
	int **dissimilar_users_matrix = relation_matrix(num_users, num_users);
	
//////////////////////////////////////////////////////////
	
//Error checking for Friends heading
getline(cin, input);
	if ( input != "#F")
	cerr << "Invalid file format - cannot find '#F'!!!" << endl;

//counting pairs of friends
int friends_counter = 0;
int friends_initial[50];

for(int i=0; (i<50 && input != "#W"); i++)
{
	cin >> input;
	stringstream(input) >> friends_initial[i];
	
	friends_counter++;
}
friends_counter-=1; //removind the #W condition

//readjusting the size of the friends array
int friends[friends_counter];

for(int i=0; i<friends_counter;i++)
	friends[i] = friends_initial[i];

////////////////////////////////////////////////////

//Error checking for Owns heading
	if ( input != "#W")
	cerr << "Invalid file format - cannot find '#W'!!!" << endl;

//counting pairs
int owns_counter = 0;
int owns_initial[50];

for(int i=0; (i<50 && input != "#L"); i++)
{
	cin >> input;
	stringstream(input) >> owns_initial[i];
	
	owns_counter++;
}
owns_counter-=1; //removind the #L condition

//readjusting the size of the owns array
int owns[owns_counter];

for(int i=0; i<owns_counter;i++)
	owns[i] = owns_initial[i];

///////////////////////////////////////////////////////////

//cout << input << endl;
//Error checking for Likes heading
	if ( input != "#L")
	cerr << "Invalid file format - cannot find '#L'!!!" << endl;

//counting pairs of likes
int likes_counter = 0;
int likes_initial[50];

for(int i=0; (i<50); i++)
{
	cin >> input;

	stringstream(input) >> likes_initial[i];
	likes_counter++;
}
likes_counter-=1; //reached end of file


//readjusting the size of the likes array
int likes[likes_counter];

for(int i=0; i<likes_counter;i++)
	likes[i] = likes_initial[i];

////////////////////////////////////////////

//filling in the initial values for friendship matrix
int i=0;
int j=1;

//taking care of symettric
while(friends_counter != 0)
{
frienship_matrix[friends[i]-1][friends[j]-1] = 1;
frienship_matrix[friends[j]-1][friends[i]-1] = 1;
i+=2;
j+=2;
friends_counter-=2;
}

//taking care of reflexive
int reflex = num_users;
while( reflex != 0)
{
	frienship_matrix[reflex-1][reflex-1] = 1;
	reflex--;
}


///////////////////////////////

//filling in the initial values for ownership_matrix
int a=0;
int b=1;

while(owns_counter != 0)
{
ownership_matrix[owns[a]-1][owns[b]-1] = 1;

a+=2;
b+=2;

owns_counter-=2;
}

////////////////////////////////////////


//filling in the initial values for likes matrix
int c=0;
int d=1;

while((likes_counter != 0) && ((likes[c]-1)<=num_users) && ((likes[d]-1)<=num_content) )
{
likes_matrix[likes[c]-1][likes[d]-1] = 1;

c+=2;
d+=2;

likes_counter-=2;
}

//if friends then they like all their stuff

	for(int p=0; p<num_users; p++)
	{
		for(int q=0; q<num_users;q++)
		{
			for(int r=0; r<num_content;r++)
			{
				if((frienship_matrix[p][q] == 1) && (ownership_matrix[q][r] == 1))
				{
					likes_matrix[p][r] = 1;
				
				}
			}
		}
	}
		
//similarity relationship building

	for(int m=0; m<num_users; m++)
	{
		for(int l=0; l<num_users;l++)
		{
			for(int o=0; o<num_content;o++)
			{
				if( (likes_matrix[m][o] ==1) && (ownership_matrix[l][o] == 1) )
				{
					similar_users_matrix[m][l] = 1;
					similar_users_matrix[l][m] = 1;
				}
			}
		}
	}
//taking care of reflexive
int sim = num_users;
while( sim != 0)
{
	similar_users_matrix[sim-1][sim-1] = 1;
	sim--;
}

//dissimilar relation_matrix

	for(int m=0; m<num_users; m++)
	{
		for(int l=0; l<num_users;l++)
		{
				if( similar_users_matrix[m][l] != 1 )
				{
					dissimilar_users_matrix[m][l] = 1;
					dissimilar_users_matrix[l][m] = 1;
				}

		}
	}
	
	for(int m=0; m<num_users; m++)
	{
		for(int l=0; l<num_users;l++)
		{
				if( (dissimilar_users_matrix[m][l] == 1) && similar_users_matrix[m][l] == 1  )
				{
					cerr << "error has ocurred while analysings dissimilar users" << endl;
				}

		}
	}
	
///////////////////////////////////////
//////////////////////////////////////

cout << "friendship" << endl;	
for(int i=0; i<num_users; i++)
	{
		for(int j=0; j<num_users;j++)
		{
			cout << frienship_matrix[i][j] << " ";
		}
		
		cout << endl;
	}
 ///////////////////////////
cout << "owner" << endl;

 for(int i=0; i<num_users; i++)
	{
		for(int j=0; j<num_content;j++)
		{
			cout << ownership_matrix[i][j] << " ";
		}
		
		cout << endl;
	}

///////////////////////////////

cout << "likes" << endl;

for(int i=0; i<num_users; i++)
	{
		for(int j=0; j<num_content;j++)
		{
			cout << likes_matrix[i][j] << " ";
		}
		
		cout << endl;
	}
	
////////////////////////////
cout << "similar" << endl;
for(int i=0; i<num_users; i++)
	{
		for(int j=0; j<num_users;j++)
		{
			cout << similar_users_matrix[i][j] << " ";
		}
		
		cout << endl;
	}
	
////////////////////////////
cout << "dissimilar" << endl;
for(int i=0; i<num_users; i++)
	{
		for(int j=0; j<num_users;j++)
		{
			cout << dissimilar_users_matrix[i][j] << " ";
		}
		
		cout << endl;
	}


	return 0;
}






















