//Amiral Batti oyunu

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ekran_goruntusu(int [][25],int); //Atislardan sonra savas alanin son halini yazdirmak icin kullanildi
char harften_rakam_yap(char); //ASCII standartlarina gore harfi rakama cevirir
int rakamdan_harf_yap (int); //ASCII standartlarina gore rakami harfe cevirir
void gemi_yerlestir(int [][25],int,int,int,int *); //Savas alanin disina tasmadan ve cakisma olmadan gemilerin rastgele yerlestirilmesini saglar
void atis(int [][25],int,int,int *,int [],int,int,int *); //Atis yapilan koordinatlar icin gemilerin vurulup vurulmadigini kontrol eder
int gemi_kontrol(int [][25],int [],int,int,int [],int); //Vurulan gemilerin batip batmadigini kontrol eder

int main()
{
  system("color 3f"); //Arkaplan rengi

  int N,x,y,i,j,atis_hakki,batik_gemi_sayisi=0;
  int oyun_alani[25][25]={{0}};
  int gemiler[48]={0};
  int isabet[12]={0};
  int gemi_uzunluk,gemi_uzunluk_top=0;
  char sutun;

  //Kullanicidan savas alanin bir kenarinin uzunlugu alinip kontrolu yapiliyor
  do{

     printf(" Oynamak istediginiz savas alanin bir kenarinin uzunlugunu giriniz: ");
     scanf("%d",&N);
     printf("\n");

    }while(N%2!=0 || N>24 || N<4 );

      //Yerlestirilecek gemi sayisi kadar donen bu dongu icerisinde gemilerin uzunluklari kullanicidan alinip savas alanina yerlestiriliyor
      for(i=0;i<N/2;i++)
      {
            do{
                switch(i)
                {
                    case 0:
                        printf(" Ucak gemisinin uzunlugunu giriniz: ");
                        fflush(stdin);
                        scanf("%d",&gemi_uzunluk);break;

                    case 1:
                        printf(" Kruvazor geminin uzunlugunu giriniz: ");
                        fflush(stdin);
                        scanf("%d",&gemi_uzunluk);break;

                    case 2:
                        printf(" Denizaltinin uzunlugunu giriniz: ");
                        fflush(stdin);
                        scanf("%d",&gemi_uzunluk);break;

                    case 3:
                        printf(" Muhrip geminin uzunlugunu giriniz: ");
                        fflush(stdin);
                        scanf("%d",&gemi_uzunluk);break;

                    case 4:
                        printf(" Firkateyn gemisinin uzunlugunu giriniz: ");
                        fflush(stdin);
                        scanf("%d",&gemi_uzunluk);break;

                    default:
                        printf(" %d. geminin uzunlugunu giriniz: ",i+1);
                        fflush(stdin);
                        scanf("%d",&gemi_uzunluk);break;
                }

                    if(gemi_uzunluk>=2 && gemi_uzunluk<=N/2+1){
                        gemiler[i*4]=gemi_uzunluk;
                        gemi_yerlestir(oyun_alani,gemi_uzunluk,N,i*4,gemiler);
                        gemi_uzunluk_top=gemi_uzunluk_top+gemi_uzunluk;
                    }
             }while(gemi_uzunluk<2 || gemi_uzunluk>N/2+1); //Gemi uzunluklarinin kontrolu

             atis_hakki=N*N-gemi_uzunluk_top; //Toplam atis hakki hesaplaniyor

      }


  //Yerlestirilen gemileri gormek icin savas alanini yazdiran donguler (hile)

 /*printf("\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d",oyun_alani[i][j]);
        }
        printf("\n");
    }*/

        printf("---------------------------------------\n");
        printf("Toplam atis yapma hakkiniz: %d\n",atis_hakki);
        printf("Oyuna baslamak icin bir tusa basiniz...");
        getche();
        system("cls"); //Ekrani temizleyen komut

  printf("\n\n\n\n\n   ");

        for(i=0;i<N;i++)
        {
            printf(" %c",rakamdan_harf_yap(i));
        }

  printf("\n\n");

        for(i=0;i<N;i++)
        {
            if((i+1)<10)
            {
                printf(" %d ",i+1);
            }
            else
            {
                printf("%d ",i+1);
            }


            for(j=0;j<N;j++)
            {
                printf(" *");
            }
            printf("\n");
        }

       //Atis hakki kadar kullanicidan koordinatlar isteniyor ve kontrolu yapiliyor
       for(i=0;i<N*N-gemi_uzunluk_top;i++)
       {
         do{

             printf("\n Atis yapmak istediginiz koordinatlari satir ve sutun sirasiyla giriniz: ");
             scanf("%d%c",&x,&sutun);
             y=harften_rakam_yap(sutun);

           }while(x<1 || x>N || y<0 || y>N);

         atis_hakki--;
         atis(oyun_alani,x-1,y,gemiler,isabet,N,atis_hakki,&batik_gemi_sayisi);


        if(atis_hakki==0) //Kullanicinin atis hakki dolduysa
        {
            system("cls");
            printf("\nAtis hakkiniz bitti. Malesef Oyunu kaybettiniz :(\n");
            printf("Savas alaninin son hali:");
            ekran_goruntusu(oyun_alani,N);
            break;
        }
        if(batik_gemi_sayisi==N/2) //Butun gemiler batirildiysa
        {
            system("cls");
            printf("\nTebrikler! %d atista oyunu kazandiniz!\n",N*N-gemi_uzunluk_top-atis_hakki);
            printf("Savas alaninin son hali:");
            ekran_goruntusu(oyun_alani,N);
            break;
        }

        ekran_goruntusu(oyun_alani,N);
        }

return 0;
}

