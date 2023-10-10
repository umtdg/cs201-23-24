/*
    Author: Umut Dağ
    Student ID: 21801674
    Section No: 2
*/

#include "IssueTrackingSystem.h"

#include <cstdlib>
#include <cstring>
#include <iostream>


// struct Issue
void
Issue::display() const {
    std::cout << id
        << ", " << desc
        << ", " << asignee << ".\n";
}

// struct Employee
void
Employee::display() const {
    std::cout << name
        << ", " << title
        << ", " << issues.length() << " issue(s).\n";
}

const Issue*
Employee::findIssue(int issueId, size_t *index) const {
    size_t nIssues = issues.length();
    for (size_t i = 0; i < nIssues; i++) {
        if (issues.at(i).id != issueId) continue;

        if (index) *index = i;
        return &issues.at(i);
    }

    return nullptr;
}


// class ITS

// helpers
const Employee*
IssueTrackingSystem::findEmployee(
    const std::string& name,
    size_t *index
) const {
    size_t len = employees.length();
    for (size_t i = 0; i < len; i++) {
        if (employees.at(i).name != name) continue;

        if (index) *index = i;
        return &employees.at(i);
    }

    return nullptr;
}

Employee*
IssueTrackingSystem::findEmployee(
    const std::string& name,
    size_t *index
) {
    const IssueTrackingSystem *constThis = const_cast<const IssueTrackingSystem*>(this);
    return const_cast<Employee*>(constThis->findEmployee(name, index));
}

const Issue*
IssueTrackingSystem::findIssue(
    int issueId,
    size_t *index,
    size_t *employeeIndex
) const {
    size_t nEmployees = employees.length();
    for (size_t i = 0; i < nEmployees; i++) {
        const Issue* issue = employees.at(i).findIssue(issueId, index);
        if (issue) {
            if (employeeIndex) *employeeIndex = i;

            return issue;
        }
    }

    return nullptr;
}

// employee functions
void
IssueTrackingSystem::addEmployee(
    const std::string name,
    const std::string title
) {
    if (findEmployee(name, nullptr)) {
        std::cout << "Cannot add employee. Employee with name "
            << name << " already exists.\n";
        return;
    }

    employees.add(
        { std::move(name), std::move(title), DynamicArray<Issue>{} }
    );

    std::cout << "Added employee "
        << employees.at(employees.length() - 1).name << ".\n";
}

void
IssueTrackingSystem::removeEmployee(const std::string name) {
    size_t index;
    if (!findEmployee(name, &index)) {
        std::cout << "Cannot remove employee. There is no employee with name "
            << name << ".\n";
    }

    const Employee &e = employees.at(index);
    if (e.issues.length() != 0) {
        std::cout << "Cannot remove employee. "
            << e.name << " has assigned issued.\n";
        return;
    }

    employees.remove(index);
        std::cout << "Removed employee " << name << ".\n";
}

void
IssueTrackingSystem::showAllEmployees() const {
    std::cout << "Employees in the system:\n";
    size_t len = employees.length();
    if (len == 0) {
        std::cout << "None\n";
        return;
    }

    for (size_t i = 0; i < len; i++) {
        employees.at(i).display();
    }
}

void
IssueTrackingSystem::showEmployee(const std::string name) const {
    const Employee *employee = findEmployee(name, nullptr);
    if (employee) {
        employee->display();
    } else {
        std::cout << "Cannot show employee. There is no employee with name "
            << name << ".\n";
    }
}

size_t
IssueTrackingSystem::employeeCount() const {
    return employees.length();
}

// issue functions
void
IssueTrackingSystem::addIssue(
    const int issueId,
    const std::string description,
    const std::string assigneeName
) {
    if (findIssue(issueId)) {
        std::cout << "Cannot add issue. Issue with ID "
            << issueId << " already exists.\n";
        return;
    }

    Employee* employee = findEmployee(assigneeName, nullptr);
    if (!employee) {
        std::cout << "Cannot add issue. There is no employee with name "
            << assigneeName << ".\n";
        return;
    }

    employee->issues.add(
        { issueId, description, assigneeName }
    );
    std::cout << "Added issue " << issueId << ".\n";
}

void
IssueTrackingSystem::removeIssue(const int issueId) {
    size_t issueIndex, employeeIndex;
    if (findIssue(issueId, &issueIndex, &employeeIndex)) {
        employees.at(employeeIndex).issues.remove(issueIndex);
        std::cout << "Removed issue " << issueId << ".\n";
    } else {
        std::cout << "Cannot remove issue. There is no issue with ID "
            << issueId << ".\n";
    }
}

void
IssueTrackingSystem::changeAssignee(
    const std::string previousAssignee,
    const std::string newAssignee
) {
    if (previousAssignee == newAssignee) return;

    Employee *oldEmployee = nullptr;
    Employee *newEmployee = nullptr;

    size_t nEmployees = employees.length();
    for (size_t i = 0; i < nEmployees; i++) {
        Employee& e = employees.at(i);
        if (e.name == previousAssignee) oldEmployee = &e;
        if (e.name == newAssignee) newEmployee = &e;
    }

    if (!oldEmployee || !newEmployee) {
        std::cout << "Cannot change assignee. Previous and/or new assignee does not exist.\n";
        return;
    }

    size_t nIssues = oldEmployee->issues.length();
    for (size_t i = 0; i < nIssues; i++) {
        Issue& issue = oldEmployee->issues.at(i);
        issue.asignee = newAssignee;

        newEmployee->issues.add(issue);
        oldEmployee->issues.remove(i);
    }

    std::cout << "Changed assignee from " << previousAssignee
        << " to " << newAssignee << ".\n";
}

void
IssueTrackingSystem::showIssue(const int issueId) const {
    const Issue *issue = findIssue(issueId);
    if (issue) {
        issue->display();
    } else {
        std::cout << "Cannot show issue. There is no issue with ID "
            << issueId << ".\n";
    }
}

void
IssueTrackingSystem::showAllIssues() const {
    std::cout << "Issues in the system:\n";

    size_t nEmployees = employees.length();
    if (nEmployees == 0) {
        std::cout << "None\n";
        return;
    }

    for (size_t i = 0; i < nEmployees; i++) {
        const Employee& e = employees.at(i);
        size_t nIssues = e.issues.length();
        for (size_t j = 0; j < nIssues; j++) {
            e.issues.at(j).display();
        }
    }
}
