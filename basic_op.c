/* Copyright (c) 2015 The University of Edinburgh. */

/* 
* This software was developed as part of the                       
* EC FP7 funded project Adept (Project ID: 610490)                 
* www.adept-project.eu                                            
*/

/* Licensed under the Apache License, Version 2.0 (the "License"); */
/* you may not use this file except in compliance with the License. */
/* You may obtain a copy of the License at */

/*     http://www.apache.org/licenses/LICENSE-2.0 */

/* Unless required by applicable law or agreed to in writing, software */
/* distributed under the License is distributed on an "AS IS" BASIS, */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and */
/* limitations under the License. */

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "level0.h"
#include "utils.h"

/*
 *
 * Basic integer operations - +, -, * and /
 *
 */
int int_basic_op(char *opType, unsigned long reps){

#ifdef ONEVOL
	unsigned int a, b, c;
	volatile unsigned int d;
#undef ONEVOL
#else
#ifdef ALLVOL
	volatile unsigned int a, b, c, d;
#undef ALLVOL
#else
	unsigned int a, b, c, d;
#endif
#endif
  
	int i;

	char choice = (char)opType[0];
  
	srand((unsigned int)time(NULL));
  
	a = rand();
	b = rand();
	c = rand();
	d = rand();

	struct timespec start, end;
  
	/* warm-up loop with nop */
	warmup_loop(reps);

	/* measure loop on its own with nop */
	loop_timer_nop(reps);

	/* measure loop on its own */
	loop_timer(reps);

	switch(choice){
  
	/* addition */  
    case '+': {
      
      /* warm-up loop */
      for(i=0; i<100; i++) c = a+b;
      
      /* main loops */
      clock_gettime(CLOCK, &start);
      
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("add r1,r0\n\t"
			::: "r1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			::: "eax", "memory");
#else
	  c = a+d;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Addition - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("add r1,r0\n\t"
			"add r2,r1\n\t"
			::: "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			::: "eax", "ebx", "memory");
#else
	  c = a+d;
	  b = d+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Addition - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a+d;
	  b = d+c;
	  a = b+d;
	  c = d+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Addition - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       "add r2,r0\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			"add %%ecx,%%eax\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a+d;
	  b = d+c;
	  a = b+d;
	  c = d+a;
	  b = c+d;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Addition - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       "add r2,r0\n\t"
		       "add r0,r1\n\t"
		       "add r1,r2\n\t"
		       "add r2,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			"add %%ecx,%%eax\n\t"
			"add %%ebx,%%ecx\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a+d;
	  b = d+c;
	  a = b+d;
	  c = d+a;
	  b = c+d;
	  c = d+b;
	  a = d+c;
	  b = a+d;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Addition - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       "add r2,r0\n\t"
		       "add r0,r1\n\t"
		       "add r1,r2\n\t"
		       "add r2,r3\n\t"
		       "add r0,r3\n\t"
		       "add r1,r1\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			"add %%ecx,%%eax\n\t"
			"add %%ebx,%%ecx\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%ebx,%%eax\n\t"
			"add %%ecx,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a+d;
	  b = d+c;
	  a = b+d;
	  c = d+a;
	  b = c+d;
	  c = d+b;
	  a = d+c;
	  b = a+d;
	  c = b+d;
	  b = c+d;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Addition - 10 ops");

      break;
    }
    case '-': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a-b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("sub r1,r0\n\t"
			::: "r1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			::: "eax", "memory");
#else
	  c = a-b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Substraction - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("sub r1,r0\n\t"
			"sub r2,r1\n\t"
			::: "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			::: "eax", "ebx", "memory");
#else
	  c = a-b;
	  a = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Substraction - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a-b;
	  a = b-c;
	  b = a-c;
	  c = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Substraction - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       "sub r2,r0\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			"sub %%ecx,%%eax\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a-b;
	  a = b-c;
	  b = a-c;
	  c = c-a;
	  b = b-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Substraction - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       "sub r2,r0\n\t"
		       "sub r0,r1\n\t"
		       "sub r1,r2\n\t"
		       "sub r2,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			"sub %%ecx,%%eax\n\t"
			"sub %%ebx,%%ecx\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a-b;
	  a = b-c;
	  b = a-c;
	  c = c-a;
	  b = b-a;
	  c = c-b;
	  a = a-c;
	  b = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Substraction - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       "sub r2,r0\n\t"
		       "sub r0,r1\n\t"
		       "sub r1,r2\n\t"
		       "sub r2,r3\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r1\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			"sub %%ecx,%%eax\n\t"
			"sub %%ebx,%%ecx\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a-b;
	  a = b-c;
	  b = a-c;
	  c = c-a;
	  b = b-a;
	  c = c-b;
	  a = a-c;
	  b = b-c;
	  c = b-a;
	  b = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Substraction - 10 ops");
      
      break;
    }
    case '*': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a*b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("mul r1,r0\n\t"
			::: "r1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			::: "eax", "memory");
#else
	  c = a*b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Multiplication - 1 op");
      
      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("mul r1,r0\n\t"
			"mul r2,r1\n\t"
			::: "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			::: "eax", "ebx", "memory");
#else
	  c = a*b;
	  a = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Multiplication - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a*b;
	  a = b*c;
	  b = a*c;
	  c = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Multiplication - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       "mul r2,r0\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			"imul %%ecx,%%eax\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a*b;
	  a = b*c;
	  b = a*c;
	  c = c*a;
	  b = b*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Multiplication - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       "mul r2,r0\n\t"
		       "mul r0,r1\n\t"
		       "mul r1,r2\n\t"
		       "mul r2,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			"imul %%ecx,%%eax\n\t"
			"imul %%ebx,%%ecx\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a*b;
	  a = b*c;
	  b = a*c;
	  c = c*a;
	  b = b*a;
	  c = c*b;
	  a = a*c;
	  b = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Multiplication - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       "mul r2,r0\n\t"
		       "mul r0,r1\n\t"
		       "mul r1,r2\n\t"
		       "mul r2,r3\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r1\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			"imul %%ecx,%%eax\n\t"
			"imul %%ebx,%%ecx\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#else
	  c = a*b;
	  a = b*c;
	  b = a*c;
	  c = c*a;
	  b = b*a;
	  c = c*b;
	  a = a*c;
	  b = b*c;
	  c = b*a;
	  b = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Multiplication - 10 ops");

      break;
    }
    case '/': {
      
      /* need to avoid re-use of variables to make sure */
      /* we do not get divison by 0.                    */
      volatile int r1,r2,r3,r4,r5,r6,r7,r8,r9,r10;

      /* ensure none of the random numbers are zero */
      if (a == 0) a++;
      if (b == 0) b++;
      if (c == 0) c++;
      if (d == 0) d++;

      /* warm-up loop */
      for(i=0; i<100; i++) r1 = a/b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
		       :: "r" (b) : "r0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       :: "a" ((long)a), "r" (b) : "edx", "memory");
#else
	  r1 = a/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Division - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      :: "r" (b), "r" (c) : "r0", "r1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       :: "a" ((long)a), "r" (b), "r" (c) : "edx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Division - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       :: "a" ((long)a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Division - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      "udiv r0,%2\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       :: "a" ((long)a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Division - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      "udiv r0,%2\n\t"
	      "udiv r2,%1\n\t"
	      "udiv r0,%0\n\t"
	      "udiv r1,%2\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       :: "a" ((long)a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Division - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      "udiv r0,%2\n\t"
	      "udiv r2,%1\n\t"
	      "udiv r0,%0\n\t"
	      "udiv r1,%2\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r0,%1\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       :: "a" ((long)a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
	r9 = c/c;
	r10 = r10/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Integer Division - 10 ops");

      break;
    }
    default: printf("Only possible operation choices are '+', '-', '*' and '/'.\n");
  }
  
  return 0;
  
}

int float_basic_op(char *opType, unsigned long reps){

#ifdef ONEVOL
	float a, b;
	volatile float c;
#undef ONEVOL
#else
#ifdef ALLVOL
	volatile float a, b, c;
#undef ALLVOL
#else
	float a, b, c;
#endif
#endif  

  int i;

  char choice = (char)opType[0];

  srand((unsigned int)time(NULL));
  
  a = rand()/1.0;
  b = rand()/1.0;
  
  struct timespec start, end;
  
  /* warm-up loop with nop */
  warmup_loop(reps);

  /* measure loop on its own with nop */
  loop_timer_nop(reps);

  /* measure loop on its own */
  loop_timer(reps);
  
  switch(choice){
    case '+': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a+b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fadds s0,s0,s1\n\t"
		       ::: "s0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addss %%xmm1,%%xmm0\n\t"
		       ::: "xmm0", "memory");
#else
	  c = a+b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Addition - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fadds s0,s0,s1\n\t"
		       "fadds s1,s1,s2\n\t"
		       ::: "s0", "s1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addss %%xmm1,%%xmm0\n\t"
		       "addss %%xmm2,%%xmm1\n\t"
		       ::: "xmm0", "xmm1", "memory");
#else
	c = a+b;
	a = b+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Addition - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fadds s0,s0,s1\n\t"
		       "fadds s1,s1,s2\n\t"
		       "fadds s2,s2,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addss %%xmm1,%%xmm0\n\t"
		       "addss %%xmm2,%%xmm1\n\t"
		       "addss %%xmm0,%%xmm2\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
#endif
      }
      
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Addition - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fadds s0,s0,s1\n\t"
		       "fadds s1,s1,s2\n\t"
		       "fadds s2,s2,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       "fadds s2,s2,s1\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addss %%xmm1,%%xmm0\n\t"
		       "addss %%xmm2,%%xmm1\n\t"
		       "addss %%xmm0,%%xmm2\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       "addss %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Addition - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fadds s0,s0,s1\n\t"
		       "fadds s1,s1,s2\n\t"
		       "fadds s2,s2,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       "fadds s2,s2,s1\n\t"
		       "fadds s1,s1,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       "fadds s2,s2,s1\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addss %%xmm1,%%xmm0\n\t"
		       "addss %%xmm2,%%xmm1\n\t"
		       "addss %%xmm0,%%xmm2\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       "addss %%xmm1,%%xmm2\n\t"
		       "addss %%xmm0,%%xmm1\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       "addss %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
	c = c+b;
	a = a+c;
	b = b+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Addition - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fadds s0,s0,s1\n\t"
		       "fadds s1,s1,s2\n\t"
		       "fadds s2,s2,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       "fadds s2,s2,s1\n\t"
		       "fadds s1,s1,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       "fadds s2,s2,s1\n\t"
		       "fadds s1,s1,s0\n\t"
		       "fadds s0,s0,s2\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addss %%xmm1,%%xmm0\n\t"
		       "addss %%xmm2,%%xmm1\n\t"
		       "addss %%xmm0,%%xmm2\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       "addss %%xmm1,%%xmm2\n\t"
		       "addss %%xmm0,%%xmm1\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       "addss %%xmm1,%%xmm2\n\t"
		       "addss %%xmm0,%%xmm1\n\t"
		       "addss %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
	c = c+b;
	a = a+c;
	b = b+c;
	c = b+a;
	b = c+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Addition - 10 ops");

      break;
    }
    case '-': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a-b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubs s0,s0,s1\n\t"
		       ::: "s0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subss %%xmm1,%%xmm0\n\t"
		       ::: "xmm0", "memory");
#else
	  c = a-b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Substraction - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubs s0,s0,s1\n\t"
		       "fsubs s1,s1,s2\n\t"
		       ::: "s0", "s1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subss %%xmm1,%%xmm0\n\t"
		       "subss %%xmm2,%%xmm1\n\t"
		       ::: "xmm0", "xmm1", "memory");
#else
	c = a-b;
	a = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Substraction - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubs s0,s0,s1\n\t"
		       "fsubs s1,s1,s2\n\t"
		       "fsubs s2,s2,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subss %%xmm1,%%xmm0\n\t"
		       "subss %%xmm2,%%xmm1\n\t"
		       "subss %%xmm0,%%xmm2\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Substraction - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubs s0,s0,s1\n\t"
		       "fsubs s1,s1,s2\n\t"
		       "fsubs s2,s2,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       "fsubs s2,s2,s1\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subss %%xmm1,%%xmm0\n\t"
		       "subss %%xmm2,%%xmm1\n\t"
		       "subss %%xmm0,%%xmm2\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       "subss %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Substraction - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubs s0,s0,s1\n\t"
		       "fsubs s1,s1,s2\n\t"
		       "fsubs s2,s2,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       "fsubs s2,s2,s1\n\t"
		       "fsubs s1,s1,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       "fsubs s2,s2,s1\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subss %%xmm1,%%xmm0\n\t"
		       "subss %%xmm2,%%xmm1\n\t"
		       "subss %%xmm0,%%xmm2\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       "subss %%xmm1,%%xmm2\n\t"
		       "subss %%xmm0,%%xmm1\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       "subss %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
	c = c-b;
	a = a-c;
	b = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Substraction - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubs s0,s0,s1\n\t"
		       "fsubs s1,s1,s2\n\t"
		       "fsubs s2,s2,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       "fsubs s2,s2,s1\n\t"
		       "fsubs s1,s1,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       "fsubs s2,s2,s1\n\t"
		       "fsubs s1,s1,s0\n\t"
		       "fsubs s0,s0,s2\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subss %%xmm1,%%xmm0\n\t"
		       "subss %%xmm2,%%xmm1\n\t"
		       "subss %%xmm0,%%xmm2\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       "subss %%xmm1,%%xmm2\n\t"
		       "subss %%xmm0,%%xmm1\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       "subss %%xmm1,%%xmm2\n\t"
		       "subss %%xmm0,%%xmm1\n\t"
		       "subss %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
	c = c-b;
	a = a-c;
	b = b-c;
	c = b-a;
	b = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Substraction - 10 ops");

      break;
    }
    case '*': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a*b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuls s0,s0,s1\n\t"
		       ::: "s0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulss %%xmm1,%%xmm0\n\t"
		       ::: "xmm0", "memory");
