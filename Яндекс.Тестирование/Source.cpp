#include <iostream>
#include <string>
#include <map>

using namespace std;

// 1 right window
#define Rejection "Cannot fulfill passengers requirements"

map<int, char> seats = {
	{0,'A'},
	{1,'B'},
	{2,'C'},
	{3,'_'},
	{4,'D'},
	{5,'E'},
	{6,'F'}
};

class Plane {
public:
	char* planePlan;
	int countRows;
	int space;
	int occupied = 0;
	int width;


	Plane(int width_value) {
		char buff;
		width = width_value;

		cin >> countRows;

		planePlan = new char[countRows * width];
		space = countRows * (width - 1);


		for (int i = 0; i < (countRows * width); i++) {
			cin >> buff;

			switch (buff)
			{
			case '.': {
				planePlan[i] = '.';
				break;
			}
			case '#': {
				planePlan[i] = '#';
				occupied++;
				break;
			}
			case '_': {
				planePlan[i] = '_';
				break;
			}
			default:
				break;
			}
		}

	}

	bool addPassanger(string* wish) {
		int countPeople = stoi(wish[0]);
		int findPlace = 0;
		char key1 = wish[1][0];
		char key2 = wish[2][0];


		switch (key1)
		{
		case 'r': {
			switch (key2)
			{
			case 'w': {
				for (int i = 0; i < countRows + 1; i++) {
					if (findPlace == countPeople) {
						int startJ = 6;
						int finishJ = 6 - countPeople;


						cout << "Passengers can take seats:";
						printPlace(i, finishJ, startJ);
						cout << endl;

						while (startJ > finishJ) {
							planePlan[(i - 1) * width + startJ] = 'X';
							startJ--;
						}
						
						return true;						
					} // проверка на количество и обработка информации
					if (i == countRows + 1)
						break; // костыль


					findPlace = 0; // обнуляем так как сменили ряд

					if (planePlan[i * width + 6] == '#')
						continue; // проверка на свободное окно в ряду
					else
						findPlace++;

					for (int j = 5; j > 3; j--) {
						if (findPlace == countPeople)
							break; // проверка на количество

						if (planePlan[i * width + j] == '.')
							findPlace++;
						else
							break; // если занято меняем ряд					
					}
				}
				break;
			}

			case 'a': {
				for (int i = 0; i < countRows + 1; i++) {
					if (findPlace == countPeople) {
						int startJ = 4;
						int finishJ = 4 + countPeople;


						cout << "Passengers can take seats:";
						printPlace(i, startJ - 1, finishJ - 1);
						cout << endl;

						while (startJ < finishJ) {
							planePlan[(i - 1) * width + startJ] = 'X';
							startJ++;
						}

						return true;
					} // проверка на количество и обработка информации
					if (i == countRows + 1)
						break; // костыль

					findPlace = 0; // обнуляем так как сменили ряд

					if (planePlan[i * width + 4] == '#')
						continue; // проверка на свободное окно в ряду
					else
						findPlace++;

					for (int j = 5; j < 7; j++) {
						if (findPlace == countPeople)
							break; // проверка на количество

						if (planePlan[i * width + j] == '.')
							findPlace++;
						else
							break; // если занято меняем ряд					
					}
				}
				break;
			}
			}
			break; // закрыли r
		}
		case 'l': {
			switch (key2)
			{
			case 'w': {
				for (int i = 0; i < countRows + 1; i++) {
					if (findPlace == countPeople) {
						int startJ = 0;
						int finishJ = 0 + countPeople;


						cout << "Passengers can take seats:";
						printPlace(i, startJ - 1, finishJ - 1);
						cout << endl;

						while (startJ < finishJ) {
							planePlan[(i - 1) * width + startJ] = 'X';
							startJ++;
						}

						return true;
					} // проверка на количество и обработка информации

					if (i == countRows + 1)
						break; // костыль

					findPlace = 0; // обнуляем так как сменили ряд

					if (planePlan[i * width + 0] == '#')
						continue; // проверка на свободное окно в ряду
					else
						findPlace++;

					for (int j = 1; j < 3; j++) {
						if (findPlace == countPeople)
							break; // проверка на количество

						if (planePlan[i * width + j] == '.')
							findPlace++;
						else
							break; // если занято меняем ряд					
					}				
				}
				break; // закрыли кейс "w"
			}
			case 'a': {
				for (int i = 0; i < countRows + 1; i++) {
					if (findPlace == countPeople) {
						int startJ = 2;
						int finishJ = 2 - countPeople;


						cout << "Passengers can take seats:";
						printPlace(i, finishJ, startJ);
						cout << endl;

						while (startJ > finishJ) {
							planePlan[(i - 1) * width + startJ] = 'X';
							startJ--;
						}

						return true;
					} // проверка на количество и обработка информации
					if (i == countRows + 1)
						break; // костыль

					findPlace = 0; // обнуляем так как сменили ряд

					if (planePlan[i * width + 2] == '#')
						continue; // проверка на свободное окно в ряду
					else
						findPlace++;

					for (int j = 1; j > -1; j--) {
						if (findPlace == countPeople)
							break; // проверка на количество

						if (planePlan[i * width + j] == '.')
							findPlace++;
						else
							break; // если занято меняем ряд					
					}
				}
				break; // закрыли кейс "a"
			}

			} // закрыли key2
			break;
		} // закрыли "l"

		}
		cout << Rejection << endl;
		return false;
	}
		
	void addManyPassanger() {
		int countRequest;
		string* wish = new string[3];

		cin >> countRequest;

		for (int i = 0; i < countRequest; i++) {
			cin >> wish[0];
			cin >> wish[1];
			cin >> wish[2];
			if (addPassanger(wish))
				printPlan();
		}
	}

	void printPlan() {
		for (int i = 0; i < (countRows * width); i++) {
			cout << planePlan[i];
			if (planePlan[i] == 'X') {
				planePlan[i] = '#';
			}
			if ((i + 1) % width == 0)
				cout << endl;
		}
	}

	void printPlace(int row, int start, int stop) {
		while (start < stop) {
			cout << " " << to_string(row) << seats[start + 1];
			start++;
		}
	}

};


int main() {
	Plane plane(7);

	plane.addManyPassanger();

	//plane.printPlan();
}