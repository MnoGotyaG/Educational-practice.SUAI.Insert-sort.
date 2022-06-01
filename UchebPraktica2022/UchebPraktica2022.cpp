//#include<string>
//#include<list>
//#include<vector>
//#include<iostream>
//#include<sstream>
//#include <cctype>
//
//using namespace std;
//
////i, j, key = 0, temp = 0;
//void InsertSort(vector<string> array_of_words) //сортировка вставками
//{
//	int len_array_of_words = array_of_words.size();
//	for (int i = 0; i < len_array_of_words - 1; i++)
//	{
//		int key = i + 1;
//		string temp = array_of_words[key];
//		for (int j = i + 1; j > 0; j--)
//		{
//			if (temp < array_of_words[j - 1])
//			{
//				array_of_words[j] = array_of_words[j - 1];
//				key = j - 1;
//			}
//		}
//		array_of_words[key] = temp;
//	}
//	cout << endl << "Результирующий массив: ";
//	for (int i = 0; i < len_array_of_words; i++) //вывод массива
//		cout << array_of_words[i] << " ";
//}
//void sort(vector<string> array_of_words)
//{
//	int len_array_of_words = array_of_words.size();
//	string tmp;
//	for (int i = 0, j; i < len_array_of_words; ++i)
//	{
//		tmp = array_of_words[i];
//		for (j = i - 1; j >= 0 && tolower(array_of_words[j][0]) > tolower(tmp[0]); --j)
//			array_of_words[j + 1] = array_of_words[j];
//		array_of_words[j + 1] = tmp;
//	}
//	for (int i = 0; i < array_of_words.size(); ++i)
//	{
//		
//		cout << array_of_words[i] << endl;
//	}
//}
//
////главная функция
//void main()
//{
//	setlocale(LC_ALL, "Rus");
//	vector<string> new_text ;
//	string new_word;
//	string input_txt = "На мне этот гучи я свечусь, как рок зведа 12,3";
//
//	//stringstream any_words(input_txt);
//	vector <string> array_of_words;
//	//for (string word; any_words >> word; array_of_words.push_back(word));*/
//	cout << input_txt.size() << endl;
//	for (int j = 0; j < (input_txt.size() + 1); ++j)
//	{
//		auto ch = input_txt[j];
//		if ((isalpha((unsigned char)ch))) new_word += ch;
//		else if ((isdigit(ch)))
//		else if (new_word.length() != 0)
//		{
//			array_of_words.push_back(new_word);
//			new_word.clear();
//		}
//	}
//	for (int i = 0; i< array_of_words.size(); ++i)
//	{
//		cout << array_of_words[i] << endl;
//	}
//	cout << endl; 
//	//InsertSort(array_of_words);
//	sort(array_of_words);
//	wchar_t lox;
//	/*for (string word : input_txt)
//	{
//		for (char ch : word) {
//
//		}
//		new_text.push_back(word);
//	}
//	cout << input_txt.length() << endl;*/
//
//	
//	//int n;
//	//cout << "Количество элементов в массиве > "; cin >> n;
//	//int* mas = new int[n];
//	//for (i = 0; i < n; i++) //ввод массива
//	//{
//	//	cout << i + 1 << " элемент > "; cin >> mas[i];
//	//}
//	//InsertSort(mas, n); //вызов функции
//	//delete[] mas;
//	//system("pause>>void");
//}