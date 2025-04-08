/* Including the basic libraries for input/output streams and for manipulating them */
#include <iostream>
#include <iomanip>

/* Including just the parts of the Eigen library we'll use in the code */
#include "Eigen/Core"
#include "Eigen/LU"
#include "Eigen/QR"

/* Otherwise, we can include all of the library, uncommenting this next line: */
//#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

/* Creating a function that tells us if the relative error of the vectors obtained with the methods used in the code 
is less than or equal to the machine epsilon. If that's the case, the function returns the boolean value true, 
otherwise it returns false. We'll use it to print a message that will tell us whether the solution vector and 
the solution we found are the same vector. (not asked in the assignment, but I wanted to try and implement it) */
bool areTheyTheSame(double const& number){
    double eps = numeric_limits<double>::epsilon();
    if(number <= eps){
        return true;
    }
    return false;
}

int main(){

    /* Using the comma-initializer to initialize the matrixes and the vectors we're going to use in the code */
    Matrix2d A;
    A << 5.547001962252291e-01, -3.770900990025203e-02,
         8.320502943378437e-01, -9.992887623566787e-01;
    Vector2d b;
    b << -5.169911863249772e-01, 
         1.672384680188350e-01;

    /* Let's define the vector solution using the function Ones() for fixed-size matrix types */
    Vector2d x = -Vector2d::Ones();

    /* Finding the solution of each system using the PALU then the QR decomposition with full pivoting */
    Vector2d PALU1 = A.fullPivLu().solve(b);
    Vector2d QR1 = A.fullPivHouseholderQr().solve(b);

    /* Calculating the relative error using the lpNorm(2), which is the euclidean norm for vectors
    or the Frobenius norm for matrixes */
    double rel_err_PALU_1 = ((x - PALU1).norm())/(x.norm());
    double rel_err_QR_1 = ((x - QR1).norm())/(x.norm());

    /* Printing out some messages to inform us about the relative errors between the vector provided and the vector we found */
    cout << "The relative error for the 1st system using the PALU decomposition with full pivoting is: " << setprecision(15) 
         << scientific << rel_err_PALU_1 << endl;
    cout << "Therefore, for the computer the vector found using this method is the same as the solution vector x provided: "
         << boolalpha << areTheyTheSame(rel_err_PALU_1) << endl;
    cout << "The relative error for the 1st system using the QR decomposition with full pivoting is: " 
         << rel_err_QR_1 << endl;
    cout << "Therefore, for the computer the vector found using this method is the same as the solution vector x provided: "
         << boolalpha << areTheyTheSame(rel_err_QR_1) << endl << endl;


    Matrix2d C = A;
    /* The difference between A and C is their second column, so let's modify just that "block" of the matrix */
    C.col(1) << -5.540607316466765e-01, 
                -8.324762492991313e-01;
    Vector2d d;
    d << -6.394645785530173e-04,
         4.259549612877223e-04;

    /* Repeating the same algorithm as above: */
    Vector2d PALU2 = C.fullPivLu().solve(d);
    Vector2d QR2 = C.fullPivHouseholderQr().solve(d);
    double rel_err_PALU_2 = ((x - PALU2).norm())/(x.norm());
    double rel_err_QR_2 = ((x - QR2).norm())/(x.norm());
    cout << "The relative error for the 2nd system using the PALU decomposition with full pivoting is: " 
         << rel_err_PALU_2 << endl;
    cout << "Therefore, for the computer the vector found using this method is the same as the solution vector x provided: "
         << boolalpha << areTheyTheSame(rel_err_PALU_2) << endl;
    cout << "The relative error for the 2nd system using the QR decomposition with full pivoting is: " 
        << rel_err_QR_2 << endl;
    cout << "Therefore, for the computer the vector found using this method is the same as the solution vector x provided: "
         << boolalpha << areTheyTheSame(rel_err_QR_2) << endl << endl;

    Matrix2d E = C;
    /* The difference between C and E is their second column, so let's modify just that "block" of the matrix */
    E.col(1) << -5.547001955851905e-01,
                -8.320502947645361e-01;
    Vector2d f;
    f << -6.400391328043042e-10,
         4.266924591433963e-10;

    /* Repeating the same algorithm as above: */
    Vector2d PALU3 = E.fullPivLu().solve(f);
    Vector2d QR3 = E.fullPivHouseholderQr().solve(f);
    double rel_err_PALU_3 = ((x - PALU3).norm())/(x.norm());
    double rel_err_QR_3 = ((x - QR3).norm())/(x.norm());
    cout << "The relative error for the 3rd system using the PALU decomposition with full pivoting is: " << setprecision(15) 
        << scientific << rel_err_PALU_3 << endl;
    cout << "Therefore, for the computer the vector found using this method is the same as the solution vector x provided: "
         << boolalpha << areTheyTheSame(rel_err_PALU_3) << endl;
    cout << "The relative error for the 3rd system using the QR decomposition with full pivoting is: " 
        << rel_err_QR_3 << endl;
    cout << "Therefore, for the computer the vector found using this method is the same as the solution vector x provided: "
        << boolalpha << areTheyTheSame(rel_err_QR_3) << endl << endl;

    return 0;
}
