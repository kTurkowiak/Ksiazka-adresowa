#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
fstream PLIKAdresaci;
fstream PLIKUzytkownicy;

struct Adresat
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik
{
    int id;
    string login, haslo;
};


void odczytywanieDanychZPliku(vector <Adresat> & adresaci,int numerUzytkownika);
char wczytajZnakZMenu();
void logowanie (vector <Uzytkownik> & uzytkownicy);
void rejestracja (vector <Uzytkownik> & uzytkownicy);
void zapisDoPlikuUzytkownicy (vector <Uzytkownik> & uzytkownicy);
void odczytanieUzytkownikow (vector <Uzytkownik> & uzytkownicy);
void zapisDoPliku (vector <Adresat> & adresaci, int numerUzytkownika);
void dodajAdresata(vector <Adresat> & adresaci);
void wyszukajAdresataPoNazwisku(vector <Adresat> & adresaci);
void wyszukajAdresataPoImieniu (vector <Adresat> & adresaci);
void wyswietlWszystkieKontakty(vector <Adresat> & adresaci);
void usunAdresata (vector <Adresat> & adresaci);
void menuGlowne (vector <Uzytkownik> & uzytkownicy,int numerUzytkownika);
char wczytajZnakZPodmenu();
int sprawdzCzyIDIstnieje(vector <Adresat> & adresaci);
void edytujAdresata (vector <Adresat> & adresaci);
void edycjaHasla (vector <Uzytkownik> & uzytkownicy, int numerUzytkownika);


int main()
{

    vector <Uzytkownik> uzytkownicy;
    odczytanieUzytkownikow(uzytkownicy);
    char wybor;
    while (1)
    {
        system("cls");
        cout << "Menu glowne logowania." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout << "1. Logowanie." << endl;
        cout << "2. Rejestracja." << endl;
        cout << "9. Koniec programu." << endl;
        cout << "Wybierz cyfre: " << endl;
        wybor = wczytajZnakZMenu();
        switch (wybor)
        {
        case '1':
            logowanie(uzytkownicy);
            break;
        case '2':
            rejestracja (uzytkownicy);
            break;
        case '9':
            cout<<"Zamykanie programu." << endl;
            exit(0);
        }
    }
    return 0;
}

char wczytajZnakZMenu()
{
    string wejscie = "";
    char znak = {0};
    while (true)
    {
        getline(cin, wejscie);
        if ( (wejscie[0]=='9') || ((wejscie[0] >= '1') && (wejscie[0] <='2')))
        {
            znak=wejscie[0];
            break;
        }
        cout << "Ta opcja jest nieobslugiwana. Wpisz ponownie cyfre." << endl;
    }
    return znak;
}

void logowanie(vector <Uzytkownik> & uzytkownicy)
{
    string tymczasowyLogin = "";
    string tymczasoweHaslo = "";
    cout << "Podaj login:" << endl;
    cin >> tymczasowyLogin;
    cout << "Podaj haslo:" << endl;
    cin >> tymczasoweHaslo;
    bool zalogowanie = 1;
    int vectorSize = uzytkownicy.size();
    for (int i=0; i<vectorSize ;i++)
    {
         if ((uzytkownicy[i].login == tymczasowyLogin) && (uzytkownicy[i].haslo == tymczasoweHaslo))
        {
            cout << "Udalo sie zalogowac" << endl;
            system ("pause");
            zalogowanie = 1;
            menuGlowne(uzytkownicy,i);
        }
        else
        {
            zalogowanie = 0;
        }
    }
    if (zalogowanie == 0)
    {
       cout << "Nie udalo sie zalogowac" << endl;
       system ("pause");
    }

}

