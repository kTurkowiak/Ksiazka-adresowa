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
fstream PLIKAdresacitymczasowy;

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
void zapisDoPliku (vector <Adresat> & adresaci,int numerUzytkownika, int IDDoUsuniecia);
void dodajAdresata(vector <Adresat> & adresaci);
int wyliczenieNajwyzszegoNumeruID (vector <Adresat> & adresaci);
string wczytajLinie();
void wyszukajAdresataPoNazwisku(vector <Adresat> & adresaci);
void wyszukajAdresataPoImieniu (vector <Adresat> & adresaci);
void wyswietlWszystkieKontakty(vector <Adresat> & adresaci);
int usunAdresata (vector <Adresat> & adresaci);
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
    for (int i = 0; i<vectorSize ; i++)
    {
        if ((uzytkownicy[i].login == tymczasowyLogin) && (uzytkownicy[i].haslo == tymczasoweHaslo))
        {
            cout << "Udalo sie zalogowac" << endl;
            system ("pause");
            menuGlowne(uzytkownicy,i);
            zalogowanie = 1;
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
    cout << "Zarejestrowano uzytkownika" << endl;
    system("pause");
}

void zapisDoPlikuUzytkownicy(vector <Uzytkownik> & uzytkownicy)
{
    PLIKUzytkownicy.open("Uzytkownicy.txt",ios::out);
    int vectorSize = uzytkownicy.size();
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
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    uzytkownicy[j].id =  atoi(tymczasowyString.c_str());
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 1:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    uzytkownicy[j].login = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 2:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    uzytkownicy[j].haslo = tymczasowyString;
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
    odczytywanieDanychZPliku(adresaci, numerUzytkownika);
    int IDDoUsuniecia = 0;

    while (1)
    {
        system("cls");
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
            zapisDoPliku(adresaci,numerUzytkownika,IDDoUsuniecia);
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
            IDDoUsuniecia = usunAdresata(adresaci);
            zapisDoPliku(adresaci,numerUzytkownika,IDDoUsuniecia);
            system("pause");
            break;
        case '6':
            edytujAdresata(adresaci);
            zapisDoPliku(adresaci,numerUzytkownika,IDDoUsuniecia);
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
        else if (wejscie.length() == 1)
        {
            cout << "Ta opcja jest nieobslugiwana. Wpisz ponownie cyfre." << endl;
        }
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
        int IDUzytkownika = 0;
        string tymczasowyStringID = "";
        for (int i=0; i<=dlugoscLinii; i++)
        {
            if (odczytaneLinieZPliku[i] == '|')
            {
                switch(sektorDanych)
                {
                case 0:
                    tymczasowyStringID = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 1:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    IDUzytkownika = atoi(tymczasowyString.c_str());
                    if (IDUzytkownika != (int) numerUzytkownika)
                    {
                        i = dlugoscLinii;
                        sektorDanych = 6;
                        break;
                    }
                    adresaci.push_back(Adresat());
                    adresaci[j].id =  atoi(tymczasowyStringID.c_str());
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 2:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].imie = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 3:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].nazwisko = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 4:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].numerTelefonu = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 5:
                    tymczasowyString = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    adresaci[j].email = tymczasowyString;
                    polozeniePoprzedniegoZnaku = i+1;
                    sektorDanych++;
                    break;
                case 6:
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
    PLIKAdresaci.close();
}

void zapisDoPliku (vector <Adresat> & adresaci,int numerUzytkownika, int IDDoUsuniecia)
{
    PLIKAdresacitymczasowy.open("Ksiazka Adresowa tymczasowy.txt",ios::out);
    PLIKAdresaci.open("Ksiazka Adresowa.txt",ios::in);
    string odczytaneLinieZPliku;
    int dlugoscLinii = 0;
    int tymczasowyStringIntID = 0;
    int i = 0;
    while(getline(PLIKAdresaci,odczytaneLinieZPliku))
    {
        dlugoscLinii = odczytaneLinieZPliku.length();
        int sektorDanych = 0;
        int polozeniePoprzedniegoZnaku = 0;
        string tymczasowyStringID = "";
        for (int j=0; j<=dlugoscLinii; j++)
        {
            if (odczytaneLinieZPliku[j] == '|')
            {
                switch(sektorDanych)
                {
                case 0:
                    tymczasowyStringID = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, j-polozeniePoprzedniegoZnaku);
                    tymczasowyStringIntID = atoi(tymczasowyStringID.c_str());
                    polozeniePoprzedniegoZnaku = j+1;
                    j = dlugoscLinii;
                    break;
                }
            }
        }
        if (tymczasowyStringIntID == adresaci[i].id)
        {
            PLIKAdresacitymczasowy << adresaci[i].id << "|";
            PLIKAdresacitymczasowy << numerUzytkownika << "|";
            PLIKAdresacitymczasowy << adresaci[i].imie << "|";
            PLIKAdresacitymczasowy << adresaci[i].nazwisko << "|";
            PLIKAdresacitymczasowy << adresaci[i].numerTelefonu << "|";
            PLIKAdresacitymczasowy << adresaci[i].email << "|";
            PLIKAdresacitymczasowy << adresaci[i].adres << "|" << endl;
            i++;
        }
        else if (tymczasowyStringIntID == IDDoUsuniecia)
        {
            continue;
        }
        else
        {
            PLIKAdresacitymczasowy << odczytaneLinieZPliku << endl;
        }

    }
    int vectorSize = adresaci.size();
    if (i<vectorSize)
    {
        PLIKAdresacitymczasowy << adresaci[i].id << "|";
        PLIKAdresacitymczasowy << numerUzytkownika << "|";
        PLIKAdresacitymczasowy << adresaci[i].imie << "|";
        PLIKAdresacitymczasowy << adresaci[i].nazwisko << "|";
        PLIKAdresacitymczasowy << adresaci[i].numerTelefonu << "|";
        PLIKAdresacitymczasowy << adresaci[i].email << "|";
        PLIKAdresacitymczasowy << adresaci[i].adres << "|" << endl;
    }
    PLIKAdresacitymczasowy.close();
    PLIKAdresaci.close();
    remove("Ksiazka Adresowa.txt");
    rename("Ksiazka Adresowa tymczasowy.txt","Ksiazka Adresowa.txt");
}


void dodajAdresata(vector <Adresat> & adresaci)
{
    int wielkoscWektora = adresaci.size();
    int najwyzszyNumerID = wyliczenieNajwyzszegoNumeruID(adresaci);
    najwyzszyNumerID++;
    adresaci.push_back(Adresat());
    adresaci[wielkoscWektora].id = najwyzszyNumerID;
    string tymczasowyString ="";
    cout << "Podaj imie nowego kontaktu:";
    tymczasowyString = wczytajLinie();
    adresaci[wielkoscWektora].imie = tymczasowyString;
    cout << "Podaj nazwisko nowego kontaktu:";
    tymczasowyString = wczytajLinie();
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
    cout << "Zarejestrowano nowy kontakt:";
    system("pause");
}

int wyliczenieNajwyzszegoNumeruID (vector <Adresat> & adresaci)
{
    int tymczasowyStringInt = 0;
    PLIKAdresaci.open("Ksiazka Adresowa.txt",ios::in);
    string odczytaneLinieZPliku;
    int dlugoscLinii = 0;
    while(getline(PLIKAdresaci,odczytaneLinieZPliku))
    {
        dlugoscLinii = odczytaneLinieZPliku.length();
        int sektorDanych = 0;
        int polozeniePoprzedniegoZnaku = 0;
        string tymczasowyStringID = "";
        for (int i=0; i<=dlugoscLinii; i++)
        {
            if (odczytaneLinieZPliku[i] == '|')
            {
                switch(sektorDanych)
                {
                case 0:
                    tymczasowyStringID = odczytaneLinieZPliku.substr(polozeniePoprzedniegoZnaku, i-polozeniePoprzedniegoZnaku);
                    tymczasowyStringInt = atoi(tymczasowyStringID.c_str());
                    polozeniePoprzedniegoZnaku = i+1;
                    i = dlugoscLinii;
                    break;
                }

            }
        }
    }
    PLIKAdresaci.close();
    return tymczasowyStringInt;
}

string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline (cin, wejscie);
    return wejscie;
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

int usunAdresata (vector <Adresat> & adresaci) // nie usuwa adresata bo zapisuje dane przechowywane w pliku tymczasowym
{
    char takLubNie;
    int komorkaAdresataDoUsuniecia;
    int kontaktDoUsuniecia;
    komorkaAdresataDoUsuniecia = sprawdzCzyIDIstnieje(adresaci);
    while (1)
    {
        cout << "Czy na pewno chcesz usunac kontakt " << adresaci[komorkaAdresataDoUsuniecia].imie << " " << adresaci[komorkaAdresataDoUsuniecia].nazwisko << "?" << endl;
        cout << "Wybierz z klawiatury y w celu potwierdzenia lub n w celu anulowania." << endl;
        cin >> takLubNie;
        if ((takLubNie == 'y') || (takLubNie == 'Y'))
        {   kontaktDoUsuniecia = adresaci[komorkaAdresataDoUsuniecia].id;
            adresaci.erase(adresaci.begin()+komorkaAdresataDoUsuniecia);
            return kontaktDoUsuniecia;
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
        cout << "Podaj id kontaktu: " << endl;
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
    string tymczasowyString = "";

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
                tymczasowyString = wczytajLinie();
                adresaci[komorkaAdresataDoEdycji].imie = tymczasowyString;
                break;
            case '2':
                cout << "Wprowadz nowe nazwisko:" << endl;
                tymczasowyString = wczytajLinie();
                adresaci[komorkaAdresataDoEdycji].nazwisko = tymczasowyString;
                break;
            case '3':
                cout << "Wprowadz nowy numer telefonu:" << endl;
                tymczasowyString = wczytajLinie();
                adresaci[komorkaAdresataDoEdycji].numerTelefonu = tymczasowyString;
                break;
            case '4':
                cout << "Wprowadz nowy email:" << endl;
                tymczasowyString = wczytajLinie();
                adresaci[komorkaAdresataDoEdycji].email = tymczasowyString;
                break;
            case '5':
                cout << "Wprowadz nowy adres:" << endl;
                tymczasowyString = wczytajLinie();
                adresaci[komorkaAdresataDoEdycji].adres = tymczasowyString;
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



