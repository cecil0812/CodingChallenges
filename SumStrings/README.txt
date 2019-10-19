Sum strings

Implement: string addNumbers(string a, string b);

Note that a and b are both positive, real numbers (yes, can including decimal points).  They can both be arbitrarily long and indeed, are likely to NOT be the same length.

Examples:

string a = "3.14";
string b = ".91";
addNumbers(a, b); // 4.05

string a1 = ".91";
string b1 = "3.14";
addNumbers(a1, b1); // 4.05

string a2 = "1.91";
string b2 = "333.1412";
addNumbers(a2, b2); //335.0512

string a3 = "47426246591237423.3985486002482462467";
string b3 = "36484591.37353355489069";
addNumbers(a3, b3); //47426246627722014.7720821551389362467
addNumbers(b3, a3); //47426246627722014.7720821551389362467

string a5 = "4742";
string b5 = "3648.34";
addNumbers(b5, a5); //8390.34
addNumbers(a5, b5); //8390.34