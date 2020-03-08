#include <iostream>
using namespace std;
class Matrice {
    int nr_l_c;
    int **mat;
public:
    Matrice();//implicit
    Matrice(int dim, int*a);//E SUPLIMENTAR!!
    Matrice(int dim, int **a);
    Matrice(const Matrice&);
    Matrice& operator = (const Matrice&);
    ~Matrice();
    int getelement(int i, int j) {
        return mat[i][j];
    }
    int setelement(int i, int j, int val) {
        mat[i][j] = val;
    }
    friend ostream& operator<<(ostream&, const Matrice&);
    friend istream& operator>>(istream&, Matrice&);
};
class Vector {
private:
    int dim;
    int *v;
public:
    Vector();
    Vector(int* vect, int n );
    Vector& operator = (const Vector&);
    Vector(const Vector&);
    ~Vector();
    friend istream& operator>>(istream&, Vector&);
    friend ostream& operator<<(ostream&, const Vector&);

    friend class Lista;

};
class Lista {
private:
    Vector *l;
    int nr_linii;
public:
    Lista();
    Lista(int nr, Vector *li);
    Lista& operator = (const Lista&);
    Lista(const Lista&);
    ~Lista();
    friend istream& operator>>(istream&,Lista&);
    friend ostream& operator<<(ostream&,const Lista&);
};
class Graf {
protected:
        int nr_noduri;
public:
        Graf(int i) {
            nr_noduri = i;
            cout<<"S-a apelat constructorul pentru graf"<<endl;
        }
        ~Graf() {
             cout<<"S-a apelat destructorul pentru graf"<<endl;
        }
        virtual void afisare() = 0;
};
class Graf_Neorientat: public Graf {
        Lista GN;
public:
        Graf_Neorientat(Lista L, int nr):Graf(nr) {
            cout<<"S-a apelat constructorul pentru graf neorientat "<<endl;
            GN=L;
        }
        void afisare() {
            cout<<"Se afiseaza graful neorientat "<<endl<<GN<<endl;
        }
        ~Graf_Neorientat() {
            cout<<" S-a apelat destructorul pentru graf neorientat"<<endl;
        }

};
class Graf_Orientat:public Graf {
        Matrice GO;
public:
         Graf_Orientat(Matrice M, int nr):Graf(nr) {
             GO = M;
         }
         void afisare() {
             cout<<"Se afiseaza graful orientat "<<endl<<GO<<endl;
         }
         ~Graf_Orientat() {
             cout<<"S-a apelat destructorul pentru graf orientat"<<endl;
         }
         void vector_tati(int nod_start) {
             int i, j, ok;
             Vector *p;
             int *c;
             Matrice Mcopy;
             Mcopy = GO;
             int nr = 0, l;
             ok = 1;

             for (i = 0; i < nr_noduri; i++) {
                for (j = 0; j < nr_noduri; j++) {
                    if(Mcopy.getelement(i, j) == 1) {
                            Mcopy.setelement(j, i, 1);
                    }
                }
             }

            for (i = 0; i < nr_noduri && ok == 1; i++) {
                  ok = 0;
                  for (j = 0; j <= nr_noduri; j++) {
                      if (Mcopy.getelement(i, j) == 1) {
                            ok = 1;
                      }
                  }
            }

         }

        if (ok == 0) {
                cout<<"Graful nu este conex;"<<endl;
        }
        else {
            cout<<"Graful este conex;"<<endl;

            p=new Vector[nr_noduri];

            for (j = 0; j < nr_noduri; j++) {
                    if (j != nod_start) {

                         nr = 0;

                        for (i = 0; i < nr_noduri; i++) {
                                if (GO.getelement(i, j) == 1) {
                                        nr = nr + 1;
                                }
                        }
                        c = new int[nr];
                        l = 0;

                        for (i = 0; i < nr_noduri; i++) {
                                if (GO.getelement(i, j) == 1) {
                                    c[l] = i + 1;
                                    l++;
                                }

                        }
                    }

                     else {
                        nr = 1;
                        c = new int;
                        c[0] = 0;
                     }
            }



             Vector f(c, nr);
             p[j] = f;

             delete[] c;

        }
            Lista L_tati(nr_noduri, p);
            cout<<L_tati;

 };

