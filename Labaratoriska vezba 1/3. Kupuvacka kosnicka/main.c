#include <stdio.h>

typedef struct proizvodi {
    char ime[50];
    float cena;
    float kolicina;
} products;

float suma(float kol, float cena){
    int suma;
    suma = kol*cena;
    return suma;
}


void print(char *ime, float *cena, float *kolicina, int i){
    printf("%d. %s  %.2f x %.1f = %.2f\n", i, ime, *cena, *kolicina, suma(*kolicina,*cena));
}

int main(void){
    proizvodi p[100];
    int n;
    float total=0.0;
    scanf("%d", &n);
    
    for(int i=1; i<=n; i++){
        scanf("%s", p[i].ime);
        scanf("%f", &p[i].cena);
        scanf("%f", &p[i].kolicina);
    }

    for(int i=1; i<=n; i++){
        total+=suma(p[i].kolicina,p[i].cena);
        print(p[i].ime,&p[i].cena,&p[i].kolicina,i);
    }
    printf("Total: %.2f", total);
}
