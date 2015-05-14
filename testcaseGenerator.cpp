#include <iostream>
#include <cstdlib>
#include <fstream>
#include <set>
#include <random>

using namespace std;

void usage(){

	cout<<"type ./bin/generator n m [inserts, deletes, both]"<<endl;

}

int main(int argc, const char* argv[]){

	if(argc != 4){
		usage();
		return 1;
	}
	
	string opt = argv[3];
	if(opt != "inserts" && opt!="deletes" && opt!="both"){
		usage();
		return 1;
	}
	
	int n = atoi(argv[1]);
	size_t m = atoi(argv[2]);
	ofstream fout;
	string fname = "input/changeFile"+to_string(n)+".txt";
	fout.open(fname,ios_base::out);
	
	fout<<"init("<<n<<")"<<endl;

	static std::mt19937 s(2134);
	static std::uniform_int_distribution<int> dist(0, n-1);

	set< pair<int, int> > mySet;
	if(opt == "inserts"){
		
		while(mySet.size()!= m){
			pair<int,int> tmp;
			tmp.first = dist(s);
			tmp.second = dist(s);
			mySet.insert(tmp);
		}
		
		std::set< pair<int,int> >::iterator it;
		for (it = mySet.begin(); it != mySet.end(); ++it)
		{
			fout<<"insert("<<(*it).first<<","<<(*it).second<<")"<<endl;
			fout<<"transitive closure?"<<endl;
		}
		
	}
	
	if(opt == "deletes"){
		
		while(mySet.size()!=m){
			pair<int,int> tmp;
			tmp.first = dist(s);
			tmp.second = dist(s);
			mySet.insert(tmp);
		}
		
		std::set< pair<int,int> >::iterator it;
		for (it = mySet.begin(); it != mySet.end(); ++it)
		{
			fout<<"delete("<<(*it).first<<","<<(*it).second<<")"<<endl;
			fout<<"transitive closure?"<<endl;
		}
		
	}
	
	else{
		
		/*
		static std::mt19937 s2(2134);
		static std::uniform_int_distribution<int> dist2(1,10);
		pairs<int,int> insertions;
		for(i=0;i<n;i++){
			int next = dist2(s2);
			if(next <= 7){
				insertions.first = dist(s);
				insertions.second = dist(s);
				mySet.insert(insertions);
			}
			else{
			
				
			
			}
			
			
		}
		*/
		
		
		
	}
	
	fout.close();


	return 0;
}