Matrice::Matrice() {
    nr_l_c = 0;
    mat = 0;
    cout<<"S-a apelat constructorul implicit pentru matrice"<<endl;
}

Matrice ::Matrice(int dim, int*a) {
    int i, j;
    this->nr_l_c = dim;
    this->mat = new int*[nr_l_c];

    for (i = 0; i < dim; i++) {
        this->mat[i] = new int[dim];
        for (j = 0; j < dim; j++) {
            this->mat[i][j] =  a[i * nr_l_c + j];
        }
    }
    cout<<"S-a apelat constructorul de initializare suplimentar pentru matrice!"<<endl;
}
Matrice::Matrice(int dim,int **a) {
    int i, j;
    this->nr_l_c = dim;
    this->mat = new int*[nr_l_c];

    for (i = 0; i < dim; i++) {
        this->mat[i] = new int[dim];
        for (j = 0; j < dim; j++) {
            this->mat[i][j]=a[i][j];
        }
    }
    cout<<"S-a apelat constructorul de initializare pentru matrice!"<<endl;

}
Matrice::Matrice(const Matrice& M) {
    int i, j;
    nr_l_c = M.nr_l_c;
    mat = new int*[M.nr_l_c];

    for (i = 0; i < M.nr_l_c; i++) {
        mat[i] = new int[nr_l_c];
           for (j = 0; j < M.nr_l_c; j++) {
              mat[i][j] = M.mat[i][j];
           }
    }
       cout<<"S-a apelat constructorul de copiere pentru matrice!"<<endl;
}
Matrice::~Matrice() {
    int i;

    if (mat){
        for (i = 0; i < nr_l_c; i++)
           if(mat[i]) delete []mat[i];
    }
    delete[] mat;
    cout<<" S-a apelat destructorul pentru matrice !"<<endl;
}
Matrice& Matrice::operator=(const Matrice& M) {
    int i, j;

    if (this != &M) {
        if (mat) {
            for (i = 0; i < nr_l_c; i++) {
                if(mat[i]) delete[] mat[i];
            }
            delete[] mat;
        }
        nr_l_c = M.nr_l_c;
        mat = new int* [M.nr_l_c];

        for (i = 0; i < M.nr_l_c; i++) {
            mat[i] = new int[M.nr_l_c];
            for (j = 0; j < M.nr_l_c; j++) {
                mat[i][j] = M.mat[i][j];
            }

        }
}
    cout<<"S-a folosit operatorul '=' supraincarcat !"<<endl;
    return *this;
}
ostream& operator<<(ostream&out, const Matrice& M) {
    int i, j;

    for (i = 0; i < M.nr_l_c; i++) {
        for (j = 0; j < M.nr_l_c; j++) {
            out<<M.mat[i][j]<<" ";
        }
        out<<endl;
    }
    return out;
}
istream& operator>>(istream& in, Matrice&M) {
    int i, j;
    in>>M.nr_l_c;
    M.mat = new int*[M.nr_l_c];

    for (i = 0; i < M.nr_l_c; i++) {
            M.mat[i] = new int[M.nr_l_c];
            for (j = 0; j < M.nr_l_c; j++) {
                in>>M.mat[i][j];
            }
    }

    return in;

}

