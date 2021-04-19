#include "Studients.hpp"

using namespace std;

void Studient::ReadTaskCoeffs()
{
  taskFile >> curCoeffs.a >> curCoeffs.b >> curCoeffs.c;
}

void Studient::PrintAnswer()
{
  answersFile << curCoeffs.a << " " << curCoeffs.b << " " << curCoeffs.c << " ";
  curSolution.PrintShort(answersFile);
  answersFile << " " << name << endl;
}

Studient::Studient(string name, istream& taskFile, ostream& answersFile) : taskFile(taskFile), answersFile(answersFile)
{
  this->name = name;
}

void Studient::DoEquationTask()
{
  while (!taskFile.eof())
  {
    ReadTaskCoeffs();
    if (taskFile.fail())
    {
      break;
    }
    TryToSolve();
    PrintAnswer();
  }
}

BadStudient::BadStudient(string name, istream& taskFile, ostream& answersFile) : Studient(name, taskFile, answersFile) {}

void BadStudient::TryToSolve()
{
  curSolution = EquationSolution(0.);
}

GoodStudient::GoodStudient(string name, istream& taskFile, ostream& answersFile) : Studient(name, taskFile, answersFile) {}

void GoodStudient::TryToSolve()
{
  EquationSolver::SolveEquation(curCoeffs, curSolution);
}

MiddleStudient::MiddleStudient(string name, istream& taskFile, ostream& answersFile) : Studient(name, taskFile, answersFile) {}

void MiddleStudient::TryToSolve()
{
  if (rand() % 2 == 0)
    EquationSolver::SolveEquation(curCoeffs, curSolution);
  else
    curSolution = EquationSolution(0.);
}
