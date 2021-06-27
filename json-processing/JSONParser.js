let Hemex = require("../Hemex");

function JSONParser()
{
    // Memory utilization
    this.map = null;
    this.text =  "";
    // registry data to parser
    let hmx = new Hemex();

    /**
     * Parse Array, object or value
     * @param {Hemex} hmx 
     */
    function tryParseScope(hmx)
    {
        // Skip spaces
        if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
        if(hmx.isChar('['))
        {
            return tryParseArray(hmx)
        }
        if(hmx.isChar('{'))
        {
            return tryParseObject(hmx)
        }
        return tryParseValue(hmx)
    }

    /**
     * Parse Array object
     * @param {Hemex} hmx 
     */
    function tryParseArray(hmx)
    {
        let result = [];
        if(hmx.isChar('[')) hmx.nextChar();
        hmx.while(()=>{
            // Skip spaces
            if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
            // Read array, object and values
            let data = tryParseScope(hmx);
            result.push(data);
            // Skip spaces
            if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
            // Detect delimiter and stop or continue
            if(hmx.isChar(','))
            {
                hmx.nextChar();
                return true;
            }else if(hmx.isChar(']')){
                hmx.nextChar();
                return false;
            }else{
                throw new Error("Unexpected end of Array list")
            }
        });
        return result;
    }

    /**
     * Parse Named object
     * @param {Hemex} hmx 
     */
    function tryParseObject(hmx)
    {
        let result = {};
        if(hmx.isChar('{')) hmx.nextChar();
        hmx.while(()=>{
            // Skip spaces
            if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
            // Read name
            let name = tryParseValue(hmx);
            // Skip spaces and derimiter between value and name
            if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
            if(hmx.isChar(':')) hmx.nextChar();
            if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
            // Read array, object and values
            let data = tryParseScope(hmx);
            result[name] = data;
            // Skip spaces
            if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
            // Detect delimiter and stop or continue
            if(hmx.isChar(','))
            {
                hmx.nextChar();
                return true;
            }else if(hmx.isChar('}')){
                hmx.nextChar();
                return false;
            }else{
                throw new Error("Unexpected end of Array list")
            }
        });
        return result;
    }
    
    /**
     * Parse values: true false 14 489 and Strings
     * @param {Hemex} hmx 
     */
    function tryParseValue(hmx)
    {
        let res;
        // is number
        if(hmx.isNumber())
        {
            // Backup position
            hmx.beginPosition();
            let t = hmx.readNumber();
            if(!t)
            {
                hmx.rejectPosition();
                throw new Error("Unexpected number valuue")
            }
            hmx.acceptPosition();
            return t[1] != 10 ? parseInt(t[0],t[1]) : parseFloat(t[0],t[1]);
        }
        // is boolean
        if(res = hmx.includes(["true","false"]))
        {
            hmx.toChar(res[0].length);
            return res == "true"
        }
        // is string
        if(res = hmx.includes(["'","\""]))
        {
            return tryParseString(hmx,res[0]);
        }
    };
    /**
     * Parse string: "abc" 'Hi \' this is compact string'
     * @param {Hemex} hmx 
     */
    function tryParseString(hmx,res)
    {
        let data = [];
        // Backup position
        hmx.beginPosition();
        if(hmx.isChar(res)) hmx.nextChar();
        hmx.each(()=>{
            let char = hmx.getChar();
            switch(char)
            {
                case '\\':{
                    // Skip next char
                    hmx.nextChar();
                    // and add data
                    data.push('\\'+hmx.getChar());
                    return true;
                }
                case res:{
                    // Skip next char
                    hmx.nextChar();
                    // End of string return data
                    return false;
                }
                default:{
                    // add char to data
                    data.push(char)
                    return true;
                }
            };
        });
        // Commit position
        hmx.acceptPosition();
        return data.join('')
    }


    this.parse = function(text){
        hmx.setText(text);
        let value = tryParseScope(hmx);
        debugger;
    }
}

module.exports = JSONParser;

// Testing
let u = new JSONParser();
u.parse(`[ "Merhab",56    ,  {"abc":false,85:14} ]`);
// looking result
console.log(u.map);