#include <iostream>
#include <cmath>
using namespace std;

class Vector_Complex;

class Complex {
    double m_real, m_imaginar;

public:
    //Constructori
    Complex(): m_real(0), m_imaginar(0){}

    Complex(double real, double imaginar): m_real(real), m_imaginar(imaginar){}

    Complex(double real): m_real(real), m_imaginar(0){}

    //Constructor de copiere
    Complex(Complex &complex):m_real(complex.m_real), m_imaginar(complex.m_imaginar){}

    //Destructor
    ~Complex(){}

    //Getteri
    double GetReal(){
        return m_real;
    }

    double GetImaginary(){
        return m_imaginar;
    }

    //Setteri
    void SetReal(double real){
        m_real = real;
    }

    void SetImaginary(double imaginar){
        m_imaginar = imaginar;
    }

    //supraincarcare << si >>
    friend std::istream& operator>> (std::istream& in, Complex& complex){
        in >> complex.m_real >> complex.m_imaginar;
        return in;
    }

    friend std::ostream& operator<< (std::ostream& out, Complex& complex){
        //out << complex.m_real << " " << complex.m_imaginar;
        if (complex.m_imaginar == 0)
            out << complex.m_real << "; "; //afisarea doar partii reale
        else
            if (complex.m_real == 0)
                if (complex.m_imaginar > 0)
                    out << "i*" << complex.m_imaginar << "; "; //afisare sub forma "i*a"
                else
                    out << "-i*" << -complex.m_imaginar << "; "; //afisare sub forma "-i*a"
            else
                if (complex.m_imaginar > 0)
                    out << complex.m_real << "+i*" << complex.m_imaginar << "; "; //afisare sub forma "a+i*b"
                else
                    out << complex.m_real << "-i*" << -complex.m_imaginar << "; " ; //afisare sub forma "a -i*b"

        return out;
    }

    //operator +
    friend Complex operator+ (Complex c1, Complex c2);

    //operator -
    friend Complex operator- (Complex c1, Complex c2);

    //operator *
    friend Complex operator* (Complex c1, Complex c2);

    //operator /
    friend Complex operator/ (Complex c1, Complex c2);

    //modulul unui numar
    double Abs();

    friend class Vector_Complex;

};

Complex operator+ (Complex c1, Complex c2)
{
    Complex result;
    result.m_real = c1.m_real + c2.m_real;
    result.m_imaginar = c1.m_imaginar + c2.m_imaginar;
    return result;
}

Complex operator- (Complex c1, Complex c2)
{
    Complex result;
    result.m_real = c1.m_real - c2.m_real;
    result.m_imaginar = c1.m_imaginar - c2.m_imaginar;
    return result;
}

Complex operator* (Complex c1, Complex c2)
{
    Complex result;
    result.m_real = c1.m_real * c2.m_real - c1.m_imaginar * c2.m_imaginar;
    result.m_imaginar = c1.m_real * c2.m_imaginar + c2.m_real * c1.m_imaginar;

    return result;
}

Complex operator/ (Complex c1, Complex c2)
{
    Complex result;
    result.m_real = (c1.m_real * c2.m_real + c1.m_imaginar * c2.m_imaginar) / (c2.m_real * c2.m_real + c2.m_imaginar * c2.m_imaginar);
    result.m_imaginar = (c1.m_imaginar * c2.m_real - c1.m_real * c2.m_imaginar) / (c2.m_real * c2.m_real + c2.m_imaginar * c2.m_imaginar);

    return result;
}

double Complex::Abs()
{
    return sqrt(m_real * m_real + m_imaginar * m_imaginar);
}

//citim n obiecte de tip Complex, memeoram si afisam
void readNComplexNumbers()
{
    cout << "Numarul de numere complexe de citit:" << endl;
    int n;
    cin >> n;

    cout << "Scrie " << n << " numere complexe:" << endl;

    Complex* numbers = new Complex[n];
    for (int i = 0; i < n; i ++){
        //citim numerele
        cin >> numbers[i];
    }

    cout << "Ai memorat urmatoarele " << n << " numere complexe:" << endl;
    for (int i = 0; i < n; i++){
        cout << numbers[i] << endl;
    }

}

class Vector_Complex
{
    int m_lungime_vector;
    Complex m_vector_complex[1000];

public:

    //Constructori
    Vector_Complex(): m_lungime_vector(0){} //Constructor pentru vector vid

    Vector_Complex(int nr, int lungime): m_lungime_vector(lungime) //Constructor pentru un vector cu un numar dat pe toate componentele
    {
        for (int i = 0; i < lungime; i ++){
            m_vector_complex[i] = nr;
        }
    }

