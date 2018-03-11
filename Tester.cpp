#include"Tester.hpp"

void addDelTests()
{

    std::system("./sfarchiver add arc1 ./testfiles/test1.txt");

    // test duplicate add case

    std::system("./sfarchiver add arc1 ./testfiles/test1.txt");
    std::system("./sfarchiver add arc1 ./testfiles/test1ddgd.txt");

    // delete checks

    std::system("./sfarchiver del arc1 test1.txt");
    std::system("./sfarchiver del arc1 test1.txt");
    std::system("./sfarchiver del arc1 google.png");

    //add delete add delete....

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

    //extract tests

}
void extractTests()
{
    std::system("./sfarchiver add arc2 ./testfiles/test1.txt");
    std::system("./sfarchiver add arc2 ./testfiles/test2.txt");
    std::system("./sfarchiver del arc2 test1.txt");
    std::system("./sfarchiver extract arc2 test2.txt");
    std::system("./sfarchiver del arc2 test2.txt");

}


void performanceTests()
{
    std::cout<<"Performance Test 1. Deleting a small file stored after two large files"<<std::endl;

    std::system("./sfarchiver add arc1 ./testfiles/verne.txt");
    std::system("./sfarchiver add arc1 ./testfiles/twain.txt");
    std::system("./sfarchiver add arc1 ./testfiles/jfk.txt");
    auto start = std::chrono::system_clock::now(); // start timer
    std::system("./sfarchiver del arc1 jfk.txt");
    std::system("./sfarchiver del arc1 twain.txt");
    std::system("./sfarchiver del arc1 verne.txt");
    auto end = std::chrono::system_clock::now();

    std::cout<<"Performance Test 2. Deleting a small file stored first"<<std::endl;
    std::system("./sfarchiver add arc1 ./testfiles/jfk.txt");
    std::system("./sfarchiver add arc1 ./testfiles/verne.txt");
    std::system("./sfarchiver add arc1 ./testfiles/twain.txt");
    auto start1 = std::chrono::system_clock::now();
    std::system("./sfarchiver del arc1 jfk.txt");
    std::system("./sfarchiver del arc1 twain.txt");
    std::system("./sfarchiver del arc1 verne.txt");
    auto end1 = std::chrono::system_clock::now();
    std::cout<<"COmparing execution times"<<std::endl;
    std::cout<< "Performance Test1 has taken "<<std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << " microseconds to run."<<std::endl;
    std::cout<< "Performance Test2 has taken "<<std::chrono::duration_cast<std::chrono::microseconds>(end1-start1).count() << " microseconds to run."<<std::endl;
}

void memoryTests()
{

}
void Tester:: runTests()
{
  //  addDelTests();
  //  extractTests();
  performanceTests();

}
