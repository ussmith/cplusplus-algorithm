#include <iostream>

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

void search(const std::vector<std::string> &words, std::string toFind) {
   //std::cout << "Searching" << std::endl;
   int top = words.size() - 1;
   int bottom = 0;
   int half = (top - bottom)/2;
   //std::cout << "Bottom - " << bottom << " Half - " << half <<  " Top - " << top << std::endl;

   bool found, done = false;
   int steps = 0;

   std::string target;
   while (!found && !done) {
     ++steps;

     //std::cout << "Bottom - " << bottom << " Half - " << half << " Top - " << top << std::endl;

     std::string target = words[half];
     
     if (bottom == top) {
       std::cout << "Not Found " << steps << " steps" <<  std::endl;
       done = true;
     }

     //std::cout << "target " << target << " : goal " << toFind << std::endl;
     if (target.compare(toFind) == 0) {
        std::cout << "Found " << steps << " steps - index = " << half <<  std::endl;
        found = true;
     } else if (target.compare(toFind) > 0) {
       //std::cout << "Shifting down" << std::endl;
       top = half;
     } else if (target.compare(toFind) < 0) {
       //std::cout << "Shifting up" << std::endl;
       bottom = half; 
     } 

     half = ((top - bottom) / 2) + bottom;
   }
}

int main(int argc, char **argv) {

  std::string line;
  std::ifstream myfile ("/usr/share/dict/american-english");

  std::vector<std::string> words;
  
  if (myfile.is_open())
  {
    while (std::getline(myfile,line)) {
      words.push_back(line);
    }
    //std::cout << words.size() << std::endl;

    myfile.close();
  } else {
    std::cout << "Unable to open file" << std::endl; 
  }

  std::thread t1(search, words, "hello");
  std::thread t2(search, words, "zoo");
  std::thread t3(search, words, "dog");
  std::thread t4(search, words, "llama");
  std::thread t5(search, words, "monkey");
  std::thread t6(search, words, "bug");
  std::thread t7(search, words, "bugger");
  std::thread t8(search, words, "veracity");
  std::thread t9(search, words, "***");
  //std::thread t10(search, words, "umbrella");


  auto l = [](const std::vector<std::string> &s, std::string t) {
    for (std::string word : s) {
      std::cout << word << std::endl;
    }};

  std::thread t10(l, words, "***");
  search(words, "goodbye");

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  t10.join();

  std::cout << "Done" << std::endl;

  return 0;
}