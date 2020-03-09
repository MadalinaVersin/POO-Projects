#include <iostream>
#include <cstring>
using namespace std;
class Film {
 private:
   char *nume;
    char* tip;
    int ore;
    int minute;
    int secunde;
    double incasari_cinematograf;
public:
    Film(char* n,char* t,int o,int m,int s,double i);
    Film();
    Film(const Film&ob);
    Film &operator=(const Film&ob);
    int  get_incasari();
    friend istream &operator>>(istream &in, Film &ob);
    friend ostream &operator<<(ostream &out, Film&ob);
    ~Film(){
        delete[]nume;
        delete[]tip;
        }
};
class Personal {
protected:
    char *nume_pers;
    char *cnp;
    int nr_filme;
    Film *nume_film;
    double suma_incasata;
public:
    Personal();
    Personal(char *n, char*cnp, int nr, Film *filme, double suma);
    Personal(const Personal&ob);
    Personal &operator=(const Personal&ob);
    virtual void citire(istream &);
    virtual void afisare(ostream &);
    virtual int get_rol(){};
    friend istream &operator>>(istream &in,Personal &ob);
    friend ostream &operator<<(ostream &out,Personal&ob);
    ~Personal() {
        delete[]nume_pers;
        delete[]cnp;
        }
};
class Regizor:public Personal {
private:
    double suma_fixa;
public:
    Regizor();
    Regizor(char *n, char*cnp, int nr, Film *filme, double suma, double sumfix);
    Regizor(const Regizor&ob);
    Regizor&operator=(const Regizor&ob);
    void citire(istream &);
    void afisare(ostream &);
    void calcul_incasari();
    friend istream &operator>>(istream&in, Regizor&ob);
    friend ostream &operator<<(ostream&out, Regizor&ob);
    ~Regizor(){};

};
class Actor:public Personal {
private:
    int rol;
    double bonus;
public:
    Actor();
    Actor(char *n, char*cnp, int nr, Film *filme, double suma, int r);
    Actor(const Actor&ob);
    Actor&operator=(const Actor&ob);
    void citire(istream &);
    void afisare(ostream &);
    void calc_sum_incasata();
    int get_rol() {
       return rol;
    };
    void calc_bonus();
    friend istream&operator>>(istream &in, Actor&ob);
    friend ostream&operator<<(ostream&out, Actor&ob);
    ~Actor(){}

};
template <class T>class FirmaDistributie {
    static T nr_total_pers;
    static T nr_actori;
    Personal **vectpers;
public:
    FirmaDistributie() {
        vectpers=NULL;
        }
    FirmaDistributie<T>&operator+=(Personal*);
    static void incrementare_pers() {
        nr_total_pers++;
        }
    static void incrementarea_actori(){nr_actori++;}
    void afisare2();
    ~FirmaDistributie() {
        delete[]vectpers;
        }
};
template<>
class FirmaDistributie<unsigned> {
    static unsigned nr_total_pers;
    static unsigned nr_actori_principal;
    Personal**vectpers;
public:
    FirmaDistributie(){vectpers=NULL;}
    FirmaDistributie<unsigned>&operator+=(Personal*);
    static void incrementare_pers() {
        nr_total_pers++;
        }
    static void incementare_act_principal() {
        nr_actori_principal++;
        }
    void rol_actori(int rol);
    void afisare2();
    ~FirmaDistributie() {
        delete[]vectpers;
        }
};
template<class T>
T FirmaDistributie<T>::nr_total_pers=0;

template<class T>
T FirmaDistributie<T>::nr_actori=0;


unsigned FirmaDistributie<unsigned>::nr_actori_principal=0;


unsigned FirmaDistributie<unsigned>::nr_total_pers=0;
void verif_negativ(int a)
{
    try
    {
        if(a<0)
            throw a;
    }
    catch(int x)
    {
        cout<<"Exceptie pe vlaorea "<<x<<"\n";
    }
}

