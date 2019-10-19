Write bool isMatch(const string& s, const string& p) where s is the string to search and p is a psuedo-regular expression.

Valid pattern p's are:
Alpha characters (no numbers)
? - means zero or one (like a regex)
* - means zero or more (like a regex)

No other matching allowed/required.  Assume patterns are always valid.

Examples:
string s = "aa";
string p = "a";
FALSE


string s = "aa";
string p = "aa";
TRUE


string s = "aa";
string p = "*";
TRUE


string s = "aa";
string p = "a*";
TRUE


string s = "aa";
string p = "a?";
TRUE


string s = "aaa";
string p = "a?";
FALSE


string s = "cb";
string p = "?";
FALSE


string s = "adceb";
string p = "a*b";
TRUE


string s = "acdcb";
string p = "a*c?b";
FALSE


string s = "abcdefg";
string p = "a*def?";
TRUE