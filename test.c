#include "applyxn.h"
#include <stdio.h>

#define A(T,N,AdditionalArgs,item) \
	C(T,N,AdditionalArgs,item); 

int main() {
	APPLYXn(A, (1,2,3), 'a', 'b', 'c', 'd', 'e', 'f')
	APPLYXn(A, (), 'a', 'b', 'c', 'd', 'e', 'f')
	APPLYXn(A, 1, 'a', 'b', 'c', 'd', 'e', 'f')
	APPLYXn(A, , 'a', 'b', 'c', 'd', 'e', 'f')
	return 0;	
}
