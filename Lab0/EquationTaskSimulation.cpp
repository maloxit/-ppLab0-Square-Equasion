#include <iostream>
#include <fstream>
#include <iomanip>

#include "Studients.hpp"
#include "Teacher.hpp"

using namespace std;

void MakeAllStudientsDoTasks()
{
  ifstream studFile = ifstream("studients.txt");
  ofstream answersFile = ofstream("answers.txt");
  answersFile << setprecision(6) << fixed;

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
    stud_p->DoEquationTask();
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