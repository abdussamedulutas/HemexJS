let Hemex = require("../Hemex");

const Priority = {
    '/': 11,
    '*': 10,
    '%': 9,
    '+': 8,
    '-': 7,
    '<<': 6,
    '>>': 5,
    '>>>': 4,
    '&': 3,
    '^': 2,
    '|': 1
};
const PriorityLayer = 11;

function ArithmeticParser()
{
    let hmx = new Hemex();
    this.parse = function(text){
        hmx.setText(text);
        let _var = +1, _var_is = false, _var_sing = '';
        let operators = [];
        let variables = [];
        let priorities = [];

        var preOrder = () =>  operators.length < variables.length || operators.length == variables.length ? 'var' : 'opt'

        let pharantesisLevel = 0;
        hmx.while(function(){
            let c = null;
            hmx.readWhiteSpace();
            switch(c = hmx.getChar())
            {
                case '(':
                case ')':{
                    if(c == '(')
                    {
                        pharantesisLevel += 11;
                    }else if(c == ')'){
                        pharantesisLevel -= 11;
                    }
                    hmx.toChar(+1);
                    break;
                }
                case '+':{
                    if(!_var_is)
                    {
                        _var_sing = '+';
                        _var *= +1;
                        hmx.nextChar();
                    }else{
                        if(preOrder() == 'opt'){
                            throw "Syntax Error";
                        }
                        operators.push(c);
                        priorities.push(pharantesisLevel + Priority[c]);
                        _var_is = true;
                        hmx.nextChar();
                    }
                    break;
                }
                case '-':{
                    if(!_var_is)
                    {
                        _var_sing = '-';
                        _var *= -1;
                        hmx.nextChar();
                    }else{
                        if(preOrder() == 'opt'){
                            throw "Syntax Error";
                        }
                        operators.push(c);
                        priorities.push(pharantesisLevel + Priority['-']);
                        _var_is = true;
                        hmx.nextChar();
                    }
                    break;
                }
                case '<':
                case '>':{
                    if(preOrder() == 'opt'){
                        throw "Syntax Error";
                    }
                    if(hmx.include('<<'))
                    {
                        operators.push('<<');
                        priorities.push(pharantesisLevel + Priority['<<']);
                        _var_is = false;
                        hmx.nextChar();
                        hmx.toChar(+2);
                    }else if(hmx.include('>>>')){
                        operators.push('>>>');
                        priorities.push(pharantesisLevel + Priority['>>>']);
                        _var_is = false;
                        hmx.toChar(+3);
                    }else if(hmx.include('>>')){
                        operators.push('>>');
                        priorities.push(pharantesisLevel + Priority['>>']);
                        _var_is = false;
                        hmx.toChar(+2);
                    }else{
                        throw "Syntax Error";
                    }
                    break;
                }
                case '*':
                case '/':
                case '%':
                case '&':
                case '^':
                case '|':{
                    if(preOrder() == 'opt'){
                        throw "Syntax Error";
                    }
                    operators.push(c);
                    priorities.push(pharantesisLevel + Priority[c]);
                    _var_is = false;
                    hmx.nextChar();
                    break;
                }
                default:{
                    if(hmx.isNumber())
                    {
                        let num = hmx.readNumber();
                        let lett;

                        if(num[1] == 10)
                        {
                            lett = parseFloat(num[0]);
                        }else{
                            lett = parseInt(num[0],num[1]);
                        }
                        variables.push(lett * _var);
                        _var_is = true;
                        _var_sing = '';
                        _var = +1;
                    }else throw "Syntax Error";
                }
            };
            hmx.readWhiteSpace();
            return true;
        })

        let codes = [], loop = 0, NS = {index:0};
        while(operators.length > 0)
        {
            let optIndex = -1;
            let optPriority = -1;
            for(let index = 0; index < priorities.length; index++)
            {
                if(priorities[index] == -1) continue;
                if(optPriority < priorities[index]){
                    optPriority = priorities[index];
                    optIndex = index;
                }
            };

            if(optIndex == -1) break;
            

            let leftHandVariable = variables[optIndex];
            let rightHandVariable = variables[optIndex + 1];
            let bigOpt = operators[optIndex];
            let n = `TEMP${NS.index++}`;
            codes.push(`${n} = ${leftHandVariable} ${bigOpt} ${rightHandVariable}`);
            variables = variables.map((_,index) => optIndex + 1 != index ? _ : n);

            priorities = priorities.filter((_,index) => optIndex != index);
            operators = operators.filter((_,index) => optIndex != index);
            variables = variables.filter((_,index) => optIndex != index);

            loop++;
        }
        return codes;
    };
}
module.exports = ArithmeticParser;