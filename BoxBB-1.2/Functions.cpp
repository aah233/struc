/***************************************************************************
                          Functions.cpp  -  description
                             -------------------
    begin                : Jan 2020
    copyright            : (C) 2020 by L.G. Casado
    email                : leo@ual.es
    See https://www.sfu.ca/~ssurjano/optimization.html
    See http://verifiedby.me/kv/index-e.html (kv library).
 ****************************************************************************/
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <kv/autodif.hpp>
#include <kv/interval.hpp>
#include "defines.h"
#include "Functions.hpp"

using namespace std;

/*---------------------------------------------------------------------------*/
PCHARCt NamefProblem(const int NFunction)
{
    switch (NFunction)
    {
    case 0:
        return "Test";
        break;
    case 1:
        return "KearEx1";
        break;
    case 2:
        return "KearEx2";
        break;
    case 3:
        return "KearEx6";
        break;
    case 4:
        return "GoldStein-Price";
        break;
    case 5:
        return "Three Hump Camel Back";
        break;
    case 6:
        return "Six Hump Camel Back";
        break;
    case 7:
        return "Griewank";
        break;
    case 8:
        return "Shekel10";
        break;
    case 9:
        return "Hartmann3";
        break;
    case 10:
        return "Hartmann4";
        break;
    case 11:
        return "Hartmann6";
        break;
    case 12:
        return "Levy";
        break;
    case 13:
        return "Schubert";
        break;
    case 14:
        return "MacCormick";
        break;
    case 15:
        return "Rosembrock";
        break;
    case 16:
        return "Michalewicz";
        break;
    case 17:
        return "Styblinski-Tang";
        break;
    case 18:
        return "Dixon-Price";
        break;
    case 19:
        return "Trid";
        break;
    case 20:
        return "TridDown";
        break;
    case 21:
        return "PortfolioMarkowitz4";
        break;
    case 22:
        return "IvoN10Dens075Dvert20";
        break;
    case 23:
        return "IvoN10Dens095Dvert20";
        break;
    case 24:
        return "Ackley";
        break;
    case 25:
        return "Rastrigin";
        break;
    case 26:
        return "PermDb";
        break;
    case 27:
        return "DeVilliersGlasser02";
        break;
    default:
        cerr << "NameProbmem: No such problem" << endl;
        exit(1);
    }
}

/*---------------------------------------------------------------------------*/
int DimfProblem(const int NFunction)
{
    switch (NFunction)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        return 2;
        break;
    case 7:
        return -1;
        break;
    case 8:
        return 4;
        break;
    case 9:
        return 3;
        break;
    case 10:
        return 4;
        break;
    case 11:
        return 6;
        break;
    case 12:
        return -1;
        break;
    case 13:
    case 14:
        return 2;
        break;
    case 15:
        return -1;
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
        return -1;
        break;
    case 21:
        return 4;
        break;
    case 22:
    case 23:
        return 11;
        break;
    case 24:
    case 25:
    case 26:
        return -1;
        break;
    case 27:
        return 5;
        break;
    default:
        cerr << "DimfProbmem: No such problem" << endl;
        exit(1);
    }
}

/*---------------------------------------------------------------------------*/
void ListFunctions(FILE *FOut)
{
    int i;

    for (i = 1; i <= 20; i++)
        fprintf(stderr, "%d: NDim=%d, %s.\n",
                i, DimfProblem(i), NamefProblem(i));
}

/*---------------------------------------------------------------------------*/
template <class T>
T Test(const ub ::vector<T> &x)
{
    return pow(x(0), 2) + pow(x(1), 2);
}

/*---------------------------------------------------------------------------*/
template <class T>
T fKearEx1(const ub ::vector<T> &x)
{
    return pow(x(0), 2) + pow(x(1), 3);
}

/*---------------------------------------------------------------------------*/
template <class T>
T fKearEx2(const ub ::vector<T> &x)
{
    return 0.25 * pow(x(0), 2) + x(0) + x(1) + 0.25 * x(0) * x(1) + 0.25 * pow(x(1), 3);
}

/*---------------------------------------------------------------------------*/
template <class T>
T fKearEx6(const ub ::vector<T> &x)
{
    return 0.25 * pow(x(0), 2) + x(0) + x(1) + 0.25 * x(0) * x(1) + 0.5 * pow(x(1), 2);
}

