#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>

char player1[10], player2[10];

//pre defined ships info
int Ship_lenght[10] = {5, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int Ship_score[10] = {5, 8, 8, 12, 12, 12, 25, 25, 25, 25};

bool p1 = false;

typedef struct
{
    char symbol;
    int x;
    int y;
}Cell;

Cell p1_gameBoard[11][11],p2_gameBoard[11][11];

typedef struct Pr
{
    char username[10];
    int score;

    struct Pr *next;
}Profile;

typedef struct shp
{
    int explosion;
    int lenght;
    int x;
    int y;
    char direction;
    int score;

    struct shp *next;
}Ship;

//function to add the data from file to linked list
void appendFileList(Profile** head_ref, int score, char username[])
{
    Profile* new_node = (Profile*) malloc(sizeof(Profile));

    Profile *last = *head_ref;

    strcpy(new_node->username, username);

    new_node->score = score;

    new_node->next = NULL;

    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    return;
}

//a dynamic array of user showing each symbol of a coordination
void gameBoard(Cell gameBoard[][11])
{
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            gameBoard[i][j].symbol = 'O';
            gameBoard[i][j].x = i;
            gameBoard[i][j].y = j;
        }
    }
}

//showed at the end of the game if user quits
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

//show a map of the game while setting the ships on it and while playing the game
void showMap(Cell gameBoard[][11])
{
    printf("\t\t    1\t    2\t    3\t    4\t    5\t    6\t    7\t    8\t    9\t    10\n");
    printf("\t\t---------------------------------------------------------------------------------\n\t");
    for(int i = 1; i<11; i++)
    {
        printf("     %d",i);
        for(int j = 1; j<11 ; j++)
        {
            printf("\t|   %c", gameBoard[i][j].symbol);
        }
        printf("   |\n\t\t---------------------------------------------------------------------------------\n\t");
    }
}

//function to read the profile text file and add the elements to a linked list of profiles
/*void fileToList(Profile *head_ref)
{
    char username[10];
    int score_int = 0;
    FILE *fp;
    fp = fopen("Profiles.txt", "r");
    char score[10];
    char ln[2];
    char chunk[10];
    size_t usr = sizeof(chunk);
    char *line = malloc(usr);


    line[0] = '\0';
    while(fgets(chunk, sizeof(chunk), fp) != NULL)
    {
        strcat(line, chunk);

        if(line[strlen(line - 1)] == '\n')
        {
            fputs(line, stdout);
            //strcpy(username, chunk);
            line[0] = '\0';
        }

        strcat(line, chunk);

        if(line[strlen(line - 1)] == '\n')
        {
            fputs(line, stdout);
            //strcpy(score, chunk);
            line[0] = '\0';
        }
        //fscanf(fp, "%[^\n]", username);
        //fscanf(fp, "%[^\n]", score);

        for (int i = 0; score[i] != '\0'; i++) {
            //printf("1\t");
            score_int = score_int * 10 + (score[i] - 48);
        }



        appendFileList(&head_ref, score_int, username);

    }

    fclose(fp);

    delay(2000);

}
*/

// shows a list of existing profiles read from a text file
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

