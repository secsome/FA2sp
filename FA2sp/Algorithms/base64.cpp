#include "base64.h"

std::string base64::encode(std::string_view s)
{
	std::string ret;
	ret.reserve((s.length() + 2) / 3 * 4);

    size_t pos = 0;
    while (pos < s.length()) 
    {
        ret += encoder[(s[pos] & 0xFC) >> 2];
        if (pos + 1 < s.length()) 
        {
            ret += encoder[((s[pos] & 0x03) << 4) + ((s[pos + 1] & 0xF0) >> 4)];
            if (pos + 2 < s.length()) 
            {
                ret += encoder[((s[pos + 1] & 0x0F) << 2) + ((s[pos + 2] & 0xC0) >> 6)];
                ret += encoder[s[pos + 2] & 0x3F];
            }
            else 
            {
                ret += encoder[(s[pos + 1] & 0x0F) << 2];
                ret += '=';
            }
        }
        else 
        {
            ret += encoder[(s[pos + 0] & 0x03) << 4];
            ret += "==";
        }
        pos += 3;
    }

    ret.shrink_to_fit();
    return ret;
}

std::string base64::decode(std::string_view s)
{
    std::string ret;
    ret.reserve(s.length() / 4 * 3);

    size_t pos = 0;
    while (pos < s.length()) 
    {
        auto p1 = decoder[s[pos + 1]];
        ret += ((decoder[s[pos]]) << 2) + ((p1 & 0x30) >> 4);
        if ((pos + 2 < s.length()) && s[pos + 2] != '=' && s[pos + 2] != '.')
        {
            auto p2 = decoder[s[pos + 2]];
            ret += ((p1 & 0x0F) << 4) + ((p2 & 0x3C) >> 2);
            if ((pos + 3 < s.length()) && s[pos + 3] != '=' && s[pos + 3] != '.')
                ret += (((p2 & 0x03) << 6) + decoder[s[pos + 3]]);
        }
        pos += 4;
    }

    ret.shrink_to_fit();
    return ret;
}
