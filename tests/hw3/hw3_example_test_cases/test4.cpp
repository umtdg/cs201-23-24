#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
#include "SocialMediaPlatform.h"
//--------------------------------------------------------------------

TEST(FollowUnfollow, FollowUnfollow1) {
    string inputFile = BASE;
    inputFile += "/output4.txt";
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

    SMP.followContentCreator(5, 1);
    SMP.unfollowContentCreator(6,4);
    SMP.addContent(6,5, "News of October");
    SMP.removeContent(10, 7);
    SMP.showContentsOf(1);

    SMP.addContentCreator(3, "Ali");
    SMP.addContentCreator(2, "Elif");
    SMP.addContentCreator(1, "Selin");

    SMP.addRegularUser(7, "Alper");
    SMP.addRegularUser(3, "Gokce");
    SMP.addRegularUser(5, "Yigit");

    SMP.addContent(3, 20, "Running");
    SMP.addContent(1, 15, "Walking");
    SMP.addContent(2, 5, "Thinking");

    SMP.followContentCreator(5, 1);
    SMP.followContentCreator(5, 2);
    SMP.followContentCreator(5, 3);
    SMP.unfollowContentCreator(5, 3);
    SMP.followContentCreator(7, 2);
    SMP.followContentCreator(7, 1);
    SMP.followContentCreator(7, 3);
    SMP.unfollowContentCreator(7, 2);
    SMP.followContentCreator(3, 3);
    SMP.followContentCreator(3, 2);
    SMP.followContentCreator(3, 1);
    SMP.unfollowContentCreator(3, 1);
    SMP.unfollowContentCreator(3, 1);
    SMP.unfollowContentCreator(3, 2);
    SMP.unfollowContentCreator(3, 7);
    SMP.unfollowContentCreator(7, 3);

    SMP.showAllRegularUsers();
    cout << endl;
    SMP.showAllContentCreators();
    cout << endl;

    SMP.showContentsOf(1);
    SMP.showContentsOf(2);
    SMP.showContentsOf(3);

    SMP.showFollowersOf(1);
    SMP.showFollowersOf(2);
    SMP.showFollowersOf(3);

    SMP.addContentCreator(4, "Cenk");
    SMP.showContentsOf(4);
    SMP.showFollowersOf(4);
//--------------------------------------------------------------------

    string testOutput = ss.str();
    EXPECT_EQ( testOutput, expectedOutput );
    cout.rdbuf( buffer );
}

int main( int argc, char** argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