/*---------------------------------------------------------------------------*/
template <class T>
T fGP(const ub ::vector<T> &x)
{
    T fact1, fact1a, fact1b;
    T fact2, fact2a, fact2b;

    fact1a = pow(x(0) + x(1) + 1., 2);
    fact1b = 19. - 14. * x(0) + 3. * pow(x(0), 2) - 14. * x(1) + 6. * x(0) * x(1) + 3. * pow(x(1), 2);
    fact1 = 1. + fact1a * fact1b;

    fact2a = pow(2. * x(0) - 3. * x(1), 2);
    fact2b = 18. - 32. * x(0) + 12. * pow(x(0), 2) + 48. * x(1) - 36. * x(0) * x(1) + 27. * pow(x(1), 2);
    fact2 = 30 + fact2a * fact2b;

    return fact1 * fact2;
}

/*---------------------------------------------------------------------------*/
template <class T>
T fTHCB(const ub ::vector<T> &x)
{
    return 2.0 * pow(x[0], 2) - 1.05 * pow(x(0), 4) +
           pow(x(0), 6) / 6.0 + x(0) * x(1) + pow(x(1), 2);
}
/*---------------------------------------------------------------------------*/
template <class T>
T fSHCB(const ub ::vector<T> &x)
{
    return (4.0 - 2.1 * pow(x(0), 2) + pow(x(0), 4) / 3.0) * pow(x(0), 2) +
           x(0) * x(1) + (-4.0 + 4.0 * pow(x(1), 2)) * pow(x(1), 2);
}

/*---------------------------------------------------------------------------*/
template <class T>
T fGriew(const ub ::vector<T> &x)
{
    int d = x.size();
    T sum, prod;

    sum = 0.;
    prod = 1.;
    for (int i = 0; i < d; i++)
    {
        sum += pow(x(i), 2) / 4000.0;
        prod *= cos(x(i) / sqrt(i + 1));
    }
    return sum - prod + 1.;
}

/*---------------------------------------------------------------------------*/
template <class T>
T fShekel(const ub ::vector<T> &x, int iter)
{
    int i, j;
    double b[10] = {0.1, 0.2, 0.3, 0.4, 0.4, 0.6, 0.3, 0.7, 0.5, 0.5};
    double C[4][10] = {{4.0, 1.0, 8.0, 6.0, 3.0, 2.0, 5.0, 8.0, 6.0, 7.0},
                       {4.0, 1.0, 8.0, 6.0, 7.0, 9.0, 3.0, 1.0, 2.0, 3.6},
                       {4.0, 1.0, 8.0, 6.0, 3.0, 2.0, 5.0, 8.0, 6.0, 7.0},
                       {4.0, 1.0, 8.0, 6.0, 7.0, 9.0, 3.0, 1.0, 2.0, 3.6}};
    T outer, inner;

    outer = 0.;
    for (i = 0; i < iter; i++)
    {
        inner = 0.;
        for (j = 0; j < 4; j++)
            inner += pow(x(j) - C[j][i], 2);
        outer += 1. / (inner + b[i]);
    }
    return -outer;
}

/*----------------------------------------------------------------------------*/
template <class T>
T fH3(const ub ::vector<T> &x)
{
    int i, j;
    double alpha[4] = {1.0, 1.2, 3.0, 3.2};
    double A[4][3] = {{3.0, 10.0, 30.0},
                      {0.1, 10.0, 35.0},
                      {3.0, 10.0, 30.0},
                      {0.1, 10.0, 35.0}};
    double P[4][3] = {{0.3689, 0.1170, 0.2673},
                      {0.4699, 0.4387, 0.7470},
                      {0.1091, 0.8732, 0.5547},
                      {0.0381, 0.5743, 0.8828}};
    T outer, inner;

    outer = 0.;
    for (i = 0; i < 4; i++)
    {
        inner = 0.;
        for (j = 0; j < 3; j++)
            inner += A[i][j] * pow(x(j) - P[i][j], 2);
        outer += alpha[i] * exp(-inner);
    }
    return -outer;
}

