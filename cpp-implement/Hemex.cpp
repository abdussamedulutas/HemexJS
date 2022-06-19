#ifndef HEMEX_LEXING_LIB

#define HEMEX_LEXING_LIB

#include <string>
#include <vector>
#include <functional>
typedef unsigned int positive;

namespace Hemex
{
    int min(int a, int b)
    {
        return a < b ? a : b;
    }
    
    int max(int a, int b)
    {
        return a > b ? a : b;
    }
    enum HemexNumberBase {
        BASE_2 = 2,
        BASE_8 = 8,
        BASE_10 = 10,
        BASE_16 = 16
    };
    struct ReadNumberResult
    {
        bool isFloat = false;
        bool success = false;
        int base = BASE_10;
        std::string text;
    };

    template <typename KeyType, typename ValueType>
    struct MapItem
    {
        KeyType name;
        ValueType value;
    };
    template <typename KeyType, typename ValueType>
    struct MapPos
    {
        MapItem<KeyType,ValueType> mapitem;
        int position = 0;
        bool finded = false;
    };

    template <typename KeyType, typename ValueType>
    class Map
    {
        private:
            std::vector<MapItem<KeyType,ValueType>> e;
        public:
            void clear(){
                this->e.clear();
            }
            void remove(KeyType key){
                MapPos<KeyType,ValueType> find = this->has(key);
                if(find.finded)
                {
                    this->e.erase(this->e.begin() + find.position);
                }
            }
            std::vector<MapItem<KeyType,ValueType>> entries(){
                return this->e;
            }
            void forEach(std::function<void(KeyType,ValueType,int)> callback){
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    MapItem<KeyType,ValueType> item = this->e.at(T);
                    callback(item.name, item.value, T);
                };
            }
            ValueType get(KeyType key){
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    MapItem<KeyType,ValueType> item = this->e.at(T);
                    if(item.name == key)
                    {
                        return item.value;
                    }
                };
                return;
            }
            ValueType at(size_t key){
                MapItem<KeyType,ValueType> item = this->e.at(key);
                return item.value;
            }
            MapPos<KeyType,ValueType> has(KeyType key){
                MapPos<KeyType,ValueType> e;
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    MapItem<KeyType,ValueType> item = this->e.at(T);
                    if(item.name == key)
                    {
                        e.finded = true;
                        e.mapitem = item;
                        e.position = T;
                    }
                };
                return e;
            }
            std::vector<KeyType> keys(){
                std::vector<KeyType> e;
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    MapItem<KeyType,ValueType> item = this->e.at(T);
                    e.push_back(item.name);
                };
                return e;
            }
            void set(KeyType name, ValueType value){
                MapItem<KeyType,ValueType> e;
                e.name = name;
                e.value = value;
                MapPos<KeyType,ValueType> k = this->has(name);
                if(k.finded == false)
                {
                    this->e.push_back(e);
                }else{
                    this->e.at(k.position).value = value;
                }
            }
            int size(){
                return this->e.size();
            }
            std::vector<ValueType> values(){
                std::vector<ValueType> e;
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    MapItem<KeyType,ValueType> item = this->e.at(T);
                    e.push_back(item.name);
                };
                return e;
            }
    };
    template <typename ValueType>
    struct SetPos
    {
        ValueType mapitem;
        int position = 0;
        bool finded = false;
    };
    template <typename ValueType>
    class Set
    {
        private:
            std::vector<ValueType> e;
        public:
            void clear(){
                this->e.clear();
            }
            void remove(ValueType value){
                SetPos<ValueType> find = this->has(value);
                if(find.finded)
                {
                    this->e.erase(this->e.begin() + find.position);
                }
            }
            std::vector<ValueType> entries(){
                return this->e;
            }
            void forEach(std::function<void(ValueType,int)> callback){
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    ValueType item = this->e.at(T);
                    callback(item.value, T);
                };
            }
            SetPos<ValueType> has(ValueType key){
                SetPos<ValueType> e;
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    ValueType item = this->e.at(T);
                    if(item == key)
                    {
                        e.finded = true;
                        e.mapitem = item;
                        e.position = T;
                    }
                };
                return e;
            }
            void add(ValueType value){
                SetPos<ValueType> k = this->has(value);
                if(k.finded == false)
                {
                    this->e.push_back(e);
                }else{
                    this->e.at(k.position).value = value;
                }
            }
            int size(){
                return this->e.size();
            }
            std::vector<ValueType> values(){
                std::vector<ValueType> e;
                int size = this->e.size();
                for (int T = 0; T < size;T++)
                {
                    ValueType item = this->e.at(T);
                    e.push_back(item);
                };
                return e;
            }
    };

    struct IncludesResult
    {
        bool success;
        std::vector<std::string> matched;
        bool search(std::string word)
        {
            for(std::string matches : this->matched)
            {
                if(matches == word)
                {
                    return true;
                }
            }
            return false;
        }
    };

    const char EOL = (char) 10;
    const char whitespace[] = {
        (char) 9,
        (char) 10,
        (char) 11,
        (char) 12,
        (char) 13,
        (char) 32,
        (char) 133
    };
    class Hemex
    {
        public:
        bool DEBUG = false;
        positive offset = 0;
        std::vector<positive> offsetMap;
        std::string text;
        positive length = 0;
        long int step = 0;

        void setText(std::string text)
        {
            if(text.size() == 0)
            {
                return;
            }
            this->text = text;
            this->length = text.size();
            this->offset = 0;
            this->offsetMap = std::vector<positive>();
        }

        std::string getText()
        {
            return this->text;
        }
        void beginPosition()
        {
            this->offsetMap.push_back(this->getLastPosition());
        }
        positive getLastPosition()
        {
            if(this->offsetMap.size() == 0)
            {
                return this->offset;
            }
            else
            {
                return this->offsetMap[this->offsetMap.size() - 1];
            }
        }
        void acceptPosition()
        {
            positive T = this->offsetMap[this->offsetMap.size() - 1];
            this->setLastPosition(T);
        }
        void rejectPosition()
        {
            this->offsetMap.pop_back();
        }
        void setLastPosition(positive n)
        {
            if(this->offsetMap.size() == 0)
            {
                this->offset = n;
            }
            else
            {
                this->offsetMap[this->offsetMap.size() - 1] = n;
            }
        }
        positive * positionRange()
        {
            std::size_t len = this->offsetMap.size();
            if(len == 0)
            {
                return new positive[2]{0, this->offset};
            }
            else if(len == 1)
            {
                return new positive[2]{
                    this->offset,
                    this->offsetMap[len - 1]
                };
            }else{
                return new positive[2]{
                    this->offsetMap[len - 2],
                    this->offsetMap[len - 1]
                };
            }
        }
        std::string getPositionRange()
        {
            positive *A = this->positionRange();
            std::string mem;

            for (positive i = A[0]; i < A[1];i++)
            {
                mem.push_back(this->text.at(i));
            }
            return mem;
        }
        positive getOffset()
        {
            return this->getLastPosition();
        }
        positive setOffset(positive n)
        {
            this->setLastPosition(n);
            return this->getLastPosition();
        }



        char getChar(positive additionalOffset = 0)
        {
            return this->text.at(this->getOffset() + additionalOffset);
        }

        bool isChar(char b)
        {
            if(this->isEnd()) return false;
            return this->getChar() == b;
        }

        const char* dump(positive offset = 0, positive length = 10)
        {
            positive start = this->getOffset() + offset;
            positive end = min(
                this->getOffset() + offset + length,
                this->length
            );

            std::string mem;

            for (positive i = start; i < end;i++)
            {
                mem.push_back(this->text.at(i));
            };
            return mem.data();
        }
        bool isEnd()
        {
            bool result = this->length <= this->getOffset();
            return result;
        }
        void nextChar()
        {
            if(this->isEnd()) return;
            this->setOffset(this->getOffset() + 1);
        }
        void toChar(positive n)
        {
            if(this->isEnd()) return;
            this->setOffset(this->getOffset() + n);
        }
        std::string readWhileFunc(std::function<bool(char,bool)> callback, bool p = false)
        {
            std::string result;
            while(!this->isEnd())
            {
                bool sonuc = callback(this->getChar(),p);
                if(sonuc)
                {
                    result.push_back(this->getChar());
                }
                else
                {
                    return result;
                }
                this->nextChar();
            }
            return result;
        }
        void Each(std::function<bool(char,bool)> callback, bool p = false)
        {
            while(!this->isEnd())
            {
                bool sonuc = callback(this->getChar(),p);
                if(!sonuc)
                {
                    return;
                }
                this->nextChar();
            }
        }
        void While(std::function<bool(char,bool)> callback, bool reverse = false)
        {
            while(!this->isEnd())
            {
                bool sonuc = callback(this->getChar(),reverse);
                if(!sonuc)
                {
                    return;
                }
            }
        }
        static bool isNewLine(char a, bool reverse = true)
        {
            switch(a)
            {
                case EOL: return reverse;
                default: return !reverse;
            }
        }
        bool isNewLine()
        {
            char a = this->getChar();
            bool reverse = true;
            switch(a)
            {
                case EOL: return reverse;
                default: return !reverse;
            }
        }
        static bool isNumber(char a, bool reverse = true)
        {
            bool result = (a >= 48 && a <= 57);
            return reverse ? !result : result;
        }
        bool isNumber()
        {
            char a = this->getChar();
            bool reverse = true;
            bool result = (a >= 48 && a <= 57);
            return reverse ? result : !result;
        }

        static bool isBigLetter(char a, bool reverse = true)
        {
            bool result = (a >= 97 && a <= 122);
            return reverse ? !result : result;
        }
        bool isBigLetter()
        {
            char a = this->getChar();
            bool reverse = true;
            bool result = (a >= 97 && a <= 122);
            return reverse ? result : !result;
        }
        static bool isSmallLetter(char a, bool reverse = true)
        {
            bool result = (a >= 65 && a <= 90);
            return reverse ? !result : result;
        }
        bool isSmallLetter()
        {
            char a = this->getChar();
            bool reverse = true;
            bool result = (a >= 65 && a <= 90);
            return reverse ? result : !result;
        }
        static bool isLetter(char a, bool reverse = true)
        {
            bool result = Hemex::isSmallLetter(a,reverse) || Hemex::isBigLetter(a,reverse);
            return reverse ? !result : result;
        }
        bool isLetter()
        {
            char a = this->getChar();
            bool reverse = true;
            bool result = this->isSmallLetter() || this->isBigLetter();
            return reverse ? result : !result;
        }
        static bool isWhiteSpace(char a, bool reverse = true)
        {
            bool result = false;
            for(char spacechar : whitespace)
            {
                if(a == spacechar)
                {
                    result = result || true;
                }
            }
            return reverse ? !result : result;
        }
        bool isWhiteSpace()
        {
            char a = this->getChar();
            bool reverse = true;
            bool result = false;
            for(char spacechar : whitespace)
            {
                if(a == spacechar)
                {
                    result = result || true;
                }
            }
            return reverse ? result : !result;
        }
        std::string getLine()
        {
            return this->readWhileFunc([](char c,bool b) -> bool {
                return Hemex::isNewLine(c,b);
            });
        }
        std::string readNumbers()
        {
            return this->readWhileFunc([](char c,bool b) -> bool {
                return Hemex::isNumber(c,b);
            });
        }
        std::string readLetters()
        {
            return this->readWhileFunc([](char c,bool b) -> bool {
                return Hemex::isLetter(c,b);
            });
        }
        std::string readWhitespace()
        {
            return this->readWhileFunc([](char c,bool b) -> bool {
                return Hemex::isWhiteSpace(c,b);
            });
        }
        bool include(std::string word,bool accept = true)
        {
            this->beginPosition();
            for (positive i = 0; i < word.size(); i++)
            {
                if(word.at(i) != this->getChar())
                {
                    this->rejectPosition();
                    return false;
                }
                this->nextChar();
            }
            if(accept)
            {
                this->acceptPosition();
            }
            else
            {
                this->rejectPosition();
            };
            return true;
        }
        IncludesResult includes(std::vector<std::string> arrays, bool accept = true)
        {
            int arraySize = arrays.size();
            IncludesResult result;
            this->beginPosition();
            bool * flags = (bool *) calloc(arraySize,sizeof(bool));
            for (int T = 0; T < arraySize; T++) flags[T] = true;
            int index = 0;
            this->While([&](char e,bool reserve) -> bool{
                bool stopLoop = true;
                for (int T = 0; T < arraySize; T++)
                {
                    if(!flags[T] || arrays.at(T).size() <= index)
                    {
                        continue;
                    }
                    stopLoop = false;
                    if(flags[T])
                    {
                        flags[T] = arrays.at(T).at(index) == e;
                    }
                }
                index++;
                bool allFlags = true;
                for (int T = 0; T < arraySize; T++)
                {
                    if(flags[T])
                    {
                        allFlags = false;
                    }
                };
                if(stopLoop || allFlags)
                {
                    return false;
                }
                else
                {
                    this->nextChar();
                }
                return true;
            });


            int indis = 0;
            for (int T = 0; T < arraySize; T++)
            {
                if(flags[T])
                {
                    if(result.success == false)
                    {
                        result.success = true;
                    };
                    result.matched.push_back(arrays.at(T));
                }
            }
            if(accept)
            {
                this->acceptPosition();
            }
            else
            {
                this->rejectPosition();
            };
            return result;
        }
        ReadNumberResult readNumber(bool addNumberHeader = false)
        {
            ReadNumberResult result;
            bool nextDot = false;
            if(this->isChar('0'))
            {
                this->nextChar();
                switch (this->getChar())
                {
                    case 'x':{
                        result.base = BASE_16;
                        if(addNumberHeader){
                            result.text.push_back('0');
                            result.text.push_back('x');
                        }
                        this->nextChar();
                        break;
                    }
                    case 'b':{
                        result.base = BASE_2;
                        if(addNumberHeader){
                            result.text.push_back('0');
                            result.text.push_back('b');
                        }
                        this->nextChar();
                        break;
                    }
                    default:{
                        result.base = BASE_8;
                        if(addNumberHeader){
                            result.text.push_back('0');
                        }
                        this->nextChar();
                        break;
                    }
                }
            }else{
                result.base = BASE_10;
            };


            this->Each([&](char chr,bool reverse) -> bool {
                char c = this->getChar();
                switch (c)
                {
                    case '0':
                    case '1':
                    {
                        result.text.push_back(c);
                        break;
                    }
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':{
                        if(result.base >= 8){
                            result.text.push_back(c);
                            break;
                        }else return false;
                    }
                    case '8':
                    case '9':{
                        if(result.base >= 10){
                            result.text.push_back(c);
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
                    case 'F':
                    case 'f':{
                        if(result.base >= 16){
                            result.text.push_back(c);
                            break;
                        }else return false;
                    }
                    case '.':{
                        if(!nextDot){
                            if(result.text.size() == 0){
                                result.text.push_back('0');
                            }else result.text.push_back('.');
                            nextDot = true;
                            result.isFloat = true;
                        }else{
                            return false;
                        };
                        break;
                    }
                    case 'e':{
                        if(this->getChar(1) != '+'){
                            if(result.base == BASE_16){
                                result.text.push_back(c);
                                break;
                            }else return false;
                        };
                        if(result.text.size() == 0){
                            return false;
                        };
                        result.text.push_back('e');
                        this->nextChar();
                        if(this->isChar('+') || this->isChar('-')){
                            result.text.push_back(this->getChar());
                            this->nextChar();
                        };
                        this->Each([&](char chr,bool reverse) -> bool{
                            switch(this->getChar()){
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
                                    result.text.push_back(this->getChar());
                                    this->nextChar();
                                    break;
                                }
                                default:{
                                    return false;
                                }
                            };
                            return true;
                        });
                    }
                    default:{
                        return false;
                    }
                };
                return true;
            });
            return result;
        };
        Map<std::string,std::function<void(Hemex*)>> lexers;

        void addLexer(
            std::string name,
            std::function<void(Hemex*)> callback
        )
        {
            if(this->lexers.has(name).finded == false)
            {
                this->lexers.set(name, callback);
            }
        }
        void gather(std::string jobname)
        {
            MapPos<std::string, std::function<void (Hemex *)>> bes;
            bes = this->lexers.has(jobname);
            if(bes.finded)
            {
                bes.mapitem.value(this);
            }
        }
    };
    class HemexMapTree
    {
        public:
        std::string name;
        std::string type;
        Map<std::string, std::string> attributes;
        Map<std::string, HemexMapTree> childrens;
        HemexMapTree operator[](int index)
        {
            return this->childrens.at(index);
        }
        HemexMapTree operator[](std::string index)
        {
            MapPos<std::string, HemexMapTree> k = this->childrens.has(index);
            if(k.finded)
            {
                return k.mapitem.value;
            }
        }
    };
    char * readAllFile(std::string path)
    {
        FILE *file;
        file = fopen(path.data(), "r");
        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        fseek(file, 0, SEEK_SET);
        char * content = (char *) malloc(fsize);
        fread(content, fsize, 1, file);
        fclose(file);
        return content;
    }
}

#endif