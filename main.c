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

typedef struct
{
    char symbol;
    int x;
    int y;
}Cell;

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
    int x;
    int y;
    int direction;

    struct shp *next;
}Ship;

void gameBoard(Cell gameBoard[][10])
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            gameBoard[i][j].symbol = 'W';
            gameBoard[i][j].x = i;
            gameBoard[i][j].y = j;
        }
    }
}

void showCredits()
{
    system("cls");
			{
				printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t                            CREDITS\n");
				printf("\t\t\t               DEVEOLPED BY REZA FARAHBAKHSH(9931074)\n");
				delay(1500);
				system("cls");
			}
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void showMap()
{
    int position = 0;
    printf("\t\t    A\t    B\t    C\t    D\t    E\t    F\t    G\t    H\t    I\t    J\n");
    printf("\t\t---------------------------------------------------------------------------------\n\t");
    for(int i = 0; i<10; i++)
    {
        printf("     %d",i+1);
        for(int j = 0; j<10 ; j++)
        {
            printf("\t|   O");
        }
        printf("   |\n\t\t---------------------------------------------------------------------------------\n\t");
    }
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
    if(p1 == true)
    {
        strcpy(player2,new_data);
    }
    else
    {
        strcpy(player1,new_data);
        p1 = true;
    }

}

void setShips()
{
        showMap();
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
    delay(2000);
    system ("cls");

    //showMap();
    //delay(5000);
    system("cls");

    printf("1. Play with a friend\n\n" );   //coming soon

    printf("2. Play with bot\n\n");

    printf("3. Load game\n\n");             //coming soon

    printf("4. Settings (unavailable)\n\n");//coming soon

    printf("5. Quit game\n\n");

    printf("Please enter your choice: ");
    scanf("%d",&num);


    return num;
}

int main()
{

    Cell p1_gameBoard[10][10],p2_gameBoard[10][10];

    gameBoard(p1_gameBoard);
    gameBoard(p2_gameBoard);

    int choice = showMenu(1);
    if(choice == 5)
    {
        showCredits();
        return 0;
    }else if(choice == 2)
    {
        system("cls");
        strcpy(player1,"BOT");
        p1 = true;
        newProfile();
        system("cls");
        profileList();
        getch();
        system("cls");
        setShips();
        getch();
    }

    showCredits();
    return 0;
}
