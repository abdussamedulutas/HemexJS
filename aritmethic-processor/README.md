# HemexJS Javascript Lexing Library

## Usage:


Sending and parsing from ArithmeticParser
```javascript
//Create parser initializer
let aParser = new ArithmeticParser();

//Send text to sync parsing and returning
let result = aParser.parse(`-1 * 7 / 2 + 6 / (+9 - 3 - 2 - 1) + 7`);
```
The result is;
```json
[
    "TEMP0 = 9 - 3",
    "TEMP1 = TEMP0 - 2",
    "TEMP2 = TEMP1 - 1",
    "TEMP3 = 7 / 2",
    "TEMP4 = 6 / TEMP2",
    "TEMP5 = -1 * TEMP3",
    "TEMP6 = TEMP5 + TEMP4",
    "TEMP7 = TEMP6 + 7"
]
```
---------
Operator List;

- `/` Priority is 11
- `*` Priority is 10
- `%` Priority is 9
- `+` Priority is 8
- `-` Priority is 7
- `<<` Priority is 6
- `>>` Priority is 5
- `>>>` Priority is 4
- `&` Priority is 3
- `^` Priority is 2
- `|` Priority is 1
