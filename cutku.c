#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //pwd

void writeFileku(FILE *file, char *filepath, char *isi)
{
    file = fopen(filepath, "a");
    if (file != NULL)
    {
        strcat(isi, "\n");
        fputs(isi, file);
    }
    fclose(file);
    
}

void readFileku(char *filepath, int xwrite, int injum)
{
     if (filepath == NULL)
     {
        printf("\nerr: input path kosong\n\n");
        exit(0);
     }

     char *token;
     char str[254];
     char xindex[254];
     int  counter = 0;
     int  index = 0;
     int  jum = injum;

     FILE *pf = fopen(filepath, "r");
     FILE *wf;

     if (xwrite == 0)printf("\n[+] Loading file...");

     if (pf != NULL)
     {
         while(fgets(str, 254, pf) != NULL)
         {
             token = strtok(str, "\n");
             while(token != NULL)
             {
                 sprintf(xindex, "%s.%d.cutku", filepath, index);
                 
                 if (xwrite == 1) writeFileku(wf, xindex, token);
                 token = strtok(NULL, "\n");
             }
             if (counter == jum) {
                 if (xwrite == 1) printf("[!] Writing... %d\n", index);
                 index++;
                 jum += 100;
             }
             counter++;
          }
      }
      fclose(pf);

      if (xwrite == 0) 
      {
          char ui[10];
          printf(" \n\n");
          printf("[+] Jumlah baris file ini adalah: %d\n", counter);
          printf("[+] Per file berisi %d baris adalah: %d file \n", injum, index);
          printf("[+] Yakin mau pecah file ini y/n ? ");scanf("%s", &ui);
          printf("\n\n");

          if (strcmp(ui, "y") == 0 || strcmp(ui, "Y") == 0)
          {
              readFileku(filepath, 1, injum);
          }
          else {
              printf("\n\nProses membagi file dibatalkan\n");
          }
      }
}

int main(int argc, char* argv[])
{
     if (argc == 1) {
        printf("\n\n\t\t### Cutku v1.0 ###\n\n[+] contoh: $./cutku 100 dokumen.txt\n");
        printf("dimana argumen satu adalah isi per file dan kedua nama file\n");
        printf("[+] untuk menghapus: $ rm *.cutku\n\n");
        exit(0);
     }
     
     char cwd[254];
     
     if (getcwd(cwd, sizeof(cwd)) != NULL) 
     {
        strcat(cwd, "/");
        strcat(cwd, argv[2]);

        int injum = (int)strtol(argv[1], (char **)NULL, 10);
        readFileku(cwd, 0, injum);
     }
     
     return 0;
}
    