//this function adds a new profile if the user wishes to
void newProfile()
{
    char new_data[10];

    printf("please enter your Username (max 10 characters): ");

    scanf("%s",new_data);

     // check if user exists
     // fetch every line from file to array
     // check every name until \n
     // load profile if user exists
     // else create and store new user

    FILE *fp;
    fp = fopen("Profiles.txt","a+");
    fprintf(fp,"%s%s%d%s",new_data,"\n",0,"\n");
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

//function to add the ships to a list
//input : head (aka pointer to first in the list) and gameboard of player

void appendShip(Ship** head_ref,Cell gameBoard[][11], int ln)
{
    /* 1. allocate node */
    Ship* new_node = (Ship*) malloc(sizeof(Ship));

    Ship *last = *head_ref;  /* used in step 5*/

    new_node->lenght  = Ship_lenght[ln];

    showMap(gameBoard);

    printf("\n please enter coordination for ship with length of: %d\n\n first column (horizontal)\t second row(vertical)\t third direction\n\n example: 5 6 H\t input: ",new_node->lenght);

    int x, y;
    char d;

    L1:scanf("%d %d %c",&y,&x,&d);

    system("cls");

    if(x > 11 || x < 1 || y < 1 || y > 11)
    {
        showMap(gameBoard);
        printf("\ninvalid input/s. please try again: ");
        goto L1;
    }
    if(d != 'H')
    {
        if(d != 'V')
        {
            showMap(gameBoard);
            printf("\ninvalid input/s. please try again with V or H: ");
            goto L1;
        }
    }
    //printf("bug?\t"); // debugger
    if(d == 'V')
    {
        if(x + Ship_lenght[ln] > 11)
        {
            showMap(gameBoard);
            printf("\n\tship crossing boder/s. please try again: ");
            goto L1;
        }
        bool near = false; // to check if there are ships nearby
        for (int i = x; i < x + Ship_lenght[ln]; i++)
        {
            if(gameBoard[i][y].symbol == 'S')
                near = true;
            //printf("bug?\t"); // debugger
        }
        if (near == true)
        {
            showMap(gameBoard);
            printf("\n\tinput is too close to another ship\n try again please: ");
            goto L1;
        }
        for(int i = 0; i < Ship_lenght[ln]; i++)
            {
                gameBoard[x + i][y].symbol = 'S';
                //printf("bug? %d  ",i); // debugger
            }
        for (int i = x - 1; i < x + Ship_lenght[ln] + 1; i++)
        {
            for(int j = y - 1; j < y + 2; j++)
            {
                if(gameBoard[i][j].symbol != 'S')
                    gameBoard[i][j].symbol = 'W';
            }
        }
    }

     if(d == 'H')
    {
        if(y + Ship_lenght[ln] > 11)
        {
            showMap(gameBoard);
            printf("\n\tship crossing border/s. please try again: ");
            goto L1;
        }
        bool near = false; // to check if there are ships nearby
        for (int i = -1; i < 2; i++)
        {
            for(int j = 0; j < Ship_lenght[ln] + 1; j++)
            {
                if(gameBoard[x + i][y + j].symbol == 'S')
                    near = true;
                //printf("bug?\t"); // debugger
            }
        }
        if (near == true)
        {
            showMap(gameBoard);
            printf("\n\tinput is too close to another ship\n try again please: ");
            goto L1;
        }
        for(int i = 0; i < Ship_lenght[ln]; i++)
            {
                gameBoard[x][y + i].symbol = 'S';
                //printf("bug? %d  ",i); // debugger
            }
        for (int i = x - 1; i < x + 2; i++)
        {
            for(int j = y - 1; j < y + Ship_lenght[ln] + 1; j++)
            {
                if(gameBoard[i][j].symbol != 'S')
                    gameBoard[i][j].symbol = 'W';
            }
        }
    }

    new_node->direction = d;
    new_node->x = x;
    new_node->y = y;
    new_node->score = Ship_score[ln];


    new_node->next = NULL;

    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    return;
}

//function to check if ships are destroyed and to check how many blocks of ship is hit
void deleteShip(Ship** head_ref, int score, Cell gameBoard[][11], int x, int y)
{
    Ship *temp = *head_ref, *prev;

    //to check if ship is hit
    if(temp->direction == 'V')
    {
        if(y == temp->y)
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                if(x == temp->x + i && gameBoard[x][y] == 'E' && gameBoard[x][y] == 'C')
                {
                    gameBoard[x][y].symbol = 'E';
                    temp->explosion++;
                }
            }
        }
    }
    else
    {
        if(x == temp->x)
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                if(y == temp->y + i && gameBoard[x][y] == 'E' && gameBoard[x][y] == 'C')
                {
                    gameBoard[x][y].symbol = 'E';
                    temp->explosion++;
                }
            }
        }
    }

    //to check if ship is destroyed
    if (temp != NULL && temp->lenght == temp->explosion) {
        if(temp->direction == 'V')
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                gameBoard[temp->x + i][temp->y].symbol = 'C';
            }
            for(int i = -1; i < temp->lenght + 1; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(gameBoard[temp->x + i][temp->y + j].symbol != 'C')
                        gameBoard[temp->x + i][temp->y + j].symbol = 'W';
                }
            }
        }
        else
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                gameBoard[temp->x][temp->y + i].symbol = 'C';
            }
            for(int i = -1; i < temp->lenght + 1; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(gameBoard[temp->x + j][temp->y + i].symbol != 'C')
                        gameBoard[temp->x + j][temp->y + i].symbol = 'W';
                }
            }
        }

        score += temp->score;

        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }

    while (temp != NULL && temp->lenght != temp->explosion) {
        prev = temp;
        temp = temp->next;
            //to check if ship is hit
        if(temp->direction == 'V')
        {
            if(y == temp->y)
            {
                for(int i = 0; i < temp->lenght; i++)
                {
                    if(x == temp->x + i && gameBoard[x][y] == 'E' && gameBoard[x][y] == 'C')
                    {
                        gameBoard[x][y].symbol = 'E';
                        temp->explosion++;
                    }
                }
            }
        }
        else
        {
            if(x == temp->x)
            {
                for(int i = 0; i < temp->lenght; i++)
                {
                    if(y == temp->y + i && gameBoard[x][y] == 'E' && gameBoard[x][y] == 'C')
                    {
                        gameBoard[x][y].symbol = 'E';
                        temp->explosion++;
                    }
                }
            }
        }

    }

    if (temp == NULL)
        return;

    //if ship is destroyed then:
    if(temp->direction == 'V')
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                gameBoard[temp->x + i][temp->y].symbol = 'C';
            }
            for(int i = -1; i < temp->lenght + 1; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if(gameBoard[temp->x + i][temp->y + j].symbol != 'C')
                        gameBoard[temp->x + i][temp->y + j].symbol = 'W';
                }
            }
        }
    else
    {
        for(int i = 0; i < temp->lenght; i++)
        {
            gameBoard[temp->x][temp->y + i].symbol = 'C';
        }
        for(int i = -1; i < temp->lenght + 1; i++)
        {
            for(int j = -1; j < 2; j++)
            {
                if(gameBoard[temp->x + j][temp->y + i].symbol != 'C')
                    gameBoard[temp->x + j][temp->y + i].symbol = 'W';
            }
        }
    }

    score += temp->score;

    prev->next = temp->next;

    free(temp); // Free memory
}

