#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

int width = 40, height = 20;
char buffer[40 * 20];
int snake[40 * 20];
int backgroundASCIICode = '.';
int moveSide = 0; //0 - right, 1 - left, 2 - up, 3 - down;
int n;
int _isEnter = 0;
int appleCoordinates = 0;
char appleTexture = '$';
int plusSnakeCoordinates = 0;
int _isGame = 1;
char c;

void GetKey() {
	char b;
	if (kbhit()) {
		c = getch();
	}
	if (c == 'p') {
		while (1) {
			if (kbhit()) {
				c = getch();
				if (c == 'w' || c == 'd' || c == 's' || c == 'a') {
					break;
				}
			}
		}
	}
	if (c == 'd' && moveSide != 1) {
		moveSide = 0;
	} else if (c == 'a' && moveSide != 0) {
		moveSide = 1;
	} else if (c == 'w' && moveSide != 3) {
		moveSide = 2;
	} else if (c == 's' && moveSide != 2) {
		moveSide = 3;
	}
}

void Moving() {
	if (moveSide == 0) {
		if ((snake[0] + 1) % width != 0) {
			plusSnakeCoordinates = snake[n - 1];
			for (int i = n - 1; i > 0; i --) {
				snake[i] = snake[i - 1];
			}
			snake[0] += 1;
		} else {
			_isGame = 0;
		}
	} else if (moveSide == 1) {
		if (((snake[0] - 1) % width != (width - 1)) && (snake[0] > 0)) {
			plusSnakeCoordinates = snake[n - 1];
			for (int i = n - 1; i > 0; i --) {
				snake[i] = snake[i - 1];
			}
			snake[0] -= 1;
		} else {
			_isGame = 0;
		}
	} else if (moveSide == 2) {
		if ((snake[0] - width) >= 0) {
			plusSnakeCoordinates = snake[n - 1];
			for (int i = n - 1; i > 0; i --) {
				snake[i] = snake[i - 1];
			}
			snake[0] -= width;
		} else {
			_isGame = 0;
		}
	} else if (moveSide == 3) {
		if ((snake[0] + width) <= width * height) {
			plusSnakeCoordinates = snake[n - 1];
			for (int i = n - 1; i > 0; i --) {
				snake[i] = snake[i - 1];
			}
			snake[0] += width;
		} else {
			_isGame = 0;
		}
	}
}

void Apple() {
	if (snake[0] == appleCoordinates) {
		int _isApple = 1;
		snake[n] = plusSnakeCoordinates;
		n ++;
		while (_isApple) {
			appleCoordinates = rand() % (width * height);
			_isApple = 0;
			for (int i = 0; i < n; i ++) {
				if (snake[i] == appleCoordinates) {
					_isApple = 1;
				}
			}
		}
	}
}

void IsGame() {
	for (int i = 1; i < n; i ++) {
		if (snake[0] == snake[i]) {
			_isGame = 0;
			break;
		}
	}
}

