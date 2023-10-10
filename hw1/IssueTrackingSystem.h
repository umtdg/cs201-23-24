/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#pragma once

#include <string>

#include "dyarray.h"

struct Issue {
    int id;
    std::string desc;
    std::string asignee;

    void display() const;
};

struct Employee {
    std::string name;
    std::string title;
    DynamicArray<Issue> issues;

    const Issue* findIssue(int issueId, size_t *index) const;

    void display() const;
};

class IssueTrackingSystem {
private:
    DynamicArray<Employee> employees;

public:
    IssueTrackingSystem() = default;
    ~IssueTrackingSystem() = default;

    IssueTrackingSystem(const IssueTrackingSystem& other) = default;
    IssueTrackingSystem(IssueTrackingSystem&& other) noexcept = default;

    IssueTrackingSystem& operator=(const IssueTrackingSystem& other) = default;
    IssueTrackingSystem& operator=(IssueTrackingSystem&& other) noexcept = default;

    void addEmployee(const std::string name, const std::string title);
    void removeEmployee(const std::string name);
    void addIssue(
        const int issueId,
        const std::string description,
        const std::string assigneeName
    );
    void removeIssue(const int issueId);
    void changeAssignee(
        const std::string previousAssignee,
        const std::string newAssignee
    );

    void showAllEmployees() const;
    void showAllIssues() const;
    void showEmployee(const std::string name) const;
    void showIssue(const int issueId) const;

    size_t employeeCount() const;

private:
    const Employee* findEmployee(
        const std::string& name,
        size_t *index
    ) const;
    Employee* findEmployee(
        const std::string& name,
        size_t *index
    );
    const Issue* findIssue(
        int issueId,
        size_t *index = nullptr,
        size_t *employeeIndex = nullptr
    ) const;
};