Film::Film()
{
    nume = NULL;
    tip = NULL;
    ore = 0;
    minute = 0;
    secunde = 0;

}

Film::Film(char* n, char* t, int o, int m, int s, double i)
{   nume = new char[strlen(n) + 1];
    tip = new char[strlen(t) + 1];
    strcpy(nume, n);
    strcpy(tip, t);
    ore = o;
    minute = m;
    secunde = s;
    incasari_cinematograf = i;

}
Film::Film(const Film&ob) {
   nume = new char[strlen(ob.nume) + 1];
   tip = new char[strlen(ob.tip) + 1];
   strcpy(nume, ob.nume);
   strcpy(tip, ob.tip);
   ore = ob.ore;
   minute = ob.minute;
   secunde = ob.secunde;
   incasari_cinematograf = ob.incasari_cinematograf;

}
Film & Film ::operator=(const Film&ob) {
    if(this != &ob) {
            nume = new char[strlen(ob.nume) + 1];
            tip = new char[strlen(ob.tip) + 1];
            strcpy(this->nume, ob.nume);
            strcpy(this->tip, ob.tip);
            this->ore = ob.ore;
            this->minute = ob.minute;
            this->secunde = ob.secunde;
            this->incasari_cinematograf = ob.incasari_cinematograf;
    }
    return *this;
}
int Film::get_incasari() {
    return incasari_cinematograf;
}
istream & operator>>(istream &in,Film &ob) {
    char n[30];char t[30];
    cout<<"Introduceti numele filmului: ";
    in>>n;
    cout<<"Introduceti tipul filmului: ";
    in>>t;
    ob.nume=new char[strlen(n)+1];
    ob.tip=new char[strlen(t)+1];
    strcpy(ob.nume,n);
    strcpy(ob.tip,t);
    cout<<"Introduceti cate ore dureaza filmul: ";
    in>>ob.ore;
    cout<<"Introduceti cate minute dureaza filmul: ";
    in>>ob.minute;
    cout<<"Introduceti cate secunde dureaza filmul: ";
    in>>ob.secunde;
    cout<<"Introduceti suma incasata: ";
    in>>ob.incasari_cinematograf;
    return in;
}
ostream &operator<<(ostream &out,Film &ob) {
    out<<ob.nume<<" ";
    out<<ob.tip<<" ";
    out<<ob.ore<<" ";
    out<<ob.minute<<" ";
    out<<ob.secunde<<" ";
    out<<ob.incasari_cinematograf<<" ";
    return out;
}
Personal::Personal() {
    nume_pers = NULL;
    cnp = NULL;
    nr_filme = 0;
    suma_incasata = 0;
    nume_film = NULL;
}
Personal::Personal(char*n,char*c,int nr,Film*filme,double suma)
{
    int i;
    nume_pers = new char[strlen(n) + 1];
    cnp = new char[strlen(c) + 1];
    strcpy(nume_pers, n);
    strcpy(cnp, c);
    nr_filme = nr;
    suma_incasata = suma;
    nume_film = new Film[nr];
    for (i = 0; i < nr; i++) {
        nume_film[i] = filme[i];
    }
}
Personal&Personal::operator=(const Personal&ob) {
    if(this != &ob) {
        int i;
        nume_pers = new char[strlen(ob.nume_pers) + 1];
        strcpy(nume_pers, ob.nume_pers);
        cnp = new char[strlen(ob.cnp) + 1];
        strcpy(cnp, ob.cnp);
        nr_filme = ob.nr_filme;
        suma_incasata = ob.suma_incasata;
        for (i = 0; i < nr_filme; i++) {

                nume_film[i]=ob.nume_film[i];
        }


    }
    return *this;

}
Personal::Personal(const Personal&ob) {  int i;
    nume_pers = new char[strlen(ob.nume_pers) + 1];
    strcpy(nume_pers, ob.nume_pers);
    cnp = new char[strlen(ob.cnp) + 1];
    strcpy(cnp, ob.cnp);
    nr_filme = ob.nr_filme;
    nume_film = new Film[ob.nr_filme];
    for (i = 0; i < nr_filme; i++) {
            nume_film[i] = ob.nume_film[i];
    }
    suma_incasata = ob.suma_incasata;

}
void Personal::citire(istream & i) {
    int j;
    char n[30], c[20];
    Film F[20];
    cout<<"Introduceti numele persoanei: ";
    i>>n;
    cout<<"Introduceti cnp-ul: ";
    i>>c;
    cout<<"Introduceti numarul de filme la care a participat: ";
    i>>nr_filme;
    cout<<"Introduceti filmele : "<<endl;
    nume_film = new Film[nr_filme];
    for (j = 0;j < nr_filme; j++) {
        i>>F[j];
        nume_film[j] = F[j];
        }
     nume_pers = new char[strlen(n) + 1];
     strcpy(nume_pers, n);
     cnp = new char[strlen(c) + 1];
     strcpy(cnp, c);
     cout<<"Introduceti suma incasata de persoana: ";
     i>>suma_incasata;

}
void Personal::afisare(ostream &out)
{
    int i;
    out<<"Persoana " <<nume_pers<<" a participat la "<<nr_filme<<"filme"<<endl;
    out<<"Filmele  la care a participat sunt: "<<endl;
    for (i = 0; i < nr_filme; i++) {

            out<<nume_film[i]<<endl;
    }
}
istream &operator>>(istream & i,Personal &b) {
    b.citire(i);
    return i;
}
ostream &operator<<(ostream &out,Personal&b) {
    b.afisare(out);
    return out;

}
Regizor::Regizor():Personal() {
    suma_fixa = 0;

}
Regizor::Regizor(char*n, char*cnp, int nr, Film*filme, double suma, double sumfix):Personal(n, cnp, nr, filme, suma) {
    suma_fixa = sumfix;

}
Regizor&Regizor::operator=(const Regizor&ob) {
    if(this != &ob) {
        this->Personal::operator=(ob);
        suma_fixa = ob.suma_fixa;
        return *this;
    }
}
Regizor::Regizor(const Regizor &ob):Personal(ob) {
    suma_fixa = ob.suma_fixa;
}
void Regizor::citire(istream &i) {
    Personal::citire(i);
    cout<<"Se citeste suma fixata pentru regizor: ";
    i>>suma_fixa;

}
void Regizor::afisare(ostream &out) {
    Personal::afisare(out);
    cout<<"Se afiseaza suma fixa: ";
    out<<suma_fixa<<endl;
    cout<<"Se afiseaza suma totala incasata de regizor: ";
    calcul_incasari();
    cout<<suma_incasata<<endl;
}
void Regizor::calcul_incasari() {
    int j;
    for (j = 0; j < nr_filme; j++) {
        suma_incasata = suma_incasata + suma_fixa;
    }
}
istream &operator>>(istream& in,Regizor &b) {
    b.citire(in);
    return in;

}
ostream&operator<<(ostream&out,Regizor &b) {
    b.afisare(out);
    return out;
}
Actor::Actor():Personal() {
    rol=0;
    bonus=0;
}
Actor::Actor(char*n, char*c, int nr, Film*filme, double suma, int r):Personal(n, c, nr, filme, suma) {
    rol = r;
    bonus = 0;
}
Actor&Actor::operator=(const Actor&ob) {
    if(this != &ob) {
        this->Personal::operator=(ob);
        rol = ob.rol;
        bonus = ob.bonus;
    }
    return *this;

}
Actor::Actor(const Actor&ob):Personal(ob) {
    rol = ob.rol;
    bonus = ob.bonus;
}
void Actor::citire(istream&i) {
    Personal::citire(i);
    cout<<"Se citeste rolul actorului (1 daca este rol principal si -1 daca este rol secundar) : ";
    i>>rol;
}
void Actor::afisare(ostream &out) {
    Personal::afisare(out);
    cout<<"Rolul este: ";
    out<<rol<<endl;
    calc_sum_incasata();
    cout<<"Incasarile actorului cu tot cu bonusuri sunt: ";
    out<<suma_incasata<<endl;
}
void Actor::calc_bonus() {
    int j;
    for (j = 0;j < nr_filme; j++) {
            bonus=bonus+0.1*nume_film[j].get_incasari();
    }
}
void Actor::calc_sum_incasata() {
    if(rol==1) {
        calc_bonus();
    }
    suma_incasata = suma_incasata + bonus;
}
istream&operator>>(istream&a,Actor &ob) {
    ob.citire(a);
    return a;
}
ostream&operator<<(ostream&out,Actor&ob) {
    ob.afisare(out);
    return out;

}

