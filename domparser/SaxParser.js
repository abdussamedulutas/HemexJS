let Hemex = require("../Hemex");

/** @class */
function SaxParser()
{
    let hmx = new Hemex();


    // Lexing : \r\n space esc other whitespaces
    hmx.addLexer({
        name:"trySkipWhiteSpace",
    },function(hmx){
        if(hmx.isWhiteSpace()) hmx.readWhiteSpace();
    });

    // Lexing : Tag name and proprty name = ABC | svg:circle  | tag_name | data$weak
    hmx.addLexer({
        name:"tryParseTagName",
    },function(hmx){
        if(!hmx.isLetter())
        {
            return;
        };
        return hmx.readWhileFunc(()=> {
            return hmx.isLetter() || hmx.isNumber() || hmx.includes([':','_','-','$'])
        })
    });

    // Lexing : Tag property value = "string" implodedvalue   298
    hmx.addLexer({
        name:"tryParseTagPropertyValue",
    },function(hmx){
        hmx.gather("trySkipWhiteSpace");
        let p;
        if(p = hmx.includes(['\'','"','`']))
        {
            hmx.nextChar();
            return hmx.gather("tryParseString",p[0]);
        }else if(hmx.isNumber())
        {
            return hmx.readNumber()[0]
        }else{
            return hmx.gather("tryParseTagName");
        }
    });

    // Lexing : Parsing string = "abc"   'Abc' 'Ab\'c'
    hmx.addLexer({
        name:"tryParseString",
    },function(hmx,dot){
        let data = [];
        hmx.while(()=>{
            switch(hmx.getChar())
            {
                case dot:{
                    hmx.nextChar();
                    return false;
                }
                case '\\':{
                    hmx.nextChar();
                    data.push(hmx.getChar())
                    return true;
                }
                default:{
                    data.push(hmx.getChar());
                    hmx.nextChar();
                    return true;
                }
            }
        });
        return data.join('');
    });

    // Lexing : tag property=  <a b=c>  <a b:c=d> <a b>  <a b:c>  <a b:c="def">  <a b:c=27> 
    hmx.addLexer({
        name:"tryParseTagProperties",
    },function(hmx){
        let options = {};
        hmx.while(()=>{
            hmx.gather("trySkipWhiteSpace");
            if(!hmx.isLetter())
            {
                return false;
            };
            let name = hmx.gather("tryParseTagName");
            hmx.gather("trySkipWhiteSpace");
            if(hmx.isChar('='))
            {
                hmx.nextChar();
                let value = hmx.gather("tryParseTagPropertyValue");
                options[name] = value;
            }else{
                options[name] = "";
            };
            if(hmx.isWhiteSpace()) return true;
        });
        return options;
    });


    // Lexing : tag body = <a/>  <a></a>  <a><b></b></a> <a> data </a>
    hmx.addLexer({
        name:"tryParseTag",
    },function(hmx){
        hmx.beginPosition();
        hmx.gather("trySkipWhiteSpace");
        if(!hmx.isChar('<') || hmx.include('</'))
        {
            hmx.rejectPosition();
            return;
        }
        hmx.nextChar();
        let tagName = hmx.gather("tryParseTagName");
        let options = hmx.gather("tryParseTagProperties");
        hmx.gather("trySkipWhiteSpace");
        if(hmx.include('/>'))
        {
            hmx.toChar(2);
            hmx.gather("trySkipWhiteSpace");
            hmx.acceptPosition();
            return [tagName, options,[]];
        }else if(hmx.include('>')){
            hmx.nextChar();
            let childs = hmx.gather('tryParseScope',true);
            hmx.gather("trySkipWhiteSpace");
            let closeTag = '</'+tagName+'>';
            if(hmx.include(closeTag))
            {
                hmx.toChar(closeTag.length);
            }
            return [tagName, options,childs];
        }else{
            hmx.rejectPosition();
            return;
        }
    });

    // Lexing : tag without everything = abc def 123456   0x2888, 247
    // Lexing : Crashed tags =   <abc  <bef\>    <a>link<\a>
    hmx.addLexer({
        name:"tryParseData",
    },function(hmx, scope){
        hmx.beginPosition();
        hmx.gather("trySkipWhiteSpace");
        let data = [];
        if(hmx.isChar('<') && scope){
            data = ['<'];
            hmx.nextChar();
        };
        let f = hmx.readWhileFunc(()=>{
            return !hmx.isChar('<')
        });
        if(f) data.push(f);
        hmx.acceptPosition();
        if(data.length)
        {
            return data.join('').trim();
        }else{
            return null;
        }
    });

    // Lexing : Comments
    hmx.addLexer({
        name:"tryParseComment",
    },function(hmx, scope){
        hmx.beginPosition();

        if(!hmx.include('<!--'))
        {
            hmx.rejectPosition();
            return;
        }else{
            hmx.toChar(4);
        }
        hmx.each(()=>{
            if(hmx.include('-->'))
            {
                hmx.toChar(4);
                return false;
            }else{
                return true;
            }
        });

        return true;
    });

    // Lexing : Parsing scope
    hmx.addLexer({
        name:"tryParseScope",
    },function(hmx,eatBrokenTag){
        let childs = [];
        hmx.while(()=>{
            hmx.gather("trySkipWhiteSpace");
            let item;
            if(hmx.isChar('<'))
            {
                item = hmx.gather("tryParseTag");
                if(item)
                {
                    childs.push(item)
                };
            };
            if(!item){
                item = hmx.gather("tryParseComment");
            };
            if(!item){
                item = hmx.gather("tryParseData",eatBrokenTag ? false : true);
                if(item)
                {
                    childs.push(['#data',item])
                };
            };
            return !!item;
        });
        return childs;
    });

    this.data = [];

    this.parse = function(text){
        hmx.setText(text);
        return this.data = hmx.gather("tryParseScope");
    };
};

module.exports = SaxParser;