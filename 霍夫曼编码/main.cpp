#include"huffman.h"
#include<iomanip>

int main() {
	string str;
	string codedText;
	cout << "输入你要编码的字符串：";
	getline(cin, str);
	HuffmanCode t(str);
	t.Encode();
	cout << "编码结果为：";
	cout << t.CodedText() << endl;
	cout << "霍夫曼编码相比asc码节省了" << setprecision(3) << t.Compare() << "%的空间" << endl;
	do{
		cout << "输入要解码的编码，或输入Q退出：";
		getline(cin, codedText);
		if (codedText != "q"&&codedText != "Q") {
			cout << "解码结果为：";
			t.Decode(codedText);
		}
	} while (codedText != "q"&&codedText != "Q");
	system("pause");
	return 0;
}