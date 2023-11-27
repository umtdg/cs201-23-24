/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#include "smp_types.h"

bool ContentCreator::addContent(const int id) {
    if (_contents.find(id) != nullptr) {
        return false;
    }

    _contents.insert(id);
    return true;
}

bool ContentCreator::removeContent(const int id) {
    return _contents.remove(id);
}

bool ContentCreator::addFollower(const int id) {
    if (_followers.find(id) != nullptr) {
        return false;
    }

    _followers.insert(id);
    return true;
}

bool ContentCreator::removeFollower(const int id) {
    return _followers.remove(id);
}

void ContentCreator::showContents() const {
    std::cout << "Contents of content creator with ID " << _id << ":\n";
    _contents.display();
}

void ContentCreator::showFollowers() const {
    std::cout << "Regular users following content creator with ID " << _id << ":\n";
    _followers.display();
}
