#include "Dino.h"
#include "Player.h"

void waitForSeconds(int inputTime)
{
	int tmptime = time(0) + inputTime;
	while (time(0) < tmptime);
}

std::vector<std::string> splitString(std::string inputString)
{
	std::vector<std::string> result;
	std::string tmp = "";

	for (int i = 0; i < inputString.size(); i++)
	{
		if (inputString[i] != ' ') tmp += inputString[i];
		else
		{
			result.push_back(tmp);
			tmp = "";
		}
	}
	if (tmp != "")
		result.push_back(tmp);

	return result;
}
