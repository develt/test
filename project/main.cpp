#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "graph_wrapper.h"


using namespace std;

bool load_dict(std::vector<std::wstring>& dict, const char* file_path,  
                                  const wstring& from, const wstring& to,  
                                          size_t& from_ind, size_t& to_ind)
{
  std::wifstream file;
  std::wstring line;
  std::set<wstring> checker;

  locale deflocale("");
  setlocale(LC_ALL, "");

  file.open(file_path);        

  if (!file.is_open())
  {
      wcout << "wrong file name: " << file_path;

      return false;
  }
        
  file.imbue(deflocale); 

  size_t ind = 1;
  from_ind = ~0;
  to_ind = ~0;
	
  while(file.good())
  {
      getline(file, line);

	  if (checker.find(line) != checker.end())
		  continue;

      if (line == from) 
          from_ind = ind;

      if (line == to)
          to_ind = ind;

	  checker.insert(line);

      dict.push_back(line);
                
      ++ind;
  }

  file.close();

  if (from_ind == ~0 || to_ind == ~0)
  {
      wcout << "any of input word (" << from << " or " << to << 
		  ") not found in dictionary" << endl;

      return false;
  }

  return true;
}

bool load_start_end_word(const char* file_path, std::wstring& start_word,
	                                              std::wstring& end_word)
{
  wifstream file;
  locale deflocale("");
  setlocale(LC_ALL, "");

  file.open(file_path);
    
  if (!file.is_open())
  {
      wcout << L"wrong file name: " << file_path;

      return false;
  }
        
  file.imbue(deflocale); 
        
  size_t ind = 0;

  while(file.good())
  {
      if (ind++ == 0)
      {
          getline(file, start_word);

		  continue;
      }
     
	  getline(file, end_word);
                                        
          break;       
  }

  file.close();

  if (ind != 2)
  {
      wcout << L"any of input word not found" << endl;

      return false;
  }

  return true;
}

int main(int argc, char* argv[]) 
{ 
  std::vector<std::wstring> dict;
  size_t start_vertex_id = ~0;
  size_t end_vertex_id = ~0;
  std::wstring start_word;
  std::wstring end_word;

  try {

    alfa_test::graph_wrapper gw;

    if (argc < 3)
    {
        wcout << L"Usage: alfa_test dict_path word_from word_to" << endl;

        return 1;
    }
        
        
    if (!load_start_end_word(argv[2], start_word, end_word))
        return 1;
        
    if (!load_dict(dict, argv[1], start_word, end_word,  
	                      end_vertex_id, start_vertex_id))
        return 1;
        
    gw.get_shortest_path(end_vertex_id, start_vertex_id, dict);

  }
  catch(const std::exception& e)
  {
	  cout << "std::exceptoin: " << e.what() << endl;
  }
}

