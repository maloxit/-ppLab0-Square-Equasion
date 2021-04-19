#pragma once

#include <iostream>
#include <list>
#include "EquationSolver.hpp"

class Teacher
{
private:
  using StudientScore = struct
  {
    std::string name;
    int points;
  };
  std::list<StudientScore> studList;
  std::istream& answersFile;
  std::ostream& tableFile;
  EquationCoeffs curCoeffs;
  EquationSolution curSolution;
  EquationSolution studSolution;
  void ReadTaskCoeffs();
  void ReadStudSolution();
  void AddPoints(int points, std::string name);

public:
  Teacher(std::istream& answersFile, std::ostream& tableFile);
  void CheckAnswers();
  void PrintTable();
};