void rejestracja (vector <Uzytkownik> & uzytkownicy)
{
        PLIKUzytkownicy.open("Uzytkownicy.txt",ios::in);
    if (!PLIKUzytkownicy.good())
    {
        cout << "Nie odnaleziono bazy uzytkownikow. Tworzenie nowego pliku" << endl;
        PLIKUzytkownicy.open("Uzytkownicy.txt",ios::out);
        PLIKUzytkownicy.close();
    }
    int wielkoscWektoraUzytkownicy = uzytkownicy.size();
    int najwyzszyNumerIDUzytkownika = 1;
    if (wielkoscWektoraUzytkownicy != 0)
    {
        najwyzszyNumerIDUzytkownika = uzytkownicy.back().id;
        najwyzszyNumerIDUzytkownika++;
    }
    uzytkownicy.push_back(Uzytkownik());
    uzytkownicy[wielkoscWektoraUzytkownicy].id = najwyzszyNumerIDUzytkownika;
    string tymczasowyString = "";
    cout << "Rejestracja nowego uzytkownika. Podaj login:" << endl;
    cin >> tymczasowyString;
    uzytkownicy[wielkoscWektoraUzytkownicy].login = tymczasowyString;  //
    cout << "Podaj haslo:" << endl;
    cin >> tymczasowyString;
    uzytkownicy[wielkoscWektoraUzytkownicy].haslo = tymczasowyString;
    PLIKUzytkownicy.close();
    zapisDoPlikuUzytkownicy(uzytkownicy);

}

void zapisDoPlikuUzytkownicy(vector <Uzytkownik> & uzytkownicy)
{
    PLIKUzytkownicy.open("Uzytkownicy.txt",ios::out);
    int vectorSize = uzytkownicy.size();
    //cout <<"vectorSize->"<< uzytkownicy.size()<<endl;
    for(int i=0; i<vectorSize; i++)
    {
        PLIKUzytkownicy << uzytkownicy[i].id << "|";
        PLIKUzytkownicy << uzytkownicy[i].login << "|";
        PLIKUzytkownicy << uzytkownicy[i].haslo << "|" <<endl;
    }
    PLIKUzytkownicy.close();
}

void odczytanieUzytkownikow(vector <Uzytkownik> & uzytkownicy)
{
    string tymczasowyLogin = "";
    string tymczasoweHaslo = "";
    PLIKUzytkownicy.open("Uzytkownicy.txt",ios::in);
    if (!PLIKUzytkownicy.good())
    {
        cout << "Nie odnaleziono uzytkownikow. Przechodze do rejestracji" << endl;
        rejestracja(uzytkownicy);
    }
    string odczytaneLinieZPliku;
    int dlugoscLinii = 0;
    int j = 0;
    while(getline(PLIKUzytkownicy,odczytaneLinieZPliku))
    {
        dlugoscLinii = odczytaneLinieZPliku.length();
        int sektorDanych = 0;
        int polozeniePoprzedniegoZnaku = 0;
        string tymczasowyString = "";
        for (int i=0; i<=dlugoscLinii; i++)
        {
            if (odczytaneLinieZPliku[i] == '|')
            {
                switch(sektorDanych)
                {
                case 0:
                    uzytkownicy.push_back(Uzytkownik());
                    //cout << "j ->"<< j <<endl;
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    //cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    uzytkownicy[j].id =  atoi(tymczasowyString.c_str());
                    //cout << "uzytkownicy[j].id ->"<< uzytkownicy[j].id <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 1:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    uzytkownicy[j].login = tymczasowyString;
                    //cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    //cout << "uzytkownicy[j].login ->"<< uzytkownicy[j].login <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 2:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    uzytkownicy[j].haslo = tymczasowyString;
                    //cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    //cout << "uzytkownicy[j].haslo ->"<< uzytkownicy[j].haslo <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    j++;
                    break;
                }

            }
        }

    }
    PLIKUzytkownicy.close();
}

