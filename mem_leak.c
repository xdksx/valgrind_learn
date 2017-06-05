/*内存泄露（Memory leak）指的是，在程序中动态申请的内存，在使用完后既没有释放，
 * 又无法被程序的其他部分访问。内存泄露是在开发大型程序中最令人头疼的问题，以至于有人说，
 * 内存泄露是无法避免的。其实不然，防止内存泄露要从良好的编程习惯做起，
 * 另外重要的一点就是要加强单元测试（Unit Test），而memcheck就是这样一款优秀的工具。

下面是一个比较典型的内存泄露案例。main函数调用了mk函数生成树结点，
* 可是在调用完成之后，却没有相应的函数：nodefr释放内存，
* 这样内存中的这个树结构就无法被其他部分访问，造成了内存泄露。

在一个单独的函数中，每个人的内存泄露意识都是比较强的。但很多情况下，
* 我们都会对malloc/free 或new/delete做一些包装，以符合我们特定的需要，
* 无法做到在一个函数中既使用又释放。这个例子也说明了内存泄露最容易发生的地方：
* 即两个部分的接口部分，一个函数申请内存，一个函数释放内存。并且这些函数由不同的人开发、
* 使用，这样造成内存泄露的可能性就比较大了。这需要养成良好的单元测试习惯，将内存泄露消灭在初始阶段。
*/
/*编译等：ksx@ksx-Inspiron-3537:~/workspace/valgrind$ gcc -Wall -o mem_leak mem_leak.c mem_leak_tree.c -g
mem_leak.c: In function ‘main’:
mem_leak.c:6:22: warning: variable ‘tree3’ set but not used [-Wunused-but-set-variable]
  node *tree1,*tree2,*tree3;
                      ^
ksx@ksx-Inspiron-3537:~/workspace/valgrind$ valgrind --tool=memcheck --leak-check=full ./mem_leak 
*/
/*结果：
 * ==10112== Memcheck, a memory error detector
==10112== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==10112== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==10112== Command: ./mem_leak
==10112== 
==10112== 
==10112== HEAP SUMMARY:
==10112==     in use at exit: 192 bytes in 8 blocks
==10112==   total heap usage: 8 allocs, 0 frees, 192 bytes allocated
==10112== 
==10112== 192 (24 direct, 168 indirect) bytes in 1 blocks are definitely lost in loss record 8 of 8
==10112==    at 0x4C2DB8F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==10112==    by 0x400639: mk (mem_leak_tree.c:5)
==10112==    by 0x40060F: main (mem_leak.c:9)
==10112== 
==10112== LEAK SUMMARY:
==10112==    definitely lost: 24 bytes in 1 blocks
==10112==    indirectly lost: 168 bytes in 7 blocks
==10112==      possibly lost: 0 bytes in 0 blocks
==10112==    still reachable: 0 bytes in 0 blocks
==10112==         suppressed: 0 bytes in 0 blocks
==10112== 
==10112== For counts of detected and suppressed errors, rerun with: -v
==10112== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/
/*该示例程序是生成一棵树的过程，每个树节点的大小为12（考虑内存对齐），
 * 共8个节点。从上述输出可以看出，所有的内存泄露都被发现。
 * Memcheck将内存泄露分为两种，一种是可能的内存泄露（Possibly lost），
 * 另外一种是确定的内存泄露（Definitely lost）。
 * Possibly lost 是指仍然存在某个指针能够访问某块内存，但该指针指向的已经不是该内存首地址。
 * Definitely lost 是指已经不能够访问这块内存。
 * 而Definitely lost又分为两种：直接的（direct）和间接的（indirect）。
 * 直接和间接的区别就是，直接是没有任何指针指向该内存，间接是指指向该内存的指针都位于内存泄露处。
 * 在上述的例子中，根节点是directly lost，而其他节点是indirectly lost。*/


#include<stdio.h>
#include<stdlib.h>
#include "mem_leak_tree.h"
int main()
{
	node *tree1,*tree2,*tree3;
	tree1=mk(mk(mk(0,0,'3'),0,'2'),0,'1');
	tree2=mk(0,mk(0,mk(0,0,'6'),'5'),'4');
	tree3=mk(mk(tree1,tree2,'8'),0,'7');
	return 0;
}

