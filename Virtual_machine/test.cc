# include<bits/stdc++.h>
# include "VM.h"

using namespace std;

int main(){
	VM ass;
	ifstream stream("in");
	
	string comand;
	while(getline(stream, comand)){
		ass.set_instruction(comand);
	}
	
	try{
		ass.run();
	}catch(string erro){
		cout<<erro<<endl;
	}
}