#else
	  c = a*b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Multiplication - 1 op");
      
      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuls s0,s0,s1\n\t"
		       "fmuls s1,s1,s2\n\t"
		       ::: "s0", "s1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulss %%xmm1,%%xmm0\n\t"
		       "mulss %%xmm2,%%xmm1\n\t"
		       ::: "xmm0", "xmm1", "memory");
#else
	c = a*b;
	a = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Multiplication - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuls s0,s0,s1\n\t"
		       "fmuls s1,s1,s2\n\t"
		       "fmuls s2,s2,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulss %%xmm1,%%xmm0\n\t"
		       "mulss %%xmm2,%%xmm1\n\t"
		       "mulss %%xmm0,%%xmm2\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Multiplication - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuls s0,s0,s1\n\t"
		       "fmuls s1,s1,s2\n\t"
		       "fmuls s2,s2,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       "fmuls s2,s2,s1\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulss %%xmm1,%%xmm0\n\t"
		       "mulss %%xmm2,%%xmm1\n\t"
		       "mulss %%xmm0,%%xmm2\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       "mulss %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Multiplication - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuls s0,s0,s1\n\t"
		       "fmuls s1,s1,s2\n\t"
		       "fmuls s2,s2,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       "fmuls s2,s2,s1\n\t"
		       "fmuls s1,s1,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       "fmuls s2,s2,s1\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulss %%xmm1,%%xmm0\n\t"
		       "mulss %%xmm2,%%xmm1\n\t"
		       "mulss %%xmm0,%%xmm2\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       "mulss %%xmm1,%%xmm2\n\t"
		       "mulss %%xmm0,%%xmm1\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       "mulss %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
	c = c*b;
	a = a*c;
	b = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Multiplication - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuls s0,s0,s1\n\t"
		       "fmuls s1,s1,s2\n\t"
		       "fmuls s2,s2,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       "fmuls s2,s2,s1\n\t"
		       "fmuls s1,s1,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       "fmuls s2,s2,s1\n\t"
		       "fmuls s1,s1,s0\n\t"
		       "fmuls s0,s0,s2\n\t"
		       ::: "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulss %%xmm1,%%xmm0\n\t"
		       "mulss %%xmm2,%%xmm1\n\t"
		       "mulss %%xmm0,%%xmm2\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       "mulss %%xmm1,%%xmm2\n\t"
		       "mulss %%xmm0,%%xmm1\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       "mulss %%xmm1,%%xmm2\n\t"
		       "mulss %%xmm0,%%xmm1\n\t"
		       "mulss %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
	c = c*b;
	a = a*c;
	b = b*c;
	c = b*a;
	b = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float multiplication - 10 ops");
      
      break;
    }
    case '/': {
      /* need to avoid re-use of variables to make sure */
      /* we do not get divison by 0.                    */
      volatile int r1,r2,r3,r4,r5,r6,r7,r8,r9,r10;

      if (a == 0.0) a = 1.0;
      if (b == 0.0) b = 1.0;
      if (c == 0.0) c = 1.0;

      /* warm-up loop */
      for(i=0; i<100; i++) r1 = a/b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivs s0,s0,%0\n\t"
		       :: "t" (b) : "s0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divss %0,%%xmm0\n\t"
		       :: "x" (b) : "xmm0", "memory");