int rakamdan_harf_yap (int rakam)
{
    rakam=rakam + 65;
    if (rakam > 90) {
        rakam=rakam%65;
    }

    return rakam;
}

char harften_rakam_yap(char harf)
{
    harf=harf%65;

    return harf;
}

void ekran_goruntusu(int oyun_alani[][25],int N)
{
    int i,j;
    printf("\n\n   ");

        for(i=0;i<N;i++)
        {
            printf(" %c",rakamdan_harf_yap(i));
        }

        printf("\n\n");

        for(i=0;i<N;i++)
        {
            if((i+1)<10)
            {
                printf(" %d ",i+1);
            }
            else
            {
                printf("%d ",i+1);
            }

            //Bu dongude isabetli, karavana atislar ve batan gemiler belirlenip ilgili harf karsiliklari ekrana yazdiriliyor
            for(j=0;j<N;j++)
            {
                if(oyun_alani[i][j]==0 || oyun_alani[i][j]==1)
                {
                    printf(" *");
                }
                else if(oyun_alani[i][j]==2)
                {
                    printf(" K");
                }
                else if(oyun_alani[i][j]==3)
                {
                    printf(" I");
                }
                else if(oyun_alani[i][j]==4)
                {
                    printf(" B");
                }
            }
            printf("\n");
        }
}

