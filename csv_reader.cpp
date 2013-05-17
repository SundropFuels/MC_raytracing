#include "csv_reader.h"
#include <iostream>


csv_reader::csv_reader()
{
//this should do nothing right now
}

csv_reader::csv_reader(string & filename)
{
 file.open(filename.c_str());                //open file for reading
 
 CSV_parse();
 file.close();                               //close file, make available for other things
  
 
}

csv_reader::~csv_reader()
{
                         //do nothing
                         
}

/**********************************************************************************************************
Iterator implementations

**********************************************************************************************************/


csv_reader::iterator::iterator()
{
     
}

csv_reader::iterator::~iterator()
{
     
}

csv_reader::iterator::iterator(const iterator & original)
{
     pos = original.pos;
}

bool csv_reader::iterator::operator==(const iterator & it)
{
     return (pos == it.get_pos());
}

bool csv_reader::iterator::operator!=(const iterator & it)
{
     return !(pos == it.get_pos());
}

void csv_reader::iterator::operator++()
{
     
     pos++;
     
}

void csv_reader::iterator::operator--()
{
     pos--;
}

void csv_reader::iterator::set_pos(int & val)
{
     pos = val;
}

int csv_reader::iterator::get_pos() const
{
    return pos;
}


void csv_reader::CSV_parse()
{
     
    
     
     while(file.good())            //so long as the stream is valid, continue to add string vectors to string_fields
     {
                string_fields.push_back(CSV_get_line());
     }
     
     line_pos = 0;
     col_pos = 0;
     //for some reason, this pushes an extra line on -- this is in the get_line function -- I will fix later when I redev this whole class
	//in the meantime, I am going to just pop the extra line
	string_fields.pop_back();
     it = string_fields.begin();
     col_it = (*it).begin();
    
      
      
}




vector<string> csv_reader::CSV_get_line()
{
               char fieldDelim = ',';        //CSV has a comma delimiter
               char recordDelim = '\n';      //end of line character
               
               
               bool trimWhiteSpace = true;   //eliminate white space in files
               
               vector<string> record;
               string field;                 //temporary field construction
               int start = -1;
               int end = -1;
               char ch;
               
               while(file.get(ch))
               {
                                  if(ch == fieldDelim || ch == recordDelim)
                                  {
                                        //These mark the end of a field
                                        //Save the field, reset for the next field
                                        //Break there if there are no more fields
                                        
                                        //We can trim whitespace here, but ignore for now
                                        
                                        //save the new field and reset the temporary
                                                                                                                       
                                        record.push_back(field);
                                        field.clear();
                                  
                                  
                                        //exit case 1: !is, managed by loop condition (no chars to get)
                                        //exit case 2: recordDelim, managed here - line got
                                  
                                        if(ch == recordDelim) break;
                                  }
                                  
                                  //could handle quotes here, if necessary
                                  
                                  
                                  //add character to the field
                                  else field.push_back(ch);                  
               }
               
               
               
               return record;     //if I get EOF or recordDelim, return the line
              
               //do nothing right now
               
}



  
void csv_reader::print_vector()
{
     for(int i = 0; i < string_fields.size(); i++)
     {
             for(int j=0;j < string_fields[i].size(); j++)
             {
                     cout << string_fields[i][j] << "  ";
             }
             
             cout << endl;
     }
}

int csv_reader::lines()
{
    return string_fields.size();
}

bool csv_reader::end_of_line()
{
	return (col_it == (*it).end());
}

bool csv_reader::end_of_file()
{
	return (it == string_fields.end());
}
