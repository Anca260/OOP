#include <iostream>
#include <cstdlib>

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

        if(nr > 0)
        {
            cout << "Introduceti cele " << nr << " valori ale nodurilor: ";
            int cnt, val;
            for(cnt = 1; cnt <= nr; cnt++)
            {
                in >> val;
                inserare_pozitie(cnt, val);
            }
        }

    }

    ///functie care afiseaza lista
    void iterareLista(ostream & out)
    {
        if(prim == NULL)
        {
            out << "Lista curenta este vida.\n";
            return;
        }

        if(prim == ultim)
        {
            out << "Lista este: { " << prim -> getInfo() << " }\n";
            return;
        }

        out << "Lista este: { ";
        Nod* curr = prim;
        while(curr -> getNext() != prim)
        {
            out << curr -> getInfo() << " -> ";
            curr = curr -> getNext();
        }
        out << ultim -> getInfo() << " -> " << prim -> getInfo() << " }\n";
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


    ///supraincarcarea operatorului >>
    friend istream & operator >> (istream & in, ListaCirculara & lc)
    {
        lc.citire(in);
        return in;
    }



    ///functie care efectueaza stergerea unui element de pe o anumita pozitie
    void stergere_pozitie(int poz)
    {
        if(prim == NULL)
        {
            cout << "Nu se poate efectua stergerea.\n";
            return;
        }

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
                cout << "Lista curenta este vida!\n";
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

        else if(poz == nr) ///stergerea ultimului element al listei
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
            cout << "Nu se poate efectua inversarea legaturilor.\n";
        else if(prim == ultim)
            cout << "Lista ramane neschimbata\n";
        else
        {
            cout << "Inversam legaturile listei.\n";

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
        if(prim == NULL)
        {
            cout << "Nu se poate efectua operatia.\n";
            return;
        }

        cout << "Elementele se elimina in urmatoarea ordine: ";
        while(nr != 0)
        {
            cnt++;
            if(curr == prim)
                poz = 0;

            poz = poz + 1;

            if(cnt == k)
            {
                cnt = 0;
                cout << curr -> getInfo();
                curr = curr -> getNext();
                stergere_pozitie(poz);
                nr--;
                if(nr != 0)
                    cout << " , ";
                else
                    cout << ".";
                poz--;
            }

            else if(cnt != k && prim != ultim)
                curr = curr -> getNext();
        }
    }


    ///functie pentru citire, memorare si afisare
    void functie(ListaCirculara lc)
    {
        cin >> lc;
        cout << lc;
    }


    ///supraincarcarea operatorului + care efectueaza concatenarea a doua liste
    friend ListaCirculara operator+(const ListaCirculara &lc1, const ListaCirculara &lc2)
    {
        /* if(lc1.prim == NULL && lc2.prim == NULL)
         {
             return;
         }*/

        if(lc2.prim == NULL)
            return lc1;

        if(lc1.prim == NULL)
            return lc2;

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


    /*~ListaCirculara()
    {
        Nod* p = new Nod();
        while(prim != NULL)
        {
            p = prim;
            prim = prim -> getNext();
            delete p;
        }
    }*/

};


void menu_output()
{
    cout << "\n Anca Grupa 211 - Proiect 1 - Nume proiect: Clasa Lista_circulara (implementata dinamic) \n";
    cout << "\n\t MENIU:";
    cout << "\n===========================================\n";
    cout << "\n";
    cout << "1. Crearea listei \n";
    cout << "2. Inserarea unui element pe o anumita pozitie a listei \n";
    cout << "3. Stergerea unui element de pe o anumita pozitie din lista \n";
    cout << "4. Inversarea legaturilor listei \n";
    cout << "5. Eliminarea elementelor listei circulare din k in k pana la golirea acesteia \n";
    cout << "6. Afisare lista curenta \n";
    cout << "7. Concatenarea a doua liste circulare \n";
    cout << "0. Iesire. \n";
}

void menu(ListaCirculara lc)
{
    int option;  ///optiunea aleasa din meniu
    option = 0;
    int ok = 0;

    do
    {
        menu_output();

        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;

        if (option == 1)
        {
            if(ok == 0)
            {
                ok = 1;
                cin >> lc;
                cout << lc;
            }
            else
            {
                cout << "Lista a fost deja creata. \n";
                cout << "Puteti alege optiunea 2: inserare element in lista.";
            }
        }
        if (option == 2)
        {
            cout << lc;

            cout << "Introduceti valoarea nodului de inserat in lista: ";
            int val;
            cin >> val;

            cout << "Introduceti pozitia pe care sa fie inserat acest nod: ";
            int poz;
            cin >> poz;

            lc.inserare_pozitie(poz, val);
            cout << lc;
        }

        if (option == 3)
        {
            cout << lc;

            cout << "Stergeti pozitia de care sa fie sters nodul: ";
            int poz;
            cin >> poz;

            lc.stergere_pozitie(poz);
            cout << lc;
        }

        if (option == 4)
        {
            cout << lc;
            lc.inversare_legaturi();
            cout << lc;
        }

        if (option == 5)
        {
            cout << lc;

            int k;
            cout << "Introduceti valoarea parametrului k: ";
            cin >> k;

            lc.golire_lista(k);
            ok = 0;
        }

        if(option == 6)
        {
            cout << lc;
        }

        if(option == 7)
        {
            ListaCirculara lc1, lc2;
            cout << "--- Prima lista (lista curenta) ---\n";
            cout << lc;

            cout << "--- A doua lista ---\n";
            cin >> lc2;
            cout << lc2;

            cout << "--- Lista finala ---\n";
            lc = lc + lc2;
            cout << lc;
            cout << "\nOBSERVATIE: Lista intitulata -Lista finala- va fi cea utilizata la apelarea altor optiuni din meniu.\n";
        }

        if (option == 0)
        {
            cout << "\nEXIT!\n";
        }

        if (option < 0 || option > 7)
        {
            cout << "\nSelectie invalida\n";
        }

        cout << "\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option != 0);
}

int main()
{
    ListaCirculara lc;
    menu(lc);
    return 0;
}
