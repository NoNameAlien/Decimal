# Decimal Routines

### Table of Contents
* [Introduction](#introduction)
* [Goals](#goals)
* [Implementation](#implementation)
* [Arithmetic Operators](#arithmetic-operators)
* [Comparison Operators](#comparison-operators)
* [Converters and Parsers](#converters-and-parsers)
* [Additional Functions](#additional-functions)
* [Build](#Build)
* [Tests](#tests)

### Introduction

Implementation of simple decimal processing routines using a specialized decimal representation, consisting of a 1-bit sign, a 96-bit integer number, and a scaling factor. Common arithmetic operations, comparisons, conversion, and parsing, as well as additional functions will be implemented using this representation.

### Goals
- Learn decimal operations and implementations using specialized representations
- Get better at working with memory in C
- Improve Makefile
- Implement tests for the library
- Familiarize with other numerical libraries

### Implementation

The library will support the following functions:
* Arithmetic Operators (Addition, Subtraction, Multiplication, Division)
* Comparison Operators (Less than, Less than or equal to, Greater than, Greater than or equal to, Equal to, Not equal to)
* Converters and Parsers (From int, From float, To int, To float)
* Additional Functions (Floor, Round, Truncate, Negate)

### Arithmetic Operators
Function | Description
-------- | -----------
s21_add | Adds two decimal values
s21_sub | Subtracts two decimal values
s21_mul | Multiplies two decimal values
s21_div | Divides two decimal values

### Comparison Operators
Function | Description
-------- | -----------
s21_is_less | Returns 1 if a decimal value is less than another one, 0 otherwise
s21_is_less_or_equal | Returns 1 if a decimal value is less than or equal to another one, 0 otherwise
s21_is_greater | Returns 1 if a decimal value is greater than another one, 0 otherwise
s21_is_greater_or_equal | Returns 1 if a decimal value is greater than or equal to another one, 0 otherwise
s21_is_equal | Returns 1 if a decimal value is equal to another one, 0 otherwise
s21_is_not_equal | Returns 1 if a decimal value is not equal to another one, 0 otherwise

### Converters and Parsers
Function | Description
-------- | -----------
s21_from_int_to_decimal | Converts an int into a decimal
s21_from_float_to_decimal | Converts a float into a decimal
s21_from_decimal_to_int | Converts a decimal into an int (discarding fractional part)
s21_from_decimal_to_float | Converts a decimal into a float

### Additional Functions
Function | Description
-------- | -----------
s21_floor | Returns the floor of a decimal
s21_round | Rounds a decimal to the nearest integer
s21_truncate | Truncates a decimal to its integral digits
s21_negate | Negates a decimal value (multiplies by -1)

## Build
```
$ git clone https://github.com/NoNameAlien/Decimal
$ cd Decimal
$ make 
```

### Tests
* Unit tests are implemented using [Check](https://libcheck.github.io/check/) & coverage report with [LCOV](https://github.com/linux-test-project/lcov)
