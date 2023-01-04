#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearConsole()
{
	system("clear");
}

void randomSeed()
{
	time_t clock;
	time(&clock);
	srand(clock);
}

void clearInputStream()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

char toUppercase(char c)
{
	if (c >= 'a')
	{
		return c - ('a' - 'A');
	}

	return c;
}

char toLowercase(char c)
{
	if (c < 'a')
	{
		return c + ('a' - 'A');
	}

	return c;
}

enum Hand
{
	Rock,
	Paper,
	Scissors,
	Null = -1
};

Hand intToHand(int i)
{
	switch (i)
	{
		case 0:
			return Rock;
			break;
		case 1:
			return Paper;
			break;
		case 2:
			return Scissors;
			break;
		default:
			return Null;
	}
}

const char* handToString(Hand hand)
{
	switch (hand)
	{
		case Rock:
			return "rock";
			break;
		case Paper:
			return "paper";
			break;
		case Scissors:
			return "scissors";
			break;
		default:
			return "null";
	}
}

enum Result
{
	Win,
	Loss,
	Draw
};

Result getResult(Hand playerHand, Hand cpuHand)
{
	if (playerHand == cpuHand)
	{
		return Draw;
	}

	if (playerHand == Rock     && cpuHand == Scissors
	    ||
	    playerHand == Paper    && cpuHand == Rock
	    ||
	    playerHand == Scissors && cpuHand == Paper)
	{
		return Win;
	}

	return Loss;
}

int main()
{
	Hand playerHand, cpuHand;
	unsigned int playerScore, cpuScore, draws;

	bool playing = true;

	clearConsole();
	printf("Rock, paper, scissors in C!\n");

	while (playing)
	{
		playerHand = Null;
		while (playerHand == Null)
		{
			printf("Rock[r], paper[p], or scissors[s]? -> ");
			char c = getchar();
			c = toLowercase(c);
			clearInputStream();
			switch (c)
			{
				case 'r':
					playerHand = Rock;
					break;
				case 'p':
					playerHand = Paper;
					break;
				case 's':
					playerHand = Scissors;
					break;
			}
		}

		randomSeed();
		cpuHand = intToHand(rand() % 3);

		Result result = getResult(playerHand, cpuHand);
		printf("%s%s%s%s%s", "You chose ", handToString(playerHand), " and CPU chose ", handToString(cpuHand), ".\n");
		switch (result)
		{
			case Win:
				printf("You won! :)\n");
				playerScore++;
				break;
			case Loss:
				printf("You lost... :(\n");
				cpuScore++;
				break;
			case Draw:
				printf("Draw. :|\n");
				draws++;
				break;
		}
		printf("%s%u%s", "Your score: ", playerScore, "\n");
		printf("%s%u%s", "CPU score: ", cpuScore, "\n");
		printf("%s%u%s", "Draws: ", draws, "\n");

		while (true)
		{
			printf("Want to play again? [y/n]? -> ");
			char c = getchar();
			c = toLowercase(c);
			clearInputStream();
			if (c == 'y')
			{
				break;
			}
			else if (c == 'n')
			{
				playing = false;
				break;
			}
		}
	}
	printf("Thank you for playing!\n");

	return 0;
}
