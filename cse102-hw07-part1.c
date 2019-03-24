#include <stdio.h>

typedef enum {white_man='w', black_man='b', white_king='W', black_king='B', empty='-'} piece;
typedef enum {white = 10, black = 20} player;

void init_board(piece board[][8]);
void display_board(piece board[][8]);
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player *p);
int check_end_of_game(piece board[][8]);
int black_man_eat(piece board[][8]);
int white_man_eat(piece board[][8]);
int black_king_eat(piece board[][8]);
int white_king_eat(piece board[][8]);

/* this game is useful to play with two players. ı couldn't done samples.*/

int main(){
	int i,k=0,from_x,from_y,to_x,to_y,control=0,fault_move;
	piece board[8][8];
	init_board(board);
	display_board(board);

	for(i=10;k==0;i+=10){
		if(i%20==10){
			printf("\nWhite player choose your man by using coordinates:");
			scanf("%d %d",&from_x,&from_y);
			printf("\nWhere do you want to swap your man by using coordinates:");
			scanf("%d %d",&to_x,&to_y);
		}
		else if(i%20==0){
			printf("\nBlack player choose your man by using coordinates:");
			scanf("%d %d",&from_x,&from_y);
			printf("\nWhere do you want to swap your man by using coordinates:");
			scanf("%d %d",&to_x,&to_y);
		}
		fault_move=move(board,from_x,from_y,to_x,to_y,&i);
		if(fault_move==-1 || fault_move==-2){
			if(i%20==10){
				printf("\nWhite player you did invalid move. Because of Black player Win!!\n");
				k++;
			}
			else{
				printf("\nBlack player you did invalid move. Because of White player Win!!\n");
				k++;
			}
		}		
	
		display_board(board);
		control=check_end_of_game(board);
		if(control==10){
			printf("\nWhite player win the game!!");
			k++;
		}
		else if(control==20){
			printf("\nBlack player win the game!!");
			k++;
		}	
	}
	
}

void init_board(piece board[][8]){
	int i,j;
	piece temp_board[9][9]={
						   { empty,empty,empty,empty,empty,empty,empty,empty},
						   { black_man,black_man,black_man,black_man,black_man,black_man,black_man,black_man},
						   { black_man,black_man,black_man,black_man,black_man,black_man,black_man,black_man},
						   { empty,empty,empty,empty,empty,empty,empty,empty},
						   { empty,empty,empty,empty,empty,empty,empty,empty},
						   { white_man,white_man,white_man,white_man,white_man,white_man,white_man,white_man},
						   { white_man,white_man,white_man,white_man,white_man,white_man,white_man,white_man},  
						   { empty,empty,empty,empty,empty,empty,empty,empty}
						   														};
			   														
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			board[i][j]=temp_board[i][j];
		}
	}
}
					
void display_board(piece board[][8]){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player *p){
	int i,j,m,eaten=0,pool=0;
	if(*p%20==10){/*white man*/
		if(board[from_x][from_y]!=white_king){	
			if(board[from_x][from_y]!=white_man && board[from_x][from_y]!=white_king) return -1;
			else if(board[to_x][to_y]==white_man || board[to_x][to_y]==white_king) return -2;
			else if(from_x-to_x>1) return -2;
			else if(from_y-to_y>1 && from_y-to_y<-1) return -2;		
		}
		if(board[to_x][to_y]==empty){
			board[to_x][to_y]=white_man;
			board[from_x][from_y]=empty;
		}
		
		do{
			eaten=black_man_eat(board);
			pool+=eaten;
		}while(eaten!=0);

		
		
		do{
			eaten=black_king_eat(board);
			pool+=eaten;	
		}while(eaten!=0);
		
		
	}	
			
	else if(*p%20==0){/*black man*/	
		if(board[from_x][from_y]!=black_king){	
			if(board[from_x][from_y]!=black_man && board[from_x][from_y]!=black_king) return -1;
			else if(board[to_x][to_y]==black_man || board[to_x][to_y]==black_king) return -2;
			else if(to_x-from_x>1) return -2;
			else if(from_y-to_y>1 && from_y-to_y<-1) return -2;
		}
		if(board[to_x][to_y]==empty){
			board[to_x][to_y]=black_man;
			board[from_x][from_y]=empty;
		}
		
		do{
			eaten=white_man_eat(board);
			pool+=eaten;
		}while(eaten!=0);
		
		do{
			eaten=white_king_eat(board);
			pool+=eaten;
		}while(eaten!=0);
	}
	
	
		
	for(i=0;i<8;i++){
		if(board[0][i]==white_man){
			board[0][i]=white_king;
		}
		if(board[7][i]==black_man){
			board[7][i]=black_king;
		}
	}
	
	if(pool!=0){
		*p+=10;
	 }	

}

int check_end_of_game(piece board[][8]){				   	
	
	int i,j,black_counter=0,white_counter=0;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==black_man || board[i][j]== black_king) black_counter++;
			else if(board[i][j]==white_man || board[i][j]==white_king) white_counter++;
		}
	}
	
	if(16-black_counter==16) return white;
	else if(16-white_counter==16) return black;
	else return -1;
}


