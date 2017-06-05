//内存覆盖的问题：
/*
 * C 语言的强大和可怕之处在于其可以直接操作内存，C 标准库中提供了大量这样的函数，比如 strcpy, strncpy,
 *  memcpy, strcat 等，这些函数有一个共同的特点就是需要设置源地址 (src)，和目标地址(dst)，src 和 dst 
 * 指向的地址不能发生重叠，否则结果将不可预期。
下面就是一个 src 和 dst 发生重叠的例子。
* 在 15 与 17 行中，src 和 dst 所指向的地址相差 20，但指定的拷贝长度却是 21，这样就会把之前的拷贝值覆盖。
* 第 24 行程序类似，src(x+20) 与 dst(x) 所指向的地址相差 20，但 dst 的长度却为 21，这样也会发生内存覆盖。
*/
//编译：
/* gcc -Wall -o mem_overlap mem_overlap.c -g
valgrind --tool=memcheck --leak-check=full ./mem_overlap 
*/
/*结果：
 * ==8230== Memcheck, a memory error detector
==8230== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==8230== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==8230== Command: ./mem_overlap
==8230== 
==8230== Conditional jump or move depends on uninitialised value(s)
==8230==    at 0x4C315A5: __strncpy_sse2_unaligned (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==8230==    by 0x40062C: main (mem_overlap.c:13)
==8230== 
==8230== Conditional jump or move depends on uninitialised value(s)
==8230==    at 0x4C315A5: __strncpy_sse2_unaligned (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==8230==    by 0x400648: main (mem_overlap.c:14)
==8230== 
==8230== Source and destination overlap in strncpy(0xffefffaa5, 0xffefffab9, 21)  //这里
==8230==    at 0x4C31626: __strncpy_sse2_unaligned (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==8230==    by 0x400680: main (mem_overlap.c:16)
==8230== 
==8230== 
==8230== HEAP SUMMARY:
==8230==     in use at exit: 0 bytes in 0 blocks
==8230==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==8230== 
==8230== All heap blocks were freed -- no leaks are possible
==8230== 
==8230== For counts of detected and suppressed errors, rerun with: -v
==8230== Use --track-origins=yes to see where uninitialised values come from
==8230== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char x[50];
	int i;
	for(i=0;i<5;i++)
	{
		x[i]=i+1;
	}
	strncpy(x+20,x,20);// ok
	strncpy(x+20,x,21);//overlap
	strncpy(x,x+20,20);//ok
	strncpy(x,x+20,21);//overlap
        x[39]='\0';
	strcpy(x,x+20);//ok
	x[39]=39;
	x[40]='\0';
	strcpy(x,x+20); //overlap
	return 0;
}
