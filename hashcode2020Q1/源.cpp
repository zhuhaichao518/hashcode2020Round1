#include <fstream>
#include <iostream>
#include <list> 
#include <vector>
#include <iterator> 
#include <string>
#include <math.h>
#include <map>
#include <algorithm>

using namespace std;

int bookscore[100000], bookowned[100000];
struct library1 {
	int index;
	int booknum;
	int signupdays;
	vector<int> books;
	int scannum;
	int totalbookvalue;
	int score;
	int mytime;
};

struct booktype {
	int bookid;
	bool plantoscan = false;
	int score;
	int ownednum;
	vector<int> ownedlibrary;
};
booktype book[100001];
vector<library1> library;

bool compare2(library1 l1, library1 l2) {
	return l1.score > l2.score;
	return 1;
}

bool comparebook(int b1, int b2) {
	return book[b1].score > book[b2].score;
	return 1;
}

int main() {
	ifstream in;
	ofstream out;
	char* file1[6] = { "a_example.txt","b_read_on.txt","c_incunabula.txt","d_tough_choices.txt", "e_so_many_books.txt","f_libraries_of_the_world.txt" };
	char* file2[6] = { "a_example.txt.out","b_read_on.txt.out","c_incunabula.txt.out","d_tough_choices.txt.out", "e_so_many_books.txt.out","f_libraries_of_the_world.txt.out" };
	//for (int iii = 1; iii < 1; iii++) {
	in.open(file1[4]);
	out.open(file2[4]);
	int bookkinds;
	in >> bookkinds;
	int librarynum;
	in >> librarynum;
	int totaldays;
	in >> totaldays;
	int allbookvalue = 0;
	const int qidongshijiancankao = 100000, sudu = 1000, zongjiazhi = 50;//which is more important?
																		 ////sub1 1000 100000 1

																		 //10000

	for (int i = 0; i < bookkinds; i++) {
		in >> book[i].score;
		book[i].bookid = i;
		allbookvalue += book[i].score;
		book[i].plantoscan = false;
	}
	for (int i = 0; i < librarynum; i++) {
		library1 newlibrary;
		in >> newlibrary.booknum;
		in >> newlibrary.signupdays;
		in >> newlibrary.scannum;
		newlibrary.index = i;
		newlibrary.totalbookvalue = 0;
		library.push_back(newlibrary);
		for (int j = 0; j < library[i].booknum; j++) {
			int nwbook;
			in >> nwbook;
			library[i].totalbookvalue += book[nwbook].score;
			book[nwbook].ownednum++;
			book[i].ownedlibrary.push_back(j);
			library[i].books.push_back(nwbook);
			//socre!!! no consider the rare of books;
			//library[i].score = library[i].totalbookvalue * zongjiazhi + library[i].scannum * sudu + qidongshijiancankao * (totaldays - library[i].signupdays);
			//cout<<"zongjiazhicankao:"<<library[i].totalbookvalue * zongjiazhi<<"sudu:"<< library[i].scannum * sudu <<"zhuceshijian:"<< qidongshijiancankao * (totaldays - library[i].signupdays)<<endl;
		}
		library[i].score = library[i].totalbookvalue * zongjiazhi + library[i].scannum * sudu + qidongshijiancankao * (totaldays - library[i].signupdays);
		//cout << "zongjiazhicankao:" << library[i].totalbookvalue * zongjiazhi << "sudu:" << library[i].scannum * sudu << "zhuceshijian:" << qidongshijiancankao * (totaldays - library[i].signupdays) << endl;

	}
	//sort(library[0], library[librarynum - 1], compare2);
	sort(library.begin(), library.end(), compare2);
	int remaintime = totaldays;
	int time = 0;
	int scanlibnum = 0;

	while (remaintime > 0 && scanlibnum < librarynum) {
		if (remaintime < library[scanlibnum].signupdays) break;
		remaintime -= library[scanlibnum].signupdays;
		time += library[scanlibnum].signupdays;
		library[scanlibnum].mytime = time;
		scanlibnum++;
	}
	out << scanlibnum << endl;


	for (int i = 0; i < scanlibnum; i++) {
		out << library[i].index << ' ' << library[i].booknum << endl;
		//sort(library[i].books[0], library[i].books[library[i].booknum - 1], comparebook);
		sort(library[i].books.begin(), library[i].books.end(), comparebook);
		for (int j = 0; j < library[i].booknum - 1; j++) {
			out << library[i].books[j] << ' ';
			if ((library[i].mytime + j / library[i].scannum) <= totaldays) {
				book[library[i].books[j]].score = 0;
			}
		}
		out << library[i].books[library[i].booknum - 1] << endl;
	}

	in.close();
	out.close();
	//}
	return 0;
}