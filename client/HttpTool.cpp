#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <regex>
using namespace std;

string get_cookie(const string resp)
{
    string substr = "Set-Cookie: ";
    string cookie;
    size_t pos;
    if ((pos = resp.find(substr)) != string::npos)
    {
        pos += substr.length();
        while (resp[pos] != ';')
        {
            // cout << resp[pos] << endl;
            cookie.push_back(resp[pos]);
            ++pos;
        }
    }
    return cookie;
}
string get_alert(const string resp)
{
    string substr = "alert";
    string res;
    size_t pos;
    if ((pos = resp.find(substr)) != string::npos)
    {
        pos += substr.length() + 2;                      // 2个字符，即 ( 和 '
        while (resp[pos] != '\'' && pos < resp.length()) // alert('xxx')
        {
            if (resp[pos] == '\\' && pos + 1 < resp.length() && resp[pos + 1] == 'n')
            {
                res.push_back('\n'); //尾零
                pos += 2;
            }
            else
            {
                res.push_back(resp[pos]);
                ++pos;
            }
        }
    }
    return res;
}
string FileToStr(string filepath)
{
    fstream f(filepath, ios::in | ios::binary);
    if (f.good())
    {
        f.unsetf(ios::skipws); // 关闭inputFile的忽略空格标志,可以文件中的保留空格
        istream_iterator<char> iter(f);
        string s(iter, istream_iterator<char>());
        return s;
    }
    else
    {
        cout << "Can't open file!" << endl;
        return "";
    }
}
string MapToString(map<string, string> data)
{
    string res = "";
    map<string, string>::iterator iter;
    for (iter = data.begin(); iter != data.end(); ++iter)
    {
        res += iter->first + "=" + iter->second + "&";
    }
    res.erase(res.end() - 1);
    return res;
}
string UrlEncode(string s)
{
    char need[6];
    string temp;
    string changelist = "+/%#&?= ";
    string::iterator it;
    for (size_t i = 0; i < s.length(); i++)
    {
        for (size_t j = 0; j < changelist.length(); j++)
        {
            if (s[i] == changelist[j])
            {
                sprintf(need, "%%%X", int(s[i]));
                temp = need;
                it = s.begin() + i;
                s.erase(it);
                s.insert(s.begin() + i, temp.begin(), temp.end());
                i += temp.length() - 1;
            }
        }
    }
    return s;
}
bool search_to_submit(string s, string html)
{
    bool found = false;
    string pattern("<tr>.*?<input type=\"file\".*?></tr>"), subpattern("<td>(.*?)</td>");
    regex r(pattern), sub(subpattern);
    string temp;
    for (sregex_iterator it(html.begin(), html.end(), r), end_it; it != end_it && (!found); ++it)
    {
        int num = 0;
        for (sregex_iterator sub_it(temp.begin(), temp.end(), sub), e_it; sub_it != e_it; ++sub_it)
        {
            num++;
            if (num == 2)
            {
                if (sub_it->str(1) == s)
                {
                    found = true;
                    break;
                }
            }
        }
    }
    return found;
}