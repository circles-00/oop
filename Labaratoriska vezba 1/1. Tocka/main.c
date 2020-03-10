#include <stdio.h>
#include <math.h>

typedef struct tocka2D{
    float x, y;
} tocka2D;

typedef struct tocka3D{
    float x, y, z;
} tocka3D;

float rastojanie(tocka2D a, tocka2D b){
    float base, distance;
    base=((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y));
    distance=sqrt(base);
    return distance;
}

float rastojanie3D(tocka3D a, tocka3D b){
    float base, distance;
    base=((b.x-a.x)*(b.x-a.x))+((b.y-a.y)*(b.y-a.y)+((b.z-a.z)*(b.z-a.z)));
    distance=sqrt(base);
    return distance;
}

/* We use triangle's area to determine whether the points lay on the same line, if the area is 0, they lay on the same line, otherwise, they don't  */
int ista_prava(tocka2D a, tocka2D b, tocka2D c){
    float area;
    area = (a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))/2;
    if(area==0.0)
        return 1;
    else
        return 0;
}

int main(void) {
    float x1, y1, x2, y2;

    scanf("%f %f", &x1, &y1);
    scanf("%f %f", &x2, &y2);
	
    tocka2D t1 = { x1, y1 };
    tocka2D t2 = { x2, y2 };
    printf("%.2f\n", rastojanie(t1, t2));
    
    float z1, z2;
    scanf("%f %f", &z1, &z2);
    tocka3D t3 = {x1, y1, z1};
    tocka3D t4 = {x2, y2, z2};
    printf("%.2f\n", rastojanie3D(t3, t4));
    
    tocka2D t5 = {z1, z2};
    printf("%d\n", ista_prava(t1, t2, t5));
}
