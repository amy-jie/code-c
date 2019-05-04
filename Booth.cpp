#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
int N = 0;  //记录移位的次数
int Yn = 0;//附加位
void Comp(string  value, char store[], int length);//求补码
void  RMove(char *partproduct, char*X2, int partproduct_length, int X2_length);//右移操作,乘数移丢的位存放在Yn
void Minus(char X1[], char minus[], int X1_length);//求【-X】的补数
void Plus(char partproduct[], char X1[], char X2[], char minus[], int X1_length, int X2_length);//加法
void Multiply(char X1[], char X2[], char product[], char minus[], int X1_length, int X2_length);
void Comp2(char product[], char finalproduct[], int product_length);//将结果转换成真值
void main()
{
	string  muled, muler;
	getline(cin, muled, ',');
	getline(cin, muler, '\n');
	int store1_length, store2_length, minus_length, product_length,
		X1_length, X2_length, finalproduct_length;
	//算出所用数组的长度,并开辟出数组空间
	int i;
	for (i = 0; muled[i] != NULL; i++);
	store1_length = i;
	int j;
	for (j = 0; muler[j] != NULL; j++);
	store2_length = j;
	char *store1 = new char[store1_length];//转换时暂存补码
	char *store2 = new char[store2_length];
	minus_length = store1_length + 1;
	char *minus = new char[minus_length];//[-x]的补数
	product_length = store1_length + store2_length - 3;
	finalproduct_length = product_length + 1;
	char *product = new char[product_length];//积,补码
	char *finalproduct = new char[finalproduct_length];//积，真值
	X1_length = store1_length + 1;
	X2_length = store2_length - 1;
	char *X1 = new char[X1_length];
	char *X2 = new char[X2_length];//运算时需要的数形式
	//int l1 = X1_length, l2 = X2_length;
	Comp(muled, store1, store1_length);
	if (store1[0] == '0') X1[0] = '0';//转换成运算所需的形式
	else X1[0] = '1';
	for (int i = 1, j = 0; j <= store1_length - 1; i++, j++)
		X1[i] = store1[j];
	Comp(muler, store2, store2_length);
	if (store2[0] == '0')  X2[0] = '0';//转换成运算所需的形式
	else  X2[0] = '1';
	for (int i = 1, j = 2; j <= store2_length - 1; i++, j++)
		X2[i] = store2[j];
	Minus(X1, minus, X1_length);
	Multiply(X1, X2, product, minus, X1_length, X2_length);
	Comp2(product, finalproduct, product_length);
	cout << finalproduct;
	delete[]store1; delete[]store2,
		delete[]finalproduct; delete[]minus;
	delete[]product;
	delete[]X1; delete[]X2;
}
void Comp(string  value, char *store, int length)
{
	int i, j;
	if (value[0] == '+')	{
		store[0] = '0';
		store[1] = '.';
		for (i = 2, j = 3; i < length; i++, j++)
			store[i] = value[j];
	else
	{
		store[0] = '1';
		store[1] = '.';
		for (i = 3, j = 2; i < length; i++, j++)//按位取反
		{
			if (value[i] == '0')   store[j] = '1';
			else store[j] = '0';
		}
		store[length - 1] = '\0';
		for (i = length - 2; i >= 2; i--)//末位+1
		{
			if (store[i] == '0')
			{
				store[i] = '1';
				break;
			}
			else
				store[i] = '0';
		}
		if (i < 2) store[0] = '0';
	}
	}
	//将结果转换成真值
	void Comp2(char product[], char finalproduct[], int product_length)
	{
		int q, j;
		if (product[0] == '1')
		{
			for (q = product_length - 2; q > 1; q--)//
			{
				if (product[q] == '1')
				{
					product[q] = '0'; break;
				}
				else
					product[q] = '1';
			}
			finalproduct[0] = '-';
			finalproduct[1] = '0';
			finalproduct[2] = '.';
			for (q = 3, j = 2; j < product_length; q++, j++)
			{
				if (product[j] == '1') finalproduct[q] = '0';
				else if (product[j] == '0')  finalproduct[q] = '1';
				else finalproduct[q] = product[j];
			}
		}
		else
		{
			finalproduct[0] = '+';
			finalproduct[1] = '0';
			finalproduct[2] = '.';
			for (int i = 3, j = 2; j < product_length; i++, j++)
				finalproduct[i] = product[j];
		}
	}
	void Minus(char X1[], char minus[], int X1_length)
	{
		for (int i = 0; i < X1_length; i++)
		{
			if (X1[i] == '0') minus[i] = '1';
			else if (X1[i] == '1')   minus[i] = '0';
			else minus[i] = X1[i];
		}
		for (int i = X1_length - 2; i >= 0; i--)
		{
			if (minus[i] == '0')
			{
				minus[i] = '1';
				break;
			}
			else
				minus[i] = '0';
		}
	}
	void Plus(char partproduct[], char X1[], char X2[], char minus[], int X1_length, int X2_length)
	{
		int carry = 0;//表示进位
		int i = X1_length - 2;
		int a, b, c;
		if ((Yn - (int)X2[X2_length - 2] + '0') == 1)
		{
			while (partproduct[i] != '.') {
				a = partproduct[i] - '0';
				b = X1[i] - '0';
				c = a^b;
				c = c^carry;
				partproduct[i] = c + '0';
				if (a + b + carry > 1) carry = 1;
				else  carry = 0;
				i--;
			}
			a = partproduct[1] - '0';
			b = X1[1] - '0';
			c = a^b;
			c = c^carry;
			partproduct[1] = c + '0';
			if (a + b + carry > 1) carry = 1;
			else  carry = 0;
			a = partproduct[0] - '0';
			b = X1[0] - '0';
			c = a^b;
			c = c^carry;
			partproduct[0] = c + '0';
			if (a + b + carry > 1) carry = 1;
			else  carry = 0;
		}
		if ((Yn - (int)X2[X2_length - 2] + '0') == -1)
		{
			while (partproduct[i] != '.') {
				a = partproduct[i] - '0';
				b = minus[i] - '0';
				c = a^b;
				c = c^carry;
				partproduct[i] = c + '0';
				if (a + b + carry > 1) carry = 1;
				else  carry = 0;
				i--;
			}
			a = partproduct[1] - '0';
			b = minus[1] - '0';
			c = a^b;
			c = c^carry;
			partproduct[1] = c + '0';
			if (a + b + carry > 1) carry = 1;
			else  carry = 0;
			a = partproduct[0] - '0';
			b = minus[0] - '0';
			c = a^b;
			c = c^carry;
			partproduct[0] = c + '0';
			if (a + b + carry > 1) carry = 1;
			else  carry = 0;
		}
		for (int q = 1; q > -1; q--)
		{
			a = partproduct[q] - '0';
			b = minus[q] - '0';
			c = a^b;
			c = c^carry;
			partproduct[q] = c + '0';
			if (a + b + carry > 1) carry = 1;
			else  carry = 0;
			q--;
		}
	}

	void  RMove(char *partproduct, char*X2, int partproduct_length, int X2_length) //右移
	{
		Yn = (int)X2[X2_length - 2] - '0';   //附加位，用于判断位移及加减
		for (int i = X2_length - 2; i > 0; i--)
			X2[i] = X2[i - 1];
		X2[0] = partproduct[partproduct_length - 2];//部分积的最后一位移到乘数寄存器中保存
		for (int j = partproduct_length - 2; j > 3; j--)
			partproduct[j] = partproduct[j - 1];
		if (partproduct[0] == '1')
			partproduct[3] = '1';
		else
			partproduct[3] = '0';
		N++;
	}
	void Multiply(char X1[], char X2[], char product[], char minus[], int X1_length, int X2_length)
	{
		char *partproduct = new char[X1_length];
		partproduct[0] = '0';
		partproduct[1] = '0';
		partproduct[2] = '.';
		for (int i = 3; i <= X1_length - 2; i++)
			partproduct[i] = '0';
		partproduct[X1_length - 1] = '\0';
		for (; N < X2_length - 2;)
		{
			switch (Yn - (int)X2[X2_length - 2] + '0')
			{
			case 0: RMove(partproduct, X2, X1_length, X2_length); break;
			case 1: Plus(partproduct, X1, X2, minus, X1_length, X2_length); RMove(partproduct, X2, X1_length, X2_length);  break;
			case -1: Plus(partproduct, X1, X2, minus, X1_length, X2_length); RMove(partproduct, X2, X1_length, X2_length);  break;
			}
		}
		Plus(partproduct, X1, X2, minus, X1_length, X2_length);
		for (int i = 0, j = 1; j < X1_length; i++, j++)
			product[i] = partproduct[j];
		for (int i = X1_length - 2, j = 0; j < X2_length - 2; i++, j++)
			product[i] = X2[j];
		product[X1_length + X2_length - 3 - 1] = '\0';
		delete[]partproduct;
	}


}