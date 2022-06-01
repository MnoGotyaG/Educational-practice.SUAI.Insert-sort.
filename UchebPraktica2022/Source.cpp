#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <locale>
#include <codecvt>


using namespace std;//������������� ������������ ���� ����������� ���������� �++

void sort_text(vector<wstring>& words)//�������� ���������� ���������
{
	for (int i = 1; i < words.size(); ++i)//���� �� ������� ����
	{
		int k = i;

		while (k > 0)//���� �>0
		{
			wchar_t first_symb = words[k][0];// ������ ������ ��������  ����� 
			wchar_t second_symb = words[k - 1][0];//������ ������ �����������  ����� 

			int mass1 = 0;//������� ���. ���� ��� ���������
			int mass2 = 0;

			if (iswdigit(words[k][0])) mass1 += 1200;//���� ������ ����� �� ����������� ��� ���
			
			else//����� ���� �� �����
			{
				first_symb = towlower(words[k][0]);//��������� ����� � ������ �������
				//����������� ��� ����� �, �� ��� ���� ����� �������� � ������� (� ��� ������ ���� ��������� ����� ��������)
				if (int(first_symb) <= L'�') mass1 = 0;
				else if (int(first_symb) == L'�') mass1 -= 28;
				else if (int(first_symb) > L'�') mass1 += 1;
			}
			//���� ����� ��� ������ ����� ����������� �����
			if (iswdigit(words[k - 1][0])) mass2 += 1200;
			else
			{
				second_symb = towlower(words[k - 1][0]);
				if (int(second_symb) <= L'�') mass2 = 0;
				else if (int(second_symb) == L'�') mass2 -= 28;
				else if (int(second_symb) > L'�') mass2 += 1;
			}

			if ((second_symb + mass2) > (first_symb + mass1))//���������� �������� ���. ����� �������� ����������� ����
			{
				//������ �������
				wstring tmp = words[k - 1];
				words[k - 1] = words[k];
				words[k] = tmp;

			}
			--k;// ��������� � �����������  ����
		}

	}
}

void parse_text(wstring& input_txt, vector <wstring>& words)
{
	wstring new_word;// ����� ��� ������

	for (int i = 0; i < (input_txt.size()); ++i)
	{
		wchar_t ch = input_txt[i];// ������
		
		if (iswalnum(ch))// ���� ch  ����� ��� �����
		{
			new_word += ch;// ��������� ������ 
			if (input_txt.size() - 1 == i)//���� ����� �� ����� (��� ������ ���������� �����)
			{
				words.push_back(new_word);//��������� ����� � ������ ����
				new_word.clear();// ������� ����� ��� ������
			}
		}
		//����� ���� ������� ������ ������� ��� ����� � ���������� � ���� ������� �����,�� ���������� ������� ��� ����� � �����
		else if (iswdigit(input_txt[i + 1]) and (iswdigit(input_txt[i - 1]) and ((ch == L',') or (ch == L'.'))))
		{
			new_word += ch;//��������� ������
		}
		else if (new_word.length())//����� ���� ���������� ������� �� ��������� (����� �����) �� ������
		{
			words.push_back(new_word);//��������� �����
			new_word.clear();//������� �����
		}

	}



}

void get_stats(vector<wstring>& words, int* stats)
{
	for (auto word : words)//������ ����� �� ������� ����
	{
		wchar_t ch = towlower(word[0]);//� ������ ������� �����
		
		//����������� ��� ����� �, ���������� ����� �
		//��� ������� ������� ����������� ��� ������ � ������� � �����������
		if (ch == L'�') stats[6] += 1;
		else
		{
			if (ch > L'�') stats[int(ch) - 1072 + 1] += 1;
			else stats[int(ch) - 1072] += 1;
		}
	}
}

void read_file(wstring FILE_PATH, wstring& input_txt)
{
	wstring line; // �����(���� ���������� �����������)
	wifstream file;// ���� �� ������

	file.open(FILE_PATH);// �������� �����

	// ����� ��������� ����� �� UTF-8
	file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));
	
	if (!file.is_open()) // ���� �� ��������
	{
		wcout << L"���� �� ������\n\n";
		exit(-1);
	}

	while (getline(file, line))//������ ������ ������ ���� ����
	{
		input_txt += line;//���������� ������ �� ������ � ������ � �������
		input_txt += L'\n';
	}
	file.close();// �������� �����
}

