//内存读写越界
/*编译与运行：
 * gcc -o read_mem_outofrange read_mem_outofrange.c  -g
　　valgrind --tool=memcheck --leak-check=full ./read_mem_outofrange 
*/
/*结果分析：
 * 进程号　　　　说明
 * ==5165== Memcheck, a memory error detector
==5165== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==5165== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==5165== Command: ./read_mem_outofrange
==5165== 
==5165== Invalid write of size 4　　　//无效写（非法）
==5165==    at 0x4005B0: main (read_mem_outofrange.c:13) //位置
==5165==  Address 0x5203050 is 0 bytes after a block of size 16 alloc'd
==5165==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==5165==    by 0x400585: main (read_mem_outofrange.c:7)
==5165== 
==5165== Invalid read of size 4   //读无效
==5165==    at 0x4005BA: main (read_mem_outofrange.c:14)
==5165==  Address 0x5203050 is 0 bytes after a block of size 16 alloc'd
==5165==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==5165==    by 0x400585: main (read_mem_outofrange.c:7)
==5165== 
the value of p is:5==5165== 
==5165== HEAP SUMMARY:
==5165==     in use at exit: 16 bytes in 1 blocks　
==5165==   total heap usage: 2 allocs, 1 frees, 1,040 bytes allocated
==5165== 
==5165== 16 bytes in 1 blocks are definitely lost in loss record 1 of 1
==5165==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==5165==    by 0x400585: main (read_mem_outofrange.c:7)
==5165== 
==5165== LEAK SUMMARY:
==5165==    definitely lost: 16 bytes in 1 blocks
==5165==    indirectly lost: 0 bytes in 0 blocks
==5165==      possibly lost: 0 bytes in 0 blocks
==5165==    still reachable: 0 bytes in 0 blocks
==5165==         suppressed: 0 bytes in 0 blocks
==5165== 
==5165== For counts of detected and suppressed errors, rerun with: -v
==5165== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int len=4;
	int *pt=(int*)malloc(len*sizeof(int));　　//行7
	int *p=pt;
	for(int i=0;i<len;i++)
	{
		p++;
	}
	*p=5;　　　//行　13
	printf("the value of p is:%d",*p);
	return 0;
}
