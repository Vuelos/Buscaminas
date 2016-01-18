#include <stdlib.h>
#include <stdio.h>

class buscaminas{
    public: 
        buscaminas(int, int, int); // x, y, minas
        bool Es_libre(int, int); // x , y
        bool Es_mina(int, int); // x , y
        void Mostrar();
    private:
        void Mostrar_ceros(int,int);
        int campo[100][100]; //maximo de ancho y alto
        bool visible [100][100]; //parte del campo que se muestra
        int minas;
        int ancho, alto;
        int x, y;
        int i, j, l, k;
        int numero;
        int cx, cy, lim_x, lim_y;
};
void buscaminas::Mostrar(){
    printf("\n");
    for(i=0;i<ancho;i++){
        printf("\n");
        for(j=0;j<alto;j++){
            if (visible[i][j] == true) printf(" %d",campo[i][j]);
            else printf(" X");
        }
    }
}
bool buscaminas::Es_mina(int x, int y){
    if (campo[x][y] == 9) {
        visible[x][y] = true;
        return true;
    } else return false;
}

bool buscaminas::Es_libre(int x, int y){
    if (campo[x][y] != 9) {
        Mostrar_ceros(x,y); 
        return true;
    } else return false;
}

void buscaminas::Mostrar_ceros (int x , int y){
    visible[x][y] = true;
    if (campo[x][y] == 0) {
        //muestro todos los adyacentes
        cx = cy = -1;      //busco desde
        lim_x = lim_y = 1; // hasta
                
        if (x == 0) cx = 0;             //no izq
        if (x == ancho - 1) lim_x = 0;  //no der
        if (y == 0) cy = 0;             //no top
        if (y == alto - 1) lim_y = 0;   //no bot
        
        for(l=cx; l<=lim_x; l++){
            for(k=cy; k<=lim_y;k++){
                if ((l != 0 || k != 0) && visible[x+l][y+k] == false){
                    Mostrar_ceros(x + l, y + k);
                }
            }
        }
    }   
}

buscaminas::buscaminas(int x,int y,int m){
    
    minas = m;
    alto = y;
    ancho = x;
    //limpio
    for(i=0;i<ancho;i++){
        for(j=0;j<alto;j++){
          campo[i][j]  = 0;
        }
    }
    //reparto las minas        
    while (minas > 0){
        x = rand() % ancho;
        y = rand() % alto;
        if (campo[x][y] != 9){  /*9 para las minas*/
            campo[x][y] = 9;
            minas--;
        }
    }

    printf("minas colocadas\n");
    
    //pongo los numeros
    for(i=0; i<ancho; i++){
        for(j=0; j<alto; j++){
            if (campo [i][j] != 9){
                
                //veo adonde buscar
                cx = cy = -1;      //busco desde
                lim_x = lim_y = 1; // hasta
                
                if (i == 0) cx = 0;             //no izq
                if (i == ancho - 1) lim_x = 0;  //no der
                if (j == 0) cy = 0;             //no top
                if (j == alto - 1) lim_y = 0;   //no bot

                numero = 0;
                //busco
                for(l=cx; l<=lim_x; l++){
                    for(k=cy; k<=lim_y;k++){
                        if (l != 0 || k != 0){
                            if (campo [i + l][j + k] == 9) numero++;
                        }
                    }
                }
                campo [i][j] = numero;
            }    
        }
    }
    printf("numeros asignados\n");
}
int main()
{
    int ingreso, x, y;
    printf("Buscaminas!\n");
    buscaminas b(20,20,20);
    while(1){
        b.Mostrar();
        printf("\n Que haces? \n 1 - es mina || 2 - es libre\n");
        scanf("%d",&ingreso);
        switch(ingreso){
            case 1: 
                    printf("\nIngresar alto y ancho\n");
                    scanf("%d",&y);
                    printf("\n");
                    scanf("%d",&x);
                    b.Es_mina(x,y);
                    break;
            case 2:
                    printf("\nIngresar alto y ancho\n");
                    scanf("%d",&y);
                    printf("\n");
                    scanf("%d",&x);
                    b.Es_libre(x,y);
                    break;
        }
    }
    return 0;
}
