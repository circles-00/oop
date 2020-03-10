#include <stdio.h>

 typedef struct products {
    char name[50];
    float price;
    float quantity;
} products;


float subTotal(float quantity, float price){
    int subTotal;
    subTotal = quantity*price;
    return subTotal;
}


void print(char *name, float *price, float *quantity, int i){
    printf("%d. %s	%.2f x %.1f = %.2f\n", i, name, *price, *quantity, subTotal(*quantity,*price));
}

int main(void){
    products p[100];
    int n;
    float total=0.0;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++){
        scanf("%s", p[i].name);
        scanf("%f", &p[i].price);
        scanf("%f", &p[i].quantity);
    }

    for(int i=1; i<=n; i++){
        total+=subTotal(p[i].quantity,p[i].price);
        print(p[i].name,&p[i].price,&p[i].quantity,i);
    }
    printf("Total: %.2f", total);
}
