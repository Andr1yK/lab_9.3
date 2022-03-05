#include "pch.h"
#include "CppUnitTest.h"
#include <functional>
#include "../lab_9.3/lab_9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
    TEST_METHOD(TestSort)
    {
      function<bool(Note, Note)> callback = [](Note c, Note p) -> bool {
        int cYear = c.birthday[2],
          pYear = p.birthday[2],
          cMonth = c.birthday[1],
          pMonth = p.birthday[1],
          cDay = c.birthday[0],
          pDay = p.birthday[0];

        bool byYear = cYear > pYear;
        bool byMonth = cYear == pYear
          && cMonth > pMonth;

        bool byDay = cYear == pYear
          && cMonth == pMonth
          && cDay > pDay;

        return byYear || byMonth || byDay;
      };

      const int N = 10;

      Note notes[N] = {
        {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
        {"Atlanta Gall",      "380925229621", {4,  12, 2020} },
        {"Uma Noble",         "380633648116", {21, 5,  1998} },
        {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
        {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
        {"Santino Read",      "380683046862", {23, 3,  2010} },
        {"Shana Flores",      "380631996430", {17, 5,  1998} },
        {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
        {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
        {"Eathan Roach",      "380683038390", {7,  7,  2010} },
      };

      Sort(notes, N, callback);

      Note excepted[N] = {
        {"Atlanta Gall",      "380925229621", {4,  12, 2020} },
        {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
        {"Eathan Roach",      "380683038390", {7,  7,  2010} },
        {"Santino Read",      "380683046862", {23, 3,  2010} },
        {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
        {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
        {"Uma Noble",         "380633648116", {21, 5,  1998} },
        {"Shana Flores",      "380631996430", {17, 5,  1998} },
        {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
        {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
      };

      for (int i = 0; i < N; i++)
        Assert::AreEqual(excepted[i].fullName, notes[i].fullName);
    };

    TEST_METHOD(TestSearch1)
    {
      const int N = 10;

      Note notes[N] = {
        {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
        {"Atlanta Gall",      "380925229621", {4,  12, 2020} },
        {"Uma Noble",         "380633648116", {21, 5,  1998} },
        {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
        {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
        {"Santino Read",      "380683046862", {23, 3,  2010} },
        {"Shana Flores",      "380631996430", {17, 5,  1998} },
        {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
        {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
        {"Eathan Roach",      "380683038390", {7,  7,  2010} },
      };

      int findedIndex = Search(notes, N, "380506986742");

      Assert::AreEqual(4, findedIndex);

      Assert::AreEqual(notes[4].fullName, notes[findedIndex].fullName);
      Assert::AreEqual(notes[4].tel, notes[findedIndex].tel);
    };

    TEST_METHOD(TestSearch2)
    {
      const int N = 10;

      Note notes[N] = {
        {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
        {"Atlanta Gall",      "380925229621", {4,  12, 2020} },
        {"Uma Noble",         "380633648116", {21, 5,  1998} },
        {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
        {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
        {"Santino Read",      "380683046862", {23, 3,  2010} },
        {"Shana Flores",      "380631996430", {17, 5,  1998} },
        {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
        {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
        {"Eathan Roach",      "380683038390", {7,  7,  2010} },
      };

      int findedIndex = Search(notes, N, "380000000000");

      Assert::AreEqual(-1, findedIndex);
    };

    TEST_METHOD(TestWorkWithFile)
    {
      int N = 10;

      Note notes[10] = {
        {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
        {"Atlanta Gall",      "380925229621", {4,  12, 2020} },
        {"Uma Noble",         "380633648116", {21, 5,  1998} },
        {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
        {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
        {"Santino Read",      "380683046862", {23, 3,  2010} },
        {"Shana Flores",      "380631996430", {17, 5,  1998} },
        {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
        {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
        {"Eathan Roach",      "380683038390", {7,  7,  2010} },
      };


      SaveToFile(notes, N, "testWorkWithFile.txt");

      Note* actual = new Note[N];
      LoadFromFile(actual, N, "testWorkWithFile.txt");

      for (int i = 0; i < N; i++) {
        Assert::AreEqual(notes[i].fullName, actual[i].fullName);
        Assert::AreEqual(notes[i].tel, actual[i].tel);
      }
    };
	};
}
