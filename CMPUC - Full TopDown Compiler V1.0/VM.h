#include<bits/stdc++.h>
using namespace std;

class VM{
  # define maxRegs 64
  # define maxMem 64
  # define maxI 1000
  
  # define ERRO1 string("Invalid operation!")
  # define ERRO2 string("Stack empty!")
  # define ERRO3 string("jump id out of the range!")
  # define ERRO4 string("Segmentation fault !")
  # define ERRO5 string("Invalid register !")
  # define ERRO6 string("Valor invalido!")
  
  private :
  
    int mem[maxMem], pc, qtdI;
    string memI[maxI], opCode;
    stack<int> stk;
    stringstream curI;
    unordered_map<string, int> regs;
    
    bool fetch();
    void id();
    void op_ar();
    void op_mem();
    void op_stack();
    void op_jump();
    void op_io();
    void op_move();
    void ex(int typeOp);
    void valid_regs(string reg);
    void valid_adress(string adress);
    int get_type(string x);
    bool isNumber(string x);
    void valid_instruc(string I);
    
  public :
  
    void set_instruction(string I);
    void run();
    VM(); // construtor
    
};

VM::VM(){
  pc = qtdI = 0;
}

bool VM::isNumber(string x){
  for(char c : x){
    if(!isdigit(c)) return 0;
  }
  return 1;
}

int VM::get_type(string x){
  string Sar("ADD | SUB | MUL | DIV | MOD | POT | AND | OR | NOT");
  string Sjump("BEQ | BNE | BLT | BLE | BGT | BGE | JUMP");
  if(Sar.find(x) != string::npos) return 1;
  if(x == "LOAD" || x == "STORE") return 2;
  if(x == "PUSH" || x == "POP") return 3;
  if(Sjump.find(x) != string::npos) return 4;
  if(x == "READ" || x == "WRITE") return 5;
  if(x == "MOVE") return 6;
  return -1;
}

void VM::valid_regs(string reg){
  if(reg.empty() || !isNumber(reg.substr(1)) || reg[0] != 'R') throw ERRO5;
  int x = stoi(reg.substr(1));
  if( x < 0 || x >= maxRegs) throw ERRO5;
}

void VM::valid_adress(string adress){
  if(!isNumber(adress) ||  adress.size() > 10) throw ERRO4;
  int x = stoi(adress);
  if(x < 0 || x >= maxMem) throw ERRO4;
}

// parser
void VM::valid_instruc(string I){
  stringstream flow(I);
  string op, r1, r2 , r3, adress, val;
  flow>>op;
  int type = get_type(op);
  if(type == 1){
		if(op == "NOT"){
			return ;
			flow>>r1;
			valid_regs(r1);
		}
    flow>>r1>>r2>>r3;
    valid_regs(r3), valid_regs(r2), valid_regs(r1);
  }else if(type == 2){
    flow >> r1>>adress;
    valid_adress(adress), valid_regs(r1);
  }else if(type == 3){
    flow>>r1;
    valid_regs(r1);
  }else if(type == 4){
		if(op == "JUMP"){
			flow>>adress;
			valid_adress(adress);
			return;
		}
    flow>>r1>>r2>>adress;
    valid_adress(adress), valid_regs(r2), valid_regs(r1);
  }else if(type == 5){
    flow >> r1;
    valid_regs(r1);
  }else if(type == 6){
    flow>>r1>>val;
    valid_regs(r1);
    if(isNumber(val) == 0) ERRO6;
  }else throw ERRO1;
  
  if(!flow.eof()) throw ERRO1;
}

void VM::set_instruction(string I){
  valid_instruc(I);
  memI[qtdI++] = I;
}

// interpretador
void VM::run(){
  while(fetch()){
    id();
    ex(get_type(opCode));
  }
}

// instruction fetch
bool VM::fetch(){
  if(pc == qtdI) return 0;
  curI.clear();
  curI.str(memI[pc++]);
  return 1;
}
// opCode decodification
void VM::id(){
  curI >> opCode;
}

// executions
void VM::ex(int typeOp){
  switch (typeOp){
    case 1 : op_ar(); break;
    case 2 : op_mem(); break;
    case 3 : op_stack(); break;
    case 4 : op_jump(); break;
    case 5 : op_io(); break;
    case 6 : op_move(); break;
    default: throw ERRO1;
  }
}

// aritmetic operations
void VM::op_ar(){
  string r1, r2, r_dest;
  if(opCode == "NOT"){
		curI>>r1;
		regs[r1] = !regs[r1];
		return;
	}
	
  curI>>r1>>r2>>r_dest;
  if(opCode == "ADD") regs[r_dest] = regs[r1]+regs[r2];
  else if(opCode == "SUB") regs[r_dest] = regs[r1]-regs[r2];
  else if(opCode == "MUL") regs[r_dest] = regs[r1]*regs[r2];
  else if(opCode == "DIV") regs[r_dest] = regs[r1]/regs[r2];
  else if(opCode == "MOD") regs[r_dest] = regs[r1]%regs[r2];
  else if(opCode == "POT") regs[r_dest] = pow(regs[r1],regs[r2]);
  else if(opCode == "AND") regs[r_dest] = regs[r1] && regs[r2];
  else regs[r_dest] =  regs[r1] || regs[r2];
}

// mem operations
void VM::op_mem(){
  string r1, adress;
  curI>>r1>>adress;
  
  if(opCode == "LOAD") {
    regs[r1] = mem[stoi(adress)];
  }
  else mem[stoi(adress)] = regs[r1];
}

// stack operations
void VM::op_stack(){
  string r1;
  curI>>r1;
  if(opCode == "POP") {
    if(stk.empty()) throw ERRO2;
    regs[r1] = stk.top();
    stk.pop();
  }
  else stk.push(regs[r1]);
}

// jump (in|con)ditional operations
void VM::op_jump(){
	string pos, r1, r2;
	if(opCode == "JUMP"){
		curI >> pos;
		pc = min(stoi(pos), qtdI);
	}else{
		curI >> r1 >> r2 >> pos;
		if(opCode == "BEQ"){
			if(regs[r1] == regs[r2]) pc = min(stoi(pos), qtdI);
		}else if(opCode == "BNE"){
			if(regs[r1] != regs[r2]) pc = min(stoi(pos), qtdI);
		}else if(opCode == "BLT"){
			if(regs[r1] < regs[r2])  pc = min(stoi(pos), qtdI);
		}else if(opCode == "BLE"){
			if(regs[r1] <= regs[r2]) pc = min(stoi(pos), qtdI);
		}else if(opCode == "BGT"){
			if(regs[r1] > regs[r2])  pc = min(stoi(pos), qtdI);
		}else if(opCode == "BGE"){
			if(regs[r1] >= regs[r2]) pc = min(stoi(pos), qtdI);
		}else throw ERRO1;
	}
}

// input/ output operations
void VM::op_io(){
  string r1;
  curI>>r1;
  
  if(opCode == "READ"){
    cin>>regs[r1];
  }else{
    cout<<regs[r1]<<endl;
  }
}

void VM::op_move(){
  string r1, val;
  curI>>r1>>val;
  regs[r1] = stoi(val);
}
