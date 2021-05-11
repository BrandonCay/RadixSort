#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

//integer radix
void distribute(const vector<int>& v, queue<int> digitQueue[], int power); 
//post:puts digits into respective bins
void collect(queue<int> digitQueue[], vector<int>& v); 
//post:collects the digits into the original bin
void radixSort(vector<int>& v, int d); 
//post:repreats the process until all digits have been done

//string radix
void distribute(const vector<string>& v, queue<string> charQueue[], int charPos); 
//post:puts characters into respective bins
void collect(queue<string> charQueue[], vector<string>& v); 
//post:collects the characters into the original bin
void radixSort(vector<string>& v, int maxSize); 
//post:repreats the process until all characters have been done
									 
template<class T>
void displayVec(vector<T>& v);
//post:displays the contents of the vector
template<class T>
void fillVec(vector<string>& v, T arrList[], int arrSize, int maxSize);
//post: takes a list and fills the vector with the list's values 
void fillIntVec(vector<int>& v, int arrList[], int arrSize);
//post: fills an int vector with values from an int array
void fillIntVec(vector<int>& v, uniform_int_distribution<int> arrList, int arrSize);
//post: fills an int vector with random values from an uniform_int_distribution to a vector

default_random_engine g;//generates values. Used for testing random values
int main() {
	clock_t t;
	const static int arrNum = 10;
	vector<int>v2;
	vector<string>v;
	int maxSize = 6;
	int maxDigits = 4;
	
	//for testing time and space:

	/*
	uniform_int_distribution<int> a(1000,9999);//distribution generation order
	fillIntVec(v2, a, arrNum);
	t = clock();
	radixSort(v2,maxDigits);
	t = clock()-t;
	cout << "Time: " << static_cast<float>(t) / CLOCKS_PER_SEC << endl;
	*/
	
	int arrList[arrNum] = {2692,3879,5339,1126,2281,5267,7945,4067,2409,7198};
	string stringList[arrNum] = { "radix","bubble","insert" ,"select","quick","bucket","shell","heap","merge","count" };

	//fillVec(v2,arrList,arrNum,1);
	fillVec(v, stringList, arrNum, maxSize);
	fillIntVec(v2, arrList, arrNum);
	
	cout << "Before radixSort: " << endl;
	displayVec(v2);
	cout << "After radixSort: " << endl;
	radixSort(v2,maxDigits);
	displayVec(v2);

	cout << "Before radixSort: " << endl;
	displayVec(v);
	cout << "After radixSort: " << endl;
	radixSort(v,maxSize);
	displayVec(v);
	
	
	return 0;
}

template<class T>
void displayVec(vector<T>& v) {
	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << *it << endl;
	}
	cout << endl;
}
template<class T>
void fillVec(vector<string>& v, T arrList[], int arrSize, int maxSize) {
	for (int i = 0; i < arrSize; ++i) {
		string temp = arrList[i];
		temp.resize(maxSize);
		v.push_back(temp);
	}
}

void fillIntVec(vector<int>& v, int arrList[], int arrSize) {
	for (int i = 0; i < arrSize; ++i) {
		int temp = arrList[i];
		v.push_back(temp);
	}
}

void fillIntVec(vector<int>& v, uniform_int_distribution<int> arrList, int arrSize) {
	for (int i = 0; i < arrSize; ++i) {
		int temp = arrList(g);
		v.push_back(temp);
	}
}

//string
void distribute(const vector<string>& v, queue<string> charQueue[], int charPos) {
	for (int i = 0; i < v.size(); ++i) {

		int charNum = int(v[i][charPos]) - 97;

		if (charNum >= 0 && charNum < 26) {
			charQueue[charNum].push(v[i]);
		}
		else if (charNum == -97) {
			charQueue[26].push(v[i]);
		}
	}
}
void collect(queue<string> charQueue[], vector<string>& v) {
	int vPos = 0;
	for (int i = 0; i < 27; ++i) {//iterates through buckets
		while (!charQueue[i].empty()) {
			v[vPos] = charQueue[i].front();
			charQueue[i].pop();
			++vPos;
		}
	}
}


void radixSort(vector<string>& v, int maxSize) {
	queue<string>buckets[27];
	int charPos = maxSize-1;
	for (; charPos >= 0; --charPos) {
		distribute(v, buckets, charPos);
		collect(buckets, v);
	}

}

//int
void distribute(const vector<int>& v, queue<int>digits[], int power) {
	for (int i = 0; i < v.size(); ++i) {
		digits[(v[i] / power) % 10].push(v[i]);
	}
}

void collect(vector<int>& v, queue<int>digits[]) {
	int i = 0, digit;
	for (digit = 0; digit < 10; ++digit) {
		while (!digits[digit].empty()) {
			v[i] = digits[digit].front();
			digits[digit].pop();
			++i;
		}
	}
}

void radixSort(vector<int>& v, int d) {
	queue<int>digits[10];
	int power = 1;

	for (int i = 0; i < d; ++i) {
		distribute(v, digits, power);
		collect(v, digits);
		power *= 10;
	}
}
