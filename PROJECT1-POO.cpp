#include <iostream>
using namespace std;
#define SIZE 100
class polinom {
    int grad;
    double coef[SIZE];
    public:
      friend istream& operator>>(istream&, polinom&);
      friend ostream& operator<<(ostream&, const polinom&);
      double calcul(double x);
      polinom operator+(polinom pol2);
      polinom operator-(polinom pol2);
      polinom operator*(polinom pol2);
      friend class pereche;
};
class pereche {
    double nrrel;
    polinom pol;
    public:
        friend istream& operator>>(istream&,pereche&);
        friend ostream& operator<<(ostream&,const pereche&);
        void verific();

};
ostream& operator<<(ostream& out, const polinom& pol) {
    int i;
    out << "Polinomul cu gradul " << pol.grad << endl;
    out << " Si monoamele: " << endl;
    for (i = 0; i <= pol.grad; i++) {
            out << pol.coef[i] << "*X^" << i << " ";
    }
    out << endl;
    return out;
}
istream& operator>>(istream&in,polinom&pol)
{
    int i;
    in>>pol.grad;
    for (i = 0;i <= pol.grad; i++)
        in>>pol.coef[i];
    return in;

}
double polinom::calcul(double x) {
    int i, j;
    double s = 0, p;

    for (i = 0;i <= grad;i++) {
            p=1;
            for (j = i; j > 0; j--) {
                    p = p * x;
            }
            s = s + coef[i] * p;
    }
   return s;
}
polinom polinom::operator+(polinom pol2) {
    int i;
    polinom pol3;

    if (grad >= pol2.grad) {
        pol3.grad = grad;

        for (i = pol2.grad + 1; i <= pol3.grad; i++) {

                pol2.coef[i]=0;
         }
    }
    else {
            pol3.grad = pol2.grad;

            for (i = grad + 1; i <= pol3.grad; i++) {

                coef[i] = 0;
         }
    }
    for (i = 0; i <= pol3.grad; i++) {
            pol3.coef[i] = coef[i] + pol2.coef[i];
    }

    i = pol3.grad;

    while (pol3.coef[i] == 0 && i > 0) {
            i = i--;
    }

    pol3.grad = i;
    return pol3;
}

polinom polinom::operator-(polinom pol2) {
    int i;
    polinom pol3;

    if (grad >= pol2.grad) {
        pol3.grad = grad;

        for (i = pol2.grad + 1; i <= pol3.grad; i++) {
             pol2.coef[i]=0;
        }
    }
    else {
            pol3.grad = pol2.grad;
            for (i = grad + 1; i <= pol3.grad; i++) {
                coef[i] = 0;
            }
         }


    for (i = 0; i <= pol3.grad; i++) {
            pol3.coef[i] = coef[i] - pol2.coef[i];
    }

    i = pol3.grad;

    while (pol3.coef[i] == 0 && i > 0) {
            i = i - 1;
    }

    pol3.grad = i;
    return pol3;

}


polinom polinom::operator*(polinom pol2){
    int i, j;
    polinom pol3;

    pol3.grad = grad + pol2.grad;

    for (i = 0; i <= grad + pol2.grad; i++) {
            pol3.coef[i] = 0;
    }

    for (i = 0; i <= grad; i++) {
         for (j = 0;j <= pol2.grad; j++) {
                pol3.coef[i+j]=pol3.coef[i+j]+coef[i]*pol2.coef[j];
         }
    }
    i = pol3.grad;

    while ((i > 0) && (pol3.coef[i] == 0)) {
            i = i - 1;
    }

    pol3.grad = i;
    return pol3;

}


istream& operator>>(istream &i, pereche&per) {
    i>>per.nrrel;
    cin>>per.pol;
    return i;
}
ostream& operator<<(ostream &o, const pereche& per) {
    o<<"Numarul real "<<per.nrrel<<endl;
    cout<<per.pol;
    return o;
}
void pereche::verific() {
    double rez;
    rez = pol.calcul(nrrel);
    if (rez == 0) {
       cout<<" Este radacina "<<endl;
    }
    else cout<<"Nu este radacina"<<endl;
}


int main()
{
   pereche per1;
   polinom pol1, pol2, pol3;
   cout<<" Se citeste o comanda : 1 pentru a calcula valoarea unui polinom;"<<endl;
   cout<<"                      : 2 pentru suma a doua polinoame;"<<endl;
   cout<<"                      : 3 pentru diferenta a doua polinoame;"<<endl;
   cout<<"                      : 4 pentru produsul a doua polinoame ;"<<endl;
   cout<<"                      : 5 se citeste o pereche formata dintr-un numar real si un polinom si se verifica daca polinomul este sau nu radacina;"<<endl;
   cout<<"                      : 0 pentru finalizarea programului;"<<endl;
   int x;
   double y;
   cin>>x;
   while (x != 0) {
       switch(x) {
           case 1:cout<<"Se citeste numarul real : ";
                  cin>>y;
                  cout<<"Se citeste polinomul : ";
                  cin>>pol1;
                  cout<<pol1.calcul(y);
                  break;

          case 2: cout<<"Se citeste primul polinom : ";
                  cin>>pol1;
                  cout<<"Se citeste al doilea polinom : ";
                  cin>>pol2;
                  pol3=pol1+pol2;
                  cout<<"Suma este : "<<endl<<pol3;
                  break;

          case 3: cout<<"Se citeste primul polinom : ";
                  cin>>pol1;
                  cout<<"Se citeste al doilea polinom : ";
                  cin>>pol2;
                  pol3=pol1-pol2;
                  cout<<"Diferenta dintre primul polinom si al doilea este :"<<endl;
                  cout<<pol3;
                  break;

         case 4:  cout<<"Se citeste primul polinom : ";
                  cin>>pol1;
                  cout<<"Se citeste al doilea polinom : ";
                  cin>>pol2;
                  pol3=pol1*pol2;
                  cout<<pol3;
                  break;

        case 5:   cout<<"Se citeste perechea : (nr real,grad polinom, polinomul) ";
                  cin>>per1;
                  per1.verific();
                  break;
       }
       cin>>x;
   }
    return 0;
}
