#include <iostream>
#include <vector> 
#include <algorithm>
#include <iterator>
#include <ctime>

using namespace std;

class Card {
	int value;

public:

	Card *next; //shouldnt be a pointer to a card but an int
	Card(){}
	Card(int val) :value(val){}
	Card(const Card &c) :value(c.value), next(c.next){}
	void show();
	bool isKing() const;
	bool isAce() const;


};
bool Card::isKing() const {//celochislennoe delenie ispolzovat'
	//if (value == 13 || value == 26 || value == 39 || value == 52)

	return (value % 13 == 0) ? true : false;
	//return false;
}
bool Card::isAce() const {
	//if (value == 1 || value == 14 || value == 27 || value == 40)
	return (value % 13 == 1) ? true : false;
	//return false;
}

void Card::show() //ego//optimize till 13 variants
{
	int v = value % 13;
	if (v > 1 && v < 11)
		cout << v;
	else
	{
		switch (v)
		{
		case 1:
			cout << 'A'; break;
		case 11:
			cout << 'J'; break;
		case 12:
			cout << 'Q'; break;
		case 0:
			cout << 'K'; break;
		}
	}
	v = value / 13 + 3;
	cout << static_cast<char>(v);
}
class List {//sleduyshaya eto prosto por'adkovyj nomer elementa, obrashenije k elementam raznoje na odnoj strukture
	Card *head, *tail;
	int size;
public:
	List() :head(NULL), tail(NULL), size(0) {};
	void push(int value);
	void push(Card& card);
	void pop();
	bool isEmpty()const{ return (size == 0); }
	bool isFull()const{ return (size == 104); }
	Card first();
	void takeTable(List& list);
	int Size(){ return size; }

};

Card List::first(){
	return *head;
}

void List::push(int value){

	Card *newCard = new Card(value);
	newCard->next = head;


	if (!isEmpty())
	{
		tail->next = newCard;
		tail = newCard;
	}
	else head = tail = newCard;
	size++;
}
void List::push(Card& card){

	Card *newCard = new Card(card);
	card.next = head;

	if (!isEmpty())
	{

		tail->next = newCard;
		tail = newCard;
	}
	else head = tail = newCard;
	size++;
}
void List::pop(){
	if (!isEmpty()){
		if (head == head->next)
		{
			head = NULL;
		}
		else {
			Card *temp = head;
			head = head->next;
		}
		size--;
	}
}

void List::takeTable(List& list)
{
	while (!list.isEmpty())
	{

		push(list.first()); //.value);
		list.pop();
	}
}
class Player {
public:
	List cards;
	Player(){}

	Card& pickCard()
	{
		Card& c = cards.first();
		c.next = NULL;
		cards.pop();
		return c;
	}
	void takeTable(List& list)
	{
		cards.takeTable(list);
	}
};

class Deck {
private:
	int deck[52];//usual int array //ego
public:
	Deck(){
		for (int i = 0; i < 52; i++)
			deck[i] = i;
	}
	Deck& shuffle();
	//List& dealCards();
	void dealCards(Player& player);
	void show(int i);
	void print();
};

Deck& Deck::shuffle(){
	srand(unsigned(time(0)));
	for (int i = 0; i<52; i++)
	{
		int r = i + (rand() % (52 - i));
		swap(deck[i], deck[r]);
	}
	return *this;
}
//List& Deck::dealCards()
//{
//	List l = List();
//	for (int i = 0; i<52; i++)
//	{
//		l.push(deck[i]);
//	}
//	return l;
//}
void Deck::show(int num)
{
	int v = num % 13;
	if (v > 1 && v < 11)
		cout << v;
	else
	{
		switch (v)
		{
		case 1:
			cout << 'A'; break;
		case 11:
			cout << 'J'; break;
		case 12:
			cout << 'Q'; break;
		case 0:
			cout << 'K'; break;
		}
	}
	v = num / 13 + 3;
	cout << static_cast<char>(v);
}
void Deck::print() {
	for (int i = 0; i<52; i++)
	{
		show(deck[i]);
		cout << "  ";
	}
	cout << endl;
}
void Deck::dealCards(Player& p)//parameters - players which cards are delivered to
{
	p.cards = List();
	for (int i = 0; i<52; i++)
	{
		p.cards.push(deck[i]);
	}
}



int main()
{
	Deck deck = Deck();
	deck.print();
	Player player1 = Player();
	deck.shuffle();
	cout << "Shuffled:" << endl;
	deck.print();
	deck.dealCards(player1);
	//	system("pause");
	Player player2 = Player();
	deck.shuffle();
	cout << "Shuffled:" << endl;
	deck.print();
	deck.dealCards(player2);
	Card card1, card2;
	List table = List();
	//	system("pause");
	int i = 0;
	while (true)
	{
		cout << "Round " << i++ << endl;
		cout << "Table size: " << table.Size() << endl;
		cout << "Player1 size: " << player1.cards.Size() << endl;
		cout << "Player2 size: " << player2.cards.Size() << endl;

		if (player1.cards.isEmpty())
		{
			cout << "Player2 has winned!!! Player1 is empty";
			break;
		}
		if (player2.cards.isFull())
		{
			cout << "Player2 has winned!!! Full";
			break;
		}

		if (player2.cards.isEmpty())
		{
			cout << "Player1 has winned!!! Player2 is empty";
			break;
		}
		if (player1.cards.isFull())
		{
			cout << "Player1 has winned!!! Full";
			break;
		}
		card1 = player1.pickCard();
		table.push(card1);
		cout << "Player1: ";
		card1.show();
		cout << endl;
		if (card1.isKing()) //is KING
		{
			card2 = player2.pickCard();
			cout << "Player2: ";
			card2.show();
			table.push(card2);
			if (player2.cards.isEmpty()) continue;
			card2 = player2.pickCard();
			card2.show();
			cout << endl;
			table.push(card2);
			player1.takeTable(table);
			continue;
		}
		if (card1.isAce()) //is ACE
		{
			card2 = player2.pickCard();
			cout << "Player2: ";
			card2.show();
			table.push(card2);
			if (player2.cards.isEmpty()) continue;
			card2 = player2.pickCard();
			card2.show();
			table.push(card2);
			if (player2.cards.isEmpty()) continue;
			card2 = player2.pickCard();
			card2.show();
			cout << endl;
			table.push(card2);
			player1.takeTable(table);
			continue;
		}
		card2 = player2.pickCard();
		cout << "Player2: ";
		card2.show();
		cout << endl;
		table.push(card2);
		if (card2.isKing()) //is KING
		{
			if (player1.cards.isEmpty()) continue;
			card1 = player1.pickCard();
			cout << "Player1: ";
			card1.show();
			cout << endl;
			table.push(card1);
			player2.takeTable(table);
			continue;
		}
		if (card2.isAce()) //is ACE
		{
			if (player1.cards.isEmpty()) continue;
			card1 = player1.pickCard();
			cout << "Player1: ";
			card1.show();
			table.push(card1);
			if (player1.cards.isEmpty()) continue;
			card1 = player1.pickCard();
			card1.show();
			cout << endl;
			table.push(card1);
			player2.takeTable(table);
			continue;
		}

	}
	cout << endl;
	system("pause");
	return 0;
}


