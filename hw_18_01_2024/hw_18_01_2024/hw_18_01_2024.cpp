#include <iostream>
#include <algorithm>
#include <ctime>
#include <regex>
#include <locale>
using namespace std;

class String
{
	char* text = nullptr;
	unsigned int length = 0;
	unsigned int capacity = 80;

public:
	String() : String("", 80) {}

	String(const char* text) : String(text, 80) {}

	String(unsigned int capacity) : String("", capacity) {}

	String(const String& original) : String(original.text, original.capacity) {}

	// main c-tor
	String(const char* text, unsigned int capacity)
	{
		SetString(text, capacity);
	}

private:
	void SetString(const char* text, unsigned int capacity = 80)
	{
		length = strlen(text);

		// для пустых строк делаем резерв памяти 80
		if (length == 0)
		{
			this->capacity = 80;
		}
		else // для НЕпустых - по ситуации
		{
			// нормализация переданного параметра capacity
			if (capacity > length * 10)
				capacity = length * 10;

			if (capacity <= length)
				capacity = length + 1;

			this->capacity = capacity;
		}

		/*cout << "\n\n=================\n\n";
		cout << "capacity param: " << this->capacity << "\n";
		cout << "length param: " << this->length << "\n";
		cout << "\n\n=================\n\n";*/

		if (this->text != nullptr)
			delete[] this->text;

		this->text = new char[this->capacity];
		strcpy_s(this->text, length + 1, text);
	}

public:
	~String()
	{
		if (text != nullptr)
		{
			delete[] text;
			text = nullptr;
		}
	}

	//заполнение строки с клавиатуры
	void FromKeyboard()
	{
		cout << "Enter text: ";
		char txt[100];
		cin.getline(txt, sizeof(txt));
		SetString(txt);
	}

	//сравнение нашеё строки с какой-то другой строкой, если контенты совпали - вернуть true, иначе - false
	bool CompareTo(String& str)
	{
		for (int i = 0; i < strlen(text); i++)
		{
			if (text[i] == str.text[i])
			{
				cout << "true\n";
				return true;
			}
			else
			{
				cout << "false\n";
				return false;
			}
		}
	}

	//проверить, содержится ли в нашей строке переданная подстрока (в любой позиции)
	bool Contains(String& txt)
	{
		return strstr(text, txt.text) != nullptr;
	}

	//присоединить в конец нашей строки переданную как параметр строку
	void Concat(String& str)
	{
		unsigned int newLength = length + str.length;
		if (newLength >= capacity)
		{
			capacity = newLength + 1;
			char* temp = new char[capacity];
			strcpy_s(temp, length + 1, text);
			strcpy_s(temp, capacity, str.text);
			delete[] text;
			text = temp;
			length = newLength;
		}
		else
		{
			strcat_s(text, capacity, str.text);
			length = newLength;
		}
	}

	//проверить, заканчивается ли наша строка текстом, который передан в параметре
	bool  EndsWith(String& txt)
	{
		if (txt.length > length)
			return false;
		return strcmp(text + length - txt.length, txt.text) == 0;
	}

	//проверить, начинается ли наша строка с текста, который передан в параметре
	bool StartsWith(String& txt)
	{
		if (txt.length > length)
			return false;
		return strncmp(text, txt.text, txt.length) == 0;
	}

	//проверка на вхождение символа в строку, в результате работы возвращает индекс первого найденого символа (от начала строки, слева направо), если нечего не найдено, возвращает -1
	int IndexOf(char symbol)
	{
		for (int i = 0; i < length; i++)
		{
			if (text[i] == symbol)
			{
				return i;
			}
		}
		return -1;
	}

	//проверка на вхождение символа в строку, в результате работы возвращает индекс последнего найденного символа (поиск с конйа строки, справа налево); если нечего не найдено, возвращает -1
	int LastIndexOf(char symbol)
	{
		for (int i = length - 1; i >= 0; i--)
		{
			if (text[i] == symbol)
			{
				return i;
			}
		}
		return -1;
	}

	//удаление всех символов до конца строки, начиная от переданного индекса (с проверкой корректности индекса)
	void Remove(int start)
	{
		if (start >= 0 && start < length)
		{
			memmove(text + start, text + start + 1, length - start);
			length--;
			text[length] = '\0';
		}
	}

	//удаление count символов, начиная от индекса start (с проверко корректности индекса и требуемого количества)
	void Remove(int start, int count)
	{
		if (start >= 0 && start < length && count > 0)
		{
			memmove(text + start, text + start + count, length - start - count);
			length -= count;
			text[length] = '\0';
		}
	}

	//меняет в строке все найденные символы O на переданный символ D
	void Replace(char O, char D)
	{
		for (unsigned int i = 0; i < length; i++)
		{
			if (text[i] == O)
			{
				text[i] = D;
			}
		}
		cout << text << "\n";
	}

