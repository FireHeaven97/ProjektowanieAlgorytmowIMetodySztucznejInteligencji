#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class Gra
{
    enum class Gracz
    {
        nikt = '-',
        czlowiek = 'X',
        komputer = 'O'
    };

    struct Ruch
    {
        unsigned x = 0;
        unsigned y = 0;
    };

    static const unsigned WYM = 3;  //tu mozna zmienic wymiar planszy

    Gracz plansza[WYM][WYM];
    unsigned pozostale;

public:
    Gra() : pozostale(WYM * WYM)
    {
        for (unsigned i = 0; i < WYM; i++)
        {
            for (unsigned j = 0; j < WYM; j++)
            {
                plansza[i][j] = Gracz::nikt;
            }
        }
    }

    void rozgrywka()
    {
        unsigned tura = 0;
        bool wyjscie = false;

        pokazplansze();
        std::cout << "\n Wprowadz koordynaty [rzad, kolumna]: Przyklad 00. \n";

        do
        {
            if (tura == 0)
            {
                PobierzRuchGracza();

                if (SprawdzWygrana(Gracz::czlowiek))
                {
                    std::cout << "\n Wygrales. \n";
                    wyjscie = true;
                }
            }
            else
            {
                std::cout << "\n Ruch przeciwnika: \n";

                Ruch aiRuch = minimax();

                std::cout << aiRuch.x << aiRuch.y << "\n";

                plansza[aiRuch.x][aiRuch.y] = Gracz::komputer;
                pozostale--;

                if (SprawdzWygrana(Gracz::komputer))
                {
                    std::cout << "\n Komputer wygral. \n";
                    wyjscie = true;
                }
            }

            if (SprawdzRemis())
            {
                std::cout << "\n Remis. \n";
                wyjscie = true;
            }

            tura ^= 1;
            pokazplansze();

        } while (!wyjscie);
    }

    void pokazplansze()
    {
        for (unsigned i = 0; i < WYM; i++)
        {
            std::cout << "\n|";
            for (unsigned j = 0; j < WYM; j++)
            {
                std::cout << std::setw(3) << static_cast<char>(plansza[i][j]) << std::setw(3) << " |";
            }
        }
        std::cout << "\n\n";
    }

    bool SprawdzRemis()
    {
        return pozostale == 0;
    }

    bool SprawdzWygrana(Gracz Gracz)
    {
        for (unsigned i = 0; i < WYM; ++i)
        {
            bool WygranaRzedami = true;
            bool WygranaKolumnami = true;
            for (unsigned j = 0; j < WYM; ++j)
            {
                WygranaRzedami &= plansza[i][j] == Gracz;
                WygranaKolumnami &= plansza[j][i] == Gracz;
            }
            if (WygranaKolumnami || WygranaRzedami)
                return true;
        }

        bool WygranaNaUkos = true;
        for (unsigned i = 0; i < WYM; ++i)
            WygranaNaUkos &= plansza[i][i] == Gracz;

        if (WygranaNaUkos)
            return true;

        WygranaNaUkos = true;
        for (unsigned i = 0; i < WYM; ++i)
            WygranaNaUkos &= plansza[WYM - i - 1][i] == Gracz;

        return WygranaNaUkos;
    }


    Ruch minimax()
    {
        int Wynik = std::numeric_limits<int>::max();
        Ruch Ruch;
        int Poziom = 0;

        for (unsigned i = 0; i < WYM; i++)
        {
            for (unsigned j = 0; j < WYM; j++)
            {
                if (plansza[i][j] == Gracz::nikt)
                {
                    plansza[i][j] = Gracz::komputer;
                    pozostale--;

                    int temp = MaxWyszukiwanie(Poziom, numeric_limits<int>::min(), numeric_limits<int>::max());

                    if (temp < Wynik)
                    {
                        Wynik = temp;
                        Ruch.x = i;
                        Ruch.y = j;
                    }

                    plansza[i][j] = Gracz::nikt;
                    pozostale++;
                }
            }
        }

        return Ruch;
    }

    int MaxWyszukiwanie(int Poziom, int Alfa, int Beta)
    {
        if (SprawdzWygrana(Gracz::czlowiek)) { return 10; }
        else if (SprawdzWygrana(Gracz::komputer)) { return -10; }
        else if (SprawdzRemis()) { return 0; }

        int Wynik = numeric_limits<int>::min();

        for (unsigned i = 0; i < WYM; i++)
        {
            for (unsigned j = 0; j < WYM; j++)
            {
                if (plansza[i][j] == Gracz::nikt)
                {
                    plansza[i][j] = Gracz::czlowiek;
                    pozostale--;

                    Wynik = std::max(Wynik, MinWyszukiwanie(Poziom + 1, Alfa, Beta) - Poziom);
                    Alfa = std::max(Alfa, Wynik);

                    plansza[i][j] = Gracz::nikt;
                    pozostale++;

                    if (Beta <= Alfa) return Alfa;
                }
            }
        }

        return Wynik;
    }

    int MinWyszukiwanie(int Poziom, int Alfa, int Beta)
    {
        if (SprawdzWygrana(Gracz::czlowiek)) { return 10; }
        else if (SprawdzWygrana(Gracz::komputer)) { return -10; }
        else if (SprawdzRemis()) { return 0; }

        int Wynik = numeric_limits<int>::max();

        for (unsigned i = 0; i < WYM; i++)
        {
            for (unsigned j = 0; j < WYM; j++)
            {
                if (plansza[i][j] == Gracz::nikt)
                {
                    plansza[i][j] = Gracz::komputer;
                    pozostale--;

                    Wynik = std::min(Wynik, MaxWyszukiwanie(Poziom + 1, Alfa, Beta) + Poziom);
                    Beta = std::min(Beta, Wynik);

                    plansza[i][j] = Gracz::nikt;
                    pozostale++;

                    if (Beta <= Alfa) return Beta;
                }
            }
        }

        return Wynik;
    }

    void PobierzRuchGracza()
    {
        bool Porazka = true;
        unsigned x = -1, y = -1;

        do
        {
            std::cout << "\n Twoj ruch: \n";

            char koordynaty;
            cin >> koordynaty;
            x = koordynaty - '0';
            cin >> koordynaty;
            y = koordynaty - '0';

            Porazka = plansza[x][y] != Gracz::nikt;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (Porazka);

        plansza[x][y] = Gracz::czlowiek;
        pozostale--;
    }
};

int main()
{
    char Znak;
    do
    {
    Gra KolkoiKrzyzyk;
    KolkoiKrzyzyk.rozgrywka();
    std::cin.ignore();cout <<"\n Chcialbys zagrac jeszcze raz: t/n? \n";
    cin>>Znak;
    system("cls");
  } while (Znak!='n');
  return 0;
}
