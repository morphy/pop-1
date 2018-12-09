#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

using namespace std;

void clear()
{
  //cout << "\033[2J\033[1;1H";
  system("cls");
}

void setw(int x)
{
  for(int i=0; i<x; i++) cout << " ";
}

void help()
{
  int width = 62;
  cout << char(0xC9);
  for(int i=0; i<(width-2); i++) cout << char(0xCD);
  cout << char(0xBB) << endl;

  cout << char(0xBA) << "h - display help";
  setw(width - 18);
  cout << char(0xBA) << endl;

  cout << char(0xBA) << "n x y abc - new game x by y using abc letters";
  setw(width - 47);
  cout << char(0xBA) << endl;

  cout << char(0xBA) << "b - go back to game";
  setw(width - 21);
  cout << char(0xBA) << endl;

  cout << char(0xBA) << "q - quit game";
  setw(width - 15);
  cout << char(0xBA) << endl;

  cout << char(0xBA) << "c x - set uppercase to x";
  setw(width - 26);
  cout << char(0xBA) << endl;

  cout << char(0xC8);
  for(int i=0; i<(width-2); i++) cout << char(0xCD);
  cout << char(0xBC) << endl;
}

void logo()
{
  cout << char(0xC9);
  for(int i=0; i<7; i++) cout << char(0xCD);
  cout << char(0xBB) << endl;
  cout << char(0xBA) << "Literki" << char(0xBA) << endl;
  cout << char(0xC8);
  for(int i=0; i<7; i++) cout << char(0xCD);
  cout << char(0xBC) << endl << endl;
}

void dmap(int width, int height, char map[])
{
  cout << char(0xC9);
  for(int i=0; i<(width*2); i++) cout << char(0xCD);
  cout << char(0xBB) << endl;

  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(j == 0) cout << char(0xBA);
      cout << map[i*width + j] << " ";
      if(j == width-1) cout << char(0xBA);
    }

    cout << endl;
  }

  cout << char(0xC8);
  for(int i=0; i<(width*2); i++) cout << char(0xCD);
  cout << char(0xBC) << endl;
}

void gmap(int width, int height, string letters, char map[])
{
  int index;
  char l;

  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      index = rand() % letters.length();
      l = letters[index];
      map[i*width + j] = l;
    }
  }
}

void spread(int width, int height, int row, int col, char map[])
{
  char thi = map[row*width + col];
  map[row*width + col] -= 32;

  if(row+1 < height)
  {
    if(map[(row+1)*width + col] == thi)
    {
      spread(width, height, row+1, col, map);
    }
  }

  if(col+1 < width)
  {
    if(map[row*width + (col+1)] == thi)
    {
      spread(width, height, row, col+1, map);
    }
  }

  if(row > 0)
  {
    if(map[(row-1)*width + col] == thi)
    {
      spread(width, height, row-1, col, map);
    }
  }

  if(col > 0)
  {
    if(map[row*width + (col-1)] == thi)
    {
      spread(width, height, row, col-1, map);
    }
  }

  return;
}

void replace(int width, int height, int row, int col, char letter, char map[])
{
  char thi = map[row*width + col];
  map[row*width + col] = letter;

  if(row+1 < height)
  {
    if(map[(row+1)*width + col] == thi)
    {
      replace(width, height, row+1, col, letter, map);
    }
  }

  if(col+1 < width)
  {
    if(map[row*width + (col+1)] == thi)
    {
      replace(width, height, row, col+1, letter, map);
    }
  }

  if(row > 0)
  {
    if(map[(row-1)*width + col] == thi)
    {
      replace(width, height, row-1, col, letter, map);
    }
  }

  if(col > 0)
  {
    if(map[row*width + (col-1)] == thi)
    {
      replace(width, height, row, col-1, letter, map);
    }
  }

  return;
}

bool win(int width, int height, char map[])
{
  for(int i=0; i<height; i++)
  {
    for(int j=0; j<width; j++)
    {
      if(map[i*width + j] != map[0]) return false;
    }
  }

  return true;
}

bool isint(string x)
{
  for(int i=0; i<x.length(); i++)
  {
    if(!((x[i] > 47) && (x[i] < 58))) return false;
  }

  return true;
}

int getint()
{
  string w;
  cin >> w;

  while(!isint(w))
  {
    cout << "Please enter a number" << endl;
    cin >> w;
  }

  return stoi(w);
}

bool isstring(string x)
{
  for(int i=0; i<x.length(); i++)
  {
    if(!((x[i] > 96) && (x[i] < 123))) return false;
  }

  return true;
}

string getstring()
{
  string w;
  cin >> w;

  while(!isstring(w))
  {
    cout << "Please enter lowercase letters" << endl;
    cin >> w;
  }

  return w;
}

bool ischar(string x)
{
  if(x.length() != 1) return false;
  if(!((x[0] > 96) && (x[0] < 123))) return false;

  return true;
}

char getchr()
{
  string w;
  cin >> w;

  while(!ischar(w))
  {
    cout << "Please enter lowercase letter" << endl;
    cin >> w;
  }

  return w[0];
}

int main()
{
  /* Init variables */

  char cmd, letter;
  int width, height, index, helper;
  string w, h, letters;

  srand(time(NULL));

  clear();

  /* Enter start settings */

  cout << endl << "Enter width: ";
  width = getint();

  cout << endl << "Enter height: ";
  height = getint();

  cout << endl << "Enter letters: ";
  letters = getstring();

  clear();

  /* Init map */

  char *map = new char[width*height];

  /* Genrate random letters */

  gmap(width, height, letters, map);

  /* Make uppercase */

  spread(width, height, 0, 0, map);

  /* Display logo */

  logo();

  /* Display map */

  dmap(width, height, map);

  /* Get user input */

  while(true)
  {
    cout << endl << "command: ";
    cmd = getchr();

    switch(cmd)
    {
      case 'h':
      {
        clear();
        logo();
        help();
      } break;
      case 'q':
      {
        delete [] map;
        return 0;
      } break;
      case 'b':
      {
        clear();
        logo();
        dmap(width, height, map);
      } break;
      case 'n':
      {
        cout << endl << "Enter width: ";
        width = getint();

        cout << endl << "Enter height: ";
        height = getint();

        cout << endl << "Enter letters: ";
        letters = getstring();

        delete [] map;
        char *map = new char[width*height];
        gmap(width, height, letters, map);
        spread(width, height, 0, 0, map);

        if(win(width, height, map))
        {
          cout << endl << "You have won the game !" << endl;
        }

        clear();
        logo();
        dmap(width, height, map);
      } break;
      case 'c':
      {
        cout << endl << "Enter letter: ";
        letter = getchr();

        replace(width, height, 0, 0, letter, map);
        spread(width, height, 0, 0, map);
        clear();
        logo();
        dmap(width, height, map);

        if(win(width, height, map))
        {
          cout << endl << "You have won the game !" << endl;
        }
      } break;
      default: cout << "Unknown command, try again" << endl; break;
    }
  }

  delete [] map;

  return 0;
}
