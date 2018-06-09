#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<sstream>

using namespace std;

bool isActive;

void PrintMenu();
void Start();
bool ProcessCommand(char command);

string InputAnExpression();

string PrefixToInfix(string prefix);
vector<string> PrefixToPostfix(string prefix);
vector<string> InfixToPostfix(string infix);
string InfixToPrefix(string infix);
string PostfixToInfix(string postfix);
string PostfixToPrefix(string postfix);

string ReverseBrackets(string equasion);
string VectorToString(vector<string> expression);

string CalculateFromInfix(string expression);
double Calculate(vector<string> expression);

int ReturntRank(char symbol);

int main()
{
	isActive = true;

	Start();

	return 0;
}

void Start()
{
	PrintMenu();

	do
	{

		char command;

		cin >> command;

		if (ProcessCommand(command))
		{
			system("pause");
			system("cls");
			PrintMenu();
		}
	} while (isActive);
}

void PrintMenu()
{
	cout << "Options:" << endl;
	cout << "Press 1: Transform from Prefix to Infix" << endl;
	cout << "Press 2: Transform from Prefix to Postfix" << endl;
	cout << "Press 3: Transform from Infix to Prefix" << endl;
	cout << "Press 4: Transform from Infix to Postfix" << endl;
	cout << "Press 5: Transform from Postfix to Prefix" << endl;
	cout << "Press 6: Transform from Postfix to Infix" << endl;
	cout << "Press 7: Calculate form Infix" << endl;
	cout << "Press q: To quit" << endl;
}

bool ProcessCommand(char command)
{
	string result;

	switch (command)
	{
	case '1':
		result = PrefixToInfix(InputAnExpression());
		cout << result << endl;
		return true;
	case '2':
		result = VectorToString(PrefixToPostfix(InputAnExpression()));
		cout << result << endl;
		return true;
	case '3':
		result = InfixToPrefix(InputAnExpression());
		cout << result << endl;
		return true;
	case '4':
		result = VectorToString(InfixToPostfix(InputAnExpression()));
		cout << result << endl;
		return true;
	case '5':
		result = PostfixToPrefix(InputAnExpression());
		cout << result << endl;
		return true;
	case '6':
		result = PostfixToInfix(InputAnExpression());
		cout << result << endl;
		return true;
	case '7':
		result = CalculateFromInfix(InputAnExpression());
		cout << result << endl;
		return true;
	case 'q':
		isActive = false;
		return false;
	default:
		cout << "(" << command << ") is not a valid command" << endl;
		return false;
	}
}

string InputAnExpression()
{
	cout << "Enter an expression:" << endl;
	string expression;
	cin >> expression;

	return expression;
}

string PrefixToInfix(string prefix)
{
	stack<string> toInfix;

	for (int i = prefix.size() - 1; i >= 0; i--)
	{
		int currentChar = ReturntRank(prefix[i]);

		if (currentChar == 0) {
			toInfix.push(string(1, prefix[i]));
			continue;
		}

		string first = toInfix.top();
		toInfix.pop();

		string second = toInfix.top();
		toInfix.pop();

		if (currentChar == 1)
		{
			string newNumber = first + prefix[i] + second;
			toInfix.push(newNumber);
		}
		else
		{
			string newNumber = "(" + first + ")" + prefix[i] + "(" + second + ")";
			toInfix.push(newNumber);
		}
	}

	return toInfix.top();
}

vector<string> InfixToPostfix(string infix)
{
	stack<char> operators;
	vector<string> result;

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
		{
			operators.push(infix[i]);
			continue;
		}

		if (infix[i] == ')')
		{
			while (operators.top() != '(') {
				result.push_back(string(1, operators.top()));

				operators.pop();
			}
			operators.pop();
			continue;
		}
		int currentChar = ReturntRank(infix[i]);
		if (currentChar == 0) {
			string number = "";
			while (currentChar == 0)
			{
				number += infix[i];
				i++;
				if (i < infix.size()) {
					currentChar = infix[i];
				}
				else break;
			}
			i--;
			result.push_back(number);
			continue;
		}
		if (operators.empty()) {
			operators.push(infix[i]);
			continue;
		}

		char op = operators.top();
		int lastOperator = ReturntRank(op);
		while (lastOperator >= currentChar)
		{
			operators.pop();

			result.push_back(string(1, op));

			if (operators.empty())
			{
				break;
			}

			op = operators.top();
			lastOperator = ReturntRank(op);
		}
		operators.push(infix[i]);
	}

	while (!operators.empty())
	{
		result.push_back(string(1, operators.top()));
		operators.pop();
	}

	return result;
}

string InfixToPrefix(string infix)
{
	reverse(infix.begin(), infix.end());

	infix = ReverseBrackets(infix);

	string result = VectorToString(InfixToPostfix(infix));

	reverse(result.begin(), result.end());

	return result;
}

string PostfixToInfix(string postfix)
{
	reverse(postfix.begin(), postfix.end());

	string result = PrefixToInfix(postfix);

	reverse(result.begin(), result.end());

	return ReverseBrackets(result);
}

vector<string> PrefixToPostfix(string prefix)
{
	string infix = PrefixToInfix(prefix);

	return InfixToPostfix(infix);
}

string PostfixToPrefix(string postfix)
{
	string infix = PostfixToInfix(postfix);

	return InfixToPrefix(infix);
}

string ReverseBrackets(string equasion)
{
	for (int i = 0; i < equasion.size(); i++)
	{
		if (equasion[i] == '(')
		{
			equasion[i] = ')';
		}
		else if (equasion[i] == ')')
		{
			equasion[i] = '(';
		}
	}

	return equasion;
}

string VectorToString(vector<string> expression)
{
	string result = "";

	for (int i = 0; i < expression.size(); i++)
	{
		result += expression[i];
	}

	return result;
}

int ReturntRank(char symbol)
{
	switch (symbol)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
		return -1;
	default:
		return 0;
	}
}

string CalculateFromInfix(string expression)
{
	vector<string> postfixExpression = InfixToPostfix(expression);
	double result = Calculate(postfixExpression);

	ostringstream strs;
	strs << result;
	return strs.str();
}

double Calculate(vector<string> expression)
{
	stack<double> numbers;
	for (int i = 0; i < expression.size(); i++)
	{
		string current = expression[i];

		if (isdigit(current[0]))
		{
			numbers.push(stod(current));
		}
		else
		{
			double first = numbers.top();
			numbers.pop();
			double second = numbers.top();
			numbers.pop();

			switch (current[0])
			{
			case '+':
				numbers.push(first + second);
				break;
			case '-':
				numbers.push(second - first);
				break;
			case '*':
				numbers.push(first * second);
				break;
			case '/':
				numbers.push(second / first);
				break;
			}
		}
	}
	return numbers.top();
}

