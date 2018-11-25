//Function performance by location test
//This program tests the exectution time of a test function as it changes the storage location of the variables used.  This program isn't very useful as it is now, but the concept could be put to good use later on.
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
	vector<int> variables; //Stores the variables used in the test function.  These values will change.  The variables are tracked by their memory location instead of their position in variables.
	variables.push_back(5); //variable[0] = 5
	variables.push_back(10); //variable[1] = 10
	vector <int*> pVariables; //Stores pointers for all variables 
	for (unsigned int i = 0; i < variables.size(); i++)
	{
		pVariables.push_back(&variables[i]); // Store the memory location of variables in pVariables.
	}
	int numberOfTests = 0; //Tracks how many times the test function been executed.
	do
	{
		for (int i = 0; i < variables.size(); i++)
		{
			cout << "Location of " << *pVariables[i] << ": " << pVariables[i] << endl; //Display the memory location all variables for the test function.
		}
		numberOfTests++;
		auto timeStart = high_resolution_clock::now(); //Gets the current time = time the program starts. (Highly accurate, not hour minute second)
		testFunction(pVariables); //Perform the test function.
		auto timeStop = high_resolution_clock::now(); //Gets the current time = time the program ends.
		auto dTime = duration_cast<microseconds>(timeStop - timeStart); //Calculate the difference in time between start and end.
		swapLocation(pVariables, variables); //Swap the memory location of the variables.
		cout << "Test " << numberOfTests << " time to execute: " << dTime.count() << endl; //Display the execution time in milliseconds.
		cout << "--------------------------------------------------------\n";
	} while (numberOfTests < 2);
	system("pause");
	return 0;
}

void swapLocation(vector <int*>& pVariables, vector <int>& variables) //Swap the memory location of the variables.
{
	int temp = variables[0]; //Create a temporary value to temporarily hold on of the variables to allow for the swap.
	int* pTemp = &temp; //Get the memory location of the temp variable.
	pVariables[0] = pTemp; //pVariables[0] now points to temp
	variables[0] = variables[1]; //variables[0] and variables[1] both equal the orrigional value of variables[1]
	pVariables[1] = &variables[0]; //pVariables[1] now points to variables[0]
	variables[1] = temp; //variables[0] and variables[1] have swapped values
	pVariables[0] = &variables[1]; //pVariables[0] now points to variables[1]
	return;
}
void testFunction(vector<int*>& pVariables) //Test function that is to be timed.
{
	//The specific function chosen is unimportant to the purpose of this program.  It is a generic example that multiplies the variables by themselves based on POWER.
	const int POWER[] = { 2, 5 }; //Exponents
	vector <unsigned long int> answers; //Stores answeres
	for (int i = 0; i < pVariables.size(); i++) 
	{
		answers.push_back(toPowerof(POWER[i], *pVariables[i])); //Calculate answer with toPowerOf()
		cout << *pVariables[i] << "^" << POWER[i] << " = " << answers[i] << endl; //Display answer
	}
	return;
}

	int toPowerof(int power, int variable) //calculates variable^power and returns it
	{
		int answer = 1;
		for (int i = 0; i < power; i++) 
		{
			answer *= variable;
		}
		return answer;
	}