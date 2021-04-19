#include "Teacher.hpp"

using namespace std;

void Teacher::ReadTaskCoeffs()
{
  answersFile >> curCoeffs.a >> curCoeffs.b >> curCoeffs.c;
}

void Teacher::ReadStudSolution()
{
  string typeStr;
  answersFile >> typeStr;
  if (typeStr == "ZERO")
  {
    studSolution = EquationSolution(false);
  }
  else if (typeStr == "ANY")
  {
    studSolution = EquationSolution(true);
  }
  else if (typeStr == "ONE")
  {
    double x1;
    answersFile >> x1;
    studSolution = EquationSolution(x1);
  }
  else if (typeStr == "TWO")
  {
    double x1, x2;
    answersFile >> x1 >> x2;
    studSolution = EquationSolution(x1, x2);
  }
  else
  {
    studSolution = EquationSolution();
  }
}

void Teacher::AddPoints(int points, string name)
{
  for (auto& studScore : studList)
  {
    if (studScore.name == name)
    {
      studScore.points += points;
      return;
    }
  }
  StudientScore newStud = { name, points };
  studList.push_front(newStud);
}

Teacher::Teacher(istream& answersFile, ostream& tableFile) : answersFile(answersFile), tableFile(tableFile)
{
  studList = list<StudientScore>();
  curSolution = EquationSolution();
  studSolution = EquationSolution();
}

void Teacher::CheckAnswers()
{
  string name;
  while (!answersFile.eof())
  {
    ReadTaskCoeffs();
    if (answersFile.fail())
    {
      break;
    }
    EquationSolver::SolveEquation(curCoeffs, curSolution);
    ReadStudSolution();
    answersFile >> name;
    if (curSolution == studSolution)
      AddPoints(1, name);
    else
      AddPoints(0, name);
  }
}

void Teacher::PrintTable()
{
  for (auto& studScore : studList)
  {
    tableFile << studScore.name << " - " << studScore.points << endl;
  }
}