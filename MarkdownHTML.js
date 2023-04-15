Hemex.parsers.set('markdown',HMXMarkdownHTML);

function HMXMarkdownHTML()
{
    this.mdcode = "";
    this.htmlcode = "";
    this.setMDCode = val => this.mdcode = val;
    this.getMDCode = () => this.htmlcode;
    this.parse = function(text){
        if(text)
        {
            this.mdcode = text;
        }
        let AST = MarkdownASTParser(this.mdcode);
        debugger;
    };
};

function MarkdownASTParser(text)
{
    let AST = [];
    /**
     * @type {import("./Hemex")}
     */
    let hmx = new Hemex();
    hmx.setText(text);


    hmx.addLexer({
        name: "scope"
    },(hmx)=>{
        debugger;
    });

    hmx.gather('scope');
    return AST;
}