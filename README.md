ABOUT
=====

SNUSP is an esolanguage, you can find more info on Internet, e.g.
http://esolangs.org/wiki/SNUSP

This interpreter implements the Modular SNUSP

Usage from the command line is very simple

./snuspi snusp FILE [debug]

where FILE is the source file, and 'snusp' the option that requires the FILE
name after it.



COMPILING
=========

As simple as

gcc snuspi.c

Add options as you prefer.


NOTES (2012)
============

I've written this interpreter years ago; if I remember well, it was
my first contribution to the RosettaCode wiki

http://rosettacode.org/wiki/RCSNUSP/C

In this snapshot I've removed the support for the "enhanced" version,
I've moved something in the header and used C99 bool type.
