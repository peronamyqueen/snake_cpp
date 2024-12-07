#include <iostream>
#include <conio.h> // Для _kbhit() и _getch()
#include <windows.h> // Для Sleep()
#include <vector>
#include <cstdlib> // Для rand() и srand()
#include <ctime> // Для srand(time(0))

using namespace std;
void drawField(int width, int height, const vector<pair<int, int>>& snake, pair<int, int > food) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
				cout << "#";
			}
			else if (x == food.first && y == food.second) {
				cout << "*";
			}
			else {
				bool isSnake = false;
				for (auto segment : snake) {
					if (segment.first == x && segment.second == y) {
						isSnake = true;
						break;
					}
				}
				cout << (isSnake ? "0" : " ");
			}
		}
		cout << endl;
	}
}
void playerInput(char& direction) {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (direction != 's') direction = 'w'; break;
		case 's':
			if (direction != 'w') direction = 's'; break;
		case 'a':
			if (direction != 'd') direction = 'a'; break;
		case 'd':
			if (direction != 'a') direction = 'd'; break;
		}
	}
}

void updateSnake(vector<pair<int, int>>& snake, char& direction, bool& grow) {
	auto head = snake.front();
	switch (direction) {
	case 'w': head.second--; break;
	case 's': head.second++; break;
	case 'a': head.first--; break;
	case 'd': head.first++; break;
	}
	snake.insert(snake.begin(), head);
	if (!grow) {
		snake.pop_back();
	}
	else {
		grow = false;
	}
}
void checkFood(vector < pair<int, int>>& snake, pair<int, int>& food, bool& grow, int width, int height) {
	if (snake.front() == food) {
		grow = true;
		food.first = 1 + rand() % (width - 2);
		food.second = 1 + rand() % (height - 2);
	}
}
bool checkCollision(vector<pair<int, int>>& snake, int width, int height) {
	auto head = snake.front();
	if (head.first <= 0 || head.first >= width - 1 || head.second <= 0 || head.second >= height - 1) {
		return true;
	}
	for (size_t i = 1; i < snake.size(); i++) {
		if (snake[i] == head) {
			return true;
		}
	}
	return false;
}


int main() {
	const int width = 20;
	const int height = 20;
	vector<pair<int, int>> snake = { {width / 2 , height / 2} };
	pair<int, int> food = { 1 + rand() % (width - 2) , 1 + rand() % (height - 2) };
	char direction = 'd';
	bool grow = false;
	bool gameover = false;

	srand(time(0));

	while (!gameover) {
		system("cls");
		drawField(width, height, snake, food);
		playerInput(direction);
		updateSnake(snake, direction, grow);
		checkFood(snake, food, grow, width, height);
		gameover = checkCollision(snake, width, height);
		Sleep(80);
	}
	cout << "GAME OVER" << endl;
	return 0;
}