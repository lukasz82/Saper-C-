#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <string.h>
using namespace std;


		int mapa_2d[10][10];
		char mapa_gracza[10][10]; // mapa na której będą wyświetlane rezultaty
		int ilosc_bomb;
		int licznik_bomb;
		int poz_x, poz_y; // pozycje analizowanego obszaru - po potwierdzeniu pozycji poprzez kursor
		int kopia_x, kopia_y; // pozycje kursora, kursor nie ma wpływu na mape dokuki nie zaakceptujemy jego pozycji
		int ilosc_pozostalych_bomb;
		int start; // zmienna potrzebna tylko na początku gry do sprawdzenia pól koło gracza
		int rozmiar_mapy;
		unsigned char znak;
		bool czy_koniec_gry; //




		void Mapa (int); // <-- A --> PROJEKT DOMU :)  int - jest parametrem mapy, będzie to jej rozmiar przy jej tworzeniu (tak zwanego obiektu klasy)
		void WyswietlMape();
		void WylosujBomby();
		void WyswietlMapeGracza();
		void AnalizujMape();
		void Analizuj3x3(int, int);
		void Sprawdz(int, int);
		void UstalPozGracza(int, int);
		void ZmienPozGracza();
		char Gra();


void Mapa(int ile_bomb) { // tutaj są instrukcje dla ekipy jak ma zbudować obiekt (np. DOM), czyli algorytm tworzenia obiektu na podstawie projektu (klasy)
	rozmiar_mapy = 10;
	if ( ile_bomb > 20) ile_bomb = 20; // nie można dać więcej niż 20 bomb
	if ( ile_bomb < 1) ile_bomb = 10; // nie można dać więcej niż 20 bomb
	ilosc_bomb = ile_bomb;
	ilosc_pozostalych_bomb = ile_bomb;
	licznik_bomb = 0;
	start = 1;
	czy_koniec_gry = false;

	for (int i = 0; i < rozmiar_mapy; ++i)
		{
			for(int j = 0; j < rozmiar_mapy; ++j)
			{
				mapa_2d[i][j] = 0;
				mapa_gracza[i][j] = '-';
			}

		}
	// domyślnie dla testów wstawiam bomby
	//mapa_2d[4][6] = 9;
	//mapa_2d[4][8] = 9;
	//mapa_2d[6][6] = 9;
	//mapa_2d[6][8] = 9;

	cout << "Stworzylem mape" << endl;
}



void WyswietlMape() { // funkcja wyświetlająca mapę
	for (int i = 0; i < rozmiar_mapy; ++i)
		{
			for(int j = 0; j < rozmiar_mapy; ++j)
			{
				cout << mapa_2d[i][j];
			}
			cout << endl;
		}
};

void WyswietlMapeGracza() { // funkcja wyświetlająca mapę
	for (int i = 0; i < rozmiar_mapy; ++i)
		{
			for(int j = 0; j < rozmiar_mapy; ++j)
			{
				if ( i == kopia_x && j == kopia_y)
				{
					cout << "x";
					continue;
				}

				if ( mapa_2d[i][j] == 8)
				{
                    cout << ' ';
					continue;
				}



				switch (mapa_2d[i][j]) {
				case 1 : cout << '1'; continue;
				case 2 : cout << '2'; continue;
				case 3 : cout << '3'; continue;
				case 4 : cout << '4'; continue;
				case 5 : cout << '5'; continue;
				case 6 : cout << '6'; continue;
				case 7 : cout << '7'; continue;
				}

				cout << mapa_gracza[i][j];
			}
			cout << endl;
		}
};

void WylosujBomby() { // funkcja losująca bomby na mapie // funkcja przy wywołaniu oczekuje że podamy jakąś wartość typu int (w tym przypadku ilość_bomb)
	int licznik;
	licznik = 0;
	srand (time (0));
	int x,y;

	while (licznik < ilosc_bomb) {
		x = rand() % (rozmiar_mapy);
		y = rand() % (rozmiar_mapy);
		cout << "Wyl. bomba na poz.: " << x << " , " << y << endl;
		if (mapa_2d[x][y] == 9) continue;
		mapa_2d[x][y] = 9;
		licznik++;
	}
};

void Analizuj3x3(int x, int y)
{
	licznik_bomb = 0;
	for (int i = x-1; i < x+2; ++i)
	{
		for (int j = y-1; j < y+2; ++j)
		{
			if ( i > -1 && i < rozmiar_mapy && j > -1 && j < rozmiar_mapy)
			{
				if (mapa_2d[i][j] == 9) licznik_bomb++;

			}
		}
	}
}

void Sprawdz(int x, int y)
{
	if (licznik_bomb == 0 && mapa_2d[x][y] == 0) mapa_2d[x][y] = 0;
	if (licznik_bomb > 0 && mapa_2d[x][y] == 0)
	{
		mapa_2d[x][y] = licznik_bomb;
		mapa_gracza[x][y] = licznik_bomb;
	}
	licznik_bomb = 0;
}

void UstalPozGracza(int x, int y)
{
	poz_x = x;
	poz_y = y;
	kopia_x = x;
	kopia_y = y;
	while (mapa_2d[poz_x][poz_y] == 9) { // sprawdza czy na domyslnej pozycji nie ma już bomby i w razie konieczności przestawia gracza
	poz_x++;
	poz_y++;
	}
	mapa_2d[poz_x][poz_y] = 8;
}

