/*
**
snuspi - a SNUSP interpreter, with enhancement
Copyright (C) 2008, 2009, 2010, 2011, 2012  Mauro Panigada

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Steet, Fifth Floor, Boston, MA  02111-1307  USA
    
**
** The enhancing is about the accumulator register that can
** hold a value read from a cell, and write it to a cell;
** the & change the behaviour of , (read from a cell and store
** into the accumulator, instead of reading from stdin and
** writing to the current cell) and . (write accumulator
** to the current cell, instead of writing the current cell
** to stdout)
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "snuspi.h"



bool debug = false;

char buffer[LINESIZE];

int  x = 0, y = 0, dx = 1, dy = 0;
bool swapped = false;
char accumulator = 0;

struct fieldslice field[MAXHEIGHT];
struct callstack stack[MAXCALLS];
char cells[MAXCELLS];

int maxi = 0;
int sp = MAXCALLS;
int cellidx = 0;


const char *in_the_space = "help! I was thrown alone in the void space!\n";
const char *trip_around_world = "wow! I always dreamed about a trip around the world!\n";


int main(int argc, char **argv)
{
  int i, c;
  char *filename = NULL, *pc;
  FILE *srch;
  bool ok = true;
  
  for(i = 1; i < argc ; i++ )
  {
    if ( strcmp(argv[i], "snusp") == 0 )
    {
      if ( (i+1) < argc )
      {
	filename = argv[i + 1]; i++;
      } else {
	fprintf(stderr, "omitted string for 'snusp'\n");
      }
      continue;
    }
    if ( strcmp(argv[i], "debug") == 0 )
    {
      debug = true; continue;
    }
    fprintf(stderr, "unrecognized option '%s'\n", argv[i]);
  }
     
  if ( filename == NULL )
  {
    fprintf(stderr, "no source file specified\n");
    exit(1);
  }
  
  /* load program */
  if ( (srch = fopen(filename, "r") ) == NULL )
  {
    fprintf(stderr, "cannot locate file '%s'\n", filename);
    exit(1);
  }
     
  for (i = 0; (fgets(buffer, LINESIZE, srch) != NULL) && i < MAXHEIGHT; i++ )
  {
    field[i].s = strdup(buffer);
    if ( field[i].s == NULL )
    {
      fprintf(stderr, "can't allocate buffer\n");
      exit(1);
    }
    field[i].l = strlen(buffer);
    if ( (pc = strchr(buffer, snusp_START)) != NULL )
    {
      x = pc - buffer;
      y = i;
    }
  }
  if ( i == MAXHEIGHT )
  {
    fprintf(stderr, "bottom universal limit reached! Continuing anyway\n");
  }
  fclose(srch);
     
  maxi = i;
     
  /* interpreter */
  while( ok )
  {
    char cmd;
         
    if ( (y >= i) || (y < 0) )
    {
      fprintf(stderr, in_the_space);
      fprintf(stderr, "(%d,%d) (%d,%d)\n", x, y, dx, dy);
      break;
    }
    if ( (x >= field[y].l) || (x < 0) )
    {
      fprintf(stderr, in_the_space);
      fprintf(stderr, "(%d,%d) (%d,%d)\n", x, y, dx, dy);
      break;
    }
    cmd = field[y].s[x];
    if ( debug )
    {
      fprintf(stderr, "(%d, %d) (%d, %d) %c sp=%d idx=%d\n", x, y,
	      dx, dy, cmd, sp, cellidx);
    }
    switch ( cmd )
    {
    case snusp_LEAVE:
      if ( sp < MAXCALLS )
      {
	x = stack[sp].x;
	y = stack[sp].y;
	dx = stack[sp].dx;
	dy = stack[sp].dy;
	sp++;
      } else {
	ok = false;
      }
      break;
    case snusp_ENTER:
      sp--;
      if (sp < 0 )
      {
	fprintf(stderr, "too many nested calls! skipping!\n");
	sp++;
      } else {
	stack[sp].x = x;
	stack[sp].y = y;
	stack[sp].dx = dx;
	stack[sp].dy = dy;
	x += dx; y += dy;
      }
      break;
    case snusp_RIGHT:
      if ( (cellidx+1) >= MAXCELLS )
      {
	fprintf(stderr, trip_around_world);
      }
      cellidx = (cellidx+1)%MAXCELLS;
      break;
    case snusp_LEFT:
      if ( (cellidx-1) < 0 )
      {
	fprintf(stderr, trip_around_world);
      }
      cellidx = (cellidx+MAXCELLS-1)%MAXCELLS;
      break;
    case snusp_INC:
      cells[cellidx]++;
      break;
    case snusp_DEC:
      cells[cellidx]--;
      break;
    case snusp_LURD:
      /* \ */
      if ( dx != 0 )
      {
	dy = dx; dx = 0;
      } else {
	dx = dy;
	dy = 0;
      }
      break;
    case snusp_RULD:
      /* / */
      if ( dx != 0 )
      {
	dy = -dx; dx = 0;
      } else {
	dx = -dy; dy = 0;
      }
      break;
    case snusp_SKIP:
      x += dx; y += dy;
      break;
    case snusp_SKIPZ:
      if ( cells[cellidx] == 0 )
      {
	x += dx; y += dy;
      }
      break;
    case snusp_READ:
      c = getchar();
      cells[cellidx] = c & 0xFF;
      break;
    case snusp_WRITE:
      printf("%c", cells[cellidx]);
      break;
    default:
      break;
    }
    x += dx; y += dy;
  }
     
  for(i=0; i < maxi; i++)
    free(field[i].s);

  return 0;
}