void menuGlowne (vector <Uzytkownik> & uzytkownicy, int numerUzytkownika)
{
    vector <Adresat> adresaci;
    while (1)
    {
        odczytywanieDanychZPliku(adresaci, numerUzytkownika);
        //system("cls");
        cout << "Menu glowne." << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout << "1. Rejestracja nowej osoby." << endl;
        cout << "2. Wyszukiwanie po imieniu." << endl;
        cout << "3. Wyszukiwanie po nazwisku." << endl;
        cout << "4. Wyswietl wszystkie kontakty." << endl;
        cout << "5. Usun kontakt." << endl;
        cout << "6. Edytuj kontakt." << endl;
        cout << "7. Edytuj haslo." << endl;
        cout << "9. Wyloguj." << endl;
        cout << "Wybierz cyfre: " << endl;
        char wybor;
        wybor = wczytajZnakZPodmenu();
        switch(wybor)
        {
        case '1':
            dodajAdresata(adresaci);
            zapisDoPliku(adresaci,numerUzytkownika);
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
            usunAdresata(adresaci);                                         //coœ dziwnego dodaje po zapisie do Ksiazki Adresowej
            zapisDoPliku(adresaci,numerUzytkownika);
            system("pause");
            break;
        case '6':
            edytujAdresata(adresaci);
            zapisDoPliku(adresaci,numerUzytkownika);
            system("pause");
            break;
        case '7':
            edycjaHasla(uzytkownicy, numerUzytkownika);
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
}

char wczytajZnakZPodmenu()
{
    string wejscie = "";
    char znak = {0};
    while (true)
    {
        getline(cin, wejscie);
        if ( (wejscie[0]=='9') || ((wejscie[0] >= '1') && (wejscie[0] <='7')))
        {
            znak=wejscie[0];
            break;
        }
        cout << "Ta opcja jest nieobslugiwana. Wpisz ponownie cyfre." << endl;
    }
    return znak;
}

void odczytywanieDanychZPliku(vector <Adresat> & adresaci,int numerUzytkownika)
{
    PLIKAdresaci.open("Ksiazka Adresowa.txt",ios::in);
    if (!PLIKAdresaci.good())
    {
        cout << "Nie odnaleziono bazy danych. Tworzenie nowego pliku" << endl;
        PLIKAdresaci.open("Ksiazka Adresowa.txt",ios::out);
        PLIKAdresaci.close();

    }
    string odczytaneLinieZPliku;
    int dlugoscLinii = 0;
    int j = 0;
    while(getline(PLIKAdresaci,odczytaneLinieZPliku))
    {

        dlugoscLinii = odczytaneLinieZPliku.length();
        int sektorDanych = 0;
        int polozeniePoprzedniegoZnaku = 0;

        string tymczasowyString = "";
        for (int i=0; i<=dlugoscLinii; i++)
        {
            if (odczytaneLinieZPliku[i] == '|')
            {

                switch(sektorDanych)
                {

                case 0:
                    adresaci.push_back(Adresat());
                    cout << "j ->"<< j <<endl;
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    adresaci[j].id =  atoi(tymczasowyString.c_str());
                    cout << "adresaci[j].id ->"<< adresaci[j].id <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 1:  //wymaga sprawdzenia czy dany adresat powinien zostac wczytany dla danego uzytkownika
                    //tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    //uzytkownicy[numerUzytkownika].id =  atoi(tymczasowyString.c_str());
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                   break;
                case 2:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].imie = tymczasowyString;
                    cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    cout << "adresaci[j].imie ->"<< adresaci[j].imie <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 3:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].nazwisko = tymczasowyString;
                    cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    cout << "adresaci[j].nazwisko ->"<< adresaci[j].nazwisko <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 4:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].numerTelefonu = tymczasowyString;
                    cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    cout << "adresaci[j].numerTelefonu ->"<< adresaci[j].numerTelefonu <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 5:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].email = tymczasowyString;
                    cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    cout << "adresaci[j].email ->"<< adresaci[j].email <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 6:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].adres = tymczasowyString;
                    cout << "tymczasowyString ->"<< tymczasowyString <<endl;
                    cout << "adresaci[j].adres ->"<< adresaci[j].adres <<endl;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    j++;
                    break;
                }

            }
        }

    }
    PLIKAdresaci.close();
}

void zapisDoPliku (vector <Adresat> & adresaci,int numerUzytkownika)
{
    PLIKAdresaci.open("Ksiazka Adresowa.txt",ios::out);
    int vectorSize = adresaci.size();
    for(int i=0; i<vectorSize; i++)
    {
        PLIKAdresaci<< adresaci[i].id << "|";
        PLIKAdresaci<< numerUzytkownika << "|";
        PLIKAdresaci<< adresaci[i].imie << "|";
        PLIKAdresaci<< adresaci[i].nazwisko << "|";
        PLIKAdresaci<< adresaci[i].numerTelefonu << "|";
        PLIKAdresaci<< adresaci[i].email << "|";
        PLIKAdresaci<< adresaci[i].adres << "|" << endl;
    }
    PLIKAdresaci.close();
}

