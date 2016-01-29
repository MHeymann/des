# des
Data Encryption Standard for fun

This is my own implementation of DES, to get some experience with working with bit operations 
and as an introduction to Encyrption.  I used the following website as a guide:

    http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

###Key 
This section generate the different subkeys from a given key to use for
encrypting and decrypting data.  

###Encode 
Will contain the main method used for encrypting and decrypting data.  

###Encode/Permutation
Implementation of the intitial and final permutations performed during the
encoding of 64 bit words.  

###Encode/Feistel 
Contains implementation of the Feistel function.  This includes
expansion and supstitution steps.  

###Encode/Feistel/Expansion 
Code to expand 32 bits to 48 using a simple permutaion table.  

###Encode/Feistel/Substitution 
Code to implement the substitution process during which 48 bits gets reduced to
32 bits.  

###bittables 
Contains some python scritpts used to generate lookuptables for the
different permutations performed in the various steps of encription.

Feel free to comment on improving at heymann.murray@gmail.com
