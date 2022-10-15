#include<iostream>
using namespace std;

struct wezel_avl
{
    int dane;
    int wysokosc;
    struct wezel_avl *lewo;
    struct wezel_avl *prawo;

}* korzen;

class drzewo_avl
{
    public:
        int wysokosc(wezel_avl *);
        int roznica(wezel_avl *);
        wezel_avl *rr_rotacja(wezel_avl *);
        wezel_avl *ll_rotacja(wezel_avl *);
        wezel_avl *lr_rotacja(wezel_avl *);
        wezel_avl *rl_rotacja(wezel_avl *);
        wezel_avl* balans(wezel_avl *);
        wezel_avl* dodaj(wezel_avl *, int );
        wezel_avl* ZnajdzMin(wezel_avl* );
        wezel_avl* ZnajdzMax(wezel_avl* );
        void wyswietl(wezel_avl *);
        void inorder(wezel_avl *);
        void preorder(wezel_avl *);
        void postorder(wezel_avl *);
        wezel_avl* usun(int , wezel_avl* );
        drzewo_avl()
        {
            korzen = NULL;
        }
};

int main()
{
    int wybor, wybrane;
    drzewo_avl drzewo;
    while (1)
    {
    	cout<<endl;
        cout<<"Drzewo AVL: "<<endl;
        cout<<"1. Dodaj element do drzewa"<<endl;
        cout<<"2. Usun element z drzewa"<<endl;
        cout<<"3. Wyswietl zbalansowane drzewo AVL"<<endl;
        cout<<"4. Wyswietl wysokosc drzewa"<<endl;
        cout<<"5. Przejscie inorder"<<endl;
        cout<<"6. Przejscie preorder"<<endl;
        cout<<"7. Przejscie postorder"<<endl;
        cout<<"8. Wyjscie"<<endl;
        cout<<"Podaj swoj wybor: ";
        cin>>wybor;
        switch(wybor)
        {
        case 1:
            cout<<"Wpisz wartosc do dodania: ";
            cin>>wybrane;
            korzen = drzewo.dodaj(korzen, wybrane);
            break;
        case 2:
              cout<<"Wpisz wartosc do usuniecia: ";
              cin>>wybrane;
              korzen = drzewo.usun(wybrane,korzen);
              break;
        case 3:
            if (korzen == NULL)
            {
            	cout<<endl;
                cout<<"Drzewo jest puste."<<endl;
                continue;
            }
            cout<<endl;
            cout<<"Zbalansowane drzewo AVL: "<<endl;
              drzewo.wyswietl(korzen);
            break;
        case 4:
           	  cout<<endl;
              cout<<"Wysokosc drzewa: ";
              cout<<drzewo.wysokosc(korzen)<<endl;
              break;
        case 5:
        	cout<<endl;
            cout<<"Rotacja inorder: "<<endl;
            drzewo.inorder(korzen);
            cout<<endl;
            break;
        case 6:
        	cout<<endl;
            cout<<"Rotacja preorder: "<<endl;
            drzewo.preorder(korzen);
            cout<<endl;
            break;
        case 7:
        	cout<<endl;
            cout<<"Rotacja postorder: "<<endl;
            drzewo.postorder(korzen);
            cout<<endl;
            break;
        case 8:
            exit(1);
            break;
        default:
        	cout<<endl;
            cout<<"Zly wybor."<<endl;
        }
    }
    return 0;
}

int drzewo_avl::wysokosc(wezel_avl *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int lewo_wysokosc = wysokosc (temp->lewo);
        int prawo_wysokosc = wysokosc (temp->prawo);
        int max_wysokosc = max (lewo_wysokosc, prawo_wysokosc);
        h = max_wysokosc +1;
    }
    return h;
}

int drzewo_avl::roznica(wezel_avl *temp)
{
    int lewo_wysokosc = wysokosc (temp->lewo);
    int prawo_wysokosc = wysokosc (temp->prawo);
    int b_factor= lewo_wysokosc - prawo_wysokosc;
    return b_factor;
}

wezel_avl *drzewo_avl::rr_rotacja(wezel_avl *rodzic)
{
    wezel_avl *temp;
    temp = rodzic->prawo;
    rodzic->prawo = temp->lewo;
    temp->lewo = rodzic;
    return temp;
}

wezel_avl *drzewo_avl::ll_rotacja(wezel_avl *rodzic)
{
    wezel_avl *temp;
    temp = rodzic->lewo;
    rodzic->lewo = temp->prawo;
    temp->prawo = rodzic;
    return temp;
}

