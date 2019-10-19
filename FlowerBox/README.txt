You are to implement the following method:

bool canPlant(vector<bool> flowerBox, int number);

flowerBox is an array of booleans containing either true where a flower is planted or false if none is planted.  Flowers can only be planted if they have empty space on either side.  For instance:

[F, F, T, F] <--- Ok

[F, T, T, F] <--- Not ok

Given the array and how many flowers to plant (number), return true or false if that many flowers can be planted.

Additionally, what improvements might you make on this method?  Is boolean the best thing to return from it?