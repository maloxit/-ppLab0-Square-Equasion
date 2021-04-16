#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>

using namespace std;

const int ansPrecision = 6;

using SqrEqsnCoeffs = struct
{
  double a;
  double b;
  double c;
};

class SqrEqsnSolution
{
private:
  enum AnsType
  {
    ZERO,
    ONE,
    TWO,
    ANY
  } type;
  double x[2];
public:
  SqrEqsnSolution();
  SqrEqsnSolution(bool isAny);
  SqrEqsnSolution(double x1);
  SqrEqsnSolution(double x1, double x2);
  bool operator==(SqrEqsnSolution& r)
  {
    return this->type == r.type && abs(this->x[0] - r.x[0]) <= pow(10, 1 - ansPrecision) && abs(this->x[1] - r.x[1]) <= pow(10, 1 - ansPrecision);
  }
  void Print();
  void PrintShort(ostream& ostrm);
};

SqrEqsnSolution::SqrEqsnSolution()
{
  type = ZERO;
  x[0] = 0;
  x[1] = 0;
}

SqrEqsnSolution::SqrEqsnSolution(bool isAny)
{
  if (isAny)
    type = ANY;
  else
    type = ZERO;
  x[0] = 0;
  x[1] = 0;
}

SqrEqsnSolution::SqrEqsnSolution(double x1)
{
  type = ONE;
  x[0] = x1;
}

SqrEqsnSolution::SqrEqsnSolution(double x1, double x2)
{
  type = TWO;
  x[0] = x1;
  x[1] = x2;
}

void SqrEqsnSolution::Print()
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

void SqrEqsnSolution::PrintShort(ostream& ostrm)
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

class SqrEqsnSolver
{
private:
  inline int IsZero(double val) { return abs(val) < FLT_EPSILON; }
  void SolveSquare(SqrEqsnCoeffs& coeffs, SqrEqsnSolution& solution);
  void SolveLin(SqrEqsnCoeffs& coeffs, SqrEqsnSolution& solution);

public:
  void SolveEquasion(SqrEqsnCoeffs& coeffs, SqrEqsnSolution& solution);
};

void SqrEqsnSolver::SolveSquare(SqrEqsnCoeffs& coeffs, SqrEqsnSolution& solution)
{
  double discr = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs.c;
  if (IsZero(discr))
    solution = SqrEqsnSolution(-coeffs.b / (2 * coeffs.a));
  else if (discr < 0)
    solution = SqrEqsnSolution(false);
  else
  {
    discr = sqrt(discr);
    solution = SqrEqsnSolution((-coeffs.b - discr) / (2 * coeffs.a), (-coeffs.b + discr) / (2 * coeffs.a));
  }
}

void SqrEqsnSolver::SolveLin(SqrEqsnCoeffs& coeffs, SqrEqsnSolution& solution)
{
  if (IsZero(coeffs.b))
  {
    if (IsZero(coeffs.c))
      solution = SqrEqsnSolution(true);
    else
      solution = SqrEqsnSolution(false);
  }
  else
  {
    if (IsZero(coeffs.c))
      solution = SqrEqsnSolution(0.);
    else
      solution = SqrEqsnSolution(-coeffs.c / coeffs.b);
  }
}

void SqrEqsnSolver::SolveEquasion(SqrEqsnCoeffs& coeffs, SqrEqsnSolution& solution)
{
  if (IsZero(coeffs.a))
    SolveLin(coeffs, solution);
  else
    SolveSquare(coeffs, solution);
}

class Studient
{
protected:
  string name;
  SqrEqsnCoeffs curCoeffs;
  SqrEqsnSolution curSolution;
  istream& taskFile;
  ostream& answersFile;
  void ReadTaskCoeffs();
  void PrintAnswer();
  virtual void TryToSolve() {}
public:
  Studient(string name, istream& taskFile, ostream& answersFile);
  void DoSqrEqsnTask();
};

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

void Studient::DoSqrEqsnTask()
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

class BadStudient : public Studient
{
public:
  BadStudient(string name, istream& taskFile, ostream& answersFile) : Studient(name, taskFile, answersFile) {}
private:
  void TryToSolve()
  {
    curSolution = SqrEqsnSolution(0.);
  }
};