void gemi_yerlestir(int oyun_alani[][25],int gemi_uzunluk, int N, int gemi_no, int gemiler [])
{
    int yerlesti=0,kontrol,i,j; //j, gecici koordinat degeridir
    int yon,x,y;

    while(yerlesti==0)
    {
        kontrol=0;
        j=0;

        srand(time(NULL));

        //Yon ve x, y koordinatlari icin rastgele degerler uretiliyor
        yon=rand()%4+1;
        x=rand()%N; //satir, yatay eksen
        y=rand()%N; //sutun, dusey eksen

        //Her gemi icin o gemiye ait x, y ve yon bilgileri "gemiler" dizisinde saklaniyor
        gemiler[gemi_no+1]=x;
        gemiler[gemi_no+2]=y;
        gemiler[gemi_no+3]=yon;

    switch(yon)
    {
        case 1:  //kuzey

            j=x;

            if(gemi_uzunluk<=x+1) //Geminin savas alanina sýgma kontrolu
            {
                if(oyun_alani[x-gemi_uzunluk][y]==0 && oyun_alani[x+1][y]!=1) //Baslangic noktasinin altindaki ve geminin uzunlugu kadar ustundeki noktanin kontrolu
                {
                  for(i=0;i<gemi_uzunluk;i++)
                  {
                     if(oyun_alani[j][y]!=1) //Noktanin kontrolu
                     {
                          if(oyun_alani[j][y-1]!=1 && oyun_alani[j][y+1]!=1) //Noktanin saginin ve solunun kontrolu
                          {
                                kontrol++;
                                j--;
                          }

                     }
                    }
                 }
            }

          //Gemi yerlesebiliyorsa geminin uzunluguna ve yonuna gore "oyun_alani" matrisinin ilgili elemanlarina 1 degeri ataniyor
          if(kontrol==gemi_uzunluk)
             {
                 while(gemi_uzunluk>0)
                 {
                       oyun_alani[x][y]=1;
                       gemi_uzunluk--;
                       x--;
                 }
             }
             break;


        case 2:   //guney

            j=x;

            if(x+gemi_uzunluk<=N) //Geminin savas alanina sýgma kontrolu
            {
                if(oyun_alani[x+gemi_uzunluk][y]==0 && oyun_alani[x-1][y]!=1) //Baslangic noktasinin ustundeki ve geminin uzunlugu kadar altindaki noktanin kontrolu
                 {
                  for(i=0;i<gemi_uzunluk;i++)
                   {
                     if(oyun_alani[j][y]!=1) //Noktanin kontrolu
                       {
                          if(oyun_alani[j][y-1]!=1 && oyun_alani[j][y+1]!=1) //Noktanin saginin ve solunun kontrolu
                            {
                                kontrol++;
                                j++;

                            }

                       }
                }
            }
        }

        //Gemi yerlesebiliyorsa geminin uzunluguna ve yonuna gore "oyun_alani" matrisinin ilgili elemanlarina 1 degeri ataniyor
        if(kontrol==gemi_uzunluk)
             {
                 while(gemi_uzunluk>0)
                 {
                       oyun_alani[x][y]=1;
                        gemi_uzunluk--;
                        x++;
                 }
             }
        break;


        case 3:  //dogu

            j=y;

            if(y+gemi_uzunluk<=N) //Geminin savas alanina sýgma kontrolu
            {
                if(oyun_alani[x][y+gemi_uzunluk]==0 && oyun_alani[x][y-1]!=1) //Baslangic noktasinin solundaki ve geminin uzunlugu kadar sagindaki noktanin kontrolu
                 {
                  for(i=0;i<gemi_uzunluk;i++)
                   {
                     if(oyun_alani[x][j]!=1) //Noktanin kontrolu
                       {
                          if(oyun_alani[x-1][j]!=1 && oyun_alani[x+1][j]!=1) //Noktanin ustunun ve altinin kontrolu
                            {
                               kontrol++;
                               j++;
                            }

                       }
                }
            }
        }

        //Gemi yerlesebiliyorsa geminin uzunluguna ve yonuna gore "oyun_alani" matrisinin ilgili elemanlarina 1 degeri ataniyor
        if(kontrol==gemi_uzunluk)
             {
                 while(gemi_uzunluk>0)
                 {
                       oyun_alani[x][y]=1;
                        gemi_uzunluk--;
                        y++;
                 }
             }

        break;


        case 4:  //bati

            j=y;

            if(gemi_uzunluk<=y+1) //Geminin savas alanina sýgma kontrolu
            {
                if(oyun_alani[x][y-gemi_uzunluk]==0 && oyun_alani[x][y+1]!=1) //Baslangic noktasinin sagindaki ve geminin uzunlugu kadar solundaki noktanin kontrolu
                 {
                  for(i=0;i<gemi_uzunluk;i++)
                   {
                     if(oyun_alani[x][j]!=1) //Noktanin kontrolu
                       {
                          if(oyun_alani[x-1][j]!=1 && oyun_alani[x+1][j]!=1) //Noktanin ustunun ve altinin kontrolu
                            {
                                kontrol++;
                                j--;
                            }

                       }
                }
            }
          }

      //Gemi yerlesebiliyorsa geminin uzunluguna ve yonuna gore "oyun_alani" matrisinin ilgili elemanlarina 1 degeri ataniyor
      if(kontrol==gemi_uzunluk)
         {
             while(gemi_uzunluk>0)
             {
                   oyun_alani[x][y]=1;
                    gemi_uzunluk--;
                    y--;
             }
         }

      break;
   }

        //Geminin yerlesip yerlesemedigi kontrol ediliyor
        if(gemi_uzunluk==0)
        {
           yerlesti=1;
        }

    }

}

