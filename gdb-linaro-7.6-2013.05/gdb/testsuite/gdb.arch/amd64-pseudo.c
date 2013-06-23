/* Test program for byte registers.

   Copyright 2010-2013 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdio.h>

int data[] = {
  0x14131211,
  0x24232221,
  0x34333231,
  0x44434241,
  0x54535251,
  0x64636261,
  0x74737271,
  0x84838281,
  0x94939291,
  0xa4a3a2a1,
  0xb4b3b2b1,
  0xc4c3c2c1,
  0xd4d3d2d1,
  0xe4e3e2e1,
};

int
main (int argc, char **argv)
{
  asm ("mov 0(%0), %%eax\n\t"
       "mov 4(%0), %%ebx\n\t"
       "mov 8(%0), %%ecx\n\t"
       "mov 12(%0), %%edx\n\t"
       "mov 16(%0), %%esi\n\t"
       "mov 20(%0), %%edi\n\t"
       : /* no output operands */
       : "r" (data) 
       : "eax", "ebx", "ecx", "edx", "esi", "edi");
  asm ("nop"); /* first breakpoint here */

  asm ("mov 24(%0), %%r8d\n\t"
       "mov 28(%0), %%r9d\n\t"
       "mov 32(%0), %%r10d\n\t"
       "mov 36(%0), %%r11\n\t"
       "mov 40(%0), %%r12d\n\t"
       "mov 44(%0), %%r13d\n\t"
       "mov 48(%0), %%r14d\n\t"
       "mov 52(%0), %%r15d\n\t"
       : /* no output operands */
       : "r" (data) 
       : "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15");
  asm ("nop"); /* second breakpoint here */

  /* amd64-dword.exp writes eax-edi here.
     Tell gcc they're clobbered so it doesn't try to keep "data" in
     one of them.  */
  asm (""
       : /* no outputs */
       : /* no inputs */
       : "eax", "ebx", "ecx", "edx", "esi", "edi");

  asm ("mov %%eax, 0(%0)\n\t"
       "mov %%ebx, 4(%0)\n\t"
       "mov %%ecx, 8(%0)\n\t"
       "mov %%edx, 12(%0)\n\t"
       "mov %%esi, 16(%0)\n\t"
       "mov %%edi, 20(%0)\n\t"
       : /* no output operands */
       : "r" (data) 
       : "eax", "ebx", "ecx", "edx", "esi", "edi");
  asm ("nop"); /* third breakpoint here */

  /* amd64-dword.exp writes r8-r15 here.
     Tell gcc they're clobbered so it doesn't try to keep "data" in
     one of them.  */
  asm (""
       : /* no outputs */
       : /* no inputs */
       : "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15");

  asm ("mov %%r8d, 24(%0)\n\t"
       "mov %%r9d, 28(%0)\n\t"
       "mov %%r10d, 32(%0)\n\t"
       "mov %%r11d, 36(%0)\n\t"
       "mov %%r12d, 40(%0)\n\t"
       "mov %%r13d, 44(%0)\n\t"
       "mov %%r14d, 48(%0)\n\t"
       "mov %%r15d, 52(%0)\n\t"
       : /* no output operands */
       : "r" (data) 
       : "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15");
  puts ("Bye!"); /* forth breakpoint here */

  return 0;
}
