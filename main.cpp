#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

//Wersja 0.1 pracujaca z zapisem do pliku;Change: Na podstawie ksi¹¿ki adresowej na tablicach wersji 0.3, zmieniono na wektory

using namespace std;

fstream PLIK;

struct Adresat
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};


string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline (cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};
    while (true)
    {
        getline(cin, wejscie);
        if ( (wejscie[0]=='9') || (wejscie[0] >= '1') && (wejscie[0] <='6'))
        {
            znak=wejscie[0];
            break;
        }
        cout << "Ta opcja jest nieobslugiwana. Wpisz ponownie cyfre." << endl;
    }
    return znak;
}

char wczytajZnak2()
{
    string wejscie = "";
    char znak = {0};
    while (true)
    {
        getline(cin, wejscie);
        if ((wejscie[0] >= '1') && (wejscie[0] <='5'))
        {
            znak=wejscie[0];
            break;
        }
        cout << "Ta opcja jest nieobslugiwana. Wpisz ponownie cyfre." << endl;
    }
    return znak;
}

char wczytajZnak3()
{
    string wejscie = "";
    char znak = {0};
    while (true)
    {
        getline(cin, wejscie);
        if ((wejscie[0] >= '1') && (wejscie[0] <='3') || (wejscie[0]=='9') )
        {
            znak=wejscie[0];
            break;
        }
        cout << "Ta opcja jest nieobslugiwana. Wpisz ponownie cyfre." << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita()
{

    string wejscie = "";
    int liczba = 0;
    while (true)
    {
        getline(cin, wejscie);
        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return liczba;
}

string konwersjaIntNaString (int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

void odczytywanieDanychZPliku(vector <Adresat> & adresaci)
{

    int najwyzszyNumerID = 0;
    int j = 0;
    PLIK.open("Ksiazka Adresowa.txt",ios::in);
    if (!PLIK.good())
    {
        cout << "Nie odnaleziono bazy danych. Tworzenie nowego pliku" << endl;
        PLIK.open("Ksiazka Adresowa.txt",ios::out);
        PLIK.close();
    }
    string odczytaneLinieZPliku;
    int dlugosc = 0;
    while(getline(PLIK,odczytaneLinieZPliku))
    {
        dlugosc = odczytaneLinieZPliku.length();
        int sektorDanych = 0;
        int polozeniePoprzedniegoZnaku = 0;

        string tymczasowyString = "";
        for (int i=0; i<=dlugosc; i++)
        {
            if (odczytaneLinieZPliku[i] == '|')
            {

                switch(sektorDanych)
                {
                case 0:
                    adresaci.push_back(Adresat());
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].id =  atoi(tymczasowyString.c_str());
                    polozeniePoprzedniegoZnaku = i+1;
                    najwyzszyNumerID = adresaci[j].id;
                    sektorDanych++;
                    break;
                case 1:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].imie = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 2:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].nazwisko = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 3:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].numerTelefonu = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 4:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].email = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 5:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].adres = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    j++;
                    break;
                }

            }
        }
    }
    PLIK.close();

}

void wyswietlWszystkieKontakty(vector <Adresat> & adresaci)
{
    int vectorSize = adresaci.size();   //bardziej optymalne rozwiazanie. Wywoluje 1 petle a nie skacze za kazdym razem przeszukujac wektor i jego wielkosc
    for(int i=0; i < vectorSize; i++)
    {
        cout << "Id: "<< adresaci[i].id << endl << "Imie: " << adresaci[i].imie << endl << "Nazwisko: " << adresaci[i].nazwisko << endl << "Numer telefonu: " << adresaci[i].numerTelefonu << endl << "Adres: " << adresaci[i].email << endl << adresaci[i].adres << endl << endl;
    }

    cout << endl;
}

