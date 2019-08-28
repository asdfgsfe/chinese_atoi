#include <string>
#include <iostream>
#include <vector>
using namespace std;

void Dump(const vector<string>& words)
{
  for (auto& word : words)
  {
    std::cout << word << " ";
  }
  std::cout << std::endl;
}

 
int main(void)
{ 
  string s = "你好CSDN，我的";
  string test("我");
  std::cout << test.size() << std::endl;
  string t;
  vector<string> words;
  for(int i=0; i<s.length(); i++)
  {
    if(s[i]<255 && s[i]>0)//扩充的ASCII字符范围为0-255,如是,处理一个字节
    {
      t.append(s.substr(i,1));
      t.append("/");
      words.emplace_back(s.substr(i,1));
    }
    else//<0,>255的是汉字,处理两个字节
    {
      int j = i;
      while (s[j] >= 255 || s[j] <= 0)
      {
        ++j;
      }
      words.emplace_back(s.substr(i,3));
      t.append(s.substr(i,3));
      t.append("/");
      //++i;
      i += 2;
    }
  }
  cout << t << endl;//输出符合要求
  Dump(words);
  return 0;
}
