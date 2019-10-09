#include <iostream>                                                                                              
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

const static int g_chinese = string("我").size();

static unordered_map<string, int> g_uints = {
	{ "亿", 100000000 },{ "万", 10000 },{ "千", 1000 },{ "百", 100 },{ "十", 10 },{ "个", 1 } };

static unordered_map<string, int> g_numbers = {
	{ "九", 9 },{ "八", 8 },{ "七", 7 },{ "六", 6 },{ "五", 5 },{ "四", 4 },{ "三", 3 },{ "二", 2 },{ "一", 1 },{ "零", 0 } };

bool g_invaildInput = false;

//思路非常简单就是从右至左分析中文的数字,遇到'位'计记录下来,
//非'位'就乘以位并加入到结果result中.firstUnit单表第一级位,second代表二级位,
//例如:三十八万 十是secondUnit,万是firsUnit
long long CvrProcess(const string& cnum, int end, bool minus)
{
	long long firstUnit = 1;                    //一级单位
	long long secondUnit = 1;                   //二级单位
	long long num = 0;
	int flag = minus ? -1 : 1;
	int i = cnum.size() - 1;
	while (i - g_chinese + 1 >= end)
	{
		string cur = cnum.substr(i - g_chinese + 1, g_chinese);
		if (g_uints.count(cur) && g_numbers.count(cur))
		{
			return 0;
		}
		//std::cout << "i=" << i << " cur=" << cur << std::endl;
		long tmpUnit = g_uints.count(cur) ? g_uints[cur] : 1;
		if (tmpUnit > firstUnit)
		{
			firstUnit = tmpUnit;
			secondUnit = 1;
		}
		else if (tmpUnit > secondUnit)
		{
			secondUnit = tmpUnit;
		}
		num += flag * firstUnit * secondUnit * (g_numbers.count(cur) ? g_numbers[cur] : 0);
		if ((minus && num < (signed int) 0x80000000) || (!minus && num > (signed int)0x7fffffff))
		{
			return 0;
		}
		i -= g_chinese;
		//std::cout << "firstUint=" << firstUnit << " secondUint=" << secondUnit
		//	<< " tmp=" << tmpUnit << " result=" << result 
		//	<< " cur=" << (firstUnit * secondUnit * (g_numbers.count(cur) ? g_numbers[cur] : 0)) << std::endl;
	}
	g_invaildInput = false;
	return num;
}

//多于两个单位连一起的情况 特殊字符等
int Atoi(const string& str)
{
	g_invaildInput = true;
	if (str.empty())
	{
		return 0;
	}
	bool minus = false;
	int i = 0;
	if (str.substr(i, g_chinese) == "负")
	{
		i += g_chinese;
		minus = true;
	}
	else if (str.substr(i, g_chinese) == "正")
	{
		i += g_chinese;
	}
	if (i != str.size())
	{
		return (int)CvrProcess(str, i, minus);
	}
	return 0;
}

int main(void)
{
	string num("负二十二");
	std::cout << num << " " << Atoi(num) << std::endl;
	//string num("二十千万"); //二十千万其实就是2亿 这里表达有错误
	//std::cout << num << " " << Atoi(num) << std::endl;
	//num = "四千三百五十三";
	//std::cout << num << " " << Atoi(num) << std::endl;
	//num = "二亿三千四百二十五万";
	//std::cout << num << " " << Atoi(num) << std::endl;

	return 0;
}