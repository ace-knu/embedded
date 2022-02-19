/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

void call();
int global = 100;

int
main(int argc, char* argv[])
{

/* local variable */
	int local = 10;

	printf("local : %d\n",local);
	printf("global : %d\n",global);
	call();
	printf("==========================\n");

	{
		int local = 5;

		printf("local : %d\n",local);
		printf("global : %d\n",global);
		call();
		printf("==========================\n");
	}

	printf("local : %d\n",local);
	printf("global : %d\n",global);
	call();
	printf("==========================\n");

  return 0;
}

void call()
{
	static int st_call = 0;
	int call = 0;
	printf("st_call : %d \n", st_call);
	printf("call : %d \n", call);
	st_call++;
	call++;
}

//#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