void dodajAdresata(vector <Adresat> & adresaci)
{
    PLIK.open("Ksiazka Adresowa.txt",ios::in);
    int najwyzszyNumerID;
    string sprawdzenie;
    getline (PLIK, sprawdzenie);
    int dlugosc = sprawdzenie.length();
    int wielkoscWektora;
    if  (dlugosc == 0)
    {
       wielkoscWektora = 0;
    }
    else
    {
        wielkoscWektora = adresaci.size();
    }
    if (wielkoscWektora != 0)
    {
        najwyzszyNumerID = adresaci.back().id;
    }
    else
    {
        najwyzszyNumerID = 0;
    }
    PLIK.close();

            adresaci.push_back(Adresat());
            najwyzszyNumerID++;
            string tymczasowyString ="";
            adresaci[wielkoscWektora].id = najwyzszyNumerID;
            cout << "Podaj imie nowego kontaktu:";
            cin >> tymczasowyString;
            adresaci[wielkoscWektora].imie = tymczasowyString;
            cout << "Podaj nazwisko nowego kontaktu:";
            cin >> tymczasowyString;
            adresaci[wielkoscWektora].nazwisko = tymczasowyString;
            cout << "Podaj numer telefonu nowego kontaktu:";
            tymczasowyString = wczytajLinie();
            adresaci[wielkoscWektora].numerTelefonu = tymczasowyString;
            cout << "Podaj email nowego kontaktu:";
            tymczasowyString = wczytajLinie();
            adresaci[wielkoscWektora].email = tymczasowyString;
            cout << "Podaj adres nowego kontaktu:";
            tymczasowyString = wczytajLinie();
            adresaci[wielkoscWektora].adres = tymczasowyString;
}

void zapisDoPliku (vector <Adresat> & adresaci)
{
    PLIK.open("Ksiazka Adresowa.txt",ios::out);
    for(int i=0; i<adresaci.size(); i++)
    {
        PLIK<< adresaci[i].id << "|";
        PLIK<< adresaci[i].imie << "|";
        PLIK<< adresaci[i].nazwisko << "|";
        PLIK<< adresaci[i].numerTelefonu << "|";
        PLIK<< adresaci[i].email << "|";
        PLIK<< adresaci[i].adres << "|" << endl;

    }
    PLIK.close();
}

void wyszukajAdresataPoImieniu (vector <Adresat> & adresaci)
{
    string imieDoWyszukania = "";
    cout << "Podaj imie do wyszukania" << endl;
    cin >> imieDoWyszukania;
    cout << "Wyswietlam wyniki wyszukiwania imienia: " << imieDoWyszukania << endl;
    bool czyZnalezionoPrzynajmniejJednoImie = 0;
    for(int i=0; i<adresaci.size(); i++)
    {
        if (imieDoWyszukania == adresaci[i].imie)
        {
            cout <<adresaci[i].id << " "<< adresaci[i].imie << " " << adresaci[i].nazwisko << " " << adresaci[i].numerTelefonu << " " << adresaci[i].email << " " << adresaci[i].adres << endl;
            czyZnalezionoPrzynajmniejJednoImie = 1;
        }
        cout << endl;
    }
    if (czyZnalezionoPrzynajmniejJednoImie == 0)
    {
        cout << "Brak wynikow w ksiazce adresowej dla imienia: " << imieDoWyszukania << endl << endl;
    }
}

void wyszukajAdresataPoNazwisku(vector <Adresat> & adresaci)
{
    string nazwiskoDoWyszukania = "";
    cout << "Podaj nazwisko do wyszukania" << endl;
    cin >> nazwiskoDoWyszukania;
    cout << "Wyswietlam wyniki wyszukiwania nazwiska: " << nazwiskoDoWyszukania << endl;
    bool czyZnalezionoPrzynajmniejJednoImie = 0;
    for(int i=0; i<adresaci.size(); i++)
    {
        if (nazwiskoDoWyszukania == adresaci[i].nazwisko)
        {
            cout <<adresaci[i].id << " "<< adresaci[i].imie << " " << adresaci[i].nazwisko << " " << adresaci[i].numerTelefonu << " " << adresaci[i].email << " " << adresaci[i].adres << endl << endl;
            czyZnalezionoPrzynajmniejJednoImie = 1;
        }
        cout << endl;
    }
    if (czyZnalezionoPrzynajmniejJednoImie == 0)
    {
        cout << "Brak wynikow w ksiazce adresowej dla nazwiska: " << nazwiskoDoWyszukania << endl << endl;
    }
}


void usunAdresata (vector <Adresat> & adresaci)
{
    int najwyzszyNumerID = adresaci.back().id;
    string idDoUsuniecia = "";
    int idDoUsunieciaInt;
    int tymczasowyID = 0;
    while (true)
    {

        cout << "Podaj id adresata do usuniecia" << endl;
        cin >> idDoUsuniecia;
        idDoUsunieciaInt = atoi (idDoUsuniecia.c_str());

        if (idDoUsunieciaInt <= najwyzszyNumerID)
        {
            break;
        }
        cout << "Nie ma uzytkownika z takim numerem. Wpisz ponownie." << endl;
        break;
    }
   // if (idDoUsunieciaInt == najwyzszyNumerID)
   // {
   //     najwyzszyNumerID = najwyzszyNumerID-1;
   // }
    for(int i=0; i<=adresaci.size(); i++)
    {
        tymczasowyID = adresaci[i].id;
        if (tymczasowyID == idDoUsunieciaInt)
        {
            adresaci.erase(adresaci.begin()+tymczasowyID-1);
        }
    }
    cout << "Powracam do Menu Glownego" << endl;
}