void FirmaDistributie<unsigned>::rol_actori(int r)
{
    /*try{
    if((r!=1)&&(r!=-1))
       throw r;}
       catch(int r)
       {
           cout<<"Valuarea data pt rolul actorilor este incorecta";
       }*/
    if(r == 1) {
        incementare_act_principal();
    }
}
template <class T>
FirmaDistributie<T>&FirmaDistributie<T>::operator+=(Personal *x)
{
    int i;
    verif_negativ(nr_total_pers);
    Personal **aux;
    aux = new Personal*[nr_total_pers + 1];
    for (i = 0; i < nr_total_pers; i++) {
        aux[i]=vectpers[i];
    }
    aux[nr_total_pers] = x;
    Personal**a;
    a = aux;
    aux = vectpers;
    vectpers = a;
    delete[]aux;
    incrementare_pers();
    return*this;

}

FirmaDistributie<unsigned>&FirmaDistributie<unsigned>::operator+=(Personal*x) {
    int i;
    verif_negativ(nr_total_pers);
    Personal**aux;
    aux = new Personal*[nr_total_pers+1];
    for (i = 0; i < nr_total_pers; i++) {
        aux[i] = vectpers[i];
    }
    aux[nr_total_pers] = x;
    Personal**a;
    a = aux;
    aux = vectpers;
    vectpers = a;
    delete[]aux;
    incrementare_pers();
    return *this;
}
template<class T>
void FirmaDistributie<T>::afisare2() {
    int i;
    cout<<"NUMARUL TOTAL DE PERSOANE ESTE :"<<nr_total_pers<<endl;
    for (i = 0;i < nr_total_pers; i++) {
        vectpers[i]->afisare(cout);
        cout<<endl;
    }
}
void FirmaDistributie<unsigned>::afisare2() {
    int i;
    cout<<"NUMARUL TOTAL DE PERSOANE ESTE :"<<nr_total_pers<<endl;
    cout<<"NUMARUL TOTAL DE ACTORI IN ROL PTINCIPAL :"<<nr_actori_principal<<endl;
    for (i = 0;i < nr_total_pers; i++) {
        cout<<endl;
        vectpers[i]->afisare(cout);
        cout<<endl;
    }
}

int main()
{  int i;
    /*Film M[10];
    for ( i = 0; i < 3; i++) {
            cin>>M[i];
    }
    for ( i = 0; i < 3; i++) {
            cout<<M[i];
            }
    */

   FirmaDistributie<unsigned>a;
   int nr;
   cout<<"Se citeste numarul de persoane: ";
   cin>>nr;
   int tip;
   for (i = 1; i <= nr; i++) {
      cout<<"Se citeste tipul persoanei(1 actor,2regizor): ";
      cin>>tip;
      if (tip == 1){
            Personal* b;
            b = new Actor();
            b->citire(cin);
            int x = b->get_rol();
            a.rol_actori(x);
            a += b;

      }
      else {
            Personal*c;
            c = new Regizor();
            c->citire(cin);
            a += c;
      }
   }
   a.afisare2();

    return 0;
}
