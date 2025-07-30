
// ***************** // 
// for game logic //
// ***************** //
#ifndef DICE_IMPLEMENT
#define DICE_IMPLEMENT
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <DiceGame.h>
#include <stdint.h>

void gameSetup( void )
{

}


/** gameStart commit message > write by ChatGPT
 * Add game start function to init player data

 * This function asks the user how many players are playing
 * It then sets each player's starting money to 100

 * It prints all players' money and asks each player to enter their bet
 * (except player 0(Host)) The number of players is returned for later use
 */
int8_t gameStart(int8_t* money, int8_t* player_bet)
{   
    uint8_t players = 0;                                // init player number
    printf("type in how many players: ");
    scanf("%hhu", &players);

    for (uint8_t i = 0; i < players; i++) {
        money[i] = 100;                             // init player's money amount
    }

    printf("player's money: ");
    for(uint8_t i = 0; i < 10; i++){
        printf("%d,",money[i]);
    }
    printf("\n");
    for (uint8_t player_num = 1;player_num < players; player_num++){
        printf("player NO.%d bet: ", player_num);
        scanf("%hhu", &player_bet[player_num]);
    }

    return players;
}
/** roll_the_dice commit message > write by Gallon
 * Add dice rolling function with random values
 * 
 * Use system clock to generator random values
 * Press 'Enter' buttom to generator 4 ramdom numbers(1 ~ 6)
 * save numbers into dice_number array, and then print them in terminal
 */
int8_t roll_the_dice(int8_t* dice_number)
{
    printf("press 'enter' buttom to roll the dice!\n");
    getchar();
    getchar();
    srand(clock());
    for(uint8_t i = 0; i < 4; i++){
        uint8_t r = rand() % 6;
        dice_number[i] = r + 1;
    }
     printf("dice number is: %d %d %d %d\n", dice_number[0], dice_number[1], dice_number[2], dice_number[3]);
     return 0;
}
/** calculate_score commit message > write by Gallon
 * Add function to get score from dice roll
 * 
 * Roll 4 dice the same can get score 'dice_number' + 12
 * Roll 3 dice the same can get 'the_same_number' + 'diff_number'
 * Roll 2 pairs dice the same can get 'the_same_number' + 'the_same_number'
 * Roll 2 dice the same(with 2 different) can get 'diff_number' + 'diff_number'
 * Roll all dice different need to re-roll the dice
 * save score value for later use
 */
int8_t calculate_score(int8_t* dice_number) 
{
    int8_t score = 0;
    uint8_t count[7] = {0};  // index 1~6 使用，代表數字 1~6 出現次數
    for (uint8_t i = 0; i < DICE_NUM; i++) {
        count[dice_number[i]]++;
    }

    uint8_t single_dice = 0;
    for(uint8_t i = 0; i < 7; i++)//判斷骰子相同次數
    {
        if(count[i] == 4)//四顆骰子點數相同
        {
            score = i + 12;
            printf("you got 4 same!\n");
            printf("your score is %d\n", score);
        }

        if(count[i] == 3)//三顆骰子點數相同
        {
            uint8_t dice_3_same = 0;
            uint8_t dice_1_diff = 0;
            dice_3_same = i;
            for(uint8_t j=0; j < 7; j++){
                if(count[j] == 1)
                dice_1_diff = j;
            }
            score = dice_3_same + dice_1_diff;
            printf("you got 3 same!\n");
            printf("your score is %d\n", score);
        }

        if(count[i] == 2)//兩顆骰子點數相同
        {   
            uint8_t pair1 = 0, pair2 = 0, single1 = 0, single2 = 0;
            pair1 = i;
            for(uint8_t j = 6; j > 0; j--)// 2 pair狀況
            {
                if(count[j] == 2 && j != pair1){
                    pair2 = j;
                    break;
                }
            }

            if(pair2 == 0)      // 1 pair + 2 signle
            {   
                uint8_t single_time = 0;
                for(uint8_t k = 0; k < 7; k++){
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
            /*
            printf("pair1 = %d\n", pair1);
            printf("pair2 = %d\n", pair2);
            printf("single1 = %d\n", single1);
            printf("single2 = %d\n", single2);
            */
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
/** print_dice commit message > write by Gallon
 * Print result from roll_the_dice for debugging
 * 
 * print the dice result from roll_the_dice
 * no any value save for later use
 */
void print_dice(int8_t* dice_number) //debug用功能
{
    printf("Dice: ");
    for (uint8_t i = 0; i < DICE_NUM; i++) {
        printf("%d ", dice_number[i]);
    }
    printf("\n");
}
/** player_win_lose commit message > write by ChatGPT
 * Add function to compare score between player and host 
 * 
 * Each player rolls the dice and gets a score
 * If the score is not valid, the player rolls again
 * The score is saved and compared with the host (player 0)
 * 
 * Prints a win or lose message based on the result
 */
int player_win_lose(uint8_t players, int8_t* player_score)
{
    printf("All palyers bet, let's roll the dice!\n");
    for(uint8_t player_num = 0; player_num < players; player_num++){           //第n個玩家骰骰子，第一個莊家NO.0
        printf("~~~~~~~~~~~~~~Let's switch the dice~~~~~~~~~~~~~~\n");
        printf("Player NO.%d roll the dice!\n",player_num);
        int8_t score = -1;
        while(score < 0){                       //骰子點數是否有效
            int8_t dice_number[DICE_NUM] = {0};
            roll_the_dice(dice_number);
            score = calculate_score(dice_number);
            player_score[player_num] = score;            //將有效點數存起來
        }
        if(player_num == HOST_PLAYER ){
            printf("---------------------\n");
            printf("|Host roll %d point!|\n", player_score[0]);
            printf("---------------------\n");
        }
        if(player_num != HOST_PLAYER && player_score[player_num] > player_score[0]){
            printf("------------------------------------\n");
            printf("|Congratulations! You win the Host!|\n");
            printf("------------------------------------\n");
        }
        if(player_num != HOST_PLAYER && player_score[player_num] <= player_score[0]){
            printf("---------------------------\n");
            printf("|Oh no! You lose the Host!|\n");
            printf("---------------------------\n");
        }
    }
    return 0;
}

int main(){
    int8_t money[MAX_PLAYER] = {0};                        //save money amount for all players
    int8_t player_bet[MAX_PLAYER] = {0};                   //save every players' bet(except player 0(Host))
    int8_t player_score[MAX_PLAYER] = {0};                 //save every players' score
    int8_t players = gameStart(money, player_bet);
    player_win_lose(players, player_score);
    return 0;
}   //test

#endif