Vector::Vector() {
    dim = 0;
    v = 0;
    cout<<"S-a apelat constructorul implicit pentru vector!"<<endl;
}
Vector::Vector(int*vect, int n) {
    int i;
    this->dim = n;
    this->v = new int[n];
    for (i = 0; i < n; i++) {
        this->v[i]=vect[i];
    }
    cout<<"S-a apelat constructorul de initializare pentru vector!"<<endl;
}
Vector::Vector(const Vector& V) {
    int i;
    dim = V.dim;
    v  = new int[V.dim];

    for (i = 0; i < V.dim; i++) {
        v[i] = V.v[i];
    }
    cout<<"S-a apelat constructorul de copiere pentru vector!"<<endl;
}
Vector& Vector::operator=(const Vector& V) {
    int i;
    if(this != &V) {
        if(v) {
            delete[] v;
        }
    }
    dim = V.dim;
    v = new int[V.dim];

    for (i = 0; i < V.dim; i++){
            v[i]=V.v[i];
    }
    cout<<" S-a apelat operatorul '=' pentru vector!"<<endl;
    return *this;
}
Vector::~Vector() {
    if(v)
        delete[] v;
    cout<<"S-a apelat destructorul pentru vector"<<endl;

}
ostream& operator<<(ostream& out, const Vector&V) {
    int i;
    for (i = 0; i < V.dim; i++) {
        out<<V.v[i]<<" ";
    }
        return out;
}
istream& operator>>(istream& in, Vector& vect) {
    int i;
    in>>vect.dim;
    vect.v = new int[vect.dim];

    for (i = 0; i < vect.dim; i++) {
         in>>vect.v[i];
    }
    return in;
}

Lista::Lista(int nr, Vector *li) {
    int i;
    nr_linii = nr;
    l = new Vector[nr];

    for (i = 0; i < nr; i++) {
      l[i] = li[i];
    }
}
Lista::Lista() {
    nr_linii = 0;
    l = 0;
    cout<<"S-a apelat constructorul implicit pt liste!"<<endl;

}
Lista& Lista::operator=(const Lista& L) {
    int i, j;
    if(this != &L) {
        if(l) {
            for (i = 0; i < nr_linii; i++) {
                if(l[i].v)
                delete[]l[i].v;
             }
        }
             delete []l;

    }
    nr_linii = L.nr_linii;
    l = new Vector[L.nr_linii];

    for (j = 0; j < L.nr_linii; j++) {
            l[j]=L.l[j];
    }
    cout<<"S-a apelat operatorul '=' pentru clasa liste"<<endl;
    return *this;

}
Lista::Lista(const Lista& L) {
    int j;
    nr_linii = L.nr_linii;
    l = new Vector[L.nr_linii];

    for (j = 0; j < nr_linii; j++) {
        l[j] = L.l[j];
    }
        cout<<"S-a apelat constructorul de copiere pentru liste"<<endl;

}
Lista ::~Lista() {
    int i;
    if(l) {
      delete[]l;
    }
    cout<<"S-a apelat destructorul pentru lista!"<<endl;
}
ostream& operator<<(ostream& out,const Lista& L) {
     int i;
     for (i = 0; i < L.nr_linii; i++) {
            out<<L.l[i]<<endl;
     }
        return out;
 }


int main()
{
    int i,n,j,m,x;
    cout<<"1 =se citeste o lista se copiaza intr-o alta lista ,se afiseaza lista si  graful neorientat , dat sub forma de lista"<<endl;
    cout<<"2 =se citeste o matrice se copiaza aceasta si se afiseaza vectorul de tati al unui graf orientat realizat pe baza acestei matrice"<<endl;
    cin>>x;
    while (x != 0) {

       if (x == 1) {
        Vector *p;
        int *c;
        cout<<"Se citetse numarul de linii ale listei: ";

        cin>>n;
        p = new Vector[n];

        for (i = 0; i < n; i++) {
            cout <<"Se citeste numarul de elemente ale vectorului " << i << " din lista : ";
            cin >> m;
            c = new int[m];
            for (j = 0; j < m; j++)
            cin>>c[j];
            Vector f(c,m);
            p[i] = f;
            delete[] c;
        }
        Lista L(n, p);
        Lista M;
        M = L;
        cout<<M;
        Graf_Neorientat G(L, n);
        G.afisare();
      }

     if(x==2) {
        int **a;
        cin>>n;
        a = new int*[n];
        for (i = 0; i < n; i++) {
              a[i] = new int[n];
              for (j = 0; j < n; j++) {
                        cin>>a[i][j];
              }

        }
        Matrice E(n, a);
        cout<<E;
        Graf_Orientat G(E, n);
        G.afisare();
        int s = 0;
        G.vector_tati(s);
    }
        cin>>x;
    }

    return 0;
}
