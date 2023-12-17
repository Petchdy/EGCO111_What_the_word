#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void Loading_Screen();
int File_empty_or_not(char File_Name[]);
int Count_Line_In_File(char File_Name[]);
void Creat_Player_Struct();
void Creat_Dic_And_Hint();
int Login();
void Win();
void Loss();
int Yes_or_No();
void Box_here(int position, int box_position);
int Choose_Level();
void Arrow_Here(int position, int arrow_position);
void Print_Current(int n, int current[]);
int Game(int mode);
void Print_top_score();
void Update(int score, int new);
void hidecursor();

char login[15];
int user_file_exist_or_not; // = 1 -> exist || = 0 -> not exist

struct Dictionary
{
    char word[25];
    char hint[2][150];

} dic[200];

struct Player
{
    char username[15];
    int score;
} player[100], p;

int main() {
    // Starting part

    // printf("%d\n\n\n\n", Count_Line_In_File("Vocab.txt"));

    Loading_Screen();
    // add data into stuct (Dictionary, Player)
    Creat_Dic_And_Hint();
    Creat_Player_Struct();

    // new = 0 -> already exit, new = 1 -> new user
    int flag = 0, player_status = Login(), score, new = 0;
    char temp;

    // check for player name in user_info.txt
    // player_status = -1 -> new_user
    if (player_status < 0) {
        score = 0;
        new = 1;
    }
    // player_status >= 0 -> old_user
    else {
        score = player_status;
    }

    // Game part
    while (!flag)
    {

        // choose level
        int mode = Choose_Level();

        if (Game(mode)) {
            // print win screen
            Win();
            score++;
        }
        else {
            // print loss screen
            Loss();
        }

        // wait for user to press any key to continue
        printf("Your current score : %d ^_^\n",score);
        printf("Press any key to continue");
        temp = getch();

        Update(score, new);

        // Do you want to play again?
        flag = Yes_or_No();
        // flag = 0 -> play again
        if(flag == 1)
        {
            printf("\n\n\n\n\n\n");
            printf("                                                 ^ ^             \n");
            printf("                                                (O,O)            \n");
            printf("                                                (   ) BYE BYE ...    \n");
            printf("-------------------------------------------------\"-\"--------------------------------------------------------------\n");
        }
        // flag = 1 -> exit game
        else {
            continue;
        }
    }

    Print_top_score();

    printf("\n                                                Press any key to exit.");
    temp = getch();

	return 0;
}

