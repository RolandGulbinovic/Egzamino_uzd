#include <iostream>
#include <iomanip>
#include <set>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;
struct Kiekis{
	int kiek = 1; 

};
int main() {
	ifstream myFile;
	string a;

	set<string> Ats;

	map<string, pair<Kiekis, int>> myMap; // laiko kiekius zodziams > 1
	map<string, vector<int>> cf; // cross reference

	int k = 0;

	ofstream endFile;
	endFile.open("resultatas.txt");


	myFile.open("tekstas.txt");
	if (myFile.is_open()) {
		while (getline(myFile, a)) {
			k++;
			for (int i = 0, len = a.size(); i < len; i++) {

				if (a[i] == ',' || a[i] == '.' || a[i] == '!' || a[i] == '?') // palieka tik zodzius (be "." ,"!"...)
				{
					a.erase(i--, 1);
					len = a.size();
				}
			}
			istringstream ss(a);
			string word;

			while (ss >> word) // skaitomas kiekvienas zodis is eilutes atskirai
			{

				if (Ats.insert(word).second == false) {
					myMap[word].first.kiek++;
					cf[word].push_back(k);
				}

			}
		}
		//isvedimas
		endFile << "Kiek kartu pasikartoja zodziai: " << endl;
		for (auto it = myMap.cbegin(); it != myMap.cend(); ++it)
		{
			endFile << it->first << " - " << it->second.first.kiek << "\n";
		}
		endFile << endl;

		endFile << "Pasikartojimo eilutes: " << endl;
		for (auto it = cf.cbegin(); it != cf.cend(); ++it)
		{
			endFile << it->first << setw(5) << " ----> ";
			for (auto tt : it->second) {
				endFile << tt << ", ";
			}
			endFile << endl;
		}
		endFile << endl;
	}
	else {
		cout << "Failas nerastastas(Kartojimui)" << endl;
	}
	//URL
	ifstream myFileURL;
	myFileURL.open("tekstas2.txt");
	if (myFileURL.is_open()) {
		while (getline(myFileURL, a)) {
			istringstream ss(a);
			string word;

			endFile << "URL'ai tekste: " << endl;

			while (ss >> word)
			{
				if (word.find('www.') != string::npos || word.find("https://") != string::npos) { // randa zodzius kurie turi "www." arba "https://"

					if (word.back() == '.' || word.back() == ',')
						word.pop_back();
					endFile << word << endl;
				}
			}

		}
	}
	else {
		cout << "Failas nerastas(URL)" << endl;
	}
	system("pause");
	return 0;
	
}

	
