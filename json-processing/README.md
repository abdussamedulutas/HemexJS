# HemexJS Javascript Lexing Library

## Usage:


Sending and parsing from jsonparser
```javascript
//Create parser initializer
let u = new JSONParser();

//Send text to sync parsing and returning
let result = u.parse(`[ "Merhab",56    ,  {"abc":false,85:14} ]`);

```
result is native json object
```json
[
    "Merhab",
    56,
    {
        "85": 14,
        "abc": false
    }
]
```
-----------------------
## Limitations

This parser has no limitations, it can parsing bigger than 4GB json data