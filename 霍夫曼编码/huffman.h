#pragma once
#include<iostream>
#include<string>
using namespace std;

//结点模板
struct HuffmanNode
{
	int weight;
	char ch;
	string code;
	//使用数组来构造霍夫曼树，左右孩子、父节点只用储存其在数组中的下标
	int lchild, rchild, parent;
};

class HuffmanCode {
public:
	HuffmanCode(string str);
	~HuffmanCode();
	void Encode();
	string CodedText();
	void Decode(string str);
	void GetMin(int &first,int &second,int parent);
	void Mix(int first, int second, int parent);
	double Compare();
private:
	HuffmanNode*HuffmanTree;
	int leafSize;
	string str;
};

HuffmanCode::HuffmanCode(string str) {
	this->str = str;
	int arr[256] = { 0 };
	int length = str.size();
	HuffmanTree = new HuffmanNode[256];
	//初始化霍夫曼树
	for (int i = 0; i < 2 * length - 1; i++) {
		HuffmanTree[i].lchild = HuffmanTree[i].rchild = HuffmanTree[i].parent = -1;
		HuffmanTree[i].code = "";
	}
	//arr数组按asc码在对应位置储存字符出现次数
	for (int i = 0; i < length; i++) {
		arr[str[i]]++;
	}
	leafSize = 0;
	for (int i = 0; i < 256; i++) {
		if (arr[i] != 0) {
			HuffmanTree[leafSize].ch = (char)i;
			HuffmanTree[leafSize].weight = arr[i];
			leafSize++;
		}
	}
	for (int i = leafSize; i < 2 * leafSize - 1; i++) {
		int first, second;
		GetMin(first, second, i);//从当前所有结点中找出两个权值最小的
		Mix(first, second, i);//将两个结点合并成一个新的结点
	}
}

HuffmanCode::~HuffmanCode() {
	delete []HuffmanTree;
}

void HuffmanCode::GetMin(int &first, int &second, int parent) {
	int weight = 0;
	for (int i = 0; i < parent; i++) {
		if (HuffmanTree[i].parent != -1) {
			continue;
		}if (weight == 0) {
			weight = HuffmanTree[i].weight;
			first = i;
		}
		else if (weight > HuffmanTree[i].weight) {
			weight = HuffmanTree[i].weight;
			first = i;
		}
	}
	weight = 0;
	for (int i = 0; i < parent; i++) {
		if (HuffmanTree[i].parent != -1 || i == first) {
			continue;
		}
		if (weight == 0) {
			weight = HuffmanTree[i].weight;
			second = i;
		}
		else if (weight > HuffmanTree[i].weight) {
			weight = HuffmanTree[i].weight;
			second = i;
		}
	}
}

void HuffmanCode::Mix(int first, int second, int parent) {
	HuffmanTree[parent].lchild = first;
	HuffmanTree[parent].rchild = second;
	HuffmanTree[parent].weight = HuffmanTree[first].weight + HuffmanTree[second].weight;
	HuffmanTree[first].parent = parent;
	HuffmanTree[second].parent = parent;
}

void HuffmanCode::Encode() {
	string code = "";
	for (int i = 0; i < leafSize; i++) {
		int j = i;
		int parent;
		code = "";
		while (HuffmanTree[j].parent != -1) {
			parent = HuffmanTree[j].parent;
			if (j == HuffmanTree[parent].lchild) {
				code += "0";
			}
			else {
				code += "1";
			}
			j = parent;
		}
		for (int indexOfcode = code.size() - 1; indexOfcode >= 0; indexOfcode--) {
			HuffmanTree[i].code += code[indexOfcode];
		}
		cout << "字符：" << HuffmanTree[i].ch << "的编码为：" << HuffmanTree[i].code << endl;
	}
}

string HuffmanCode::CodedText() {
	string codedText = "";
	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < leafSize; j++) {
			if (str[i] == HuffmanTree[j].ch) {
				codedText += HuffmanTree[j].code;
			}
		}
	}
	return codedText;
}

void HuffmanCode::Decode(string str) {
	string decodedText = "";
	string temp = "";
	for (int i = 0; i < str.size(); i++) {
		temp += str[i];
		int j;
		for (j = 0; j < leafSize; j++) {
			if (temp == HuffmanTree[j].code) {
				decodedText += HuffmanTree[j].ch;
				temp = "";
			}
			if (i == str.size() - 1 && j == leafSize) {
			cout << "输入编码有误，遍历出错" << endl;
			return;
			}
		}
		
	}
	cout << decodedText << endl;
}

double HuffmanCode::Compare() {
	double huffmanSize = this->CodedText().size();
	double ascSize = 8 * this->str.size();
	double percentSaved = 1 - huffmanSize / ascSize;
	return 100 * percentSaved;
}