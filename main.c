#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME 200
#define N_PLAYER    3 
#define MAX_DIE     6

#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];//0-live, 1-die, 2-end
char player_statusString[3][MAX_CHARNAME] = {"LIVE", "DIE", "END"};



void opening(void){
	printf("==========================================\n");
	printf("================shark game================\n");
	printf("==========================================\n");
}

int rolldie(void)
{
	return rand()%MAX_DIE+1; 
}

void printPlayerPosition(int player)
{
	int i;
	for(i=0; i<N_BOARD; i++)
	{
		printf("|");
		if(i == player_position[player]) 
		   printf("%c", player_name[player][0]);
		else
		{
			if(board_getBoardStatus(i) == BOARDSTATUS_NOK)
			  printf("X");
			else
		 	  printf(" "); 
		}   		   
	}
	printf("|\n");
}

void printPlayerStatus(void)
{
	int i;
	for(i=0; i<N_PLAYER; i++)
	{
		printf("%s : pos %i, coin %i, status : %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
	}
	printf("----------------------\n");
}

void checkDie(void)
{
	int i;
	for(i=0; i<N_PLAYER; i++)
	{
		if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
		  player_status[i] = PLAYERSTATUS_DIE;
		  printf("%s died", player_name[i]);
	}
}

int game_end(void)
{
	int i;
	int flag_end = 1;
	
	//전 플레이어 사망
	for (i=0; i<N_PLAYER; i++)
	{
		if(player_status[i] == PLAYERSTATUS_LIVE)
		{
			flag_end = 0;
			break;
		}
	} 
	
	return flag_end;
}

int getAlivePlayer(void)
{
	int i;
	int cnt = 0;
	for (i=0; i<N_PLAYER; i++)
	{
		if(player_status[i] == PLAYERSTATUS_END)
		   cnt++;
	}
	
	return cnt;
}

int getWinner(void)
{
	int i;
	int winner = 0;
	int max_coin = -1;
	
	for(i=0; i<N_PLAYER; i++)
	{
		if(player_coin[i] > max_coin)
		 {
		 	max_coin = player_coin[i];
		 	winner = i;
		 }
	}
	
	return winner;
}

int main(int argc, char *argv[]) {
	
	int pos = 0;
	int i;
	int turn = 0;
	
	srand((unsigned)time(NULL));
	
	//0. 오프닝 
	opening();
	
	//1. 초기화 및 플레이어 이름 결정
	board_initBoard();
	//1-2.
	for(i=0; i<N_PLAYER;i++)
	{
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		//player_name
		printf("Player %i's name: ", i);
		scanf("%s", player_name[i]);
	}
		
	//2. 반복문(플레이어 턴)
	do {
	    int step = rolldie();
	    int coinResult;
	    char c;	   
		
		if (player_status[turn] != PLAYERSTATUS_LIVE)
		{
		  turn = (turn + 1)%N_PLAYER;
		  continue;		        
		}         
	      
	    
	 //2-1. 플레이어 상태 출력 
	 board_printBoardStatus();
	 for(i=0; i<N_PLAYER; i++)
	 	printPlayerPosition(turn);
	 printPlayerStatus();
	 
	 	 
	 //2-2. 주사위 던지기
	 printf("%s turn!", player_name[turn]);
	 printf("press any key to continue:");
	 scanf("%d", &c);
	 fflush(stdin);	 
	 step = rolldie();
	 
	 
	 //2-3. 이동
	 player_position[turn] += step;
	 if(player_position[turn] >= N_BOARD)
	    {
	    	player_position[turn] = N_BOARD-1;	    
	    }
	 if(player_position[turn] == N_BOARD)
	    {
	       	player_status[turn] = PLAYERSTATUS_END;
		}	
	
	 printf("Die result : %i, %s moved to %i\n", step, player_name[turn], player_position[turn]);
	 
	 
	 //2-4. 코인 줍기
	 coinResult = board_getBoardCoin(pos);
	 player_coin[turn] += coinResult;
	 printf("%s gets %i coins!\n", player_name[turn], board_getBoardCoin(pos));
	 
	 
	 //2-5. 다음 턴으로 돌림
	 turn = (turn + 1)%N_PLAYER;//wrap around
	 
	 //2-6. if (조건은 모든 플레이어가 한 번씩 돌았을 때){상어 동작}
	 if(turn == 0)
	 {
	 	//상어 동작
		int shark_pos = board_stepShark();
		printf("The shark moved!\n");
		checkDie(); 
	 }
    } while(game_end() == 1);
	//3. 정리(승자 계산 및 출력) 
	 
	 if(game_end() == 1)
	 {
	 printf("Alive player: %i\n", getAlivePlayer());
	 printf("Winner: player %i\n", getWinner());
     }
	 
	system("pause");
	return 0;
}
