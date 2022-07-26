#include <iostream>
#include <string>
#include <cmath>
#include<time.h>
using namespace std;

//十进制转二进制
string dec_bin(int dec)
{
	string bin = "";
	while (dec >= 1)
	{
		bin = to_string(dec % 2) + bin;
		dec = dec / 2;
	}
	return bin;//返回对应的二进制
}
//十六进制转二进制
string hex_bin(string str)
{
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'F')
		{
			bin += table[(str[i] - 'A' + 10)];
		}
		else
		{
			bin += table[(str[i] - '0')];
		}
	}
	return bin;
}
//二进制转十六进制
string bin_hex(string str)
{
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0)
	{
		str = '0' + str;
	}
	for (int i = 0; i < str.size(); i += 4)
	{
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0');
		//cout << "temp" << temp;
		if (temp < 10)
		{
			hex += to_string(temp);
		}
		else if (temp == 10)
		{
			hex += 'A';
			//cout <<"hex"<< hex;
		}
		else if (temp == 11)
		{
			hex += 'B';
		}
		else if (temp == 12)
		{
			hex += 'C';
		}
		else if (temp == 13)
		{
			hex += 'D';
		}
		else if (temp == 14)
		{
			hex += 'E';
		}
		else if (temp == 15)
		{
			hex += 'F';
		}
		//cout << "hex" << hex;
	}
	return hex;
}
//十六进制转十进制
long long hex_dec(string str)
{
	long long dec = 0;;
	int len = str.size();
	for (int i = 0; i < len; i++)
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			dec += (str[i] - '0');
		}
		else if ('A' <= str[i] && str[i] <= 'F')
		{
			dec += (str[i] - 'A' + 10);
		}
		if (i < (len - 1))
		{
			dec *= 16;
		}
	}
	return dec;
}
//左移位
string LeftShift(string str, int num)
{
	string res = hex_bin(str);
	res = res.substr(num) + res.substr(0, num);
	return bin_hex(res);
}
//异或
string XOR(string str1, string str2)
{
	string res = "";
	str1 = hex_bin(str1);
	str2 = hex_bin(str2);
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == str2[i])
		{
			res += '0';
		}
		else
		{
			res += '1';
		}
	}
	return bin_hex(res);
}
//P0置换
string P0(string str)
{
	return XOR(XOR(str, LeftShift(str, 9)), LeftShift(str, 17));
}
//P1置换
string P1(string str)
{
	return XOR(XOR(str, LeftShift(str, 15)), LeftShift(str, 23));
}
//或操作
string OR(string str1, string str2)
{
	string res = "";
	str1 = hex_bin(str1);
	str2 = hex_bin(str2);
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == '0' && str2[i] == '0')
		{
			res += '0';
		}
		else
		{
			res += '1';
		}
	}
	return bin_hex(res);
}
//非操作
string NOT(string str)
{
	string res = "";
	str = hex_bin(str);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0')
		{
			res += "1";
		}
		else
		{
			res += "0";
		}
	}
	return bin_hex(res);
}
//与操作
string AND(string str1, string str2)
{
	string res = "";
	str1 = hex_bin(str1);
	str2 = hex_bin(str2);
	for (int i = 0; i < str1.size(); i++)
	{
		if (str1[i] == '1' && str2[i] == '1')
		{
			res += '1';
		}
		else
		{
			res += '0';
		}
	}
	return bin_hex(res);
}
//FF_j
string FF_j(string str1, string str2, string str3, int num)
{
	if (0 <= num && num <= 15)
	{
		return XOR(XOR(str1, str2), str3);
	}
	else
	{
		return OR(OR(AND(str1, str2), AND(str1, str3)), AND(str2, str3));
	}
}
//GG_j
string GG_j(string str1, string str2, string str3, int num)
{
	if (0 <= num && num <= 15)
	{
		return XOR(XOR(str1, str2), str3);
	}
	else
	{
		return OR(AND(str1, str2), AND(NOT(str1), str3));
	}
}
//常量T初始化
static string init_T(int j)
{
	string T;
	if (0 <= j && j <= 15)
	{
		T = "79CC4519";
	}
	else
	{
		T = "7A879D8A";
	}
	return T;
}
char ccxor(char c1, char c2)
{
	return c1 == c2 ? '0' : '1';
}
char ccand(char c1, char c2)
{
	return (c1 == '1' && c2 == '1') ? '1' : '0';
}
//模运算
string Mod(string str1, string str2)
{
	string res1 = hex_bin(str1);
	string res2 = hex_bin(str2);
	char temp = '0';
	string res = "";
	for (int i = res1.size() - 1; i >= 0; i--)
	{
		res = ccxor(ccxor(res1[i], res2[i]), temp) + res;
		if (ccand(res1[i], res2[i]) == '1')
		{
			temp = '1';
		}
		else
		{
			if (ccand(res1[i], res2[i]) == '1')
			{
				temp = ccxor('1', temp);
			}
			else
			{
				temp = '0';
			}
		}
	}
	return bin_hex(res);
}
//消息填充
string padding(string str)
{
	int n;//输入消息长度
	n = str.length();
	int r_n = n;//记录原始消息长度
	int k = 0;
	while ((n + 1 + k) % 512 != 448)
	{
		k += 1;
		str += '0';//填充0
	}
	string llen = dec_bin(r_n);
	int llength = llen.size();
	for (int i = 0; i <= (64 - llength); i++)
	{
		llen = '0' + llen;
	}
	str = str + llen;//填充完成
	return str;
}
//消息扩展
string extension(string str)
{
	//将消息分组划分为16个字W_i
	string WW = str;//存储扩展字
	for (int j = 16; j < 68; j++)
	{
		WW += XOR(XOR(P1(XOR(XOR(WW.substr((j - 16) * 8, 8), WW.substr((j - 9) * 8, 8)), LeftShift(WW.substr((j - 3) * 8, 8), 15))), LeftShift(WW.substr((j - 13) * 8, 8), 7)), WW.substr((j - 6) * 8, 8));
	}
	//64个W’
	for (int j = 0; j < 64; j++)
	{
		WW += XOR(WW.substr((j * 8), 8), WW.substr((j + 4) * 8, 8));
	}
	return WW;
}
//消息压缩
string compress(string str1, string str2)
{
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8),
		D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8),
		G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";
	for (int j = 0; j < 64; j++)
	{
		SS1 = LeftShift(Mod(Mod(LeftShift(A, 12), E), LeftShift(init_T(j), j % 32)), 7);
		SS2 = XOR(SS1, LeftShift(A, 12));
		TT1 = Mod(Mod(Mod(FF_j(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = Mod(Mod(Mod(GG_j(E, F, G, j), H), SS1), str1.substr((j * 8), 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
	}
	string res = (A + B + C + D + E + F + G + H);
	return res;
}
//迭代压缩函数
string iteration(string str, string V)
{
	int num = str.size() / 128;
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++)
	{
		B = str.substr((i * 128), 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = XOR(compressB, V);
	}
	return V;
}
string SM3(string paddingmessage, string V)
{
	string result = iteration(paddingmessage, V);
	return result;
}
int main()
{
	int num = pow(2, 8);
	clock_t start, end;
	start = clock();
	int M1 = rand() % (num + 1);//生成随机数作为初始消息
	int M2 = rand() % (num + 1);
	string V = "7380166F4914B2B9172442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string M1_padding = bin_hex(padding(dec_bin(M1)));
	string H1 = SM3(M1_padding, V);//把第一次初始消息的加密结果储存下来
	//H1作为新的IV
	string M2_padding = bin_hex(padding(dec_bin(M2)));
	string H2 = SM3(M2_padding, H1);
	string M3 = M1_padding + M2_padding;
	string H3 = SM3(M3, V);
	if (H2 == H3)
	{
		cout << "succeed";
	}
	end = clock();
	cout << (float)(end - start) * 1000 / CLOCKS_PER_SEC << "ms";
	return 0;
}