//payin chap (1,1) 
// bala rast (6,6)
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <string.h>
#include <iterator>
# define cost 1
using namespace std;
class Percept{//checked
	public:
	Percept(int x, int y, int red,int blue){
		x1 = x;
		y2 = y;
		red1 = red;
		blue1=blue;
	}
	int getx(){
		return x1;
	}
	int gety(){
		return y2;
	}
	int getr(){
		return red1;
	}
	int getb(){
			return blue1;
		}
	void setx(int xx){
		x1=xx;
	}
	void sety(int yy){
		y2=yy;
	}
	void setb(int bb){
		blue1=bb;
	}
	void setr(int rr){
		red1=rr;
	}
	void print_percept(){
		cout<<"("<<x1<<","<<y2<<","<<red1<<","<<blue1<<")";
	}
	

	public:   
	int x1=0;
	int y2=0 ;
	int red1=0 ;
	int blue1=0;
};
class Point{//checked
	public:
	Point(int x, int y){
		x1 = x;
		y2 = y;
	}
	int getx(){
		return x1;
	}
	int gety(){
		return y2;
	}
	void print(){
		cout<<"("<<x1<<","<<y2<<")";
	}
	public:    
	int x1 ;
	int y2 ;
};

class s_a{//checked
public:
	s_a(int x,int y,int red, int blue, string a){
		xx=x;
		yy=y;
		rr=red;
		bb=blue;
		a1 = a;
	}
	Percept get_s(){
		return Percept(xx,yy,rr,bb);
	}
	string get_a(){
		return a1;
	}
	public:   
	int xx;
	int yy;
	int rr;
	int bb; 
	string a1 ;

};
//global variables
//n=row   m=coloumn  k=number of blue or red mushrooms 
int n,m,xstart,ystart,k;
vector<Point> redMushrooms;
vector<Point> blueMushrooms;
vector<Point> barriers;
string mario_map[100][100];
map<Percept,int> H;
map<s_a,Percept> result;



//reads file
void read_file(){//checked
	fstream myfile; 
	string filename; 
	// filename of the file 
	filename = "mario.txt"; 
	// opening file 
	myfile.open(filename.c_str()); 
	// extracting words from the file 
	int xr,yr,xb,yb,xm,ym;
	myfile>>n>>m>>xstart>>ystart>>k;
	//the red mushrooms
	for(int i=0; i<k; i++){
		myfile>>xr>>yr;
		Point tempPoint(xr,yr);
		redMushrooms.push_back(tempPoint);
	}
	for(int i=0; i<k; i++){
			myfile>>xb>>yb;
			Point tmpPoint(xb,yb);
			blueMushrooms.push_back(tmpPoint);
		}
	while (!myfile.eof()) {
		myfile>>xm>>ym;
		Point tmpoPoint(xm,ym);
		barriers.push_back(tmpoPoint);
	}
	barriers.pop_back();//x e akhar eof hesab nemishe
}
//map
/*
	(1,6).....(6,6)

	(1,1).....(6,1)
 */
void make_map(){//ched but missing mario
	int x,y;
	for (int i=0;i<redMushrooms.size();i++) {
		x=redMushrooms.at(i).getx();
		y=redMushrooms.at(i).gety();
		mario_map[n-y][x-1]="red";
	}
	for (int i=0;i<blueMushrooms.size();i++) {
		x=blueMushrooms.at(i).getx();
		y=blueMushrooms.at(i).gety();
		mario_map[n-y][x-1]="blue";
	}
	for (int i=0;i<barriers.size();i++) {
		x=barriers.at(i).getx();
		y=barriers.at(i).gety();
		mario_map[n-y][x-1]="barrier";
	}
	for (int i=0;i<n;i++) {
		for(int j=0;j<m;j++){
			if(mario_map[i][j]!="red" && mario_map[i][j] !="blue" && mario_map[i][j]!="barrier" && mario_map[i][j]!="mario")
				mario_map[i][j]="ok";
		}
	}
	mario_map[n-ystart][xstart-1]="mario";

}
void print_map(){//checked
	for (int i=0;i<n;i++) {
		cout<<'\n';
		for(int j=0;j<m;j++){
			cout<<mario_map[i][j]<<"|";
		}
	}
}

