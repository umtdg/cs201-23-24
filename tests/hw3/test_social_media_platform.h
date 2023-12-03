#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

#include <hw3/SocialMediaPlatform.h>

TEST(SocialMediaPlatform, AddRemoveContentCreator) {
    const std::string expectedOutput = "Regular users in the social media platform:\n"
    "None\n\n"
    "Content creators in the social media platform:\n"
    "None\n\n"
    "Cannot remove content creator. There is no content creator with ID 2.\n"
    "Added content creator 2.\n"
    "Cannot add content creator. There is already a content creator with ID 2.\n"
    "Added content creator 1.\n"
    "Cannot add content creator. There is already a content creator with ID 1.\n"
    "Added content creator 9.\n"
    "Added content creator 8.\n"
    "Added content creator 7.\n"
    "Added content creator 5.\n"
    "Added content creator 4.\n"
    "Regular users in the social media platform:\n"
    "None\n\n"
    "Content creators in the social media platform:\n"
    "1, Burak, 0 follower(s), 0 content(s)\n"
    "2, Ali, 0 follower(s), 0 content(s)\n"
    "4, Ela, 0 follower(s), 0 content(s)\n"
    "5, Merve, 0 follower(s), 0 content(s)\n"
    "7, Sena, 0 follower(s), 0 content(s)\n"
    "8, Furkan, 0 follower(s), 0 content(s)\n"
    "9, Omer, 0 follower(s), 0 content(s)\n\n"
    "Cannot remove content creator. There is no content creator with ID 3.\n"
    "Removed content creator 1.\n"
    "Cannot remove content creator. There is no content creator with ID 1.\n"
    "Removed content creator 8.\n\n"
    "Regular users in the social media platform:\n"
    "None\n\n"
    "Content creators in the social media platform:\n"
    "2, Ali, 0 follower(s), 0 content(s)\n"
    "4, Ela, 0 follower(s), 0 content(s)\n"
    "5, Merve, 0 follower(s), 0 content(s)\n"
    "7, Sena, 0 follower(s), 0 content(s)\n"
    "9, Omer, 0 follower(s), 0 content(s)\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------
    SocialMediaPlatform SMP;

    SMP.showAllRegularUsers();
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

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
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

    SMP.removeContentCreator(3);
    SMP.removeContentCreator(1);
    SMP.removeContentCreator(1);
    SMP.removeContentCreator(8);

    std::cout << '\n';

    SMP.showAllRegularUsers();
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';
    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(SocialMediaPlatform, AddRemoveContent) {
    const std::string expectedOutput = "Regular users in the social media platform:\n"
        "None\n\n"
        "Content creators in the social media platform:\n"
        "None\n\n"
        "Added content creator 3.\n"
        "Added content creator 2.\n"
        "Added content creator 4.\n"
        "Added content creator 1.\n"
        "Added content creator 5.\n"
        "Cannot add content creator. There is already a content creator with ID 3.\n"
        "Added content 20.\n"
        "Added content 15.\n"
        "Added content 5.\n"
        "Added content 100.\n"
        "Added content 1.\n"
        "Added content 86.\n"
        "Added content 8.\n"
        "Added content 3.\n"
        "Cannot add content. There is no content creator with ID 13.\n"
        "Cannot add content. There is already a content with ID 8.\n"
        "Cannot add content. There is already a content with ID 8.\n"
        "Content creators in the social media platform:\n"
        "1, Ayse, 0 follower(s), 2 content(s)\n"
        "2, Burak, 0 follower(s), 2 content(s)\n"
        "3, Omer, 0 follower(s), 1 content(s)\n"
        "4, Hasan, 0 follower(s), 1 content(s)\n"
        "5, Fatma, 0 follower(s), 2 content(s)\n\n"
        "Contents of content creator with ID 3:\n"
        "20\n\n"
        "Contents of content creator with ID 1:\n"
        "1\n"
        "86\n\n"
        "Contents of content creator with ID 5:\n"
        "3\n"
        "8\n\n"
        "Removed content creator 3.\n"
        "Cannot remove content. There is no content creator with ID 3.\n"
        "Removed content creator 1.\n"
        "Removed content 8.\n"
        "Cannot remove content. There is no content with ID 43 shared by content creator with ID 5.\n"
        "Cannot remove content. There is no content creator with ID 45.\n"
        "Content creators in the social media platform:\n"
        "2, Burak, 0 follower(s), 2 content(s)\n"
        "4, Hasan, 0 follower(s), 1 content(s)\n"
        "5, Fatma, 0 follower(s), 1 content(s)\n\n"
        "Cannot show. There is no content creator with ID 3.\n\n"
        "Contents of content creator with ID 2:\n"
        "5\n"
        "15\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    SocialMediaPlatform SMP;

    SMP.showAllRegularUsers();
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

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
    std::cout << '\n';
    SMP.showContentsOf(3);
    std::cout << '\n';
    SMP.showContentsOf(1);
    std::cout << '\n';
    SMP.showContentsOf(5);
    std::cout << '\n';

    SMP.removeContentCreator(3);
    SMP.removeContent(3, 20);
    SMP.removeContentCreator(1);
    SMP.removeContent(5, 8);
    SMP.removeContent(5, 43);
    SMP.removeContent(45, 45);

    SMP.showAllContentCreators();
    std::cout << '\n';
    SMP.showContentsOf(3);
    std::cout << '\n';
    SMP.showContentsOf(2);
    std::cout << '\n';

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(SocialMediaPlatform, TestFollowing) {
    const std::string expectedOutput = "Regular users in the social media platform:\n"
        "None\n\n"
        "Content creators in the social media platform:\n"
        "None\n\n"
        "Added content creator 5.\n"
        "Added content creator 3.\n"
        "Added content creator 2.\n"
        "Added content creator 1.\n"
        "Added content creator 4.\n"
        "Added regular user 1.\n"
        "Added regular user 5.\n"
        "Added regular user 10.\n"
        "Added regular user 2.\n"
        "Added regular user 7.\n"
        "Cannot add regular user. There is already a regular user with ID 2.\n"
        "Regular users in the social media platform:\n"
        "1, user1\n"
        "2, user2\n"
        "5, user5\n"
        "7, user7\n"
        "10, user10\n\n"
        "Content creators in the social media platform:\n"
        "1, Ayse, 0 follower(s), 0 content(s)\n"
        "2, Hasan, 0 follower(s), 0 content(s)\n"
        "3, Burak, 0 follower(s), 0 content(s)\n"
        "4, Fatma, 0 follower(s), 0 content(s)\n"
        "5, Omer, 0 follower(s), 0 content(s)\n\n"
        "Regular user with ID 5 followed content creator with ID 1.\n"
        "Regular user with ID 5 followed content creator with ID 3.\n"
        "Regular user with ID 5 followed content creator with ID 4.\n"
        "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Regular user with ID 1 followed content creator with ID 1.\n"
        "Regular user with ID 1 followed content creator with ID 4.\n"
        "Regular user with ID 1 followed content creator with ID 2.\n"
        "Regular user with ID 2 followed content creator with ID 2.\n"
        "Regular user with ID 7 followed content creator with ID 2.\n"
        "Regular user with ID 10 followed content creator with ID 2.\n"
        "Regular user with ID 10 followed content creator with ID 1.\n"
        "Regular user with ID 10 followed content creator with ID 4.\n"
        "Regular user with ID 7 followed content creator with ID 4.\n"
        "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Content creators in the social media platform:\n"
        "1, Ayse, 3 follower(s), 0 content(s)\n"
        "2, Hasan, 4 follower(s), 0 content(s)\n"
        "3, Burak, 1 follower(s), 0 content(s)\n"
        "4, Fatma, 4 follower(s), 0 content(s)\n"
        "5, Omer, 0 follower(s), 0 content(s)\n\n"
        "Regular users following content creator with ID 4:\n"
        "1\n"
        "5\n"
        "7\n"
        "10\n"
        "Regular users following content creator with ID 3:\n"
        "5\n"
        "Regular users following content creator with ID 2:\n"
        "1\n"
        "2\n"
        "7\n"
        "10\n"
        "Regular users following content creator with ID 1:\n"
        "1\n"
        "5\n"
        "10\n"
        "Regular users following content creator with ID 5:\n"
        "None\n"
        "Cannot show. There is no content creator with ID 8.\n"
        "Removed regular user 10.\n"
        "Removed content creator 4.\n"
        "Cannot show. There is no content creator with ID 4.\n"
        "Regular users following content creator with ID 2:\n"
        "1\n"
        "2\n"
        "7\n"
        "Added content creator 70.\n"
        "Regular users following content creator with ID 70:\n"
        "None\n"
        "Regular users in the social media platform:\n"
        "1, user1\n"
        "2, user2\n"
        "5, user5\n"
        "7, user7\n\n"
        "Content creators in the social media platform:\n"
        "1, Ayse, 2 follower(s), 0 content(s)\n"
        "2, Hasan, 3 follower(s), 0 content(s)\n"
        "3, Burak, 1 follower(s), 0 content(s)\n"
        "5, Omer, 0 follower(s), 0 content(s)\n"
        "70, Good Content Creator, 0 follower(s), 0 content(s)\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    SocialMediaPlatform SMP;

    SMP.showAllRegularUsers();
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

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
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';


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
    std::cout << '\n';

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
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(SocialMediaPlatform, TestUnfollowing) {
    const std::string expectedOutput = "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Cannot unfollow. Regular user and/or content creator ID does not exist.\n"
        "Cannot add content. There is no content creator with ID 6.\n"
        "Cannot remove content. There is no content creator with ID 10.\n"
        "Cannot show. There is no content creator with ID 1.\n"
        "Added content creator 3.\n"
        "Added content creator 2.\n"
        "Added content creator 1.\n"
        "Added regular user 7.\n"
        "Added regular user 3.\n"
        "Added regular user 5.\n"
        "Added content 20.\n"
        "Added content 15.\n"
        "Added content 5.\n"
        "Regular user with ID 5 followed content creator with ID 1.\n"
        "Regular user with ID 5 followed content creator with ID 2.\n"
        "Regular user with ID 5 followed content creator with ID 3.\n"
        "Regular user with ID 5 unfollowed content creator with ID 3.\n"
        "Regular user with ID 7 followed content creator with ID 2.\n"
        "Regular user with ID 7 followed content creator with ID 1.\n"
        "Regular user with ID 7 followed content creator with ID 3.\n"
        "Regular user with ID 7 unfollowed content creator with ID 2.\n"
        "Regular user with ID 3 followed content creator with ID 3.\n"
        "Regular user with ID 3 followed content creator with ID 2.\n"
        "Regular user with ID 3 followed content creator with ID 1.\n"
        "Regular user with ID 3 unfollowed content creator with ID 1.\n"
        "Cannot unfollow. The user is not following the content creator.\n"
        "Regular user with ID 3 unfollowed content creator with ID 2.\n"
        "Cannot unfollow. Regular user and/or content creator ID does not exist.\n"
        "Regular user with ID 7 unfollowed content creator with ID 3.\n"
        "Regular users in the social media platform:\n"
        "3, Gokce\n"
        "5, Yigit\n"
        "7, Alper\n\n"
        "Content creators in the social media platform:\n"
        "1, Selin, 2 follower(s), 1 content(s)\n"
        "2, Elif, 1 follower(s), 1 content(s)\n"
        "3, Ali, 1 follower(s), 1 content(s)\n\n"
        "Contents of content creator with ID 1:\n"
        "15\n"
        "Contents of content creator with ID 2:\n"
        "5\n"
        "Contents of content creator with ID 3:\n"
        "20\n"
        "Regular users following content creator with ID 1:\n"
        "5\n"
        "7\n"
        "Regular users following content creator with ID 2:\n"
        "5\n"
        "Regular users following content creator with ID 3:\n"
        "3\n"
        "Added content creator 4.\n"
        "Contents of content creator with ID 4:\n"
        "None\n"
        "Regular users following content creator with ID 4:\n"
        "None\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

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
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

    SMP.showContentsOf(1);
    SMP.showContentsOf(2);
    SMP.showContentsOf(3);

    SMP.showFollowersOf(1);
    SMP.showFollowersOf(2);
    SMP.showFollowersOf(3);

    SMP.addContentCreator(4, "Cenk");
    SMP.showContentsOf(4);
    SMP.showFollowersOf(4);

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(SocialMediaPlatform, MixedTest) {
    const std::string expectedOutput = "Regular users in the social media platform:\n"
        "None\n\n"
        "Content creators in the social media platform:\n"
        "None\n\n"
        "Added content creator 3.\n"
        "Added content creator 2.\n"
        "Added content creator 4.\n"
        "Removed content creator 4.\n"
        "Cannot remove content creator. There is no content creator with ID 4.\n"
        "Added content creator 4.\n"
        "Cannot add content creator. There is already a content creator with ID 4.\n"
        "Added content creator 1.\n"
        "Added content creator 6.\n\n"
        "Added content 1.\n"
        "Added content 2.\n"
        "Cannot add content. There is already a content with ID 2.\n"
        "Added content 5.\n"
        "Added content 6.\n"
        "Added content 8.\n"
        "Added content 13.\n"
        "Removed content 5.\n"
        "Cannot remove content. There is no content creator with ID 10.\n"
        "Cannot remove content. There is no content with ID 7 shared by content creator with ID 6.\n"
        "Content creators in the social media platform:\n"
        "1, Gamer, 0 follower(s), 0 content(s)\n"
        "2, Eater Man, 0 follower(s), 0 content(s)\n"
        "3, Lonely Artist, 0 follower(s), 1 content(s)\n"
        "4, Musician Guy, 0 follower(s), 1 content(s)\n"
        "6, News, 0 follower(s), 3 content(s)\n\n"
        "Added regular user 1.\n"
        "Added regular user 5.\n"
        "Added regular user 4.\n"
        "Added regular user 2.\n"
        "Cannot add regular user. There is already a regular user with ID 2.\n"
        "Added regular user 6.\n"
        "Removed regular user 2.\n"
        "Cannot remove regular user. There is no regular user with ID 7.\n\n"
        "Regular user with ID 1 followed content creator with ID 6.\n"
        "Regular user with ID 1 followed content creator with ID 2.\n"
        "Regular user with ID 1 followed content creator with ID 1.\n"
        "Regular user with ID 4 followed content creator with ID 4.\n"
        "Regular user with ID 4 followed content creator with ID 3.\n"
        "Regular user with ID 6 followed content creator with ID 4.\n"
        "Regular user with ID 6 followed content creator with ID 6.\n"
        "Regular user with ID 6 followed content creator with ID 3.\n"
        "Regular user with ID 5 followed content creator with ID 3.\n"
        "Regular user with ID 5 followed content creator with ID 1.\n"
        "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Cannot follow. Regular user and/or content creator ID does not exist.\n"
        "Cannot unfollow. Regular user and/or content creator ID does not exist.\n"
        "Cannot unfollow. Regular user and/or content creator ID does not exist.\n"
        "Cannot unfollow. Regular user and/or content creator ID does not exist.\n"
        "Cannot unfollow. The user is not following the content creator.\n"
        "Regular user with ID 6 unfollowed content creator with ID 4.\n\n"
        "Removed regular user 5.\n"
        "Removed content creator 3.\n\n"
        "Content creators in the social media platform:\n"
        "1, Gamer, 1 follower(s), 0 content(s)\n"
        "2, Eater Man, 1 follower(s), 0 content(s)\n"
        "4, Musician Guy, 1 follower(s), 1 content(s)\n"
        "6, News, 2 follower(s), 3 content(s)\n\n"
        "Regular users in the social media platform:\n"
        "1, Alper\n"
        "4, Merve\n"
        "6, Ayse\n\n"
        "Regular users following content creator with ID 6:\n"
        "1\n"
        "6\n\n"
        "Cannot show. There is no content creator with ID 10.\n\n"
        "Contents of content creator with ID 6:\n"
        "6\n"
        "8\n"
        "13\n\n"
        "Cannot show. There is no content creator with ID 10.\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    SocialMediaPlatform SMP;

    SMP.showAllRegularUsers();
    std::cout << '\n';
    SMP.showAllContentCreators();
    std::cout << '\n';

    SMP.addContentCreator(3, "Lonely Artist");
    SMP.addContentCreator(2, "Eater Man");
    SMP.addContentCreator(4, "Pet Lover");
    SMP.removeContentCreator(4);
    SMP.removeContentCreator(4);
    SMP.addContentCreator(4, "Musician Guy");
    SMP.addContentCreator(4, "Cyborg");
    SMP.addContentCreator(1, "Gamer");
    SMP.addContentCreator(6, "News");
    std::cout << '\n';

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
    std::cout << '\n';



    SMP.addRegularUser(1, "Alper");
    SMP.addRegularUser(5, "Ali");
    SMP.addRegularUser(4, "Merve");
    SMP.addRegularUser(2, "Ferit");
    SMP.addRegularUser(2, "Burak");
    SMP.addRegularUser(6, "Ayse");
    SMP.removeRegularUser(2);
    SMP.removeRegularUser(7);
    std::cout << '\n';

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
    std::cout << '\n';

    SMP.removeRegularUser(5);
    SMP.removeContentCreator(3);
    std::cout << '\n';

    SMP.showAllContentCreators();
    std::cout << '\n';
    SMP.showAllRegularUsers();
    std::cout << '\n';
    SMP.showFollowersOf(6);
    std::cout << '\n';
    SMP.showFollowersOf(10);
    std::cout << '\n';
    SMP.showContentsOf(6);
    std::cout << '\n';
    SMP.showContentsOf(10);

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}
