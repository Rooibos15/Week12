#define N_BOARD            13 
#define BOARDSTATUS_OK     1
#define BOARDSTATUS_NOK    0
#define N_COINPOS          10
#define MAX_COIN           4

int board_initBoard(void);
int board_getBoardStatus(int pos);
int board_getSharkPosition(void);
int board_stepShark(void);
int board_getBoardCoin(int pos);
int board_printBoardStatus(void); 

