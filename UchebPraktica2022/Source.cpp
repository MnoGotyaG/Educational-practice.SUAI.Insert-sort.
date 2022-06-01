#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <locale>
#include <codecvt>


using namespace std;//использование пространства имен стандартной библиотеки С++

void sort_text(vector<wstring>& words)//алгоритм сортировки вставками
{
	for (int i = 1; i < words.size(); ++i)//цикл по массиву слов
	{
		int k = i;

		while (k > 0)//пока к>0
		{
			wchar_t first_symb = words[k][0];// первый символ текущего  слова 
			wchar_t second_symb = words[k - 1][0];//первый символ предыдущего  слова 

			int mass1 = 0;//индексы доп. веса для сравнения
			int mass2 = 0;

			if (iswdigit(words[k][0])) mass1 += 1200;//если символ число то увеличиваем его вес
			
			else//Иначе если не число
			{
				first_symb = towlower(words[k][0]);//Переводим букву в нижний регистр
				//Оптимизация для буквы ё, тк она идет после алфавита в юникоде (её код больше кода последней буквы алфавита)
				if (int(first_symb) <= L'е') mass1 = 0;
				else if (int(first_symb) == L'ё') mass1 -= 28;
				else if (int(first_symb) > L'е') mass1 += 1;
			}
			//ТОже самое для первой буквы предыдущего слова
			if (iswdigit(words[k - 1][0])) mass2 += 1200;
			else
			{
				second_symb = towlower(words[k - 1][0]);
				if (int(second_symb) <= L'е') mass2 = 0;
				else if (int(second_symb) == L'ё') mass2 -= 28;
				else if (int(second_symb) > L'ё') mass2 += 1;
			}

			if ((second_symb + mass2) > (first_symb + mass1))//Сравниваем учитывая доп. массу символов посчитанную выше
			{
				//меняем местами
				wstring tmp = words[k - 1];
				words[k - 1] = words[k];
				words[k] = tmp;

			}
			--k;// переходим к предыдущему  сову
		}

	}
}

void parse_text(wstring& input_txt, vector <wstring>& words)
{
	wstring new_word;// слово для записи

	for (int i = 0; i < (input_txt.size()); ++i)
	{
		wchar_t ch = input_txt[i];// символ
		
		if (iswalnum(ch))// если ch  число или буква
		{
			new_word += ch;// добовляем символ 
			if (input_txt.size() - 1 == i)//если дошел до конца (для записи последнего слова)
			{
				words.push_back(new_word);//добавляем слово в массив слов
				new_word.clear();// очищаем слово для записи
			}
		}
		//Иначе Если текущий символ запятая или точка и предыдущий и след символы цифры,то записываем запятую или точку в слово
		else if (iswdigit(input_txt[i + 1]) and (iswdigit(input_txt[i - 1]) and ((ch == L',') or (ch == L'.'))))
		{
			new_word += ch;//добовляем символ
		}
		else if (new_word.length())//Иначе если предыдущие условия не сработали (конец слова) не пустой
		{
			words.push_back(new_word);//добовляем слово
			new_word.clear();//Очищаем слово
		}

	}



}

void get_stats(vector<wstring>& words, int* stats)
{
	for (auto word : words)//каждой слово из массива слов
	{
		wchar_t ch = towlower(word[0]);//в нижний регистр букву
		
		//оптимизация для буквы её, добавление после е
		//для каждого символа вычисляется его индекс в массиве и итерируется
		if (ch == L'ё') stats[6] += 1;
		else
		{
			if (ch > L'е') stats[int(ch) - 1072 + 1] += 1;
			else stats[int(ch) - 1072] += 1;
		}
	}
}

void read_file(wstring FILE_PATH, wstring& input_txt)
{
	wstring line; // буфер(куда записываем прочитанное)
	wifstream file;// файл на чтение

	file.open(FILE_PATH);// открытие файла

	// смена кодировки файла на UTF-8
	file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));
	
	if (!file.is_open()) // если не открылся
	{
		wcout << L"Файл не открыт\n\n";
		exit(-1);
	}

	while (getline(file, line))//читаем каждую строку пока есть
	{
		input_txt += line;//записываем строку из буфера в строку с текстом
		input_txt += L'\n';
	}
	file.close();// закрытие файла
}

