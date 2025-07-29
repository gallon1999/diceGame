
// ***************** // 
// for game logic //
// ***************** //
#ifndef DICE_IMPLEMENT
#define DICE_IMPLEMENT
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICE_NUM 4

void gameSetup( void )
{

}

int gameStart(int* money, int* player_bet)
{   
    int players = 0;
    printf("type in how many players: ");
    scanf("%d", &players);

    for (int i = 0; i < players; i++) {
        money[i] = 100;
    }

    printf("player's money: ");
    for(int i = 0; i < 10; i++){
        printf("%d,",money[i]);
    }
    printf("\n");
    for (int player_num = 1;player_num < players; player_num++){
        printf("player NO.%d bet: ", player_num);
        scanf("%d", &player_bet[player_num]);
    }

    return players;
}

int roll_the_dice(int dice_number[DICE_NUM])
{
    printf("press 'enter' buttom to roll the dice!\n");
    getchar();
    getchar();
    srand(clock());
    for(int i = 0; i < 4; i++){
        int r = rand() % 6;
        dice_number[i] = r + 1;
    }
     printf("dice number is: %d %d %d %d\n", dice_number[0], dice_number[1], dice_number[2], dice_number[3]);
     return 0;
}

int calculate_score(int dice_number[DICE_NUM]) {
    int score = 0;
    int count[7] = {0};  // index 1~6 使用，代表數字 1~6 出現次數
    for (int i = 0; i < DICE_NUM; i++) {
        count[dice_number[i]]++;
    }

    int single_dice = 0;
    for(int i = 0; i < 7; i++)//判斷骰子相同次數
    {
        if(count[i] == 4)//四顆骰子點數相同
        {
            score = i + 12;
            printf("you got 4 same!\n");
            printf("your score is %d\n", score);
        }

        if(count[i] == 3)//三顆骰子點數相同
        {
            int dice_3_same = 0;
            int dice_1_diff = 0;
            dice_3_same = i;
            for(int j=0; j < 7; j++){
                if(count[j] == 1)
                dice_1_diff = j;
            }
            score = dice_3_same + dice_1_diff;
            printf("you got 3 same!\n");
            printf("your score is %d\n", score);
        }

        if(count[i] == 2)//兩顆骰子點數相同
        {   
            int pair1 = 0, pair2 = 0, single1 = 0, single2 = 0;
            pair1 = i;
            for(int j = 6; j > 0; j--)// 2 pair狀況
            {
                if(count[j] == 2 && j != pair1){
                    pair2 = j;
                    break;
                }
            }

            if(pair2 == 0)      // 1 pair + 2 signle
            {   
                int single_time = 0;
                for(int k = 0; k < 7; k++){
                    if(count[k] == 1 && single_time == 0){
                        single1 = k;
                        single_time = single_time + 1;
                    }
                    if (count[k] == 1 && single_time == 1){
                        single2 = k;
                    }
                }
                score = single1 + single2;
                printf("your score is %d\n", score);
            }

            printf("pair1 = %d\n", pair1);
            printf("pair2 = %d\n", pair2);
            printf("single1 = %d\n", single1);
            printf("single2 = %d\n", single2);

            if (pair1 != 0 && pair2 != 0){
                score = pair1 + pair2;
                printf("you got 2 pairs!\n");
                printf("your score is %d\n", score);
                break;
            }
        }

        if(count[i] == 1 && single_dice < 4)//沒有骰子點數相同
        {
            single_dice = single_dice + 1;
        }
        if(single_dice == 4){
            printf("you roll the dice with no point!\n");
            printf("press re-roll the dice\n");
            return -1;
        }
    }
    //printf("your score is %d\n", score);
    return score;
}

void print_dice(int dice_number[4]) {
    printf("Dice: ");
    for (int i = 0; i < DICE_NUM; i++) {
        printf("%d ", dice_number[i]);
    }
    printf("\n");
}

int main(){
    int money[10] = {0};                        //存放每人金錢數
    int player_bet[10] = {0};                   //存放每人下注數
    int player_score[10] = {0};                 //存放每人骰出點數
    int players = gameStart(money, player_bet);
    printf("All palyers bet, let's roll the dice!\n");
    for(int i = 0; i < players; i++){           //第n個玩家骰骰子，第一個莊家NO.0
        printf("~~~~~~~~~~~~~~Let's switch the dice~~~~~~~~~~~~~~\n");
        printf("Player NO.%d roll the dice!\n",i);
        int score = -1;
        while(score < 0){                       //骰子點數是否有效
            int dice_number[DICE_NUM] = {0};
            roll_the_dice(dice_number);
            score = calculate_score(dice_number);
            player_score[i] = score;            //將有效點數存起來
        }
        if(i == 0 ){
            printf("---------------------\n");
            printf("|Host roll %d point!|\n", player_score[0]);
            printf("---------------------\n");
        }
        if(i != 0 && player_score[i] > player_score[0]){
            printf("------------------------------------\n");
            printf("|Congratulations! You win the Host!|\n");
            printf("------------------------------------\n");
        }
        if(i != 0 && player_score[i] <= player_score[0]){
            printf("---------------------------\n");
            printf("|Oh no! You lose the Host!|\n");
            printf("---------------------------\n");
        }
    }

    return 0;
}   //test

#endif