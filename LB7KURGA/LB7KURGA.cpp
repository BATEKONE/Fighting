#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

delegate void MethodContainer(int count); //объявление делегата для обработки события

ref class PowerUp // Класс в котором производится счет
{
public:
	event MethodContainer^ counter; // объявление события counter с типом делегата

	void Method()
	{
		for (int i = 0; i < 100; i++)
		{
			if (i == 7)
			{
				counter(i);
			}
		}
	}
};

class Room
{
private:
	int health1, health2, power1, power2, ii, jj;
public:

	void setHealth()
	{
		health1 = 70 + rand() % (80 - 70 + 1);
		cout << "Здоровье первого игрока: " << health1 << endl;
		health2 = 70 + rand() % (80 - 70 + 1);
		cout << "Здоровье второго игрока: " << health2 << endl << endl;
	}
	
	void setPower()
	{
		do
		{
			power1 = 20 + rand() % (30 - 20 + 1);
			power2 = 20 + rand() % (30 - 20 + 1);
			cout << "Здоровье игрока номер 2: " << health2 << endl;
			cout << "Mощность удара игрокa 2: " << power2 << endl << endl;
			health2 -= power1;
			cout << endl;
			cout << "Здоровье игрока номер 1: " << health1 << endl;
			cout << "Mощность удара игрокa 1: " << power1 << endl << endl;
			health1 -= power2;
			cout << endl;
			if ((health1 <= 0) && (health2 > 0))
			{
				ii++;
				cout << endl << "Игрок 1 умер" << endl << endl;
				break;
			}
			else if((health2 <= 0) && (health1 > 0))
			{
				jj++;
				cout << endl << "Игрок 2 умер" << endl << endl;
				break;
			}
		} while ((health1 >= 0) || (health2 >= 0));
	}

	void getII1()
	{
		cout << ii;
	}

	void getII2()
	{
		cout << jj;
	}
};

class Player
{
private:
	string name1, name2;
public:
	void setName()
	{
		cout << "Введите имя первого игрока: ";
		cin >> name1;
		cout << endl;
		cout << "Введите имя второго игрока: ";
		cin >> name2;
		cout << endl;
	}
};

ref class Message // Класс, который среагирует, когда значение счетчика будет равно 7
{
public:
	void Messages(int count)
	{
			cout << "GAME OVER" << endl;
			cout << "Игра достигла " << count << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int forswitch;
	bool forwhile = true;

	Player* player = new Player();
	Room* room = new Room();

	PowerUp^ powerup = gcnew PowerUp();
	Message^ message = gcnew Message();
	
	while (forwhile)
	{
		forwhile = false;
		cout << "MENU" << endl;
		cout << "1) Ввести имена игроков" << endl;
		cout << "2) Провести бой" << endl;
		cout << "3) Проверить статистику побед" << endl;
		cout << "Ваш выбор: ";
		cin >> forswitch;
		cout << endl;
		switch (forswitch)
		{
		case 1:
		{
			player->setName();
			forwhile = true;
			break;
		}
		case 2:
		{
			room->setHealth();
			room->setPower();
			powerup->counter += gcnew MethodContainer(message, &Message::Messages);
			powerup->Method();
			delete powerup;
			forwhile = true;
			break;
		}
		case 3:
		{
			room->getII1();
			cout << " || ";
			room->getII2();
			cout << endl << endl;
			forwhile = true;
			break;
		}
		}
	}
}