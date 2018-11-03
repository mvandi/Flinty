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
        static const size_t MAX_INT8_BIT_LENGTH;
        static const size_t MAX_INT16_BIT_LENGTH;
        static const size_t MAX_INT_BIT_LENGTH;
        static const size_t MAX_INT32_BIT_LENGTH;
        static const size_t MAX_INT64_BIT_LENGTH;
    public:
        BitStringBuilder(void);

        virtual ~BitStringBuilder(void);

        BitStringBuilder(const BitStringBuilder& other) = delete;
        BitStringBuilder& operator=(const BitStringBuilder& other) = delete;

        BitStringBuilder& AppendBit(const bool& value);

        BitStringBuilder& AppendBits(const BitStringBuilder& other);

        BitStringBuilder& AppendInt8(const int8& value, const size_t& length = MAX_INT8_BIT_LENGTH);

        BitStringBuilder& AppendInt8(const int8& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendInt16(const int16& value, const size_t& length = MAX_INT16_BIT_LENGTH);

        BitStringBuilder& AppendInt16(const int16& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendInt(const int& value, const size_t& length = MAX_INT_BIT_LENGTH);

        BitStringBuilder& AppendInt(const int& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendInt32(const int32& value, const size_t& length = MAX_INT32_BIT_LENGTH);

        BitStringBuilder& AppendInt32(const int32& value, const size_t& start, const size_t& end);

        BitStringBuilder& AppendInt64(const int64& value, const size_t& length = MAX_INT64_BIT_LENGTH);

        BitStringBuilder& AppendInt64(const int64& value, const size_t& start, const size_t& end);

        String ToString(void) const;
    private:
        std::stringstream m_Buffer;

        BitStringBuilder& AppendBits(const int64& value, const size_t& start, const size_t& end, const size_t& maxLength);
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
