#include"huffman.h"
#include<iomanip>

int main() {
	string str;
	string codedText;
	cout << "������Ҫ������ַ�����";
	getline(cin, str);
	HuffmanCode t(str);
	t.Encode();
	cout << "������Ϊ��";
	cout << t.CodedText() << endl;
	cout << "�������������asc���ʡ��" << setprecision(3) << t.Compare() << "%�Ŀռ�" << endl;
	do{
		cout << "����Ҫ����ı��룬������Q�˳���";
		getline(cin, codedText);
		if (codedText != "q"&&codedText != "Q") {
			cout << "������Ϊ��";
			t.Decode(codedText);
		}
	} while (codedText != "q"&&codedText != "Q");
	system("pause");
	return 0;
}