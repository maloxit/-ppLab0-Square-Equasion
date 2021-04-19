#include "EquationSolution.hpp"

using namespace std;

const int EquationSolution::ansPrecision = 6;

EquationSolution::EquationSolution()
{
  type = ZERO;
  x[0] = 0;
  x[1] = 0;
}

EquationSolution::EquationSolution(bool isAny)
{
  if (isAny)
    type = ANY;
  else
    type = ZERO;
  x[0] = 0;
  x[1] = 0;
}

EquationSolution::EquationSolution(double x1)
{
  type = ONE;
  x[0] = x1;
}

EquationSolution::EquationSolution(double x1, double x2)
{
  type = TWO;
  x[0] = x1;
  x[1] = x2;
}

bool EquationSolution::operator==(EquationSolution& r)
{
  return this->type == r.type && abs(this->x[0] - r.x[0]) <= pow(10, 1 - ansPrecision) && abs(this->x[1] - r.x[1]) <= pow(10, 1 - ansPrecision);
}

void EquationSolution::Print()
{
  switch (type)
  {
  case ZERO:
    cout << "No solution." << endl;
    break;
  case ONE:
    cout << "x = " << x[0] << endl;
    break;
  case TWO:
    cout << "x1 = " << x[0] << endl << "x2 = " << x[1] << endl;
    break;
  case ANY:
    cout << "Any solution." << endl;
    break;
  default:
    cout << "Error." << endl;
    break;
  }
}

void EquationSolution::PrintShort(ostream& ostrm)
{
  switch (type)
  {
  case ZERO:
    ostrm << "ZERO";
    break;
  case ONE:
    ostrm << "ONE " << x[0];
    break;
  case TWO:
    ostrm << "TWO " << x[0] << " " << x[1];
    break;
  case ANY:
    ostrm << "ANY";
    break;
  default:
    ostrm << "ERROR";
    break;
  }
}

