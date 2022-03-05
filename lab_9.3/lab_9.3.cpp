#include <functional>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Note {
  string fullName;
  string tel;
  int birthday[3];
};

void Fill(Note* notes, const int N);
void Print(Note* notes, const int N = 1);

void Sort(Note* notes, const int N, function<bool(Note, Note)> callback);

int Search(Note* notes, const int N, const string tel);

void SaveToFile(Note* notes, const int N, const char* filename);
void LoadFromFile(Note*& notes, int& N, const char* filename);

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  int N = 0;
  Note* notes = nullptr;
  Note* temp = nullptr;

  Note forAutoFill[10] = {
    {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
    {"Atlanta Gall", "380925229621", {4,  12, 2020} },
    {"Uma Noble",         "380633648116", {21, 5,  1998} },
    {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
    {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
    {"Santino Read",      "380683046862", {23, 3,  2010} },
    {"Shana Flores",      "380631996430", {17, 5,  1998} },
    {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
    {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
    {"Eathan Roach",      "380683038390", {7,  7,  2010} },
  };

  function<bool(Note, Note)> callback;

  char filename[100];

  string findTel;
  int findedIndex;

  int menuItem;
  do {
    cout << endl << endl;
    cout << "Виберіть дію:" << endl << endl;
    cout << " [1] - введення даних з клавіатури" << endl;
    cout << " [2] - автоматичне введення даних" << endl;
    cout << " [3] - вивід даних на екран" << endl;
    cout << " [4] - фізичне впорядкування даних" << endl;
    cout << " [5] - пошук за номером" << endl;
    cout << " [6] - зберегти дані в файл" << endl;
    cout << " [7] - загрузити дані з файлу" << endl;

    cout << endl;

    cout << " [0] - вихід та завершення роботи програми" << endl << endl;
    cout << "Введіть значення: "; cin >> menuItem;
    cout << endl << endl << endl;

    switch (menuItem)
    {
    case 1:
      cout << "Введіть N: "; cin >> N;
      notes = new Note[N];

      Fill(notes, N);
      break;

    case 2:
      cout << "Введіть N(max 10): "; cin >> N;
      if (N > 10)
        N = 10;

      temp = new Note[N];

      for (int i = 0; i < N; i++)
        temp[i] = forAutoFill[i];

      delete[] notes;
      notes = temp;
      break;

    case 3:
      Print(notes, N);
      break;

    case 4:
      callback = [](Note c, Note p) -> bool {
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

      Sort(notes, N, callback);
      break;

    case 5:
      cin.get(); cin.sync();

      cout << " Введіть номер телефону: "; getline(cin, findTel);

      if ((findedIndex = Search(notes, N, findTel)) >= 0)
        Print(&notes[findedIndex]);
      else
        cout << "Запис з таким телефонним номером не знайдено" << endl;

      break;

    case 6:
      cin.get();
      cin.sync();

      cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);

      SaveToFile(notes, N, filename);
      
      break;

    case 7:
      cin.get();
      cin.sync();

      cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);

      LoadFromFile(notes, N, filename);

      break;

    case 0:
      break;

    default:
      cout << "Ви ввели помилкове значення! "
        "Слід ввести число - номер вибраного пункту меню" << endl;
    }
  } while (menuItem != 0);

  return 0;
}

void Fill(Note* notes, const int N)
{
  for (int index = 0; index < N; index++)
  {
    cout << "Запис № " << index + 1 << ":" << endl;

    cin.get(); cin.sync();

    cout << " Прізвище та ім'я: "; getline(cin, notes[index].fullName);
    cout << endl;
    cout << " Номер телефону: "; cin >> notes[index].tel;
    cout << endl;
    
    cout << " День народження  : "; cin >> notes[index].birthday[0];
    cout << " Місяць народження: "; cin >> notes[index].birthday[1];
    cout << " Рік народження   : "; cin >> notes[index].birthday[2];

    cout << endl;
  }
}

void Print(Note* notes, const int N)
{
#pragma region HEADER
  cout << "==============================================================="
    << endl;

  cout << setfill(' ') << right << "| " << setw(3) << "№" << " | "
    << setw(20) << left << "Прізвище, ім'я" << " | "
    << setw(12) << "Телефон" << " | "
    << setw(15) << "Дата народження" << " |"
    << endl;

  cout << "---------------------------------------------------------------"
    << endl;
#pragma endregion

  for (int i = 0; i < N; i++)
  {
    Note note = notes[i];

    cout << "| " << setw(3) << right << i + 1 << " | "
      << setw(20) << left << note.fullName << " |"
      << setw(13) << right << note.tel << " | ";

    cout << setfill('0') << right
      << setw(2) << to_string(note.birthday[0]) << "."
      << setw(2) << to_string(note.birthday[1])  << "." 
      << setw(4) << to_string(note.birthday[2]) 
      << setfill(' ') << setw(7) << " |"
      << endl;

    if (i < N - 1)
      cout << "---------------------------------------------------------------"
        << endl;
  }

  cout << "==============================================================="
    << endl;
  cout << endl;
}

void Sort(Note* notes, const int N, function<bool(Note, Note)> callback)
{
  int countsSwap = 0;
  do
  {
    countsSwap = 0;

    for (int i = 1; i < N; i++) {
      const Note current = notes[i];
      const Note prev = notes[i - 1];

      if (callback(current, prev)) {
        countsSwap++;
        notes[i - 1] = current;
        notes[i] = prev;
      }
    }
  } while (countsSwap > 0);
}

int Search(Note* notes, const int N, const string tel) {
  for (int i = 0; i < N; i++)
    if (notes[i].tel == tel)
      return i;

  return -1;
}

void SaveToFile(Note* notes, const int N, const char* filename)
{
  ofstream toFile(filename, ios::binary);
  toFile.write((char*)&N, sizeof(N));

  for (int index = 0; index < N; index++)
    toFile.write((char*)&notes[index], sizeof(Note));
    
  toFile.close();
}

void LoadFromFile(Note*& notes, int& N, const char* filename)
{

  ifstream fromFile(filename, ios::binary);
  fromFile.read((char*)&N, sizeof(N));

  delete[] notes;
  notes = new Note[N]; 

  for (int i = 0; i < N; i++)
    fromFile.read((char*)&notes[i], sizeof(Note));

  fromFile.close();
}
