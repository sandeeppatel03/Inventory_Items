#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
vector<string> split(string str, char del);


class Item {
public:
	string Name;
	string Code;
	string price;

	string ToText() {
		return Name + "\t" + Code + "\t" + (price);
	}

	void LoadFromText(string content) {
		vector<string> result = split(content, '\t');

		Name = result[0];
		Code = result[1];
		price = (result[2]);

	}

};
bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

bool isInteger(int s)
{
	for (int i = 0; i < s; i++)
		if (isdigit(s) == false)
			return false;

	return true;
}



void SaveDataToFile(vector<Item>& Items)
{

	string content = "";
	for (int i = 0; i < Items.size(); i++) {
		content += Items[i].ToText() + "\n";
	}

	//Create file
	fstream file;
	file.open("C:\\New folder\\items.txt", ios_base::out);
	file.seekp(0);
	file << content;
	file.close();
}

vector<Item> ReadFileData()
{
	string fileContent = "";
	ifstream file1("C:\\New folder\\items.txt");
	string str;
	while (std::getline(file1, str))
	{
		fileContent += str + '\n';
	}


	//Read file and store it to vector
	vector<Item>storedItems;
	vector<string> fileLines = split(fileContent, '\n');
	for (int i = 0; i < fileLines.size(); i++) {
		string line = fileLines[i];
		Item itm;
		itm.LoadFromText(line);
		storedItems.push_back(itm);
	}
	return storedItems;
}

int FindItem(vector<Item> items, string code) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i].Code == code) {
			return i;
		}
	}

	return -1;
}


vector<string> split(string str, char del) {
	// declaring temp string to store the curr "word" upto del
	vector<string> result;
	string temp = "";
	for (int i = 0; i < (int)str.size(); i++) {
		// If cur char is not del, then append it to the cur "word", otherwise
		  // you have completed the word, print it, and start a new word.
		if (str[i] != del) {
			temp += str[i];
		}
		else {
			result.push_back(temp);
			temp = "";
		}
	}
	//adding remaining text(End of line)
	if (temp.size() > 0) {
		result.push_back(temp);
	}
	return result;
}

int main() {
	while (true) {
		int a;

		std::cout << "Enter the desired number to perform insert, modify and search items:\n";
		std::cout << "Enter 1 to insert an item\n";
		std::cout << "Enter 2 to modify an items\n";
		std::cout << "Enter 3 to search items\n";
		std::cout << "Enter 0 to exit\n";
		std::cin >> a;

		if (a == 0) {
			//Exit the loop if user want too
			cerr << "You have choose to exit the code or you have  entered invalid number ";
			break;
		}

		switch (a) {

		case 1: {






			vector<Item>Items = ReadFileData();
			for (int i = 0; i < 1; i++) {
				Item itm;
				cout << "Enter item name:";
				cin >> itm.Name;
				cout << "Enter item code:";
				cin >> itm.Code;
				cout << "Enter item price:";
				cin >> itm.price;
				if (isNumber(itm.price)) {

				}
				else {
					cout << "**************\nPlease enter valid item price" << endl;
					cout << "Please re-enter all data\n**************" << endl;
					break;
				}
				Items.push_back(itm);
				SaveDataToFile(Items);
				cout << "Item saved successfully" << endl;

			}
			break;





		}
		case 2: {	//Search item
			vector<Item>Items = ReadFileData();
			for (int i = 0; i < Items.size(); i++) {
				cout << i + 1 << ":" << Items[i].Code << endl;
			}

			string y;
			int index;
			cout << "Enter Index number: ";
			cin >> y;


			if (isNumber(y)) {
				index = stoi(y);

				if (index == 0) {
					cout << "Please enter valid index number" << endl;
					break;
				}

				--index;
				if (index >= 0) {
					if (index > Items.size()) {
						cerr << "Error::Index out of range\nPlease enter valid index number" << endl;
						break;
					}
					else
					{


						Item itm = Items[index];
						cout << itm.ToText();
						cout << "\nEnter New Item Name: " << endl;;
						cin >> itm.Name;
						cout << "Enter New Item Code: " << endl;
						cin >> itm.Code;
						cout << "Enter New Item Price: " << endl;
						cin >> itm.price;
						if (isNumber(itm.price)) {

						}
						else {
							cout << "**************\nPlease enter valid item price" << endl;
							cout << "Please re-enter all data\n**************" << endl;
							break;
						}

						Items[index] = itm;
						SaveDataToFile(Items);
						cout << "Item modified successfully" << endl;
						break;
					}
				}
			}
			else {
				cerr << "Please enter integer value" << endl;
				break;
			}

		}

		case 3: {
			vector<Item>Items = ReadFileData();
			for (int i = 0; i < Items.size(); i++) {

				cout << "Item " << i + 1 << " :" << endl;
				cout << "Item Name: " << Items[i].Name << endl;
				cout << "Item Code: " << Items[i].Code << endl;
				cout << "Item Price: " << Items[i].price << endl;
			}

			break;

		}


		}
	}


}