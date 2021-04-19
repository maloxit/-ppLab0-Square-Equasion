#pragma once

#include "EquationSolution.hpp"

using EquationCoeffs = struct
{
  double a;
  double b;
  double c;
};

class EquationSolver
{
private:
  static inline int IsZero(double val) { return abs(val) < FLT_EPSILON; }
  static void SolveSquare(EquationCoeffs& coeffs, EquationSolution& solution);
  static void SolveLin(EquationCoeffs& coeffs, EquationSolution& solution);

public:
  static void SolveEquation(EquationCoeffs& coeffs, EquationSolution& solution);
};