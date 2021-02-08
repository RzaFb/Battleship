#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

char player1[10], player2[10];

bool p1 = false;

void showCredits();

typedef struct Pr
{
    char username[50];
    int score;

    struct Pr *next;
}Profile;

typedef struct shp
{
    char username[50];
    int lenght;
    int start;

    struct shp *next;
}Ship;

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void profileList()
{
    printf("List Of Profiles\n+----------------------------------------+\n");
    char c;
    FILE *fp;
    fp = fopen("Profiles.txt","r");

    while((c = fgetc(fp)) != EOF)
      printf("%c", c);

    fclose(fp);
       printf("\n+----------------------------------------+\n");
}

void profileToFile(Profile* node)
{
    FILE *fp;
    fp = fopen("Profiles.bin", "ab+");
    if(node != NULL)
    {
        while(node != NULL)
        {
            fwrite(&node->username, sizeof(char), strlen(node->username), fp);
            fwrite(&node->score, sizeof(int), 1, fp);
            node = node->next;
        }
    }

    fclose(fp);
}

void newProfile()
{
    char new_data[10];

    printf("please enter your Username (max 10 characters): ");

    scanf("%s",new_data);
    if(p1 == true)
    {
        strcpy(player2,new_data);
    }
    else
    {
        strcpy(player1,new_data);
        p1 = true;
    }

     // check if user exists
     // fetch every line from file to array
     // check every name until :
     // load profile if user exists
     // else create and store new user

    FILE *fp;
    fp = fopen("Profiles.txt","a+");
    fprintf(fp,"%s%s%d%s",new_data,":",0,"\n");
    //fwrite(new_data,sizeof(char),strlen(new_data),fp);
    fclose(fp);
    printf("User created...\n");
}

void setShips()
{
    int position = 0;
    for(int i=1; i<=10; i++)
    {
        for(int j=1; j<=10; j++)
        {
            printf("%d\t",++position);
        }
        printf("\n\n");
    }
}

int showMenu(int num)
{
    printf("\n\n\n\n\n\n\n");
	printf("\t\t\t########################################################################\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#      * * *      *    * * * * *  * * * * *  *          * * * *        #\n");
    printf("\t\t\t#      *    *    * *       *          *      *          *              #\n");
    printf("\t\t\t#      * * *    *   *      *          *      *          * * *          #\n");
    printf("\t\t\t#      *    *  * * * *     *          *      *          *              #\n");
    printf("\t\t\t#      * * *  *       *    *          *      * * * * *  * * * *        #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#               * * * *  *     *  * * * * *  * * * *                   #\n");
    printf("\t\t\t#              *         *     *      *      *      *                  #\n");
    printf("\t\t\t#               * * * *  * * * *      *      * * * *                   #\n");
    printf("\t\t\t#                      * *     *      *      *                         #\n");
    printf("\t\t\t#               * * * *  *     *  * * * * *  *                         #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t#                                                                      #\n");
    printf("\t\t\t########################################################################\n");
    delay(1000);
    system ("cls");

    printf("1. Play with a friend\n\n" ); //coming soon

    printf("2. Play with bot\n\n");

    printf("3. Load game\n\n");           //coming soon

    printf("4. Load last game\n\n");      //coming soon

    printf("5. Settings\n\n");            //coming soon

    printf("6. Quit game\n\n");

    printf("Please enter your choice: ");
    scanf("%d",&num);


    return num;
}


int main()
{
    int choice = showMenu(1);
    if(choice == 6)
    {
        showCredits();
        system("pause");
    }else if(choice == 2)
    {
        strcpy(player1,"BOT");
        p1 = true;
        newProfile();
        system("cls");
        profileList();
        getch();
        system("cls");
        setShips();
    }


    system("pause");
}
void showCredits()
{
    system("cls");
		int jc,fw,ic;
				jc=25;
						while(fw==0)
			{
				for(ic=0;ic<=jc;ic++)
				printf("\n");
				printf("                            CREDITS\n");
				printf("               DEVEOLPED BY REZA FARAHBAKHSH(9931074)\n");
				if(ic==0)
                    fw=1;
				delay(1000);
				system ("cls");
				jc=jc-1;
			}
}
