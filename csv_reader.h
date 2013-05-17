#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

class csv_reader
{
      public:

      csv_reader();
      csv_reader(string & filename);
      ~csv_reader();

      //This class needs iterators to move through the CSV vectors
      class iterator
      {
            public:
            
            iterator();
            ~iterator();
            iterator(const iterator & original);       
            
            bool operator==(const iterator & it);
            bool operator!=(const iterator & it);
            void operator++();
            void operator--();
            void set_pos(int & val);
            int get_pos() const;
            
            private:
                    
            int pos;
            vector< vector<string> >::iterator lines_it;
            vector<string>::iterator cols_it;
            
            
      };



      //overload >> operator to be able to use this like a stream, where the , delmits beginning and end
      //this operator must automatically find EOL and commas -- that allows for an iterator approach to
      //automatically fill vectors of data

      //csv_reader & operator>>(ValType & var);                   //This is the double version -- will template this later            
      template <typename ValType>
      csv_reader & operator>>(ValType & var);                   //This is the double version -- will template this later 
      
      
      bool end_of_line();						//returns whether at the end of a line or not
      bool end_of_file();						//returns whether at the end of a file or not
      
      void print_vector();
      int lines();
      
      
      private:

      //a couple of private member functions that will be called by the constructor to fill the CSV file
      void CSV_parse();                                      //Parses the entire CSV file
      vector<string> CSV_get_line();                                   //Gets each line in the CSV file

      ifstream file;
      stringstream data_holder;
      
      vector< vector<string> > string_fields;
      vector< vector<string> >::iterator it;                 //iterator to replace the "lines" term
      vector<string>::iterator col_it;                       //column iterator      
      //These are for a near term, get it working implementation; we'll focus on building a generic iterator later
           
      
      int line_pos;
      int col_pos;
     

};

template <typename ValType>
csv_reader & csv_reader::operator>>(ValType & var)                   //This is the double version -- will template this later 
      {
      //first implementation will be with indexing integers, then we'll move on to vector iterators, and finally an iterator for the CSV_reader
      if(it == string_fields.end())
         {
                     cerr << "You have exceeded the length of the CSV file." << endl;
                     
                     system("PAUSE");
                     exit(1);
         }
         
                     else
                     {
                                     
                                     istringstream data_hold(*col_it);
                                     
                                   data_hold >> var;
                               //data_holder << string_fields[line_pos][col_pos];
                                   //data_holder >> var;

				
                     
                                col_it++;
				

                              
                                //if(col_it == (*it).end())
				if(end_of_line())
                                {
                                          it++;
                                          col_it = (*it).begin();
                                }
                                
                      } 
         
           return *this;
  
         }

                 
