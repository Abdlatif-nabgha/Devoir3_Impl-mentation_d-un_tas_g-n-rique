#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void tas(int tab[],int taille,int i) {
		int index=i;
		int g=2*i+1;
		int d=2*i+2;
		if(g<taille && tab[g]>tab[index]) index=g;
		if(d<taille && tab[d]>tab[index]) index=d;
		if(index!=i) {
			int temp = tab[i];
			tab[i]=tab[index];
			tab[index]=temp;
			tas(tab,taille,index);
        }
}
void tri_tas(int tab[],int taille){
		for(int i=(taille/2)-1;i>=0;i--) {
			tas(tab,taille,i);
		}
		for(int i=taille-1;i>0;i--) {
			int temp = tab[i];
			tab[i]=tab[0];
			tab[0]=temp;
			tas(tab,i,0);
		}
	}

int main() {

    int tab[]= {2,5,5,8,8,1,4,6};
    int n=8;
	tri_tas(tab,n);
    for(int i=0;i<n;i++) {
			printf("%d ",tab[i]);
	}
    return 0;       
}