
#include <iostream>
#include <string>
using namespace std;

enum enGameOptions { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, NoWinner = 3 };

struct stGameResults
{ 
	short GameRounds = 0 ;
	short  Player1WinTimes = 0 ;
	short Computer2WinTimes = 0 ;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName="";
};

struct stRoundInfo
{
	short RoundNumber = 0;	
	enGameOptions Player1Choice;
	enGameOptions Computer2Choice;
	enWinner RoundWinner;
	string WinnerName = "";
};

string Tabs(int NumberOfSpaces) 
{
	string t = "";
	for(int i =1; i<=NumberOfSpaces; i++)
		t += "\t";
	return t;
}

short Random(short From, short To) 
{
	return rand() % (To - From + 1) + From;
}

enGameOptions ReadPlayer1Choice()
{
	short PlayerChoice;
	do
	{
		cout << "what is your choice ? [1]Stone , [2]Paper , [3]Scissors\n";
		cin >> PlayerChoice;
	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameOptions)PlayerChoice;
}

enGameOptions GenerateComputerChoice()
{
	return (enGameOptions)Random(1, 3);
}

enWinner WhoWinTheRound(stRoundInfo Round)
{
	if(Round.Player1Choice==Round.Computer2Choice)
		return enWinner::NoWinner;

	switch (Round.Player1Choice)
	{
	case enGameOptions::Stone:
		if (Round.Computer2Choice == enGameOptions::Paper)
			return enWinner::Computer;
	case enGameOptions::Paper:
		if (Round.Computer2Choice == enGameOptions::Scissors)
			return enWinner::Computer;
	case enGameOptions::Scissors:
		if (Round.Computer2Choice == enGameOptions::Stone)
			return enWinner::Computer;
	}
	return enWinner::Player;
}

string WinnerName(enWinner Winner)
{
	string PlayersName[3] = { "Player", "Computer", "NoWinner" };
	return PlayersName[Winner - 1];
}

string ChoiceName(enGameOptions Choice)
{
	string ArrGameChoices[3] = { "Stone", "Paper", "Scissors" };
	return ArrGameChoices[Choice - 1];
}

void SetColor(enWinner Winner) 
{
	switch (Winner)
	{
		case enWinner::Player:
			system("color 2F"); // Set color to green
			break;
		case enWinner::Computer:
			system("color 4F"); // Set color to red
			cout << "\a"; // Beep sound
			break;
		case enWinner::NoWinner:
			system("color 6F"); // Set color to yellow
			break;
	}
}
void ShowRoundInfo(stRoundInfo Round) 
{
	cout << "\n____________Round[" << Round.RoundNumber << "]_____________\n\n";
	cout << "Player choice is : " << ChoiceName(Round.Player1Choice) << endl;
	cout << "Computer choice is : " << ChoiceName(Round.Computer2Choice) << endl;
	cout << "Round Winner :  [" << Round.WinnerName <<"]"<< endl;
	cout << "____________________________________\n" << endl;

	SetColor(Round.RoundWinner);
}

short GameRounds()
{
	short Rounds = 1;
	do
	{
		cout << "How many rounds do you want to play? \n";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds >10);
	return Rounds;
}

enWinner WhoWinTheGame(short Player1WinTimes, short Computer2WinTimes)
{
   if(Player1WinTimes > Computer2WinTimes)
	   return enWinner::Player;
   else if (Computer2WinTimes > Player1WinTimes)
	   return enWinner::Computer;
   else
	   return enWinner::NoWinner;
}

stGameResults FillFinalGameResults(  short GameRounds, short Player1WinTimes , short Computer2WinTimes , short DrawTimes)
{
	stGameResults FinalResults; 

	FinalResults.GameRounds = GameRounds;
	FinalResults.Player1WinTimes = Player1WinTimes;
	FinalResults.Computer2WinTimes = Computer2WinTimes;
	FinalResults.DrawTimes = DrawTimes;
	FinalResults.GameWinner = WhoWinTheGame(Player1WinTimes , Computer2WinTimes);
	FinalResults.WinnerName = WinnerName(FinalResults.GameWinner);

	return FinalResults;

}

stGameResults PlayGame(short GameRounds) 
{
	stRoundInfo Round;
	short Player1WinTimes = 0, Computer2WinTimes = 0, DrawTimes = 0;

	for (int GameRound = 1; GameRound <= GameRounds; GameRound++)
	{
		cout << endl << "Round[" << GameRound << "] begins : \n\n";
		Round.RoundNumber = GameRound;
		Round.Player1Choice = ReadPlayer1Choice();
		Round.Computer2Choice = GenerateComputerChoice();
		Round.RoundWinner = WhoWinTheRound(Round);
		Round.WinnerName = WinnerName(Round.RoundWinner);

		if(Round.RoundWinner == enWinner::Player)
			Player1WinTimes++;
		else if (Round.RoundWinner == enWinner::Computer)
			Computer2WinTimes++;
		else
			DrawTimes++;

		ShowRoundInfo(Round);
	}

	return FillFinalGameResults( GameRounds,Player1WinTimes , Computer2WinTimes , DrawTimes);
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "------------------------------------------------------------\n\n";
	cout << Tabs(2) << "                      *** G A M E O V E R *** \n\n";
	cout << Tabs(2) << "------------------------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults) 
{
	cout << Tabs(2) << "******************** F I N A L  R E S U L T S ********************\n\n";
	cout << Tabs(2) << "Total Rounds = " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player Win Times = " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Win Times = " << GameResults.Computer2WinTimes << endl;
	cout << Tabs(2) << "Draw Times = " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Game Winner is : [" << GameResults.WinnerName << "]\n";

	SetColor(GameResults.GameWinner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	 char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(GameRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout <<endl << Tabs(3)<< "Do you want to play again? (y/n) ?\n";
		cin >>PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}



int main()
{
	srand((unsigned)time(NULL));

	 StartGame();
}

