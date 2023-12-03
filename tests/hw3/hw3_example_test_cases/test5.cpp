#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//--------------------------------------------------------------------
#include "SocialMediaPlatform.h"
//--------------------------------------------------------------------

TEST(TestInDescription, TestInDescription1) {
    string inputFile = BASE;
    inputFile += "/output5.txt";
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

    SMP.addContentCreator(3, "Lonely Artist");
    SMP.addContentCreator(2, "Eater Man");
    SMP.addContentCreator(4, "Pet Lover");
    SMP.removeContentCreator(4);
    SMP.removeContentCreator(4);
    SMP.addContentCreator(4, "Musician Guy");
    SMP.addContentCreator(4, "Cyborg");
    SMP.addContentCreator(1, "Gamer");
    SMP.addContentCreator(6, "News");
    cout << endl;

    SMP.addContent(3,1, "How to perform art?");
    SMP.addContent(4,2, "My favourite song");
    SMP.addContent(2,2, "Best Recipe Ever");
    SMP.addContent(6,5, "News of October");
    SMP.addContent(6,6, "News of November");
    SMP.addContent(6,8, "News of December");
    SMP.addContent(6,13, "News of 2023");
    SMP.removeContent(6, 5);
    SMP.removeContent(10, 7);
    SMP.removeContent(6, 7);

    SMP.showAllContentCreators();
    cout << endl;



    SMP.addRegularUser(1, "Alper");
    SMP.addRegularUser(5, "Ali");
    SMP.addRegularUser(4, "Merve");
    SMP.addRegularUser(2, "Ferit");
    SMP.addRegularUser(2, "Burak");
    SMP.addRegularUser(6, "Ayse");
    SMP.removeRegularUser(2);
    SMP.removeRegularUser(7);
    cout << endl;

    SMP.followContentCreator(1,6);
    SMP.followContentCreator(1,2);
    SMP.followContentCreator(1,1);
    SMP.followContentCreator(4,4);
    SMP.followContentCreator(4,3);
    SMP.followContentCreator(6,4);
    SMP.followContentCreator(6,6);
    SMP.followContentCreator(6,3);
    SMP.followContentCreator(5,3);
    SMP.followContentCreator(5,1);
    SMP.followContentCreator(1,7);
    SMP.followContentCreator(10,1);
    SMP.followContentCreator(10,10);
    SMP.unfollowContentCreator(1,7);
    SMP.unfollowContentCreator(10,1);
    SMP.unfollowContentCreator(10,10);
    SMP.unfollowContentCreator(1,3);
    SMP.unfollowContentCreator(6,4);
    cout << endl;

    SMP.removeRegularUser(5);
    SMP.removeContentCreator(3);
    cout<<endl;

    SMP.showAllContentCreators();
    cout << endl;
    SMP.showAllRegularUsers();
    cout << endl;
    SMP.showFollowersOf(6);
    cout << endl;
    SMP.showFollowersOf(10);
    cout << endl;
    SMP.showContentsOf(6);
    cout<<endl;
    SMP.showContentsOf(10);
//--------------------------------------------------------------------

    string testOutput = ss.str();
    EXPECT_EQ( testOutput, expectedOutput );
    cout.rdbuf( buffer );
}

int main( int argc, char** argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
