#include "GameBoard.cpp"
#include "GameAI.cpp"
#include "PairValues.cpp"

namespace connectreveresi
{

	void connectreveresi::main(std::vector<std::wstring> &args)
	{
		// TODO code application logic here

		//Game prompt
		std::wcout << L"Welcome to connect Reversi! To move enter an integer 1-7." << std::endl;
		std::wcout << L"The object is to have your pieces occupy the most spaces!" << std::endl;
		std::wcout << L"Good luck" << std::endl;

		//Create required objects.
		GameBoard *game = new GameBoard();
		GameAI *robot = new GameAI();
		game->printBoard();

		Scanner *keyreader = new Scanner(System::in);

		int playerStatus = 1; //Player 1 goes first.

		while (!game->isGameDone())
		{

			int move;

			if (playerStatus == 1)
			{ //Get Robot move.


				GameBoard *temp = new GameBoard(); //Clone the board. This is java specific.
				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						temp->setLocation(i, j, game->getSymbol(i, j));
					}
				}

				PairValues *x = robot->maxValue(temp, -9999999, 9999999, 0, 10); // Gain a move value/pair.  //If runs too slow, change 10 to something lower.
				std::wcout << L"Calculated number: " << robot->getTotalMoves() << std::endl; //Print total moves calculated.
				robot->resetMoves(); //Reset move counter.
				move = x->getPosition() + 1; //Make a move set that's 0-6 to 1-7 for easier input.
			}
			else
			{ // Get player move.
				std::wstring command = keyreader->next();
				if (command.equalsIgnoreCase(L"quit"))
				{
					break;
				}
				move = std::stoi(command);
			}

			while (move < 1 || move > 7 || !game->makeMove(move - 1, playerStatus))
			{ //Check for valid moves.
				std::wcout << L"Your move is off the board. Please try again. Valid moves are 1-7" << std::endl;
				move = keyreader->nextInt();

			}
			game->printBoard(); // Show board.

			if (playerStatus == 1)
			{
				playerStatus = 2;
			}
			else if (playerStatus == 2)
			{
				playerStatus = 1;
			}

		}
		int winner = game->checkWinner(); //Calc winner.

		if (winner == 1)
		{
			std::wcout << L"The robot won" << std::endl;
		}
		else
		{
			std::wcout << L"The player  won" << std::endl;
		}


	}
}
