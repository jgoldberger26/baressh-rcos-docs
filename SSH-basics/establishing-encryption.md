# Negotiating Encryption
## Key Exchange
First, the client initiates the connection by sending a “hello” message, and the server responds with its own “hello” message. Then, the server responds with which protocols it supports. The client decides which, if any, of the protocols it would like to use. If the client can’t match any of the protocols provided by the server, the exchange does not continue. This includes algorithms for key exchange, encryption, and message authentication.

The Diffie-Hellman algorithm is the most commonly used for generating a secret shared key between the client and server. I will go into more detail in the next section, but know that once this step is over, both parties have access to a shared secret key without ever transmitting it over the network.

The shared secret is then used as input to a key derivation function, which generates symmetric encryption keys, integrity keys, and any other necessary session keys from the shared secret. These keys can then be used for encrypting data, authenticating messages, etc. Now the client and server can securely encrypt and authenticate data exchanged during the SSH session.

## Diffie-Hellman Algorithm
First, both parties agree on and publicly share two parameters: A large prime number, *P*, and a primitive root modulo *g*. Each party then independently generates their own secret key. A and B both choose random secret integers *a* and *b*. They then generate public keys using the formula below and exchange them over the network.

```math
A = g^a\text{ mod }p
```
```math
B = g^b\text{ mod }p
```

Both parties then compute the shared secret S using the public key received from the other:

```math
S=B^a\text{ mod }p = A^b\text{ mod }p
```

The shared secret is the same because:
```math
S = (g^b)^a\text{ mod }p=(g^a)^b\text{ mod }p
```

## Authenticating the Client
The client begins by sending the server the ID of the key-pair it would like to use. The server then checks to see if that key is in its “authorized_keys” file. If it is, the server makes the client prove their identity by encrypting a number using their public key and sending it to them. Once the client successfully decrypts the number, it then combines it with the shared session key and calculates the MD5 hash of that number, and sends it back to the server. The server performs the same calculation and compares the two hashes. If the two values match, the client is authenticated.
