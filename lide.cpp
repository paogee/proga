#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

class Field;
class Cell
{
	
	
	public:
	
		virtual Cell* nextGeneration(Field * const parent) = 0; // generate cells with the starting field
		virtual void printCell()const = 0; 
		virtual int isAlive()const = 0; 
	protected:
		int neighboursAlive (Field * f) const; // cout alive neigh
		int x, y; // coord
		
		
};		
		
 
 class cellAlive:public Cell
 {
 	public:
	 	cellAlive(int a, int b){x=a; y=b;} //alive cell creation
	 	void printCell()const{cout<<"X";} 
	 	int isAlive()const {return 1;} // check if alive
 		Cell* nextGeneration(Field * const parent); //starting field
 };
 
 //sme things but for dead cell below
 
 class cellDead:public Cell
 {
 	public:
	 	cellDead(int a, int b){x=a; y=b;} 
	 	void printCell()const {cout<<"-";} 
	 	int isAlive()const {return 0;}
		Cell* nextGeneration(Field * const parent); 
 	
 };
 
 

 
 
 class Field
 {
 	public:
 		Field(); //default field
 		Cell* elem(int x, int y){return f[x][y];} // return element of the field, i and j
 		void generateField(Field *endField); //?whole field generation
 		void printField() const;
		void printFieldfull() const; 
 		void fillField(int p); //fill in the field with 0
 		void deleteField(); //refreshing the field
 		~Field();
 	private:
 		static int const len = 23; //arr size
 		Cell *f[len][len];
 };
 
  
Cell* cellAlive:: nextGeneration (Field * const startingField)// generating the cells start and end field
 {
 	int n = this->neighboursAlive(startingField); // neigh
 	if( n == 2 || n == 3)  // rule checker
 	{ 
 		return new cellAlive(x,y); 
 	}
 	else
 	{
 		return new cellDead(x,y); 
 	}

 }
 
 
 Cell* cellDead :: nextGeneration (Field * const startingField)// only end firld
 {
 	int n = this->neighboursAlive(startingField); // neugh
 	             
 	if(n == 3)  
 	{
 		
		return new cellAlive(x,y); 
 	}
 	else
 	{
 		return new cellDead(x,y); 
 	}
 }
 
 int Cell :: neighboursAlive (Field * f) const// search neigh
 {
 	int sum = 0, i, j;
	
 	for( i = x-1; i < x+2; i++)
 	{
 		for( j = y-1; j < y+2; j++)
 		{
 			sum +=   f->elem(i,j)->isAlive();
 		}
 	}
	return sum - f->elem(x,y)->isAlive();
 }
 
 
 
 
 void Field :: fillField(int p)
 {
 	int Lenght = len-1;
 	srand(time(NULL));
 	if (p == 0) 
 	{
	 	for (int i = 0; i < len; i++ )
		{
			for (int j = 0; j < len; j++ )
			{
				f[i][j] = new cellDead(i,j); 
			}
		}
	}
	else //randomized fill in
	{
		for (int i = 1; i < Lenght; i++ )
		{
			for (int j = 1; j < Lenght; j++ )
			{
		 		if(rand()%2)
		 		{
		 			f[i][j] = new cellAlive(i,j); 
		 		}
		 		else
		 		{
		 			f[i][j] = new cellDead(i,j);
		 		}
			}
		}
	}
 }
 Field :: Field()
 {
 	int Lenght = len-1;
 	for (int i = 0; i <Lenght; i++ )//fill in borders 
 	{
 		f[0][i] = new cellDead(0,i); //up
		f[i][Lenght] = new cellDead(i,Lenght); //right
		f[Lenght][Lenght-i] = new cellDead(Lenght,Lenght-i); //low
		f[Lenght-i][0] = new cellDead(Lenght-i,0);//left
	}
}

 //same thing DUH
 Field:: ~Field()
 {
 	int Lenght = len-1;
 	for (int i = 0; i <Lenght; i++ )
 	{
 		delete f[0][i]; 
		delete f[i][Lenght]; 
		delete f[Lenght][Lenght-i]; 
		delete f[Lenght-i][0];
	}
	 
}
void Field :: deleteField()
{
	int Lenght = len-1;
 	for (int i = 1; i < Lenght; i++ )
	{
		for (int j = 1; j < Lenght; j++ )
		{
	 		delete f[i][j]; 
		}
	}
 }
 
 void Field::printField() const 
 {
 	int Lenght = len-1;
 	for (int i = 1; i < Lenght; i++ )
	{
		for (int j = 1; j < Lenght; j++ )
		{
			f[i][j]->printCell();
		}
		cout<<endl;
	}
 }
 
 void Field::printFieldfull() const //borders too
 {
 	for (int i = 0; i < len; i++ )
	{
		for (int j = 0; j < len; j++ )
		{
			f[i][j]->printCell();
		}
		cout<<endl;
	}
 }
 void Field::generateField(Field *endField)
 {
 	int Lenght = len-1;
 	for (int i = 1; i < Lenght; i++ )
	{
		for (int j = 1; j < Lenght; j++ )
		{
	 		endField->f[i][j] = f[i][j] -> nextGeneration(this);
		}
	}
 }
 
 int main()
 {

 	Field f1, f2; //create 2 fields
 	cout<<"______________________________WELCOME TO THE GAME OF LIFE:______________________________"<<endl;
 	cout<<endl;
 	f1.fillField(1);//our rand starting field
 	cout<<"______________________________Our starting field looks like:______________________________"<<endl;
 	f1.printField(); 
 	cout<<endl;
 	cout<<endl;
 	f1.generateField(&f2); //our field after the game starts
 	cout<<"______________________________Oh look 1 generation already passed:______________________________"<<endl;
 	f2.printField();
 	int iter;//iterations
 	cout<<endl;
 	cout<<"______________________________How many MORE 	GENERATIONS do YOU want to SEE:______________________________"<<endl;
 	cin>>iter;
 	cout<<endl;
 	cout<<endl;
 	
 	for (int i = 0 ;i < iter; i++)
 	{
 		if (i%2 == 1) // ????
 		{
 			f2.deleteField();
 			f1.generateField(&f2); 
 			f2.printField();
 			cout<<endl;
 		}
 		else
 		{
 			f1.deleteField();
 			f2.generateField(&f1);
 			f1.printField();
 			cout<<endl;
 		}
 		cout<<endl;
	}
	cout<<"______________________________THE END______________________________"<<endl;
 	f1.deleteField();
 	f2.deleteField();
 }

