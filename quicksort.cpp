#include <iostream>
#include <time.h>
#include <windows.h>
#include <algorithm>

using namespace std;

int ile;
clock_t start,stop;
double czas;

void quicksort(int *tablica, int lewy, int prawy)
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
    if(j>lewy) quicksort(tablica,lewy, j);
    if(i<prawy) quicksort(tablica, i, prawy);
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
    int i,j;
    cout<<"Ile losowych liczb w tablicy: ";
    cin>>ile;
    int *tablica;
    tablica=new int [ile];
    int *tablica2;
    tablica2=new int [ile];
    srand(time(NULL));
    for(int i=0; i<ile; i++)
    {
        tablica[i] = rand();
    }
    for(int i=0; i<ile; i++)
    {
       tablica2[i]=tablica[i];
    }
    cout.setf(ios::fixed);
    cout.precision(5);
    start = clock();
    quicksort(tablica2, 0, ile-1);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania quicksort: "<<czas<<" s"<<endl;
    
    if ( CzyRosnie(tablica2, ile) ) {
        cout << "Szereg rosnie. " << endl;
    } else {
        cout << "Szereg nie rosnie. " << endl;
    }

    delete [] tablica;
    delete [] tablica2;

    return 0;
}
