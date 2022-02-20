# HemexJS Javascript Lexing Library

## Usage:

Sending and parsing from SaxParser
```javascript
//  Create parser initializer
let u = new SaxParser();

//  will parse data
let data = `
    <card>
        <data name="First Name">
            John
        </data>
        <data name="Last Name">
            Wick
        </data>
        <data name="Age">
            46
        </data>
        <data name="Job">
            Developer
        </data>
    </card>
`;

//  Send text to sync parsing and returning
let result = u.parse(data);

```
result is native json object
```json
[
    [
        "card",
        {},
        [
            [
                "data",
                {
                    "name": "First Name"
                },
                [
                    ["#data","John"]
                ]
            ],
            [
                "data",
                {
                    "name": "Last Name"
                },
                [
                    ["#data","Wick"]
                ]
            ],
            [
                "data",
                {
                    "name": "Age"
                },
                [
                    ["#data","46"]
                ]
            ],
            [
                "data",
                {
                    "name": "Job"
                },
                [
                    ["#data","Developer"]
                ]
            ]
        ]
    ]
]'
```
-----------------------
## Limitations

This parser has no limitations, it can parsing bigger than 4GB json data