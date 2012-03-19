/*Copyright (c) 2012 anton.feldmann@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software 
is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
*/
#pragma once

/*check if the GCC System is 32 BIT. e.g. __SIZEOF_POINTER__ is equal to 4*/
#if __SIZEOF_POINTER__ > 4
#define BREAKPOINT_PTR ".quad"
#else
#define BREAKPOINT_PTR ".long"
#endif

#define BREAKPOINTS               \
  asm("0:"                        \
      ".pushsection breakpoints;" \
      BREAKPOINT_PTR " 0b;"       \
      ".popsection;")
