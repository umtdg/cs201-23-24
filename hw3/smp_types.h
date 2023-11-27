/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include "sorted_list.h"

#include <iostream>
#include <ostream>
#include <string>

class SMPObject {
    protected:
        int _id;
        std::string _s;

    public:
        SMPObject(const int id, const std::string s) : _id(id), _s(std::move(s)) {}

        bool operator==(const SMPObject& other) const { return _id == other._id; }
        bool operator!=(const SMPObject& other) const { return _id != other._id; }
        bool operator<(const SMPObject& other) const { return _id < other._id; }
        bool operator>(const SMPObject& other) const { return _id > other._id; }
        bool operator<=(const SMPObject& other) const { return _id <= other._id; }
        bool operator>=(const SMPObject& other) const { return _id >= other._id; }

        int id() const { return _id; }
};

class Content : public SMPObject {
    public:
        Content(const int id, const std::string title)
            : SMPObject(id, std::move(title)) {}

        const std::string& title() const { return _s; }

        friend std::ostream& operator<<(std::ostream& os, const Content& content) {
            os << content._id << ", " << content._s;
            return os;
        }
};

class User : public SMPObject {
    public:
        User(const int id, const std::string name)
            : SMPObject(id, std::move(name)) {}

        const std::string& name() const { return _s; }

        friend std::ostream& operator<<(std::ostream& os, const User& user) {
            os << user._id << ", " << user._s;
            return os;
        }
};

class ContentCreator : public User {
    private:
        sorted_list<int> _contents;
        sorted_list<int> _followers;

    public:
        ContentCreator(const int id, const std::string name)
            : User(id, name), _contents(), _followers() {}

        friend std::ostream& operator<<(std::ostream& os, const ContentCreator& creator) {
            os << creator._id
                << ", " << creator._s
                << ", " << creator._followers.length() << " follower(s)"
                << ", " << creator._contents.length() << " content(s)";
            return os;
        }

        const sorted_list<int>& contents() const { return _contents; }

        bool addContent(const int id);
        bool removeContent(const int id);

        bool addFollower(const int id);
        bool removeFollower(const int id);

        void showFollowers() const;
        void showContents() const;
};
