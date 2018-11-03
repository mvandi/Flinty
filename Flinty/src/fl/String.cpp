#include "String.h"
#include "fl/Common.h"

namespace fl {

    char* StringFormat::s_Buffer = new char[STRINGFORMAT_BUFFER_SIZE];

    const size_t BitStringBuilder::MAX_INT8_BIT_LENGTH  = sizeof(int8) * CHAR_BIT;
    const size_t BitStringBuilder::MAX_INT16_BIT_LENGTH = sizeof(int16) * MAX_INT8_BIT_LENGTH;
    const size_t BitStringBuilder::MAX_INT_BIT_LENGTH   = sizeof(int) * MAX_INT8_BIT_LENGTH;
    const size_t BitStringBuilder::MAX_INT32_BIT_LENGTH = sizeof(int32) * MAX_INT8_BIT_LENGTH;
    const size_t BitStringBuilder::MAX_INT64_BIT_LENGTH = sizeof(int64) * MAX_INT8_BIT_LENGTH;

    BitStringBuilder::BitStringBuilder(void)
    {
    }

    BitStringBuilder::~BitStringBuilder(void)
    {
        m_Buffer.str("");
        m_Buffer.clear();
    }

    BitStringBuilder& BitStringBuilder::AppendBit(const bool& value)
    {
        m_Buffer << value;
        return *this;
    }

    BitStringBuilder& BitStringBuilder::AppendBits(const BitStringBuilder& other)
    {
        m_Buffer << other.ToString();
        return *this;
    }

    BitStringBuilder& BitStringBuilder::AppendInt8(const int8& value, const size_t& length)
    {
        return AppendInt8(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendInt8(const int8& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_INT8_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendInt16(const int16& value, const size_t& length)
    {
        return AppendInt16(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendInt16(const int16& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_INT16_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendInt(const int& value, const size_t& length)
    {
        return AppendInt(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendInt(const int& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_INT_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendInt32(const int32& value, const size_t& length)
    {
        return AppendInt32(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendInt32(const int32& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_INT32_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendInt64(const int64& value, const size_t& length)
    {
        return AppendInt64(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendInt64(const int64& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_INT64_BIT_LENGTH);
    }

    String BitStringBuilder::ToString(void) const
    {
        return m_Buffer.str();
    }

    BitStringBuilder& BitStringBuilder::AppendBits(const int64& value, const size_t& start, const size_t& end, const size_t& maxLength)
    {
        FL_ASSERT(start < end);
        FL_ASSERT(start >= 0);
        FL_ASSERT(end <= maxLength);

        for (size_t i = end; i-- > start;)
            AppendBit(CHECK(value, i));

        return *this;
    }

    std::vector<String> SplitString(const String& string, const String& delimiters)
    {
        size_t start = 0;
        size_t end = string.find_first_of(delimiters);

        std::vector<String> result;

        while (end <= String::npos)
        {
            String token = string.substr(start, end - start);
            if (!token.empty())
                result.push_back(token);

            if (end == String::npos)
                break;

            start = end + 1;
            end = string.find_first_of(delimiters, start);
        }

        return result;
    }

    std::vector<String> SplitString(const String& string, const char delimiter)
    {
        return SplitString(string, String(1, delimiter));
    }

    std::vector<String> Tokenize(const String& string)
    {
        return SplitString(string, " \t\n");
    }

    std::vector<String> GetLines(const String& string)
    {
        return SplitString(string, "\n");
    }

    const char* FindToken(const char* str, const String& token)
    {
        const char* t = str;
        while (t = strstr(t, token.c_str()))
        {
            bool left = str == t || isspace(t[-1]);
            bool right = !t[token.size()] || isspace(t[token.size()]);
            if (left && right)
                return t;

            t += token.size();
        }
        return nullptr;
    }

    const char* FindToken(const String& string, const String& token)
    {
        return FindToken(string.c_str(), token);
    }

    int FindStringPosition(const String& string, const String& search, uint offset)
    {
        const char* str = string.c_str() + offset;
        const char* found = strstr(str, search.c_str());
        if (found == nullptr)
            return -1;
        return (int)(found - str) + offset;
    }

    String StringRange(const String& string, uint start, uint length)
    {
        return string.substr(start, length);
    }

    String RemoveStringRange(const String& string, uint start, uint length)
    {
        String result = string;
        return result.erase(start, length);
    }

    String GetBlock(const char* str, const char** outPosition)
    {
        const char* end = strstr(str, "}");
        if (!end)
            return String(str);

        if (outPosition)
            *outPosition = end;
        uint length = end - str + 1;
        return String(str, length);
    }

    String GetBlock(const String& string, uint offset)
    {
        const char* str = string.c_str() + offset;
        return GetBlock(str);
    }

    String GetStatement(const char* str, const char** outPosition)
    {
        const char* end = strstr(str, ";");
        if (!end)
            return String(str);

        if (outPosition)
            *outPosition = end;
        uint length = end - str + 1;
        return String(str, length);
    }

    bool StringContains(const String& string, const String& chars)
    {
        return string.find(chars) != String::npos;
    }

    bool StartsWith(const String& string, const String& start)
    {
        return string.find(start) == 0;
    }

    int NextInt(const String& string)
    {
        const char* str = string.c_str();
        for (uint i = 0; i < string.size(); i++)
        {
            if (isdigit(string[i]))
                return atoi(&string[i]);
        }
        return -1;
    }

}
