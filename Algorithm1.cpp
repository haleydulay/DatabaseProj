/*
Input:
R, a list of records sorted in increasing temporal order.
0s, a threshold to make merge decision
Output:
C, the clustering of records in R
Sc, the set of cluster signatures corresponding to C, each cluster in C has a signature in Sc.
*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
vector<string> R;
vector<string> C; // C={}

for(i=0;i<R.size();i++) // for all r in R do
{
        for(j=0;j<C.size();j++)  // for all C in C do
        {
        // compute sims(r,C)
        }
        if(//maxC in csims(r,C)>=0s   if true, then merge to the next possible cluster)
        {
        //Cmax = arg max C in c sims(r,C)
        //Cmax <- Cmax union r          append r to Cmax
        //r1 <- arg max r in C r.t      O(1) since sorted by time
        //sCmax <- sCmax \ r1           remove the last record
        //sCmax <- sCmax unior r        append r as the last record
        }
        else
        {
        // Cmax = {r}           // create a new cluster
        // sCmax = {r}          // initialize the signature for Cmax
        // C <- C union Cmax
        // Sc <- Sc union sCmax
        }
}

return 0;       // return C, Sc
}
