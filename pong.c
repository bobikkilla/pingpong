//I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI

#include <stdio.h>

void draw_field();
void game();
int action();

void main() {
    game();               
    return;
}

void draw(int ball_x, int ball_y, int left_rak_pos, int right_rak_pos,int score_left, int score_right) {
    printf("\033c");    //очистил всё, вернул курсор в начало
    for(int i = 0; i <= 26; i++) {      // рисую поле
        for(int j = 0; j <= 85; j++) {
            if(i == 0 || i == 26) {
                printf("#");
            }
            else if(j == 0 || j == 85) {
                printf("$");
            }
            else {
            printf(" ");
            }
        }
        printf("\n");
    }
    
    printf("\033[%d;%df@", ball_y, ball_x); //напечатали мяч

    printf("\033[%d;4f|", left_rak_pos-1);
    printf("\033[%d;4f|", left_rak_pos);     // печатаю левую ракетку
    printf("\033[%d;4f|", left_rak_pos+1);

    printf("\033[%d;83f|", right_rak_pos-1);
    printf("\033[%d;83f|", right_rak_pos);     // печатаю правую ракетку
    printf("\033[%d;83f|", right_rak_pos+1);

    printf("\033[29;15f First Player : %d", score_left);
    printf("\033[30;15f Second Player: %d", score_right);   // напечатали очки игроков
 
}

void game() {
    int ball_x = 44, ball_y = 13;
    int ball_dir_x = 1, ball_dir_y = 1;                                   
    int left_rak_pos = 14, right_rak_pos = 14;
    int score_right = 0, score_left = 0;
    int input = -1;
    
    while (1)
    {   
        draw(ball_x, ball_y, left_rak_pos, right_rak_pos,score_left, score_right);

        input = action();

        switch(input) {     // расчёт движения ракеток 
            case 1:
                if (left_rak_pos < 25) left_rak_pos++; // Используйте максимально возможную позицию для ракетки
                break;
            case 2:
                if (left_rak_pos > 3) left_rak_pos--; // Не позволяйте ракетке выходить за нижнюю границу
                break;
            case 3:
                if (right_rak_pos < 25) right_rak_pos++;
                break;
            case 4:
                if (right_rak_pos > 3) right_rak_pos--;
                break;
            case 0:
                break;
        }

        
        ball_x = ball_x + ball_dir_x;
        ball_y = ball_y + ball_dir_y;   // считаю положение мяча

        if(ball_y == 2) {
            ball_dir_y = 1;
        }
        else if(ball_y == 26) {         // расчёт для изменения направления по ординате
            ball_dir_y = -1;
        }

        if(ball_x == 82 && (ball_y == right_rak_pos || ball_y == right_rak_pos+1 || ball_y == right_rak_pos-1)) {
            ball_dir_x = -1;
        }
        else if(ball_x == 5 && (ball_y == left_rak_pos || ball_y == left_rak_pos+1 || ball_y == left_rak_pos-1)) { 
            ball_dir_x = 1;
        }
                                        // расчёт для изменения направления по абсциссе

        if(ball_x == 3) {
            score_right++;
            ball_x = 44, ball_y = 13;
            ball_dir_x = -1, ball_dir_y = 1; 
        }
        if(ball_x == 85) {              // событие: забит гол(здесь расписано всё для обоих сторон)
            score_left++;
            ball_x = 44, ball_y = 13;
            ball_dir_x = 1, ball_dir_y = -1; 
        }
        
        if(score_left == 21) {
            printf("\033c");
            printf("Player ONE won!\n Congratulations!!!\n");
            break;
        }
        else if(score_right == 21) {    // условия победы
            printf("\033c");
            printf("Player TWO won!\nCongratulations!!!\n");
            break;
        }
    }

    return;                
};   

int action() {
    int bazalbek,ch, ch2;
    printf("\033[35;0H write action + enter(a,z to move left racket, k,m to move right racket, space for skip): (\n ");
    ch = getchar();
    while(getchar() != '\n');
    switch(ch) {
        case 32: 
            bazalbek = 0; 
            break;
        case 97:
            bazalbek = 2;
            break;
        case 122:
            bazalbek = 1; 
            break;
        case 107:
            bazalbek = 4;
            break;
        case 109: 
            bazalbek = 3; 
            break;
        default: 
            bazalbek = -1;
            break;
    }
    return bazalbek;
}
