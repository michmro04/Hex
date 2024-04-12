//HEX

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Node {
	int x;
	int y;
	Node* next;
	Node(int x, int y) :x(x), y(y), next(nullptr){}
};

struct List {
	Node* head;

	List(): head(nullptr){}

	bool isEmpty() const {
		return head == nullptr;
	}

	Node* front() {
		return head;
	}

	void addFront(int x, int y) {
		Node* newNode = new Node(x, y);
		newNode->next = head;
		head = newNode;
	}

	void removeFront() {
		if (!isEmpty()) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	~List() {
		while (!isEmpty())
			removeFront();
	}
};






struct Board {
	char** boardData;
	int boardSize;

	//constructor
	explicit Board(int size) : boardSize(size) {
		boardData = new char* [boardSize];
		for (int i = 0; i < boardSize; i++) {
			boardData[i] = new char[boardSize];
		}
	}

	//copy constructor
	Board(const Board& other) : boardSize(other.boardSize) {
		boardData = new char* [boardSize];
		for (int i = 0; i < boardSize; i++) {
			boardData[i] = new char[boardSize];
			for (int j = 0; j < boardSize; j++)
				boardData[j][i] = other.boardData[j][i];
		}
	}

	Board& operator=(const Board& other) {
		if (this != &other) {
			for (int i = 0; i < boardSize; i++)
				delete[] boardData[i];

			delete[] boardData;

			boardSize = other.boardSize;
			boardData = new char* [boardSize];
			for (int i = 0; i < boardSize; i++) {
				boardData[i] = new char[boardSize];
				for (int j = 0; j < boardSize; j++)
					boardData[i][j] = other.boardData[i][j];
			}
		}
		return *this;
	}

	void print() const {
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				cout << boardData[j][i];
			}
			cout << endl;
		}
	}

	~Board() {
		for (int i = 0; i < boardSize; i++) {
			delete[] boardData[i];
		}
		delete[] boardData;
	}
};


void pawns_number(Board* board) {	//info about quantity of all pawns in board [0;121]
	int sum = 0;
	//go throught all fields and increment 'sum' when I find char r or b

	for (int i = 0; i < board->boardSize; i++) {
		for (int ii = 0; ii < board->boardSize; ii++) {
			if (board->boardData[ii][i] == 'r' || board->boardData[ii][i] == 'b')
				sum++;
		}
	}
	if(sum>=0 && sum<=121)
		cout << sum;
}
void is_board_correct(Board* board) {	//whether the number of red pawns is appropriate in relation to the number of blue pawns
	int red = 0;
	int blue = 0;
	//count red and blue pawns by going throught all fields, and then check the condition
	for (int i = 0; i < board->boardSize; i++) {
		for (int ii = 0; ii < board->boardSize; ii++) {
			if (board->boardData[ii][i] == 'r')
				red++;
			else if (board->boardData[ii][i] == 'b')
				blue++;
		}
	}

	if (red == blue || (red - 1) == blue) cout << "YES";
	else cout << "NO";
}



#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

bool traverse_the_board(Board* board, int row, int col, int direction, bool* whoWin) {
	if (row >= 0 && row < board->boardSize && col >= 0 && col < board->boardSize) {	//warunek wejscia w funkcje


		if (direction = RIGHT) {
			//tutaj myœlê nad wywo³aniem jeszcze raz funkcji rekurencyjnie ze zmienionymi koordynatami row i col je¿eli znajdê 'r' i gdy dojdê do krawêdzi to zmieniæ whoWin na true
		}
		if (direction = LEFT) {

		}
		if (direction = UP) {

		}
		if (direction = DOWN) {

		}


	}

	return false;
}

