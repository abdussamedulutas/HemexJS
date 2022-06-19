#include <string>
#include <vector>
#include <functional>

namespace Hemex
{
    int min(int a, int b);
    int max(int a, int b);
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
            void clear;
            void remove(KeyType key);
            std::vector<MapItem<KeyType,ValueType>> entries();
            void forEach(std::function<void(KeyType,ValueType,int)> callback);
            ValueType get(KeyType key);
            ValueType at(size_t key);
            MapPos<KeyType,ValueType> has(KeyType key);
            std::vector<KeyType> keys();
            void set(KeyType name, ValueType value);
            int size();
            std::vector<ValueType> values();
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
            void clear();
            void remove(ValueType value);
            std::vector<ValueType> entries();
            void forEach(std::function<void(ValueType,int)> callback);
            SetPos<ValueType> has(ValueType key);
            void add(ValueType value);
            int size();
            std::vector<ValueType> values();
    };

    struct IncludesResult
    {
        bool success;
        std::vector<std::string> matched;
        bool search(std::string word);
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
        unsigned int offset = 0;
        std::vector<unsigned int> offsetMap;
        std::string text;
        unsigned int length = 0;
        long int step = 0;
        void setText(std::string text);
        std::string getText();
        void beginPosition();
        unsigned int getLastPosition();
        void acceptPosition();
        void rejectPosition();
        void setLastPosition(unsigned int n);
        unsigned int * positionRange();
        std::string getPositionRange();
        unsigned int getOffset();
        unsigned int setOffset(unsigned int n);
        char getChar(unsigned int additionalOffset = 0);
        bool isChar(char b);
        char * dump(unsigned int offset = 0, unsigned int length = 10);
        bool isEnd();
        void nextChar();
        void toChar(unsigned int n);
        std::string readWhileFunc(std::function<bool(char,bool)> callback, bool p = false);
        void Each(std::function<bool(char,bool)> callback, bool p = false);
        void While(std::function<bool(char,bool)> callback, bool reverse = false);
        static bool isNewLine(char a, bool reverse = true);
        bool isNewLine();
        static bool isNumber(char a, bool reverse = true);
        bool isNumber();
        static bool isBigLetter(char a, bool reverse = true);
        bool isBigLetter();
        static bool isSmallLetter(char a, bool reverse = true);
        bool isSmallLetter();
        static bool isLetter(char a, bool reverse = true);
        bool isLetter();
        static bool isWhiteSpace(char a, bool reverse = true);
        bool isWhiteSpace();
        std::string getLine();
        std::string readNumbers();
        std::string readLetters();
        std::string readWhitespace();
        bool include(std::string word,bool accept = true);
        IncludesResult includes(std::vector<std::string> arrays, bool accept = true);
        ReadNumberResult readNumber(bool addNumberHeader = false);
        Map<std::string,std::function<void(Hemex)>> lexers;
        void addLexer(std::string name,std::function<void(Hemex)> callback);
        Map<std::string,std::string> gather(std::string jobname);
    };
    class HemexMapTree
    {
        public:
        std::string name;
        std::string type;
        Map<std::string, std::string> attributes;
        Map<std::string, HemexMapTree> childrens;
        HemexMapTree operator[](int index);
        HemexMapTree operator[](std::string index);
    };
    char * readAllFile(std::string path);
}