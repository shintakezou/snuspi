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
*/

#ifndef SNUSPI_H_
#define SNUSPI_H_

#define LINESIZE 1024
#define MAXHEIGHT 1024
#define MAXCALLS 1024
#define MAXCELLS 1024

#define snusp_START '$'
#define snusp_LEFT '<'
#define snusp_RIGHT '>'
#define snusp_INC '+'
#define snusp_DEC '-'
#define snusp_READ ','
#define snusp_WRITE '.'
#define snusp_LURD '\\'
#define snusp_RULD '/'
#define snusp_SKIP '!'
#define snusp_SKIPZ '?'
#define snusp_ENTER '@'
#define snusp_LEAVE '#'

				 /* enhanced: & transform , so that it read from current cell
				    into an accumulator, . write the accumulator to the current
				    cell; the others act the same; & again put the previous behaviour
				    back */

struct fieldslice
{
  int l;
  char *s;
};

struct callstack
{
  int x, y;
  int dx, dy;
};



#endif