void Loading_Screen() {
    system("COLOR 03");

    printf("                         ____          ___      ____        ____            ______           _______________  \n");
    printf("                        /  /|         /  /|    /   /|      /   /|          /     /|         /              /| \n");
    printf("                       /@@/ |        /@@/ |   /@@@/ |     /@@@/ |      ___/@@@@@/ |__      |@@@@@@@@@@@@@@| / \n");
    printf("                       |@@| | ___ ___|@@| |   |@@@| |     |@@@| |    _/@@@@@@@@@@/__/|__   |_____     ____|/  \n");
    printf("                       |@@| |/@@//@@/|@@| |   |@@@| | ____|@@@| |   |@@@@| |     |@@/__/|        |@@@| |      \n");
    printf("                       |@@| ||@@||@@||@@| |   |@@@| |/@@@/|@@@| |   |@@@@| | ____|@@@@/ |        |@@@| |      \n");
    printf("                       |@@| ||@@||@@||@@| |   |@@@| ||@@@||@@@| |   |@@@@| |/@@@/|@@@@| |        |@@@| |      \n");
    printf("                       |@@@@@@@@@@@@@@@@| /   |@@@| |     |@@@| |   |@@@@| ||@@@||@@@@| |        |@@@| |      \n");
    printf("                       |@@@@@@@@@@@@@@@@|/    |@@@| |     |@@@| |   |@@@@| |     |@@@@| |        |@@@| |      \n");
    printf("                         |@@| |  |@@| |       |@@@| |     |@@@| |   |@@@@| |     |@@@@| |        |@@@| /      \n");
    printf("                         |@@|/   |@@|/        |@@@|/      |@@@|/    |@@@@|/      |@@@@| /        |@@@|/       \n");
    printf("\n");
    printf("\n");
    printf("                             ___           ___        ____________        ___________          ____________      \n");
    printf("                            /  /|         /  /|      /           /|      /          /|        /           /|     \n");
    printf(" -----------------------   /@@/ |        /@@/ |    _/@@@@@@@@@@@/ |_    /@@@@@@@@@@/ |___    /@@@@@@@@@@@/_|___  \n");
    printf(" | @@@@@  @   @  @@@@@ |   |@@| | ___ ___|@@| |   |@@@@| |   |@@@@@/|   |@@@| |    |/   /|   |@@@@| | |@@@@@@@/| \n");
    printf(" |   @    @   @  @     |   |@@| |/@@//@@/|@@| |   |@@@@| |   |@@@@/ |   |@@@| |____|@@@/ |   |@@@@| |   |@@@@/ | \n");
    printf(" |   @    @@@@@  @@@@@ |   |@@| ||@@||@@||@@| |   |@@@@| |   |@@@@| |   |@@@|/     |@@@|/    |@@@@| |   |@@@@| | \n");
    printf(" |   @    @   @  @     |   |@@| ||@@||@@||@@| |   |@@@@| |   |@@@@| |   |@@@@@@@@@@@@|/__    |@@@@| |   |@@@@| | \n");
    printf(" |   @    @   @  @@@@@ |   |@@@@@@@@@@@@@@@@| /   |@@@@| |___|@@@@| /   |@@@| |  |@@@| / |   |@@@@| |___|@@@@| | \n");
    printf(" -----------------------   |@@@@@@@@@@@@@@@@|/    |@@@@|/    |@@@@|/    |@@@| |    |@@@| |   |@@@@| /__/@@@@@|/  \n");
    printf("                             |@@| |  |@@| |          |@@@@@@@@@| |      |@@@| |    |@@@| |   |@@@@@@@@@@@| |     \n");
    printf("                             |@@|/   |@@|/           |@@@@@@@@@|/       |@@@|/     |@@@|/    |@@@@@@@@@@@|/      \n");
    printf("\n");
    printf("\n");
    printf("                                                                                    __         __          \n");
    printf("                                       ___                  _______                |@@|__   __|@@|         \n");
    printf("                                     _|@@@|_              _|@@@@@@@|_                _|@@|_|@@|_           \n");
    printf("                                   _|@@@@@@@|_          _|@@@@@@@@@@@|_           __|@@@@@@@@@@|__         \n");
    printf("                                  |@@  @@@  @@|        |@@@   @@@   @@@|      ___|@@@@  @@@@  @@@@|___     \n");
    printf("                                  |@@@@@@@@@@@|        |@@@@@@@@@@@@@@@|     |@@@@@@@@@@@@@@@@@@@@@@@@|    \n");
    printf("                                  _|@@|   |@@|_         __|@@@| |@@@|__      |@@| |@@@@@@@@@@@@@@| |@@|    \n");
    printf("                                _|@@| |@@@| |@@|_    __|@@@| |@@@| |@@@|__   |@@| |@@|__    __|@@| |@@|    \n");
    printf("                               |@@||@@|   |@@||@@|  |@@@|             |@@@|         |@@@|  |@@@|           \n");
    printf("\n");
    printf("\n");
    // printf("                                Please input your username : ");
}

