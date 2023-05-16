#define max 1024
#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,v[max];
    scanf("%d",&n);
    for(int i;i<n;++i){
        v[i] = i;
    }
    for(int i;i<n;++i){
        printf("v[%d] = %d\n", v[i],i);
    }
    return 0; 
}