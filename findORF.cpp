//header files
#include <string>
#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <vector>



using namespace std;

//global variables

string sequence;
string rcSequence; //reverse complement sequence


int lines = 0;

int l = 0;
//ask the user for name file
//put all the lines in a long sequence //conctenate lines and get red of spaces
void readFile()
{
	//file name
	string filename;
	cout << "Please enter your file name: " << endl;
	cin >> filename;
	//cout << "you typed: "<< filename << endl;
	ifstream file;
	file.open(filename, ios_base::in);

	//error catcher
	if (!file.is_open())
	{
		cerr << "Error .. could not open";
		exit(1);
	}


	string line;
//	string name;
//	getline(file, name);
	while (getline(file, line))
	{
		if (line.find("<") != 0){sequence += line;}

	}
//	cout << sequence << endl; //it prints out the sequence

	file.close();
}

void getReverseComplement(string seq)
{
	for (int x = 0; x < seq.length(); x++)
	{
		if (seq.at(x) == 'A')
		{
			rcSequence += "T";
		}
		else if (seq.at(x) == 'T')
		{
			rcSequence += "A";
		}
		else if (seq.at(x) == 'C')
		{
			rcSequence += "G";
		}
		else if (seq.at(x) == 'G')
		{
			rcSequence += "C";
		}
	}
	reverse(rcSequence.begin(), rcSequence.end());
}

void findORF(string sequence)
{
	vector<int> starts;
	vector<int> stops;

	//creating windows
	vector<string> windows;
	vector <int> startWind;

	int x = sequence.length() - 2 ;
	for ( int i = 0; i < x; i+=3)
	{
		windows.push_back(sequence.substr(i, 3));
	}

	//iterate over vector elements and look for a start codon, if found, look for a stop codon and then report it

	int start = -1; //place of the start codon

	int codonPosStart = 0; //to know the position of each codon in the sequence //1-indexed

	//looking for ORF...


	//getting all the start codon..
	for (int f = 0; f < windows.size(); f++)
	{
		if (windows[f] == "ATG")
		{
			startWind.push_back(f);
			starts.push_back(codonPosStart +l);
		}
		else if (windows[f] == "GTG")
		{
			startWind.push_back(f);
			starts.push_back(codonPosStart + l);
		}
		else if (windows[f] == "TTG")
		{
			startWind.push_back(f);
			starts.push_back(codonPosStart + l);
		}
		codonPosStart+=3;
	}


	for (int o = 0; o < starts.size(); o++)
	{
		int stop = -1; //place of the stop codon
		int codonPosStop = 0;

		for (int p = startWind[o]; p < windows.size(); p++)
		{
			if (stop < 0) //TODO: if start is found, then start look for a stop. What if the stop is found at the begining? Should we ignore it
			{
				if (windows[p] == "TAA")
				{
					stop = codonPosStop + starts[o];
					if (stop < sequence.length()){stops.push_back(stop);}
				}
				else if (windows[p] == "TAG")
				{
					stop = codonPosStop + starts[o];
					if (stop < sequence.length()){stops.push_back(stop);}
				}
				else if (windows[p] == "TGA")
				{
					stop = codonPosStop + starts[o];
					if (stop < sequence.length()){stops.push_back(stop);}
				}
			}
			codonPosStop +=3 ;
		}
	}

	for (int h = 0; h < starts.size(); h++)
	{
		if (stops[h] > 0 && stops[h] < sequence.length())
		{
			cout << "Start: " << starts[h] << "\t" << " Stop: " << stops[h] <<endl;
			lines ++;
		}
	}
}

void findORF_rc(string sequence)
{
	vector<int> starts;
	vector<int> stops;

	//creating windows
	vector<string> windows;
	vector <int> startWind;

	int x = sequence.length() - 2 ;
	for ( int i = 0; i < x; i+=3)
	{
		windows.push_back(sequence.substr(i, 3));
	}

	//iterate over vector elements and look for a start codon, if found, look for a stop codon and then report it

	int start = -1; //place of the start codon

	int codonPosStart = 0; //to know the position of each codon in the sequence //1-indexed

	//looking for ORF...


	//getting all the start codon..
	for (int f = 0; f < windows.size(); f++)
	{
		if (windows[f] == "ATG")
		{
			startWind.push_back(f);
			starts.push_back(codonPosStart);
		}
		else if (windows[f] == "GTG")
		{
			startWind.push_back(f);
			starts.push_back(codonPosStart);
		}
		else if (windows[f] == "TTG")
		{
			startWind.push_back(f);
			starts.push_back(codonPosStart);
		}
		codonPosStart+=3;
	}


	for (int o = 0; o < starts.size(); o++)
	{
		int stop = -1; //place of the stop codon
		int codonPosStop = 0;

		for (int p = startWind[o]; p < windows.size(); p++)
		{
			if (stop < 0) //TODO: if start is found, then start look for a stop. What if the stop is found at the begining? Should we ignore it
			{
				if (windows[p] == "TAA")
				{
					stop = codonPosStop + starts[o];
					if (stop < sequence.length()){stops.push_back(stop);}
				}
				else if (windows[p] == "TAG")
				{
					stop = codonPosStop + starts[o];
					if (stop < sequence.length()){stops.push_back(stop);}
				}
				else if (windows[p] == "TGA")
				{
					stop = codonPosStop + starts[o];
					if (stop < sequence.length()){stops.push_back(stop);}
				}
			}
			codonPosStop +=3 ;
		}
	}

	for (int k = 0; k < starts.size(); k++)
	{
		starts[k] = sequence.length() - starts[k] + 1;
		stops[k] = sequence.length() - stops[k] + 1;
	}

	for (int h = 0; h < starts.size() ; h++)
	{
		if (stops[h] > 1 && stops[h] <= sequence.length())
		{
			cout << "Start: " << starts[h] << "\t" << " Stop: " << stops[h] <<endl;
			lines ++;
		}
	}
}


int main()
{

	readFile();
	getReverseComplement(sequence);

	cout << "The Open Reading frames for one strand...\n" << endl;

	findORF(sequence);
	l = 1;
	findORF(sequence.substr(l));
	l = 2;
	findORF(sequence.substr(l));

	cout << "\n" << endl;

	cout << "The Open Reading Frames for the opposite strand... \n" << endl;
	l = 0;
	findORF_rc(rcSequence);
	l = 1;
	findORF_rc(rcSequence.substr(l));
	l = 2;
	findORF_rc(rcSequence.substr(l));

	cout << "\n The number of ORFs found:" << lines << "\n" << endl;
//	cout << sequence.length() << endl;
}