void edytujAdresata (vector <Adresat> & adresaci)
{
    int najwyzszyNumerID = adresaci.back().id;
    int tymczasowyID = 0;
    int idDoZmianyInt = 0;

    int wybor = 0;
    string idDoZmiany = "";
    string tymczasowyString ="";
    while (true)
    {
        cout << "Podaj id adresata do zmiany" << endl;
        cin >> idDoZmiany;
        idDoZmianyInt = atoi (idDoZmiany.c_str());
        if (idDoZmianyInt <= najwyzszyNumerID)
        {
            break;
        }
        cout << "Nie ma uzytkownika z takim numerem. Wpisz ponownie." << endl;
    }
    for(int i=0; i<=adresaci.size(); i++)    {
        int tymczasowyID = adresaci[i].id;

        if (tymczasowyID == idDoZmianyInt)
        {
            cout << "Podaj co chcesz edytowac. Wybierz liczbe" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            wybor = wczytajZnak2();

            switch(wybor)
            {
            case '1':
                cout << "Podaj nowe imie kontaktu:";
                cin >> tymczasowyString;
                adresaci[i].imie = tymczasowyString;
                break;
            case '2':
                cout << "Podaj nowe nazwisko kontaktu:";
                cin >> tymczasowyString;
                adresaci[i].nazwisko = tymczasowyString;
                break;
            case '3':
                cout << "Podaj nowy numer telefonu kontaktu:";
                tymczasowyString = wczytajLinie();
                adresaci[i].numerTelefonu = tymczasowyString;
                break;
            case '4':
                cout << "Podaj nowy email kontaktu:";
                tymczasowyString = wczytajLinie();
                adresaci[i].email = tymczasowyString;
                break;
            case '5':
                cout << "Podaj nowy adres kontaktu:";
                tymczasowyString = wczytajLinie();
                adresaci[i].adres = tymczasowyString;

            }
            cout << "Dane adresata zostaly zmienione" << endl << endl;

        }


    }
}


int main()
{
    vector <Adresat> adresaci;
    int najwyzszyNumerID = 0;
    odczytywanieDanychZPliku(adresaci);
    char wybor;
    while (1)
    {
        //system("cls");
        cout << "Menu glowne logowania." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout << "1. Rejestracja." << endl;
        cout << "2. Logowanie." << endl;
        cout << "9. Koniec programu." << endl;
        wybor = wczytajZnak3();
        switch (wybor)
        {
        case '1':
            //logowanie;

            break;
        case '2':
            while (1)
            {
                //system("cls");
                cout << "Menu glowne." << endl;
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
                cout << "1. Rejestracja nowej osoby." << endl;
                cout << "2. Wyszukiwanie po imieniu." << endl;
                cout << "3. Wyszukiwanie po nazwisku." << endl;
                cout << "4. Wyswietl wszystkie kontakty." << endl;
                cout << "5. Usun kontakt." << endl;
                cout << "6. Edytuj kontakt." << endl;
                cout << "9. Wyloguj." << endl;
                cout << "Wybierz liczbe: " << endl;
                wybor = wczytajZnak();
                switch(wybor)
                {
                case '1':
                    dodajAdresata(adresaci);

                    zapisDoPliku(adresaci);
                    system("pause");
                    break;
                case '2':
                    wyszukajAdresataPoImieniu(adresaci);
                    system("pause");
                    break;
                case '3':
                    wyszukajAdresataPoNazwisku(adresaci);
                    system("pause");
                    break;
                case '4':
                    wyswietlWszystkieKontakty(adresaci);
                    system("pause");
                    break;
                case '5':
                    usunAdresata(adresaci);
                    zapisDoPliku(adresaci);
                    adresaci.clear();
                    odczytywanieDanychZPliku(adresaci);
                    system("pause");
                    break;
                case '6':
                    edytujAdresata(adresaci);
                    zapisDoPliku(adresaci);
                    system("pause");
                    break;
                case '9':
                    cout<<"Wylogowano" << endl;
                    break;
                }
                if (wybor == '9')
                {
                  break;
                }

            }
            break;
        case '9':
            cout<<"Zamykanie programu." << endl;
            exit(0);
        }

    }
    return 0;
}


