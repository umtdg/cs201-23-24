#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
#include "SocialMediaPlatform.h"
//--------------------------------------------------------------------

TEST(Follow, Follow1) {
    string inputFile = BASE;
    inputFile += "/output3.txt";
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

    SMP.addContentCreator(5, "Omer");
    SMP.addContentCreator(3, "Burak");
    SMP.addContentCreator(2, "Hasan");
    SMP.addContentCreator(1, "Ayse");
    SMP.addContentCreator(4, "Fatma");

    SMP.addRegularUser(1, "user1");
    SMP.addRegularUser(5, "user5");
    SMP.addRegularUser(10, "user10");
    SMP.addRegularUser(2, "user2");
    SMP.addRegularUser(7, "user7");
    SMP.addRegularUser(2, "user2");

    SMP.showAllRegularUsers();
    cout << endl;
    SMP.showAllContentCreators();
    cout << endl;


    SMP.followContentCreator(5, 1);
    SMP.followContentCreator(5, 3);
    SMP.followContentCreator(5, 4);
    SMP.followContentCreator(5, 70);
    SMP.followContentCreator(1, 1);
    SMP.followContentCreator(1, 4);
    SMP.followContentCreator(1, 2);
    SMP.followContentCreator(2, 2);
    SMP.followContentCreator(7, 2);
    SMP.followContentCreator(10, 2);
    SMP.followContentCreator(10, 1);
    SMP.followContentCreator(10, 4);
    SMP.followContentCreator(7, 4);
    SMP.followContentCreator(70, 5);
    SMP.followContentCreator(70, 70);

    SMP.showAllContentCreators();
    cout << endl;

    SMP.showFollowersOf(4);
    SMP.showFollowersOf(3);
    SMP.showFollowersOf(2);
    SMP.showFollowersOf(1);
    SMP.showFollowersOf(5);
    SMP.showFollowersOf(8);

    SMP.removeRegularUser(10);
    SMP.removeContentCreator(4);

    SMP.showFollowersOf(4);
    SMP.showFollowersOf(2);

    SMP.addContentCreator(70, "Good Content Creator");
    SMP.showFollowersOf(70);

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
