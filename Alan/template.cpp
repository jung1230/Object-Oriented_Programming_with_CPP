#include <iostream>
#include <cmath>

int minArray(const int* array, int length){
    int minn = array[0];
    for(int i = 1; i < length; i++){
        if (minn > array[i])
            minn = array[i];
    }
    return minn; 
}

template <typename T>
T minArrayGeneric(const T* array, int length){
    T minn = array[0];
    for(int i = 1; i < length; i++){
        if (minn > array[i])
            minn = array[i];
    }
    return minn; 
}

class Complex_num{
    private:
        double real;
        double imag; 
    public:
        Complex_num(double r, double i) : real(r), imag(i) {}

        double getReal() const { 
            return real; 
        }
        double getImag() const { 
            return imag; 
        }
        Complex_num operator+(const Complex_num& other) const{
            return Complex_num(real + other.real, imag + other.imag);
        }

        Complex_num operator-(const Complex_num& other) const {
            return Complex_num(real - other.real, imag - other.imag);
        }

        Complex_num operator*(const Complex_num& other) const {
            return Complex_num(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
        }

        Complex_num operator/(const Complex_num& other) const {
            double denominator = other.real * other.real + other.imag * other.imag;
            return Complex_num((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
        }
        void print() const {
            std::cout << real << " + " << imag << "i";
        }

};


int main(){
    int arr[] = {3, 7, 13, 83, 3, 23};
    int minn = minArray(arr, 6);
    double dArr[] = {3.5, 7.2, 13.1, 83.7, 3.9, 23.0};
    double minnn = minArrayGeneric(dArr,6);
    std::cout << "min num = " << minn << std::endl;
    std::cout << "min num = " << minnn << std::endl;

    Complex_num cArr[2] = { Complex_num(8.2, 32.4), Complex_num(34.3, 231.3)};
    Complex_num ans = cArr[1] + cArr[0];
    std::cout << "ans = ";
    ans.print();
    std::cout << std::endl;
}   