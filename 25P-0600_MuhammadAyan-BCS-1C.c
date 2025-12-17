#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    //Muhammad Ayan
    //25P-0600
    //BCS 1C
    int i, j, box, menuChoice; 
    char playerA[50], playerB[50];
    int grid[4][4];
    FILE *filePtr;

    printf("\n\t\t*** Welcome To Tic Tac Toe Game ***\n");

    while (1) {
        printf("\n\t------- MENU -------\n");
        printf("\t1. Start A New Game\n");
        printf("\t2. Search Game History By Player Name\n");
        printf("\t3. Show Statistics for The Top Three Players\n");
        printf("\t4. Exit\n");

        printf("\n\tEnter Your Choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice) {
            case 1:
                filePtr = fopen("games_log.txt", "a");  
                printf("\n\tEnter Player 1 Name: ");
                scanf(" %[^\n]s", playerA);
                for(i=0; playerA[i]; i++) playerA[i] = toupper(playerA[i]);
                fprintf(filePtr, "Player 1: %s\n", playerA);

                printf("\tEnter Player 2 Name: ");
                scanf(" %[^\n]s", playerB);
                for(i=0; playerB[i]; i++) playerB[i] = toupper(playerB[i]);
                fprintf(filePtr, "Player 2: %s\n", playerB);

                int num;
                num = 1;
                for(i = 0; i < 4; i++)
                    for(j = 0; j < 4; j++)
                        grid[i][j] = num++;

                char mark;
                int turn;
                int moves = 0;
                int winner = 0;
                int valid;

                for(turn = 1; turn <= 16; turn++) {
                    printf("\n\t4x4 Tic-Tac-Toe Board:\n");
                    for(i = 0; i < 4; i++) {
                        for(j = 0; j < 4; j++) {
                            if (grid[i][j] == -1) 
                                printf("|  O  ");
                            else if (grid[i][j] == 0)
                                printf("|  X  ");
                            else 
                                printf("|  %2d ", grid[i][j]);
                        }
                        printf("|\n");
                        printf("-------------------------------------\n");
                    }

                    if(turn % 2 == 1) {
                        mark = 'O';
                        printf("%s, Enter the Box Number: ", playerA);
                    } else {
                        mark = 'X';
                        printf("%s, Enter the Box Number: ", playerB);
                    }
                    scanf("%d", &box);

                    valid = 0;
                    for(i = 0; i < 4; i++) {
                        for(j = 0; j < 4; j++) {
                            if(grid[i][j] == box) {
                                grid[i][j] = (mark == 'O') ? -1 : 0;
                                valid = 1;
                                break;
                            }
                        }
                        if(valid) break;
                    }

                    if(!valid) {
                        printf("Invalid choice! Cell already taken.\n");
                        turn--; 
                        continue;
                    } else {
                        moves++; 
                    }

                    for(i = 0; i < 4; i++) {
                        if((grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][2] == grid[i][3]) ||
                           (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[2][i] == grid[3][i])) {
                            winner = (mark == 'O') ? 1 : 2;
                            break;
                        }
                    }

                    if((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[2][2] == grid[3][3]) ||
                       (grid[0][3] == grid[1][2] && grid[1][2] == grid[2][1] && grid[2][1] == grid[3][0])) {
                        winner = (mark == 'O') ? 1 : 2;
                    }

                    if (winner) {
                        if (winner == 1) 
                            printf("\nPlayer %s (O) Wins!\n", playerA);
                        else
                            printf("\nPlayer %s (X) Wins!\n", playerB);
                        break;
                    }
                }

                if (!winner)
                    printf("\nGame Over! It's a tie.\n");

                fprintf(filePtr, "Total Turns Played: %d\n", moves);
                if(winner == 1)
                    fprintf(filePtr, "Winner: %s (O)\n", playerA);
                else if(winner == 2)
                    fprintf(filePtr, "Winner: %s (X)\n", playerB);
                else 
                    fprintf(filePtr, "Winner: Game tied!\n");
                fprintf(filePtr, "--------------------------\n");

                fclose(filePtr); 
                break;

            case 2:
            {
                char searchName[50];
                printf("Enter Player Name: ");
                scanf(" %[^\n]s", searchName);
                for(i=0; searchName[i]; i++) searchName[i] = toupper(searchName[i]);

                FILE *fpRead = fopen("games_log.txt", "r");
                if (!fpRead) { printf("File not found!\n"); break; }

                char line1[100], line2[100], line3[100], line4[100];
                char pOne[50], pTwo[50], winName[50];
                int totalMoves;

                while(fgets(line1, sizeof(line1), fpRead)) {
                    fgets(line2, sizeof(line2), fpRead);
                    fgets(line3, sizeof(line3), fpRead);
                    fgets(line4, sizeof(line4), fpRead);

                    if (strstr(line1, searchName) || strstr(line2, searchName)) {
                        sscanf(line1, "Player 1: %[^\n]", pOne);
                        sscanf(line2, "Player 2: %[^\n]", pTwo);
                        sscanf(line3, "Total Turns Played: %d", &totalMoves);
                        sscanf(line4, "Winner: %[^\n]", winName);

                        printf("\n---- Match Found ----\n");
                        printf("Player 1: %s\n", pOne);
                        printf("Player 2: %s\n", pTwo);
                        printf("Turns: %d\n", totalMoves);
                        printf("Winner: %s\n", winName);
                        printf("----------------------\n");
                    }
                }
                fclose(fpRead);
                break;
            }

            case 3:
            {
                FILE *fpRead = fopen("games_log.txt", "r");
                if (!fpRead) { printf("File not found!\n"); break; }

                char line1[100], line2[100], line3[100], line4[100];
                char pOne[50], pTwo[50], winName[50];
                char players[100][50];
                int wins[100] = {0};
                int totalPlayers = 0;
                int found, p, temp;
                char tempName[50];

                while(fgets(line1, sizeof(line1), fpRead)) {
                    fgets(line2, sizeof(line2), fpRead);
                    fgets(line3, sizeof(line3), fpRead);
                    fgets(line4, sizeof(line4), fpRead);

                    sscanf(line1,"Player 1: %[^\n]",pOne);
                    sscanf(line2,"Player 2: %[^\n]",pTwo);
                    sscanf(line4,"Winner: %[^\n]",winName);

                    if(strcmp(winName,"Game tied!")!=0){
                        found=0;
                        for(i=0;i<totalPlayers;i++){
                            if(strcmp(players[i],winName)==0){ wins[i]++; found=1; break; }
                        }
                        if(!found){ strcpy(players[totalPlayers],winName); wins[totalPlayers]=1; totalPlayers++; }
                    }

                    for(p=0;p<2;p++){
                        char *cur=(p==0)?pOne:pTwo; 
                        found=0;
                        for(i=0;i<totalPlayers;i++){ if(strcmp(players[i],cur)==0){found=1; break;} }
                        if(!found){ strcpy(players[totalPlayers],cur); wins[totalPlayers]=0; totalPlayers++; }
                    }
                }
                fclose(fpRead);

                for(i=0;i<totalPlayers-1;i++){ 
                    for(j=0;j<totalPlayers;j++){
                        if(wins[i]<wins[j]){
                            temp=wins[i]; wins[i]=wins[j]; wins[j]=temp;
                            strcpy(tempName, players[i]);
                            strcpy(players[i], players[j]);
                            strcpy(players[j], tempName);
                        }
                    }
                }

                printf("\n--- TOP 3 PLAYERS (BY WINS) ---\n");
                for(i=0;i<totalPlayers && i<3;i++)
                    printf("%d. %s - Wins: %d\n",i+1,players[i],wins[i]);
                printf("---------------------------------------\n");
                break;
            }

            case 4:
                printf("\nExiting. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Choose again...\n");
                continue;
        }
    }

    return 0;
}
