#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

void merge(int tablica1[], int start, int srodek, int koniec)
{
int *tab_pom = new int[(koniec-start+1)];
int i = start, j = srodek+1, k = 0;

while (i <= srodek && j <= koniec)
{
if (tablica1[i] < tablica1[j])
{
	tab_pom[k] = tablica1[i];
	i++;
}
else
{
	tab_pom[k] = tablica1[j];
	j++;
}
	k++;
}

if (i <= srodek)
{
	while (i <= srodek)
	{
		tab_pom[k] = tablica1[i];
		i++;
		k++;
	}
}
else
{
while (j <= koniec)
{
	tab_pom[k] = tablica1[j];
	j++;
	k++;
}
}

for (i = 0; i <= koniec-start; i++)
tablica1[start+i] = tab_pom[i];
}

void merge_sort(int tablica1[], int start, int koniec)
{
int srodek;
if (start != koniec)
{
srodek = (start + koniec)/2;
merge_sort(tablica1, start, srodek);
merge_sort(tablica1, srodek+1, koniec);
merge(tablica1, start, srodek, koniec);
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

  int *tablica1 = new int [ile];
  for (int i = 0; i <ile; i++)
  {
    tablica1[i]=rand ();
  }

  cout << "Po sortowaniu mergesort. \n";
	merge_sort(tablica1, 0, ile-1);
  koniec=clock();
  roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
  cout<<"Czas wykonania: "<<roznica<<endl;

	if ( CzyRosnie(tablica1, ile) ) {
        cout << "Szereg rosnie. " << endl;
    } else {
        cout << "Szereg nie rosnie. " << endl;
	}

  delete [] tablica1;
}
