#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
#include "SocialMediaPlatform.h"
//--------------------------------------------------------------------

TEST(contentAndContentCreator, contentAndContentCreator1) {
    string inputFile = BASE;
    inputFile += "/output2.txt";
    ifstream file( inputFile );
    string expectedOutput = "";
    string line;
    while ( getline( file, line ) ) {
        expectedOutput = expectedOutput + line + "\n";
    }
    stringstream ss;
    auto buffer = cout.rdbuf( ss.rdbuf() );

//--------------------------------------------------------------------
    SocialMediaPlatform SMP;

    SMP.showAllRegularUsers();
    cout << endl;
    SMP.showAllContentCreators();
    cout << endl;

    SMP.addContentCreator(3, "Omer");
    SMP.addContentCreator(2, "Burak");
    SMP.addContentCreator(4, "Hasan");
    SMP.addContentCreator(1, "Ayse");
    SMP.addContentCreator(5, "Fatma");
    SMP.addContentCreator(3, "Kamil");

    SMP.addContent(3, 20, "Live Music");
    SMP.addContent(2, 15, "Poem Recitation");
    SMP.addContent(2, 5, "About life");
    SMP.addContent(4, 100, "Day in life of student");
    SMP.addContent(1, 1, "My daily routine");
    SMP.addContent(1, 86, "How to keep motivated");
    SMP.addContent(5, 8, "My thoughts on topic X");
    SMP.addContent(5, 3, "My thoughts on use of AI for computational biology tasks");
    SMP.addContent(13, 6, "My thoughts on topic Y");
    SMP.addContent(4, 8, "Study together");
    SMP.addContent(13, 8, "Historical Facts");

    SMP.showAllContentCreators();
    cout << endl;
    SMP.showContentsOf(3);
    cout << endl;
    SMP.showContentsOf(1);
    cout << endl;
    SMP.showContentsOf(5);
    cout << endl;

    SMP.removeContentCreator(3);
    SMP.removeContent(3, 20);
    SMP.removeContentCreator(1);
    SMP.removeContent(5, 8);
    SMP.removeContent(5, 43);
    SMP.removeContent(45, 45);

    SMP.showAllContentCreators();
    cout << endl;
    SMP.showContentsOf(3);
    cout << endl;
    SMP.showContentsOf(2);
    cout << endl;
//--------------------------------------------------------------------

    string testOutput = ss.str();
    EXPECT_EQ( testOutput, expectedOutput );
    cout.rdbuf( buffer );
}

int main( int argc, char** argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

