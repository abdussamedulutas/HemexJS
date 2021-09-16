function Hemex()
{

};
Hemex.EOL = "\n";
/**
 * Hemex variable white space chars
 * @type {Number[]}
 */
Hemex.WhiteSpace = [
    9,10,11,12,13,32,133
];
/**
 * Current cursor position
 * @type {Number}
 */
Hemex.prototype.offset = 0;
/**
 * Mapping offset points
 * @type {Number[]}
 */
Hemex.prototype.offsetMap = [];
Hemex.prototype.beginPosition = function(){
    this.offsetMap.push(
        this.getLastPosition()
    )
}
/**
 * Adding current position to offset map
 */
Hemex.prototype.acceptPosition = function(){
    let t = this.offsetMap.pop();
    this.setLastPosition(t)
}
/**
 * Get text range current and parent offsets
 * @returns {[Number,Number]}
 */
Hemex.prototype.positionRange = function(){
    let len = this.offsetMap.length;
    if(len == 0)
    {
        return [0,this.offset]
    }else if(len == 1){
        return [this.offset,this.offsetMap[len - 1]]
    }else{
        return [this.offsetMap[len - 2],this.offsetMap[len - 1]]
    }
}
/**
 * Get text range between current offset and parent offset
 * @returns {String}
 */
Hemex.prototype.getPositionRange = function(){
    let u = this.positionRange();
    return this.text.slice(u[0],u[1])
}
/**
 * Cancel current position and return to parent offset
 */
Hemex.prototype.rejectPosition = function(){
    this.offsetMap.pop()
}
/**
 * Get current layer of position from last offset of map
 * @returns {Number}
 */
Hemex.prototype.getLastPosition = function(){
    return this.offsetMap.length == 0 ? this.offset : this.offsetMap.slice(-1)[0]
}
/**
 * Set last position offset from offset map last layer
 * @param {Number} n 
 */
Hemex.prototype.setLastPosition = function(n){
    if(this.offsetMap.length == 0)
        this.offset = n
    else this.offsetMap[this.offsetMap.length - 1] = n
}
/**
 * Get current layer of position from last offset of map
 * Some as getLastPosition()
 * @returns {Number}
 */
Hemex.prototype.getOffset = function(){
    return this.getLastPosition()
}
/**
 * Set last position offset from offset map last layer and return it value
 * @param {Number} n 
 * @returns {Number}
 */
Hemex.prototype.setOffset = function(n){
    this.setLastPosition(n);
    return this.getLastPosition()
}
/**
 *  Get text length
 *  @type {Number}
 */
Hemex.prototype.length = 0;

/**
 * Hemex lexing data
 *  @type {String}
 */
Hemex.prototype.text = "";

/**
 * set lexing data
 * @param {String} text 
 * @returns {void}
 */
Hemex.prototype.setText = function(text){
    this.offset = 0;
    this.length = text.length;
    this.offsetMap = [];
    this.text = text;
}

/**
 * get lexing all data
 * @returns {String}
 */
Hemex.prototype.getText = function(){
    return this.text;
}
/**
 * Get one character from cursor
 * @param {Number} n 
 * @returns {String}
 */
Hemex.prototype.getChar = function(n){
    return this.text.charAt(n?this.getOffset()+n:this.getOffset())
}
/**
 * Boolean
 * @param {Number} n 
 * @returns {String}
 */
Hemex.prototype.isChar = function(b){
    return this.getChar() == b
}
/**
 * Dump all data from cursor position to end of char
 * @param {Number} n 
 */
Hemex.prototype.dump = function(n){
    return this.text.slice(this.getOffset(),this.getOffset()+n)
}
/**
 * Control coming end of line
 * @returns {Bollean}
 */
Hemex.prototype.isEnd = function(){
    return this.length > this.getOffset()
}
/**
 * Forward one char
 */
Hemex.prototype.nextChar = function(){
    this.setOffset(this.getOffset() + 1);
}
/**
 * Forward n char
 */
Hemex.prototype.toChar = function(n){
    this.setOffset(this.getOffset() + n);
}
/**
 * Reading while end of line
 * @returns {String}
 */
Hemex.prototype.getLine = function(){
    return this.readWhileFunc(function(){
        switch(this.getChar())
        {
            case Hemex.EOL: return false;
            default: return true;
        }
    }.bind(this))
}
/**
 * Read all data until the function returns false
 * @param {Boolean} p
 * @param {(char:String)=>Boolean} e 
 * @returns {String}
 */
Hemex.prototype.readWhileFunc = function(e,p){
    let k = [];
    while(this.isEnd()){
        if(e(p)) k.push(this.getChar())
        else return k.join('')
        this.nextChar();
    };
    return k.length == 0 ? false : k.join('')
}
Hemex.prototype.each = function(e,p){
    let k = [];
    while(this.isEnd())
        if(!e(p)) return;
        else this.nextChar();
}
Hemex.prototype.while = function(e,p){
    let k = [];
    while(this.isEnd())
        if(!e(p)) return;
}
/**
 * Controlling for current char type
 * @param {Boolean} reverse
 * @returns {Boolean}
 */
Hemex.prototype.isNumber = function(reverse){
    let c = this.getChar().charCodeAt(0);
    let result = c >= 48 && c <= 57;
    return reverse ? !result : result;
}
/**
 * Read all data until char type is not number
 * @param {Boolean} reverse
 * @returns {String}
 */
