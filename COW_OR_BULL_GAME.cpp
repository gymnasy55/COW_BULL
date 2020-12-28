// COW_OR_BULL_GAME.cpp: Ковальов Сергій, П-81

#define NUMDIGITS 3
#define MAXGUESS 10
#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

bool IsValid(string str)
{
	return str[0] != str[1] && str[0] != str[2] && str[1] != str[2];
}

string GetSecretNum()
	// Возвращает строку случайных чисел, которые не повторяются
{
	srand(time(NULL));
	string secretNum = "";
	int* numbers = new int[NUMDIGITS];
	bool* checked = new bool[10];
	for (int i = 0; i < 10; i++)
		checked[i] = false;
	for (int i = 0; i < NUMDIGITS; i++)
	{
		while(true)
		{
			int temp = rand() % 10;
			if(checked[temp] == false)
			{
				checked[temp] = true;
				numbers[i] = temp;
				break;
			}
		}
		secretNum += to_string(numbers[i]);
	}
	return secretNum;
}

string Clues(string guess, string secretNumber)
	// Возвращает строку с подсказкой
{
	vector<string> clues = {};
	string res = "";
	for(int i = 0; i < NUMDIGITS; i++)
	{
		if (guess[i] == secretNumber[i])
			clues.push_back("Горячо ");
		else if(secretNumber.find(guess[i]) != string::npos) // Где-то есть символ
			clues.push_back("Тепло ");
	}
	if (clues.empty())
		return "Холодно";
	sort(clues.begin(), clues.end());
	for (int i = 0; i < clues.size() - 1; i++)
		res += clues[i];
	res += clues[clues.size() - 1];
	return res;
}

bool IsOnlyDigits(string num)
	// Проверяет то, что строка состоит только из цифр
{
	if (num.empty())
		return false;
	for (char digit : num)
	{
		if (digit < '0' || digit > '9')
			return false;
	}
	return true;
}

void Rules()
	// Правила игры 
{
	cout << "Я загадаю число с таким кол-вом знаков: " << NUMDIGITS << endl;
	cout << "У вас будет " << MAXGUESS << " попыток." << endl;
	cout << "Я буду Вам подсказывать." << endl;
	cout << "Холодно - Вы ничего не отгадали." << endl;
	cout << "Тепло - Вы отгадали число, но не отгадали его позицию" << endl;
	cout << "Горячо - Вы отгадали число и позицию" << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Rules();
	while(true)
	{
		string secretNum = GetSecretNum();
		cout << "Я загадал Вам число. У вас есть " << MAXGUESS << " попыток, чтобы отгадать его.";
		int guesses = 1;
		char playAgain;
		while (guesses <= MAXGUESS)
		{
			string guess = "";
			while (guess.length() != NUMDIGITS || !IsOnlyDigits(guess) || !IsValid(guess))
			{
				cout << endl << "Попытка номер: " << guesses << endl;
				cin >> guess;
			}
			cout << Clues(guess, secretNum);
			guesses++;
			if (guess == secretNum)
			{
				cout << endl << "Вы победитель!! Поздравляем!!" << endl;
				break;
			}
			if (guesses > MAXGUESS) cout << endl << "Вы проиграли! У вас закончились попытки! Я загадал число - " << secretNum << endl;
		}
		cout << endl << "Хотите сыграть снова? Да(y) или Нет(n)?" << endl;
		cin >> playAgain;
		if (tolower(playAgain) != 'y')
			break;
	}
}