    Vector_Complex(Complex a[], int lungime): m_lungime_vector(lungime) //Cpnstructor pentru a initializa un Vector_Complex
    {                                                                   //dintr-un vector de tip Complex si lungimea sa
        for (int i = 0; i < lungime; i ++){
            m_vector_complex[i] = a[i];
        }
    }

    Vector_Complex(int lungime, Complex a[]): m_lungime_vector(lungime) //Cpnstructor pentru a initializa un Vector_Complex
    {                                                                   //din lungimea unui vector si vectorul respectiv de tip Complex
        for (int i = 0; i < lungime; i ++){
            m_vector_complex[i] = a[i];
        }
    }

    Vector_Complex(const Vector_Complex &a): m_lungime_vector(a.m_lungime_vector) //Copy constructor
    {
        for (int i = 0; i < m_lungime_vector; i ++){
            m_vector_complex[i] = a.m_vector_complex[i];
        }
    }

    //Destructor
    ~Vector_Complex(){
        //m_lungime_vector = 0;
    }

    //Getteri
    int GetLungime_Vector() //returneaza lungimea vectorului
    {
        return m_lungime_vector;
    }

    Complex GetComplex_i(int i)
    {
        return m_vector_complex[i]; //returneaza valoarea de la pozitia i din vector
    }

    void SetLungime_Vector(int lungime)
    {
        m_lungime_vector = lungime; //seteaza lungimea vectorului
    }

    void SetComplex_i(Complex c, int i)
    {
        m_vector_complex[i] = c; //seteaza c pe pozitia i din vector
    }

    //Operatori
    friend std::istream& operator>> (std::istream& in, Vector_Complex &v){

        cout << "Introdu numarul de elemente ale vectorului:" << endl;
        in >> v.m_lungime_vector;
        if (v.m_lungime_vector != 0) //Daca vectorul este vid, atunci nu se mai afiseaza mesajul urmator
            cout << "Introdu vectorul sub forma 'real imaginar':" << endl;
        for (int i = 0; i < v.m_lungime_vector; i ++)
            in >> v.m_vector_complex[i];
        cout << endl;
        return in;
    }

    friend std::ostream& operator<< (std::ostream& out, Vector_Complex &v){

        for (int i = 0; i < v.m_lungime_vector; i ++)
            out << v.m_vector_complex[i] << " ";

        return out;
    }

    Complex suma_el_vector(); //Metoda pentru a afisa suma tuturor elementelor din vectorul apelat

    double* vector_modul(); //Metoda care returneaza un array dinamic reprezentand vectorul modulelor unui vector

    void sortare_vector();  //Metoda de sortare a vectorului dupa vectorul modulelor
};

void readNComplexVectors()
{
    int nr_vectori;
    cout << "Numarul de vectori de tip complex de citit:" << endl;
    cin >> nr_vectori;
    cout << endl;

    Vector_Complex* vectori = new Vector_Complex[nr_vectori];
    for (int i = 0; i < nr_vectori; i ++){
        cin >> vectori[i];
    }

    cout << "Ai memorat urmatorii " << nr_vectori << " vectori:" << endl;
    for (int i = 0; i < nr_vectori; i++){
        if (vectori[i].GetLungime_Vector() != 0) //daca este vector nul, atunci nu se mai afiseaza cele 2 end lines
            cout << vectori[i] << endl << endl;
        else
            cout << "Vector vid\n\n";
    }
}

Vector_Complex* DemoReadNComplexVectors(int nr_vectori)
{
    Vector_Complex* vectori = new Vector_Complex[nr_vectori];
    for (int i = 0; i < nr_vectori; i ++){
        cin >> vectori[i];
    }

    cout << "Ai memorat urmatorii " << nr_vectori << " vectori:" << endl;
    for (int i = 0; i < nr_vectori; i++){
        if (vectori[i].GetLungime_Vector() != 0) //daca este vector nul, atunci nu se mai afiseaza cele 2 end lines
            cout << vectori[i] << endl << endl;
        else
            cout << "Vector vid\n\n";
    }

    return vectori;
}

Complex Vector_Complex::suma_el_vector()
{
    Complex resultat;
    for (int i = 0; i < m_lungime_vector; i ++){
        resultat = resultat + m_vector_complex[i];
    }

    return resultat;
}

double* Vector_Complex::vector_modul()
{
    double *v_module = new double[m_lungime_vector];
    for (int i = 0; i < m_lungime_vector; i ++)
        v_module[i] = m_vector_complex[i].Abs();

    return v_module;
}