void Score() {
	FILE *maxScore;
	maxScore = fopen("D:\\SublimeProject\\Debilizm\\Snake\\MaxScore.txt", "r");
	char fileString[200];
	int d;
	int scoreNumbers[4] = {0};

	scoreNumbers[3] = n;

	int lenght = 0;
	while ((d = fgetc(maxScore)) != EOF) {
		fileString[lenght] = d;
		lenght ++;
	}

	for (int i = 0, j = 4; i < 3; i ++) {
		int power = 0;
		while (fileString[j] != ' ') {
			j ++;
			power ++;
		}
		j -= power;
		for (int k = power - 1; k >= 0; k --) {
			scoreNumbers[i] += (fileString[j] - '0') * pow(10, k);
			j ++;
		}
		while (fileString[j] != 0x00) {
			if (fileString[j] != '\n') {
				j ++;
			} else {
				break;
			}
		}
		j += 5;
	}

	int nPosition = 3;
	for (int i = 2; i >= 0; i --) {
		if (scoreNumbers[3] > scoreNumbers[i]) {
			nPosition --;
		}
	}
	if (nPosition != 3) {
		for (int i = 3; i > nPosition; i --) {
			scoreNumbers[i] = scoreNumbers[i - 1];
			scoreNumbers[i - 1] = n;
		}
		char names[150];
		char ch;
		int count = 0;
		int j = 4;

		for (int i = 0; i < nPosition; i ++) {
			while (fileString[j] != ' ') {
				j ++;
			}
			j ++;

			while (fileString[j] != 0x00) {
				if (fileString[j] != '\n') {
					names[count] = fileString[j];
					count ++;
					j ++;
				} else {
					break;
				}
			}
			names[count] = ' ';
			count ++;
			j += 5;
		}

		printf("Enter your nickname: ");

		names[count] = '(';
		count ++;
		while ((ch = getche()) != EOF && ch != 13) {
			names[count] = ch;
			count ++;
		}
		names[count] = ')';
		count ++;
		names[count] = ' ';
		count ++;
		for (int i = nPosition + 1; i < 3; i ++) {
			while (fileString[j] != ' ') {
				j ++;
			}
			j ++;

			while (fileString[j] != 0x00) {
				if (fileString[j] != '\n') {
					names[count] = fileString[j];
					count ++;
					j ++;
				} else {
					break;
				}
			}
			names[count] = ' ';
			count ++;
			j += 5;
		}

		freopen("D:\\SublimeProject\\Debilizm\\Snake\\MaxScore.txt", "w", maxScore);

		printf("Leaders:\n");

		putchar('\n');
		count = 0;
		for (int i = 0; i < 3; i ++) {
			fprintf(maxScore, "%d - %d ", i + 1, scoreNumbers[i]);
			fprintf(stdout, "%d - %d ", i + 1, scoreNumbers[i]);
			while (names[count] != ' ') {
				fputc(names[count], maxScore);
				fputc(names[count], stdout);
				count ++;
			}
			count ++;
			fputc('\n', maxScore);
			fputc('\n', stdout);
		}
	} else {
		puts(fileString);
	}

	fclose(maxScore);
}

int main() {
	srand(time(NULL));

	//создание змейки
	snake[0] = rand() % (width * height - 3) + 2;
	plusSnakeCoordinates = snake[0] - 1;
	appleCoordinates = rand() % (width * height);
	n = 1;

	//создание пустого поля
	memset(buffer, backgroundASCIICode, width * height);
	//добавление на поле яблока
	buffer[appleCoordinates] = appleTexture;

	//добавление на поле змейки
	for (int i = 0; i < n; i ++) {
		buffer[snake[i]] = '#';
	}

	//вывод одного кадра игры
	for (int k = 1; k <= width * height; k ++) {
		if (k % width != 0) {
			putchar(buffer[k - 1]);
		} else {
			putchar(buffer[k - 1]);
			putchar('\n');
		}
	}

	c = getch();

	if (c == 'd') {
		moveSide = 0;
	} else if (c == 'a') {
		moveSide = 1;
	} else if (c == 'w') {
		moveSide = 2;
	} else if (c == 's') {
		moveSide = 3;
	}

	while (1) {
		//созлание пустого поля
		memset(buffer, backgroundASCIICode, width * height);
		//добавление на поле яблока
		buffer[appleCoordinates] = appleTexture;

		//движение змеи
		Moving();

		//проверка взял ли пользователь яблоко
		Apple();

		//проверка не врезалась ли змейка в себя
		IsGame();

		//добавление на поле змейки
		for (int i = 0; i < n; i ++) {
			buffer[snake[i]] = '+';
		}
		buffer[snake[n - 1]] = '-';
		buffer[snake[0]] = '#';

		//вывод одного кадра игры
		for (int k = 1; k <= width * height; k ++) {
			if (k % width != 0) {
				putchar(buffer[k - 1]);
			} else {
				putchar(buffer[k - 1]);
				putchar('\n');
			}
		}
		printf("Score = %d\n", n);

		//пользовательский ввод напрвления
		GetKey();

		if (n == width * height) {
			break;
		}

		if (_isGame == 0) {
			printf("Game Over.\n");
			printf("Your score = %d!\n", n);
			break;
		}

		Sleep(150);

		//очистка кадра
		system("cls");
	}

	putchar('\n');
	Score();

	getch();
}