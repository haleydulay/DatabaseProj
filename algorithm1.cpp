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
int counter = 0;

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

double dynamic_similarity(vector<string> r, vector<string> r2, int j)
{
double result = 0;

}

int main()
{
int identifier = 0;
double threshold = 0.2;
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
        for(int j=0;j<=counter-1;j++)  	// for all C in C do
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

// ----------------------------------------------- Algorithm 2 -----------------------------------------------------------------
/*for(int i=0;i<counter-1;i++)
{
	for(int j=0;j<=counter-1;j++)
		storage = dynamic_similarity(Sc[i],D[j],j);
	if(
}*/

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
                	getletline(file,line);
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

    return out;
}
*/ 
}
