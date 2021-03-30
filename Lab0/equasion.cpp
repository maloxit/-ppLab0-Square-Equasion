#include <iostream>

using namespace std;
enum SqrEquasionAnsType
{
  ZERO,
  ONE,
  TWO,
  ANY
};

using SqrEquasionCoeffs = struct
{ 
  double a; 
  double b; 
  double c; 
};

using SqrEquasionAns = struct
{ 
  double x[2];
  SqrEquasionAnsType type;
};

inline int IsZero(double val)
{
  return abs(val) < FLT_EPSILON;
}

void SolveSquare(SqrEquasionCoeffs& coeffs, SqrEquasionAns& ans)
{
  double discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
  if (IsZero(discr))
  {
    ans.x[0] = -coeffs.b / (2 * coeffs.a);
    ans.type = SqrEquasionAnsType::ONE;
  }
  else if (discr  < 0)
  {
    ans.type = SqrEquasionAnsType::ZERO;
  }
  else
  {
    discr = sqrt(discr);
    ans.x[0] = (-coeffs.b - discr) / (2 * coeffs.a);
    ans.x[1] = (-coeffs.b + discr) / (2 * coeffs.a);
    ans.type = SqrEquasionAnsType::TWO;
  }
}

void SolveLin(SqrEquasionCoeffs& coeffs, SqrEquasionAns& ans)
{
  if (IsZero(coeffs.b))
  {
    if (IsZero(coeffs.c))
    {
      ans.type = SqrEquasionAnsType::ANY;
    }
    else
    {
      ans.type = SqrEquasionAnsType::ZERO;
    }
  }
  else
  {
    if (IsZero(coeffs.c))
    {
      ans.x[0] = 0;
    }
    else
    {
      ans.x[0] = -coeffs.c / coeffs.b;
    }
    ans.type = SqrEquasionAnsType::ONE;
  }
}

SqrEquasionAnsType SolveEquasion(SqrEquasionCoeffs& coeffs, SqrEquasionAns& ans)
{
  if (IsZero(coeffs.a))
  {
    SolveLin(coeffs, ans);
  }
  else
  {
    SolveSquare(coeffs, ans);
  }
  return ans.type;
}

void AskCoefs(SqrEquasionCoeffs& coeffs)
{
  cout << "Solving a*x^2 + b*x + c = 0." << endl;
  cout << "Enter a:" << endl;
  cin >> coeffs.a;
  cout << "Enter b:" << endl;
  cin >> coeffs.b;
  cout << "Enter c:" << endl;
  cin >> coeffs.c;
}

void PrintAns(SqrEquasionAns& ans)
{
  switch (ans.type)
  {
  case ZERO:
    cout << "No solution." << endl;
    break;
  case ONE:
    cout << "x = " << ans.x[0] << endl;
    break;
  case TWO:
    cout << "x1 = " << ans.x[0] << endl;
    cout << "x2 = " << ans.x[1] << endl;
    break;
  case ANY:
    cout << "Any solution." << endl;
    break;
  default:
    cout << "Error." << endl;
    break;
  }
}

int main(void)
{
  SqrEquasionCoeffs coeffs;
  SqrEquasionAns ans;
  AskCoefs(coeffs);
  SolveEquasion(coeffs, ans);
  PrintAns(ans);
  return 0;
}