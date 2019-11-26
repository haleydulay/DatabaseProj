#include <string.h>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include "/Users/haley/Desktop/rapidxml.hpp"
//#include "/Users/haley/Desktop/rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

int main(){

    ifstream theFile("sampledblp.xml");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    cout << "XML loaded" << endl;

    xml_document<> doc;
    doc.parse<0>(&buffer[0]);
    xml_node<> * root_node = doc.first_node("dblp");



    //iterate over the dblp article entries
    for(xml_node<>* article_node = root_node->first_node(); article_node; article_node = article_node->next_sibling())
    {   
    
        for(xml_node<> * title_node= article_node->first_node(); title_node; title_node = title_node->next_sibling())
        {   
                char* author = title_node->value();
                //cout << author << endl;
                if(strcmp(author, "Yuval Yarom") == 0){ //edit for "Wei Wang"
                    cout << title_node->value() << endl;
                    for(xml_node<> * found_node= article_node->first_node(); found_node; found_node = found_node->next_sibling()){
                        cout << found_node->value() << endl;
                    }
                }
        

        }
        
    }


}
