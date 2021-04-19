#include "EquationSolver.hpp"

void EquationSolver::SolveSquare(EquationCoeffs& coeffs, EquationSolution& solution)
{
  double discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
  if (IsZero(discr))
    solution = EquationSolution(-coeffs.b / (2 * coeffs.a));
  else if (discr < 0)
    solution = EquationSolution(false);
  else
  {
    discr = sqrt(discr);
    solution = EquationSolution((-coeffs.b - discr) / (2 * coeffs.a), (-coeffs.b + discr) / (2 * coeffs.a));
  }
}

void EquationSolver::SolveLin(EquationCoeffs& coeffs, EquationSolution& solution)
{
  if (IsZero(coeffs.b))
  {
    if (IsZero(coeffs.c))
      solution = EquationSolution(true);
    else
      solution = EquationSolution(false);
  }
  else
  {
    if (IsZero(coeffs.c))
      solution = EquationSolution(0.);
    else
      solution = EquationSolution(-coeffs.c / coeffs.b);
  }
}

void EquationSolver::SolveEquation(EquationCoeffs& coeffs, EquationSolution& solution)
{
  if (IsZero(coeffs.a))
    SolveLin(coeffs, solution);
  else
    SolveSquare(coeffs, solution);
}