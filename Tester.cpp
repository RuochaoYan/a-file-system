#include"Tester.hpp"

void Tester:: runTests()
{


  std::system("./sfarchiver add arc1 ./testfiles/test1.txt");
  // test duplicate add case
  std::system("./sfarchiver add arc1 ./testfiles/test1.txt");
  std::system("./sfarchiver add arc1 ./testfiles/test1ddgd.txt");
  // delete checks
  std::system("./sfarchiver del arc1 test1.txt");
  std::system("./sfarchiver del arc1 test1.txt");
  std::system("./sfarchiver del arc1 google.png");

  //add delete add deleted
  std::system("./sfarchiver add arc1 ./testfiles/jfk.txt");
  std::system("./sfarchiver del arc1 jfk.txt");
  std::system("./sfarchiver add arc1 ./testfiles/jfk.txt");
  std::system("./sfarchiver add arc1 ./testfiles/verne.txt");
  std::system("./sfarchiver add arc1 ./testfiles/twain.txt");
  std::system("./sfarchiver add arc1 ./testfiles/test1.txt");
  std::system("./sfarchiver del arc1 twain.txt");
  std::system("./sfarchiver add arc1 ./testfiles/google.png");
  std::system("./sfarchiver del arc1 verne.txt");
  std::system("./sfarchiver del arc1 google.png");
  std::system("./sfarchiver add arc1 ./testfiles/testimg1.jpg");
  
  std::system("./sfarchiver del arc1 testimg1.jpg");

}
