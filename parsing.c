[10:48 PM, 7/15/2021] Ali Bassiony : //============================================================================
// Name        : parsing.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include<string.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include<stack>
using namespace std;
class node{
public:
	string data;
	string tagvalue;
	vector<node*> children;
	node* parent;
	string attributes[30];
	int degree;
	int no_children;
	int no_attributes;

	node()
	{
		data="NULL";
		tagvalue="NULL";
		parent=NULL;
		degree=0;
		no_attributes=0;
		no_children=0;
        for(int i=0;i<30;i++)
…
[10:48 PM, 7/15/2021] Ali Bassiony : #include <iostream>
#include <stack>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>

using namespace std;
int findchar(string a,char z)
	{
		for(unsigned long long i=0;i<a.size();i++)
		{
			if (z==a[i])
				return i;
		}
		return -1;
	}
void CheckError(vector <string> line , vector <int> LineOfError, vector <string> FixError)
		{
			//string[] FixError = new string[line.size()];
			for(unsigned long long i=0;i<line.size(); i++)
            {
				FixError[i] = line[i];
            }
			string str;
			int flag=0;
			string tagvalue;
			stack<string> s ;
			unsigned long long index = 0;
			string sub = line[0];
			int d;
			while (index < line.size())
			{
				int iter = findchar(sub,'<');
				if (iter == -1 && sub.length() != 0) // line is only words
				{
					flag = 1;

					index++; // go to next line
					if (index < line.size()) // check that file isn't finished
						sub = line[index];
				}
				else if (iter != -1)
				{
					if (sub[iter + 1] == '/') // closing tag  dhgdhdgteh </tag>
					{
						int close = findchar(sub,'>');
						int dash = findchar(sub,'/');
						tagvalue = sub.substr(dash + 1, close - dash - 1);
						if (tagvalue == s.top()) // no error
						{
							s.pop();
						}
						else
						{
							LineOfError[index] = 1;
							while (s.top() != tagvalue)
							{
								FixError[index - 1] += "</" + s.top() + ">";
								s.pop();
							}
							s.pop();
						}
						sub = sub.substr(findchar(sub,'>') + 1); // cut after '>'
						if (sub.length() == 0) // there's nothing after closing tag
						{
							index++; // go to next line
							if (index < line.size())
								sub = line[index];
						}
						else // may be there are spaces only after closing tag => we don't need them
						{
							d = 0; // flag
							for (unsigned long long i = 0; i < sub.length(); i++)
							{
								if (sub[i] != ' ')
								{
									d = 1;
									break;
								}
							}
							if (d == 0) // all characters are spaces
							{
								index++; // go to next line
								if (index<line.size())
									sub = line[index];
							}
						}
					}
					else if (sub[iter + 1] != '/') // opening tag
					{
						if (flag != 1)
						{
							str = sub.substr(iter); // without spaces
							int close = findchar(str,'>');
							int space =findchar(str,' ');
							int dash = findchar(str,'/');
							int open = findchar(str,'<');
							if (dash == -1 || dash > close) // not opening and closing at the same time
							{
								if (space == -1 || space > close || (space < close && space < open)) // there is no value <tag>
									tagvalue = str.substr(1, close- 1); // set child name
								else // there is value <tag ..>
								{
									tagvalue = str.substr(1, space-1); // set child name
								}
								s.push(tagvalue);
							}
							sub = str.substr(close + 1);
							if (sub.length() == 0) // there's nothing after tag
							{
								index++; // go to next line
								if (index < line.size())
									sub = line[index];
							}
							else // may be there are spaces only after tag => we don't need them
							{
								d = 0; // flag
								for (unsigned long long i = 0; i < sub.length(); i++)
								{
									if (sub[i] != ' ')
									{
										d = 1;
										break;
									}
								}
								if (d == 0) // all characters are spaces
								{
									index++; // go to next line
									if (index <line.size())
										sub = line[index];
								}
							}
						}
						else if (flag == 1)
						{
							LineOfError[index - 1] = 1;
							FixError[index - 1] += "</" + s.top() + ">";
							s.pop();
							flag = 0;
						}

					}
				}
			}
			while (s.empty() != 0)
			{
				LineOfError[index - 1] = 1;
				FixError[index - 1] += "</" + s.top() + ">";
				s.pop();
			}
			for(unsigned long long i=0;i<line.size(); i++)
			{
				cout<< LineOfError[i] <<endl;
				cout<< FixError[i]<<endl;
			}
		}
int main()
{
	//list tree;
	//int num;
	//int z;
	string delimiter="<";
	string delimiter2="=";
	ifstream in("data-sample.xml");
	string str="juuy";
	//ignore the <?xml line
	vector<string> c;
	vector<string> FixError;
	vector<int> LineOfError;


    while ( in.good() )
    {
    	//int i=0;
    	string s;
      getline (in,str);
      while(str[0]==' ')
      {
    	  str.erase(0,1);
      }
      if(findchar(str,'<')!=-1 &&str[findchar(str,'<')+1]=='!' )
      {
    	  continue;
      }
      if(findchar(str,'<')!=-1 &&str[findchar(str,'<')+1]=='?' )
      {
    	  continue;
      }
      if(findchar(str,'<')!=0 &&c.size()==0 )
            {
          	  continue;
            }
  c.push_back(str);
    }
     CheckError( c ,  LineOfError,  FixError);

}