void dodajAdresata(vector <Adresat> & adresaci)
{
    int wielkoscWektora = adresaci.size();
    int najwyzszyNumerID = 1;
    if (wielkoscWektora != 0)
    {
        najwyzszyNumerID = adresaci.back().id;
        najwyzszyNumerID++;
    }
    adresaci.push_back(Adresat());
    adresaci[wielkoscWektora].id = najwyzszyNumerID;
    string tymczasowyString ="";
    cout << "Podaj imie nowego kontaktu:";
    cin >> tymczasowyString;
    adresaci[wielkoscWektora].imie = tymczasowyString;
    cout << "Podaj nazwisko nowego kontaktu:";
    cin >> tymczasowyString;
    adresaci[wielkoscWektora].nazwisko = tymczasowyString;
    cout << "Podaj numer telefonu nowego kontaktu:";
    cin >> tymczasowyString;
    adresaci[wielkoscWektora].numerTelefonu = tymczasowyString;
    cout << "Podaj email nowego kontaktu:";
    cin >> tymczasowyString;
    adresaci[wielkoscWektora].email = tymczasowyString;
    cout << "Podaj adres nowego kontaktu:";
    cin >> tymczasowyString;
    adresaci[wielkoscWektora].adres = tymczasowyString;

}

void wyszukajAdresataPoImieniu (vector <Adresat> & adresaci)
{
    string imieDoWyszukania = "";
    cout << "Podaj imie do wyszukania" << endl;
    cin >> imieDoWyszukania;
    cout << "Wyswietlam wyniki wyszukiwania imienia: " << imieDoWyszukania << endl;
    bool czyZnalezionoPrzynajmniejJednoImie = 0;
    int vectorSize = adresaci.size();

    for(int i=0; i<vectorSize; i++)
    {
        if (imieDoWyszukania == adresaci[i].imie)
        {
            cout <<adresaci[i].id << " "<< adresaci[i].imie << " " << adresaci[i].nazwisko << " " << adresaci[i].numerTelefonu << " " << adresaci[i].email << " " << adresaci[i].adres << endl;
            czyZnalezionoPrzynajmniejJednoImie = 1;
        }

    }
    cout << endl;
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
    int vectorSize = adresaci.size();
    for(int i=0; i< vectorSize; i++)
    {
        if (nazwiskoDoWyszukania == adresaci[i].nazwisko)
        {
            cout <<adresaci[i].id << " "<< adresaci[i].imie << " " << adresaci[i].nazwisko << " " << adresaci[i].numerTelefonu << " " << adresaci[i].email << " " << adresaci[i].adres << endl;
            czyZnalezionoPrzynajmniejJednoImie = 1;
        }

    }
    cout << endl;
    if (czyZnalezionoPrzynajmniejJednoImie == 0)
    {
        cout << "Brak wynikow w ksiazce adresowej dla nazwiska: " << nazwiskoDoWyszukania << endl << endl;
    }
}

void wyswietlWszystkieKontakty(vector <Adresat> & adresaci)
{
    int vectorSize = adresaci.size();
    for(int i=0; i < vectorSize; i++)
    {
        cout << "Id: "<< adresaci[i].id << endl << "Imie: " << adresaci[i].imie << endl << "Nazwisko: " << adresaci[i].nazwisko << endl << "Numer telefonu: " << adresaci[i].numerTelefonu << endl << "E-mail: " << adresaci[i].email << endl << "Adres: " << adresaci[i].adres << endl << endl;
    }
    cout << endl;
}

void usunAdresata (vector <Adresat> & adresaci)
{

    char takLubNie;
    int komorkaAdresataDoUsuniecia;
    komorkaAdresataDoUsuniecia = sprawdzCzyIDIstnieje(adresaci);

    while (1)
    {
        cout << "Czy na pewno chcesz usunac uzytkownika " << adresaci[komorkaAdresataDoUsuniecia].imie << " " << adresaci[komorkaAdresataDoUsuniecia].nazwisko << "?" << endl;
        cout << "Wybierz z klawiatury y w celu potwierdzenia lub n w celu anulowania." << endl;
        cin >> takLubNie;
        if ((takLubNie == 'y') || (takLubNie == 'Y'))
        {
            adresaci.erase(adresaci.begin()+komorkaAdresataDoUsuniecia);
            break;
        }
        else if ((takLubNie == 'n') || (takLubNie == 'N'))
        {
            break;
        }
    }

}

