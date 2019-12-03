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

    int counter = 0;


    //iterate over the dblp article entries
    for(xml_node<>* article_node = root_node->first_node(); article_node; article_node = article_node->next_sibling())
    {   

          
            for(xml_node<> * found_node= article_node->first_node("author"); found_node; found_node = found_node->next_sibling()){
                if(counter == 2000000){
                    break;
                    }
                counter += 1;
                char* type = found_node->name();
               if(strcmp(type,"author") == 0){
                    cout << found_node->value() << endl;
                }

            }
            cout << "\n";
        }
    
        cout << "number of records: " << counter << endl;
}

    
