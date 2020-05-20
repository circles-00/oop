#include <stdio.h>

typedef struct SkiLift {
    char name[15];
    int maxUsers;
    int isInFunction;
}SkiLift;

typedef struct SkiCenter {
    char name[20];
    char country[20];
    SkiLift array[20];
    int noOfSkiLifts;
} SkiCenter;

int kapacitet(SkiCenter sc){
    int max = 0;
    int i;
    for(i=0; i<sc.noOfSkiLifts; i++){
        if(sc.array[i].isInFunction)
            max+=sc.array[i].maxUsers;
    }
    return max;
}

int compare(SkiCenter left, SkiCenter right){
    if(kapacitet(right)>kapacitet(left))
        return 1;
    else if(kapacitet(right)==kapacitet(left))
        return 0;
    else
        return -1;
}

void najgolemKapacitet(SkiCenter *st, int n){
    int i;
    int max=0;
    for(i=1; i<n; i++){
        if(compare(st[i],st[max])==-1)
            max=i;
        else if(compare(st[i], st[max])==0)
            if(st[i].noOfSkiLifts>st[max].noOfSkiLifts)
                max=i;
    }
    printf("%s\n%s\n%d", st[max].name, st[max].country, kapacitet(st[max]));
}   

int main(void){
    SkiCenter st[100];
    int n, i, j;
    scanf("%d", &n);
	for (i = 0; i < n; i++){
        scanf("%s", st[i].name);
        scanf("%s", st[i].country);
        scanf("%d", &st[i].noOfSkiLifts);
        
		for(j=0; j<st[i].noOfSkiLifts; j++){
            scanf("%s", st[i].array[j].name);
            scanf("%d", &st[i].array[j].maxUsers);
            scanf("%d", &st[i].array[j].isInFunction);
        }
	}
	
    //povik na funkcijata najgolemKapacitet
    najgolemKapacitet(st,n);

}