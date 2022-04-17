# Crypto Homework 1: Blocks and Streams

## Due Wednesday, March 2

## Question 1 (5 points)  

A block cypher with an 8 bit block size is very easy to break with a known-plaintext attack (assuming each block is just encrypted independently with the same key).  Describe how you would do so.  Hint, there's a version of this exact challenge in many newspapers daily (They're called cryptograms, [here's an example](https://api.razzlepuzzles.com/cryptogram)).
 
## Answer 1

This can be easily acheived by creating a 8-bit block and iterating through every possible key until that key deciphers the cipher text to the known plaintext and is an exact match. This operation will be fast and reasonable since it's just 8-bit block size and computers are fast enough to do that now.


## Question 2 (10 points)

Assume you're sending a long message using a block cypher (like AES) with the following scheme: split the message into blocksize chunks, then encrypt each with the same key.  Basically Alice sends Bob AES(m1, k), AES(m2, k), AES(m3, k), etc.  

* a(3 points):  Even if they can't decrypt blocks, what information can an eavesdropper discern from this scheme?  Hint:  imagine Alice is sending a table of data with fixed-length rows

* b(4 points):  Things are actually even worse!  A malicious attacker can actually CHANGE the message that Bob receives from Alice (slightly).  How?  This is particularly bad if the attacker knows the structure of the data being sent (like in part a)

* c(3 points):  How could you modify the scheme to mitigate/prevent these types of attack?

## Answer 2
* a: The eavesdropper will know that the data is using a symmetric cipher, i.e. the data uses the same encryption key for each block. He will also know that these are just pieces of data when combined together will give him the complete data.

* b: If the attackers gains access to the blocks, he can maybe find patterns in the blocks and then with the method of trial and error maybe will make out some parts of the data. And then once he understands the structure, he can tactfully alter the given data.

* c: I can add a layer of authentication such a digital signature to the verify data integrity. If the cipher data is tampered with, the shared key will produce a different cipher text than what was actually sent.

## Programming Part 1: A (bad) block cypher (25 points)

We're going to implement a block cypher similar to AES (but simplified somewhat).  The cypher will use a 64 bit blocksize, and a 64 bit key (it's probably convenient to store your data as an array of 8 unsigned bytes).

The algorithm has 3 main parts:  Computing the secret key based on a password (of any length); computing a set of substitution tables that will be used during encryption/decryption; the actual encryption algorithm which makes use of the first 2 parts.


To generate the encryption key, we're going to use a very insecure "hash" of an arbitrary length password.  

The key starts as an array of 8 zeros.  To generate the key do the following:

for i = 0 to password length:
  key[i mod 8] = key[i mod 8] xor password[i]

Think about why this particular scheme is such a bad choice.

We're going to need 8 substitution tables (each acting on 1 byte) for our algorithm.  They should be computed in the following (probably cryptographically insecure) manner.  Represent the substitution as a 256 element array (a byte with a value x will be substituted by array[x]).  Since the substitution must be reversible, each value must be mapped to a different substitution.  We can achieve this by starting with a substitution (such as the identity substitution represented by the array [0, 1, 2, ... 255]) and then shuffling it.

To get the next substitution table, apply a Fisher-Yates shuffle to the previous table [algorithm description here](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle).  To get the first table, start with the identity permutation.  Note that this is not a good way to generate these for a production implementation!  Also note that in a production cypher, these tables would probably be specified in advance (the AES substitution tables are part of the algorithm specification).  

Since "Alice" and "Bob" are part of the same program for us, we can just compute the substitution tables once and share them between the encryption and decryption functions
 

Now that we have the substitution tables and the key, the encryption algorith is as follows:

The state begins as the input message

For each of 16 rounds:

 * xor the current state with the key

 * for each byte in the state, substitute that byte using the appropriate substitution table (byte 0 should use table 0, byte 1 should use table 1, etc)

 * rotate the entire state 1 bit to the left (after this byte 0 will contain contributions from bytes 0 and 1.  Byte 7 will contain contributions from byte 7 and byte 0).

The output is the state after these 16 rounds.

Once you've implmented this encryption algorithm, implement the decryption algorithm (the "tricky" part is implementing the reverse substitution tables)
 

Verify that you can encrypt and decrypt messages using your program.  Demonstate that trying to decrypt a message using the wrong password (and therefore the wrong key) does not recover the plaintext message.

Try modifying 1 bit of the cyphertext and then decrypting with the correct passwords.  What do you see?

I suggest using C++ since you have greater control over integer types (specifically, you'll mostly be working with uint8_t types).  


## Programming Part 2: RC4 Cypher (20 points)

Implement the RC4 cypher as described in class (it's not very much code!  Probably a struct/class with a constructor and a single method to get the next pseudorandom byte.  Pseudocode is in the class slides or many other places). 

Verify that decrypting a message with a different key than the encryption key does not reveal the plaintext. 

Verify that encrypting 2 messages using the same keystream is insecure (what do you expect to see if you xor the two encrypted messages?)

Modify part of a message using a bit-flipping attack.  For example, try sending the message "Your salary is $1000" encrypted with RC4.  Modify the cyphertext so that when decrypted is says that your salary is 9999 instead.  Hint: this should just require using xor.


Submit your solutions to Github