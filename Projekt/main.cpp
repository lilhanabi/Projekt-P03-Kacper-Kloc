#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <limits.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

// Funkcja wczytująca dane z pliku
std::vector<int> wczytanie()
{
    std::vector<int> arr;
    ifstream plik("dane.txt");        // Wczytywany plik

    // Sprawdzenie czy plik istnieje i otworzenie go
    if (plik.good())
    {
        // Wczytanie danych do tablicy
        int x = 0;
        while (plik >> x)
        {
            arr.push_back(x);
        }
        // Zamknięcie pliku.
        plik.close();
    }
    else
    {
        cout << "Error!";
        _exit(0);
    }
    return arr;
}
// Funkcja sortująca
void sortuj(std::vector<int>arr, int arrLength)
{
    // Tworzenie pomocniczych zmiennych oraz dynamicznych tablic
    int j = 0, k = 0;
    int* tab1= new int[arrLength];
    int* tab2= new int[arrLength];
    for(int i=0; i<arrLength; i++)
    {
        // Umieszczenie wszystkich elementów tablicy większych lub równych 0 w pierwszej pomocniczej tablicy
        if(arr[i]>=0)
        {
            tab1[j]=arr[i];
            j++;
        }
        // Umieszczenie wszystkich elementów mniejszych od 0 w drugiej pomocniczej tablicy
        else
        {
            tab2[k]=arr[i];
            k++;
        }
    }
    // Połączenie obu pomocniczych tablic w jedną, posortowaną tablicę
    for(int i=0; i<j; i++)
        arr[i]=tab1[i];
    for(int i=0; i<k; i++)
        arr[i+j]=tab2[i];
    // Usunięcie tablic pomocniczych
    delete[] tab1;
    delete[] tab2;
    // Zapis wyniku do pliku wynik.txt
    fstream plik;
     plik.open("zapis liczb.txt",ios::out|ios::app);
    for(int i=0; i<arrLength; i++)
    {
        plik<<arr[i]<<" ";

    }
    plik<<endl;
    plik.close();
}
void sortuj_test(std::vector<int>tab, int arrLength)
{
    // Tworzenie pomocniczych zmiennych oraz dynamicznych tablic
    int j = 0, k = 0;
    int* tab1= new int[arrLength];
    int* tab2= new int[arrLength];
    for(int i=0; i<arrLength; i++)
    {
        // Umieszczenie wszystkich elementów tablicy większych lub równych 0 w pierwszej pomocniczej tablicy
        if(tab[i]>=0)
        {
            tab1[j]=tab[i];
            j++;
        }
        // Umieszczenie wszystkich elementów mniejszych od 0 w drugiej pomocniczej tablicy
        else
        {
            tab2[k]=tab[i];
            k++;
        }
    }
    // Połączenie obu pomocniczych tablic w jedną, posortowaną tablicę
    for(int i=0; i<j; i++)
        tab[i]=tab1[i];
    for(int i=0; i<k; i++)
        tab[i+j]=tab2[i];
    // Usunięcie tablic pomocniczych
    delete[] tab1;
    delete[] tab2;
    fstream plik;
    plik.open("posortowane testy.txt",ios::out|ios::app);
    for (int i = 0; i < arrLength; i++)
    {
        plik<<tab[i]<<" ";
    }
    plik<<endl;
    plik.close();

}
void testy()
{
    int N = 50;
    std::vector<int> tab;
    int liczba_testow = 10;
    std::vector<double> czasA(liczba_testow);
    for (int i=0; i<liczba_testow; i++)
    {
        srand((unsigned)time(NULL));
        fstream plik;
        plik.open("testy.txt",ios::out|ios::app);
        for (int i =0; i < N; i++)
        {
            int b = rand() % 200 - 100;
            tab.push_back(b);

            plik<<tab[i]<<" ";
        }
        plik<<endl;
        plik.close();

        /* testy algorytmu */
        auto start = high_resolution_clock::now();
        sortuj_test(tab, N);

        auto stop = high_resolution_clock::now();
        std::chrono::duration<double> czas = stop-start;
        std::cout << std::setw(9) << czas.count() << " s."<< endl;
        // zwiekszenie rozmiarow tablicy
        N = N * 2 ;
    }
}


int main()
{
    std::vector<int>arr;
    arr=wczytanie();
    // Przypisanie długości vector'a arr do zmiennej
    int arrLength = arr.size();
    cout<<"Wczytano "<<arrLength<<" liczb do tablicy: ";
    for(int i=0; i<arrLength; i++)
        cout<<arr[i]<<" ";



    /* czas wykonania obliczen algorytmem */
    auto start = high_resolution_clock::now();

    sortuj(arr, arrLength);

    auto stop = high_resolution_clock::now();
    std::chrono::duration<double> czas = stop-start;
    std::cout << "Czas obliczen: " <<
              std::setw(9) << czas.count() << " s."<< endl;
    testy();
}
