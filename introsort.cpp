#include <cmath>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

static int Podzial(int* tablica, int lewy, int prawy)
{
    int v=tablica[(lewy+prawy)/2];
    int i,j,x;
    i=lewy;
    j=prawy;
    do
    {
        while(tablica[i]<v) i++;
        while(tablica[j]>v) j--;
        if(i<=j)
        {
            x=tablica[i];
            tablica[i]=tablica[j];
            tablica[j]=x;
            i++;
            j--;
        }
    }
		while(i<=j);
	}
		void quicksort(int*tablica, int lewy, int prawy)
		{
			int i,j;
			i=lewy;
			j=prawy;
			int v = Podzial(tablica,lewy,prawy);
    	if(j>lewy) quicksort(tablica,lewy, j);
    	if(i<prawy) quicksort(tablica, i, prawy);
		}

static void MaksymalneKopcowanie(int* tablica, int RozmiarKopca, int indeks) {
	int lewy = (indeks + 1) * 2 - 1;
	int prawy = (indeks + 1) * 2;
	int najwiekszy = 0;
	if (lewy < RozmiarKopca && tablica[lewy] > tablica[indeks])
		najwiekszy = lewy;
	else
		najwiekszy = indeks;
	if (prawy < RozmiarKopca && tablica[prawy] > tablica[najwiekszy])
		najwiekszy = prawy;

	if (najwiekszy != indeks)
	{
		int temp = tablica[indeks];
		tablica[indeks] = tablica[najwiekszy];
		tablica[najwiekszy] = temp;

		MaksymalneKopcowanie(tablica, RozmiarKopca, najwiekszy);
	}
}

static void HeapSort(int* tablica, int count) {
	int RozmiarKopca = count;

	for (int p = (RozmiarKopca - 1) / 2; p >= 0; --p)
		MaksymalneKopcowanie(tablica, RozmiarKopca, p);
	for (int i = count - 1; i > 0; --i)
	{
		int temp = tablica[i];
		tablica[i] = tablica[0];
		tablica[0] = temp;

		--RozmiarKopca;
		MaksymalneKopcowanie(tablica, RozmiarKopca, 0);
	}
}

static void InsertionSort(int* tablica, int ile) {
	int i, j, tmp;

	      for (i = 1; i < ile; i++) {

	            j = i;

	            while (j > 0 && tablica[j - 1] > tablica[j]) {

	                  tmp = tablica[j];

	                  tablica[j] = tablica[j - 1];

	                  tablica[j - 1] = tmp;

	                  j--;

	            }

	      }

	}

static void IntroSort(int* tablica, int count) {
	int RozmiarPodzialu = Podzial(tablica, 0, count - 1);

	if (RozmiarPodzialu < 16)
	{
		InsertionSort(tablica, count);
	}
	else if (RozmiarPodzialu >(2 * log(count)))
	{
		HeapSort(tablica, count);
	}
	else
	{
		quicksort(tablica, 0, count - 1);
	}
}

bool CzyRosnie(int tablica[], int ile) {
    for (int i = 0; i < ile - 1; i++) {
        if (tablica[i] > tablica[i+1]) {
            return false;
        }
    }
    return true;
}

int main()
{
  int ile, i, j;
  double roznica;
  srand(time(NULL));
  cout << "Podaj ilosc licz do posortowania: ";
  cin >> ile;


  cout.setf(ios::fixed);
  cout.precision(5);
  clock_t start, koniec;
  start=clock();

  int *tablica = new int [ile];
  for(i=0; i<ile; i++)
  		 tablica[i] = rand(); 

	IntroSort(tablica, ile);
  cout<<"Po sortowaniu Introspektywnym. \n";
   koniec=clock();
   roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
   cout<<"Czas wykonania: "<<roznica<<endl;

   if ( CzyRosnie(tablica, ile) ) {
        cout << "Szereg roœnie. " << endl;
    } else {
        cout << "Szereg nie roœnie. " << endl;
   }

  delete [] tablica;

	return 0;
}
