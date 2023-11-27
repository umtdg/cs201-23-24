#include <smp_types.h>
#include <SocialMediaPlatform.h>
#include <sorted_list.h>

#include <iostream>

#define println() std::cout << '\n'

int main() {
    SocialMediaPlatform smp;

    smp.showAllRegularUsers();
    println();
    smp.showAllContentCreators();
    println();

    smp.addContentCreator(3, "Lonely Artist");
    smp.addContentCreator(2, "Eater Man");
    smp.addContentCreator(4, "Pet Lover");
    smp.removeContentCreator(4);
    smp.removeContentCreator(4);
    smp.addContentCreator(4, "Musician Guy");
    smp.addContentCreator(4, "Cyborg");
    smp.addContentCreator(1, "Gamer");
    smp.addContentCreator(6, "News");
    println();

    smp.addContent(3, 1, "How to perform art?");
    smp.addContent(4, 2, "My favourite song");
    smp.addContent(2, 2, "Best Recipe Ever");
    smp.addContent(6, 5, "News of October");
    smp.addContent(6, 6, "News of November");
    smp.addContent(6, 8, "News of December");
    smp.addContent(6, 13, "News of 2023");
    smp.removeContent(6, 5);
    smp.removeContent(10, 7);
    smp.removeContent(6, 7);

    smp.showAllContentCreators();
    println();
    smp.showAllContents();
    println();

    smp.addRegularUser( 1, "Alper" );
    smp.addRegularUser( 5, "Ali" );
    smp.addRegularUser( 4, "Merve" );
    smp.addRegularUser( 2, "Ferit" );
    smp.addRegularUser( 2, "Burak" );
    smp.addRegularUser( 6, "Ayse" );
    smp.removeRegularUser( 2 );
    smp.removeRegularUser( 7 );
    println();

    smp.followContentCreator(1,6);
    smp.followContentCreator(1,2);
    smp.followContentCreator(1,1);
    smp.followContentCreator(4,4);
    smp.followContentCreator(4,3);
    smp.followContentCreator(6,4);
    smp.followContentCreator(6,6);
    smp.followContentCreator(6,3);
    smp.followContentCreator(5,3);
    smp.followContentCreator(5,1);
    smp.followContentCreator(1,7);
    smp.followContentCreator(10,1);
    smp.followContentCreator(10,10);
    smp.unfollowContentCreator(1,7);
    smp.unfollowContentCreator(10,1);
    smp.unfollowContentCreator(10,10);
    smp.unfollowContentCreator(1,3);
    smp.unfollowContentCreator(6,4);
    println();

    smp.removeRegularUser(5);
    smp.removeContentCreator(3);
    println();

    smp.showAllContents();
    println();
    smp.showAllContentCreators();
    println();
    smp.showAllRegularUsers();
    println();

    smp.showFollowersOf(6);
    println();
    smp.showFollowersOf(10);
    println();
    smp.showContentsOf(6);
    println();
    smp.showContentsOf(10);

    return 0;
}
