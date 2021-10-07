#include <list>
#include <cstdio>
#include <string>
#include <vector>

#define cursor unsigned long
#define cchar unsigned char

bool findArrayChar(std::vector<cchar>,cchar);

class Hemex{
    private:
        std::string text;
        cursor length = 0;
        std::vector<cchar> whitelist = {9,10,11,12,13,32,132};
        std::vector<cursor> offsetMap = {};
        cchar newline = '\n';
        cursor offset = 0;
    public:
        Hemex(){}
        Hemex(std::string b){
            this->setText(b);
        }
        int getLength(){
            return this->length;
        }
        void setText(std::string b){
            this->text = b;
            this->length = b.length();
        }
        std::string getText(){
            return this->text;
        }
        void beginPosition()
        {
            offsetMap.push_back(this->offset);
        }
        void setLastPosition(cursor e){
            if(offsetMap.empty())
            {
                this->offset = e;
            }else{
                this->offsetMap[this->offsetMap.size() - 1] = e;
            }
        }
        cursor getLastPosition()
        {
            return this->offsetMap.empty() ? this->offset : this->offsetMap.back();
        }
        void acceptPosition()
        {
            cursor r = offsetMap.back();
            offsetMap.pop_back();
            this->setLastPosition(r);
        }
        void rejectPosition()
        {
            this->offsetMap.pop_back();
        }
        cursor * positionRange()
        {
            cursor len = this->offsetMap.size();
            if(len == 0)
            {
                return new cursor[]{
                    0,
                    this->offset
                };
            }else if(len == 1){
                return new cursor[]{
                    this->offset,
                    this->offsetMap[len - 1]
                };
            }else{
                return new cursor[]{
                    this->offsetMap[len - 1],
                    this->offsetMap[len - 1]
                };
            }
        }
        std::string getPositionRange()
        {
            cursor * u = this->positionRange();
            return this->text.substr(u[0],u[1]);
        }
        cursor getOffset()
        {
            return this->getLastPosition();
        }
        cursor setOffset(cursor e)
        {
            this->setLastPosition(e);
            return this->getLastPosition();
        }
        cchar getChar(cursor a = 0)
        {
            return this->text.at(this->getOffset() + a);
        }
        bool isChar(cchar e)
        {
            return getChar() == e;
        }
        bool isEnd()
        {
            return this->length > this->getOffset();
        }
        void nextChar()
        {
            this->setOffset(this->getOffset() + 1);
        }
        void toChar(cursor m = 0)
        {
            this->setOffset(this->getOffset() + m);
        }
        std::string readWhileFunc(bool (*ptr)(Hemex,bool), bool isReverse = false)
        {
            std::vector<cchar> a;
            std::string b;
            while(this->isEnd())
            {
                bool e = ptr(*this,isReverse);
                if(e)
                {
                    cchar e = this->getChar();
                    a.push_back(e);
                    this->nextChar();
                }else{
                    b.append((char *) a.data());
                    return b;
                }
            }
            b.append((char *) a.data());
            return b;
        }
        void each(bool (*ptr)(Hemex,bool), bool isReverse = false)
        {
            while(this->isEnd())
            {
                bool e = ptr(*this,isReverse);
                if(!e)
                {
                    return;
                }else{
                    this->nextChar();
                }
            }
        }
        void whilew(bool (*ptr)(Hemex,bool), bool isReverse = false)
        {
            while(this->isEnd())
            {
                bool e = ptr(*this,isReverse);
                if(!e)
                {
                    return;
                }
            }
        }
        bool isNumber(bool isReverse = false)
        {
            cchar c = this->getChar();
            bool result = c >= 48 && c <= 57;
            return isReverse ? !result : result;
        }
        static bool isNumber(Hemex n,bool isReverse)
        {
            return n.isNumber(isReverse);
        }
        std::string readNumbers(bool isReverse = false)
        {
            return this->readWhileFunc(Hemex::isNumber, isReverse);
        }
        bool isBigLetter(bool isReverse = false)
        {
            cchar c = this->getChar();
            bool result = c >= 97 && c <= 122;
            return isReverse ? !result : result;
        }
        bool isSmallLetter(bool isReverse = false)
        {
            cchar c = this->getChar();
            bool result =  c >= 65 && c <= 90;
            return isReverse ? !result : result;
        }
        bool isLetter(bool isReverse = false)
        {
            bool result = this->isSmallLetter() || this->isBigLetter();
            return isReverse ? !result : result;
        }

        static bool isLetter(Hemex n,bool isReverse)
        {
            return n.isLetter(isReverse);
        }
        std::string readLetters(bool isReverse = false)
        {
            return this->readWhileFunc(Hemex::isLetter, isReverse);
        }
        bool isWhiteSpace(bool isReverse)
        {
            cchar c = this->getChar();
            bool result = c == '\n' ||
                c == '\r' ||
                c == '\t' ||
                c == ' ' ||
                findArrayChar(this->whitelist,c);
             return isReverse ? !result : result;
        }
        static bool isWhiteSpace(Hemex n,bool isReverse)
        {
            return n.isWhiteSpace(isReverse);
        }
        std::string readWhiteSpace(bool isReverse = false)
        {
            return this->readWhileFunc(Hemex::isWhiteSpace, isReverse);
        }
        std::string include()
        {
            
        }
};
bool findArrayChar(std::vector<cchar> a,cchar c)
{
    for(cchar b : a)
    {
        if(b == c)
        {
            return true;
        }
    }
    return false;
}