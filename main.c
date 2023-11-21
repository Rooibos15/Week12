#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DIE     6

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void opening(void){
	printf("==========================================\n");
	printf("================shark game================\n");
	printf("==========================================\n");
}

int rolldie(void)
{
	return rand()%MAX_DIE+1; 
}
int main(int argc, char *argv[]) {
	
	int pos = 0;
	srand((unsigned)time(NULL));
	
	//0. 오프닝 
	opening();
	
	//1. 초기화 및 플레이어 이름 결정
	board_initBoard();
		
	//2. 반복문(플레이어 턴)
	do {
	    int step = rolldie();
	    int coinResult;
	    char c;
	    
	    board_printBoardStatus();
	    
	    pos += step;
	    coinResult = board_getBoardCoin(pos);
	    
	    printf("press any key to continue:");
	    scanf("%d", &c);
	    fflush(stdin);
	    
	 //2-1. 플레이어 상태 출력 
	 //2-2. 주사위 던지기
	 //2-3. 이동
	 //2-4. 코인 줍기
	 //2-5. 다음 턴으로 돌림
	 //2-6. if (조건은 모든 플레이어가 한 번씩 돌았을 때){상어 동작}
    } while(1);
	//3. 정리(승자 계싼 및 출력) 
	 
	 
	 
	  
	return 0;
}