void write_sorted_words(wstring FILE_PATH, vector<wstring>& words)
{
	wofstream file;
	file.open(FILE_PATH);

	file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));

	if (!file.is_open())
	{
		wcout << L"Файл не открыт\n\n";
		exit(-1);
	}
	//для каждой буквы или цифры записываем соответствующие слова начинающиеся с выбранной буквы
	for (auto ch : L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя1234567890")
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
		if (flag) file << L"\n";//Переносы строки между буквами
	}
	file.close();//закрытие файла
}

void write_data(wstring FILE_PATH, wstring& input_txt, int words_count, size_t time, int* stats)
{
	//Запись статистики в файл
	wofstream file;
	file.open(FILE_PATH);

	file.imbue(locale(locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));

	if (!file.is_open())
	{
		wcout << L"Файл не открыт\n\n";
		exit(-1);
	}

	file << L"Введенный текст:" << endl;
	file << input_txt << endl;
	file << endl;
	file << L"Вариант 3: кириллица, по алфавиту, по возрастанию, учитывать числа, сортировка вставками" << endl;
	file << L"Кол-во слов: " << words_count << endl;
	file << L"Время сортировки: " << (static_cast<double>(time) / 1000) << L" сек" << endl;
	file << L"Статистистика: кириллица, по алфавиту, по возрастанию, учитывать числа, сортировка вставками :" << endl;
	//Оптимизация для буквы ё
	for (int i = 0; i < 33; ++i)
	{
		if (i < 6) file << wchar_t(i + 1072) << L" - " << stats[i] << endl;
		else if (i == 6) file << L'ё' << L" - " << stats[6] << endl;
		else if (i > 6) file << wchar_t(i - 1 + 1072) << L" - " << stats[i] << endl;
	}

	file.close();
}

void print_data(wstring& input_txt, int words_count, size_t time, int* stats)
{
	//вывод статистики
	wcout << L"Введенный текст:" << endl;
	wcout << input_txt << endl;
	wcout << endl;
	wcout << L"Вариант 3: кириллица, по алфавиту, по возрастанию, учитывать числа, сортировка вставками" << endl;
	wcout << L"Кол-во слов: " << words_count << endl;
	wcout << L"Время сортировки: " << (static_cast<double>(time) / 1000) << L" сек" << endl;
	wcout << L"Статистистика: кириллица, по алфавиту, по возрастанию, учитывать числа, сортировка вставками :" << endl;

	//Оптимизация для буквы ё
	for (int i = 0; i < 33; ++i)
	{
		if (i < 6) wcout << wchar_t(i + 1072) << L" - " << stats[i] << endl;
		else if (i == 6) wcout << L'ё' << L" - " << stats[6] << endl;
		else if (i > 6) wcout << wchar_t(i - 1 + 1072) << L" - " << stats[i] << endl;
	}

}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// для ввода в консоль русских символов 1251- кодировка

	wstring INPUT_FILE; // путь на файл с текстом
	wcout << L"Введите путь к файлу или его название: ";
	wcin >> INPUT_FILE;
	if (INPUT_FILE.length()==0)
	{
		wcout << L"Файл пустой" << endl;
		return 0;
	}

	wstring input_txt; // исходный текст
	vector <wstring> words; // массив слов
	int stats[33]{ 0 };//Статистика (количество слов на каждую букву алфавита):

	read_file(INPUT_FILE, input_txt);  // чтение из файла
	parse_text(input_txt, words);		// получение массива слов

	clock_t start_time = clock();
	sort_text(words);	// сортировка массива слов (по алфавиту)
	
	clock_t end_time = clock();

	write_sorted_words(L"1.result3k.txt", words);   // запись в файл массива отсортированных слов


	get_stats(words, stats); // получение статистики первых букв по словам

	print_data(input_txt, words.size(), (end_time - start_time), stats); // вывод итоговой информации в консоль
	write_data(L"1.analysis3k.txt", input_txt, words.size(), (end_time - start_time), stats); //вывод итоговой информации в файл

	return 0;
}