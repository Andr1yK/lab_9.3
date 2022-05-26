#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

template <class T, class R>
void log(T str, R name) {
  cout << name << ": " << str << ';' << endl;
}

template <class T>
void log(T str) {
  cout << "LOG: " << str << ';' << endl;
}

struct Note {
  string fullName;
  string tel;
  int birthday[3];
};

int getLineCountInFile(const char* filename);

void Fill(Note* notes, const int N);
void Print(Note* notes, const int N = 1);

int Search(Note* notes, const int N, const string tel);
int SearchInFile(const char* filename, const string tel);

void WriteToFileEnd(ofstream &toFile, Note note);
void appendToFile(Note note, const char* filename);

void SaveToFile(Note* notes, const int N, const char* filename);
Note* LoadFromFile(const char* filename, unsigned int N, int startLine = 0);

int main()
{
  setlocale(LC_CTYPE, "ukr");

  int N = 0;
  Note* notes = nullptr;
  Note* temp = nullptr;
  Note* fromFileStore = nullptr;

  Note forAutoFill[10] = {
    {"Sheikh Barnard",    "380634161835", {14, 9,  2014} },
    {"Atlanta Gall",      "380925229621", {4, 12,  2020} },
    {"Uma Noble",         "380633648116", {21, 5,  1998} },
    {"Siddharth Ferry",   "380507585956", {7,  4,  1974} },
    {"Jaxon Leal",        "380506986742", {12, 8,  2000} },
    {"Santino Read",      "380683046862", {23, 3,  2010} },
    {"Shana Flores",      "380631996430", {17, 5,  1998} },
    {"Louisa Irwin",      "380503792270", {5,  9,  1974} },
    {"Anita Dominguez",   "380665919172", {1,  7,  2003} },
    {"Eathan Roach",      "380683038390", {7,  7,  2010} },
  };

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
    cout << " [4] - пошук за номером" << endl;
    cout << " [5] - пошук за номером в файлі" << endl;
    cout << " [6] - зберегти дані в файл" << endl;
    cout << " [7] - загрузити дані з файлу" << endl;
    cout << " [8] - додати дані в файл" << endl;

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
      cin.get(); cin.sync();

      cout << " Введіть номер телефону: "; getline(cin, findTel);

      if ((findedIndex = Search(notes, N, findTel)) >= 0)
        Print(&notes[findedIndex]);
      else
        cout << "Запис з таким телефонним номером не знайдено" << endl;

      break;
    
    case 5:
      cin.get(); cin.sync();

      cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
      cout << " Введіть номер телефону: "; getline(cin, findTel);

      if ((findedIndex = SearchInFile(filename, findTel)) >= 0)
        Print(&(LoadFromFile(filename, 1, findedIndex)[0]));
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

      N = getLineCountInFile(filename);

      delete[] notes;
      notes = LoadFromFile(filename, N);

      break;

    case 8:
      cin.get();
      cin.sync();

      cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);

      delete[] temp;
      temp = new Note[1];

      Fill(temp, 1);

      appendToFile(temp[0], filename);

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

int Search(Note* notes, const int N, const string tel) {
  for (int i = 0; i < N; i++)
    if (notes[i].tel == tel)
      return i;

  return -1;
}

int SearchInFile(const char* filename, const string tel) {
  ifstream fromFile(filename);

  string currentTel;
  string str;
  int pos;

  for (int index = 0; getline(fromFile, str); index++, pos = 0)
  {
    pos = str.find(", ", pos + 1);
    currentTel.assign(str, pos + 2, str.find(", ", pos + 1) - pos - 2);

    if (currentTel == tel) {
      log(index);
      return index;
    }
  }

  return -1;
}

int getLineCountInFile(const char* filename) {
  ifstream file(filename);
  unsigned int count;
  string line;
  
  for(count = 0; getline(file, line); count++);

  file.close();

  return count;
}

void appendToFile(Note note, const char* filename) {
  ofstream toFile(filename, ios::app);

  WriteToFileEnd(toFile, note);

  toFile.close();
}

void WriteToFileEnd(ofstream &toFile, Note note) {
  int* date = note.birthday;

  toFile << note.fullName << ", "
    << note.tel << ", "
    << date[0] << ", "
    << date[1] << ", "
    << date[2]
    << endl;
}

void SaveToFile(Note* notes, const int N, const char* filename)
{
  ofstream toFile(filename, ios::in);

  for (int index = 0; index < N; index++) {
    WriteToFileEnd(toFile, notes[index]);
  };

  toFile.close();
}

Note* LoadFromFile(const char* filename, unsigned int N, int startLine)
{
  ifstream fromFile(filename);
  string str;

  Note* notes = new Note[N];

  int pos = 0;
  int posEnd = 0;
  int index = 0;
  int currentLine = 0;

  string tempLine;

  while (getline(fromFile, str) && index < N)
  {
    currentLine++;
    
    if (currentLine <= startLine)
      continue;

    posEnd = str.find(", ", pos + 1);
    notes[index].fullName.assign(str, pos, posEnd - pos);
    pos = posEnd;

    posEnd = str.find(", ", pos + 1);
    notes[index].tel.assign(str, pos + 2, posEnd - pos - 2);
    pos = posEnd;

    for (int i = 0; i < 3; i++) {
      posEnd = str.find(", ", pos + 1);
      notes[index].birthday[i] = stoi(tempLine.assign(str, pos + 2, posEnd - pos - 2));
      pos = posEnd;
    }

    index++;
    pos = 0;
  }

  fromFile.close();

  return notes;
}
