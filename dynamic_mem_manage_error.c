/*常见的内存分配方式分三种：静态存储，栈上分配，堆上分配。
 * 全局变量属于静态存储，它们是在编译时就被分配了存储空间，
 * 函数内的局部变量属于栈上分配，而最灵活的内存使用方式当属堆上分配，
 * 也叫做内存动态分配了。常用的内存动态分配函数包括：malloc, alloc, realloc, new等，
 * 动态释放函数包括free, delete。

一旦成功申请了动态内存，我们就需要自己对其进行内存管理，
* 而这又是最容易犯错误的。下面的一段程序，就包括了内存动态管理中常见的错误。
* */
/*常见的内存动态管理错误包括：

     
        申请和释放不一致

由于 C++ 兼容 C，而 C 与 C++ 的内存申请和释放函数是不同的，
* 因此在 C++ 程序中，就有两套动态内存管理函数。一条不变的规则就是
* 采用 C 方式申请的内存就用 C 方式释放；用 C++ 方式申请的内存，
* 用 C++ 方式释放。也就是用 malloc/alloc/realloc 方式申请的内存，
* 用 free 释放；用 new 方式申请的内存用 delete 释放。在上述程序中，
* 用 malloc 方式申请了内存却用 delete 来释放，虽然这在很多情况下不会有问题，但这绝对是潜在的问题。

     
        申请和释放不匹配

申请了多少内存，在使用完成后就要释放多少。如果没有释放，
* 或者少释放了就是内存泄露；多释放了也会产生问题。上述程序中，
* 指针p和pt指向的是同一块内存，却被先后释放两次。

     
        释放后仍然读写

本质上说，系统会在堆上维护一个动态内存链表，如果被释放，
* 就意味着该块内存可以继续被分配给其他部分，如果内存被释放后再访问，
* 就可能覆盖其他部分的信息，这是一种严重的错误，上述程序第16行中就在释放后仍然写这块内存。

结果分析：

假设这个文件名为badmac.cpp，生成的可执行程序为badmac，用memcheck对其进行测试，输出如下。*/
/*
 *  gcc -Wall -o dynamic_mem_manage_error dynamic_mem_manage_error.c -g
ksx@ksx-Inspiron-3537:~/workspace/valgrind$ valgrind --tool=memcheck --leak-check=full ./dynamic_mem_manage_error 
*/
/*
 * ==8978== Memcheck, a memory error detector
==8978== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==8978== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==8978== Command: ./dynamic_mem_manage_error
==8978== 
==8978== 
==8978== HEAP SUMMARY:
==8978==     in use at exit: 10 bytes in 1 blocks
==8978==   total heap usage: 1 allocs, 0 frees, 10 bytes allocated
==8978== 
==8978== 10 bytes in 1 blocks are definitely lost in loss record 1 of 1
==8978==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==8978==    by 0x400537: main (dynamic_mem_manage_error.c:6)
==8978== 
==8978== LEAK SUMMARY:
==8978==    definitely lost: 10 bytes in 1 blocks
==8978==    indirectly lost: 0 bytes in 0 blocks
==8978==      possibly lost: 0 bytes in 0 blocks
==8978==    still reachable: 0 bytes in 0 blocks
==8978==         suppressed: 0 bytes in 0 blocks
==8978== 
==8978== For counts of detected and suppressed errors, rerun with: -v
==8978== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/


#include<stdlib.h>
#include<stdio.h>
int main()
{
	int i;
	char *p=(char*)malloc(10);
	char *pt=p;
	for(i=0;i<10;i++)
	{
		p[i]='z';
	}
	//delete p;
	pt[1]='x';
	//free(pt);
	return 0;
}
