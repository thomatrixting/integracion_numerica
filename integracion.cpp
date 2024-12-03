#include <iostream>
#include <cmath>

using std::cout;
using fptr = long double(long double); //function pointer

long double function(long double x);
long double compute_error(long double true_value, long double estimated_value);
long double define_integral(void);
long double trapezoid_estimation(long double vmin, long double vmax, long n ,fptr fun);
long double simpsom_estimation(long double vmin, long double vmax, long n ,fptr fun);

int main(int argc, char **argv){

    cout.precision(18);
    cout.setf(std::ios::scientific); 


    if (argc != 2) {

        std::cerr << "ERROR. Program should be called as:\n";
        std::cerr << argv[0] << " n\n";
        std::cerr << "n: the number of particions it is ussed (it must be odd)\n";
        
        return 1;
    }

    long n = std::stol(argv[1]); //read input
    long double vmin = 1;
    long double vmax = 3;

    long double true_value = define_integral();
    long double trapezoid_value = trapezoid_estimation(vmin, vmax, n, function);
    long double simpsom_value = simpsom_estimation(vmin, vmax, n, function);

    cout << "estimation trapezoid: " << trapezoid_value << "\n";
    cout << "estimation error: " << compute_error(true_value,trapezoid_value) << "\n";

    cout << "estimation simpsom: " << simpsom_value << "\n";
    cout << "estimation error: " << compute_error(true_value,simpsom_value) << "\n";
    
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