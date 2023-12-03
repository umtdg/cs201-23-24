#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
#include "SocialMediaPlatform.h"
//--------------------------------------------------------------------

TEST(contentCreatorAdd, contentCreatorAdd1) {
    string inputFile = BASE;
    inputFile += "/output1.txt";
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

    SMP.removeContentCreator(2);

    SMP.addContentCreator(2, "Ali");
    SMP.addContentCreator(2, "Veli");
    SMP.addContentCreator(1, "Burak");
    SMP.addContentCreator(1, "Ferit");
    SMP.addContentCreator(9, "Omer");
    SMP.addContentCreator(8, "Furkan");
    SMP.addContentCreator(7, "Sena");
    SMP.addContentCreator(5, "Merve");
    SMP.addContentCreator(4, "Ela");

    SMP.showAllRegularUsers();
    cout << endl;
    SMP.showAllContentCreators();
    cout << endl;

    SMP.removeContentCreator(3);
    SMP.removeContentCreator(1);
    SMP.removeContentCreator(1);
    SMP.removeContentCreator(8);

    cout<<endl;

    SMP.showAllRegularUsers();
    cout << endl;
    SMP.showAllContentCreators();
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
