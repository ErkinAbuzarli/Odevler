#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_table(int** table, int widht, int height);
void print_table(int** table, int widht, int height);
void remove_row(int** table, int widht, int height, int row);
void remove_column(int** table, int widht, int height, int column);
void rota_alg(int** table, int widht, int height);

int kapsayan_sutun(int** table, int widht, int height);
int kapsayan_satir(int** table, int widht, int height);
int agirlik(int** table,int column, int widht, int height);
int mutlak_satir(int** table, int widht, int height);
int mutlak_satir_islemleri(int** table, int widht, int height);
int bittimi(int** table, int widht, int height);
int min_agirlik(int** table, int widht, int height);
int bos_sutun(int** table, int widht, int height, int column);
int bos_satir(int** table, int widht, int height, int row);


float satir_agirlik(int** table, int widht, int height, int row);


int main()
{
    int widht = 0, height = 0, yanit = 0, temp = 0, count = 0, sayi = 0, n_t;
    int **table;

    while(widht < 6 || height < 6){
        printf("Tablo degerlerini giriniz.(min 6)\n");

        printf("Tablo Uzunlugu: ");
        scanf("%d", &widht);

        printf("Tablo Eni: ");
        scanf("%d", &height);
    }

    int min_kapsama[height];
    for(int i = 0; i < height;i++) min_kapsama[i] = -1;

    table = malloc(height * sizeof *table);
    for (int i = 0; i < height; i++)
        table[i] = malloc(widht * sizeof *table[i]);

    for (int i = 0; i < height; i++)
            for (int j = 0; j < widht; j++)
                *(table + i*widht + j) = 0;

    printf("\n\nDegerler nasil girilsin?\n1.Manuel\n2.Random\n\nYanit: ");
    scanf("%d", &yanit);


    if(yanit == 1)
    {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < widht; j++){
                printf("%c,%d: ", i+97,j+1);
                scanf("%d", &temp);
                *(table + i*widht + j) = (temp) ? 1 : 0;
            }
        printf("\n\n\n\n\nGirilen Tablo:\n\n");
        print_table(table, widht, height);
    }
    else
    {
        random_table(table, widht, height);
        printf("\n\n\n\n\nGirilen Tablo:\n\n");
        print_table(table, widht, height);
    }

    while(bittimi(table, widht, height) == -1){

        temp = -1;
        n_t = -2;

        do{
            if(n_t != -2){
                printf("Kapsayan Sutun Bulundu Ve Silindi...\n\n");
                print_table(table, widht, height);
            }
            n_t = -1;
            while((kapsayan_satir(table, widht, height) != -1) && ((n_t = mutlak_satir_islemleri(table, widht, height)) != -1)) {

                if(temp != n_t){
                    temp = n_t;
                    min_kapsama[sayi] = temp;
                    sayi++;

                    printf("Mutlak Satir Bulundu: %c\n\nVe Gerekli Islemler Yapildi...\n", temp+97);
                    print_table(table, widht, height);
                }



            }
        }while((kapsayan_sutun(table, widht,height) != -1));


        if(bittimi(table, widht, height) == -1){
            rota_alg(table, widht, height);
            printf("Rota Algoritmasi Uygulandi...\n");
            print_table(table, widht, height);
        }
    }

    printf("Min Kapsama = ");

    for(int i = 0; i < sayi; i++)
        printf("%c ", *(min_kapsama+i) + 97);

    //change_row(table,widht,height,2,3);
    scanf("");
    free(table);
    return 0;
}







int bos_sutun(int** table, int widht, int height, int column)
{
    for (int i = 0; i < height; i++)
        if(*(table + i*widht + column) == 1 || *(table + i*widht + column) == 0) return 0;
    return 1;
}


int bos_satir(int** table, int widht, int height, int row)
{
    for (int i = 0; i < widht; i++)
        if(*(table + row*widht + i) == 1 || *(table + i*widht + row) == 0) return 0;
    return 1;
}






int bittimi(int** table, int widht, int height)
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < widht; j++)
                if(*(table + i*widht + j) != 2) return -1;

    return 1;
}




void change_row(int** table, int widht, int height, int row1, int row2)
{
    int temp = 0;
    for (int i = 0; i < widht; i++)
    {
        temp = *(table + row1*widht + i);
        *(table + row1*widht + i) = *(table + row2*widht + i);
        *(table + row2*widht + i) = temp;
    }
}






