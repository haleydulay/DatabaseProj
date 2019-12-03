/*
-Algo1 S-Phase-
Input:
R, a list of records sorted in increasing temporal order.
0s, a threshold to make merge decision
Output:
C, the clustering of records in R
Sc, the set of cluster signatures corresponding to C, each cluster in C has a signature in Sc.
-Algo2 E-Phase-
Input:
C, the clustering result of the S-phase.
Sc, the set of cluster signatures associated with C.
0E, a threshold to determine whether to merge two records.
Output:
D, the final clustering result
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstring>
#include <algorithm>
#define DBLPWW 738
#define DBLP100K 103059

using namespace std;

int placement;
int maxval = 0;
int dval = 0;
int location;
int counter = 0;
int dcount = 0;

double record_similarity(vector<string> c, vector<string> d, int j)
{
int checker = 0;
double result = 0;
        for(int a=0; a<c.size(); a++)		// looping through record's attributes
        {
                for(int b=0; b<d.size(); b++)	// looping through signature's record's attributes
                {
                        if(c[a]==d[b])
			{
                                result += 1;
				checker += 1;
			}
                }
		if(checker>maxval)
		{
			maxval = checker;
			placement = j;
		}
        }
	checker = 0;

        return result / (c.size()+d.size());
}

double cluster_similarity(vector<string> r, vector<string> r2, int j)
{
double result = 0;
result += record_similarity(r,r2,j);

	return result;
}

double dynamic_attribute(vector<string> r, vector<string> r2, int j)
{
int know = 0;
double result = 0;
	for(int a=0; a<r.size(); a++)
	{
		for(int b=0; b<r2.size(); b++)
		{
			if(r[a]==r2[b])
			{
				result += 1;
				know += 1;			
			}	
		}
		if(know>dval)
		{
		dval = know;
		location = j;
		}
	}
	know = 0;

	return result / (r.size()+r2.size());
}

double dynamic_similarity(vector<string> r, vector<string> r2, int j)
{
double result = 0;
result += dynamic_attribute(r,r2,j);

	return result;
}

int main()
{
double F1_Score = 0;
double Precision = 0;
double Recall = 0;
int setting = 0;
int choice;
int identifier = 0;
double threshold = 0.2;
double d_threshold = 0.05;
ifstream file;
int index = 0;
clock_t beg = 0;
clock_t end = 0;
unsigned long long int elapsedtime = 0;     // might be a double
int type;
string line;
string experiment;
string t1 = "Matching-Accuracy";
string t2 = "Run-Time";
vector<string> Cmax;
vector<string> Scmax;
double storage = 0;
vector<vector<string> > C(DBLPWW);
vector<vector<string> > Sc(DBLPWW);
vector<vector<string> > D(DBLPWW);
vector<vector<string> > Dc(DBLPWW);


cout << "Input either 'Matching-Accuracy' or 'Run-Time' as the experiment you want to conduct: ";
cin >> experiment;

// Matching Accuracy Experiment
if(experiment==t1)
{
    vector<vector<string> > R(DBLPWW);
    file.open("dblpWW.txt");

    // Storing records from text file   
    if(!file.is_open())
        cout << "Unable to open file" << endl;
    else
    {
        while(!file.eof())
        {
		    if(file.peek()!=' ')
		    {
                    getline(file,line);
    		    R[index].push_back(line);
		    }
            	    else
		    {
			    getline(file,line);
                	    index += 1;
			    if(index==DBLPWW)
				    break;
		    }
        }  
    }
    file.close();

// ------------------------------------------------ Algorithm 1 ---------------------------------------------------------------
    for(int i=0;i<R.size();i++) // for all r in R do    //can change the size to DBLP-WW possibly if not exact # of records
    {
    double test = 0;
        for(int j=0;j<counter-1;j++)  	// for all C in C do
            storage += cluster_similarity(R[i],Sc[j],j);

	test = cluster_similarity(R[i],Sc[placement],i);

        if(test>=threshold)	// recall threshold
        {
            //Cmax = arg max C in c sims(r,C) = placement
            for(int k=0;k<R[i].size();k++)
	    	C[placement].push_back(R[i][k]);           //Cmax <- Cmax union r          append r to Cmax
	    sort(C[placement].begin(), C[placement].end());
	    C[placement].erase(unique(C[placement].begin(),C[placement].end()),C[placement].end());
            //r1 <- arg max r in C r.t     O(1) since sorted by time
            Sc[placement].pop_back();                //sCmax <- sCmax \ r1           remove the last record
            Sc[placement].push_back(R[i][R[i].size()-1]);          //sCmax <- sCmax union r        append r as the last record
        }
        else
        {
            for(int k=0;k<R[i].size();k++)      
            	Cmax.push_back(R[i][k]);           // create a new cluster             cmax = {R}
	    Scmax.push_back(R[i][0]);
            Scmax.push_back(R[i][R[i].size()-1]);           // sCmax = {r}          // initialize the signature for Cmax
	    for(int k=0;k<R[i].size();k++)
            	C[identifier].push_back(Cmax[k]);                       // C <- C union Cmax
            Sc[identifier].push_back(Scmax[0]);                       // Sc <- Sc union sCmax
	    Sc[identifier].push_back(Scmax[1]);
	    identifier++;
            counter++;
        }
	Cmax.clear();
	Scmax.clear();  
    }

cout << "Would you like to view the static phase's clustering result? 0 for No and 1 for Yes: ";
cin >> choice;

if(choice==1)
{
        for(int i=0;i<counter-1;i++)
        {
                for(int j=0;j<C[i].size();j++)
                        cout << C[i][j] << ", ";
                cout << endl;
        }
cout << endl << "Total clusters are now: " << counter << " instead of 738 original records" << endl;
}

cout << endl << "Would you like to view the signatures of the static phase's clustering result? 0 for No and 1 for Yes: ";
cin >> choice;

if(choice==1)
{
        for(int i=0;i<counter-1;i++)
        {
                for(int j=0;j<Sc[i].size();j++)
                        cout << Sc[i][j] << ", ";
                cout << endl;
        }
}



// ----------------------------------------------- Algorithm 2 -----------------------------------------------------------------
for(int i=0;i<counter-1;i++)		// for all C in C do
{
double test = 0;
	for(int j=0;j<dcount-1;j++)		// for all D in D do
		storage += dynamic_similarity(C[i],Dc[j],j);		// dynamic similarity
	
	test = dynamic_similarity(C[i],Dc[location],i);		// best possible cluster based off dynamic threshold

	cout << test << endl;	

	if(test>=d_threshold)
	{
		//Dmax = arg max D in D simd(C,D) = location
		for(int k=0;k<C[i].size();k++)
			D[location].push_back(C[i][k]);		// merge to the best 
		sort(D[location].begin(),D[location].end());
		D[location].erase(unique(D[location].begin(),D[location].end()),D[location].end());
		Dc[location].pop_back();
		Dc[location].push_back(C[i][C[i].size()-1]);	
	}
	else
	{
		for(int k=0;k<C[i].size();k++)
			D[setting].push_back(C[i][k]);	// keep the original cluster
		Dc[setting].push_back(Sc[i][0]);
		Dc[setting].push_back(Sc[i][Sc[i].size()-1]);
		dcount++;
		setting++;
	}
}

cout << "Would you like to view the dynamic phase's clustering result? 0 for No and 1 for Yes: ";
cin >> choice;

if(choice==1)
{
	for(int i=0;i<dcount-1;i++)
	{
		for(int j=0;j<D[i].size();j++)
			cout << D[i][j] << ", ";
		cout << endl;
	}
cout << endl << "Total clusters are now: " << dcount << " instead of 738 original records" << endl;
}

cout << endl << "Would you like to view the signatures of the dynamic phase's clustering result? 0 for No and 1 for Yes: ";
cin >> choice;

if(choice==1)
{
	for(int i=0;i<dcount-1;i++)
        {
                for(int j=0;j<Dc[i].size();j++)
                        cout << Dc[i][j] << ", ";
                cout << endl;
        }
}

return 0;
}
// -------------------------------------------------------------------------------------------------------------------
// Run-Time Experiment
/*
else if(experiment==t2)
{
    cout << "Enter '0' if you would like to do 10% of the DBLP-100K dataset or '1' for its entirety: ";
    cin >> type;

    if(type==0)
    {
        vector<vector<string> > R((DBLP100K/10));
        file.open("dblp100K.txt");
    
        // Storing records from text file   
        if(!file.is_open())
            cout << "Unable to open file" << endl;
        else
        {
            while(!file.eof())
            {
                if(file.peek()!='\n')
                {
                	getline(file,line);
			        R[index].push_back(line);    
                }
                else
                {
                	index += 1;
			        getline(file,line);
			        if(index==(DBLP100K/10))
				        break;
                }
            }   
        }   
        file.close();
    }
    else if(type==1)
    {
    vector<vector<string> > R(DBLP100K);
    file.open("dblp100K.txt");
    
        // Storing records from text file   
        if(!file.is_open())
            cout << "Unable to open file" << endl;
        else
        {
            while(!file.eof())
            {
		        if(file.peek()!='\n')
		        {
                	getline(file,line);
			        R[index].push_back(line);
                }
                else
                {
                	index += 1;
			        getline(file,line);
			        if(index==DBLP100K)
				        break;
                }
            }
        }   
        file.close();
    }

    beg = clock();
    end = clock();

    elapsedtime = (end-beg) / (unsigned long long int)CLOCKS_PER_SEC;       // might be a double & its gonna give seconds i think
    cout << "Scalability experiments on 10% of DBLP-100K had an execution time of about: "<< elapsedtime << " hours" << endl;

}
*/ 
}
