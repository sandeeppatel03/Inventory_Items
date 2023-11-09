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
	bool result = false;


	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)

			return false;

	return true;
}
int valid_number(string str)
{
	int i = 0, j = str.length() - 1;

	// Handling whitespaces
	while (i < str.length() && str[i] == ' ')
		i++;
	while (j >= 0 && str[j] == ' ')
		j--;

	if (i > j)
		return 0;

	// if string is of length 1 and the only
	// character is not a digit
	if (i == j && !(str[i] >= '0' && str[i] <= '9'))
		return 0;

	// If the 1st char is not '+', '-', '.' or digit
	if (str[i] != '.' && str[i] != '+'
		&& str[i] != '-' && !(str[i] >= '0' && str[i] <= '9'))
		return 0;

	// To check if a '.' or 'e' is found in given
	// string. We use this flag to make sure that
	// either of them appear only once.
	bool flagDotOrE = false;

	for (i; i <= j; i++) {
		// If any of the char does not belong to
		// {digit, +, -, ., e}
		if (str[i] != 'e' && str[i] != '.'
			&& str[i] != '+' && str[i] != '-'
			&& !(str[i] >= '0' && str[i] <= '9'))
			return 0;

		if (str[i] == '.') {
			// checks if the char 'e' has already
			// occurred before '.' If yes, return 0.
			if (flagDotOrE == true)
				return 0;

			// If '.' is the last character.
			if (i + 1 > str.length())
				return 0;

			// if '.' is not followed by a digit.
			if (!(str[i + 1] >= '0' && str[i + 1] <= '9'))
				return 0;
		}

		else if (str[i] == 'e') {
			// set flagDotOrE = 1 when e is encountered.
			flagDotOrE = true;

			// if there is no digit before 'e'.
			if (!(str[i - 1] >= '0' && str[i - 1] <= '9'))
				return 0;

			// If 'e' is the last Character
			if (i + 1 > str.length())
				return 0;

			// if e is not followed either by
			// '+', '-' or a digit
			if (str[i + 1] != '+' && str[i + 1] != '-'
				&& (str[i + 1] >= '0' && str[i] <= '9'))
				return 0;
		}
	}

	/* If the string skips all above cases, then
	it is numeric*/
	return 1;
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

		std::cout << "Enter the desired number to perform insert, modify and see all items:\n";
		std::cout << "Enter 1 to insert an item\n";
		std::cout << "Enter 2 to modify an items\n";
		std::cout << "Enter 3 to search items through item code\n";
		std::cout << "Enter 0 to exit\n";
		std::cin >> a;

		if (a == 0) {
			//Exit the loop if user want too
			cerr << "Error::You have choose to exit the code or you have  entered invalid value " << endl;
			cout << "You will exit out of the program in few seconds" << endl;
			//sleep(3);
			break;
		}

		switch (a) {

		case 1: {

			vector<Item>Items = ReadFileData();
			for (int i = 0; i < 1; i++) {
				Item itm;
				if (i == 0) {
					getline(cin, itm.Name);
				}
				cout << "Enter item name:";
				getline(cin, itm.Name);
				cout << "Enter item code: \n*It must be a single word\n";

				cin >> itm.Code;
				cout << "Enter item price:";
				cin >> itm.price;
				if (valid_number(itm.price)) {

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


				if (index >= 0) {
					if (index > Items.size()) {
						cerr << "Error::Index out of range\nPlease enter valid index number" << endl;
						break;
					}
					else
					{

						--index;
						Item itm = Items[index];
						int i = index;
						//cout << itm.ToText();


						cout << "Item number " << i + 1 << ":" << endl;
						cout << "Item Name: " << Items[i].Name << endl;
						cout << "Item Code: " << Items[i].Code << endl;
						cout << "Item Price: " << Items[i].price << endl;
						//cout<<"******************************************************************************************************************"<<endl;




						for (int i = 0; i < 1; i++) {
							if (i == 0) {
								getline(cin, itm.Name);
							}
						}
						cout << "\nEnter New Item Name: " << endl;;
						getline(cin, itm.Name);
						cout << "Enter New Item Code: " << endl;
						cin >> itm.Code;
						cout << "Enter New Item Price: " << endl;
						cin >> itm.price;
						if (valid_number(itm.price)) {

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
				cerr << "Error::Please enter integer value" << endl;
				break;
			}

		}

		case 3: {
			vector<Item>Items = ReadFileData();
			if (Items.size() == 0) {
				cerr << "Error::No items are present" << endl;
			}
			else {
				for (int i = 0; i < Items.size(); i++) {
					cout << i + 1 << ":" << Items[i].Code << endl;
				}

			}
			//vector<string>allcode;
			// for (int i;i<Items.size();i++){

			// 	//allcode.push_back(Items[i].Code);
			// 	string x;
			// 	if ((Items[i].Code).find(y) != std::string::npos) {


			// 	} 
			// 	string codes;
			// 	codes="";
			// 	codes=codes+Items[i].Code+" ";

			// }

			// int a;
			//int *p=&a;
			//a=0;


			string c;
			cout << "Enter 1 to search item code" << endl;
			cout << "Enter 2 to search through item name" << endl;
			cin >> c;
			int b;
			if (valid_number(c)) {
				b = stoi(c);
			}
			else {
				cerr << "Enter valid index" << endl;
				break;
			}

			switch (b) {

			case 1: {
				string y;
				cout << "Enter the item code to search it all parameter  " << endl;
				cin >> y;
				for (int i = 0; i < Items.size(); i++) {
					if ((Items[i].Code).find(y) != std::string::npos)
					{

						cout << "Item number " << i + 1 << ":" << endl;
						cout << "Item Name: " << Items[i].Name << endl;
						cout << "Item Code: " << Items[i].Code << endl;
						cout << "Item Price: " << Items[i].price << endl;
						cout << "******************************************************************************************************************" << endl;

					}
				}
				//cerr<<"Error::No item code found"<<endl;


				break;
			}
			case 2: {
				string y;
				cout << "Enter the item name to search it all parameter  " << endl;
				cin >> y;
				for (int i = 0; i < Items.size(); i++) {
					if ((Items[i].Name).find(y) != std::string::npos)
					{

						cout << "Item number " << i + 1 << ":" << endl;
						cout << "Item Name: " << Items[i].Name << endl;
						cout << "Item Code: " << Items[i].Code << endl;
						cout << "Item Price: " << Items[i].price << endl;
						cout << "******************************************************************************************************************" << endl;

					}
				}
				//cerr<<"Error::No item code found"<<endl;


				break;
			}
				  break;
			}


		}


		}
	}

}