void random_table(int** table, int widht, int height)
{
    srand(time(0));
    int start_h = rand()/56;

    int start_w = rand()/12;


    for (int i = 0; i < height/2; i++){
        for(int j = 0; j < widht/2; j++){
            *(table + i*widht + j) = (i == j) ? 1 : 0;
        }
        for(int j = 0; j < widht/2; j++){
            *(table + (i+1)*widht - 1 - j) = (i == j) ? 0 : 1;
        }
    }

    for (int i = height/2; i < height; i++){
        for(int j = 0; j < widht/2; j++){
            *(table + i*widht + j + widht/2) = (i-height/2 == j) ? 1 : 0;
        }
        for(int j = 0; j < widht/2; j++){
            *(table + i*widht + widht/2 - 1 - j) = (i-height/2 == j) ? 0 : 1;
        }
    }

    if (widht % 2 == 1)
        for(int j = 0; j < height-1; j += 2)
            {
                *(table + j * widht + widht/2) = 1;
                *(table + j * widht + widht/2 + 1) = 0;
            }

    if(height % 2 == 1)
        for(int j = 0; j < widht-1; j += 2)
            {
                *(table + (height/2) * widht + j) = 1;
                *(table + (height/2) * widht + j + 1) = 0;
            }

    int chng = rand() % height;

    for(int i = 0; i < height/2; i++) change_row(table, widht, height, (chng + i)%height, (chng + i*i + 1)%height);
}







void print_table(int** table, int widht, int height)
{

    printf("   |");
    for(int i = 0; i < widht; i++) printf("%d ", i);

    printf("\n");

    printf("___|");
    for(int i = 0; i < widht; i++) printf("__");

    printf("\n");

    for(int i = 0; i < height; i++){
        printf("%c  |", 97+i);

        for(int j = 0; j < widht; j++){
            *(table + i*widht + j) == 2 ? printf("- ") : printf("%d ", *(table + i*widht + j));
        }
        printf("\n");
    }
    printf("\n");

}



int agirlik(int** table, int column, int widht, int height)
{
    int count = 0;

    for(int i = 0; i < height; i++)
        if(*(table + i*widht  + column) == 1) count++;

    return count;
}


int mutlak_satir(int** table, int widht, int height)
{
    for(int i = 0; i < widht;i++)
        if(agirlik(table,i, widht, height) == 1)
            for (int j = 0; j < height; j++)
                if(*(table + j*widht + i) == 1) return j;

    return -1;
}


int mutlak_satir_islemleri(int** table, int widht, int height)
{
    int row = mutlak_satir(table, widht, height);
    if(row == -1) return -1;
    for(int i = 0; i < widht;i++)
        if(*(table + row*widht + i) == 1) remove_column(table, widht, height, i);

    remove_row(table, widht, height, row);
    return row;
}


void remove_column(int** table, int widht, int height, int column)
{
    for(int i = 0; i<height; i++)
        *(table + i*widht + column) = 2;
}


void remove_row(int** table, int widht, int height, int row)
{
    for(int i = 0; i<widht; i++)
        *(table + row*widht + i) = 2;
}


int kapsayan_satir(int** table, int widht, int height)
{
    int kapsama = 1, rt = -1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            kapsama = 1;
            if(i == j) j++;
            for (int k = 0; k < widht; k++)
            {
                 if(*(table + i*widht + k) != *(table + j*widht + k) && *(table + i*widht + k) == 1){ kapsama = 0; break; }
            }

            if(kapsama == 1 && bos_satir(table, widht, height, i) == 0) { remove_row(table, widht, height, i); rt = 1; }
        }
    }

    return rt;
}


int kapsayan_sutun(int** table, int widht, int height)
{
    int kapsama = 1, rt = -1;

    for (int i = 0; i < widht; i++)
    {
        for (int j = 0; j < widht; j++)
        {
            kapsama = 1;
            if(i == j) j++;
            for (int k = 0; k < height; k++)
            {
                 if(*(table + k*widht + i) != *(table + k*widht + j) && *(table + k*widht + i) == 0){ kapsama = 0; break; }
            }

            if(kapsama == 1 && bos_sutun(table, widht, height, i) == 0) { remove_column(table, widht, height, i); rt = 1;}

        }
    }

    return rt;
}



int min_agirlik(int** table, int widht, int height)
{
    int min = 10000;

    for(int i = 0; i < widht;i++)
        if(agirlik(table,i, widht, height) < min && agirlik(table,i, widht, height) != 0) min = agirlik(table,i, widht, height);

    return min;
}





float satir_agirlik(int** table, int widht, int height, int row)
{
    float toplam = 0;

    for (int i = 0; i < widht; i++)
        if(*(table + row*widht + i) == 1) toplam += (float)(1/(float)agirlik(table, i, widht, height));

    return (float)height * toplam;
}




void rota_alg(int** table, int widht, int height)
{
    int ans = -1;
    float minim = 10000.00000;


         int min = min_agirlik(table, widht, height);

        int satirlar[height];

        for(int i = 0; i < height;i++) satirlar[i] = 0;

        for(int i = 0; i < widht;i++)
            if(agirlik(table,i, widht, height) == min)
                for (int j = 0; j < height; j++)
                    if(*(table + j*widht + i) == 1) satirlar[j] = 1;



        for (int i = 0; i < height; i++)
            if(satirlar[i] == 1 && satir_agirlik(table, widht, height, i) < minim ){ minim = satir_agirlik(table, widht, height, i); ans = i; }

        if(ans != -1) remove_row(table, widht, height, ans);

}
 

