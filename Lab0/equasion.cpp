#include <iostream>

using namespace std;

int IsZero(double val)
{
  return abs(val) < FLT_EPSILON;
}

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
  double discr = b * b - 4 * a * c;
  if (IsZero(discr))
  {
    *x1 = -b / (2 * a);
    return 1;
  }
  if (discr  < 0)
  {
    return 0;
  }
  discr = sqrt(discr);
  *x1 = (-b - discr) / (2 * a);
  *x2 = (-b + discr) / (2 * a);
  return 2;
}

int SolveLin(double b, double c, double* x1)
{
  *x1 = -c / b;
  return 1;
}

int SolveEquasion(double a, double b, double c, double* x1, double* x2)
{
  unsigned int notZeros = 0b111U;
  if (x1 == NULL || x2 == NULL)
  {
    return -1;
  }
  if (IsZero(a))
  {
    notZeros &= 0b011U;
  }
  if (IsZero(b))
  {
    notZeros &= 0b101U;
  }
  if (IsZero(c))
  {
    notZeros &= 0b110U;
  }

  switch (notZeros)
  {
  case 0b000U:
    return 3;
    break;
  case 0b001U:
    return 0;
    break;
  case 0b010U:
    *x1 = 0;
    return 1;
    break;
  case 0b011U:
    return SolveLin(b, c, x1);
    break;
  default:
    return SolveSquare(a, b, c, x1, x2);
    break;
  }
}

int AskCoefs(double* a, double* b, double* c)
{
  cout << "Solving a*x^2 + b*x + c = 0." << endl;
  cout << "Enter a:" << endl;
  cin >> *a;
  cout << "Enter b:" << endl;
  cin >> *b;
  cout << "Enter c:" << endl;
  cin >> *c;
  return 0;
}

void PrintAns(double x1, double x2, int ansCount)
{
  switch (ansCount)
  {
  case 0:
    cout << "No solution." << endl;
    break;
  case 1:
    cout << "x = " << x1 << endl;
    break;
  case 2:
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
    break;
  case 3:
    cout << "Any solution." << endl;
    break;
  default:
    cout << "Error." << endl;
    break;
  }
}

int main(void)
{
  double a, b, c, x1, x2;
  int ansCount;
  AskCoefs(&a, &b, &c);
  ansCount = SolveEquasion(a, b, c, &x1, &x2);
  PrintAns(x1, x2, ansCount);
  return 0;
}