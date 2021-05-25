#include <iostream>
#include "Texts.h"
#include <Windows.h>
#include <conio.h>




using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	//cout << "hello";
	Text t;
	int op;




	while (true) {
		system("cls");
		cout << t << endl;
		cout << "0. Выход\n";
		cout << "1. right\n";
		cout << "2. left\n";
		cout << "3. top\n";
		cout << "4. add left\n";
		cout << "5. add right\n";
		cout << "6. remove\n";
		cout << "7. edit\n";
		cout << "8. save\n";
		cout << "9. load\n";


		cin >> op;
		string tmp;
		try {
			switch (op)
			{
			case 0: return 0; break;
			case 1: t.right(); break;
			case 2: t.left(); break;
			case 3: t.top(); break;
			case 4:
				cin.seekg(cin.eof());
				getline(cin, tmp);
				t.addLeft(tmp);
				break;
			case 5:
				cin.seekg(cin.eof());
				getline(cin, tmp);
				t.addRight(tmp);
				break;
			case 6:
				t.remove();
				break;
			case 7:
				cin.seekg(cin.eof());
				getline(cin, tmp);
				t.edit(tmp);
				break;
			}
			if (op == 8) {

				ofstream f;
				f.open("text.txt");

				f << t;
				f.close();
			}
			if (op == 9) {

				ifstream fi;
				fi.open("text.txt");


				fi >> t;
				fi.close();
			}


		}
		catch (const char* err_s) {
			cout << err_s << endl;
			_getch();
		}
	}






	return 0;
}