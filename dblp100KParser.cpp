#include <string.h>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "/Users/haley/Desktop/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

int main(){

    ifstream theFile("dblp.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');


    xml_document<> doc;
    doc.parse<0>(&buffer[0]);
    xml_node<> * root_node = doc.first_node("dblp");

    int counter = 0;    //keep track of the number of records

    //iterate over the dblp article entries
    for(xml_node<>* article_node = root_node->first_node(); article_node; article_node = article_node->next_sibling())
    {   
    
        for(xml_node<> * title_node= article_node->first_node(); title_node; title_node = title_node->next_sibling())
        {   
            if(counter >= 100000){
                break;
            }
            
            counter += 1;
            char* type = title_node->name();
            if(strcmp(type, "author") == 0){
                cout << title_node->value() << endl;
            }
            else if(strcmp(type, "title") == 0){
                cout << title_node->value() << endl;
            }
                //else if(strcmp(type, "")) conference ?
            

        }
        cout << "\n";
    }
    cout << "number of records: " << counter << endl;
}   