#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define LEFT(i) ((i)*2+1)
#define RIGHT(i) ((i)*2+2)
#define ROOT(i) (((i)-1)/2)

//versione modificata per RMQ - range minimum query

#include <climits>

struct rmqtree{
	vector<int> v,u;
	int nullvalue = INT_MAX;
	
	void update_node(int i){
		v[i]= min(v[LEFT(i)], v[RIGHT(i)]);
	}
	
	void lazyupdate(int i){
			v[i] += u[i];
			if(i<v.size()/2){
				u[RIGHT(i)] += u[i];
				u[LEFT(i)] += u[i];
			}
			u[i]=0;
	}
	
	rmqtree(vector<int> &source){
		v.resize((1<<(int)(ceil(log2(source.size())+1)))-1, nullvalue);
		u.resize(v.size(),0);
		for(int i=0;i< source.size();i++)
			v[i+v.size()/2]= source[i];
		for(int i=v.size()/2 - 1;i>=0;i--)
			update_node(i);
	}
	
	int a,b;
	int rmq(int i,int l ,int r){
		lazyupdate(i);
		//se intervallo l,r completamente incluso in qa qb
		if(l>=a && r<=b)
			return v[i];
		//se l'intervallo l,r completamente fuori da a,b
		if(r<a || l>b)
			return nullvalue;
		int m = (l+r)/2;
		return min(rmq(LEFT(i),l,m), rmq(RIGHT(i),m+1,r));
	}

	int rangemin(int qa,int qb){
		a=qa;
		b=qb;
		return rmq(0,0,v.size()/2);
	}
	
	void update_up(int i){
		update_node(i);
		if(i!=0)
			update_up(ROOT(i));
	}
	//point update
	void update(int i, int k){
		int x = v.size()/2 + i;
		v[x]= k;
		update_up(ROOT(x));
	}
	int off;
	void range_add(int i,int l,int r){
		lazyupdate(i);
		//se intervallo l,r completamente incluso in qa qb
		if(l>=a && r<=b){
			//aggiorno il nodo, lazyupdate dei figli, return
			int x=off;
			v[i]+=x;
			if(l!=r){
				u[LEFT(i)] += x/2;
				u[RIGHT(i)]+= x/2;
			}
			return;	
		}
		//se l'intervallo l,r completamente fuori da a,b
		if(r<a || l>b){
			return;
		}
		int m = (l+r)/2;
		range_add(LEFT(i),l,m);
		range_add(RIGHT(i),m+1,r);
		update_node(i);
	}
	
	void range_up(int qa,int qb,int k){
		a=qa,b=qb, off=k;
		range_add(0, 0, v.size()/2);
	}
};

int main(){
	vector<int> v{3, 5 , 7, 2, 3, 1};
	sumtree st(v);
	cout<< st.rangesum(0,3)<<' '<< st.rangesum(2,5)<< "\n";
	for(auto i :st.v)
		cout<<i<<" ";
	cout<<endl;

	st.update(2,0);
	st.update(5,99);

	cout<<st.rangesum(0,3)<< ' '<<st.rangesum(2,5)<<"\n";
	for(auto i :st.v)
		cout<<i<<" ";
	cout<<endl;

	return 0;
}