int black_man_eat(piece board[][8]){
	int i,j,eaten=0;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==black_man){
				while(board[i+1][j]==white_man && board[i+2][j]==empty || board[i+1][j]==white_king && board[i+2][j]==empty){
					board[i+1][j]=empty;
					board[i+2][j]=black_man;
					board[i][j]=empty;
					eaten++;		
				}
			}
		}
	}
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j]==black_man){
				while(board[i][j+1]==white_man && board[i][j+2]==empty || board[i][j+1]==white_king && board[i][j+2]==empty ){
					board[i][j+1]=empty;
					board[i][j+2]=black_man;
					board[i][j]=empty;
					eaten++;
				}
				while(board[i][j-1]==white_man && board[i][j-2]==empty || board[i][j-1]==white_king && board[i][j-2]==empty ){
					board[i][j-1]=empty;
					board[i][j-2]=black_man;
					board[i][j]=empty;
					eaten++;
				}
			}
		}
	}
	return eaten;
}

int white_man_eat(piece board[][8]){
	int i,j,eaten=0;
	for(i=7;i>=0;i--){
		for(j=7;j>=0;j--){
			if(board[i][j]==white_man){
				while(board[i-1][j]==black_man && board[i-2][j]==empty || board[i-1][j]==black_king && board[i-2][j]==empty){
					board[i-1][j]=empty;
					board[i-2][j]=white_man;
					board[i][j]=empty;
					eaten++;						
				}
			}
		}
	}
		
	for(i=7;i>=0;i--){
		for(j=7;j>=0;j--){
			if(board[i][j]==white_man){
				while(board[i][j+1]==black_man && board[i][j+2]==empty || board[i][j+1]==black_king && board[i][j+2]==empty ){
					board[i][j+1]=empty;
					board[i][j+2]=white_man;
					board[i][j]=empty;
					eaten++;
				}
				while(board[i][j-1]==black_man && board[i][j-2]==empty || board[i][j-1]==black_king && board[i][j-2]==empty ){
					board[i][j-1]=empty;
					board[i][j-2]=white_man;
					board[i][j]=empty;
					eaten++;
				}
			}
		}
	}
	return eaten;
}

int black_king_eat(piece board[][8]){
	int i,j,m,eaten=0;
	for(i=7;i>=0;i--){
			for(j=7;j>=0;j--){
				if(board[i][j]==black_king){
					for(m=0;m<8;m++){
						while(j<m && board[i][m]==white_man && board[i][m+1]==empty || board[i][m+1]==empty && board[i][m]==white_king ){
							board[i][j]=empty;
							board[i][m+1]=black_king;
							board[i][m]=empty;
							eaten++;
						}
						while(j>m && board[i][m]==white_man && board[i][m-1]==empty || board[i][m-1]==empty && board[i][m]==white_king ){
							board[i][j]=empty;
							board[i][m-1]=black_king;
							board[i][m]=empty;
							eaten++;
						}	
					}
			
					for(m=0;m<8;m++){
						while(i<m && board[m][j]==white_man && board[m+1][j]==empty || board[m+1][j]==empty && board[m][j]==white_king ){
							board[i][j]=empty;
							board[m+1][j]=black_king;
							board[m][j]=empty;
							eaten++;
						}
						while(i>m && board[m][j]==white_man && board[m-1][j]==empty || board[m-1][j]==empty && board[m][j]==white_king ){
							board[i][j]=empty;
							board[m-1][j]=black_king;
							board[m][j]=empty;
							eaten++;
						}
					}
				}
			}
	}
	return eaten;
}

int white_king_eat(piece board[][8]){
	int i,j,m,eaten=0;
	for(i=7;i>=0;i--){
		for(j=7;j>=0;j--){		
			if(board[i][j]==white_king){
				for(m=0;m<8;m++){
					if(j<m && board[i][m]==black_man && board[i][m+1]==empty || board[i][m+1]==empty && board[i][m]==black_king ){
						board[i][j]=empty;
						board[i][m+1]=white_king;
						board[i][m]=empty;
						eaten++;
					}
					if(j>m && board[i][m]==black_man && board[i][m-1]==empty || board[i][m]==black_king && board[i][m-1]==empty ){
						board[i][j]=empty;
						board[i][m-1]=white_king;
						board[i][m]=empty;
						eaten++;
					}	
				}
			
				for(m=0;m<8;m++){
					if(i<m && board[m][j]==black_man && board[m+1][j]==empty || board[m+1][j]==empty && board[m][j]==black_king ){
						board[i][j]=empty;
						board[m+1][j]=white_king;
						board[m][j]=empty;
						eaten++;
						
					}
					if(i>m && board[m][j]==black_man && board[m-1][j]==empty || board[m-1][j]==empty && board[m][j]==black_king ){
						board[i][j]=empty;
						board[m-1][j]=white_king;
						board[m][j]=empty;
						eaten++;
					}
				}
			}
										
		}
	}
	return eaten;
}

/*	void sample_game_1();	*/
/*  void sample_game_2();   */