//function to check where the shot hit
int checkShot(int x, int y, Ship **head, Cell gameBoard[][11])
{
    bool hit = false;
    int check = 0;
    // Store head node
    Ship* temp = *head_ref;
    // first check if shot is valid
    if(gameBoard[x][y] != 'O')
    {
        check = 2;
        return check;
    }

    // check if first ship is hit
    if(temp->direction == 'V')
    {
        if(y == temp->y)
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                if(x == temp->x + i)
                {
                    hit = true;
                }
            }
        }
    } else {
        if(x == temp->x)
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                if(y == temp->y)
                {
                    hit = true;
                }
            }
        }
    }

    // If head node itself holds
    if (temp != NULL && hit == true)
    {
        check = 1;
        return check;
    }
    // keep track of the previous node
      else
    {
    while (temp != NULL && hit == false)
    {
        temp = temp->next;
        // check if first ship is hit
    if(temp->direction == 'V')
    {
        if(y == temp->y)
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                if(x == temp->x + i)
                {
                    return 1;
                }
            }
        }
    } else {
        if(x == temp->x)
        {
            for(int i = 0; i < temp->lenght; i++)
            {
                if(y == temp->y)
                {
                    return 1;
                }
            }
        }
    }

    }
        return check;
    }
    return check;
}

//shows the intro and the menu at the beginning of the game
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

    printf("1. Play with a friend\n\n" );

    printf("2. Play with bot\n\n");

    printf("3. Load game\n\n");             //coming soon

    printf("4. Quit game\n\n");

    printf("Please enter your choice: ");

    scanf("%d",&num);


    return num;
}

//main part of the code that the magic happens
int main()
{

    Profile *head = NULL;

    //fileToList(&head);

    Cell target1[11][11], target2[11][11];

    gameBoard(target1);
    gameBoard(target2);

    Ship *head1 = NULL;
    Ship *head2 = NULL;

    gameBoard(p1_gameBoard);

    gameBoard(p2_gameBoard);

    int choice = showMenu(1);

    if(choice == 4)

    {
        showCredits();
        exit(1);

        return 0;
    }else if(choice == 2)
    {
        system("cls");

        strcpy(player1,"BOT");

        p1 = true;

        profileList();

        printf("choose profile or create new\nchoose: 1\ncreate: 2\n");

        int cho;

        scanf("%d",&cho);

        if(cho == 1)
        {
            printf("enter your username: ");
            char unm[10];
            scanf("%s",unm);
        }

        if(cho == 2)
            newProfile();

        system("cls");

        for(int i = 0; i < 10; i++)
        {
            appendShip(&head2, p2_gameBoard, i);
            //printf(" bug \t");  //manual debug
        }
    }

    showCredits();
    return 0;
}