wezel_avl *drzewo_avl::lr_rotacja(wezel_avl *rodzic)
{
    wezel_avl *temp;
    temp = rodzic->lewo;
    rodzic->lewo = rr_rotacja (temp);
    return ll_rotacja (rodzic);
}

wezel_avl *drzewo_avl::rl_rotacja(wezel_avl *rodzic)
{
    wezel_avl *temp;
    temp = rodzic->prawo;
    rodzic->prawo = ll_rotacja (temp);
    return rr_rotacja (rodzic);
}

wezel_avl *drzewo_avl::balans(wezel_avl *temp)
{
    int balans_factor = roznica (temp);
    if (balans_factor > 1)
    {
        if (roznica (temp->lewo) > 0)
            temp = ll_rotacja (temp);
        else
            temp = lr_rotacja (temp);
    }
    else if (balans_factor < -1)
    {
        if (roznica (temp->prawo) > 0)
            temp = rl_rotacja (temp);
        else
            temp = rr_rotacja (temp);
    }
    return temp;
}

wezel_avl *drzewo_avl::dodaj(wezel_avl *korzen, int wartosc)
{
    if (korzen == NULL)
    {
        korzen = new wezel_avl;
        korzen->dane = wartosc;
        korzen->lewo = NULL;
        korzen->prawo = NULL;
        return korzen;
    }
    else if (wartosc < korzen->dane)
    {
        korzen->lewo = dodaj(korzen->lewo, wartosc);
        korzen = balans (korzen);
    }
    else if (wartosc >= korzen->dane)
    {
        korzen->prawo = dodaj(korzen->prawo, wartosc);
        korzen = balans (korzen);
    }
    return korzen;
}

wezel_avl* drzewo_avl::usun(int x, wezel_avl* t)
{
    wezel_avl* temp;

    if(t == NULL)
        return NULL;

    else if(x < t->dane)
    {
        t->lewo = usun(x, t->lewo);
    }
    else if(x > t->dane)
    {
        t->prawo = usun(x, t->prawo);
    }

    else if(t->lewo && t->prawo)
    {
        temp = ZnajdzMin(t->lewo);
        t->dane = temp->dane;
        t->lewo = usun(t->dane, t->lewo);
    }
    else if(t->lewo && t->prawo)
    {
      temp = ZnajdzMin(t->prawo);
      t->dane = temp->dane;
      t->prawo = usun(t->dane, t->prawo);
    }
    
    else
    {
        temp = t;
        if(t->lewo == NULL)
        {
            t = t->prawo;
        }
        else if(t->prawo == NULL)
        {
            t = t->lewo;
        }
        delete temp;
    }
    if(t == NULL)
        return t;

    if(wysokosc(t->lewo) - wysokosc(t->prawo) == 2)
    {
      t=balans(t);
    }
    
    else if(wysokosc(t->prawo) - wysokosc(t->lewo) == 2)
    {
      t=balans(t);
    }
    return t;
}

wezel_avl* drzewo_avl::ZnajdzMin(wezel_avl* t)
{
    if(t == NULL)
        return NULL;
    else if(t->lewo == NULL)
        return t;
    else
        return ZnajdzMin(t->lewo);
}

wezel_avl* drzewo_avl::ZnajdzMax(wezel_avl* t)
{
    if(t == NULL)
        return NULL;
    else if(t->prawo == NULL)
        return t;
    else
        return ZnajdzMax(t->prawo);
}

void drzewo_avl::wyswietl(wezel_avl *ptr)
{
  cout << ptr->dane << " : lewy syn-> ";
  if(ptr->lewo) cout << ptr->lewo->dane;
  else        cout << "brak";
  cout << ", prawy syn-> ";
  if(ptr->prawo) cout << ptr->prawo->dane;
  else         cout << "brak";
  cout << endl;
  if(ptr->lewo)  wyswietl(ptr->lewo);
  if(ptr->prawo) wyswietl(ptr->prawo);
  }

void drzewo_avl::inorder(wezel_avl *drzewo)
{
    if (drzewo == NULL)
        return;
    inorder (drzewo->lewo);
    cout<<drzewo->dane<<"  ";
    inorder (drzewo->prawo);
}

void drzewo_avl::preorder(wezel_avl *drzewo)
{
    if (drzewo == NULL)
        return;
    cout<<drzewo->dane<<"  ";
    preorder (drzewo->lewo);
    preorder (drzewo->prawo);

}

void drzewo_avl::postorder(wezel_avl *drzewo)
{
    if (drzewo == NULL)
        return;
    postorder ( drzewo ->lewo );
    postorder ( drzewo ->prawo );
    cout<<drzewo->dane<<"  ";
}