void ZmienPozGracza()
{
	znak = getch();
	system ("CLS");

	if (znak == 72) // gora
	{
		kopia_x--;
	}

	if (znak == 80) // dol
	{
		kopia_x++;
	}

	if (znak == 75) // lewo
	{
		kopia_y--;
	}

	if (znak == 77) // prawo
	{
		kopia_y++;
	}

	if (znak == 'a') // akceptacja // klawisz a
	{
		poz_x = kopia_x;
		poz_y = kopia_y;
	}

	if (znak == 'r') // próba rozbrojenia bomby // klawisz r
	{
		if (mapa_2d[kopia_x][kopia_y] == 9)
		{
			mapa_2d[kopia_x][kopia_y] = 8;
			for (int i = kopia_x-1; i < kopia_x+2; ++i)
			{
				for (int j = kopia_y-1; j < kopia_y+2; ++j)
				{
					if ( i > -1 && i < rozmiar_mapy && j > -1 && j < rozmiar_mapy)
					{
						if (mapa_2d[i][j] > 0 && mapa_2d[i][j] != 9  && mapa_2d[i][j] != 8)
						{

							mapa_2d[i][j] = mapa_2d[i][j] - 1 ;
							if (mapa_2d[i][j] == 0)
                                {
                                    mapa_2d[i][j] = 8; // sprawdzone pole po rozbrojeniu
                                }
						}
					}
				}
			}


			cout << " Bomba zostala rozbrojona";
			ilosc_pozostalych_bomb--;
		} else {
			cout << "ZLE!!! Tutaj nie ma bomby" << endl;
		}
	}
	cout << " " << kopia_x << " " << kopia_y << " " <<  endl;
	cout << "Pozostalo " << ilosc_pozostalych_bomb << " Bomb do rozbrojenia" << endl;


}

void AnalizujMape() { // funkcja wyświetlająca mapę
	int x, y; // zmienne tymczasowe
	x = poz_x;
	y = poz_y;


					if (mapa_2d[x][y] != 9 && mapa_2d[x][y] != start
						&& mapa_2d[x][y] != 1
						&& mapa_2d[x][y] != 2
						&& mapa_2d[x][y] != 3
						&& mapa_2d[x][y] != 4
						&& mapa_2d[x][y] != 5
						&& mapa_2d[x][y] != 6
						&& mapa_2d[x][y] != 7
						)
					{
						start = 8;
							if (x+1 < rozmiar_mapy)
							{
								if (mapa_2d[x+1][y] == 0)
								{
									Analizuj3x3(x+1,y);
									Sprawdz(x+1,y);
									}
							}

							if (x-1 > -1)
							{
								if (mapa_2d[x-1][y] == 0)
								{
									Analizuj3x3(x-1,y);
									Sprawdz(x-1,y);
								}
							}

							if (y+1 < rozmiar_mapy)
							{
								if (mapa_2d[x][y+1] == 0)
								{
									Analizuj3x3(x,y+1);
									Sprawdz(x,y+1);
								};
							}

							if (y-1 > -1)
							{
								if (mapa_2d[x][y-1] == 0)
								{
									Analizuj3x3(x,y-1);
									Sprawdz(x,y-1);
								}
							}

							if (y+1 < rozmiar_mapy && x + 1 < rozmiar_mapy)
							{
								if (mapa_2d[x+1][y+1] == 0)
								{
									Analizuj3x3(x+1,y+1);
									Sprawdz(x+1,y+1);
								}
							}

							if (x - 1 > -1 && y - 1 > -1)
							{
								if (mapa_2d[x-1][y-1] == 0)
								{
									Analizuj3x3(x-1,y-1);
									Sprawdz(x-1,y-1);
								}
							}

							if (y-1 > -1 && x + 1 < rozmiar_mapy)
							{
								if (mapa_2d[x+1][y-1] == 0)
								{
									Analizuj3x3(x+1,y-1);
									Sprawdz(x+1,y-1);
								}
							}

							if (x-1 > -1 && y + 1 < rozmiar_mapy)
							{
								if (mapa_2d[x-1][y+1] == 0)
								{
									Analizuj3x3(x-1,y+1);
									Sprawdz(x-1,y+1);
								}
							}
				    mapa_2d[x][y] = 8;
					} else if (mapa_2d[x][y] == 9) {

					cout << "BOOM!!! BOMBA!!!, urwalo ci nogi" << endl;
					czy_koniec_gry = true;
					}
}

    char Gra()
    {
        Mapa(10); // Funkcja z wprowadzoną ilością bomb
        WyswietlMape();
        WylosujBomby();
        WyswietlMape();
        UstalPozGracza(4,4);
        AnalizujMape();
        WyswietlMapeGracza();
        while (1)
        {
            ZmienPozGracza();
            AnalizujMape();
            WyswietlMapeGracza();
            if (ilosc_pozostalych_bomb == 0)
            {
                cout << "WYGRALES" << endl;

                	system ("pause");
                    return 0;
            }
            if (czy_koniec_gry == true)
            {
                cout << "PRZEGRALES" << endl;
                cout << "Nacisnij dowolny klawisz zeby zagrac lub klawisz 'n' zeby zakonczyc" << endl;
                znak = getch();
                if ( znak == 't')
                {
                    break;
                }

                if (znak == 'n')
                {
                    czy_koniec_gry = false;
                    return znak;
                }

                if (znak != 'n' && znak != 't')
                {
                    czy_koniec_gry = false;
                    return 'n';
                }
            }
        }
    }




int main(){

    while (znak != 'n')
    {
        Gra();
    }


	system ("pause");
	return 0;
}
