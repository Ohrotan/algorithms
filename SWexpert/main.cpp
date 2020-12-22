#define DEBUG 1 
#pragma warning(disable:4996)
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "solution.h"

#if DEBUG
#define mlog(s,a){printf("%s: %d\n",s,a);}
#define input(){freopen("input.txt", "r", stdin);}
#else
#define mlog(s,a){}
#define input(){}
#endif
#define nn(){printf("\n");}
#define line(){printf("-----------------\n");}
using namespace std;

int main(void) {

	sol();
	
	return 0;
}