#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <exception>
#include <stdexcept>

#include <windows.h>
#include <winnt.h>

using namespace std;


ifstream fin("Date.in");

class IOInterface
{
public:
    virtual ostream& afisare(ostream& out) const = 0;
    virtual istream& citire(istream& in) = 0;
    virtual ifstream& fisier_c(ifstream& fin) = 0;
};


class EroareaMea : public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Exceptia mea";
    }
}eroareamea;


void functieExceptii(int a)
{
    if (a == 0) throw 0; //pt int
    if (a == 1) throw 1; //pt float
    if (a == 2) throw 2.0; //pt double
    if (a == 3) throw 's'; //pt string
    if (a == 4) throw 'c'; //pt char
    if (a == 5) throw 5; //pt bool
}

class Ticket : public IOInterface
{
    string zona;
    int seat_nr;
    double price;
    char status; //s=sold, a=available, r=reserved

public:

    string getzona() { return this->zona; }
    int getseat_nr() { return this->seat_nr; }
    double getprice() { return this->price; }
    char getstatus() { return this->status; }

    void setzona(string zona)
    {
        if (zona == "A" || zona=="a")
            this->zona = "A";
        else
            if (zona == "B" || zona=="b")
                this->zona = "B";
            else
                if (zona == "C" || zona=="c")
                    this->zona = "C";
                else
                    if (zona == "D" || zona=="d")
                        this->zona = "D";
                    else
                        functieExceptii(3);
    }
    void setseat_nr(int seat_nr) 
    {
        if (seat_nr > 0 && seat_nr < 100)
            this->seat_nr = seat_nr;
        else
            functieExceptii(0);
    }
    void setprice(double price) 
    {
        if (price > 0)
            this->price = price;
        else
            functieExceptii(2);
    }
    void setstatus(char status) 
    {
        if (status == 'A' || status == 'a')
            this->status = 'a';
        else
            if (status == 'R' || status == 'r')
                this->status = 'r';
            else
                if (status == 'S' || status == 's')
                    this->status = 's';
                 else
                        functieExceptii(4);
    }

