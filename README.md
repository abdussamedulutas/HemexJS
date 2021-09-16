# HemexJS Javascript Lexing Library

Low-Level String inspecting, lexing, parsing library

This library is written to do text mining, formatting, format manipulation and conversion.

# Methods
## new Hemex() `contructor` 
```javascript
    let hmx = new Hemex();
    Hemex.EOL   // Array<Number> End of line (CRLF)
    Hemex.WhiteSpace   // Array<Number> (space, tab, esc vs.)
    hmx.offset // Root position layer offset
    hmx.length // Current text length
    hmx.text // Current text context
```
## .setText(text)
- `text` : String - All Methods will process of this given data
- Reset all previusly settings and positions
- No return data

```javascript
    let hmx = new Hemex();
    hmx.setText(`[Number:name(a)_value(83)]`);
```

## .getText()
- Returns the processing text
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc`);
    hmx.getText();  // return the 'Abc'
```

## .getChar()
- Get one character from cursor
- returning `string` is length 1
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc`);
    hmx.getChar();  // return the 'A'
    hmx.nextChar();
    hmx.getChar();  // return the 'b'
```

## .isChar(char)
- `char` : string - Check if given character and current position character are equal
- returning `boolean`
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc`);
    hmx.isChar('A');  // return true
    hmx.isChar('b');  // return false
```

## .isEnd()
- Checking end of line and returning
- returning `boolean`
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc`);
    hmx.isEnd();    // return false
    hmx.nextChar();
    hmx.nextChar();
    hmx.nextChar();
    hmx.isEnd();    // return true
```

## .nextChar()
- Moves the cursor to the next character
- No return data
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc`);
    hmx.getChar();  // return A
    hmx.getOffset();  // return 0

    hmx.nextChar(); // next char
    hmx.getChar();  // return b
    hmx.getOffset();  // return 1

    hmx.nextChar(); // next char
    hmx.getChar();  // return c
    hmx.getOffset();  // return 2
```

## .toChar(num)
- `num` : Number - Moves the cursor to the given number of characters
- No return data
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc`);
    hmx.getChar();  // return A
    
    hmx.toChar(2); // go to 2 char next (Append current position)

    hmx.nextChar(); // next char
    hmx.getChar();  // return c
    hmx.getOffset();  // return 2
```

## .getLine()
- `num` : Number - Get chars from current position until new line char
- returning `string`
```javascript
    let hmx = new Hemex();
    hmx.setText(`Abc\ndef`);
    hmx.getLine();  // return 'Abc'
```

## .readWhileFunc(func)
- `func` : function - Read all data until the function returns false
- returning `string`
```javascript
    let hmx = new Hemex();
    hmx.setText(`example@domain.com.tr`);
    let name = hmx.readWhileFunc(function(){    // read all until finded '@' char
        return !hmx.include('@',true);
    });
    let domain = hmx.readWhileFunc(e => true);    // read all everywhere
    // name is 'abdussamedulutas'
    // name is 'domain.com.tr'
```

## .each(func)
- `func` : function - Read all data until the function returns false
- increment cursor every loop step
- returning `string`
```javascript
    let hmx = new Hemex();
    hmx.setText(`AA25BB88ET7700.XZ0003`);

    let chars = [], numbers = [];
    hmx.each(function(){

        if(hmx.isLetter()){
            let data = hmx.readWhileFunc(hmx.isLetter.bind(hmx));
            chars.push(data);
        }

        if(hmx.isNumber()){
            let data = hmx.readWhileFunc(hmx.isNumber.bind(hmx));
            numbers.push(data);
        };

        return true;
    });
    // chars is ["AA","B","T","XZ"]
    // numbers is ["25","88","7700","0003"]
```

## .while(func)
- `func` : function - Read all data until the function returns false
- Some as each but doesnt increment cursor every loop step
- returning `string`
```javascript
    let hmx = new Hemex();
    hmx.setText(`24,55,17,63,56,71.`);
    let numbers = [];
    hmx.while(function(){
        let data = hmx.readWhileFunc(hmx.isNumber.bind(hmx));
        numbers.push(data);
        if(hmx.isChar(','))
        {
            hmx.nextChar();
            return true; // Continue next event loop
        }else if(hmx.isChar('.')){
            hmx.nextChar();
            return true; // break loop
        }
    });
    // chars is [24,55,17,63,56,71]
```

## .isNumber()
- Check char is number from current position
- returning `bool`
```javascript
    let hmx = new Hemex();
    hmx.setText(`1E`); 
    hmx.isNumber(); // '1' char type is number
    hmx.nextChar(); // next char
    hmx.isNumber(); // 'E' char type is number
```

## .readNumbers()
- returns all number characters from the current position, stops when it finds a different character
- returning `string`

some as `readWhileFunc`
```javascript
    hmx.readWhileFunc(hmx.isNumber.bind(this),false)
```

## .isBigLetter()
- Check current character is big letter
- The opposite of `isBigLetter` may not be `isSmallLetter`.
- returning `bool`
```javascript
    let hmx = new Hemex();
    hmx.setText(`Ab`); 
    hmx.isBigLetter(); // returns true
    hmx.nextChar(); // next char
    hmx.isBigLetter();  // returns false
```
## .isSmallLetter()
- Controlling for current char is small letter
- The opposite of `isSmallLetter` may not be `isBigLetter`.
- returning `bool`
```javascript
    let hmx = new Hemex();
    hmx.setText(`Ab`); 
    hmx.isBigLetter(); // returns false
    hmx.nextChar(); // next char
    hmx.isBigLetter();  // returns true
```

