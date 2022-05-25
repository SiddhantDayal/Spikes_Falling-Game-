#include<iostream>
#include<conio.h>
#include<dos.h>//useful functions like delay(), kbhit
#include <windows.h>// includes every standard header
#include <time.h>//to manipulate date and time operations

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int spikeY[3];
int spikeX[3];
int spikeFlag[3];
char man[4][4] = { ' ',' ',' ',' ',
					'(','o','o',')',
					'|','x','x','|',
					'_','|','|','_' };

int manPos = WIN_WIDTH/2;
int score = 0;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"@";
			gotoxy(WIN_WIDTH-j,i); cout<<"@";
		}
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"�";
	}
}
void genSpike(int ind){
	spikeX[ind] = 17 + rand()%(33);
}
void drawSpike(int ind){
	if( spikeFlag[ind] == true ){
		gotoxy(spikeX[ind], spikeY[ind]);   cout<<"     ";
		gotoxy(spikeX[ind], spikeY[ind]+1); cout<<"     ";
		gotoxy(spikeX[ind], spikeY[ind]+2); cout<<" *** ";
		gotoxy(spikeX[ind], spikeY[ind]+3); cout<<"  *  ";
	}
}
void eraseSpike(int ind){
	if( spikeFlag[ind] == true ){
		gotoxy(spikeX[ind], spikeY[ind]); cout<<"    ";
		gotoxy(spikeX[ind], spikeY[ind]+1); cout<<"    ";
		gotoxy(spikeX[ind], spikeY[ind]+2); cout<<"    ";
		gotoxy(spikeX[ind], spikeY[ind]+3); cout<<"    ";
	}
}
void resetSpike(int ind){
	eraseSpike(ind);
	spikeY[ind] = 1;
	genSpike(ind);
}

void drawMan(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+manPos, i+22); cout<<man[i][j];
		}
	}
}
void eraseMan(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+manPos, i+22); cout<<" ";
		}
	}
}

int collision(){
	if( spikeY[0]+4 >= 23 ){
		if( spikeX[0] + 4 - manPos >= 0 && spikeX[0] + 4 - manPos < 9  ){
			return 1;
		}
	}
	return 0;
}
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t---------------------------------------"<<endl;
	cout<<"\t\t------You Have Perished in the well-----"<<endl;
	cout<<"\t\t---------------------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back AND TRY AGAIN.";
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n You have fallen into a well and you need to survive until help may arrive";
	cout<<"\n\n Make sure to avoid the falling spikes by dodging left and right";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}
void wincond(){
    system("cls");
    cout<<"---------------CONGRATULATIONS--------------";
    cout<<" \n▬▬▬.◙.▬▬▬\n ═▄▄▓▄▄\n █▀▀████▄▄▄▄\n█▄█ █▄███▀▀▀▀▀▀▀╬\n█████\n══╩══╩═\n ╬═╬\n ╬═╬\n ╬═╬\n ╬═╬\n ╬═╬\n ╬═╬ ☻/\n ╬═╬/▌\n ╬═╬/\n";
    cout<<"\n\n\n\n------------------------------You have been rescued-----------------------------";
    cout<<"\n\n\n\nPress any key to go back to menu";
	getch();
    }
void play(){
	manPos = -1 + WIN_WIDTH/2;
	score = 0;
	spikeFlag[0] = 1;
	spikeFlag[1] = 0;
	spikeY[0] = spikeY[1] = 1;

	system("cls");
	drawBorder();
	updateScore();
	genSpike(0);
	genSpike(1);

	gotoxy(WIN_WIDTH + 7, 2);cout<<"Well Game";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
	gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
	gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";
	gotoxy(WIN_WIDTH + 2, 16);cout<<"Made By-";
	gotoxy(WIN_WIDTH + 2, 17);cout<<"Siddhant";
	gotoxy(WIN_WIDTH + 2, 18);cout<<"Hitarth";
	gotoxy(WIN_WIDTH + 2, 19);cout<<"Jasbir";

	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";

	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( manPos > 18 )
					manPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( manPos < 50 )
					manPos += 4;
			}
			if(ch==27){
				break;
			}
		}

		drawMan();
		drawSpike(0);
		drawSpike(1);
		if( collision() == 1  ){
			gameover();
			return;
		}
		Sleep(50);
		eraseMan();
		eraseSpike(0);
		eraseSpike(1);

		if( spikeY[0] == 10 )
			if( spikeFlag[1] == 0 )
				spikeFlag[1] = 1;

		if( spikeFlag[0] == 1 )
			spikeY[0] += 1;

		if( spikeFlag[1] == 1 )
			spikeY[1] += 1;

		if( spikeY[0] > SCREEN_HEIGHT-4 ){
			resetSpike(0);
			score++;
			updateScore();
		}
		if( spikeY[1] > SCREEN_HEIGHT-4 ){
			resetSpike(1);
			score++;
			updateScore();
		}
		if(score>999){
            wincond();
            break;
		}
	}
}

int main()
{
	setcursor(0,0);
	srand( (unsigned)time(NULL));

	do{
		system("cls");
		gotoxy(10,5); cout<<" --------------------------------------";
		gotoxy(10,6); cout<<" |     You Have Fallen into a Well     | ";
		gotoxy(10,7); cout<<" --------------------------------------";
		gotoxy(10,9); cout<<"a. Start Game";
		gotoxy(10,10); cout<<"b. Story and Controls";
		gotoxy(10,11); cout<<"c. Quit";
		gotoxy(10,13); cout<<"Select option: ";
		char op = getche();

		if( op=='a') play();
		else if( op=='b') instructions();
		else if( op=='c') exit(0);

	}while(1);

	return 0;
}

