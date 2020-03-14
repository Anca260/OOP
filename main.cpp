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


    ///functie care citeste elementele si le introduce in lista
    void citire(istream & in)
    {
        cout << "Introduceti numarul de noduri de adaugat in lista: ";
        int nr;
        in >> nr;

        cout << "\nIntroduceti cele " << nr << " valori ale nodurilor: \n";
        int cnt, val;
        for(cnt = 1; cnt <= nr; cnt++)
        {
            in >> val;
            inserare_pozitie(cnt, val);
        }

    }

    ///functie care afiseaza lista
    void iterareLista(ostream & out)
    {
        if(prim == NULL)
        {
            out << "\nLISTA VIDA!";
            return;
        }

        if(prim == ultim)
        {
            out << "\nLista este: { " << prim -> getInfo() << " }";
            return;
        }

        out << "\nLista este: { ";
        Nod* curr = prim;
        while(curr -> getNext() != prim)
        {
            out << curr -> getInfo() << " -> ";
            curr = curr -> getNext();
        }
        out << ultim -> getInfo() << " -> " << prim -> getInfo() << " }";
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
            cout << "\nValoarea introdusa ca pozitie este incorecta.\n";
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


    ///supraincarcarea operatorului >>
    friend istream & operator >> (istream & in, ListaCirculara & lc)
    {
        lc.citire(in);
        return in;
    }



    ///functie care efectueaza stergerea unui element de pe o anumita pozitie
    void stergere_pozitie(int poz)
    {
        int nr = nr_noduri();
        if(poz > nr)
        {
            cout << "\nValoarea introdusa ca pozitie este incorecta.\n";
            return;
        }


        if(poz == 1) ///stergerea primului element al listei
        {
            if(prim == NULL)
            {
                cout << "\nLISTA VIDA!";
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


    ///supraincarcarea operatorului << pentru afisarea listei
    friend ostream & operator << (ostream & out, ListaCirculara & lc)
        {
            lc.iterareLista(out);
            return out;
        }


    ///functie care inverseaza legaturile unei liste
    void inversare_legaturi()
    {
        if(prim == NULL)
            cout << "\nLISTA VIDA!";
        else if(prim == ultim)
            cout << "\nLISTA NESCHIMBATA";
        else
        {
            ///transformam lista circulara in lista simpla
            ultim -> setNext(NULL);

            ///schimbam legaturile
            Nod* temp = prim;
            Nod* ante = new Nod();
            Nod* post = new Nod();

            while(temp != NULL)
            {
                post = temp -> getNext();
                temp -> setNext(ante);
                ante = temp;
                temp = post;
            }
            prim = ante;

            ///transformam lista simpla in lista circulara
            Nod* p = new Nod();
            for( p = prim; (p -> getNext()) -> getNext() != NULL; p = p -> getNext() );
            p -> setNext(prim);
            ultim = p;

        }
    }



    ///functie care elimina elementele listei din k in k, pana la golirea ei
    void golire_lista(int k)
    {
        Nod* curr = new Nod();
        int cnt = 0, poz = 0;
        int nr = nr_noduri();

        curr = prim;
        cout << "\n";
        while(nr != 0)
        {
            cnt++;
            if(curr == prim)
                poz = 0;

            poz = poz + 1;

            if(cnt == k)
            {
                cnt = 0;
                cout << curr -> getInfo() << " ";
                curr = curr -> getNext();
                stergere_pozitie(poz);
                nr--;
                poz--;
            }

            else if(cnt != k && prim != ultim)
                curr = curr -> getNext();
        }
    }


    ///supraincarcarea operatorului + care efectueaza concatenarea a doua liste
    friend ListaCirculara operator+(const ListaCirculara &lc1, const ListaCirculara &lc2)
    {
        ListaCirculara lc3;
        int i = 1;

        Nod* curr = new Nod();
        for(curr = lc1.prim; curr != lc1.ultim; curr = curr -> getNext())
        {
            lc3.inserare_pozitie(i, curr -> getInfo());
            i++;
        }
        lc3.inserare_pozitie(i, lc1.ultim -> getInfo());
        i++;


        for(curr = lc2.prim; curr != lc2.ultim; curr = curr -> getNext())
        {
            lc3.inserare_pozitie(i, curr -> getInfo());
            i++;
        }
        lc3.inserare_pozitie(i, lc2.ultim -> getInfo());


        return lc3;
    }

};


int main()
{
    ListaCirculara lc;
  //  lc.inserare_pozitie(1, 1);
    //lc.inserare_pozitie(2, 2);
    //lc.inserare_pozitie(3, 3);
    cin >> lc;
    cout << lc;

    //lc.golire_lista(3);

    return 0;
}