void write_sorted_words(wstring FILE_PATH, vector<wstring>& words)
{
	wofstream file;
	file.open(FILE_PATH);

	file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));

	if (!file.is_open())
	{
		wcout << L"���� �� ������\n\n";
		exit(-1);
	}
	//��� ������ ����� ��� ����� ���������� ��������������� ����� ������������ � ��������� �����
	for (auto ch : L"��������������������������������1234567890")
	{
		bool flag = false;
		for (auto word : words)
		{
			if (ch == towlower(word[0]))
			{
				file << word << L" ";
				flag = true;
			}

		}
		if (flag) file << L"\n";//�������� ������ ����� �������
	}
	file.close();//�������� �����
}

void write_data(wstring FILE_PATH, wstring& input_txt, int words_count, size_t time, int* stats)
{
	//������ ���������� � ����
	wofstream file;
	file.open(FILE_PATH);

	file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));

	if (!file.is_open())
	{
		wcout << L"���� �� ������\n\n";
		exit(-1);
	}

	file << L"��������� �����:" << endl;
	file << input_txt << endl;
	file << endl;
	file << L"������� 3: ���������, �� ��������, �� �����������, ��������� �����, ���������� ���������" << endl;
	file << L"���-�� ����: " << words_count << endl;
	file << L"����� ����������: " << (static_cast<double>(time) / 1000) << L" ���" << endl;
	file << L"�������������: ���������, �� ��������, �� �����������, ��������� �����, ���������� ��������� :" << endl;
	//����������� ��� ����� �
	for (int i = 0; i < 33; ++i)
	{
		if (i < 6) file << wchar_t(i + 1072) << L" - " << stats[i] << endl;
		else if (i == 6) file << L'�' << L" - " << stats[6] << endl;
		else if (i > 6) file << wchar_t(i - 1 + 1072) << L" - " << stats[i] << endl;
	}

	file.close();
}

void print_data(wstring& input_txt, int words_count, size_t time, int* stats)
{
	//����� ����������
	wcout << L"��������� �����:" << endl;
	wcout << input_txt << endl;
	wcout << endl;
	wcout << L"������� 3: ���������, �� ��������, �� �����������, ��������� �����, ���������� ���������" << endl;
	wcout << L"���-�� ����: " << words_count << endl;
	wcout << L"����� ����������: " << (static_cast<double>(time) / 1000) << L" ���" << endl;
	wcout << L"�������������: ���������, �� ��������, �� �����������, ��������� �����, ���������� ��������� :" << endl;

	//����������� ��� ����� �
	for (int i = 0; i < 33; ++i)
	{
		if (i < 6) wcout << wchar_t(i + 1072) << L" - " << stats[i] << endl;
		else if (i == 6) wcout << L'�' << L" - " << stats[6] << endl;
		else if (i > 6) wcout << wchar_t(i - 1 + 1072) << L" - " << stats[i] << endl;
	}

}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// ��� ����� � ������� ������� �������� 1251- ���������

	wstring INPUT_FILE; // ���� �� ���� � �������
	wcout << L"������� ���� � ����� ��� ��� ��������: ";
	wcin >> INPUT_FILE;
	if (INPUT_FILE.length()==0)
	{
		wcout << L"���� ������" << endl;
		return 0;
	}

	wstring input_txt; // �������� �����
	vector <wstring> words; // ������ ����
	int stats[33]{ 0 };//���������� (���������� ���� �� ������ ����� ��������):

	read_file(INPUT_FILE, input_txt);  // ������ �� �����
	parse_text(input_txt, words);		// ��������� ������� ����

	clock_t start_time = clock();
	sort_text(words);	// ���������� ������� ���� (�� ��������)
	
	clock_t end_time = clock();

	write_sorted_words(L"1.result3k.txt", words);   // ������ � ���� ������� ��������������� ����


	get_stats(words, stats); // ��������� ���������� ������ ���� �� ������

	print_data(input_txt, words.size(), (end_time - start_time), stats); // ����� �������� ���������� � �������
	write_data(L"1.analysis3k.txt", input_txt, words.size(), (end_time - start_time), stats); //����� �������� ���������� � ����

	return 0;
}