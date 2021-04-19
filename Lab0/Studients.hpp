#pragma once

#include "EquationSolver.hpp"

class Studient
{
protected:
  std::string name;
  EquationCoeffs curCoeffs;
  EquationSolution curSolution;
  std::istream& taskFile;
  std::ostream& answersFile;
  void ReadTaskCoeffs();
  void PrintAnswer();
  virtual void TryToSolve() = 0;
public:
  Studient(std::string name, std::istream& taskFile, std::ostream& answersFile);
  void DoEquationTask();
};

class BadStudient : public Studient
{
public:
  BadStudient(std::string name, std::istream& taskFile, std::ostream& answersFile);
private:
  void TryToSolve();
};

class GoodStudient : public Studient
{
public:
  GoodStudient(std::string name, std::istream& taskFile, std::ostream& answersFile);
private:
  void TryToSolve();
};

class MiddleStudient : public Studient
{
public:
  MiddleStudient(std::string name, std::istream& taskFile, std::ostream& answersFile);
private:
  void TryToSolve();
};