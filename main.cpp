#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void clear()
{
  cout << "\033[2J\033[1;1H";
}

void gotoxy(int x, int y)
{
  cout << "\033[" << x << ";" << y << "H";
}

void setw(int x)
{
  for(int i=0; i<x; i++) cout << " ";
}

void help()
{
  int width = 62;
  cout << "+";
  for(int i=0; i<(width-2); i++) cout << "-";
  cout << "+" << endl;

  cout << "| h - display help";
  setw(width - 18 - 1);
  cout << "|" << endl;

  cout << "| n x y abc - new game x by y using abc letters";
  setw(width - 47 - 1);
  cout << "|" << endl;

  cout << "| b - go back to game";
  setw(width - 21 - 1);
  cout << "|" << endl;

  cout << "| q - quit game";
  setw(width - 15 - 1);
  cout << "|" << endl;

  cout << "| c x - set uppercase to x";
  setw(width - 26 - 1);
  cout << "|" << endl;

  cout << "+";
  for(int i=0; i<(width-2); i++) cout << "-";
  cout << "+" << endl;
}







int main()
{
  char cmd, l;
  int width, height, index;
  string letters;

  srand(time(NULL));

  clear();
  cin >> width >> height >> letters;
  clear();
  char *map = new char[width*height];


  for(int i=0; i<width; i++)
  {
    for(int j=0; j<height; j++)
    {
      index = rand() % letters.length();
      l = letters[index];
      map[j*height + i] = l;
    }
  }

  cout << "wartosd: " << endl << map[10*height + 10] << endl;

  for(int i=0; i<width; i++)
  {
    for(int j=0; j<height; j++)
    {
      cout << map[j*height + i] << " ";
    }
    cout << endl;
  }



  cout << "Literki" << endl << "Pomoc - h" << endl;

  while(true)
  {
    cin >> cmd;

    switch(cmd)
    {
      case 'h':
      {
        clear();
        help();
      } break;
      case 'q':
      {
        delete [] map;
        return 0;
      } break;
      case 'n':
      {

      } break;
      default: cout << "Unknown command. Fuck you" << endl; break;
    }
  }






  delete [] map;

  return 0;
}
