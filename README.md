# des
Data Encryption Standard for fun

This is my own implementation of DES, to get some experience with working with bit operations 
and as an introduction to Encyrption.  I used the following website as a guide:

    http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

###bittables 
Contains some python scritpts used to generate lookuptables for the
different permutations performed in the various steps of encription.

###Encode 
Will contain the main method used for encrypting and decrypting data.  

###Feistel 
Contains implementation of the Feistel function.  This includes
expansion and supstitution steps.  

###Key 
This section generate the different subkeys from a given key to use for
encrypting and decrypting data.  

Feel free to comment on improving at heymann.murray@gmail.com
