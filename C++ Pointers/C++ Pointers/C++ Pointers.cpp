#include<iostream>
#include<vector>
#include<chrono>
using namespace std;
using namespace std::chrono;

void swapLocation(vector <int*>& pVariables, vector <int>& variables);
void testFunction(vector<int*>& pVariables);
int toPowerof(int power, int variable);

int main()
{
	vector<int> variables;
	variables.push_back(5);
	variables.push_back(10);
	vector <int*> pVariables;
	for (unsigned int i = 0; i < variables.size(); i++)
	{
		pVariables.push_back(&variables[i]);
	}
	int numberOfTests = 0;
	do
	{
		for (int i = 0; i < variables.size(); i++)
		{
			cout << "Location of " << *pVariables[i] << ": " << pVariables[i] << endl;
		}
		numberOfTests++;
		auto timeStart = high_resolution_clock::now();
		testFunction(pVariables);
		auto timeStop = high_resolution_clock::now();
		auto dTime = duration_cast<microseconds>(timeStop - timeStart);
		swapLocation(pVariables, variables);
		cout << "Test " << numberOfTests << " time to execute: " << dTime.count() << endl;
		cout << "--------------------------------------------------------\n";
	} while (numberOfTests < 2);
	system("pause");
	return 0;
}

void swapLocation(vector <int*>& pVariables, vector <int>& variables)
{
	vector <int*> pVariablesInitial = pVariables;
	int temp = variables[0];
	int* pTemp = &temp;
	pVariables[0] = pTemp;
	variables[0] = variables[1];
	pVariables[1] = &variables[0];
	variables[1] = temp;
	pVariables[0] = &variables[1];
	return;
}
void testFunction(vector<int*>& pVariables)
{
	const int POWER[] = { 2, 5 };
	vector <unsigned long int> answers;
	for (int i = 0; i < pVariables.size(); i++)
	{
		answers.push_back(toPowerof(POWER[i], *pVariables[i]));
		cout << *pVariables[i] << "^" << POWER[i] << " = " << answers[i] << endl;
	}
	return;
}

	int toPowerof(int power, int variable)
	{
		int answer = 1;
		for (int i = 0; i < power; i++)
		{
			answer *= variable;
		}
		return answer;
	}