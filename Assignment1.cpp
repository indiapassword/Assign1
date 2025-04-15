// Write a program to siumulate commands like cp, grep with the usage of fork, exe, wait, getpid, exit.

#include<iostream>
#include<fstream>
#include<vector>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

void CP(string source, string destination)
{
	pid_t pid = fork();

	if(pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if(pid == 0)
	{
		cout<<"Child p	rocess id : "<<getpid()<<endl;
		cout<<"Parent process id : "<<getppid()<<endl;
	
		string s = "";
		ifstream f1;
		f1.open(source);
		ofstream f2;
		f2.open(destination);
		while(!f1.eof())
		{
			getline(f1,s);
			f2<<s<<endl;
		}
		f1.close();
		f2.close();	
	}
}

void GREP(string arg, string fileName)
{
	pid_t pid = fork();

	if(pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if(pid == 0)
	{
		cout<<"Child process id : "<<getpid()<<endl;
		cout<<"Parent process id : "<<getppid()<<endl;

		ifstream f1;
		string line = "";
		int count = 0;

		// Remove the inverted commas
		string name = "";
		for(int i = 1; i < arg.length()-1 ; i++)
		{
			name = name + arg[i];
		}

		f1.open(fileName);
		while (!f1.eof())
		{
			getline(f1, line);
    	    	if (line.find(name) != std::string::npos)		// find function --> returns the index of first character of substring and
    	    	{												// and if substring is absent then returns the value as string::npos
    	        		count++;
    	    	}
    		}
		f1.close();
		cout<<count<<endl;
	}
}

int main()
{

	

	string s = "";
	getline(cin, s);

	// put all the individual words from a line into a vector
	vector <string> v;
	int j = 0;
	string word = "";
	for(int i = 0 ; i<s.length() ; i++)
	{
		if(s[i] != ' ')
		{
			word = word + s[i];
			continue;
		}
		v.push_back(word);
		word = "";
	}
	v.push_back(word);

	// CP command function call
	if(v.size() == 3 && v[0] == "cp" && v[1] != v[2])
	{
		CP(v[1] , v[2]);
	}

	// GREP command function call
	if(v.size() == 4 && v[0] == "grep" && v[1] == "-c" && v[2][0] == '"' && v[2][v[2].length()-1] == '"')
	{
		GREP(v[2], v[3]);
	}

	return 0;
}
