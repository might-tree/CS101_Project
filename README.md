# CS101_Course_Project

## Decoding and Cryptography

### Abstract
The assignment is about decoding a text document using various heuristics. The texts are encoded using a monoalphabetic substitution. The decoding proceeds in three phases:
* ETAI Strategy
* Dictionary Closure 
* Secret Word Enumeration

Given the key, the ciphertext for the plaintext in ```example-out.txt``` shown in ```example-in.txt```.
Given a ciphertext, the problem is to decode it using the set of three strategies mentioned above. At the end of each strategy, we either discover the secret word from which we can recreate the complete key. In this case our method is considered to be successful. Else we try the next strategy with the key returned by the previous strategy. If we exhaust all the strategies without producing the secret key, we report failure.

### Implementation
* File Handling
* Arrays
* Header Files
