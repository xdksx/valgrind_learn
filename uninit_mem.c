//使用了未初始化内存时，如下的s 
//编译程序:gcc -o uninit_mem uninit_mem.c -g
//valgrind --tool=memcheck --leak-check=full  ./uninit_men
//进程号　　说明信息
/*==3964== Memcheck, a memory error detector
==3964== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==3964== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==3964== Command: ./uninit_mem
==3964== 
==3964== Conditional jump or move depends on uninitialised value(s)　//说明条件跳转依赖的是为初始化的值
==3964==    at 0x4005D3: main (uninit_mem.c:10)　　//指定程序的第几行出现问题
==3964== 
==3964== 
==3964== HEAP SUMMARY:　　//堆情况
==3964==     in use at exit: 0 bytes in 0 blocks
==3964==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==3964== 
==3964== All heap blocks were freed -- no leaks are possible
==3964== 
==3964== For counts of detected and suppressed errors, rerun with: -v
==3964== Use --track-origins=yes to see where uninitialised values come from
==3964== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/

#include<stdio.h>
int main()
{
	int a[5];
	int i,s;
	a[0]=a[1]=a[2]=a[3]=a[4]=0;
	//s=0;
//	for(i=0;i<5;i++)
//	   s+=a[i];
	if(s==366)
		printf("sum is %d\n",s);
	return 0;
}
