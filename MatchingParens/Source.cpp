#include <iostream>
#include <stack>
#include <map>

using namespace std;

bool isValidString(const string& str);


map<char, char> mappings;
map<char, char> closingMappings;

int main(int argc, char* argv[])
{
	closingMappings[')'] = '(';
	closingMappings['}'] = '{';
	closingMappings[']'] = '[';

	mappings['('] = ')';
	mappings['{'] = '}';
	mappings['['] = ']';

	string teststring = "{[((abcdefg))]}";

	bool res = isValidString(teststring);

	return 0;
}

bool isValidString(const string& str)
{
	stack<char> stack;

	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];

		// If the current character is a closing bracket.
		if (closingMappings.find(c) != closingMappings.end())
		{
			char topElement = '#';

			// Get the top element of the stack. If the stack is empty, set a dummy value of '#'
			if (!stack.empty())
			{
				topElement = stack.top();
				stack.pop();
			}

			// If the mapping for this bracket doesn't match the stack's top element, return false.
			if (topElement != closingMappings[c])
			{
				return false;
			}
		}
		else if (mappings.find(c) != mappings.end())
		{
			// If it was an opening bracket, push to the stack.
			stack.push(c);
		}
	}

	// If the stack still contains elements, then it is an invalid expression.
	return stack.empty();
}
