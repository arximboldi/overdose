//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2003
// Gnu Public Licence
//******************************************************************************

/*
 * Algunas correcciones realizadas por Juan Pedro Bolívar Puente para evitar
 * warnings durante el proceso de compilación.
 */

#ifndef _READ_PLY
#define _READ_PLY

#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

const int MAX_LENGTH_LINE=255;

typedef enum {PLY,FORMAT,ASCII,ELEMENT,VERTEX,FACE,END_HEADER,TEXT,NUMBER} _tokens;

struct _element_token_table
{
  string Text;
  _tokens Token;
};


class _yylval
{
public:
  float Real;
  string Text;
};


class _file_ply
{
public:


  _file_ply();
  int open(const char *File_name);
  int read(vector<float> &Vertices,vector<int> &Faces);
  int create(const char *File_name);
  int write(vector<float> &Vertices,vector<int> &Faces);
  int close();

private:
  bool Debug;
  FILE *File;
  _yylval Yylval;
  char Buffer[MAX_LENGTH_LINE];
  string Text;
  vector<_element_token_table> Token_table;
  int Num_lines;


  int 	read_line();
  int 	next_token();
  void	error(const char *Error);
  int 	is_number(const char *Aux_token);
  int 	search_token(const char *Aux_token);
};

#endif
