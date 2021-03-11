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
            out << complex.m_real << endl; //afisarea doar partii reale
        else
            if (complex.m_real == 0)
                if (complex.m_imaginar > 0)
                    out << "i*" << complex.m_imaginar << endl; //afisare sub forma "i*a"
                else
                    out << "-i*" << -complex.m_imaginar << endl; //afisare sub forma "-i*a"
            else
                if (complex.m_imaginar > 0)
                    out << complex.m_real << "+i*" << complex.m_imaginar << endl; //afisare sub forma "a+i*b"
                else
                    out << complex.m_real << "-i*" << -complex.m_imaginar << endl; //afisare sub forma "a -i*b"

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
    cout << "Number of complex numbers to read: ";
    int n;
    cin >> n;

    cout << "Write " << n << " nucomplex numbers." << endl;

    Complex *numbers = new Complex[n];
    for (int i = 0; i < n; i ++){
        //citim numerele
        cin >> numbers[i];
    }

    cout << "You've read the following " << n << " numbers:" << endl;
    for (int i = 0; i < n; i++){
        cout << numbers[i] << endl;
    }

}

class Vector_Complex
{
    int n;
    Complex v[500];


};


int main()
{
    Complex c1, c2, c3;
    cin >> c1;
    cin >> c2;
    c3 = c1 - c2;
    cout << c3; //cout << c1 - c2

    readNComplexNumbers();

    return 0;
}