    Ticket();
    Ticket(string zona, int seat_nr, double price, char status);
    Ticket(const Ticket& t);
    void modify(vector <Ticket>& listaTicket);
    void deleting(vector <Ticket>& listaTicket);
    void filtru(vector <Ticket>& listaTicket);
    Ticket& operator =(const Ticket& t);
    ostream& afisare(ostream& out) const
    {
        out << "Numarul locului este: " << this->zona << this->seat_nr << endl;
        out << "Pretul este: " << this->price << endl;
        out << "Statusul este (s=sold, a=available, r=reserved): " << this->status << endl;
        return out;
    }
    istream& citire(istream& in)
    {
        string v;
        while (true)
        {
            try
            {
                cout << "Zona este: ";
                in >> v;
                if (in.fail())
                {
                    throw runtime_error("Zona este gresita. Introduceti o litera.\n");
                }
                setzona(v);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                {
                    cout << "Zona este gresita. Introduceti A, B, C sau D.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        int l;
        while (true)
        {
            try
            {
                cout << "Numarul locului este: ";
                in >> l;
                if (in.fail())
                {
                    throw runtime_error("Numarul locului este gresita. Introduceti un intreg.\n");
                }
                setseat_nr(l);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                {
                    cout << "Numarul locului este gresita. Introduceti un intreg cuprins intre 1 si 100.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        double p;
        while (true)
        {
            try
            {
                cout << "Pretul locului este: ";
                in >> p;
                if (in.fail())
                {
                    throw runtime_error("Pretul locului este gresita. Introduceti un intreg.\n");
                }
                setprice(p);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (double a)
            {
                if (a == 2.0)
                {
                    cout << "Pretul locului este gresita. Introduceti un intreg cuprins mai mare decat 1.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        char v1;
        while (true)
        {
            try
            {
                cout << "Statusul este (s=sold, a=available, r=reserved): ";
                in >> v1;
                if (in.fail())
                {
                    throw runtime_error("Statusul este gresita. Introduceti o litera.\n");
                }
                setstatus(v1);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 'c')
                {
                    cout << "Statusul este gresita. Introduceti s, a sau r.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        return in;
    }
    ifstream& fisier_c(ifstream& fin)
    {
        fin >> this->zona;
        fin >> this->seat_nr;
        fin >> this->price;
        fin >> this->status;
        return fin;
    }
    friend ostream& operator << (ostream& out, const Ticket& t);
    friend istream& operator >> (istream& in, Ticket& t);
    friend ifstream& operator >> (ifstream& fin, Ticket& t);
    ~Ticket(){}
};
Ticket::Ticket()
{
    this->zona = "";
    this->seat_nr = 0;
    this->price = 0;
    this->status = ' '; // dc nu merge '' ??? adica fara spatiu
}
Ticket::Ticket(string zona, int seat_nr, double price, char status)
{
    this->zona = zona;
    this->seat_nr = seat_nr;
    this->price = price;
    this->status = status;
}
Ticket::Ticket(const Ticket& t)
{
    this->zona = t.zona;
    this->seat_nr = t.seat_nr;
    this->price = t.price;
    this->status = t.status;
}
void Ticket::modify(vector <Ticket>& listaTicket)
{
    int nr, ci = 0;
    double p;
    string z;
    cout << "Care este zona ? ";
    cin >> z;
    cout << endl;
    cout << "Care este locul biletului pe care vrei sa il modifici? ";
    cin >> nr;
    cout << endl;
    for (int i = 0; i < listaTicket.size(); i++)
        if (listaTicket[i].getseat_nr() == nr && listaTicket[i].getzona() == z)
        {
            ci = i;
            break;
        }
    cout << "Care este noul pret? ";
    cin >> p;
    cout << endl;
    listaTicket[ci].setprice(p);
}
void Ticket::deleting(vector <Ticket>& listaTicket)
{
    int nr, ci;
    bool ok = 0;
    string z;
    cout << "Care este zona ? ";
    cin >> z;
    cout << endl;
    cout << "Care este locul biletului pe care vrei sa il stergi? ";
    cin >> nr;
    cout << endl;
    for (int i = 0; i < listaTicket.size() && ok == 0; i++)
    {
        if (listaTicket[i].getseat_nr() == nr && listaTicket[i].getzona() == z)
        {
            ci = i;
            ok = 1;
        }
    }
    listaTicket.erase(listaTicket.begin() + ci);
}
void Ticket::filtru(vector <Ticket>& listaTicket)
{
    cout << "Care este pretul biletului? ";
    double pret;
    cin >> pret;
    for (int i = 0; i < listaTicket.size(); i++)
        if (listaTicket[i].getprice() == pret)
        {
            cout << listaTicket[i];
            cout << endl;
        }
}
Ticket& Ticket::operator =(const Ticket& t)
{
    if (this != &t)
    {
        this->zona = t.zona;
        this->seat_nr = t.seat_nr;
        this->price = t.price;
        this->status = t.status;
    }
    return *this;
}
ostream& operator << (ostream& out, const Ticket& t)
{
    return t.afisare(out);
}
istream& operator >> (istream& in, Ticket& t)
{
    return t.citire(in);
}
ifstream& operator >> (ifstream& fin, Ticket& t)
{
    return t.fisier_c(fin);
}


class TicketRezervate : public IOInterface
{
    string nume_event;
    string zona;
    int seat_nr;
    double price;
public:
    string getnume_event() { return this->nume_event; }
    string getzona() { return this->zona; }
    int getseat() { return this->seat_nr; }
    double getprice() { return this->price; }

    void setnume_event(std::string name)
    {
        if (name != "")
            this->nume_event = name;
        else
            functieExceptii(3);
    }
    void setzona(string zona)
    {
        if (zona == "A" || zona == "a")
            this->zona = "A";
        else
            if (zona == "B" || zona == "b")
                this->zona = "B";
            else
                if (zona == "C" || zona == "c")
                    this->zona = "C";
                else
                    if (zona == "D" || zona == "d")
                        this->zona = "D";
                    else
                        functieExceptii(3);
    }
    void setseat_nr(int seat_nr)
    {
        if (seat_nr > 0 && seat_nr < 100)
            this->seat_nr = seat_nr;
        else
            functieExceptii(0);
    }
    void setprice(double price)
    {
        if (price > 0)
            this->price = price;
        else
            functieExceptii(2);
    }

    TicketRezervate()
    {
        this->nume_event = "";
        this->zona = "";
        this->seat_nr = 0;
        this->price = 0;
    }
    TicketRezervate(string nume_event, string zona, int seat_nr, double price)
    {
        this->nume_event = nume_event;
        this->zona = zona;
        this->seat_nr = seat_nr;
        this->price = price;
    }
    TicketRezervate(const TicketRezervate& t)
    {
        this->nume_event = t.nume_event;
        this->zona = t.zona;
        this->seat_nr = t.seat_nr;
        this->price = t.price;
    }
    TicketRezervate operator =(const TicketRezervate& t)
    {
        if (this != &t)
        {
            this->nume_event = t.nume_event;
            this->zona = t.zona;
            this->seat_nr = t.seat_nr;
            this->price = t.price;
        }
        return *this;
    }

    void deleting(vector <TicketRezervate>& listaTicket)
    {

        int nr, ci=-1;
        bool ok = 0;
        string z;
        string nume;
        while (true)
        {
            try
            {
                string v;
                cout << "Care este numele evennimentului? ";
                cin >> v;
                if (cin.fail())
                {
                    throw runtime_error("Numele evenimentului nu este corect. Introduceti un cuvant.\n");
                }
                nume = v;
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            cin.clear();
            cin.ignore();
        }
        while (true)
        {
            try
            {
                string v;
                cout << "Care este zona ? ";
                cin >> v;
                if (cin.fail() || v!="A" || v!="B" || v!="C" || v!="D")
                {
                    throw runtime_error("Zona nu este corect. Introduceti o litera dintre A, B, C, D.\n");
                }
                z = v;
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            cin.clear();
            cin.ignore();
        }
        while (true)
        {
            try
            {
                int v;
                cout << "Care este locul biletului pe care vrei sa il stergi? ";
                cin >> v;
                if (cin.fail()  || v>0)
                {
                    throw runtime_error("Locul biletulu nu este corect. Introduceti un numar intreg pozitiv.\n");
                }
                nr = v;
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            cin.clear();
            cin.ignore();
        }

        for (int i = 0; i < listaTicket.size() && ok == 0; i++)
        {
            if (listaTicket[i].getnume_event() == nume && listaTicket[i].getseat() == nr && listaTicket[i].getzona() == z)
            {
                ci = i;
                ok = 1;
            }
        }
        if (ci != -1)
            listaTicket.erase(listaTicket.begin() + ci);
        else
            cout << "Locul acesta nu este rezervat.\n";
    }
    void deleting_p(vector <TicketRezervate>& listaTicket, const TicketRezervate& t)
    {
        TicketRezervate aux = t;
        if (aux.getprice() != -1)
        {
            int ci = -1;
            bool ok = 0;
               
            for (int i = 0; i < listaTicket.size() && ok == 0; i++)
            {
                if (listaTicket[i].getnume_event() == aux.getnume_event() 
                    && listaTicket[i].getseat() == aux.getseat() 
                    && listaTicket[i].getzona() == aux.getzona())
                {
                    ci = i;
                    ok = 1;
                }
            }
            listaTicket.erase(listaTicket.begin() + ci);
        }
    }

    ostream& afisare(ostream& out) const
    {
        out << "Numele evenimentului este: " << this->nume_event << endl;
        out << "Locul biletului este: " << this->zona << this->seat_nr << endl;
        out << "Pretul biletului este: " << this->price << endl;
        return out;
    }
    istream& citire(istream& in)
    {
        string v;
        while (true)
        {
            try
            {
                cout << "Numele evenimentului este: ";
                in >> v;
                if (in.fail())
                {
                    throw runtime_error("Numele evenimentului nu este corect. Introduceti un cuvant.\n");
                }
                setnume_event(v);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                    cout << "Numele evenimentului nu este corect. Introduceti un cuvant.\n";
            }
            in.clear();
            in.ignore();
        }
        v = "";
        while (true)
        {
            try
            {
                cout << "Zona este: ";
                in >> v;
                if (in.fail())
                {
                    throw runtime_error("Zona este gresita. Introduceti o litera.\n");
                }
                setzona(v);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                {
                    cout << "Zona este gresita. Introduceti A, B, C sau D.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        int l;
        while (true)
        {
            try
            {
                cout << "Numarul locului este: ";
                in >> l;
                if (in.fail())
                {
                    throw runtime_error("Numarul locului este gresita. Introduceti un intreg.\n");
                }
                setseat_nr(l);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                {
                    cout << "Numarul locului este gresita. Introduceti un intreg cuprins intre 1 si 100.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        double p;
        while (true)
        {
            try
            {
                cout << "Pretul locului este: ";
                in >> p;
                if (in.fail())
                {
                    throw runtime_error("Pretul locului este gresita. Introduceti un intreg.\n");
                }
                setprice(p);
                break;
            }
            catch (runtime_error a)
            {
                cout << a.what();
            }
            catch (double a)
            {
                if (a == 2.0)
                {
                    cout << "Pretul locului este gresita. Introduceti un intreg cuprins mai mare decat 1.\n";
                }
            }
            in.clear();
            in.ignore();
        };
        return in;
    }
    ifstream& fisier_c(ifstream& fin)
    {
        fin >> this->nume_event;
        fin >> this->zona;
        fin >> this->seat_nr;
        fin >> this->price;
        return fin;
    }

    friend ostream& operator <<(ostream& out, const TicketRezervate& t)
    {
        return t.afisare(out);
    }
    friend  istream& operator >>(istream& in, TicketRezervate& t)
    {
        return t.citire(in);
    }
    friend ifstream& operator >>(ifstream& fin, TicketRezervate& t)
    {
        return t.fisier_c(fin);
    }
    ~TicketRezervate(){}
};

class Sala : public IOInterface, public EroareaMea
{
protected:
    int L_a;
    int L_b;
    int l_a;
    int l_b;

public:
    int getL_a() { return this->L_a; }
    int getL_b() { return this->L_b; }
    int getl_a() { return this->l_a; }
    int getl_b() { return this->l_b; }

    void setL_a(int l)
    {
        if (l > 0 && l < 10)
            this->L_a = l;
        else
            functieExceptii(0);
    }
    void setL_b(int l)
    {
        if (l > 0 && l < 10)
            this->L_b = l;
        else
            functieExceptii(0);
    }
    void setl_a(int l)
    {
        if (l > 0 && l < 10 && l <= this->L_a)
            this->l_a = l;
        else
            functieExceptii(0);
    }
    void setl_b(int l)
    {
        if (l > 0 && l < 10 && l <= this->L_b)
            this->l_b = l;
        else
            functieExceptii(0);
    }

    Sala()
    {
        this->L_a = 10;
        this->l_a = 5;
        this->L_b = 10;
        this->l_b = 5;
    }
    Sala(int L_a, int l_a, int L_b, int l_b)
    {
        this->L_a = L_a;
        this->l_a = l_a;
        this->L_b = L_b;
        this->l_b = l_b;
    }
    Sala(const Sala& s)
    {
        this->L_a = s.L_a;
        this->l_a = s.l_a;
        this->L_b = s.L_b;
        this->l_b = s.l_b;
    }
    Sala& operator =(const Sala& s)
    {
        if (this != &s)
        {
            this->L_a = s.L_a;
            this->l_a = s.l_a;
            this->L_b = s.L_b;
            this->l_b = s.l_b;
        }
        return *this;
    }

    ostream& afisare(ostream& out) const
    {
        int i, j, k;
        //pt zona A
        for (i = this->l_a - 1; i >= 0; i--)
        {
            for (k = 0; k < this->l_b; k++)
                out << "    ";
            out << "    ";
            for (j = this->L_a * i; j < this->L_a * (i + 1); j++)
            {
                out << " ___";
            }
            out << endl;
            for (k = 0; k < this->l_b; k++)
                out << "    ";
            out << "    ";
            for (j = (this->L_a * i + 1); j <= this->L_a * (i + 1); j++)
            {
                if (j >= 10)
                    out << "|A" << j;
                else
                    out << "|A" << j << " ";
            }
            out << "|\n";
        }
        out << "\n";
        //pt zonele B, D, C
        //B=C; L_d=L_a, l_d=L_b
        for (i = L_b; i > 0; i--)
        {
            //pt linia de sus a locului
            //pt B
            for (j = l_b * i; j >= l_b * (i - 1) + 1; j--)
            {
                out << " ___";
            }
            out << "    ";
            //Pt D
            for (j = L_a * i; j >= L_a * (i - 1) + 1; j--)
            {
                out << " ___";
            }
            out << "    ";
            //pt C
            for (j = l_b * i; j >= l_b * (i - 1) + 1; j--)
            {
                out << " ___";
            }
            out << endl;
            //pt locuri
            //pt B
            for (j = l_b * i; j >= l_b * (i - 1) + 1; j--)
            {
                if (j >= 10)
                    out << "|B" << j;
                else
                    out << "|B" << j << " ";
            }
            out << "|   ";
            //Pt D
            for (j = L_a * (i - 1) + 1; j <= L_a * i; j++)
            {
                if (j >= 10)
                    out << "|D" << j;
                else
                    out << "|D" << j << " ";
            }
            out << "|   ";
            //pt C
            for (j = l_b * (i - 1) + 1; j <= l_b * i; j++)
            {
                if (j >= 10)
                    out << "|C" << j;
                else
                    out << "|C" << j << " ";
            }
            out << "|\n";
        }
        out << "\n\n";
        for (j = 0; j <= (2 * L_a + 4 * l_b); j++)
            out << " ";
        out << "-------\n";
        for (j = 0; j <= (2 * L_a + 4 * l_b); j++)
            out << " ";
        out << "|SCENA|\n";
        for (j = 0; j <= (2 * L_a + 4 * l_b); j++)
            out << " ";
        out << "-------\n\n";
        return out;
    }
    istream& citire(istream& in)
    {
        int l = 0, e2 = 0;
        while (true)
        {
            try
            {
                cout << "Care este lungimea zonei A? ";
                
                in >> l;
                if (in.fail())
                {
                    throw runtime_error("Lungimea nu este corecta. Alegeti o valoare intreaga.\n");
                }
                setL_a(l);
                break;
               
            }
            catch (runtime_error &a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if(a==0)
                    cout << "Lungimea nu este corecta. Alegeti o valoare intreaga cuprinsa intre 0 si 10.\n";
            }
            in.clear();
            in.ignore();
        }
        while (true)
        {
            try
            {
                cout << "Care este latimea zonei A? ";

                in >> l;
                if (in.fail())
                {
                    throw runtime_error("Latimea nu este corecta. Alegeti o valoare intreaga.\n");
                }
                setl_a(l);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                    cout << "Lungimea nu este corecta. Alegeti o valoare intreaga cuprinsa intre 0 si lungimea zonei A.\n";
            }
            in.clear();
            in.ignore();
        }
        while (true)
        {
            try
            {
                cout << "Care este lungimea zonei B? ";

                in >> l;
                if (in.fail())
                {
                    throw runtime_error("Lungimea nu este corecta. Alegeti o valoare intreaga.\n");
                }
                setL_b(l);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                    cout << "Lungimea nu este corecta. Alegeti o valoare intreaga cuprinsa intre 0 si 10.\n";
            }
            in.clear();
            in.ignore();
        }
        while (true)
        {
            try
            {
                cout << "Care este latimea zonei B? ";

                in >> l;
                if (in.fail())
                {
                    throw runtime_error("Latimea nu este corecta. Alegeti o valoare intreaga cuprinsa intre 0 si lungimea zonei B.\n");
                }
                setl_b(l);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                    cout << "Lungimea nu este corecta. Alegeti o valoare intreaga cuprinsa intre 0 si lungimea zonei B.\n";
            }
            in.clear();
            in.ignore();
        }
        return in;
    }
    ifstream& fisier_c(ifstream& fin)
    {
        fin >> this->L_a;
        fin >> this->l_a;
        fin >> this->L_b;
        fin >> this->l_b;
        return fin;
    }
    friend ostream& operator <<(ostream& out, const Sala& s)
    {
        return s.afisare(out);
    }
    friend istream& operator >>(istream& in, Sala& s)
    {
        return s.citire(in);
    }
    friend ifstream& operator >>(ifstream& fin, Sala& s)
    {
        return s.fisier_c(fin);
    }
    virtual ~Sala() {}
};


class Location : public Sala
{
protected:
    int location_id;
    std::string venue;

public:
    int getlocation_id() { return this->location_id; }
    std::string getvenue() { return this->venue; }

    void setlocation_id(int location_id)
    {
        if (location_id > 0)
            this->location_id = location_id;
        else
            functieExceptii(0);

    }
    void setvenue(std::string venue)
    {
        if (venue != "")
            this->venue = venue;
        else
            functieExceptii(3);
    }

    Location();
    Location(int, std::string, int L_a, int l_a, int L_b, int l_b);
    Location(const Location& l);
    void modify(vector <Location>& listaLocation);
    void deleting(vector <Location>& listaLocation);
    void filtru(vector <Location>& listaLocation);
    Location& operator =(const Location& l);
    ostream& afisare(ostream& out) const
    {
        //Sala::afisare(out);
        out << "Id-ul locatiei este: " << this->location_id << endl;
        out << "Locatia este: " << this->venue << endl;
        return out;
    }
    istream& citire(istream& in)
    {
        Sala::citire(in);
        int id;
        while (true)
        {
            try
            {
                cout << "Id-ul locatiei este: ";

                in >> id;
                if (in.fail())
                {
                    throw runtime_error("Id-ul nu este corecta. Alegeti o valoare intreaga.\n");
                }
                setlocation_id(id);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                    cout << "Id-ul nu este corecta. Alegeti o valoare intreaga mai mare decat 0.\n";
            }
            in.clear();
            in.ignore();
        }
        string v;
        while (true)
        {
            try
            {
                cout << "Numele locatiei este: ";
                in >> v;
                //in.getline(v); ???
                if (in.fail())
                {
                    throw runtime_error("Numele locatiei nu este corect. Introduceti un cuvant.\n");
                }
                setvenue(v);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                    cout << "Numele locatiei nu este corect. Introduceti un cuvant.\n";
            }
            in.clear();
            in.ignore();
        }
        return in;
    }
    ifstream& fisier_c(ifstream& fin)
    {
        Sala::fisier_c(fin);
        fin >> this->location_id;
        fin >> this->venue;
        return fin;
    }
    friend ostream& operator <<(ostream& out, const Location& p);
    friend istream& operator >>(istream& in, Location& p);
    friend ifstream& operator >>(ifstream& fin, Location& p);
    ~Location() {}
};
Location::Location() : Sala()
{
    this->location_id = 0;
    this->venue = "unknown";
}
Location::Location(int location_id, std::string venue, int L_a, int l_a, int L_b, int l_b) 
    : Sala(L_a, l_a, L_b, l_b)
{
    this->location_id=location_id;
    this->venue=venue;
}
Location::Location(const Location& l) : Sala(l)
{
    this->location_id = l.location_id;
    this->venue = l.venue;
}
void Location::deleting(vector <Location>& listaLocation)
{
    int id, ci = -1;
    cout << "Care este id-ul locatiei pe care vrei sa il stergi? ";
    cin >> id;
    cout << endl;
    for (int i = 0; i < listaLocation.size(); i++)
        if (listaLocation[i].getlocation_id() == id)
        {
            ci = i;
            break;
        }
    listaLocation.erase(listaLocation.begin() + ci);
}
void Location::filtru(vector <Location>& listaLocation)
{
    int id;
    cout << "Care este id-ul locatiei pe care vrei sa il gasesti? ";
    cin >> id;
    cout << endl;
    for (int i = 0; i < listaLocation.size(); i++)
        if (listaLocation[i].getlocation_id() == id)
        {
            cout << listaLocation[i] << endl;
            break;
        }
}
Location& Location::operator =(const Location& l)
{
    if (this != &l)
    {
        Sala::operator =(l);
        this->location_id = l.location_id;
        this->venue = l.venue;
    }
    return *this;
}
ostream& operator <<(ostream& out, const Location& p)
{
    return p.afisare(out);
}
istream& operator >>(istream& in, Location& p)
{
    return p.citire(in);
}
ifstream& operator >>(ifstream& fin, Location& p)
{
    return p.fisier_c(fin);
}


class Event : public Location
{
    int event_id;
    std::string name;
    std::string data;
    std::string timp;
    std::string category;
    vector <Ticket> listaPreturi;

public:

    int getevent_id() { return this->event_id; }
    std::string getname() { return this->name; }
    std::string getdata() { return this->data; }
    std::string gettimp() { return this->timp; }
    std::string getcategory() { return this->category; }
    char getstatus(string z, int l)
    {
        if (z == "A")
            return this->listaPreturi[l-1].getstatus();
        if (z == "B")
            return this->listaPreturi[l_a * L_a + l-1].getstatus();
        if (z == "C")
            return this->listaPreturi[l_a * L_a + l_b * L_b + l-1].getstatus();
        if (z == "D")
            return this->listaPreturi[l_a * L_a + 2 * l_b * L_b + l-1].getstatus();
    }
    double getprice(string z, int l)
    {
        if (z == "A")
            return this->listaPreturi[l-1].getprice();
        if (z == "B")
            return this->listaPreturi[l_a * L_a + l-1].getprice();
        if (z == "C")
            return this->listaPreturi[l_a * L_a + l_b * L_b + l-1].getprice();
        if (z == "D")
            return this->listaPreturi[l_a * L_a + 2 * l_b * L_b + l-1].getprice();
    }

    void setevent_id(int event_id) 
    { 
        if (event_id > 0)
            this->event_id = event_id;
        else
            functieExceptii(0);
    }
    void setname(std::string name) 
    { 
        if (name != "")
            this->name = name;
        else
            functieExceptii(3);
    }
    void setdata(std::string data) 
    { 
        if (data != "")
            this->data = data;
        else
            functieExceptii(3);
    }
    void settimp(std::string timp)
    {
        if (timp != "")
            this->timp = timp;
        else
            functieExceptii(3); 
    }
    void setcategory(std::string category) 
    {
        if (category != "")
            this->category = category;
        else
            functieExceptii(3); 
    }
    void setstatus(string z, int l, char s)
    {
        if (z == "A")
            this->listaPreturi[l-1].setstatus(s);
        if (z == "B")
            this->listaPreturi[l_a * L_a + l-1].setstatus(s);
        if (z == "C")
            this->listaPreturi[l_a * L_a + l_b * L_b + l-1].setstatus(s);
        if (z == "D")
            this->listaPreturi[l_a * L_a + 2 * l_b * L_b + l-1].setstatus(s);
    }

    Event();
    Event(int, std::string, std::string, std::string, std::string, int, std::string, int L_a, int l_a, int L_b, int l_b);
    Event(const Event& e);
    void modify(vector <Event>& listaEvent);
    void deleting(vector <Event>& listaEvent);
    void filtru(vector <Event>& listaEvent);
    Event& operator = (const Event& e);
    ostream& afisare(ostream& out) const
    {
        Location::afisare(out);
        out << "Id-ul evenimentului este: " << this->event_id << endl;
        out << "Numele evenimentului este: " << this->name << endl;
        out << "Data evenimentului este: " << this->data << endl;
        out << "Ora evenimentului este: " << this->timp << endl;
        out << "Tipul evenimentului este: " << this->category << endl;
        return out;
    }
    istream& citire(istream& in)
    {
        Location::citire(in);
        int id;
        while (true)
        {
            try
            {
                cout << "Id-ul evenimentului este: ";

                in >> id;
                if (in.fail())
                {
                    throw runtime_error("Id-ul nu este corecta. Alegeti o valoare intreaga.\n");
                }
                setevent_id(id);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                    cout << "Id-ul nu este corecta. Alegeti o valoare intreaga mai mare decat 0.\n";
            }
            in.clear();
            in.ignore();
        }
        string v;
        while (true)
        {
            try
            {
                cout << "Numele evenimentului este: ";
                in >> v;
                //in.getline(v); ???
                if (in.fail())
                {
                    throw runtime_error("Numele locatiei nu este corect. Introduceti un cuvant.\n");
                }
                setname(v);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                    cout << "Numele evenimentului nu este corect. Introduceti un cuvant.\n";
            }
            in.clear();
            in.ignore();
        }
        v = "";
        while (true)
        {
            try
            {
                cout << "Data evenimentului este (zz.mm.yyyy): ";
                in >> v;
                //in.getline(v); ???
                if (in.fail())
                {
                    throw runtime_error("Data locatiei nu este corect. Introduceti o data.\n");
                }
                setdata(v);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                    cout << "Data evenimentului nu este corect. Introduceti o data de forma zz.mm.yyyy.\n";
            }
            in.clear();
            in.ignore();
        }
        v = "";
        while (true)
        {
            try
            {
                cout << "Ora evenimentului este (hh.mm): ";
                in >> v;
                //in.getline(v); ???
                if (in.fail())
                {
                    throw runtime_error("Ora locatiei nu este corect. Introduceti o ora.\n");
                }
                settimp(v);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                    cout << "Ora evenimentului nu este corect. Introduceti o ora de forma hh.mm.\n";
            }
            in.clear();
            in.ignore();
        }
        v = "";
        while (true)
        {
            try
            {
                cout << "Categoria evenimentului este: ";
                in >> v;
                //in.getline(v); ???
                if (in.fail())
                {
                    throw runtime_error("Categoria locatiei nu este corect. Introduceti un cuvant.\n");
                }
                setdata(v);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 's')
                    cout << "Categoria evenimentului nu este corect. Introduceti un cuvant.\n";
            }
            in.clear();
            in.ignore();
        }
        int p;
        while (true)
        {
            try
            {
                cout << "Pretul celui mai ieftin loc este: ";

                in >> p;
                if (in.fail())
                {
                    throw runtime_error("Pretul nu este corect. Alegeti o valoare intreaga.\n");
                }
                if (p <= 0) functieExceptii(0);

                for (int i = l_a; i >= 0; i = i - 2)
                {
                    for (int j = L_a * i; j > L_a * (i - 2) && j>0; j--)
                    {
                        Ticket aux1((string)"A", j, p, 'a');
                        this->listaPreturi.push_back(aux1);
                    }
                    p = p + 10;
                }
                for (int i = 0; i < l_a * L_a - 1; i++)
                    for (int j = i; j < l_a * L_a; j++)
                        if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                        {
                            Ticket aux1(this->listaPreturi[i]);
                            this->listaPreturi[i] = this->listaPreturi[j];
                            this->listaPreturi[j] = aux1;
                        }
                int la = L_a * l_a;
                int lb = L_b * l_b;
                int ld = L_a * L_b;
                for (int i = l_b; i >= 0; i = i - 2)
                {
                    for (int j = L_b * i; j > L_b * (i - 2) && j > 0; j--)
                    {
                        Ticket aux2((string)"B", j, p, 'a');
                        this->listaPreturi.push_back(aux2);
                    }
                    p = p + 10;
                }
                for (int i = la; i < la+lb-1; i++)
                    for (int j = i; j < la+lb; j++)
                        if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                        {
                            Ticket aux1(this->listaPreturi[i]);
                            this->listaPreturi[i] = this->listaPreturi[j];
                            this->listaPreturi[j] = aux1;
                        }
                for (int i = l_b; i >0; i = i - 2)
                {
                    for (int j = L_b * i; j > L_b * (i - 2) && j > 0; j--)
                    {
                        Ticket aux3((string)"C", j, p, 'a');
                        this->listaPreturi.push_back(aux3);
                    }
                    p = p + 10;
                }
                for (int i = la+lb; i < la+lb+lb - 1; i++)
                    for (int j = i; j < la+lb+lb; j++)
                        if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                        {
                            Ticket aux1(this->listaPreturi[i]);
                            this->listaPreturi[i] = this->listaPreturi[j];
                            this->listaPreturi[j] = aux1;
                        }
                for (int i = L_b; i >= 0; i = i - 2)
                {
                    for (int j = L_a * i; j > L_a * (i - 2) && j > 0; j--)
                    {
                        Ticket aux4((string)"D", j, p, 'a');
                        this->listaPreturi.push_back(aux4);
                    }
                    p = p + 10;
                }
                for (int i = la + lb + lb; i < la + lb + ld + lb - 1; i++)
                    for (int j = i; j < la + lb + lb + ld; j++)
                        if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                        {
                            Ticket aux1(this->listaPreturi[i]);
                            this->listaPreturi[i] = this->listaPreturi[j];
                            this->listaPreturi[j] = aux1;
                        }
                    
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 0)
                    cout << "Pretul nu este corecta. Alegeti o valoare intreaga mai mare decat 0.\n";
            }
            in.clear();
            in.ignore();
        }
        return in;
    }
    ifstream& fisier_c(ifstream& fin)
    {
        Location::fisier_c(fin);
        fin >> this->event_id;
        fin >> this->name;
        fin >> this->data;
        fin >> this->timp;
        fin >> this->category;
        int p;
        fin >> p;

        for (int i = l_a; i >= 0; i = i - 2)
        {
            for (int j = L_a * i; j > L_a * (i - 2) && j > 0; j--)
            {
                Ticket aux1((string)"A", j, p, 'a');
                this->listaPreturi.push_back(aux1);
            }
            p = p + 10;
        }
        for (int i = 0; i < l_a * L_a - 1; i++)
            for (int j = i; j < l_a * L_a; j++)
                if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                {
                    Ticket aux1(this->listaPreturi[i]);
                    this->listaPreturi[i] = this->listaPreturi[j];
                    this->listaPreturi[j] = aux1;
                }
        int la = L_a * l_a;
        int lb = L_b * l_b;
        int ld = L_a * L_b;
        for (int i = l_b; i >= 0; i = i - 2)
        {
            for (int j = L_b * i; j > L_b * (i - 2) && j > 0; j--)
            {
                Ticket aux2((string)"B", j, p, 'a');
                this->listaPreturi.push_back(aux2);
            }
            p = p + 10;
        }
        for (int i = la; i < la + lb - 1; i++)
            for (int j = i; j < la + lb; j++)
                if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                {
                    Ticket aux1(this->listaPreturi[i]);
                    this->listaPreturi[i] = this->listaPreturi[j];
                    this->listaPreturi[j] = aux1;
                }
        for (int i = l_b; i > 0; i = i - 2)
        {
            for (int j = L_b * i; j > L_b * (i - 2) && j > 0; j--)
            {
                Ticket aux3((string)"C", j, p, 'a');
                this->listaPreturi.push_back(aux3);
            }
            p = p + 10;
        }
        for (int i = la + lb; i < la + lb + lb - 1; i++)
            for (int j = i; j < la + lb + lb; j++)
                if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                {
                    Ticket aux1(this->listaPreturi[i]);
                    this->listaPreturi[i] = this->listaPreturi[j];
                    this->listaPreturi[j] = aux1;
                }
        for (int i = L_b; i >= 0; i = i - 2)
        {
            for (int j = L_a * i; j > L_a * (i - 2) && j > 0; j--)
            {
                Ticket aux4((string)"D", j, p, 'a');
                this->listaPreturi.push_back(aux4);
            }
            p = p + 10;
        }
        for (int i = la + lb + lb; i < la + lb + ld + lb - 1; i++)
            for (int j = i; j < la + lb + lb + ld; j++)
                if (this->listaPreturi[i].getseat_nr() > this->listaPreturi[j].getseat_nr())
                {
                    Ticket aux1(this->listaPreturi[i]);
                    this->listaPreturi[i] = this->listaPreturi[j];
                    this->listaPreturi[j] = aux1;
                }
        return fin;
    }
    friend ostream& operator << (ostream& out, const Event& e);
    friend istream& operator >> (istream& in, Event& e);
    friend ifstream& operator >> (ifstream& fin, Event& e);
    void locuri_libere()
    {
        HANDLE consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
        int i, j, k;
        //pt zona A
        int la = l_a * L_a;
        int lb = l_b * L_b;
        int ld = L_b * L_a;
        for (i = this->l_a - 1; i >= 0; i--)
        {
            for (k = 0; k < this->l_b; k++)
                cout << "    ";
            cout << "    ";
            for (j = this->L_a * i; j < this->L_a * (i + 1); j++)
            {
                cout << " ___";
            }
            cout << endl;
            for (k = 0; k < this->l_b; k++)
                cout << "    ";
            cout << "    ";
            for (j = L_a * i; j < L_a * (i + 1); j++)
            {
                SetConsoleTextAttribute(consolehwnd, 7);
                cout << "|";
                Ticket current = this->listaPreturi[j];

                switch (current.getstatus())
                {
                case 'a':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN);
                    break;
                case 'r':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE);
                    break;
                default:
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED);
                    break;
                }
                cout << "A" << current.getseat_nr();
                if (current.getseat_nr() < 10)  
                    cout << " ";
            }
            SetConsoleTextAttribute(consolehwnd, 7);
            cout << "|\n";
        }
        SetConsoleTextAttribute(consolehwnd, 7);
        cout << "\n";
        //pt zonele B, D, C
        //B=C; L_d=L_a, l_d=L_b
        for (i = L_b; i > 0; i--)
        {
            //pt linia de sus a locului
            //pt B
            for (j = l_b * i; j >= l_b * (i - 1) + 1; j--)
            {
                cout << " ___";
            }
            cout << "    ";
            //Pt D
            for (j = L_a * i; j >= L_a * (i - 1) + 1; j--)
            {
                cout << " ___";
            }
            cout << "    ";
            //pt C
            for (j = l_b * i; j >= l_b * (i - 1) + 1; j--)
            {
                cout << " ___";
            }
            cout << endl;
            //pt locuri
            //pt B
            for (j = l_b * i; j >= l_b * (i - 1) + 1; j--)
            {
                SetConsoleTextAttribute(consolehwnd, 7);
                cout << "|";
                Ticket current = this->listaPreturi[la + j];

                switch (current.getstatus())
                {
                case 'a':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN);
                    break;
                case 'r':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE);
                    break;
                default:
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED);
                    break;
                }
                cout << "B" << current.getseat_nr();
                if (current.getseat_nr() < 10)  cout << " ";
            }
            SetConsoleTextAttribute(consolehwnd, 7);
            cout << "|   ";
            //Pt D
            for (j = L_a * (i - 1); j < L_a * i; j++)
            {
                SetConsoleTextAttribute(consolehwnd, 7);
                cout << "|";
                Ticket current = this->listaPreturi[la + lb + lb + j];

                switch (current.getstatus())
                {
                case 'a':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN);
                    break;
                case 'r':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE);
                    break;
                default:
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED);
                    break;
                }
                cout << "D" << current.getseat_nr();
                if (current.getseat_nr() < 10)  cout << " ";
            }
            SetConsoleTextAttribute(consolehwnd, 7);
            cout << "|   ";
            //pt C
            for (j = l_b * (i - 1); j < l_b * i; j++)
            {
                SetConsoleTextAttribute(consolehwnd, 7);
                cout << "|";
                Ticket current = this->listaPreturi[la + lb + j];

                switch (current.getstatus())
                {
                case 'a':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN);
                    break;
                case 'r':
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE);
                    break;
                default:
                    SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED);
                    break;
                }
                cout << "C" << current.getseat_nr();
                if (current.getseat_nr() < 10)  cout << " ";
            }
            SetConsoleTextAttribute(consolehwnd, 7);
            cout << "|\n";
        }
        cout << "\n\n";
        for (j = 0; j <= (2 * L_a + 4 * l_b); j++)
            cout << " ";
        cout << "-------\n";
        for (j = 0; j <= (2 * L_a + 4 * l_b); j++)
            cout << " ";
        cout << "|SCENA|\n";
        for (j = 0; j <= (2 * L_a + 4 * l_b); j++)
            cout << " ";
        cout << "-------\n\n";
    }
    ~Event() {}
};
Event::Event() : Location()
{
    this->event_id = 0;
    this->name = "unknown";
    this->data = "unknown";
    this->timp = '0';
    this->category = '0';
}
Event::Event(int event_id, std::string name, std::string data, std::string timp, std::string category, int location_id, std::string venue, int L_a, int l_a, int L_b, int l_b) 
    : Location(location_id, venue, L_a, l_a, L_b, l_b)
{
    this->event_id=event_id;
    this->name=name;
    this->data=data;
    this->timp=timp;
    this->category=category;
}
Event::Event(const Event& e) : Location(e)
{
    this->event_id = e.event_id;
    this->name = e.name;
    this->data = e.data;
    this->timp = e.timp;
    this->category = e.category;
    for (int i = 0; i < e.listaPreturi.size(); i++)
        this->listaPreturi.push_back(e.listaPreturi[i]);
}
void Event::modify(vector <Event>& listaEvent)
{
    int id, ci;
    std::string data;
    cout << "Care este id-ul evenimentului pe care vrei sa il modifici? ";
    cin >> id;
    cout << endl;
    for (int i = 0; i < listaEvent.size(); i++)
        if (listaEvent[i].getevent_id() == id)
        {
            ci = i;
            break;
        }
    cout << "Care este noua data? ";
    cin >> data;
    cout << endl;
    listaEvent[ci].setdata(data);
}
void Event::deleting(vector <Event>& listaEvent)
{
    int id, ci;
    cout << "Care este id-ul evenimentului pe care vrei sa il stergi? ";
    cin >> id;
    cout << endl;
    for (int i = 0; i < listaEvent.size(); i++)
        if (listaEvent[i].getevent_id() == id)
        {
            ci = i;
            break;
        }
    listaEvent.erase(listaEvent.begin() + ci);
}
void Event::filtru(vector <Event>& listaEvent)
{
    cout << "Care este data?";
    string ziua;
    cin >> ziua;
    for (int i = 0; i < listaEvent.size(); i++)
        if (listaEvent[i].getdata() == ziua)
        {
            cout << listaEvent[i];
            cout << endl;
        }
}
Event& Event::operator =(const Event& e)
{
    if (this != &e)
    {
        Location::operator =(e);
        this->event_id = e.event_id;
        this->name = e.name;
        this->data = e.data;
        this->timp = e.timp;
        this->category = e.category;
        for (int i = 0; i < e.listaPreturi.size(); i++)
            this->listaPreturi.push_back(e.listaPreturi[i]);
    }
    return *this;
}
ostream& operator << (ostream& out, const Event& e)
{
    return e.afisare(out);
}
istream& operator >> (istream& in, Event& e)
{
    return e.citire(in);
}
ifstream& operator >> (ifstream& fin, Event& e)
{
    return e.fisier_c(fin);
}



class Payment : public IOInterface
{
    static int id_contor;
    const int payment_id;
    char tip_plata; //o=online; f=fizic
    double amount;
    bool metoda; //0=card, 1=numerar
    vector <TicketRezervate> lista;

public:

    char gettip_plata() { return this->tip_plata; }
    int getpayment_id() { return this->payment_id; }
    float getamount() const { return this->amount; }
    bool getmetoda() { return this->metoda; }
    vector <TicketRezervate>& getlista() { return this->lista; }

    void settip_plata(char tip_plata)
    {
        if (tip_plata == 'o' || tip_plata == 'O')
            this->tip_plata = 'o';
        else
            if (tip_plata == 'f' || tip_plata == 'F')
                this->tip_plata = 'f';
            else
                functieExceptii(4);
    }
    void setamount(double amount) 
    {
        if (amount > 0)
            this->amount = amount;
        else
            functieExceptii(1);
    }
    void setmetoda(bool metoda) 
    {
        if (metoda == 0)
            this->metoda = 0;
        else
            if (metoda == 1)
                this->metoda = 1;
            else
                functieExceptii(5);
    }
    void setlista(vector <TicketRezervate> lista) // ??? verificare
    {
        for(int i=0; i<lista.size(); i++)
            this->lista[i] = lista[i];
    }

    Payment();
    Payment(char tip_plata, double amount, bool metoda);
    Payment(const Payment& p);
    void modify(vector <Payment>& listaPayment);
    void deleting(vector <Payment>& listaPayment);
    friend TicketRezervate deleting_p(vector <TicketRezervate>& listaTicket);
    void filtru(vector <Payment>& listaPayment);
    Payment& operator =(const Payment& p);

    ostream& afisare(ostream& out) const
    {
        out << "Id-ul platii este: " << this->payment_id << endl;
        out << "Tipul de plata este (o pentru online, f pentru fizic): " << this->tip_plata << endl;
        out << "Valoarea platii este: " << this->amount << endl;
        out << "Metoda de plata este (0 pentru card, 1 pentru numerar): " << this->metoda << endl;
        return out;
    }
    istream& citire(istream& in)
    {
        char aux;
        while (true)
        {
            try
            {
                cout << "Tipul platii este (o pentru online, f pentru fizic): ";

                in >> aux;
                if (in.fail())
                {
                    throw runtime_error("Tipul de plata nu este corecta. Alegeti o litera.\n");
                }
                settip_plata(aux);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (char a)
            {
                if (a == 'c')
                    cout << "Tipul de plata nu este corecta. Alegeti o litera dintre o si f.\n";
            }
            in.clear();
            in.ignore();
        }
        bool m;
        while (true)
        {
            try
            {
                cout << "Metoda de plata este (0 pentru card, 1 pentru numerar): ";

                in >> m;
                if (in.fail())
                {
                    throw runtime_error("Metoda de plata nu este corecta. Alegeti o valoare intreaga.\n");
                }
                setmetoda(m);
                break;

            }
            catch (runtime_error& a)
            {
                cout << a.what();
            }
            catch (int a)
            {
                if (a == 5)
                    cout << "Metoda de plata nu este corecta. Alegeti o valoare intreaga dintre 0 si 1.\n";
            }
            in.clear();
            in.ignore();
        }
        return in;
    }
    ifstream& fisier_c(ifstream& fin)
    {
        int m;
        fin >> this->tip_plata;
        fin >> this->amount;
        fin >> m;
        if (m == 1)
            this->metoda = true;
        else
            this->metoda = false;
        return fin;
    }

    friend ostream& operator << (ostream& out, const Payment& p);
    friend istream& operator >> (istream& in, Payment& p);
    friend ifstream& operator >> (ifstream& fin, Payment& p);

    Payment operator +=(const TicketRezervate& t)
    {
        TicketRezervate aux(t);
        lista.push_back(aux);
        this->amount = this->amount + aux.getprice();
        return *this;
    }
    friend Payment operator += (const TicketRezervate& t, Payment& p)
    {
        TicketRezervate aux(t);
        p.lista.push_back(aux);
        p.amount = p.amount + aux.getprice();
        return p;
    }
    ~Payment()
    {
        id_contor = id_contor - 1;
    }
};
int Payment::id_contor = 0;
Payment::Payment() : payment_id(id_contor)
{
    this->tip_plata = 'f';
    this->amount = 0;
    this->metoda = 0;
}
Payment::Payment(char tip_plata, double amount, bool metoda) : payment_id(id_contor++)
{
    this->tip_plata = tip_plata;
    this->amount = amount;
    this->metoda = metoda;
}
Payment::Payment(const Payment& p) : payment_id(id_contor++)
{
    this->tip_plata = p.tip_plata;
    this->amount = p.amount;
    this->metoda = p.metoda;
    for (int i = 0; i < p.lista.size(); i++)
        this->lista.push_back(p.lista[i]);
}
void Payment::modify(vector <Payment>& listaPayment)
{
    int id, ci;
    float p;
    cout << "Care este id-ul platii pe care vrei sa o modifici? ";
    cin >> id;
    cout << endl;
    for (int i = 0; i < listaPayment.size(); i++)
        if (listaPayment[i].getpayment_id() == id)
        {
            ci = i;
            break;
        }
    cout << "Care este noua valoare? ";
    cin >> p;
    cout << endl;
    listaPayment[ci].setamount(p);
}
void Payment::deleting(vector <Payment>& listaPayment)
{
    int id, ci;
    cout << "Care este id-ul platii pe care vrei sa o stergi? ";
    cin >> id;
    cout << endl;
    for (int i = 0; i < listaPayment.size(); i++)
        if (listaPayment[i].getpayment_id() == id)
        {
            ci = i;
            break;
        }
    listaPayment.erase(listaPayment.begin() + ci);
}
TicketRezervate deleting_p(vector <TicketRezervate>& listaTicket)
{

    int nr, ci = -1;
    bool ok = 0;
    string z;
    string nume;
    while (true)
    {
        try
        {
            string v;
            cout << "Care este numele evenimentului? ";
            cin >> v;
            if (cin.fail())
            {
                throw runtime_error("Numele evenimentului nu este corect. Introduceti un cuvant.\n");
            }
            nume = v;
            break;

        }
        catch (runtime_error& a)
        {
            cout << a.what();
        }
        cin.clear();
        cin.ignore();
    }
    while (true)
    {
        try
        {
            string v;
            cout << "Care este zona ? ";
            cin >> v;
            if (cin.fail() || (v != "A" && v != "B" && v != "C" && v != "D"))
            {
                throw runtime_error("Zona nu este corect. Introduceti o litera dintre A, B, C, D.\n");
            }
            z = v;
            break;

        }
        catch (runtime_error& a)
        {
            cout << a.what();
        }
        cin.clear();
        cin.ignore();
    }
    while (true)
    {
        try
        {
            int v;
            cout << "Care este locul biletului pe care vrei sa il stergi? ";
            cin >> v;
            if (cin.fail() || v <= 0)
            {
                throw runtime_error("Locul biletului nu este corect. Introduceti un numar intreg pozitiv.\n");
            }
            nr = v;
            break;

        }
        catch (runtime_error& a)
        {
            cout << a.what();
        }
        cin.clear();
        cin.ignore();
    }

    for (int i = 0; i < listaTicket.size() && ok == 0; i++)
    {
        if (listaTicket[i].getnume_event() == nume && listaTicket[i].getseat() == nr && listaTicket[i].getzona() == z)
        {
            ci = i;
            ok = 1;
        }
    }
    if (ci != -1)
        listaTicket.erase(listaTicket.begin() + ci);
    else
        cout << "Locul acesta nu este rezervat.\n";
    TicketRezervate t(nume, z, nr, ci);
    return t;
}
void Payment::filtru(vector <Payment>& listaPayment)
{
    cout << "Care este pretul achizitiei? ";
    float pret;
    cin >> pret;
    for (int i = 0; i < listaPayment.size(); i++)
        if (listaPayment[i].getamount() == pret)
        {
            cout << listaPayment[i];
            cout << endl;
        }
}
Payment& Payment::operator =(const Payment& p)
{
    if (this != &p)
    {
        this->tip_plata = p.tip_plata;
        this->amount = p.amount;
        this->metoda = p.metoda;
        for (int i = 0; i < p.lista.size(); i++)
            this->lista.push_back(p.lista[i]);
    }
    return *this;
}
ostream& operator << (ostream& out, const Payment& p)
{
    return p.afisare(out);
}
istream& operator >> (istream& in, Payment& p)
{
    return p.citire(in);
}
ifstream& operator >> (ifstream& fin, Payment& p)
{
    return p.fisier_c(fin);
}


class MeniuInteractiv
{
private:
    static MeniuInteractiv* obiect;
    string data;

    MeniuInteractiv()
    {
        data = "dd.mm.yyyy";
    }

public:
    static MeniuInteractiv* getInstance()
    {
        if (!obiect)
            obiect = new MeniuInteractiv;
        return obiect;
    }

    string getData() { return this->data; }
    void setData(string a)
    {
        if (a != "")
            this->data = a;
    }

    void meniu()
    {
        bool stop = false;
        int i;
        vector <Sala> listaSala;
        vector <Location> listaLocation;
        vector <Event> listaEvent;
        vector <Ticket> listaTicket;
        vector <Payment> listaPayment;
        vector < TicketRezervate> listaTicketRezervate;

        Event d;
        
        for (int i = 0; i < 3; i++)
        {
            fin >> d;
            Location* l;
            Sala* s;
            listaEvent.push_back(d);
            try
            {
                l = dynamic_cast<Location*>(&d);
                if (l == NULL)
                    throw eroareamea;
                listaLocation.push_back(*l);
            }
            catch (const EroareaMea& eroareamea)
            {
                cout << "\n Vectorul location e null.\n";
            }
            catch (const std::bad_cast& e)
            {
                cout << "\n ati gresit dynamic_cast pt location";
                cout << e.what();
            }

            try
            {
                s = dynamic_cast<Sala*>(&d);
                if (s == NULL)
                    throw eroareamea;
                listaSala.push_back(*s);
            }
            catch (const EroareaMea& eroareamea)
            {
                cout << "\n Vectorul sala e null.\n";
            }
            catch (const std::bad_cast& e)
            {
                cout << "\n ati gresit dynamic_cast pt sala";
                cout << e.what();
            }


            /*
            listaLocation.push_back(d);
            listaSala.push_back(d);
            */
        }
        while (stop != true)
        {
            cout << "Apasa 1 daca vrei sa adaugi date" << endl;
            cout << "Apasa 2 daca vrei sa vezi lista de valori" << endl;
            cout << "Apasa 3 daca vrei sa modifici o valoare existenta" << endl;
            cout << "Apasa 4 daca vrei sa stergi o valoare existenta" << endl;
            cout << "Apasa 5 daca vrei sa filtrezi" << endl;
            cout << "Apasa 6 pentru a realiza o comanda" << endl;
            cout << "Apasa 7 pentru stop" << endl;
            cout << "Introdu o comanda: " << endl;
            int comanda1, comanda2, comanda3;
            cin >> comanda1;
            switch (comanda1)
            {
            case 1:
            {
                cout << "Apasa 1 daca vrei sa adaugi date in clasa event" << endl;
                cout << "Apasa 2 daca vrei sa adaugi date in clasa ticket" << endl;
                cout << "Apasa 3 daca vrei sa adaugi date in clasa sala" << endl;
                cout << "Apasa 4 daca vrei sa adaugi date in clasa payment" << endl;
                cout << "Apasa 5 daca vrei sa adaugi date in clasa location" << endl;
                cout << "Apasa 6 daca vrei sa adaugi date in clasa tickete rezervate" << endl;
                cin >> comanda2;
                switch (comanda2)
                {
                case 1:
                {
                    Event a;
                    cin >> a;
                    listaEvent.push_back(a);
                    break;
                }
                case 2:
                {
                    Ticket a;
                    cin >> a;
                    listaTicket.push_back(a);
                    break;
                }
                case 3:
                {
                    Sala a;
                    cin >> a;
                    listaSala.push_back(a);
                    break;
                }
                case 4:
                {
                    Payment a;
                    cin >> a;
                    listaPayment.push_back(a);
                    break;
                }
                case 5:
                {
                    Location a;
                    cin >> a;
                    listaLocation.push_back(a);
                    break;
                }
                case 6:
                {
                    TicketRezervate a;
                    cin >> a;
                    listaTicketRezervate.push_back(a);
                    break;
                }
                default:
                {
                    cout << "Comanda incorecta" << endl;
                    break;
                }
                }
                break;
            }
            case 2:
            {
                cout << "Apasa 1 daca vrei sa vezi lista de valori pentru clasa event" << endl;
                cout << "Apasa 2 daca vrei sa vezi lista de valori pentru clasa ticket" << endl;
                cout << "Apasa 3 daca vrei sa vezi lista de valori pentru clasa sala" << endl;
                cout << "Apasa 4 daca vrei sa vezi lista de valori pentru clasa payment" << endl;
                cout << "Apasa 5 daca vrei sa vezi lista de valori pentru clasa location" << endl;
                cout << "Apasa 6 daca vrei sa vezi lista de valori pentru clasa tickete rezervate" << endl;
                cin >> comanda3;
                switch (comanda3)
                {
                case 1:
                {
                    for (int i = 0; i < listaEvent.size(); i++)
                    {
                        cout << listaEvent[i];
                        cout << endl;
                    }
                    break;
                }
                case 2:
                {
                    for (int i = 0; i < listaTicket.size(); i++)
                    {
                        cout << listaTicket[i];
                        cout << endl;
                    }
                    break;
                }
                case 3:
                {
                    for (int i = 0; i < listaSala.size(); i++)
                    {
                        cout << listaSala[i];
                        cout << endl;
                    }
                    break;
                }
                case 4:
                {
                    for (int i = 0; i < listaPayment.size(); i++)
                    {
                        cout << listaPayment[i];
                        cout << endl;
                    }
                    break;
                }
                case 5:
                {
                    for (int i = 0; i < listaLocation.size(); i++)
                    {
                        cout << listaLocation[i];
                        cout << endl;
                    }
                    break;
                }
                case 6:
                {
                    for (int i = 0; i < listaTicketRezervate.size(); i++)
                    {
                        cout << listaTicketRezervate[i];
                        cout << endl;
                    }
                    break;
                }
                default:
                {
                    cout << "Comanda incorecta" << endl;
                    break;
                }
                }
                break;
            }
            case 3:
            {
                cout << "Apasa 1 daca vrei sa modifici date in clasa event" << endl;
                cout << "Apasa 2 daca vrei sa modifici date in clasa ticket" << endl;
                cout << "Apasa 3 daca vrei sa modifici date in clasa payment" << endl;
                cin >> comanda2;
                switch (comanda2)
                {

                case 1:
                {
                    listaEvent[0].modify(listaEvent);
                    break;
                }
                case 2:
                {
                    listaTicket[0].modify(listaTicket);
                    break;
                }
                case 3:
                {
                    listaPayment[0].modify(listaPayment);
                    break;
                }
                default:
                {
                    cout << "Comanda incorecta" << endl;
                    break;
                }
                }
                break;
            }
            case 4:
            {
                cout << "Apasa 1 daca vrei sa stergi date din clasa event" << endl;
                cout << "Apasa 2 daca vrei sa stergi date din clasa ticket" << endl;
                cout << "Apasa 3 daca vrei sa stergi date din clasa payment" << endl;
                cout << "Apasa 4 daca vrei sa stergi date in clasa location" << endl;
                cout << "Apasa 5 daca vrei sa stergi date in clasa ticket rezervate" << endl;
                cin >> comanda2;
                switch (comanda2)
                {
                case 1:
                {
                    listaEvent[0].deleting(listaEvent);
                    break;
                }
                case 2:
                {
                    listaTicket[0].deleting(listaTicket);
                    break;
                }
                case 3:
                {
                    listaPayment[0].deleting(listaPayment);
                    break;
                }
                case 4:
                {
                    listaLocation[0].deleting(listaLocation);
                    break;
                }
                case 5:
                {
                    listaTicketRezervate[0].deleting(listaTicketRezervate);
                    break;
                }
                default:
                {
                    cout << "Comanda incorecta" << endl;
                    break;
                }
                }
                break;
            }
            case 5:
            {
                cout << "Apasa 1 daca vrei sa filtrezi dupa id-ul unui eveniment" << endl;
                cout << "Apasa 2 daca vrei sa filtrezi dupa pretul unui bilet" << endl;
                cout << "Apasa 3 daca vrei sa filtrezi dupa pretul unei achizitii" << endl;
                cout << "Apasa 4 daca vrei sa filtrezi dupa id-ul unei locatii" << endl;
                int comanda4;
                cin >> comanda4;
                switch (comanda4)
                {
                case 1:
                {
                    listaEvent[0].filtru(listaEvent);
                    break;
                }
                case 2:
                {
                    listaTicket[0].filtru(listaTicket);
                    break;
                }
                case 3:
                {
                    listaPayment[0].filtru(listaPayment);
                    break;
                }
                case 4:
                {
                    listaLocation[0].filtru(listaLocation);
                    break;
                }
                default:
                {
                    cout << "Comanda incorecta" << endl;
                    break;
                }
                }
                break;
            }
            case 6:
            {
                vector <TicketRezervate> l;
                Payment p;
                int ok = 0;
                while (ok == 0)
                {
                    cout << "Apasa 1 pentru a adauga un ticket\n";
                    cout << "Apasa 2 pentru a sterge un ticket\n";
                    cout << "Apasa 3 pentru a vedea ticketele adaugate la comanda\n";
                    cout << "Apasa 4 pentru a incheia tranzactia\n";
                    int comanda3;
                    cin >> comanda3;
                    switch (comanda3)
                    {
                    case 1:
                    {
                        for (int i = 0; i < listaEvent.size(); i++)
                        {
                            cout << listaEvent[i];
                            listaEvent[i].locuri_libere();
                            cout << endl;
                        }
                        int  id, loc;
                        string zona;
                        while (true)
                        {
                            try
                            {
                            
                                cout << "Care este id-ul evnimentului la care doriti sa cumparati bilete? ";
                                int aux;
                                cin >> aux;
                                if (cin.fail())
                                {
                                    throw runtime_error("Id-ul nu este corect. Introduceti un intreg pozitiv.\n");
                                }
                                id = aux;
                                break;
                            }
                            catch (const runtime_error& a)
                            {
                                cout << a.what();
                            }
                            cin.clear();
                            cin.ignore();
                        }
                        while (true)
                        {
                            try
                            {
                                cout << "Care este zona biletului pe care doriti sa il cumparati? ";
                                string aux;
                                cin >> aux;
                                if (cin.fail() || (aux != "A" && aux != "B" && aux != "C" && aux != "D"))
                                {
                                    throw runtime_error("Zona nu este corect. Introduceti o litera dintre A, B, C, D.\n");
                                }
                                zona = aux;
                                break;
                            }
                            catch (const runtime_error& a)
                            {
                                cout << a.what();
                            }
                            cin.clear();
                            cin.ignore();
                        }
                        while (true)
                        {
                            try
                            {
                                cout << "Care este locul biletului pe care doriti sa il cumparati? ";
                                int aux;
                                cin >> aux;
                                if (cin.fail() || aux <= 0)
                                {
                                    throw runtime_error("Locul nu este corect. Introduceti un intreg pozitiv.\n");
                                }
                                loc = aux;
                                break;
                            }
                            catch (const runtime_error& a)
                            {
                                cout << a.what();
                            }
                            cin.clear();
                            cin.ignore();
                        }
                        int ci;
                        for (int i = 0; i < listaEvent.size(); i++)
                            if (listaEvent[i].getevent_id() == id)
                            {
                                ci = i;
                                break;
                            }
                        try
                        {
                            if (listaEvent[ci].getstatus(zona, loc) != 'a')
                                throw eroareamea;
                            TicketRezervate t(listaEvent[ci].getname(), zona, loc, listaEvent[ci].getprice(zona, loc));
                            p += t;
                            l.push_back(t);
                            listaEvent[ci].setstatus(zona, loc, 'r');
                        }
                        catch (const EroareaMea a)
                        {
                            cout << "Locul nu este liber.\n";
                        }
                        
                        break;
                    }
                    case 2:
                    {
                        TicketRezervate t, aux;
                        t = deleting_p(p.getlista());
                        if(t.getprice()!=-1)
                            l[0].deleting_p(l, t);
                        break;
                    }
                    case 3:
                    {
                        for (int i = 0; i < l.size(); i++)
                        {
                            cout << l[i];
                        }
                        break;
                    }
                    case 4:
                    {
                        bool x;
                        while (true)
                        {
                            try
                            {
                                cout << "Doriti sa platiti biletele sau doar sa le rezervati?( introduceti 0 pentru a plati sau 1 pentru a rezerva) ";
                                cin >> x;
                                if (cin.fail())
                                    throw runtime_error("Nu este o optiune valida.");
                                break;
                            }
                            catch (runtime_error& a)
                            {
                                cout << a.what();
                            }
                            cin.clear();
                            cin.ignore();
                        }
                        if (x == 0)
                        {
                            int ci;
                            for (int i = 0; i < l.size(); i++)
                            {
                                for (int j = 0; j < listaEvent.size(); j++)
                                    if (listaEvent[j].getname() == l[i].getnume_event())
                                    {
                                        ci = j;
                                        break;
                                    }
                                listaEvent[ci].setstatus(l[i].getzona(), l[i].getseat(), 's');
                            }
                            cout << "Biletele au fost platite.\n";
                            p.settip_plata('o');
                            p.setmetoda(0);
                        }
                        else
                        {
                            cout << "Biletele sunt rezervate. Aventi timp de 10 zile lucratoare sa finalaziti tranzactia.\n";
                        }
                        ok = 1;
                        listaPayment.push_back(p);
                        break;
                    }
                    default:
                    {
                        cout << "Comanda incorecta.\n";
                        break;
                    }
                    }
                }
                break;
            }
            case 7:
            {
                stop = true;
                break;
            }
            default:
            {
                cout << "Comanda incorecta" << endl;
                break;
            }
            }
        }
    }
    ~MeniuInteractiv()
    {
        if (!this->obiect)
        {
            delete[] this->obiect;
            this->obiect = NULL;
        }
    }
};
MeniuInteractiv* MeniuInteractiv::obiect = 0;


int main()
{
    
    MeniuInteractiv* meniulMeu = meniulMeu->getInstance();
    meniulMeu->setData("10.01.2024");
    meniulMeu->meniu();
    
    return 0;
}
