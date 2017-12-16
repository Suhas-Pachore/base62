# base62

A 2-digit base62 nubmer system with alphanumeric character set in this order [0-9][a-z][A-Z]

A simple number increment fucntion to get next base62 number.

An additional function to support running legacy systems, which treats number upto 99 as base10 numbers and then starts base62 numbers from a0. base10[00-99], base62[a0-ZZ].