	//привод к нижнему регистру (в том числе и для кириллического текста)
	String ToLower()
	{
		_strlwr_s(text, capacity);
		return text;
	}

	//привод к верхнему регистру (в том числе и для кириллического текста)
	String ToUpper()
	{
		_strupr_s(text, capacity);
		return text;
	}

	//переворачивает строки (изменение порядка следования символов в массиве на противоположный)
	void Reverse()
	{
		if (text != nullptr && length > 1)
		{
			cout << _strrev(text) << "\n";
		}
	}

	//сортировка всех символов строки в алфавитном порядке от А до Я
	void SortAZ()
	{
		if (text != nullptr && length > 1)
		{
			sort(text, text + strlen(text));
			cout << text << "\n";
		}
	}

	//сортировка всех символов строки в алфавитном порядке от Я до А
	void SortZA()
	{
		if (text != nullptr && length > 0)
		{
			sort(text, text + length, [](char a, char b)
				{
					return tolower(a, locale()) > tolower(b, locale());
				});
			cout << text << "\n";
		}
	}

	//случайное перемешивание символов строки
	void Shuffle()
	{
		if (text != nullptr && length > 1)
		{
			random_shuffle(text, text + strlen(text));
			cout << text << "\n";
		}
	}

	//заполнение строки случайными символави (на весь capacity)
	void RandomFill()
	{
		for (int y = 0; y < length; y++)
		{
			text[y] = rand() % length;
			text[y] = 'a' + rand() % 26;
			cout << text[y];
		}
	}

	// возвращать из класса указатель на массив чаров нельзя - это нарушит инкапсуляцию и позволит клиенту СЛОМАТЬ содержимое (состояние) объекта
	// если создавать копию массива чаров, то под неё придётся выделять память, а почистить её клиент скорее всего ЗАБУДЕТ 
	// поэтому здесь выдаётся КОПИЯ состояния в виде объекта текущего класса
	String GetString() const
	{
		//char* copy = new char[length + 1];
		//strcpy_s(copy, length + 1, text);
		//return copy;

		String copy = text;
		return copy;
	}

	int GetLength() const
	{
		return length;
	}

	// метода SetLength не должно быть!

	int GetCapacity() const
	{
		return capacity;
	}

	// в целях повшения производительности, не тратится время на:
	// 1) очистку памяти делитом
	// 2) запись в каждый символ пробелов (не запускается цикл фор)
	// 3) не меняется capacity

	// достаточно в начало строки записать \0, и длину выставить в 0
	// многие методы класса ориентируются именно на длину, и если она равна 0, то клиент будет уверен, что строка пустая
	void Clear()
	{
		text[0] = '\0';
		length = 0;
	}

	// если резерв памяти стал значительно больше, чем размер строки, то можно вызвать принудительное перевыделение памяти, суть которого в 
	void ShrinkToFit() // том, чтобы сделать резерв такой же длины, как и length
	{
		if (length + 1 <= capacity)
		{
			return;
		}

		capacity = length + 1;
		char* temp = new char[capacity];
		strcpy_s(temp, capacity, text);
		delete[] text;
		text = temp;
	}

	void Print() const
	{
		cout << "Text: " << text << "\n";
		cout << "Length: " << length << "\n";
		cout << "Capacity: " << capacity << "\n";
	}
};

int main()
{
	srand(time(NULL));
	String a("Alex. ");
	String b("ITSTEP .");

	//введенние с клавиатуры
	/*String c;
	c.FromKeyboard();
	c.Print();*/

	//тест CompareTo
	//a.CompareTo(b);
	
	//тест Contains
	/*String substr("STEP");
	cout << "Contains STEP: " << a.Contains(substr) << "\n";*/
	
	//тест Concat
	a.Concat(b);
	a.Print();

	// тест EndsWith и StartsWith
	/*String endTest("ITSTEP .");
	String startTest("Alex");
	cout << "EndsWith ITSTEP .: " << a.EndsWith(endTest) << "\n";
	cout << "StartsWith Alex: " << a.StartsWith(startTest) << "\n";*/

	//тест IndexOf и LastIndexOf
	/*cout << "IndexOf 'x': " << a.IndexOf('x') << "\n";
	cout << "LastIndexOf '.': " << a.LastIndexOf('.') << "\n";*/

	//тест Remove
	/*a.Remove(0);
	a.Remove(0, 4);
	a.Print();*/

	//тест Replace
	/*a.Replace('e', 'E');*/

	//тест ToLower и ToUpper
	/*a.ToLower();
	a.Print();
	a.ToUpper();
	a.Print();*/

	//тест Reverse
	/*a.Reverse();*/

	//тест SortAZ и SortZA
	/*a.SortAZ();
	a.SortZA();*/

	//тест Shuffle
	/*a.Shuffle();*/

	//тест RandomFill
	/*a.RandomFill();*/
}