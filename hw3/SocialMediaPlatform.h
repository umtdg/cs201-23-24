/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include "smp_types.h"

#include <string>

class SocialMediaPlatform {
    private:
        sorted_list<User> _users;
        sorted_list<ContentCreator> _creators;
        sorted_list<Content> _contents;

    public:
        SocialMediaPlatform() = default;
        ~SocialMediaPlatform() = default;

        // rule of five
        SocialMediaPlatform(const SocialMediaPlatform&) = default;
        SocialMediaPlatform(SocialMediaPlatform&&) = default;
        SocialMediaPlatform& operator=(const SocialMediaPlatform&) = default;
        SocialMediaPlatform& operator=(SocialMediaPlatform&&) = default;

        void addRegularUser(const int id, const std::string name);
        void removeRegularUser(const int id);

        void addContentCreator(const int id, const std::string name);
        void removeContentCreator(const int id);

        void addContent(const int creatorId, const int id, const std::string title);
        void removeContent(const int creatorId, const int id);

        void followContentCreator(const int userId, const int creatorId);
        void unfollowContentCreator(const int userId, const int creatorId);

        void showFollowersOf(const int creatorId) const;
        void showContentsOf(const int creatorId) const;

        void showAllRegularUsers() const;
        void showAllContentCreators() const;
        void showAllContents() const;
};