void atis(int oyun_alani[][25],int x,int y,int gemiler [],int isabet [],int N,int atis_hakki,int *batik)
{
    system("cls");

    int kontrol;

    kontrol=oyun_alani[x][y];

    printf("------------------------------------------\n");

    switch(kontrol)
    {
        case 0:

            printf("Maalesef isabetsiz\n");
            printf("Kalan hakkiniz: %d",atis_hakki);
            oyun_alani[x][y]=2;
            break;

        case 1:

            printf("Atis basarili!\n");
            oyun_alani[x][y]=3;

            if(gemi_kontrol(oyun_alani,gemiler,x,y,isabet,N)==1)
            {
                *batik=*batik+1;
                printf("Tebrikler! Gemi batti!\n");
            }

            printf("Kalan hakkiniz: %d",atis_hakki);
            break;

        case 2:

            printf("Buraya daha once de atis yapmistiniz!\n");
            printf("Kalan hakkiniz: %d",atis_hakki);
            break;

        case 3:

            printf("Buraya zaten isabetli bir atis yapmistiniz!\n");
            printf("Kalan hakkiniz: %d",atis_hakki);
            break;

        case 4:

            printf("Bu gemiyi zaten batirmistiniz!\n");
            printf("Kalan hakkiniz : %d",atis_hakki);
            break;
    }

    printf("\n------------------------------------------");
}

int gemi_kontrol(int oyun_alani[][25],int gemiler [],int x,int y,int isabet [],int N)
{
    int i,j,k;

    for(i=0;i<12;i++)
    {

    if(isabet[i]==gemiler[i*4])
        continue;

    switch(gemiler[4*i+3])
    {
      case 1:
             j=0;
             while(j<gemiler[4*i])
             {
                 if(gemiler[4*i+1]-j==x && gemiler[4*i+2]==y){
                    isabet[i]++;
                    if(isabet[i]==gemiler[(i)*4])
                      {
                       for(k=0;k<gemiler[4*i];k++)
                          {
                              oyun_alani[gemiler[4*i+1]-k][gemiler[4*i+2]]=4;
                          }
                        return 1;
                      }
                    }
                    j++;

             }break;

      case 2:
             j=0;
             while(j<gemiler[4*i])
             {
                 if(gemiler[4*i+1]+j==x && gemiler[4*i+2]==y)
                 {
                    isabet[i]++;
                    if(isabet[i]==gemiler[(i)*4])
                      {
                       for(k=0;k<gemiler[4*i];k++)
                          {
                              oyun_alani[gemiler[4*i+1]+k][gemiler[4*i+2]]=4;
                          }
                        return 1;
                      }
                    }
                     j++;

             }break;

      case 3:
             j=0;
             while(j<gemiler[4*i])
             {
                 if(gemiler[4*i+1]==x && gemiler[4*i+2]+j==y){
                    isabet[i]++;
                    if(isabet[i]==gemiler[(i)*4])
                      {
                       for(k=0;k<gemiler[4*i];k++)
                          {
                              oyun_alani[gemiler[4*i+1]][gemiler[4*i+2]+k]=4;
                          }
                        return 1;
                      }
                    }
                    j++;

             }break;

       case 4:
             j=0;
             while(j<gemiler[4*i])
             {
                 if(gemiler[4*i+1]==x && gemiler[4*i+2]-j==y){
                    isabet[i]++;
                    if(isabet[i]==gemiler[(i)*4])
                      {
                       for(k=0;k<gemiler[4*i];k++)
                          {
                              oyun_alani[gemiler[4*i+1]][gemiler[4*i+2]-k]=4;
                          }
                        return 1;
                      }
                    }
                    j++;

             }break;

    }

  }
    return 0;

}