#else
	  r1 = a/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Division - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivs s0,s0,%0\n\t"
		       "fdivs s1,s1,%1\n\t"
		       :: "t" (b), "t" (c) : "s0", "s1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divss %0,%%xmm0\n\t"
		       "divss %1,%%xmm1\n\t"
		       :: "x" (b), "x" (c) : "xmm0", "xmm1", "memory");
#else
	r1 = a/b;
	r2 = b/c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Division - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivs s0,s0,%0\n\t"
		       "fdivs s1,s1,%1\n\t"
		       "fdivs s2,s2,%2\n\t"
		       "fdivs s0,s0,%1\n\t"
		       :: "t" (a), "t" (b), "t" (c) : "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divss %0,%%xmm0\n\t"
		       "divss %1,%%xmm1\n\t"
		       "divss %2,%%xmm2\n\t"
		       "divss %1,%%xmm0\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Division - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivs s0,s0,%0\n\t"
		       "fdivs s1,s1,%1\n\t"
		       "fdivs s2,s2,%2\n\t"
		       "fdivs s0,s0,%1\n\t"
		       "fdivs s2,s2,%0\n\t"
		       :: "t" (a), "t" (b), "t" (c) : "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divss %0,%%xmm0\n\t"
		       "divss %1,%%xmm1\n\t"
		       "divss %2,%%xmm2\n\t"
		       "divss %1,%%xmm0\n\t"
		       "divss %0,%%xmm2\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Division - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivs s0,s0,%0\n\t"
		       "fdivs s1,s1,%1\n\t"
		       "fdivs s2,s2,%2\n\t"
		       "fdivs s0,s0,%1\n\t"
		       "fdivs s2,s2,%0\n\t"
		       "fdivs s1,s1,%2\n\t"
		       "fdivs s0,s0,%2\n\t"
		       "fdivs s2,s2,%1\n\t"
		       :: "t" (a), "t" (b), "t" (c) : "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divss %0,%%xmm0\n\t"
		       "divss %1,%%xmm1\n\t"
		       "divss %2,%%xmm2\n\t"
		       "divss %1,%%xmm0\n\t"
		       "divss %0,%%xmm2\n\t"
		       "divss %2,%%xmm1\n\t"
		       "divss %2,%%xmm0\n\t"
		       "divss %1,%%xmm2\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Division - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivs s0,s0,%0\n\t"
		       "fdivs s1,s1,%1\n\t"
		       "fdivs s2,s2,%2\n\t"
		       "fdivs s0,s0,%1\n\t"
		       "fdivs s2,s2,%0\n\t"
		       "fdivs s1,s1,%2\n\t"
		       "fdivs s0,s0,%2\n\t"
		       "fdivs s2,s2,%1\n\t"
		       "fdivs s1,s1,%0\n\t"
		       "fdivs s0,s0,%2\n\t"
		       :: "t" (a), "t" (b), "t" (c) : "s0", "s1", "s2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divss %0,%%xmm0\n\t"
		       "divss %1,%%xmm1\n\t"
		       "divss %2,%%xmm2\n\t"
		       "divss %1,%%xmm0\n\t"
		       "divss %0,%%xmm2\n\t"
		       "divss %2,%%xmm1\n\t"
		       "divss %2,%%xmm0\n\t"
		       "divss %1,%%xmm2\n\t"
		       "divss %0,%%xmm1\n\t"
		       "divss %2,%%xmm0\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
	r9 = c/c;
	r10 = r10/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Float Division - 10 ops");

      break;
    }
    default: printf("Only possible operation choices are '+', '-', '*' and '/'.\n");
  }
  
  return 0;
  
}

