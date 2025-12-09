#include "pch.h"

void UI::handleKeyPress(uint32_t keyCode)
{
	vector<LambdaHolder>& relevantLambdas = keyPressLambdas[keyCode];
	for (const LambdaHolder& lambdaHolder : relevantLambdas)
	{
		lambdaHolder.lambda();
	}
}