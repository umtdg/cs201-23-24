/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#include "SocialMediaPlatform.h"

#include <iostream>

void SocialMediaPlatform::addRegularUser(const int id, const std::string name) {
    User user(id, std::move(name));

    if (_users.find(user) != nullptr) {
        std::cout << "Cannot add regular user. There is already a regular user with ID "
                    << id << ".\n";
        return;
    }

    _users.insert(std::move(user));
    std::cout << "Added regular user " << id << ".\n";
}

void SocialMediaPlatform::removeRegularUser(const int id) {
    if (!_users.remove(User(id, ""))) {
        std::cout << "Cannot remove regular user. There is no regular user with ID "
                    << id << ".\n";
        return;
    }

    // Remove the user from the followers list of all content creators.
    for (auto node = _creators.head(); node != nullptr; node = node->next) {
        node->value.removeFollower(id);
    }

    std::cout << "Removed regular user " << id << ".\n";
}

void SocialMediaPlatform::addContentCreator(const int id, const std::string name) {
    ContentCreator creator(id, std::move(name));

    if (_creators.find(creator) != nullptr) {
        std::cout << "Cannot add content creator. There is already a content creator with ID "
                    << id << ".\n";
        return;
    }

    _creators.insert(std::move(creator));
    std::cout << "Added content creator " << id << ".\n";
}

void SocialMediaPlatform::removeContentCreator(const int id) {
    ContentCreator creator(id, "");

    auto creatorNode = _creators.find(creator);
    if (creatorNode == nullptr) {
        std::cout << "Cannot remove content creator. There is no content creator with ID "
                    << id << ".\n";
        return;
    }

    // Remove contents of the creator
    for (auto node = creatorNode->value.contents().head(); node != nullptr; node = node->next) {
        _contents.remove(Content(node->value, ""));
    }

    _creators.remove(creator);
    std::cout << "Removed content creator " << id << ".\n";
}

void SocialMediaPlatform::addContent(const int creatorId, const int id, const std::string title) {
    if (_contents.find(Content(id, "")) != nullptr) {
        std::cout << "Cannot add content. There is already a content with ID "
                    << id << ".\n";
        return;
    }

    auto creatorNode = _creators.find(ContentCreator(creatorId, ""));
    if (creatorNode == nullptr) {
        std::cout << "Cannot add content. There is no content creator with ID "
                    << creatorId << ".\n";
        return;
    }

    Content content(id, std::move(title));
    _contents.insert(content);
    creatorNode->value.addContent(id);

    std::cout << "Added content " << id << ".\n";
}

void SocialMediaPlatform::removeContent(const int creatorId, const int id) {
    auto creatorNode = _creators.find(ContentCreator(creatorId, ""));
    if (creatorNode == nullptr) {
        std::cout << "Cannot remove content. There is no content creator with ID "
                    << creatorId << ".\n";
        return;
    }

    if (!creatorNode->value.removeContent(id)) {
        std::cout << "Cannot remove content. There is no content with ID "
                << id << " shared by content creator with ID "
                << creatorId << ".\n";
        return;
    }

    _contents.remove(Content(id, ""));
    std::cout << "Removed content " << id << ".\n";
}

void SocialMediaPlatform::followContentCreator(const int userId, const int creatorId) {
    auto userNode = _users.find(User(userId, ""));
    auto creatorNode = _creators.find(ContentCreator(creatorId, ""));

    if (userNode == nullptr || creatorNode == nullptr) {
        std::cout << "Cannot follow. Regular user and/or content creator ID does not exist.\n";
        return;
    }

    if (!creatorNode->value.addFollower(userId)) {
        std::cout << "Cannot follow. The user is already following the content creator.\n";
        return;
    }

    std::cout << "Regular user with ID " << userId
            << " followed content creator with ID " << creatorId << ".\n";
}

void SocialMediaPlatform::unfollowContentCreator(const int userId, const int creatorId) {
    auto userNode = _users.find(User(userId, ""));
    auto creatorNode = _creators.find(ContentCreator(creatorId, ""));

    if (userNode == nullptr || creatorNode == nullptr) {
        std::cout << "Cannot unfollow. Regular user and/or content creator ID does not exist.\n";
        return;
    }

    if (!creatorNode->value.removeFollower(userId)) {
        std::cout << "Cannot unfollow. The user is not following the content creator.\n";
        return;
    }

    std::cout << "Regular user with ID " << userId
            << " unfollowed content creator with ID " << creatorId << ".\n";
}

void SocialMediaPlatform::showFollowersOf(const int creatorId) const {
    auto creatorNode = _creators.find(ContentCreator(creatorId, ""));
    if (creatorNode == nullptr) {
        std::cout << "Cannot show. There is no content creator with ID "
                    << creatorId << ".\n";
        return;
    }

    creatorNode->value.showFollowers();
}

void SocialMediaPlatform::showContentsOf(const int creatorId) const {
    auto creatorNode = _creators.find(ContentCreator(creatorId, ""));
    if (creatorNode == nullptr) {
        std::cout << "Cannot show. There is no content creator with ID "
                    << creatorId << ".\n";
        return;
    }

    creatorNode->value.showContents();
}

void SocialMediaPlatform::showAllRegularUsers() const {
    std::cout << "Regular users in the social media platform:\n";
    _users.display();
}

void SocialMediaPlatform::showAllContentCreators() const {
    std::cout << "Content creators in the social media platform:\n";
    _creators.display();
}

void SocialMediaPlatform::showAllContents() const {
    std::cout << "Contents in the social media platform:\n";
    _contents.display();
}
