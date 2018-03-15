#include<bits/stdc++.h>		//apriori algorithm and predicting most valuable item
using namespace std;	//running on minimum support confidence of 0.023% (i.e. number of transactions per item - 2 as an increase of 1 leads to clearing of all values during self join in the first iteration) due to available data
long long int no_of_transactions= 8654;  //running on confidence of 90%
long long int largest_tid= 17671;   //size of itemsets is taken as 2 because mean transaction size is of 1.22 items per transaction. Hence premature ending of loop to find possible itemset(s).
long long int largest_item_id= 466614;
vector<long long int> transaction_list[17671],item_id_list[466614];	
int supp=2;	
struct node
{
	vector<long long int> item[2];
};
void union1(vector<long long int> v1,vector<long long int> v2 ,vector<long long int> &result)
{
	for (int i=0;i<v1.size();i++)
	{
		result.push_back(v1[i]);
	}			
	for (int i=0;i<v2.size();i++)
	{
		bool a=true;
		for (int j=0;j<v1.size();j++)
		{
			if (v2[i]==v1[j])
			{
				a=false;
			}
			break;
		}
		if (a==true)
			{
				result.push_back(v2[i]);
			}
	}
};
void intersection1(vector<long long int> v1,vector<long long int> v2 ,vector<long long int> &result)
{
	for (int i=0;i<v2.size();i++)
	{
		for (int j=0;j<v1.size();j++)	
		{
			if (v1[j]==v2[i])
			result.push_back(v2[i]);
			break;
		}
	}	
};
vector<struct node> backup;
void add_new(vector<struct node> &v,int c,int start)
{
	int h=v.size();
	for (int i=start;i<h-1;i++)
	{
		for (int j=i+1;j<h;j++)
		{
			//cout<<"i = "<<i<<" j = "<<j<<endl;
			//cout<<"before intersection"<<endl;
			struct node m;
			m.item[0].push_back(-1);
			m.item[1].push_back(-1);
			//cout<<"m ban gaya"<<endl;
			struct node result;
			sort(v[i].item[0].begin(),v[i].item[0].end());
			sort(v[j].item[0].begin(),v[j].item[0].end());
			sort(v[i].item[1].begin(),v[i].item[1].end());
			sort(v[j].item[1].begin(),v[j].item[1].end());
	//vector<long long int>::iterator it,it1;
	//cout<<"v[i] and v[j] ka sorting done"<<endl;
			union1(v[i].item[0],v[j].item[0],result.item[0]);
			//cout<<"union done"<<endl;
	//result.item[0].resize(it-result.item[0].begin());
			if(result.item[0].size()!=v[i].item[0].size()+1)
				{
					result=m;
					break;
				}
			intersection1(v[i].item[1], v[j].item[1], result.item[1]);
	//cout<<"intersection done"<<endl;
	//result.tran.resize(it1-result.tran.begin());
	if (result.item[1].size()<c)
	{
		result=m;
		break;
	}
			//struct node n=intersect(v[i],v[j],c);
			//cout<<"after intersection"<<endl;
			if (!(result.item[0][0]==-1))
			{
				v.push_back(result);	
			}	
		}	
	}	
	//cout<<"v.size() = "<<v.size()<<endl;
	//return &v;
};
int main()
{
	long long int s=0;
	vector<int> item_track; 
	int max_transactions=0,counter=0;
	for (int i=0;i<no_of_transactions;i++)
	{
		int vid,item_id,tr_id;
		string s;
		cin>>vid>>s>>item_id>>tr_id;
		transaction_list[tr_id].push_back(item_id);
		item_id_list[item_id].push_back(tr_id);
		if (item_id_list[item_id].size()>max_transactions)
		{
			max_transactions=item_id_list[item_id].size();
		}
		if (item_id_list[item_id].size()>=supp)			//2 - 2908; 5 - 578; 10 - 201; 15 - 105(about); 25 - 48
		{
			counter=counter+1;
			item_track.push_back(item_id);
		}
	}	
	long long int s1=0;
	for (int i=0;i<17671;i++)
	{
		if (transaction_list[i].size()>0)
		{
			s1=s1+1;
			s=s+transaction_list[i].size();
		}
	}
	cout<<"Average - "<<(double)s/(double)s1;	
	cout<<"max_transactions = "<<max_transactions<<endl;
	cout<<"counter = "<<counter<<endl;
	vector<struct node> v;   
	for (long long int i=0;i<item_track.size();i++)
	{
			struct node n;			
			n.item[0].push_back(i);			
			for (long long int j=0;j<item_id_list[item_track[i]].size();j++)
			{
				n.item[1].push_back(item_id_list[item_track[i]][j]);	
			}		
			v.push_back(n);
	}		
	bool a=true;	
	int f=0;
	for (int i=0;i<1;i++)
	{
		//cout<<"f = "<<f<<endl;
		long long int size1=v.size();	
		add_new(v,supp,0);		
		v.erase(v.begin(),v.begin()+size1);		
		cout<<v.size()<<endl;
		if (v.size()==1 || v.size()==0)
		{			
			a=false;
		}		
		//f=f+1;				
	}	
	vector<int> result1[2];
	double m1=1.0;
	for (int i=0;i<v.size();i++)
	{
	cout<<"Item set members - "<<endl;
	cout<<item_track[v[i].item[0][0]]<<" ";	
	cout<<item_track[v[i].item[0][1]];
	cout<<endl;
	cout<<"Applying confidence level - "<<endl;
	double n=2.0;
	double d=(double)item_id_list[item_track[v[i].item[0][0]]].size();
	d=n/d;
	if (d<m1)
	{
		m1=d;
	}
	cout<<"First time d value = "<<d<<endl;
	if (d>=0.9)
	{
		result1[0].push_back(item_track[v[i].item[0][0]]);		
		result1[1].push_back(item_track[v[i].item[0][1]]);		
	//cout<<"Item accepted at left side for the given dataset"<<endl;
	}
	cout<<"Second time d value = "<<d<<endl;
	d=(double)item_id_list[item_track[v[i].item[0][1]]].size();
	d=n/d;
	if (d<m1)
	{
		m1=d;
	}
	if (d>=0.9)
	{
		result1[0].push_back(item_track[v[i].item[0][1]]);		
		result1[1].push_back(item_track[v[i].item[0][0]]);		
	}
	}		
	cout<<"Accepted rules - "<<endl;
	for (int i=0;i<result1[0].size();i++)
	{		
		cout<<result1[0][i]<<"->"<<result1[1][i]<<endl;
		cout<<"----------------------------------------------------"<<endl;
	}
	cout<<"m1 (min. value of d) = "<<m1<<endl;
	cout<<"Size of accepted rules - "<<result1[0].size()<<endl;
    return 0;
}

