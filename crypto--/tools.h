#ifndef _TOOLS_H_
#define _TOOLS_H_ 
#include "aes.h"
/**
 *  将一个char字符数组转化为二进制
 *  存到一个 byte 数组中
 */
bool charToByte(byte out[16], std::string& s)
{
	if (s[15] == NULL)return false;
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 8; ++j)
			out[i][j] = ((s[i] >> j) & 1);
	return true;
}

/**
 *  将连续的128位分成16组，存到一个 byte 数组中
 */
void divideToByte(byte out[16], bitset<128>& data)
{
	bitset<128> temp;
	for (int i = 0; i < 16; ++i)
	{
		temp = (data << 8 * i) >> 120;
		out[i] = temp.to_ulong();
	}
}


/**
 *  将16个 byte 合并成连续的128位
 */
bitset<128> mergeByte(byte in[16])
{
	bitset<128> res;
	res.reset();  // 置0
	bitset<128> temp;
	for (int i = 0; i < 16; ++i)
	{
		temp = in[i].to_ulong();
		temp <<= 8 * (15 - i);
		res |= temp;
	}
	return res;
}
int myrng(unsigned char* dst, int len, void* dat)
{
	int x;
	for (x = 0; x < len; x++) dst[x] = rand() & 0xFF;
	return len;
}

//生成指定字长的随机字符串
string GetRandList(int len)
{
	unsigned int number;
	int err;
	char strRandomList[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '@', '#', '$', '%', '&', '*', '_' };
	string pwd = "";
	for (int i = 0; i < len; i++)
	{
		err = rand_s(&number);
		if (err != 0) {
			printf_s("The rand_s function failed!\n");
		}
		pwd += strRandomList[number % 70];//随机取strRandomList 的项值
	}
	return pwd;
}

void ex_Eulid(mp_int* a, mp_int* b, mp_int* a1, mp_int* b1, mp_int* temp3) {
	if (mp_cmp_d(b, 0) == 0) {
		mp_set(a1, 1);
		mp_set(b1, 0);
		mp_copy(temp3, a);
	}
	else {
		mp_int temp1;
		mp_int temp2;
		mp_init(&temp1);
		mp_init(&temp2);
		mp_mod(a, b, &temp1);
		ex_Eulid(b, &temp1, a1, b1, temp3);
		mp_copy(a1, &temp1);
		mp_copy(b1, a1);
		mp_div(a, b, temp3, &temp2);
		mp_mul(temp3, b1, temp3);
		mp_sub(&temp1, temp3, b1);
	}
}

#endif