class GoodStudient : public Studient, SqrEqsnSolver
{
public:
  GoodStudient(string name, istream& taskFile, ostream& answersFile) : Studient(name, taskFile, answersFile) {}
private:
  void TryToSolve()
  {
    SolveEquasion(curCoeffs, curSolution);
  }
};

class MiddleStudient : public Studient, SqrEqsnSolver
{
public:
  MiddleStudient(string name, istream& taskFile, ostream& answersFile) : Studient(name, taskFile, answersFile) {}
private:
  void TryToSolve()
  {
    if (rand() % 2 == 0)
      SolveEquasion(curCoeffs, curSolution);
    else
      curSolution = SqrEqsnSolution(0.);
  }
};

class Teacher : SqrEqsnSolver
{
private:
  using StudientScore = struct
  {
    string name;
    int points;
  };
  list<StudientScore> studList;
  istream& answersFile;
  ostream& tableFile;
  SqrEqsnCoeffs curCoeffs;
  SqrEqsnSolution curSolution;
  SqrEqsnSolution studSolution;

  void ReadTaskCoeffs()
  {
    answersFile >> curCoeffs.a >> curCoeffs.b >> curCoeffs.c;
  }
  void ReadStudSolution()
  {
    string typeStr;
    answersFile >> typeStr;
    if (typeStr == "ZERO")
    {
      studSolution = SqrEqsnSolution(false);
    }
    else if (typeStr == "ANY")
    {
      studSolution = SqrEqsnSolution(true);
    }
    else if (typeStr == "ONE")
    {
      double x1;
      answersFile >> x1;
      studSolution = SqrEqsnSolution(x1);
    }
    else if (typeStr == "TWO")
    {
      double x1, x2;
      answersFile >> x1 >> x2;
      studSolution = SqrEqsnSolution(x1, x2);
    }
    else
    {
      studSolution = SqrEqsnSolution();
    }
  }
  void AddPoints(int points, string name)
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
public:
  Teacher(istream& answersFile, ostream& tableFile) : answersFile(answersFile), tableFile(tableFile)
  {
    studList = list<StudientScore>();
    curSolution = SqrEqsnSolution();
    studSolution = SqrEqsnSolution();
  }
  void CheckAnswers()
  {
    string name;
    while (!answersFile.eof())
    {
      ReadTaskCoeffs();
      if (answersFile.fail())
      {
        break;
      }
      SolveEquasion(curCoeffs, curSolution);
      ReadStudSolution();
      answersFile >> name;
      if (curSolution == studSolution)
        AddPoints(1, name);
      else
        AddPoints(0, name);
    }
  }
  void PrintTable()
  {
    for (auto& studScore : studList)
    {
      tableFile << studScore.name << " - " << studScore.points << endl;
    }
  }
};

void MakeAllStudientsDoTasks()
{
  ifstream studFile = ifstream("studients.txt");
  ofstream answersFile = ofstream("answers.txt");
  answersFile << setprecision(ansPrecision) << fixed;

  while (!studFile.eof())
  {
    string studName;
    string studType;
    studFile >> studName;
    if (studFile.fail())
    {
      break;
    }
    studFile >> studType;
    if (studFile.fail())
    {
      break;
    }
    Studient* stud_p;
    ifstream taskFile = ifstream("task.txt");
    if (studType == "B")
      stud_p = new BadStudient(studName, taskFile, answersFile);
    else if (studType == "G")
      stud_p = new GoodStudient(studName, taskFile, answersFile);
    else if (studType == "M")
      stud_p = new MiddleStudient(studName, taskFile, answersFile);
    else
    {
      taskFile.close();
      break;
    }
    stud_p->DoSqrEqsnTask();
    delete stud_p;
    taskFile.close();
  }
  studFile.close();
  answersFile.close();
}


int main(void)
{
  MakeAllStudientsDoTasks();
  ifstream answersFile = ifstream("answers.txt");
  ofstream tableFile = ofstream("table.txt");
  Teacher* teacher_p = new Teacher(answersFile, tableFile);
  teacher_p->CheckAnswers();
  teacher_p->PrintTable();
  tableFile.close();
  return 0;
}