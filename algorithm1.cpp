/*
Input:
R, a list of records sorted in increasing temporal order.
0s, a threshold to make merge decision
Output:
C, the clustering of records in R
Sc, the set of cluster signatures corresponding to C, each cluster in C has a signature in Sc.
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <time>
#include <ctime>
#define DBLP-WW 738
#define DBLP-100K 103059

using namespace std;

struct output
{
vector<string> C;
vector<string> Sc;
}

int main()
{
ifstream file;
int index = 0;
clock_t beg = 0;
clock_t end = 0;
unsigned long long int elapsedtime = 0;     // might be a double
int type;
int record_count = 0;
string line;
string experiment;
string t1 = "Matching-Accuracy";
string t2 = "Run-Time";
output out;
vector<string> Cmax;
vector<string> Scmax;

cout << "Input either 'Matching-Accuracy' or 'Run-Time' as the experiment you want to conduct: ";
cin >> experiment;

// Matching Accuracy Experiment
if(experiment==t1)
{
    vector<vector<string> > R(DBLP-WW);
    file.open("dblpWW.txt");

    // Storing records from text file   
    if(!file.isopen())
        cout << "Unable to open file" << endl;
    else
    {
        while(!file.eof())
        {
            getline(file,line);
            if(line!='\n')
            {
                //idk how to push it back into the 2d vector tbh
            }
            else
            {
                // skip over to the next index of vector to signify the end of a record.
                index += 1;
            } 
        }  
    }
    file.close();
    
    for(int i=0;i<R.size();i++) // for all r in R do    //can change the size to DBLP-WW possibly if not exact # of records
    {
        for(int j=0;j<C.size();j++)  // for all C in C do
        {
            // compute sims(r,C)
        }
        if(//maxC in csims(r,C)>=0s   if true, then merge to the next possible cluster)
        {
            //Cmax = arg max C in c sims(r,C)
            Cmax.push_back(R[i]);           //Cmax <- Cmax union r          append r to Cmax
            //r1 <- arg max r in C r.t      O(1) since sorted by time
            Scmax.pop_back();                //sCmax <- sCmax \ r1           remove the last record
            Scmax.push_back(R[i]);          //sCmax <- sCmax unior r        append r as the last record
        }
        else
        {      
            Cmax = R[i];           // create a new cluster             cmax = {R}
            Scmax = R[i];           // sCmax = {r}          // initialize the signature for Cmax
            out.C.push_back(Cmax);                       // C <- C union Cmax
            out.Sc.push_back(Scmax);                       // Sc <- Sc union sCmax
        }   
    }
    return out;       // return C, Sc
}
// -------------------------------------------------------------------------------------------------------------------
// Run-Time Experiment
else if(experiment==t2)
{
    cout << "Enter '0' if you would like to do 10% of the DBLP-100K dataset or '1' for its entirety: ";
    cin >> type;

    if(type==0)
    {
        vector<vector<string> > R((DBLP-100K/10));
        file.open("dblp100K.txt");
    
        // Storing records from text file   
        if(!file.isopen())
            cout << "Unable to open file" << endl;
        else
        {
            while(!file.eof())
            {
                getline(file,line);
                if(line!='\n')
                {
                    //idk how to push it back into the 2d vector tbh
                }
                else
                {
                    recourd_count += 1;
                    // skip over to the next index of vector to signify the end of a record.
                }
                if(record_count >= DBLP-100K/10)
                    break;
            }   
        }   
        file.close();
    }
    else if(type==1)
    {
    vector<vector<string> > R(DBLP-100K);
    file.open("dblp100K.txt");
    
        // Storing records from text file   
        if(!file.isopen())
            cout << "Unable to open file" << endl;
        else
        {
            while(!file.eof())
            {
                getline(file,line);
                if(line!='\n')
                {
                    //idk how to push it back into the 2d vector tbh
                }
                else
                {
                    // skip over to the next index of vector to signify the end of a record.
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
