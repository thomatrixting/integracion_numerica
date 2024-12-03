#include <iostream>
#include <cmath>
#include <fstream>

using std::cout;
using fptr = long double(long double); //function pointer

long double function(long double x);
long double compute_error(long double true_value, long double estimated_value);
long double define_integral(void);
long double trapezoid_estimation(long double vmin, long double vmax, long n ,fptr fun);
long double simpsom_estimation(long double vmin, long double vmax, long n ,fptr fun);

int main(int argc, char **argv){


    long double vmin = 1;
    long double vmax = 3;
    long double true_value = define_integral();

    std::ofstream fout("datos.csv");

    fout.precision(18);
    fout.setf(std::ios::scientific); 

    fout << "n,trapezoid,trapezoid_error,simpsom,simpsom_error"<< "\n"; //header

    for (long n = 10; n <= 10000;n = n+4){
        fout << n << ",";

        long double trapezoid_value = trapezoid_estimation(vmin, vmax, n, function);
        long double simpsom_value = simpsom_estimation(vmin, vmax, n, function);

        fout << trapezoid_value << ",";
        fout << compute_error(true_value,trapezoid_value) << ",";

        fout << simpsom_value << ",";
        fout << compute_error(true_value,simpsom_value) << "\n";

    }



    
}


long double function(long double x){
    long double result = std::log( std::pow(x,4) );
    return result;
}

long double define_integral(void){

    return 12*std::log(3) - 8; //the exact value is set to reduce the computacional error

}

long double compute_error(long double true_value, long double estimated_value){
    return std::fabs(1.0 - true_value/estimated_value)*100;
}

long double trapezoid_estimation(long double vmin, long double vmax, long n ,fptr fun){
    long double delta = (vmax - vmin)/(n);
    long double sum = 0;

    //add last and firts intem
    sum = sum + fun(vmin);
    sum = sum + fun(vmax);

    for (int i = 1; i<n; i++ ){ //exclude firts and last intem
        sum = sum + 2*fun(vmin + delta*i) ;
    }

    return (delta/2)*sum;
}

long double simpsom_estimation(long double vmin, long double vmax, long n ,fptr fun){
    long double delta = (vmax - vmin)/(n);
    long double sum = 0;

    //add last and firts intem
    sum = sum + fun(vmin);
    sum = sum + fun(vmax);

    for (int i = 1; i<n; i=i+2 ){ //exclude firts and last intem and iterate in odd numbers
        sum = sum + 4*fun(vmin + delta*i) ;
    }
    for (int i = 2; i<n; i=i+2 ){ //exclude firts and last intem and iterate in even numbers
        sum = sum + 2*fun(vmin + delta*i) ;
    }

    return (delta/3)*sum; 

}