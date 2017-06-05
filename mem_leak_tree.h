#ifndef _BADLEAK_
#define _BADLEAK_
 
typedef struct _node{
	struct _node *l;
	struct _node *r;
	char v;
}node;
node *mk(node *l,node *r,char val);
void nodefr(node *n);
#endif