int File_empty_or_not(char File_Name[]) {

    FILE *fp;

    fp = fopen(File_Name, "r");

    if (fp == NULL) {
        printf("Error can't read user_info file\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);

    int size = ftell(fp);

    if (size == 0)
    {
        return -1; // -> empty
        // printf("this is an empty file.");
    }
    else {
        return 0;
    }
}

int Count_Line_In_File(char File_Name[]) {

    char c;
    int i = 1;

    FILE *fp;

    fp = fopen(File_Name, "r");

    if (fp == NULL) {
        printf("Error can't read file\n");
        exit(1);
    }

    if (File_empty_or_not(File_Name) == -1) {
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n') // Increment i if this character is newline
        {
            i++;
        }
    }

    fclose(fp);

    return i;

}

void Creat_Player_Struct() {

    FILE *fp;
    char temp;
    int existing_user;

    fp = fopen("user_info.txt", "r");

    if (fp == NULL) {
        fclose(fp);
        fp = fopen("user_info.txt", "w+");
    }

    if (File_empty_or_not("user_info.txt") == -1) {
        // do nothing + this file is empty
    }
    else {

        existing_user = Count_Line_In_File("user_info.txt");

        fp = fopen("user_info.txt", "r");

        for (int i = 0; i < existing_user; i++)
        {
            fscanf(fp, "%14[^,],%d", player[i].username, &player[i].score);
            temp = fgetc(fp);
        }

        fclose(fp);
    }

}

void Creat_Dic_And_Hint() {

    int i = 0;
    char temp1, temp2;

    FILE *fp;

    fp = fopen("Vocab.txt", "r");

    if (fp == NULL) {

        printf("Error can't read Vocab file\n");
        temp1 = getch();
        exit(1);
    }

    while (!feof(fp))
    {
        // store words in struct:dic[i].word
        fscanf(fp, "%s", dic[i].word);
        i++;
    }

    fclose(fp);

    // printf("closed file (dic)\n");

    fp = fopen("Hint.txt", "r");

    if (fp == NULL) {

        printf("Error can't read Hint file\n");
        temp2 = getch();
        exit(1);
    }

    // printf("start reading hints\n");

    i = 0;
    char temp;
    while (!feof(fp))
    {
        fscanf(fp, "%150[^,],%150[^\n]", dic[i].hint[0], dic[i].hint[1]);
        temp = fgetc(fp);
        // printf("hint1 = %s, hint2 = %s\n", dic[i].hint1, dic[i].hint2);
        i++;
    }

    fclose(fp);
}

int Login() {

    FILE *fp;
    char temp;
    int score = 0, flag = 1;
    int existing_user;
    existing_user = Count_Line_In_File("user_info.txt");

    fp = fopen("user_info.txt", "r");

    if (fp == NULL) {
        printf("Error can't read user_info file\n");
        exit(1);
    }

    printf("                                Please input your username : ");
    scanf("%14[^\n]%*c", login);

    for (int i = 0; i < strlen(login); i++)
    {
        if (login[i] == ',') {
            flag = 0;
        }
    }

    if (strlen(login) == 0) {
        strcpy(login, "guest");
    }
    else if (!strcmp(login, " ")) {
        strcpy(login, "guest");
    }
    else if (!flag) {
        strcpy(login, "guest");
    }
    

    // printf("Login as : %s", login);

    for (int i = 0; i < existing_user; i++) {

        if (!strcmp(player[i].username, login)) {
            printf("                                              Welcome back : %s\n", player[i].username);
            Sleep(1000);
            printf("                                              Press any key to continue.");
            temp = getch();
            fclose(fp);

            return player[i].score;
        }

    }

    printf("                                                   Welcome : %s\n", login);
    Sleep(1000);
    printf("                                                   Press any key to continue.");
    temp = getch();

    return -1;
}

void Win() {
    printf("\n\n");
    printf("                            *                     *         *                                             \n");
    printf("                      *                       *         *                *          *                     \n");
    printf("                                 *      *              ***                         ***                    \n");
    printf("                  *       *            ***         * ******* *      *               *                     \n");
    printf("                *****                   *              ***                    *             *             \n");
    printf("            *     *                                     *                                 *****           \n");
    printf("                                                                                            *             \n\n");
    printf("             **         @@  @@   @@@@@   @@   @@     @@  @@  @@  @@@@@@@@  @@    @@   @@                  \n");
    printf("        *               @@  @@  @@   @@  @@   @@     @@  @@  @@     @@     @@@   @@   @@          *       \n");
    printf("        *               @@  @@  @@   @@  @@   @@     @@  @@  @@     @@     @@@@  @@   @@                  \n");
    printf("                  *      @@@@   @@   @@  @@   @@     @@  @@  @@     @@     @@ @@ @@   @@     *            \n");
    printf("            *             @@    @@   @@  @@   @@     @@  @@  @@     @@     @@  @@@@   @@            **    \n");
    printf("           ***            @@    @@   @@  @@   @@      @@@@@@@@      @@     @@   @@@                       \n");
    printf("            *             @@     @@@@@    @@@@@        @    @    @@@@@@@@  @@    @@   @@                  \n\n");
    printf("                                                                                        *      *          \n");
    printf("                    *              *                                                   ***                \n");
    printf("                  *****                              *              *                   *                 \n");
    printf("                    *          *             *                    *****                                   \n");
    printf("                              ***           ***          *          *         **                          \n");
    printf("                           * ***** *         *        *                                                   \n");
    printf("                              ***                             **                                          \n");
    printf("                               *                                                                          \n");
    printf("\n\n");
}

void Loss() {
    printf("\n\n");
    printf("              @@  @@   @@@@@   @@   @@     @@       @@@@@    @@@@@@  @@@@@@   @@       @@@@@@@           \n");
    printf("              @@  @@  @@   @@  @@   @@     @@      @@   @@   @@      @@       @@     @         @          \n");
    printf("              @@  @@  @@   @@  @@   @@     @@      @@   @@   @@      @@       @@    @   @   @   @         \n");
    printf("               @@@@   @@   @@  @@   @@     @@      @@   @@   @@@@@@  @@@@@@   @@    @           @         \n");
    printf("                @@    @@   @@  @@   @@     @@      @@   @@       @@  @@       @@    @   @@@@@   @         \n");
    printf("                @@    @@   @@  @@   @@     @@      @@   @@       @@  @@              @         @          \n");
    printf("                @@     @@@@@    @@@@@      @@@@@@   @@@@@    @@@@@@  @@@@@@   @@       @@@@@@@            \n");
    printf("\n\n");
}

int Yes_or_No() {

    system("cls");
    system("COLOR 0E");
    int current_position = 0;
    int key_press = 0;
    int min = 0, max = 1;
    while (key_press != 13)
    {

        system("cls");

        printf("                                            Do you want to play again?\n");
        Box_here(0, current_position);
        Box_here(1, current_position);

        printf( "\033[5;%dH", 57);
        printf("YES");
        printf( "\033[10;%dH", 58);
        printf("NO");

        key_press = getch();

        if (key_press == 80 && current_position != max) {
            current_position++;
        }
        else if (key_press == 72 && current_position != min) {
            current_position--;
        }
        else {
            // pass
        }

    }

    return current_position;
}

void Box_here(int position, int box_position) {

    if (position == box_position == 0)
    {
        printf( "\033[3;%dH", 0);
        printf("                                                 -----------------");
        printf( "\033[4;%dH", 0);
        printf("                                                 |               |");
        printf( "\033[5;%dH", 0);
        printf("                                                 |               |");
        printf( "\033[6;%dH", 0);
        printf("                                                 |               |");
        printf( "\033[7;%dH", 0);
        printf("                                                 -----------------");

        printf( "\033[8;%dH", 0);
        printf("                                                                  ");
        printf( "\033[9;%dH", 0);
        printf("                                                                  ");
        printf( "\033[10;%dH", 0);
        printf("                                                                  ");
        printf( "\033[11;%dH", 0);
        printf("                                                                  ");
        printf( "\033[12;%dH", 0);
        printf("                                                                  ");
    }
    else {
        printf( "\033[8;%dH", 0);
        printf("                                                 -----------------");
        printf( "\033[9;%dH", 0);
        printf("                                                 |               |");
        printf( "\033[10;%dH", 0);
        printf("                                                 |               |");
        printf( "\033[11;%dH", 0);
        printf("                                                 |               |");
        printf( "\033[12;%dH", 0);
        printf("                                                 -----------------");

        printf( "\033[3;%dH", 0);
        printf("                                                                  ");
        printf( "\033[4;%dH", 0);
        printf("                                                                  ");
        printf( "\033[5;%dH", 0);
        printf("                                                                  ");
        printf( "\033[6;%dH", 0);
        printf("                                                                  ");
        printf( "\033[7;%dH", 0);
        printf("                                                                  ");
    }
}

int Choose_Level() {

    // hide cursor
    printf("\e[?25l");
    system("cls");
    system("COLOR 0D");
    int arrow_current_position = 0;
    int key_press = 0;
    int min = 0, max = 2;

    while (key_press != 13)
    {

        system("cls");

        Arrow_Here(0, arrow_current_position);
        Arrow_Here(1, arrow_current_position);
        Arrow_Here(2, arrow_current_position);

        printf ( "\033[2;%dH", 16);
        printf("  ---------------------------\n");
        printf ( "\033[3;%dH", 16);
        printf(" |         Easy mode         |\n");
        printf ( "\033[4;%dH", 16);
        printf("  ---------------------------\n");

        printf ( "\033[7;%dH", 16);
        printf("  ---------------------------\n");
        printf ( "\033[8;%dH", 16);
        printf(" |        Normal mode        | \n");
        printf ( "\033[9;%dH", 16);
        printf("  ---------------------------\n");

        printf ( "\033[12;%dH", 16);
        printf("  ---------------------------\n");
        printf ( "\033[13;%dH", 16);
        printf(" |        Hard mode          |\n");
        printf ( "\033[14;%dH", 16);
        printf("  ---------------------------\n");

        printf("\n\n");
        printf("--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--");
        printf("\n\n");

        key_press = getch();

        //key_press = 80 -> down
        //key_press = 72 -> up

        if (key_press == 80 && arrow_current_position != max) {
            arrow_current_position++;
        }
        else if (key_press == 72 && arrow_current_position != min) {
            arrow_current_position--;
        }
        else {
            // pass
        }

    }
    // system("cls");
    return arrow_current_position+1;

}

void Arrow_Here(int position, int arrow_position) {

    if (position == arrow_position)
    {
        printf(" _______|\\   \n");
        printf("|         \\  \n");
        printf("|          * \n");
        printf("|_______  /  \n");
        printf("        |/   \n");
    }
    else {
        printf("             \n");
        printf("             \n");
        printf("             \n");
        printf("             \n");
        printf("             \n");
    }

}

void Print_Current(int word_number, int current[]) {

    int blank_space = 56 - strlen(dic[word_number].word);
    printf("\n\n");
    // printf("                                                 ");
    for (int i = 0; i < blank_space; i++)
    {
        printf(" ");
    }


    for (int i = 0; i < strlen(dic[word_number].word); i++)
    {
        if (current[i] == 1)
        {
            printf(" %c", dic[word_number].word[i]);
        }
        else
        {
            printf(" _");
        }
    }
    printf("\n");
}

int Game(int mode) {

    fflush(stdin);
    system("cls");
    system("COLOR 0A");
    // *Setting part*
    int life, hint, count = 0;
    switch (mode)
    {
    case 1:
        life = 4;
        hint = 2;
        break;
    case 2:
        life = 3;
        hint = 1;
        break;
    case 3:
        life = 2;
        hint = 0;
        break;
    }

    // set random seed
    srand(time(NULL));

	// rand()%x -> random number from [0 - (x-1)]
	int random_word_number = rand()%(Count_Line_In_File("Vocab.txt"));
    int random_missing_index;
    // n = lenght of word
	int n = strlen(dic[random_word_number].word);
    // array showing which index is missing or showing or etc.
    int index_checking[n];
    // how many index will be missing?
    // int missing_count = n-(n/(mode))+1;
    int missing_count = (n+1)/(5-mode) + 1;

    // set default value (1) in index_checking
    for (int i = 0; i < n; i++)
    {
        index_checking[i] = 1;
    }
    // run a loop to set missing index
    // random missing index -> replace 1 (showing) by -1 (missing)
    while (count < missing_count)
    {
        random_missing_index = rand()%n;
        if (index_checking[random_missing_index] == 1)
        {
            count++;
            index_checking[random_missing_index] = -1;
        }
    }

    // *Guessing part*

    printf("--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--\n\n");
    printf("                                                                                        Life : %d | Hint : %d", life, hint);

    char guessing;
    char dummy[20];
    int blank_space = 113; // for hint

    // Check life & count
    // printf("count = %d, life = %d\n", count, life);

    // count = 0 -> get all the ans
    // life = 0 -> lost the game
    while (life > 0 && count > 0)
    {
        // print current
        Print_Current(random_word_number, index_checking);

        printf("\n");
        printf("                                                 ");
        printf("Guessing... : ");
        fflush(stdin);
        scanf(" %s", dummy);
        fflush(stdin);
        printf("\n");

        if (strlen(dummy) == 1) {
            guessing = dummy[0];
        }

        // type in ? for hint
        // Hints stored in struct -> dic[].hint[]
        if (strlen(dummy) > 1) {
            printf("                                              ");
            printf("Only 1 character pls!\n");
        }
        else if(guessing=='?' && hint > 1)
        {
            // printf("                                                 ");
            for (int i = 0; i < (blank_space - strlen(dic[random_word_number].hint[0]) - 7) / 2; i++)
            {
                printf(" ");
            }

            printf("hint : %s\n", dic[random_word_number].hint[0]);
            hint--;
        }
        else if (guessing == '?' && hint == 1)
        {
            // printf("                                                 ");
            for (int i = 0; i < (blank_space - strlen(dic[random_word_number].hint[1]) - 7) / 2; i++)
            {
                printf(" ");
            }

            printf("hint : %s\n", dic[random_word_number].hint[1]);
            hint--;
        }
        else if (guessing == '?' && hint == 0)
        {
            printf("                                                  ");
            printf("No more hint!\n");
        }
        else if ((int)guessing >= 65 && (int)guessing <= 90) 
        {
            printf("                                                 ");
            printf("Only lowercase!\n");
        }
        else if ((int)guessing >= 97 && (int)guessing <= 122) 
        {
            int check = 0;
            for (int i = 0; i < n; i++)
            {
                if (index_checking[i] == -1)
                {
                    if (dic[random_word_number].word[i] == guessing)
                    {
                        index_checking[i] = 1;
                        count--;
                        check = 1;
                        printf("                                                    ");
                        printf("Correct!\n");
                    }
                }
            }
            if (check == 0) {
                life--;
                printf("                                                      ");
                printf("Wrong!\n");
            }
        }
        else {
            printf("                                                 ");
            printf("English letters!\n");
        }

        printf("\n\n");
        printf("--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--o--");
        printf("\n\n");
        if (life > 0 && count > 0) {
            printf("                                                                                        Life : %d | Hint : %d", life, hint);
        }

    }

    // *End game part*

    //Print_Current(random_word_number, index_checking);

    printf("\n\n                                                The word is %s\n\n", dic[random_word_number].word);

    if (life > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Print_top_score() {
    int existing_user = Count_Line_In_File("user_info.txt");
    char line[100];

    Creat_Player_Struct();

    for(int i=0; i<existing_user-1; i++) {
        for(int j=i+1; j<existing_user; j++)
        {
            if(player[i].score<player[j].score)
            {
                p=player[i];
                player[i]=player[j];
                player[j]=p;
            }
        }
    }
    printf("\n                                                        ");
    printf("Top5 \n\n");
    printf("                                               username          score\n\n");
    if (existing_user > 5) {
        existing_user = 5;
    }
    for(int i=0; i<existing_user; i++)
    {
        printf("                                                ");
        printf("%d %-15s %d\n",i+1,player[i].username,player[i].score);
    }

}

void Update(int score, int new) {

    FILE *fp;
    char temp;

    int existing_user = Count_Line_In_File("user_info.txt");

    fp = fopen("user_info.txt", "r");

    if (fp == NULL) {
        printf("Error can't read user_info file\n");
        exit(1);
    }

    if (!new)
    {
        for (int i = 0; i < existing_user; i++) {

            if (!strcmp(player[i].username, login)) {
                player[i].score = score;
            }
        }

        fclose(fp);

        fp = fopen("user_info.txt", "w+");

        for (int i = 0; i < existing_user; i++)
        {
            fprintf(fp, "%s,%d", player[i].username, player[i].score);
            if (i != existing_user-1) {
                fprintf(fp, "\n");
            }
        }

    }
    else if (new && File_empty_or_not("user_info.txt") == 0) {
        fclose(fp);
        fp = fopen("user_info.txt", "a");
        fprintf(fp, "\n%s,%d", login, score);
    }
    else {
        fclose(fp);
        fp = fopen("user_info.txt", "w+");
        fprintf(fp, "%s,%d", login, score);
    }

    fclose(fp);

}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

// hide cursor
//printf("\e[?25l");
// show cursor
// printf("\e[?25h");
