#include <iostream>
#include <vector>

using namespace std;

struct QueenConfig
{
	int x;
	int y;
};

bool isUnguarded(int boardSize, int x, int y, const vector<QueenConfig>& config);
void addQueen(int x, int y, vector<QueenConfig>& config);
bool solveFromConfig(int boardSize, vector<QueenConfig>& config);
void removeQueen(int x, int y, vector<QueenConfig>& config);


int main(int argc, char* argv[])
{
	// Board is considered to be square
	int boardSize = 8;
	vector<QueenConfig> config;

	solveFromConfig(boardSize, config);

	return 0;
}

bool isUnGuarded(int boardSize, int x, int y, const vector<QueenConfig>& config)
{
	for (int index = 0; index < config.size(); ++index)
	{
		if (config[index].x == x)
		{
			return false;
		}

		if (config[index].y == y)
		{
			return false;
		}

		// Forward diagonal
		int xDir = x + 1;
		int yDir = y + 1;
		while (xDir < boardSize && yDir < boardSize)
		{
			if (config[index].x == xDir
				&& config[index].y == yDir)
			{
				return false;
			}
			
			++xDir;
			++yDir;
		}

		//Backward diagonal x
		xDir = x - 1;
		yDir = y - 1;
		while (xDir >= 0 && yDir >= 0)
		{
			if (config[index].x == xDir
				&& config[index].y == yDir)
			{
				return false;
			}
			
			--xDir;
			--yDir;
		}

		xDir = x - 1;
		yDir = y + 1;
		while (xDir < boardSize && yDir < boardSize)
		{
			if (config[index].x == xDir
				&& config[index].y == yDir)
			{
				return false;
			}

			--xDir;
			++yDir;
		}

		xDir = x + 1;
		yDir = y - 1;
		while (xDir < boardSize && yDir < boardSize)
		{
			if (config[index].x == xDir
				&& config[index].y == yDir)
			{
				return false;
			}

			++xDir;
			--yDir;
		}
	}

	return true;
}

void addQueen(int x, int y, vector<QueenConfig>& config)
{
	QueenConfig	q;
	q.x = x;
	q.y = y;

	config.push_back(q);
}

bool solveFromConfig(int boardSize, vector<QueenConfig>& config)
{
	if (config.size() == boardSize)
	{
		return true;
	}

	for (int i = 0; i < boardSize; ++i)
	{
		for (int j = 0; j < boardSize; ++j)
		{
			if (isUnGuarded(boardSize, i, j, config))
			{
				addQueen(i, j, config);

				bool res = solveFromConfig(boardSize, config);

				if (res == true)
				{
					return true;
				}

				removeQueen(i, j, config);
			}
		}
	}

	return false;
}

void removeQueen(int x, int y, vector<QueenConfig>& config)
{
	vector<QueenConfig>::const_iterator iter = config.begin();
	
	while (iter != config.end())
	{
		if (iter->x == x
			&& iter->y == y)
		{
			config.erase(iter);
			iter = config.end();
			return;
		}

		++iter;
	}
}