/*---------------------------------------------------------------------------*/
template <class T>
T fH4(const ub ::vector<T> &x)
{
    int i, j;
    double alpha[4] = {1.0, 1.2, 3.0, 3.2};
    double A[4][4] = {{10.0, 3.0, 17.0, 3.5},
                      {0.05, 10.0, 17.0, 0.1},
                      {3.0, 3.5, 1.7, 10.0},
                      {17.0, 8.0, 0.05, 10.0}};
    double P[4][4] = {{0.1312, 0.1696, 0.5569, 0.0124},
                      {0.2329, 0.4135, 0.8307, 0.3736},
                      {0.2348, 0.1451, 0.3522, 0.2883},
                      {0.4047, 0.8828, 0.8732, 0.5743}};
    T outer, inner;

    outer = 0.;
    for (i = 0; i < 4; i++)
    {
        inner = 0.;
        for (j = 0; j < 4; j++)
            inner += A[i][j] * pow(x(j) - P[i][j], 2);
        outer += alpha[i] * exp(-inner);
    }
    return (1.1 - outer) / 0.839;
}

/*---------------------------------------------------------------------------*/
template <class T>
T fH6(const ub ::vector<T> &x)
{
    int i, j;
    double alpha[4] = {1.0, 1.2, 3.0, 3.2};
    double A[4][6] = {{10.0, 3.0, 17.0, 3.5, 1.7, 8.0},
                      {0.05, 10.0, 17.0, 0.1, 8.0, 14.0},
                      {3.0, 3.5, 1.7, 10.0, 17.0, 8.0},
                      {17.0, 8.0, 0.05, 10.0, 0.1, 14.0}};
    double P[4][6] = {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
                      {0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
                      {0.2348, 0.1451, 0.3522, 0.2883, 0.3047, 0.6650},
                      {0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
    T outer, inner;

    outer = 0.;
    for (i = 0; i < 4; i++)
    {
        inner = 0.;
        for (j = 0; j < 6; j++)
            inner += A[i][j] * pow(x(j) - P[i][j], 2);
        outer += alpha[i] * exp(-inner);
    }
    return -outer;
}

/*---------------------------------------------------------------------------*/
template <class T>
T fLevy(const ub ::vector<T> &x)
{
    int d = x.size();
    int i;
    static T pi = kv::constants<T>::pi();

    ub::vector<T> w(d);

    T term1, term3, sum;

    for (i = 0; i < d; i++)
        w(i) = 1.0 + (x(i) - 1.0) / 4.0;

    term1 = pow(sin(pi * w(0)), 2);
    term3 = pow(w(d - 1) - 1.0, 2) * (1.0 + pow(sin(2.0 * pi * w(d - 1)), 2));

    sum = 0.;
    for (i = 0; i < d - 1; i++)
        sum += pow(w(i) - 1.0, 2) * (1.0 + 10.0 * pow(sin(pi * w(i) + 1.0), 2));

    return term1 + sum + term3;
}

/*---------------------------------------------------------------------------*/
template <class T>
T fLevy13(const ub ::vector<T> &x)
{
    static T pi = kv::constants<T>::pi();
    T term1, term2, term3;

    term1 = pow(sin(3. * pi * x(0)), 2);
    term2 = pow(x(0) - 1., 2) * (1. + pow(sin(3. * pi * x(1)), 2));
    term3 = pow(x(1) - 1., 2) * (1. + pow(sin(2. * pi * x(1)), 2));

    return term1 + term2 + term3;
}

/*---------------------------------------------------------------------------*/
template <class T>
T Schubert(const ub ::vector<T> &x)
{
    int i;
    T sum1, sum2;

    sum1 = 0;
    sum2 = 0;

    for (i = 1; i <= 5; i++)
    {
        sum1 += i * cos((i + 1) * x(0) + i);
        sum2 += i * cos((i + 1) * x(1) + i);
    }
    return sum1 * sum2;
}

/*---------------------------------------------------------------------------*/
template <class T>
T McCormick(const ub ::vector<T> &x)
{
    T term1, term2, term3, term4;

    term1 = sin(x(0) + x(1)); // Mal el sin es de todo.
    term2 = pow(x(0) - x(1), 2);
    term3 = -1.5 * x(0);
    term4 = 2.5 * x(1);

    return term1 + term2 + term3 + term4 + 1.;
}

/*---------------------------------------------------------------------------*/
template <class T>
T Rosembrock(const ub ::vector<T> &x)
{
    int i;
    int d = x.size();
    T sum;

    sum = 0.;
    for (i = 0; i < d - 1; i++)
        sum += 100. * pow(x(i + 1) - x(i), 2) + pow(x(i) - 1, 2);

    return sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T Michalewicz(const ub ::vector<T> &x)
{
    static T pi = kv::constants<T>::pi();
    int i;
    int d = x.size();
    T sum;

    sum = 0.;
    for (i = 0; i < d; i++)
        sum += sin(x(i)) * pow(sin((i + 1) * pow(x(i), 2) / pi), 20);

    return -sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T StybTang(const ub ::vector<T> &x)
{
    int i;
    int d = x.size();
    T sum;

    sum = 0.;
    for (i = 0; i < d; i++)
        sum += pow(x(i), 4) - 16. * pow(x(i), 2) + 5. * x(i);

    return sum / 2.;
}

/*---------------------------------------------------------------------------*/

template <class T>
T Schaffer2(const ub ::vector<T> &x)
{
    T fact1, fact2;

    fact1 = pow(sin(pow(x(0), 2) - pow(x(1), 2)), 2) - .5;
    fact2 = pow(1. + 0.001 * pow(x(0), 2) + pow(x(1), 2), 2);

    return 0.5 + fact1 / fact2;
}

/*---------------------------------------------------------------------------*/
template <class T>
T Rastrigin(const ub ::vector<T> &x)
{
    static T pi = kv::constants<T>::pi();
    int i, d = x.size();

    T sum;

    sum = 0.;

    for (i = 0; i < d; i++)
        sum += pow(x(i), 2) - 10. * cos(2. * pi * x(i));

    return 10. * d + sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T DixonPrice(const ub ::vector<T> &x)
{
    int i, d = x.size();
    ;

    T term1, sum;

    term1 = pow(x(0) - 1., 2);
    sum = 0.;

    for (i = 1; i < d; i++)
        sum += i * pow(2. * x(i) - x(i - 1), 2);

    return term1 + sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T Trid(const ub ::vector<T> &x)
{
    int i, d = x.size();

    T sum1, sum2;

    sum1 = pow(x(0) - 1., 2);
    sum2 = 0.;

    for (i = 1; i < d; i++)
    {
        sum1 += pow(x(i) - 1., 2);
        sum2 += x(i) * x(i - 1);
    }

    return sum1 - sum2;
}

/*---------------------------------------------------------------------------*/
template <class T>
T TridDown(const ub ::vector<T> &x)
{
    return -Trid(x);
}

/*---------------------------------------------------------------------------*/
template <class T>
T PortfolioMarkowitz4(const ub ::vector<T> &x)
{
    int i, j;
    double mu[4] = {11.5, 9.50, 5.00, 4.00};
    double A[4][4] = {{1.66, 0.34, 0.58, -0.01},
                      {0.34, 0.64, 0.04, -0.01},
                      {0.58, 0.04, 1.00, 0.01},
                      {-0.01, -0.01, 0.01, 0.10}};

    T vA[4];
    T Sum1, Sum2;

    for (j = 0; j < 4; j++) // colums A
    {
        vA[j] = 0.0;
        for (i = 0; i < 4; i++) // rows A
            vA[j] += x(i) * A[i][j];
    }
    Sum1 = 0.0;
    Sum2 = 0.0;
    for (i = 0; i < 4; i++)
    {
        Sum1 += vA[i] * x(i); // vAv
        Sum2 += mu[i] * x(i);
    }

    return 10 * Sum1 - Sum2;
}

/*---------------------------------------------------------------------------*/
template <class T>
T IvoN10Dens075Dvert20(const ub ::vector<T> &x)
{
    int i, j;
    double A[11][11] = {
        {3.49, 9.56, 8.31, 13.41, 3.06, 1.32, 7.44, 9.93, 3.35, -2.75, 11.72},
        {9.56, 4.51, 4.76, -2.24, 5.72, 6.46, 14.40, -3.11, 5.64, 2.84, 12.22},
        {8.31, 4.76, 12.18, 11.51, 10.16, 10.82, 17.88, 3.92, 11.68, 0.32, 16.06},
        {13.41, -2.24, 11.51, 9.61, 7.32, 7.97, 8.34, -0.43, 6.84, 2.31, 14.77},
        {3.06, 5.72, 10.16, 7.32, 18.02, 11.87, 12.42, 15.59, 5.29, 5.12, 18.98},
        {1.32, 6.46, 10.82, 7.97, 11.87, 14.83, 7.11, 6.85, 9.68, 10.04, 17.38},
        {7.44, 14.40, 17.88, 8.34, 12.42, 7.11, 17.42, 15.64, 4.16, 9.59, 18.68},
        {9.93, -3.11, 3.92, -0.43, 15.59, 6.85, 15.64, 8.59, 6.11, 1.47, 14.26},
        {3.35, 5.64, 11.68, 6.84, 5.29, 9.68, 4.16, 6.11, 8.53, 4.97, 14.23},
        {-2.75, 2.84, 0.32, 2.31, 5.12, 10.04, 9.59, 1.47, 4.97, 7.52, 13.73},
        {11.72, 12.22, 16.06, 14.77, 18.98, 17.38, 18.68, 14.26, 14.23, 13.73, 19.94}};
    T vA[11];
    T Sum;

    for (j = 0; j < 11; j++) // colums A
    {
        vA[j] = 0.0;
        for (i = 0; i < 11; i++) // rows A
            vA[j] += x(i) * A[i][j];
    }

    Sum = 0.0;
    for (i = 0; i < 11; i++)
        Sum += vA[i] * x(i); // vAv

    return Sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T IvoN10Dens095Dvert20(const ub ::vector<T> &x)
{
    int i, j;
    double A[11][11] = {
        {3.49, -0.44, 8.31, 3.41, 3.06, 1.32, 7.44, -0.07, 3.35, -2.75, 11.72},
        {-0.44, 4.51, 4.76, -2.24, 5.72, 6.46, 14.40, -3.11, 5.64, 2.84, 12.22},
        {8.31, 4.76, 12.18, 11.51, 10.16, 10.82, 7.88, 3.92, 1.68, 0.32, 16.06},
        {3.41, -2.24, 11.51, 9.61, 7.32, 7.97, 8.34, -0.43, 6.84, 2.31, 14.77},
        {3.06, 5.72, 10.16, 7.32, 18.02, 11.87, 12.42, 5.59, 5.29, 5.12, 18.98},
        {1.32, 6.46, 10.82, 7.97, 11.87, 14.83, 7.11, 6.85, 9.68, 10.04, 17.38},
        {7.44, 14.40, 7.88, 8.34, 12.42, 7.11, 17.42, 15.64, 4.16, 9.59, 18.68},
        {-0.07, -3.11, 3.92, -0.43, 5.59, 6.85, 15.64, 8.59, 6.11, 1.47, 14.26},
        {3.35, 5.64, 1.68, 6.84, 5.29, 9.68, 4.16, 6.11, 8.53, 4.97, 14.23},
        {-2.75, 2.84, 0.32, 2.31, 5.12, 10.04, 9.59, 1.47, 4.97, 7.52, 13.73},
        {11.72, 12.22, 16.06, 14.77, 18.98, 17.38, 18.68, 14.26, 14.23, 13.73, 19.94}};
    T vA[11];
    T Sum;

    for (j = 0; j < 11; j++) // colums A
    {
        vA[j] = 0.0;
        for (i = 0; i < 11; i++) // rows A
            vA[j] += x(i) * A[i][j];
    }

    Sum = 0.0;
    for (i = 0; i < 11; i++)
        Sum += vA[i] * x(i); // vAv

    return Sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T IvoN10Dens1Dvert20(const ub ::vector<T> &x)
{
    int i, j;
    double A[11][11] = {
        {3.49, -0.44, -1.69, 3.41, 3.06, 1.32, 7.44, -0.07, 3.35, -2.75, 11.72},
        {-0.44, 4.51, 4.76, -2.24, 5.72, 6.46, 4.40, -3.11, 5.64, 2.84, 12.22},
        {-1.69, 4.76, 12.18, 1.51, 10.16, 10.82, 7.88, 3.92, 1.68, 0.32, 16.06},
        {3.41, -2.24, 1.51, 9.61, 7.32, 7.97, 8.34, -0.43, 6.84, 2.31, 14.77},
        {3.06, 5.72, 10.16, 7.32, 18.02, 11.87, 12.42, 5.59, 5.29, 5.12, 18.98},
        {1.32, 6.46, 10.82, 7.97, 11.87, 14.83, 7.11, 6.85, 9.68, 10.04, 17.38},
        {7.44, 4.40, 7.88, 8.34, 12.42, 7.11, 17.42, 5.64, 4.16, 9.59, 18.68},
        {-0.07, -3.11, 3.92, -0.43, 5.59, 6.85, 5.64, 8.59, 6.11, 1.47, 14.26},
        {3.35, 5.64, 1.68, 6.84, 5.29, 9.68, 4.16, 6.11, 8.53, 4.97, 14.23},
        {-2.75, 2.84, 0.32, 2.31, 5.12, 10.04, 9.59, 1.47, 4.97, 7.52, 13.73},
        {11.72, 12.22, 16.06, 14.77, 18.98, 17.38, 18.68, 14.26, 14.23, 13.73, 19.94}};
    T vA[11];
    T Sum;

    for (j = 0; j < 11; j++) // colums A
    {
        vA[j] = 0.0;
        for (i = 0; i < 11; i++) // rows A
            vA[j] += x(i) * A[i][j];
    }

    Sum = 0.0;
    for (i = 0; i < 11; i++)
        Sum += vA[i] * x(i); // vAv

    return Sum;
}

/*---------------------------------------------------------------------------*/
template <class T>
T Ackley(const ub ::vector<T> &x)
{
    static T pi = kv::constants<T>::pi();
    static T c = 2.0 * pi;
    static double b = 0.2;
    static double a = 20.0;
    int i;
    int d = x.size();

    // Produces division by 0.
    // Use http://verifiedby.me/kv/interval/index-e.html
    // division_part1  parted

    T sum1, sum2, term1, term2;

    sum1 = 0.0;
    sum2 = 0.0;
    for (i = 0; i < d; i++)
    {
        sum1 += pow(x(i), 2);
        sum2 += cos(c * x(i));
    }

    sum1 += 1e-16; // To avoid [0,y] and division by 0 ¿?

    // cout << "d = " << d << endl << std::flush;
    // cout<< "Sum1=" << sum1 << endl << std::flush;
    // cout<< "Sum2=" << sum2 << endl << std::flush;
    term1 = -a * exp(-b * sqrt(sum1 / d));
    // cout<<"term1=" << term1<< endl << std::flush;
    term2 = -exp(sum2 / d);
    // cout<<"term2=" << term1<< endl << std::flush;

    return term1 + term2 + a + exp(1.0);
}

/*---------------------------------------------------------------------------*/
template <class T>
T PermDb(const ub ::vector<T> &x)
{
    static double b = 0.5;
    int i, j;
    int d = x.size();

    T outer, inner;

    outer = 0.0;
    for (i = 1; i <= d; i++)
    {
        inner = 0.0;
        for (j = 0; j < d; j++)
            inner += (pow((j + 1), i) + b) * (pow(x(j) / (j + 1), i) - 1);
        outer += pow(inner, 2);
    }

    return outer;
}

/*---------------------------------------------------------------------------*/
/*https://infinity77.net/global_optimization/test_functions.html*/
template <class T>
T DeVilliersGlasser02(const ub ::vector<T> &x)
{
    int i;
    static T e = kv::constants<T>::e();
    T sum, t, y;

    for (i = 1; i <= 24; i++)
    {
        t = 0.1 * (i - 1);
        y = 53.81 * pow(1.27, t) * tanh(3.012 * t + sin(2.13 * t)) * cos(pow(e, 0.507) * t);
        sum += pow(pow(x(0) * x(1), t) * tanh(x(2) * t + sin(x(3) * t)) * cos(t * pow(e, x(4))) - y, 2.0);
    }
    return sum;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
void fEvalIA(const int NFunction, const itvV &X, itv &F)
{
    int d;

    d = DimfProblem(NFunction);

    if (d != -1 && d != (int)X.size())
    {
        fprintf(stderr, "fEval:Bad X's size.\n");
        exit(1);
    }

    switch (NFunction)
    {
    case 0:
        F = Test(X);
        break;
    case 1:
        F = fKearEx1(X);
        break;
    case 2:
        F = fKearEx2(X);
        break;
    case 3:
        F = fKearEx6(X);
        break;
    case 4:
        F = fGP(X);
        break;
    case 5:
        F = fTHCB(X);
        break;
    case 6:
        F = fSHCB(X);
        break;
    case 7:
        F = fGriew(X);
        break;
    case 8:
        F = fShekel(X, 10);
        break;
    case 9:
        F = fH3(X);
        break;
    case 10:
        F = fH4(X);
        break;
    case 11:
        F = fH6(X);
        break;
    case 12:
        F = fLevy(X);
        break;
    case 13:
        F = Schubert(X);
        break;
    case 14:
        F = McCormick(X);
        break;
    case 15:
        F = Rosembrock(X);
        break;
    case 16:
        F = Michalewicz(X);
        break;
    case 17:
        F = StybTang(X);
        break;
    case 18:
        F = DixonPrice(X);
        break;
    case 19:
        F = Trid(X);
        break;
    case 20:
        F = TridDown(X);
        break;
    case 21:
        F = PortfolioMarkowitz4(X);
        break;
    case 22:
        F = IvoN10Dens075Dvert20(X);
        break;
    case 23:
        F = IvoN10Dens095Dvert20(X);
        break;
    case 24:
        F = Ackley(X);
        break;
    case 25:
        F = Rastrigin(X);
        break;
    case 26:
        F = PermDb(X);
        break;
    case 27:
        F = DeVilliersGlasser02(X);
        break;
    default:
        cerr << "fEval: No such problem" << endl;
        exit(1);
    }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
void fgEvalIA(const int NFunction, const itvV &X, itv &F, itvV &G)
{
    int d;

    d = DimfProblem(NFunction);

    if (d != -1 && d != (int)X.size())
    {
        fprintf(stderr, "fgEval:Bad X's size.\n");
        exit(1);
    }

    if (d != -1 && d != (int)G.size())
    {
        fprintf(stderr, "fgEval:Bad G's size.\n");
        exit(1);
    }

    kv ::autodif<itv> val;
    ub ::vector<kv ::autodif<itv>> itvVAdif;
    itvVAdif = kv ::autodif<itv>::init(X);

    switch (NFunction)
    {
    case 0:
        val = Test(itvVAdif);
        break;
    case 1:
        val = fKearEx1(itvVAdif);
        break;
    case 2:
        val = fKearEx2(itvVAdif);
        break;
    case 3:
        val = fKearEx6(itvVAdif);
        break;
    case 4:
        val = fGP(itvVAdif);
        break;
    case 5:
        val = fTHCB(itvVAdif);
        break;
    case 6:
        val = fSHCB(itvVAdif);
        break;
    case 7:
        val = fGriew(itvVAdif);
        break;
    case 8:
        val = fShekel(itvVAdif, 10);
        break;
    case 9:
        val = fH3(itvVAdif);
        break;
    case 10:
        val = fH4(itvVAdif);
        break;
    case 11:
        val = fH6(itvVAdif);
        break;
    case 12:
        val = fLevy(itvVAdif);
        break;
    case 13:
        val = Schubert(itvVAdif);
        break;
    case 14:
        val = McCormick(itvVAdif);
        break;
    case 15:
        val = Rosembrock(itvVAdif);
        break;
    case 16:
        val = Michalewicz(itvVAdif);
        break;
    case 17:
        val = StybTang(itvVAdif);
        break;
    case 18:
        val = DixonPrice(itvVAdif);
        break;
    case 19:
        val = Trid(itvVAdif);
        break;
    case 20:
        val = TridDown(itvVAdif);
        break;
    case 21:
        val = PortfolioMarkowitz4(itvVAdif);
        break;
    case 22:
        val = IvoN10Dens075Dvert20(itvVAdif);
        break;
    case 23:
        val = IvoN10Dens095Dvert20(itvVAdif);
        break;
    case 24:
        val = Ackley(itvVAdif);
        break;
    case 25:
        val = Rastrigin(itvVAdif);
        break;
    case 26:
        val = PermDb(itvVAdif);
        break;
    case 27:
        val = DeVilliersGlasser02(itvVAdif);
        break;
    default:
        cerr << "itvVAdifF: No such problem" << endl;
        exit(1);
    }
    kv ::autodif<itv>::split(val, F, G);
}

/*---------------------------------------------------------------------------*/
bool Monotonous(const itvV &G, const int NDim)
{

    if (NDim != (int)G.size())
    {
        fprintf(stderr, "Monotonous: G.size()=%ld, NDim=%d.\n",
                G.size(), NDim);
        exit(1);
    }

    for (int i = 0; i < NDim; i++)
        if (!zero_in(G[i]))
            return true;

    return false;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