void Vector_Complex::sortare_vector()
{
    //Vector_Complex v(m_vector_complex, m_lungime_vector);
    double* v_module = this->vector_modul();
    double aux;
    Complex aux1;

    for (int i = 0; i < m_lungime_vector - 1; i ++)
        for (int j = i + 1; j < m_lungime_vector; j ++){
            if (v_module[j] < v_module[i]){
                aux = v_module[j];
                v_module[j] = v_module[i];
                v_module[i] = aux;
                //swap(v_module[j], v_module[i]); Nu a functionat pe alte compilatoare, nu stiu de ce

                aux1 = m_vector_complex[j];
                m_vector_complex[j] = m_vector_complex[i];
                m_vector_complex[i] = aux1;
                //swap(m_vector_complex[j], m_vector_complex[i]); Nu a functionat pe alte compilatoare, nu stiu de ce
            }
        }
}


//Meniu interactiv

void afisare_optiuni()
{
    cout << "1. Citire, memorare si afisare a n vectori de tip Complex:\n";
    cout << "2. Citire si memorare a unui vector de tip Complex:\n";
    cout << "3. Afisare suma elementelor din vectorul dat cu ajutorul optiunii 2:\n";
    cout << "4. Afisare a vectorului de module corespunzator vectorului dat cu ajutorul optiunii 2:\n";
    cout << "5. Sortare a vectorului dat cu ajutorul optiunii 2 dupa modul:\n";
    cout << "6. Stergere a vectorului dat la optiunea 2 si citirea si memorarea a unui nou vector de tip Complex:\n";
    cout << "7. Afisarea vectorului:\n";
    cout << "8. Demo citire, memorare si afisare a n vectori de tip Complex:\n";
    cout << "9. Afisare suma fiecarui vector dat cu ajutorul optiunii 8:\n";
    cout << "10. Afisare vectorii de module ai celor n vectori dati cu ajutorul optiunii 8:\n";
    cout << "0. Oprire program.\n\n";
}

void meniu_interactiv()
{
    cout << "Alegeti urmatoarele optiuni:\n\n";
    afisare_optiuni();

    int optiune = 0, nr_vectori_demo = 0;
    double* demo_vector_modul;
    Complex suma;
    Vector_Complex v;
    Vector_Complex* n_vectori;

    cin >> optiune;
    cout << endl;

    while (optiune != 0){
        if (optiune == 1)
            readNComplexVectors();

        else if (optiune == 2 || optiune == 6){
            cin >> v;
            cout << "Ati memorat vectorul cu succes!\n\n";
        }

        else if (optiune == 3){
            if (v.GetLungime_Vector() > 0){
                suma = v.suma_el_vector();
                cout << "Suma tuturor elementelor din vector este: " << suma << endl << endl;
            }
            else
                cout << "Nu a fost dat niciun vector!\n\n";
        }

        else if (optiune == 4){
            if (v.GetLungime_Vector() > 0){
                for (int i = 0; i < v.GetLungime_Vector(); i ++)
                    cout << v.vector_modul()[i] << "; ";
                cout << endl  << endl;
            }
            else
                cout << "Nu a fost dat niciun vector!\n\n";
        }

        else if (optiune == 5){
            if (v.GetLungime_Vector() > 0){
                v.sortare_vector();
                cout << "Vectorul a fost sortat!\n\n";
            }
            else
                cout << "Nu a fost dat niciun vector!\n\n";
        }

        else if (optiune == 7)
            cout << "Vectorul este:\n\n" << v;

        else if (optiune == 8){
            cout << "Numarul de vectori de tip complex de citit:\n";
            cin >> nr_vectori_demo;
            cout << endl;
            n_vectori = DemoReadNComplexVectors(nr_vectori_demo);
        }

        else if (optiune == 9){
            if (nr_vectori_demo > 0)
                for (int i = 0; i < nr_vectori_demo; i ++){
                    suma = n_vectori[i].suma_el_vector();
                    cout << "Suma tuturor elementelor din vectorul " << i << " este: " <<  suma << endl;
                }
            else
                cout << "Nu au fost dati n vectori cu ajutorul optiunii 8!\n\n";
        }

        else if (optiune == 10){
            if (nr_vectori_demo > 0)
                for (int i = 0; i < nr_vectori_demo; i ++){
                    for (int j = 0; j < n_vectori[i].GetLungime_Vector(); j ++)
                        cout << n_vectori[i].vector_modul()[j] << "; ";
                        cout << endl  << endl;
                }
            else
                cout << "Nu au fost dati n vectori cu ajutorul optiunii 8!\n\n";
        }

        else
            cout << "Optiune necunoscuta!! \n\n";


        //Se afiseaza din nou optiunile si se citeste optiunea.
        cout << "Alegeti urmatoarele optiuni:\n\n";
        afisare_optiuni();

        cin >> optiune;
        cout << endl;
    }
    delete[] n_vectori;
}

int main()
{
    meniu_interactiv();

    return 0;
}
