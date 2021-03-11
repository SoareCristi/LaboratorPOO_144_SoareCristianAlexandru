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

    Complex *numbers = new Complex[n];
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

    Vector_Complex(const Vector_Complex &a): m_lungime_vector(a.m_lungime_vector) //Copy constructor
    {
        for (int i = 0; i < m_lungime_vector; i ++){
            m_vector_complex[i] = a.m_vector_complex[i];
        }
    }

    //Destructor
    ~Vector_Complex(){
        m_lungime_vector = 0;
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


    // TO DO: modulul unui vector
    // TO DO: sortare crescator dupa modul
    // TO DO: suma tuturor elementelor
};

void readNComplexVectors()
{
    int nr_vectori;
    cout << "Numarul de vectori de tip complex de citit:" << endl;
    cin >> nr_vectori;
    cout << endl;

    Vector_Complex *vectori = new Vector_Complex[nr_vectori];
    for (int i = 0; i < nr_vectori; i ++){
        cin >> vectori[i];
    }

    cout << "Ai memorat urmatorii " << nr_vectori << " vectori:" << endl;
    for (int i = 0; i < nr_vectori; i++){
        if (vectori[i].GetLungime_Vector() != 0) //daca este vector nul, atunci nu se mai afiseaza cele 2 end lines
            cout << vectori[i] << endl << endl;
    }

}


int main()
{
    readNComplexVectors();
    return 0;
}
