#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
	std::unordered_map<std::string, std::string> myhashmap{
		//unordered_map is unordered unsurprisingly
		{"A","1"},
		{"B","2"}
	};
	for (auto& iter : myhashmap) {
		//iter.first is the key
		//iter.second is the value
		std::cout << "Key:[" << iter.first << "] Value:[" << iter.second << "]\n";
	}
	myhashmap["C"] = "3";
	myhashmap["D"] = "4";

	// Output values by key
	std::cout << "The value of C:[" << myhashmap["C"] << "]\n";
	std::cout << "Value of a non existing key:[" << myhashmap["Not IN map"] << "]\n";
}
