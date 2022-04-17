# Crypto Homework 1: Blocks and Streams

## Due Wednesday, March 2

## Question 1 (5 points)  

A block cypher with an 8 bit block size is very easy to break with a known-plaintext attack (assuming each block is just encrypted independently with the same key).  Describe how you would do so.  Hint, there's a version of this exact challenge in many newspapers daily (They're called cryptograms, [here's an example](https://api.razzlepuzzles.com/cryptogram)).

## Answer 1

With a known plaintext, the attacker knows what the words and the characters present in the plaintext looks like once it has been encrypted. Using that the attacker can create a substitution table that will parse any other cipher text and substitute it with the correct decrypted value. Using this method, over the course of a few transmission, and applying the technique of trail and error and some guesswork, the attacker can fully populate the substitution table. Without even obtaining the key, the attacker can now read and manipulate the block ciphers.

Apart from that, the computers have become very powerful and can easily bruteforce an 8 bit key in a matter of seconds. But this is the case with any encryption and that's why SHA256 is being used extensively now due to it's computational demand to crack.
 

## Question 2 (10 points)

Assume you're sending a long message using a block cypher (like AES) with the following scheme: split the message into blocksize chunks, then encrypt each with the same key.  Basically Alice sends Bob AES(m1, k), AES(m2, k), AES(m3, k), etc.  

* a(3 points):  Even if they can't decrypt blocks, what information can an eavesdropper discern from this scheme?  Hint:  imagine Alice is sending a table of data with fixed-length rows

* Ans: An eavesdropper can dicern duplicate patterns and know that the plaintext content of one pattern is exactly the same as the other duplicate.

* b(4 points):  Things are actually even worse!  A malicious attacker can actually CHANGE the message that Bob receives from Alice (slightly).  How?  This is particularly bad if the attacker knows the structure of the data being sent (like in part a)

* Ans: Once the attacker has a few patterns he knows, he can misplaced them in the cipher text to swap and manipulate data. He can heavily corrupt the data by just moving, deleting blocks.

* c(3 points):  How could you modify the scheme to mitigate/prevent these types of attack?

* Ans: There are multiple ways to overcome this, a few options are as follows:
  * Cypher block chaining:
    * XOR the current block with the cipher text of the previous block.
    * XOR the first message with a random block.
  This isn't the best solution but it will make it difficult for the attacker compared to what we had before.

  * RSA:
    * Implement signed certificates and certificate authorities. A certificate is a cryptographically signed object that consists info about the sender/receiver. It cannot be tampered with as it needs the signer's private key to be modified or created. CA is the entity that manages these certificates. The basic communication looks like:
      * You ask for sender's signed certifcate.
      * Verify signature on the certificate and if it's valid,
        * Verify signer of this certificate 
        * Keep repeating until you verify a top level "trust store" certificate.
      * If not valid then drop communication and take necessary measures.