//defining heuristic
int h(Percept p , int heuristicType){
	int heuristic;
	if (heuristicType ==1) { //h1
		int heuristic1;
		heuristic1=k*2-p.getb()-p.getr();
		 heuristic=heuristic1;
	}
	else if(heuristicType==2){ //h2
		int heuristic2;
		int dist[2];
		dist[0]=10000;
		for (int i=0;i<n;i++) {
			for (int j=0;j<m;j++) {
				if(mario_map[i][j].compare("red")==0 || mario_map[i][j].compare("blue")==0){
					dist[1]=abs(i-p.getx())+abs(j-p.gety());
					if(dist[1]<dist[0]){
						dist[0]=dist[1];
					}
				}
			}
		}
		heuristic2=dist[0];
		heuristic=heuristic2;
	}
	else if(heuristicType==3){ //h3
		vector<int> xs;
		vector<int> ys;
		int heuristic3;
		for (int i=0;i<n;i++) {
			for (int j=0;j<m;j++) {
				if(mario_map[i][j].compare("red")==0|| mario_map[i][j].compare("blue")==0){
					xs.push_back(j+1);
					ys.push_back(n-i);
				}
			}
		}
		int distance[2];
		distance[0]=0;
		for (int i=0;i<xs.size();i++) {
			for(int j=0;j<i;j++){
				distance[1]= abs(xs[i]-xs[j])+abs(ys[i]-ys[j]);
				if(distance[1]>distance[0]){
				distance[0]=distance[1];
				}
			}
		}
		heuristic3=distance[0];
		heuristic=heuristic3;
	}
	return heuristic;
}
int updateH(Percept p,int heuristicType){
	int min1,min2,min3,min4;
	s_a p1(p.getx(),p.gety(),p.getr(),p.getb(),"up");
	s_a p2(p.getx(),p.gety(),p.getr(),p.getb(),"down");
	s_a p3(p.getx(),p.gety(),p.getr(),p.getb(),"right");
	s_a p4(p.getx(),p.gety(),p.getr(),p.getb(),"left");
	
	map<s_a, Percept>::iterator it1;
	//iterator<s_a, Percept> it1;
	it1 = result.find(p1); 	
	if(it1 != result.end()){ // "Key-value pair present in map"
		min1=H.at(result.at(p1))+cost;

		//break
	}
	else {
		min1=h(p,heuristicType);
	}
	
	map<s_a, Percept>::iterator it2;
	//iterator<s_a, Percept> it2;
	it2 = result.find(p2); 	
	if(it2 != result.end()){ // "Key-value pair present in map"
		min2=H.at(result.at(p2))+cost;
		//break;
	}
	else {
		min2=h(p,heuristicType);
	}
	//iterator<s_a, Percept> it3;
	map<s_a, Percept>::iterator it3;
	it3 = result.find(p3); 	
	if(it3 != result.end()){ // "Key-value pair present in map"
		min3=H.at(result.at(p3))+cost;
		//break;
	}
	else {
		min3=h(p,heuristicType);
	}
	//iterator<s_a, Percept> it4;
	map<s_a, Percept>::iterator it4;
	it4 = result.find(p4); 	
	if(it4 != result.end()){ // "Key-value pair present in map"
		min4=H.at(result.at(p4))+cost;
		//break;
	}
	else {
		min4=h(p,heuristicType);
	}

	return min( min(min1,min2) , min(min3, min4) );
}

string find_lowest_cost_action(Percept p, int heuristicType){
	int min1,min2,min3,min4;
	s_a p1(p.getx(),p.gety(),p.getr(),p.getb(),"up");
	s_a p2(p.getx(),p.gety(),p.getr(),p.getb(),"down");
	s_a p3(p.getx(),p.gety(),p.getr(),p.getb(),"right");
	s_a p4(p.getx(),p.gety(),p.getr(),p.getb(),"left");
	
	//iterator<s_a, Percept> it1;
	map<s_a, Percept>::iterator it1;
	it1 = result.find(p1); 	
	if(it1 != result.end()){ // "Key-value pair present in map"
		min1=H.at(result.at(p1))+cost;
		//break;
	}
	else {
		min1=h(p,heuristicType);
	}
	
	//iterator<s_a, Percept> it2;
	map<s_a, Percept>::iterator it2;
	it2 = result.find(p2); 	
	if(it2 != result.end()){ // "Key-value pair present in map"
		min2=H.at(result.at(p2))+cost;
		//break;
	}
	else {
		min2=h(p,heuristicType);
	}
	
	//iterator<s_a, Percept> it3;
	map<s_a, Percept>::iterator it3;
	it3 = result.find(p3); 	
	if(it3 != result.end()){ // "Key-value pair present in map"
		min3=H.at(result.at(p3))+cost;
		//break;
	}
	else {
		min3=h(p,heuristicType);
	}
	
	//iterator<s_a, Percept> it4;
	map<s_a, Percept>::iterator it4;
	it4 = result.find(p4); 	
	if(it4 != result.end()){ // "Key-value pair present in map"
		min4=H.at(result.at(p4))+cost;
		//break;
	}
	else {
		min4=h(p,heuristicType);
	}
	int answer;
	string minimum;
	answer=min( min(min1,min2) , min(min3, min4) );
	if(answer==min1){
		minimum="up";
	}
	else if(answer == min2){
		minimum="down";
	}
	else if(answer == min3){
		minimum="right";
	}
	else if(answer == min4){
		minimum="left";
	}
	return minimum;
}
	


