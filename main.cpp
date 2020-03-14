#include <iostream>

using namespace std;

class Nod
{
private:
    int info;
    Nod* next;

public:
    Nod()
    {
        next = NULL;
    }
    Nod(int data)
    {
        this -> info = data;
        this -> next = NULL;
    }
    Nod(int data, Nod* next)
    {
        this -> info = data;
        this -> next = next;
    }
    int getInfo()
    {
        return info;
    }
    Nod* getNext()
    {
        return next;
    }
    void setInfo(int info)
    {
        this -> info = info;
    }
    void setNext(Nod* next)
    {
        this -> next = next;
    }
    ~Nod()
    {

    }
};

class ListaCirculara
{
private:
    Nod* prim;
    Nod* ultim;


    ///functie care returneaza numarul de noduri al listei
    int nr_noduri()
    {
        if(prim == NULL)
            return 0;
        else if(prim == ultim)
            return 1;
        else
        {
            int cnt = 0;
            Nod* p = new Nod();
            for( p = prim; p -> getNext() != prim; p = p -> getNext() )
                cnt++;

            cnt++;
            return cnt;
        }
    }


public:
    ListaCirculara()
    {
        prim = NULL;
        ultim = NULL;
    }


    void inserare_pozitie(int poz, int data)
    {
        int nr = nr_noduri();
        if(poz > nr + 1)
        {
            cout << "Nu sunt suficiente elemente in lista";
            return;
        }

        if(poz == 1) ///inserarea unui element la inceputul listei
        {
            if(prim == NULL)
            {
                prim = new Nod(data, prim);
                ultim = prim;
            }
            else
            {
                Nod* aux = new Nod(data, prim);
                prim = aux;
                ultim -> setNext(prim);
            }
        }

        else if(poz == nr + 1) ///inserare unui element la finalul listei
        {
            Nod* aux = new Nod(data, prim);
            ultim -> setNext(aux);
            ultim = aux;
        }

        else ///inserarea unui element in interiorul listei
        {
            int cnt = 1;
            Nod* p = new Nod();
            p = prim;
            while( p -> getNext() != prim && cnt != poz - 1)
            {
                p = p -> getNext();
                cnt++;
            }

            Nod* aux = new Nod(data, p -> getNext());
            p -> setNext(aux);

        }
    }


    ///functie care afiseaza lista
    void iterareLista()
    {
        if(prim == NULL)
        {
            cout << "LISTA VIDA!\n";
            return;
        }

        if(prim == ultim)
        {
            cout << prim -> getInfo() << " ";
            return;
        }

        Nod* curr = prim;
        while(curr -> getNext() != prim)
        {
            cout << curr -> getInfo() << " ";
            curr = curr -> getNext();
        }
        cout << ultim -> getInfo() << " ";
    }

};


int main()
{
    ListaCirculara l;
    l.inserare_pozitie(1, 1);
    l.inserare_pozitie(2, 2);
    l.inserare_pozitie(3, 3);
    l.inserare_pozitie(1, 4);
    l.inserare_pozitie(2, 5);
    // cout << l.nr_noduri() << "\n\n\n";
    l.iterareLista();

    return 0;
}
