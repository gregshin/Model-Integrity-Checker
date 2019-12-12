#include<sstream> 
#include<iostream>

using namespace std; 

int main()
{
 stringstream ss;
 int num = 12345;
ss << num;
string strNum; ss >> strNum;
return 0; }