string find_action(Percept oldState,Percept newState, string action,int heuristicType){
	string a;
	string newAction;
	if(newState.getr()>1 && newState.getb()>1){
		a="finish";
	}
	else{
		map<Percept, int>::iterator it10;
		it10 = H.find(newState); 	
		if(it10 == H.end()){ // "Key-value pair not present in map"
			H.insert({newState,h(newState,heuristicType)});
			cout<<"H[("<<newState.getx()<<","<<newState.gety()<<","<<newState.getr()<<","<<newState.getb()<<") initialized to: "<<h(newState,heuristicType);
		}
		if(newState.getx() != xstart && newState.gety() != ystart && newState.getr() !=0 && newState.getb() != 0){ // if s isn't null
			s_a tmp(oldState.getx(),oldState.gety(),oldState.getr(),oldState.getb(),action);
			result.insert({tmp,newState});
			///update H[s]
			H.erase(oldState);
			H.insert({oldState,updateH(oldState,heuristicType)});
			cout<<"H[("<<oldState.getx()<<","<<oldState.gety()<<","<<oldState.getr()<<","<<oldState.getb()<<") is: "<<updateH(oldState,heuristicType);
		}
		newAction=find_lowest_cost_action(newState, heuristicType);
		oldState.setx(newState.getx()); //this is the new old set s<-s'
		oldState.sety(newState.gety());
		oldState.setb(newState.getb());
		oldState.setr(newState.getr());
		//might need to return oldstate	 problem	 
	}
	return newAction;
}
Percept find_action2(Percept oldState,Percept newState, string action,int heuristicType){ //returns s
	string a;
	string newAction;
	if(newState.getr()>1 && newState.getb()>1){
		a="finish";
	}
	else{
		map<Percept, int>::iterator it;
		it = H.find(newState); 	
		if(it == H.end()){ // "Key-value pair not present in map"
			H.insert({newState,h(newState,heuristicType)});
			cout<<"H[("<<newState.getx()<<","<<newState.gety()<<","<<newState.getr()<<","<<newState.getb()<<") initialized to: "<<h(newState,heuristicType);
		}
		if(newState.getx() != xstart && newState.gety() != ystart && newState.getr() !=0 && newState.getb() != 0){ // if s isn't null
			s_a tmp(oldState.getx(),oldState.gety(),oldState.getr(),oldState.getb(),action);
			result.insert({tmp,newState});
			///update H[s]
			H.erase(oldState);
			H.insert({oldState,updateH(oldState,heuristicType)});
			cout<<"H[("<<oldState.getx()<<","<<oldState.gety()<<","<<oldState.getr()<<","<<oldState.getb()<<") is: "<<updateH(oldState,heuristicType);
		}
		newAction=find_lowest_cost_action(newState, heuristicType);
		oldState.setx(newState.getx()); //this is the new old set s<-s'
		oldState.sety(newState.gety());
		oldState.setb(newState.getb());
		oldState.setr(newState.getr());
		//might need to return oldstate	 problem	 
	}
	return oldState;
}