Hemex.prototype.readNumbers = function(reverse){
    return this.readWhileFunc(this.isNumber.bind(this),reverse)
}
/**
 * Controlling for current char type
 * @param {Boolean} reverse
 * @returns {Boolean}
 */
Hemex.prototype.isBigLetter = function(reverse){
    let c = this.getChar().charCodeAt(0);
    let result = c >= 97 && c <= 122;
    return reverse ? !result : result;
}
/**
 * Controlling for current char type
 * @param {Boolean} reverse
 * @returns {Boolean}
 */
Hemex.prototype.isSmallLetter = function(reverse){
    let c = this.getChar().charCodeAt(0);
    let result = c >= 65 && c <= 90;
    return reverse ? !result : result;
}
/**
 * Controlling for current char type
 * @param {Boolean} reverse
 * @returns {Boolean}
 */
Hemex.prototype.isLetter = function(reverse){
    let result = this.isSmallLetter() || this.isBigLetter()
    return reverse ? !result : result;
}
/**
 * Read all data until char type is not letter
 * @param {Boolean} reverse
 * @returns {String}
 */
Hemex.prototype.readLetters = function(reverse){
    return this.readWhileFunc(this.isLetter.bind(this),reverse)
}
/**
 * Controlling for current char type
 * @param {Boolean} reverse
 * @returns {Boolean}
 */
Hemex.prototype.isWhiteSpace = function(reverse){
    let c = this.getChar(),ct = c.charCodeAt(0);
    let result = (
        c == '\n' ||
        c == '\r' ||
        c == '\t' ||
        c == ' ' ||
        Hemex.WhiteSpace.includes(ct)
    )
    return reverse ? !result : result;
}
/**
 * Read all data until char type is not white space
 * @param {Boolean} reverse
 * @returns {String}
 */
Hemex.prototype.readWhiteSpace = function(reverse){
    return this.readWhileFunc(this.isWhiteSpace.bind(this),reverse)
}
/**
 * Controlling data
 * @param {Boolean} reverse
 * @returns {String}
 */
Hemex.prototype.include = function(words,next){
    this.beginPosition();
    for(let i = 0; i<words.length; i++)
    {
        if(words[i] != this.getChar())
        {
            this.rejectPosition();
            return false;
        };
        this.nextChar();
    };
    if(next) this.acceptPosition();
    else this.rejectPosition();
    return true;
}
/**
 * Controlling data
 * @param {Boolean} reverse
 * @returns {String}
 */
Hemex.prototype.includes = function(arrays,next){
    this.beginPosition();
    let flags = Array.from(arrays).fill(true);
    let index = 0;
    this.each(function(){
        let stopLoop = true;
        for(let T in arrays)
        {
            if(!flags[T] || arrays[T].length <= index) continue;
            stopLoop = false;
            flags[T] &= arrays[T][index] == this.getChar()
        };
        index++;
        return !stopLoop && flags.filter(function(val){return val}).length != 0;
    }.bind(this));
    let result = arrays.filter(function(_,index){return flags[index]});
    if(next) this.acceptPosition();
    else this.rejectPosition();
    return result.length == 0 ? false : result
}
/**
 * Parsing number formats like; 12 75.1 0xE7 0b10 +3.46
 * @returns {[String,Number]}
 */
Hemex.prototype.readNumber = function(){
    let data = [];
    let base = 10;
    let nextDot = false;
    let c = this.getChar();
    if(this.isChar('0'))
    {
        this.nextChar();
        switch(this.getChar())
        {
            case 'x':{
                base = 16;
                this.nextChar();
                data.push('0x')
                break;
            }
            case 'b':{
                base = 2;
                this.nextChar();
                data.push('0b')
                break;
            }
            default:{
                base = 8;
                this.nextChar();
                data.push('0')
            }
        }
    }else base = 10;
    this.each(()=>{
        switch(c = this.getChar())
        {
            case '0':
            case '1':{
                data.push(c);
                break;
            }
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':{
                if(base >= 8){
                    data.push(c);
                    break;
                }else return false;
            }
            case '8':
            case '9':{
                if(base >= 10){
                    data.push(c);
                    break;
                }else return false;
            }
            case 'A':
            case 'a':
            case 'B':
            case 'b':
            case 'C':
            case 'c':
            case 'D':
            case 'd':
            /* case 'E': case 'e': */
            case 'F':
            case 'f':{
                if(base >= 16){
                    data.push(c);
                    break;
                }else return false;
            }
            case '.':{
                if(!nextDot){
                    if(data.length == 0){
                        data.push("0");
                    }else data.push(".");
                    nextDot = true;
                    isFloat = true;
                }else{
                    throw new Error("Float number in Double dot");
                };
                break;
            }
            case 'E':
            case 'e':{
                if(this.getChar(1)!='+'){
                    if(base == 16){
                        data.push(c);
                        break;
                    }else return false;
                };
                if(data.length == 0){
                    this.rejectPosition();
                    return false;
                };
                data.push('e');
                this.nextChar();
                if(this.getChar()=='+' || this.getChar()=='-'){
                    data.push(char());
                    this.nextChar();
                };
                let result = null;
                this.each(()=>{
                    switch(this.getChar()){
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':{
                            data.push(this.getChar());
                            this.nextChar();
                            break;
                        }
                        default:{
                            return false;
                        }
                    }
                })
            }
            default:{
                return false;
            }
        };
        return true
    });
    return data.length == 0 ? false : [data.join(''),base]
}


module.exports = Hemex;