## .readNumbers()
- returns all letter characters from the current position, stops when it finds a different character
- returning `string`

some as `readWhileFunc`
```javascript
    hmx.readWhileFunc(hmx.isLetter.bind(this),false)
```

## .isWhiteSpace()
- Controlling for current char is white space char
- returning `bool`
```javascript
    let hmx = new Hemex();
    hmx.setText(`Male Female`);
    hmx.include("Female",true);  // returns false
    hmx.include("Male",true);  // returns false
    if(hmx.isWhiteSpace()){ // if current char is whitespace char
        hmx.readWhileFunc(hmx.isWhiteSpace.bind(hmx),false)    //skip to next
    };
    hmx.include("Female",true);  // returns true
```

## .readWhiteSpace()
- returns all white space characters from the current position, stops when it finds a different character
- returning `string`

some as `readWhileFunc`
```javascript
    hmx.readWhileFunc(hmx.isWhiteSpace.bind(this),false)
```

## .include(param)
- `param` : string - Checks from current position the existence of the specified word
- returning `bool`
```javascript
   let hmx = new Hemex();
    hmx.setText("Male Female");
    hmx.include(`Male`);    // is true
    hmx.include(`Female`);    // is false
```
## .includes(arrayParam)
- `param` : array of string - Checks from current position the existence of the specified anywords
- returning `string` - founded word
```javascript
   let hmx = new Hemex();
    hmx.setText("<input>");
    let finded = hmx.includes([
        '<input>',
        '<textarea>',
        '<div>',
        '<span>'
    ]);
    // finded '<input>'
```
## .readNumber()
- Checks from current position the existence of formatted number
- returning `string` - founded word

Resolving this formats

```javascript
0, 1.5, +1.755, 0x8E, 0b48, 064.770, 1e+4, -1746.32e-20
```

------
# Mapping positions

hemex nests all positions in layers


# Layering Methods
## .beginPosition()
- Create new position layer from last position
```javascript
    let hmx = new Hemex();
    hmx.setText(...)
    hmx.nextChar(); // current position 1 | Layer 1
    hmx.nextChar(); // current position 2 | 
    
    hmx.beginPosition();
    hmx.nextChar(); // current position 3 | 
    hmx.nextChar(); // current position 4 | Layer 2
    hmx.nextChar(); // current position 5 | 
    hmx.rejectPosition();   // --> commit to parent layer
    
    hmx.getOffset() // current position 2 | Executed Layer 1
```

## .acceptPosition()
- Go back previous layer
- Copy position of current layer to previous layer and delete current layer
```javascript
    let hmx = new Hemex();
    hmx.setText(...)
    hmx.nextChar(); // current position 1 | Layer 1
    hmx.nextChar(); // current position 2 | 

    hmx.beginPosition();
    hmx.nextChar(); // current position 3 | 
    hmx.nextChar(); // current position 4 | Layer 2
    hmx.nextChar(); // current position 5 | 
    hmx.acceptPosition();   // --> commit to parent layer

    hmx.getOffset() // current position 5 | Executed Layer 1
```
## .positionRange()
- Returns the coords between current position and the previous position.
- `[int ParentLayerPosition,int CurrentLayerPosition]`
- returning `[number,number]`
```javascript
    let hmx = new Hemex();
    hmx.setText(...)
    hmx.nextChar(); // current position 1 | Layer 1
    hmx.nextChar(); // current position 2 | 

    hmx.beginPosition();
    hmx.nextChar(); // current position 3 | 
    hmx.nextChar(); // current position 4 | Layer 2
    hmx.nextChar(); // current position 5 | 
    hmx.positionRange(); // return the [2,5]
```
## .getPositionRange()
- Returns the text between current position and the previous position.
- returning `string`
```javascript
    let hmx = new Hemex();
    hmx.setText('ABCDEFGH')
    hmx.getChar(); // current char is A | Layer 1
    hmx.nextChar(); // current char is B | 

    hmx.beginPosition();
    hmx.nextChar(); // current char is C | 
    hmx.nextChar(); // current char is D | Layer 2
    hmx.nextChar(); // current char is E | 
    hmx.getPositionRange(); // return 'CDE'
```
## .rejectPosition()
- Ignore current position and delete layer, Go back previous layer
```javascript
    let hmx = new Hemex();
    hmx.setText('ABCDEFGH')
    hmx.getChar(); // current char is A | Layer 1
    hmx.nextChar(); // current char is B | 

    hmx.beginPosition();
    hmx.nextChar(); // current char is C | 
    hmx.nextChar(); // current char is D | Layer 2
    hmx.nextChar(); // current char is E | 
    hmx.rejectPosition(); // rollback layer to previus layer

    hmx.getChar(); // current char is B
```
## .getOffset()
- Get current position from current layer
- Returning `number`
```javascript
    let hmx = new Hemex();
    hmx.setText('ABCDEFGH')
    hmx.getChar(); // current char is A | Layer 1
    hmx.nextChar(); // current char is B | 
    hmx.getOffset(); // returns 1
```
## .setOffset(num)
- `num` - Number : Set current position from current layer
```javascript
    let hmx = new Hemex();
    hmx.setText('ABCDEFGH')
    hmx.getChar(); // current char is A | Layer 1
    hmx.setOffset(6); // go to the next to 6 char
    hmx.getChar(); // returns 'G'
```