Percept find_new_state(Percept oldState,string action){
	Percept newState(0,0,0,0);
	if(action=="up"){
		if(oldState.getx()==0){//marz
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else if(mario_map[oldState.getx()-1][oldState.gety()].compare("barrier")==0){//bala mane
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else{//can move
			mario_map[oldState.getx()][oldState.gety()]="ok";
			newState.sety(oldState.gety());
			newState.setx(oldState.getx()-1);
			if(mario_map[newState.getx()][newState.gety()].compare("red")==0){//there is a red mushroom in new state &mario eats it
				newState.setr(oldState.getr()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setb(oldState.getb());
			}
			else if(mario_map[newState.getx()][newState.gety()].compare("blue")==0){//there is a blue mushrrom in new state & mario eats it
				newState.setb(oldState.getb()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setr(oldState.getr());
			}
			else{//no mushrooms just a simple move upward
				newState.setb(oldState.getb());
				newState.setr(oldState.getr());
				mario_map[newState.getx()][newState.gety()]="mario";
			}
		}
	}
	else if(action=="down"){
		if(oldState.getx()==n-1){//marz
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else if(mario_map[oldState.getx()+1][oldState.gety()].compare("barrier")==0){//payin mane
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else{//can move
			mario_map[oldState.getx()][oldState.gety()]="ok";
			newState.sety(oldState.gety());
			newState.setx(oldState.getx()+1);
			if(mario_map[newState.getx()][newState.gety()].compare("red")==0){//there is a red mushroom in new state &mario eats it
				newState.setr(oldState.getr()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setb(oldState.getb());
			}
			else if(mario_map[newState.getx()][newState.gety()].compare("blue")==0){//there is a blue mushrrom in new state & mario eats it
				newState.setb(oldState.getb()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setr(oldState.getr());
			}
			else{//no mushrooms just a simple move downward
				newState.setb(oldState.getb());
				newState.setr(oldState.getr());
				mario_map[newState.getx()][newState.gety()]="mario";
			}
		}
	}
	else if(action=="right"){
		if(oldState.gety()== m-1){//marz
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else if(mario_map[oldState.getx()][oldState.gety()+1].compare("barrier")==0){//rast mane
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else{//can move
			mario_map[oldState.getx()][oldState.gety()]="ok";
			newState.sety(oldState.gety()+1);
			newState.setx(oldState.getx());
			if(mario_map[newState.getx()][newState.gety()].compare("red")==0){//there is a red mushroom in new state &mario eats it
				newState.setr(oldState.getr()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setb(oldState.getb());
			}
			else if(mario_map[newState.getx()][newState.gety()].compare("blue")==0){//there is a blue mushrrom in new state & mario eats it
				newState.setb(oldState.getb()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setr(oldState.getr());
			}
			else{//no mushrooms just a simple move downward
				newState.setb(oldState.getb());
				newState.setr(oldState.getr());
				mario_map[newState.getx()][newState.gety()]="mario";
			}
		}
		
	}
	else if(action=="left"){
		if(oldState.gety()== 0){//marz
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else if(mario_map[oldState.getx()][oldState.gety()-1].compare("barrier")==0){//chap mane
			newState.sety(oldState.gety());
			newState.setx(oldState.getx());
			newState.setr(oldState.getr());
			newState.setb(oldState.getb());
		}
		else{//can move
			mario_map[oldState.getx()][oldState.gety()]="ok";
			newState.sety(oldState.gety()-1);
			newState.setx(oldState.getx());
			if(mario_map[newState.getx()][newState.gety()].compare("red")==0){//there is a red mushroom in new state &mario eats it
				newState.setr(oldState.getr()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setb(oldState.getb());
			}
			else if(mario_map[newState.getx()][newState.gety()].compare("blue")==0){//there is a blue mushrrom in new state & mario eats it
				newState.setb(oldState.getb()+1);
				mario_map[newState.getx()][newState.gety()]="mario";
				newState.setr(oldState.getr());
			}
			else{//no mushrooms just a simple move downward
				newState.setb(oldState.getb());
				newState.setr(oldState.getr());
				mario_map[newState.getx()][newState.gety()]="mario";
			}
		}
	}
	else if(action =="finish"){
		newState.sety(oldState.gety());
		newState.setx(oldState.getx());
		newState.setr(oldState.getr());
		newState.setb(oldState.getb());
	}
	
	return newState;
}
	
void lrta_star(Percept p,int heuristicType){

	Percept oldState(0,0,0,0);
	string action;
	if(p.getx()==xstart && p.gety()==ystart && p.getb()==0 && p.getr()==0){ //start
		oldState.setx(NULL);
		oldState.sety(NULL);
		oldState.setr(NULL);
		oldState.setb(NULL);
		action = "";
	} 
	Percept newState(p.getx(),p.gety(),p.getr(),p.getb());
	//nextin
	int stage=0;
	while (action != "finish") {
		action=find_action(oldState, newState, action, heuristicType);
		oldState=find_action2(oldState, newState, action, heuristicType);
		newState=find_new_state(oldState, action);
		stage++;
	}
	cout<<"finished in "<<stage<<" stages";
}
	
int main(int argc, char *argv[]) {
	read_file();
	make_map();
	//print_map();
	//n-y x-1
	cout<<"-----------"<<endl;
	int heuristicType;
	cout<<"enter heuristic type (1,2 or 3): ";
	cin>>heuristicType;
	Percept start(xstart,ystart,0,0);
	lrta_star(start,heuristicType);	
}