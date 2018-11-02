#pragma once

#include "fl/Common.h"
#include "fl/Types.h"

#include <string>
#include <sstream>
typedef std::string String;

namespace fl {

    #define STRINGFORMAT_BUFFER_SIZE 10 * 1024

    class FL_API StringFormat
    {
    private:
        static char* s_Buffer;
    public:
        template<typename T>
        static String Hex(const T& input)
        {
            memset(s_Buffer, 0, STRINGFORMAT_BUFFER_SIZE);
            sprintf(s_Buffer, "%02x", input);
            return String(s_Buffer);
        }

        template<typename T>
        static String Hex(const T* input, uint size)
        {
            memset(s_Buffer, 0, STRINGFORMAT_BUFFER_SIZE);
            for (uint i = 0; i < size; i++)
                sprintf(s_Buffer + i * 3, "%02x ", input[i]);
            return String(s_Buffer);
        }

        static String Float(const float input, uint places = 2)
        {
            memset(s_Buffer, 0, STRINGFORMAT_BUFFER_SIZE);
            sprintf(s_Buffer, "%.2f", input);
            return String(s_Buffer);
        }

        template<typename T>
        static String ToString(const T& input)
        {
            return std::to_string(input);
        }
    };

    class FL_API BitStringBuilder {
    private:
        static const size_t MAX_BYTE_BIT_LENGTH;
        static const size_t MAX_SHORT_BIT_LENGTH;
        static const size_t MAX_INT_BIT_LENGTH;
        static const size_t MAX_LONG_BIT_LENGTH;
        static const size_t MAX_LONG_LONG_BIT_LENGTH;
    public:
        BitStringBuilder& AppendBit(const bool& value);

        BitStringBuilder& AppendByte(const char& value, const size_t& length = MAX_BYTE_BIT_LENGTH);

        BitStringBuilder& AppendByte(const char& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendShort(const short& value, const size_t& length = MAX_SHORT_BIT_LENGTH);

        BitStringBuilder& AppendShort(const short& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendInt(const int& value, const size_t& length = MAX_INT_BIT_LENGTH);

        BitStringBuilder& AppendInt(const int& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendLong(const long& value, const size_t& length = MAX_LONG_BIT_LENGTH);

        BitStringBuilder& AppendLong(const long& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendLongLong(const long long& value, const size_t& length = MAX_LONG_LONG_BIT_LENGTH);

        BitStringBuilder& AppendLongLong(const long long& value, const size_t& start, const size_t& end);

        String ToString(void) const;
    private:
        std::stringstream m_Buffer;

        BitStringBuilder& AppendBits(const long long& value, const size_t& start, const size_t& end, const size_t& maxLength);
    };

    std::vector<String> SplitString(const String& string, const String& delimiters);
    std::vector<String> SplitString(const String& string, const char delimiter);
    std::vector<String> Tokenize(const String& string);
    std::vector<String> GetLines(const String& string);

    const char* FindToken(const char* str, const String& token);
    const char* FindToken(const String& string, const String& token);
    int FindStringPosition(const String& string, const String& search, uint offset = 0);
    String StringRange(const String& string, uint start, uint length);
    String RemoveStringRange(const String& string, uint start, uint length);

    String GetBlock(const char* str, const char** outPosition = nullptr);
    String GetBlock(const String& string, uint offset = 0);

    String GetStatement(const char* str, const char** outPosition = nullptr);

    bool StringContains(const String& string, const String& chars);
    bool StartsWith(const String& string, const String& start);
    int NextInt(const String& string);

}
