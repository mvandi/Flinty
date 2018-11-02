#include "String.h"
#include "fl/Common.h"

namespace fl {

	char* StringFormat::s_Buffer = new char[STRINGFORMAT_BUFFER_SIZE];

    const size_t BitStringBuilder::MAX_BYTE_BIT_LENGTH = sizeof(char) * CHAR_BIT;
    const size_t BitStringBuilder::MAX_SHORT_BIT_LENGTH = sizeof(short) * MAX_BYTE_BIT_LENGTH;
    const size_t BitStringBuilder::MAX_INT_BIT_LENGTH = sizeof(int) * MAX_BYTE_BIT_LENGTH;
    const size_t BitStringBuilder::MAX_LONG_BIT_LENGTH = sizeof(long) * MAX_BYTE_BIT_LENGTH;
    const size_t BitStringBuilder::MAX_LONG_LONG_BIT_LENGTH = sizeof(long long) * MAX_BYTE_BIT_LENGTH;

    BitStringBuilder& BitStringBuilder::AppendBit(const bool& value)
    {
        m_Buffer << value;
        return *this;
    }

    BitStringBuilder& BitStringBuilder::AppendByte(const char& value, const size_t& length)
    {
        return AppendByte(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendByte(const char& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_BYTE_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendShort(const short& value, const size_t& length)
    {
        return AppendShort(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendShort(const short& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_SHORT_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendInt(const int& value, const size_t& length)
    {
        return AppendInt(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendInt(const int& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_INT_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendLong(const long& value, const size_t& length)
    {
        return AppendLong(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendLong(const long& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_LONG_BIT_LENGTH);
    }

    BitStringBuilder& BitStringBuilder::AppendLongLong(const long long& value, const size_t& length)
    {
        return AppendLongLong(value, 0, length);
    }

    BitStringBuilder& BitStringBuilder::AppendLongLong(const long long& value, const size_t& start, const size_t& end)
    {
        return AppendBits(value, start, end, MAX_LONG_LONG_BIT_LENGTH);
    }

    String BitStringBuilder::ToString(void) const
    {
        return m_Buffer.str();
    }

    BitStringBuilder& BitStringBuilder::AppendBits(const long long& value, const size_t& start, const size_t& end, const size_t& maxLength)
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