int sprawdzCzyIDIstnieje(vector <Adresat> & adresaci)
{
    int idAdresataDoUsuniecia;
    int komorkaAdresataDoUsuniecia;
    while (1)
    {
        bool czyZnalezionoNumerID = 0;
        cout << "Podaj id uzytkownika: " << endl;
        cin >> idAdresataDoUsuniecia;
        int vectorSize = adresaci.size();
        for (int i=0; i<vectorSize; i++)
        {
            if (idAdresataDoUsuniecia == adresaci[i].id)
            {
                czyZnalezionoNumerID=1;
                komorkaAdresataDoUsuniecia = i;
            }
        }
        if (czyZnalezionoNumerID == 0)
        {
            cout << "Nie ma takiego numeru ID." << endl;
        }
        else
        {
            break;
        }
    }

    return komorkaAdresataDoUsuniecia;
}

void edytujAdresata (vector <Adresat> & adresaci)
{
    char takLubNie;
    int komorkaAdresataDoEdycji;
    komorkaAdresataDoEdycji = sprawdzCzyIDIstnieje(adresaci);
    string tymczasaowyString = "";

    while (1)
    {
        cout << "Czy na pewno chcesz edytowac uzytkownika " <<"ID:" << adresaci[komorkaAdresataDoEdycji].id << ". "<< adresaci[komorkaAdresataDoEdycji].imie << " " << adresaci[komorkaAdresataDoEdycji].nazwisko << endl;
        cout << adresaci[komorkaAdresataDoEdycji].numerTelefonu << endl;
        cout << adresaci[komorkaAdresataDoEdycji].email << endl;
        cout << adresaci[komorkaAdresataDoEdycji].adres << endl;
        cout << "Wybierz z klawiatury y w celu potwierdzenia lub n w celu anulowania." << endl;
        takLubNie = getch();
        if ((takLubNie == 'y') || (takLubNie == 'Y'))
        {
            cout << "Jaka dana chcialbys edytowac?" << endl;
            cout << "1. Imie"  << endl;
            cout << "2. Nazwisko"  << endl;
            cout << "3. Numer Telefonu"  << endl;
            cout << "4. Email"  << endl;
            cout << "5. Adres"  << endl;
            cout << "6. Anuluj edycje"  << endl;
            cout << "Wybierz"  << endl;
            char wybor;
            cin >> wybor;
            switch(wybor)
            {
            case '1':
                cout << "Wprowadz nowe imie:" << endl;
                cin >> tymczasaowyString;
                adresaci[komorkaAdresataDoEdycji].imie = tymczasaowyString;
                break;
            case '2':
                cout << "Wprowadz nowe nazwisko:" << endl;
                cin >> tymczasaowyString;
                adresaci[komorkaAdresataDoEdycji].nazwisko = tymczasaowyString;
                break;
            case '3':
                cout << "Wprowadz nowy numer telefonu:" << endl;
                cin >> tymczasaowyString;
                adresaci[komorkaAdresataDoEdycji].numerTelefonu = tymczasaowyString;
                break;
            case '4':
                cout << "Wprowadz nowy email:" << endl;
                cin >> tymczasaowyString;
                adresaci[komorkaAdresataDoEdycji].email = tymczasaowyString;
                break;
            case '5':
                cout << "Wprowadz nowy adres:" << endl;
                cin >> tymczasaowyString;
                adresaci[komorkaAdresataDoEdycji].adres = tymczasaowyString;
                break;
            case '6':
                break;
            }
            break;
        }
        else if ((takLubNie == 'n') || (takLubNie == 'N'))
        {
            break;
        }
    }

}

void edycjaHasla (vector <Uzytkownik> & uzytkownicy, int numerUzytkownika)
{
    string tymczasowyString = "";
    cout << "Podaj nowe haslo:" << endl;
    cin >> tymczasowyString;
    uzytkownicy[numerUzytkownika].haslo = tymczasowyString;
    zapisDoPlikuUzytkownicy(uzytkownicy);
}



