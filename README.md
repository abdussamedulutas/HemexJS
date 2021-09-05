# HemexJS Javascript Lexing Library

Low-Level String inspecting, lexing, parsing library

This library is written to do text mining, formatting, format manipulation and conversion.

# Methods
## new Hemex() `contructor` 
## .setText(text)
- `text` : String - All Methods will process of this given data
- Reset all previusly settings and positions
- No return data

## .getText()
- Returns the processing text

## .getChar()
- Get one character from cursor
- returning `string` is length 1

## .isChar(char)
- `char` : string - Check if given character and current position character are equal
- returning `boolean`

## .isEnd()
- Checking end of line and returning
- returning `boolean`

## .nextChar()
- Moves the cursor to the next character
- No return data

## .toChar(num)
- `num` : Number - Moves the cursor to the given number of characters
- No return data

## .getLine()
- `num` : Number - Get chars from current position until new line char
- returning `string`

## .readWhileFunc(func)
- `func` : function - Read all data until the function returns false
- returning `string`

## .each(func)
- `func` : function - Read all data until the function returns false
- increment cursor every loop step
- returning `string`

## .while(func)
- `func` : function - Read all data until the function returns false
- Some as each but doesnt increment cursor every loop step
- returning `string`

## .isNumber()
- Check char is number from current position
- returning `bool`

## .readNumbers()
- returns all number characters from the current position, stops when it finds a different character
- returning `string`

some as `readWhileFunc`
```javascript
    hmx.readWhileFunc(hmx.isNumber.bind(this),false)
```

## .isBigLetter()
- Check current character is big letter
- returning `bool`
## .isSmallLetter()
- Controlling for current char is small letter
- returning `bool`

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
## .includes(arrayParam)
- `param` : array of string - Checks from current position the existence of the specified anywords
- returning `string` - founded word
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
## .acceptPosition()
- Go back previous layer
- Copy position of current layer to previous layer and delete current layer
## .positionRange()
- Returns the coords between current position and the previous position.
- returning `[number,number]`
## .getPositionRange()
- Returns the text between current position and the previous position.
- returning `string`
## .rejectPosition()
- Ignore current position and delete layer, Go back previous layer
## .getOffset()
- Get current position from current layer
- Returning `number`
## .setOffset(num)
- `num` - Number : Set current position from current layer