int long_basic_op(char *opType, unsigned long reps){
  
  #ifdef ONEVOL
	long a, b;
	volatile long c;
#undef ONEVOL
#else
#ifdef ALLVOL
	volatile long a, b, c;
#undef ALLVOL
#else
	long a, b, c;
#endif
#endif

	int i;

  	char choice = (char)opType[0];
  
	srand((unsigned int)time(NULL));
  
	a = (long)rand();
  	b = (long)rand();
  	c = (long)rand();
  
  	struct timespec start, end;
  
	/* warm-up loop with nop */
	warmup_loop(reps);

	/* measure loop on its own with nop */
	loop_timer_nop(reps);

	/* measure loop on its own */
	loop_timer(reps);
  
  	switch(choice){
    	case '+': {
      	/* warm-up loop */
      	for(i=0; i<100; i++) c = a+b;
      
	    /* main loop */
    	clock_gettime(CLOCK, &start);
      	for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  		asm volatile ("add r1,r0\n\t"
			::: "r1", "memory");
#elif defined __i386__ && !defined NO_ASM
	  		asm volatile ("add %%ebx,%%eax\n\t"
			::: "eax", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  		asm volatile ("add %%rbx,%%rax\n\t"
			::: "rax", "memory");
#else
	  		c = a+b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Addition - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("add r1,r0\n\t"
			"add r2,r1\n\t"
			::: "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			::: "eax", "ebx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("add %%rbx,%%rax\n\t"
			"add %%rcx,%%rbx\n\t"
			::: "rax", "rbx", "memory");
#else
	c = a+b;
	a = b+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Addition - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("add %%rbx,%%rax\n\t"
			"add %%rcx,%%rbx\n\t"
			"add %%rax,%%rcx\n\t"
			"add %%rax,%%rbx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
#endif
      }
      
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Addition - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       "add r2,r0\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			"add %%ecx,%%eax\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("add %%rbx,%%rax\n\t"
			"add %%rcx,%%rbx\n\t"
			"add %%rax,%%rcx\n\t"
			"add %%rax,%%rbx\n\t"
			"add %%rcx,%%rax\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Addition - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       "add r2,r0\n\t"
		       "add r0,r1\n\t"
		       "add r1,r2\n\t"
		       "add r2,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			"add %%ecx,%%eax\n\t"
			"add %%ebx,%%ecx\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("add %%rbx,%%rax\n\t"
			"add %%rcx,%%rbx\n\t"
			"add %%rax,%%rcx\n\t"
			"add %%rax,%%rbx\n\t"
			"add %%rcx,%%rax\n\t"
			"add %%rbx,%%rcx\n\t"
			"add %%rcx,%%rbx\n\t"
			"add %%rax,%%rcx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
	c = c+b;
	a = a+c;
	b = b+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Addition - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("add r1,r0\n\t"
		       "add r2,r1\n\t"
		       "add r0,r3\n\t"
		       "add r1,r3\n\t"
		       "add r2,r0\n\t"
		       "add r0,r1\n\t"
		       "add r1,r2\n\t"
		       "add r2,r3\n\t"
		       "add r0,r3\n\t"
		       "add r1,r1\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("add %%ebx,%%eax\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%eax,%%ebx\n\t"
			"add %%ecx,%%eax\n\t"
			"add %%ebx,%%ecx\n\t"
			"add %%ecx,%%ebx\n\t"
			"add %%eax,%%ecx\n\t"
			"add %%ebx,%%eax\n\t"
			"add %%ecx,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("add %%rbx,%%rax\n\t"
			"add %%rcx,%%rbx\n\t"
			"add %%rax,%%rcx\n\t"
			"add %%rax,%%rbx\n\t"
			"add %%rcx,%%rax\n\t"
			"add %%rbx,%%rcx\n\t"
			"add %%rcx,%%rbx\n\t"
			"add %%rax,%%rcx\n\t"
			"add %%rbx,%%rax\n\t"
			"add %%rcx,%%rcx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
	c = c+b;
	a = a+c;
	b = b+c;
	c = b+a;
	b = c+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Addition - 10 ops");

      break;
    }
    case '-': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a-b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("sub r1,r0\n\t"
			::: "r1", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			::: "eax", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("sub %%rbx,%%rax\n\t"
			::: "rax", "memory");
#else
	  c = a-b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("sub r1,r0\n\t"
			"sub r2,r1\n\t"
			::: "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			::: "eax", "ebx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("sub %%rbx,%%rax\n\t"
			"sub %%rcx,%%rbx\n\t"
			::: "rax", "rbx", "memory");
#else
	c = a-b;
	a = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("sub %%rbx,%%rax\n\t"
			"sub %%rcx,%%rbx\n\t"
			"sub %%rax,%%rcx\n\t"
			"sub %%rax,%%rbx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       "sub r2,r0\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			"sub %%ecx,%%eax\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("sub %%rbx,%%rax\n\t"
			"sub %%rcx,%%rbx\n\t"
			"sub %%rax,%%rcx\n\t"
			"sub %%rax,%%rbx\n\t"
			"sub %%rcx,%%rax\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       "sub r2,r0\n\t"
		       "sub r0,r1\n\t"
		       "sub r1,r2\n\t"
		       "sub r2,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			"sub %%ecx,%%eax\n\t"
			"sub %%ebx,%%ecx\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("sub %%rbx,%%rax\n\t"
			"sub %%rcx,%%rbx\n\t"
			"sub %%rax,%%rcx\n\t"
			"sub %%rax,%%rbx\n\t"
			"sub %%rcx,%%rax\n\t"
			"sub %%rbx,%%rcx\n\t"
			"sub %%rcx,%%rbx\n\t"
			"sub %%rax,%%rcx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
	c = c-b;
	a = a-c;
	b = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("sub r1,r0\n\t"
		       "sub r2,r1\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r3\n\t"
		       "sub r2,r0\n\t"
		       "sub r0,r1\n\t"
		       "sub r1,r2\n\t"
		       "sub r2,r3\n\t"
		       "sub r0,r3\n\t"
		       "sub r1,r1\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%eax,%%ebx\n\t"
			"sub %%ecx,%%eax\n\t"
			"sub %%ebx,%%ecx\n\t"
			"sub %%ecx,%%ebx\n\t"
			"sub %%eax,%%ecx\n\t"
			"sub %%ebx,%%eax\n\t"
			"sub %%ecx,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("sub %%rbx,%%rax\n\t"
			"sub %%rcx,%%rbx\n\t"
			"sub %%rax,%%rcx\n\t"
			"sub %%rax,%%rbx\n\t"
			"sub %%rcx,%%rax\n\t"
			"sub %%rbx,%%rcx\n\t"
			"sub %%rcx,%%rbx\n\t"
			"sub %%rax,%%rcx\n\t"
			"sub %%rbx,%%rax\n\t"
			"sub %%rcx,%%rcx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
	c = c-b;
	a = a-c;
	b = b-c;
	c = b-a;
	b = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction - 10 ops");
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) c = a-b;
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Substraction");
      
      //      printf("Done for opType 'substraction'.\n");
      break;
    }
    case '*': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a*b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("mul r1,r0\n\t"
			::: "r1", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			::: "eax", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("imul %%rbx,%%rax\n\t"
			::: "rax", "memory");
#else
	  c = a*b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Multiplication - 1 op");
      
      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile ("mul r1,r0\n\t"
			"mul r2,r1\n\t"
			::: "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			::: "eax", "ebx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("imul %%rbx,%%rax\n\t"
			"imul %%rcx,%%rbx\n\t"
			::: "rax", "rbx", "memory");
#else
	c = a*b;
	a = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Multiplication - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("imul %%rbx,%%rax\n\t"
			"imul %%rcx,%%rbx\n\t"
			"imul %%rax,%%rcx\n\t"
			"imul %%rax,%%rbx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Multiplication - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       "mul r2,r0\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			"imul %%ecx,%%eax\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("imul %%rbx,%%rax\n\t"
			"imul %%rcx,%%rbx\n\t"
			"imul %%rax,%%rcx\n\t"
			"imul %%rax,%%rbx\n\t"
			"imul %%rcx,%%rax\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Multiplication - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       "mul r2,r0\n\t"
		       "mul r0,r1\n\t"
		       "mul r1,r2\n\t"
		       "mul r2,r3\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			"imul %%ecx,%%eax\n\t"
			"imul %%ebx,%%ecx\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("imul %%rbx,%%rax\n\t"
			"imul %%rcx,%%rbx\n\t"
			"imul %%rax,%%rcx\n\t"
			"imul %%rax,%%rbx\n\t"
			"imul %%rcx,%%rax\n\t"
			"imul %%rbx,%%rcx\n\t"
			"imul %%rcx,%%rbx\n\t"
			"imul %%rax,%%rcx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
	c = c*b;
	a = a*c;
	b = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Multiplication - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("mul r1,r0\n\t"
		       "mul r2,r1\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r3\n\t"
		       "mul r2,r0\n\t"
		       "mul r0,r1\n\t"
		       "mul r1,r2\n\t"
		       "mul r2,r3\n\t"
		       "mul r0,r3\n\t"
		       "mul r1,r1\n\t"
		       ::: "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile ("imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%eax,%%ebx\n\t"
			"imul %%ecx,%%eax\n\t"
			"imul %%ebx,%%ecx\n\t"
			"imul %%ecx,%%ebx\n\t"
			"imul %%eax,%%ecx\n\t"
			"imul %%ebx,%%eax\n\t"
			"imul %%ecx,%%ecx\n\t"
			::: "eax", "ebx", "ecx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile ("imul %%rbx,%%rax\n\t"
			"imul %%rcx,%%rbx\n\t"
			"imul %%rax,%%rcx\n\t"
			"imul %%rax,%%rbx\n\t"
			"imul %%rcx,%%rax\n\t"
			"imul %%rbx,%%rcx\n\t"
			"imul %%rcx,%%rbx\n\t"
			"imul %%rax,%%rcx\n\t"
			"imul %%rbx,%%rax\n\t"
			"imul %%rcx,%%rcx\n\t"
			::: "rax", "rbx", "rcx", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
	c = c*b;
	a = a*c;
	b = b*c;
	c = b*a;
	b = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Multiplication - 10 ops");

      break;
    }
    case '/': {

      /* need to avoid re-use of variables to make sure */
      /* we do not get divison by 0.                    */
      volatile int r1,r2,r3,r4,r5,r6,r7,r8,r9,r10;

      /* ensure none of the random numbers are zero */
      if (a == 0) a++;
      if (b == 0) b++;
      if (c == 0) c++;

      /* warm-up loop */
      for(i=0; i<100; i++) r1 = a/b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
		       :: "r" (b) : "r0", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       :: "a" (a), "r" (b) : "edx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile("xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       :: "a" (a), "r" (b) : "rdx", "memory");
#else
	  r1 = a/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Division - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      :: "r" (b), "r" (c) : "r0", "r1", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       :: "a" (a), "r" (b), "r" (c) : "edx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile("xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       :: "a" (a), "r" (b), "r" (c) : "rdx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Division - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile("xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "rdx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Division - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      "udiv r0,%2\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile("xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "rdx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Division - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      "udiv r0,%2\n\t"
	      "udiv r2,%1\n\t"
	      "udiv r0,%0\n\t"
	      "udiv r1,%2\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile("xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "rdx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Division - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("udiv r0,%0\n\t"
	      "udiv r1,%1\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r1,%0\n\t"
	      "udiv r0,%2\n\t"
	      "udiv r2,%1\n\t"
	      "udiv r0,%0\n\t"
	      "udiv r1,%2\n\t"
	      "udiv r2,%2\n\t"
	      "udiv r0,%1\n\t"
	      :: "r" (a), "r" (b), "r" (c) : "r0", "r1", "r2", "memory");
#elif defined __i386__ && !defined NO_ASM
	  asm volatile("xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %2\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %3\n\t"
		       "xor %%edx,%%edx\n\t"
		       "div %1\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "edx", "memory");
#elif defined __amd64__ && !defined NO_ASM
	  asm volatile("xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %2\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %3\n\t"
		       "xor %%rdx,%%rdx\n\t"
		       "div %1\n\t"
		       :: "a" (a), "r" (a), "r" (b), "r" (c) : "rdx", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
	r9 = c/c;
	r10 = r10/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Long Division - 10 ops");

      break;
    }
    default: printf("Only possible operation choices are '+', '-', '*' and '/'.\n");
  }
  
  return 0;
  
}

int double_basic_op(char *opType, unsigned long reps){

#ifdef ONEVOL
	double a, b;
	volatile double c;
#undef ONEVOL
#else
#ifdef ALLVOL
	volatile double a, b, c;
#undef ALLVOL
#else
	double a, b, c;
#endif
#endif
  
  int i;
  
  char choice = (char)opType[0];

  srand((int)time(NULL));
  
  a = rand()/1.0;
  b = rand()/1.0;

  struct timespec start, end;
  
  //  printf("Benchmarking double operation %c.\n", choice);
  
  /* warm-up loop with nop */
  warmup_loop(reps);

  /* measure loop on its own with nop */
  loop_timer_nop(reps);

  /* measure loop on its own */
  loop_timer(reps);
  
  switch(choice){
    case '+': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a+b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("faddd d0,d0,d1\n\t"
		       ::: "d0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addsd %%xmm1,%%xmm0\n\t"
		       ::: "xmm0", "memory");
#else
	  c = a+b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Addition - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("faddd d0,d0,d1\n\t"
		       "faddd d1,d1,d2\n\t"
		       ::: "d0", "d1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addsd %%xmm1,%%xmm0\n\t"
		       "addsd %%xmm2,%%xmm1\n\t"
		       ::: "xmm0", "xmm1", "memory");
#else
	c = a+b;
	a = b+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Addition - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("faddd d0,d0,d1\n\t"
		       "faddd d1,d1,d2\n\t"
		       "faddd d2,d2,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addsd %%xmm1,%%xmm0\n\t"
		       "addsd %%xmm2,%%xmm1\n\t"
		       "addsd %%xmm0,%%xmm2\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
#endif
      }
      
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Addition - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("faddd d0,d0,d1\n\t"
		       "faddd d1,d1,d2\n\t"
		       "faddd d2,d2,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       "faddd d2,d2,d1\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addsd %%xmm1,%%xmm0\n\t"
		       "addsd %%xmm2,%%xmm1\n\t"
		       "addsd %%xmm0,%%xmm2\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       "addsd %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Addition - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("faddd d0,d0,d1\n\t"
		       "faddd d1,d1,d2\n\t"
		       "faddd d2,d2,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       "faddd d2,d2,d1\n\t"
		       "faddd d1,d1,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       "faddd d2,d2,d1\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addsd %%xmm1,%%xmm0\n\t"
		       "addsd %%xmm2,%%xmm1\n\t"
		       "addsd %%xmm0,%%xmm2\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       "addsd %%xmm1,%%xmm2\n\t"
		       "addsd %%xmm0,%%xmm1\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       "addsd %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
	c = c+b;
	a = a+c;
	b = b+c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Addition - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("faddd d0,d0,d1\n\t"
		       "faddd d1,d1,d2\n\t"
		       "faddd d2,d2,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       "faddd d2,d2,d1\n\t"
		       "faddd d1,d1,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       "faddd d2,d2,d1\n\t"
		       "faddd d1,d1,d0\n\t"
		       "faddd d0,d0,d2\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("addsd %%xmm1,%%xmm0\n\t"
		       "addsd %%xmm2,%%xmm1\n\t"
		       "addsd %%xmm0,%%xmm2\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       "addsd %%xmm1,%%xmm2\n\t"
		       "addsd %%xmm0,%%xmm1\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       "addsd %%xmm1,%%xmm2\n\t"
		       "addsd %%xmm0,%%xmm1\n\t"
		       "addsd %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a+b;
	a = b+c;
	b = a+c;
	c = c+a;
	b = b+a;
	c = c+b;
	a = a+c;
	b = b+c;
	c = b+a;
	b = c+a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Addition - 10 ops");

      //      printf("Done for opType 'addition'.\n");
      break;
    }
    case '-': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a-b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubd d0,d0,d1\n\t"
		       ::: "d0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subsd %%xmm1,%%xmm0\n\t"
		       ::: "xmm0", "memory");
#else
	  c = a-b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Substraction - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubd d0,d0,d1\n\t"
		       "fsubd d1,d1,d2\n\t"
		       ::: "d0", "d1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subsd %%xmm1,%%xmm0\n\t"
		       "subsd %%xmm2,%%xmm1\n\t"
		       ::: "xmm0", "xmm1", "memory");
#else
	c = a-b;
	a = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Substraction - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubd d0,d0,d1\n\t"
		       "fsubd d1,d1,d2\n\t"
		       "fsubd d2,d2,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subsd %%xmm1,%%xmm0\n\t"
		       "subsd %%xmm2,%%xmm1\n\t"
		       "subsd %%xmm0,%%xmm2\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Substraction - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubd d0,d0,d1\n\t"
		       "fsubd d1,d1,d2\n\t"
		       "fsubd d2,d2,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       "fsubd d2,d2,d1\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subsd %%xmm1,%%xmm0\n\t"
		       "subsd %%xmm2,%%xmm1\n\t"
		       "subsd %%xmm0,%%xmm2\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       "subsd %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Substraction - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubd d0,d0,d1\n\t"
		       "fsubd d1,d1,d2\n\t"
		       "fsubd d2,d2,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       "fsubd d2,d2,d1\n\t"
		       "fsubd d1,d1,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       "fsubd d2,d2,d1\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subsd %%xmm1,%%xmm0\n\t"
		       "subsd %%xmm2,%%xmm1\n\t"
		       "subsd %%xmm0,%%xmm2\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       "subsd %%xmm1,%%xmm2\n\t"
		       "subsd %%xmm0,%%xmm1\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       "subsd %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
	c = c-b;
	a = a-c;
	b = b-c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Substraction - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fsubd d0,d0,d1\n\t"
		       "fsubd d1,d1,d2\n\t"
		       "fsubd d2,d2,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       "fsubd d2,d2,d1\n\t"
		       "fsubd d1,d1,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       "fsubd d2,d2,d1\n\t"
		       "fsubd d1,d1,d0\n\t"
		       "fsubd d0,d0,d2\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("subsd %%xmm1,%%xmm0\n\t"
		       "subsd %%xmm2,%%xmm1\n\t"
		       "subsd %%xmm0,%%xmm2\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       "subsd %%xmm1,%%xmm2\n\t"
		       "subsd %%xmm0,%%xmm1\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       "subsd %%xmm1,%%xmm2\n\t"
		       "subsd %%xmm0,%%xmm1\n\t"
		       "subsd %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a-b;
	a = b-c;
	b = a-c;
	c = c-a;
	b = b-a;
	c = c-b;
	a = a-c;
	b = b-c;
	c = b-a;
	b = c-a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Substraction - 10 ops");

      break;
    }
    case '*': {
      /* warm-up loop */
      for(i=0; i<100; i++) c = a*b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuld d0,d0,d1\n\t"
		       ::: "d0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulsd %%xmm1,%%xmm0\n\t"
		       ::: "xmm0", "memory");
#else
	  c = a*b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Multiplication - 1 op");
      
      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuld d0,d0,d1\n\t"
		       "fmuld d1,d1,d2\n\t"
		       ::: "d0", "d1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulsd %%xmm1,%%xmm0\n\t"
		       "mulsd %%xmm2,%%xmm1\n\t"
		       ::: "xmm0", "xmm1", "memory");
#else
	c = a*b;
	a = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Multiplication - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuld d0,d0,d1\n\t"
		       "fmuld d1,d1,d2\n\t"
		       "fmuld d2,d2,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulsd %%xmm1,%%xmm0\n\t"
		       "mulsd %%xmm2,%%xmm1\n\t"
		       "mulsd %%xmm0,%%xmm2\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Multiplication - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuld d0,d0,d1\n\t"
		       "fmuld d1,d1,d2\n\t"
		       "fmuld d2,d2,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       "fmuld d2,d2,d1\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulsd %%xmm1,%%xmm0\n\t"
		       "mulsd %%xmm2,%%xmm1\n\t"
		       "mulsd %%xmm0,%%xmm2\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       "mulsd %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Multiplication - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuld d0,d0,d1\n\t"
		       "fmuld d1,d1,d2\n\t"
		       "fmuld d2,d2,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       "fmuld d2,d2,d1\n\t"
		       "fmuld d1,d1,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       "fmuld d2,d2,d1\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulsd %%xmm1,%%xmm0\n\t"
		       "mulsd %%xmm2,%%xmm1\n\t"
		       "mulsd %%xmm0,%%xmm2\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       "mulsd %%xmm1,%%xmm2\n\t"
		       "mulsd %%xmm0,%%xmm1\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       "mulsd %%xmm1,%%xmm2\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
	c = c*b;
	a = a*c;
	b = b*c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Multiplication - 8 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fmuld d0,d0,d1\n\t"
		       "fmuld d1,d1,d2\n\t"
		       "fmuld d2,d2,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       "fmuld d2,d2,d1\n\t"
		       "fmuld d1,d1,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       "fmuld d2,d2,d1\n\t"
		       "fmuld d1,d1,d0\n\t"
		       "fmuld d0,d0,d2\n\t"
		       ::: "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("mulsd %%xmm1,%%xmm0\n\t"
		       "mulsd %%xmm2,%%xmm1\n\t"
		       "mulsd %%xmm0,%%xmm2\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       "mulsd %%xmm1,%%xmm2\n\t"
		       "mulsd %%xmm0,%%xmm1\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       "mulsd %%xmm1,%%xmm2\n\t"
		       "mulsd %%xmm0,%%xmm1\n\t"
		       "mulsd %%xmm2,%%xmm0\n\t"
		       ::: "xmm0", "xmm1", "xmm2", "memory");
#else
	c = a*b;
	a = b*c;
	b = a*c;
	c = c*a;
	b = b*a;
	c = c*b;
	a = a*c;
	b = b*c;
	c = b*a;
	b = c*a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double multiplication - 10 ops");

      break;
    }
    case '/': {
      /* need to avoid re-use of variables to make sure */
      /* we do not get divison by 0.                    */
      volatile int r1,r2,r3,r4,r5,r6,r7,r8,r9,r10;

      if (a == 0.0) a = 1.0;
      if (b == 0.0) b = 1.0;
      if (c == 0.0) c = 1.0;

      /* warm-up loop */
      for(i=0; i<100; i++) r1 = a/b;
      
      /* main loop */
      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++) {
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivd d0,d0,%P0\n\t"
		       :: "w" (b) : "d0", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divsd %0,%%xmm0\n\t"
		       :: "x" (b) : "xmm0", "memory");
#else
	  r1 = a/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Division - 1 op");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivd d0,d0,%P0\n\t"
		       "fdivd d1,d1,%P1\n\t"
		       :: "w" (b), "w" (c) : "d0", "d1", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divsd %0,%%xmm0\n\t"
		       "divsd %1,%%xmm1\n\t"
		       :: "x" (b), "x" (c) : "xmm0", "xmm1", "memory");
#else
	r1 = a/b;
	r2 = b/c;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Division - 2 ops");

      reps = reps / 2;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivd d0,d0,%P0\n\t"
		       "fdivd d1,d1,%P1\n\t"
		       "fdivd d2,d2,%P2\n\t"
		       "fdivd d0,d0,%P1\n\t"
		       :: "w" (a), "w" (b), "w" (c) : "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divsd %0,%%xmm0\n\t"
		       "divsd %1,%%xmm1\n\t"
		       "divsd %2,%%xmm2\n\t"
		       "divsd %1,%%xmm0\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Division - 4 ops");

      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivd d0,d0,%P0\n\t"
		       "fdivd d1,d1,%P1\n\t"
		       "fdivd d2,d2,%P2\n\t"
		       "fdivd d0,d0,%P1\n\t"
		       "fdivd d2,d2,%P0\n\t"
		       :: "w" (a), "w" (b), "w" (c) : "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divsd %0,%%xmm0\n\t"
		       "divsd %1,%%xmm1\n\t"
		       "divsd %2,%%xmm2\n\t"
		       "divsd %1,%%xmm0\n\t"
		       "divsd %0,%%xmm2\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Division - 5 ops");

      reps = reps * 5 / 8;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivd d0,d0,%P0\n\t"
		       "fdivd d1,d1,%P1\n\t"
		       "fdivd d2,d2,%P2\n\t"
		       "fdivd d0,d0,%P1\n\t"
		       "fdivd d2,d2,%P0\n\t"
		       "fdivd d1,d1,%P2\n\t"
		       "fdivd d0,d0,%P2\n\t"
		       "fdivd d2,d2,%P1\n\t"
		       :: "w" (a), "w" (b), "w" (c) : "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divsd %0,%%xmm0\n\t"
		       "divsd %1,%%xmm1\n\t"
		       "divsd %2,%%xmm2\n\t"
		       "divsd %1,%%xmm0\n\t"
		       "divsd %0,%%xmm2\n\t"
		       "divsd %2,%%xmm1\n\t"
		       "divsd %2,%%xmm0\n\t"
		       "divsd %1,%%xmm2\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Division - 8 ops");
      
      reps = reps * 4 / 5;

      clock_gettime(CLOCK, &start);
      for(i=0; i<reps; i++){
#if defined __arm__ && !defined NO_ASM
	  asm volatile("fdivd d0,d0,%P0\n\t"
		       "fdivd d1,d1,%P1\n\t"
		       "fdivd d2,d2,%P2\n\t"
		       "fdivd d0,d0,%P1\n\t"
		       "fdivd d2,d2,%P0\n\t"
		       "fdivd d1,d1,%P2\n\t"
		       "fdivd d0,d0,%P2\n\t"
		       "fdivd d2,d2,%P1\n\t"
		       "fdivd d1,d1,%P0\n\t"
		       "fdivd d0,d0,%P2\n\t"
		       :: "w" (a), "w" (b), "w" (c) : "d0", "d1", "d2", "memory");
#elif (defined __amd64__ || defined __i386__) && !defined NO_ASM
	  asm volatile("divsd %0,%%xmm0\n\t"
		       "divsd %1,%%xmm1\n\t"
		       "divsd %2,%%xmm2\n\t"
		       "divsd %1,%%xmm0\n\t"
		       "divsd %0,%%xmm2\n\t"
		       "divsd %2,%%xmm1\n\t"
		       "divsd %2,%%xmm0\n\t"
		       "divsd %1,%%xmm2\n\t"
		       "divsd %0,%%xmm1\n\t"
		       "divsd %2,%%xmm0\n\t"
		       :: "x" (a), "x" (b), "x" (c) : "xmm0", "xmm1", "xmm2", "memory");
#else
	r1 = a/b;
	r2 = b/c;
	r3 = a/c;
	r4 = b/a;
	r5 = c/a;
	r6 = c/b;
	r7 = a/a;
	r8 = b/b;
	r9 = c/c;
	r10 = r10/a;
#endif
      }
      clock_gettime(CLOCK, &end);
      
      elapsed_time_hr(start, end, "Double Division - 10 ops");

      break;
    }
    default: printf("Only possible operation choices are '+', '-', '*' and '/'.\n");
  }
  
  return 0;
  
}
