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
        delete next;
    }
};

class ListaCirculara
{
private:
    Nod* prim;
    Nod* ultim;

public:
    ListaCirculara()
    {
        prim = NULL;
        ultim = NULL;
    }///constructor lista

    void inserare_final(int data)
    {
        if(prim == NULL)
        {
            prim = new Nod(data);
            ultim = prim;
        }
        else
        {
            Nod* temp = new Nod(data, prim);
            ultim -> setNext(temp);
            ultim = temp;
        }
    }

    void inserare_inceput(int data)
    {
        if(prim == NULL)
        {
            prim = new Nod(data, prim);
            ultim = prim;
        }
        else
        {
            Nod* temp = new Nod(data, prim);
            prim = temp;
            ultim -> setNext(prim);
        }
    }


    Nod* cautare_valoare(int data)
    {
        Nod* p = new Nod();
        for( p = prim; p -> getNext() != prim &&  p -> getInfo() != data; p = p -> getNext() );
        /// p este nodul cu valoarea "data"

        return p;
    }


    void inserare_mijloc(int data_p, int data_temp) ///inserare dupa nodul cu valoarea "data"
    {
        Nod* p = cautare_valoare(data_p);
        /// p este nodul cu valoarea "data_p"

        ///inseram nodul temp dupa nodul p
        Nod* temp = new Nod(data_temp, p -> getNext());
        p -> setNext(temp);
    }


    void iterareLista()
    {
        if(prim == NULL)
        {
            cout << "LISTA VIDA!\n";
            return;
        }

        Nod* curr = prim;
        do
        {
            cout << curr -> getInfo() << "\n";
            curr = curr -> getNext();
        }
        while(curr != prim);

    }

    void stergere_inceput()
    {
        if(prim == NULL)
        {
            cout << "LISTA VIDA!";
        }
        else if(prim == ultim)
        {
            prim = NULL;
            ultim = NULL;
            delete prim;
        }
        else
        {
            Nod* temp = prim -> getNext();
            ultim -> setNext(temp);
            /// !!! delete prim + destructor;
            prim = temp;
        }

    }

    Nod* cautare_pozitie(Nod* r)
    {
        Nod* p = new Nod();
        for( p = prim; p -> getNext() != prim && p -> getNext() != r; p = p -> getNext() );
        /// p este predecesorul nodului r ( p -> next = r)

        return p;
    }


    void stergere_final()
    {
        ///p, ultim, prim

        Nod* p = cautare_pozitie(ultim);
        ///p este penultimul element din lista

        p -> setNext(prim);
        ///delete ultim
        ultim = p;
    }


    void stergere_mijloc(int data)
    {
        Nod* p = new Nod();
        for( p = prim -> getNext(); p -> getNext() != prim && (p -> getNext()) -> getInfo() != data; p = p -> getNext() );
        /// p este predecesorul nodului cu valoarea "data"

        ///p, r (de sters), t
        Nod* r = p -> getNext(); /// nodul cu valoarea "data" (nodul de sters)
        Nod* t = r -> getNext();

        p -> setNext(t);
        /// delete r;

    }

    void stergere(int data)
    {
        if(prim -> getInfo() == data)
            stergere_inceput();
        else if(ultim -> getInfo() == data)
            stergere_final();
        else
            stergere_mijloc(data);
    }

    void inversare_legaturi()
    {
        if(prim == NULL)
            cout << "LISTA VIDA!";
        else if(prim == ultim)
            cout << "LISTA NESCHIMBATA";
        else
        {
            ///transformam lista circulara in lista simpla
            ultim -> setNext(NULL);

            ///schimbam legaturile
            Nod* temp = prim;
            Nod* ant = new Nod();
            Nod* post = new Nod();

            while(temp != NULL)
            {
                post = temp -> getNext();
                temp -> setNext(ant);
                ant = temp;
                temp = post;
            }
            prim = ant;

            ///transformam lista simpla in lista circulara
            Nod* p = new Nod();
            for( p = prim; (p -> getNext()) -> getNext() != NULL; p = p -> getNext() );
            p -> setNext(prim);
            ultim = p;

        }
    }


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

    void golire_lista(int k)
    {
        int nr = nr_noduri();
        Nod* p = prim;


    }

};


int main()
{
    ListaCirculara l;
    l.inserare_inceput(3);
    l.inserare_final(4);
    l.inserare_final(6);
    l.inserare_final(7);
    l.inserare_inceput(2);
    l.inserare_inceput(1);
    l.inserare_mijloc(4, 5);


    /*  l.inserare_mijloc(4, 5);
      l.iterareLista();
      l.inserare_inceput(1);
      l.inserare_final(2);
      l.inserare_final(3);
      l.stergere_inceput(1);
    */
    l.stergere(7);
   // l.inversare_legaturi();
    l.iterareLista();
    cout << l.nr_noduri();



    return 0;
}
