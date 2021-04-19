#pragma once

#include <iostream>

class EquationSolution
{
private:
  static const int ansPrecision;
  enum AnsType
  {
    ZERO,
    ONE,
    TWO,
    ANY
  } type;
  double x[2];
public:
  EquationSolution();
  EquationSolution(bool isAny);
  EquationSolution(double x1);
  EquationSolution(double x1, double x2);
  bool operator==(EquationSolution& r);
  void Print();
  void PrintShort(std::ostream& ostrm);
};

