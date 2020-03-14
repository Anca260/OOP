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

    ///functie care insereaza un element pe o anumita pozitie
    void inserare_pozitie(int poz, int data)
    {
        int nr = nr_noduri();
        if(poz > nr + 1)
        {
            cout << "Valoarea introdusa ca pozitie este incorecta.\n";
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



    ///functie care efectueaza stergerea unui element de pe o anumita pozitie
    void stergere_pozitie(int poz)
    {
        int nr = nr_noduri();
        if(poz > nr)
        {
            cout << "Valoarea introdusa ca pozitie este incorecta.\n";
            return;
        }


        if(poz == 1) ///stergerea primului element al listei
        {
            if(prim == NULL)
            {
                cout << "LISTA VIDA!";
            }
            else if (prim == ultim)
            {
                delete prim;
                prim = NULL;
                ultim = NULL;
            }
            else
            {
                Nod* temp = prim;
                ultim->setNext(temp->getNext());
                prim = temp -> getNext();
                delete temp;
            }
        }

        else if(poz == nr) ///stergerea uktimului element al listei
        {
            ///determinam predecesorul ultimului nod al listei
            Nod* ante = new Nod();
            for( ante = prim; ante -> getNext() != ultim; ante = ante -> getNext() );

            ante -> setNext(prim);
            delete ultim;
            ultim = ante;
        }

        else ///stergerea unui element din interiorul listei
        {
            ///determinam nodul de pe pozitia "poz - 1"
            Nod* ante = new Nod();
            ante = prim;
            int cnt = 1;
            while(cnt != poz - 1)
            {
                ante = ante -> getNext();
                cnt++;
            }

            Nod* curr = new Nod();
            Nod* post = new Nod();
            curr = ante -> getNext();
            post = curr -> getNext();

            ante -> setNext(post);
            delete curr;


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
    l.iterareLista();
    cout << "\n\n\n";
    l.stergere_pozitie(1);
    l.iterareLista();
    cout << "\n\n\n";
    l.stergere_pozitie(4);
    l.iterareLista();
    cout << "\n\n\n";
    l.inserare_pozitie(1, 8);
    l.stergere_pozitie(2);
    l.iterareLista();

    return 0;
}