void is_game_over(Board* board) {

	bool redWins = false;
	bool blueWins = false;

	//przechodzenie przez tablicê dla red
	for (int i = 0; i < board->boardSize; i++) {
			//lawa czesc:
		if (board->boardData[i][0] == 'r') {
			for (int j = 0; j < board->boardSize; j++) {
				traverse_the_board(board, i, j, RIGHT, &redWins);
			}
		}
			//prawa czesc:
		if (board->boardData[i][board->boardSize-1] == 'r') {
			for (int j = 0; j < board->boardSize; j++) {
				traverse_the_board(board, i, j, LEFT, &redWins);
			}
		}
	}

	//przechodzenie przez tablicê dla blue
	for (int i = 0; i < board->boardSize; i++) {
		//gorna czesc:
		if (board->boardData[0][i] == 'b') {
			for (int j = 0; j < board->boardSize; j++) {
				traverse_the_board(board, j, i, DOWN, &blueWins);
			}
		}
		//dolna czesc:
		if (board->boardData[board->boardSize-1][i] == 'b') {
			for (int j = 0; j < board->boardSize; j++) {
				traverse_the_board(board, j, i, UP, &blueWins);
			}
		}
	}


	if (redWins) cout << "YES RED";
	else if (blueWins) cout << "YES BLUE";
	else cout << "NO";
}






int read_size(char* buffer) {
	int i = 0;
	while (buffer[i] == ' ') {
		i++;
	}
	return ((i-1)/3)+1;
}

const int sizeOfLine = 75;

char** read_board(int size) {
	char buffer[sizeOfLine];
	char** board = new char*[size];	//tablica wskaŸników

	for (int i = 0; i < size; i++) {
		board[i] = new char[size];	//tworzymy dla ka¿dego wskaŸnika tablicê elementów (charow), //ka¿da tablica wskaŸników ma kollumne elementow
	}

	for (int line = 1; line < size * 2; line++) {
		fgets(buffer, sizeOfLine, stdin);

		int position = 0;
		while (buffer[position] == ' ')
			position++;
		if (line == size) position = 2;
		else {
			position += 4;	//chcemy byæ na pierwszym elemencjie
		}
		int iloscPol = 0;
		if (line <= size) iloscPol = line;
		else iloscPol = 2*size-line;

		//miejsca poczatkowego wpisuywania do tablicy
		int x = 0;
		int y = 0;
		if (line <= size) {
			y = line -1;
		}
		else {
			y = size-1;
			x = line - size;
		}

		for (int tile = 0; tile < iloscPol; tile++) {	//przechodzimy po ka¿dym tailu w linii
			char who = buffer[position];

			board[x][y] = who;	//wpisanie kogosc w dane pole
			x++;			//zmiana koordynatow
			y--;
			position += 6;
		}
	}
	return board;
}

//=================================MAIN=========================================
int main() {
	char buffer[sizeOfLine];
	Board board(0);

	while(fgets(buffer, sizeOfLine, stdin)){	//sprawdzamy czy linie jest nullptr i wpisujemy ju¿ wartosci do buffera
		if (buffer[0] == ' ') {
			int size = read_size(buffer);		//rozmiar
			board = Board(size);				//konstruktor planszy
			board.boardData = read_board(size);	//dane
			fgets(buffer, sizeOfLine, stdin);	//odrzudamy '---' na koncu wejscia
			//board.print();
		}
		else {				//polecenia z uzyciem strcmp zwrocic ueage na \n w strcmp, bo mnoze jeston wrzucany prze3z fgets do bufora
			if (strcmp(buffer, "BOARD_SIZE\n") == 0) {
				cout << board.boardSize << endl;
			}
			else if (strcmp(buffer, "PAWNS_NUMBER\n") == 0) {
				pawns_number(&board);
			}
			else if (strcmp(buffer, "IS_BOARD_CORRECT\n") == 0) {
				is_board_correct(&board);
			}
			else if (strcmp(buffer, "IS_GAME_OVER\n") == 0) {
				is_game_over(&board);
			}
			else if (strcmp(buffer, "IS_BOARD_POSSIBLE\n") == 0) {

			}
			cout << endl;
		}
	} 
		
	return 0;
}











