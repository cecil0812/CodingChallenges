Run Length Encoding.

This is a problem that I ask a lot in interviews (courtesy Richard Russo).  The main issue I get from candidates is that they don't really understand what a byte really is or how to look at hex codes.  Remember that FF = 1 1 1 1 1 1 1 1 (one byte). This should be obvious but you'd be surprised at how many candiates get confused just because I'm making them look at bytes.  Yes, this could be done with strings for less abstraction but you should know what a byte is if you are a college graduate.

For junior candidates, I'm a lot nicer than for senior candidates, obviously.


Say you have the following bytes:

FF FF FF FF FF FF

^ There are 6 bytes right there.  It takes 6 bytes to store that data.  But suppose we encoded that so instead of storing all the data, we stored how many "runs" of bytes there were.

06 FF <-- 6 "runs" of the byte FF.  Notice the 0 in front of the size to denote a full byte.

Notice that if there are NO runs, we don't do anything:

FF AA BB CC DD => FF AA BB CC DD
FF FF FF FF FF FF 01 AA => 06 FF 01 AA

Ok that's fine.  But what happens when your data looks like this:

06 FF 01 AA

When you go to decode that is it:

FF FF FF FF FF FF 01 AA

or

06 FF 01 AA ???

How can you tell? (attempt to reason this out before looking below)
-------------------------------------------------------------------------------



A better way would be to include some sort of escape byte so we can tell if we are dealing with an encoded section or not.  In this example, let's make 00 be our escape byte.

FF FF FF FF FF FF 01 AA => 00 06 FF 01 AA
06 FF 01 AA => 06 FF 01 AA


That works out.  But what if 00 is in our data set?

00 06 FF 01 AA => ???

What would be a better escape character? (attempt to reason this out before looking below)
-------------------------------------------------------------------------------------------------



Here is where a lot of candidates show that they don't know what a byte actually is and attempt to store a single bit on the data stream.  Computers deal in whole bytes*, we can't store a single bit without taking an entire byte anyway:

*For the most part, just assume that any computer we care about here deals in whole bytes

Bits:
0 0 0 0 0 0 0 1 <-- one bit stored but stored as one byte in memory anyway so: 01

The best way - and the way it's usually actually implemented - is to make the count be an escape character.  Since we are dealing with "runs" of bytes, we should never see a "run" in the encoded data set, right?

Naive method:
FF FF FF FF FF => 05 FF // No runs in the encoded method

Using the count as an escape character:

05 05 FF
^
Notice that 05 is repeated which should NEVER occur.  This tells us that the 05 is really a count and the FF is the repeated data.

Examples:

FF FF FF FF FF FF => 06 06 FF
FF AA BB CC DD => FF AA BB CC DD
FF FF FF FF FF FF 01 AA => 06 06 FF 01 AA
00 06 FF 01 AA => 00 06 FF 01 AA
FF FF FF FF FF => 05 05 FF
00 06 FF AA AA AA AA => 00 06 FF 04 04 AA

Note that this is actually worse for some runs:

FF FF => 02 02 FF

Unfortunately, that is a trade-off we have to make.

Now the challenge is to write:

size_t rle_encode(const char* input, size_t length, char* outputStr, size_t outlen);
size_t rle_decode(const char* input, size_t length, char* outputStr, size_t outlen);

(Remember that char = byte in C++.)

Or the easier but really the same for stl::string:

void rle_encode(const string& input, string& outputStr);
void rle_decode(const string& input, string& outputStr);

Try to write the byte one first.  If that is confusing, write the string one and figure out what is going on.


Extra Extra credit:

What happens if we have more than 255 bytes in a run?

We can only store a max count of 255 in one byte.  If the data looks like this:

FF ... FF (300 times)

We can't store 300 in a single byte so what do we do? (attempt to reason this out before looking below)
---------------------------------------------------------------------------------------------------------




We break it up into pieces that fit into a single byte:

FF ... FF (300 times) => FF FF FF 2D 2D FF

(Note: 2D = 45 in hex, 300 - 255 = 45)

We can still decode this according to our normal rules, it's only the encoder that needs to change to account for this.