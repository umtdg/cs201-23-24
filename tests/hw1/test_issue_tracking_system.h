#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>

//--------------------------------------------------------------------
#include <hw1/IssueTrackingSystem.h>
//--------------------------------------------------------------------

TEST(Employee, FindExistingIssue) {
    Employee e;
    size_t index;

    e.issues.add({ 1, "issue1", "desc1" });
    e.issues.add({ 2, "issue2", "desc2" });

    ASSERT_NE(e.findIssue(1, nullptr), nullptr);
    ASSERT_NE(e.findIssue(2, &index), nullptr);
    ASSERT_EQ(index, 1);
}

TEST(IssueTrackingSystem, AddEmployee) {
    const std::string expectedOutput = "Employees in the system:\n"
        "None\n\n"
        "Added employee Linda.\n"
        "Added employee Hakan.\n"
        "Added employee Robert.\n"
        "Added employee Michael.\n"
        "Added employee Ceren.\n\n"
        "Hakan, Research Scientist, 0 issue(s).\n"
        "Cannot show employee. There is no employee with name Efe.\n\n"
        "Employees in the system:\n"
        "Linda, ML Engineer, 0 issue(s).\n"
        "Hakan, Research Scientist, 0 issue(s).\n"
        "Robert, Research Scientist, 0 issue(s).\n"
        "Michael, Product Manager, 0 issue(s).\n"
        "Ceren, Software Engineer, 0 issue(s).\n\n"
        "Added employee Efe.\n"
        "Cannot add employee. Employee with name Linda already exists.\n\n"
        "Linda, ML Engineer, 0 issue(s).\n"
        "Efe, Human Resources Specialist, 0 issue(s).\n\n"
        "Employees in the system:\n"
        "Linda, ML Engineer, 0 issue(s).\n"
        "Hakan, Research Scientist, 0 issue(s).\n"
        "Robert, Research Scientist, 0 issue(s).\n"
        "Michael, Product Manager, 0 issue(s).\n"
        "Ceren, Software Engineer, 0 issue(s).\n"
        "Efe, Human Resources Specialist, 0 issue(s).\n";

    testing::internal::CaptureStdout();

    //--------------------------------------------------------------------
    IssueTrackingSystem ITS;

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Linda", "ML Engineer");
    ITS.addEmployee("Hakan", "Research Scientist");
    ITS.addEmployee("Robert", "Research Scientist");
    ITS.addEmployee("Michael", "Product Manager");
    ITS.addEmployee("Ceren", "Software Engineer");
    std::cout << '\n';

    ITS.showEmployee("Hakan");
    ITS.showEmployee("Efe");
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Efe", "Human Resources Specialist");
    ITS.addEmployee("Linda", "Product Manager");
    std::cout << '\n';

    ITS.showEmployee("Linda");
    ITS.showEmployee("Efe");
    std::cout << '\n';

    ITS.showAllEmployees();
    //--------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, RemoveEmployee) {
    const std::string expectedOutput = "Employees in the system:\n"
        "None\n\n"
        "Added employee Robert.\n"
        "Added employee Ceren.\n"
        "Added employee Efe.\n\n"
        "Employees in the system:\n"
        "Robert, Research Scientist, 0 issue(s).\n"
        "Ceren, Research Scientist, 0 issue(s).\n"
        "Efe, Product Manager, 0 issue(s).\n\n"
        "Removed employee Robert.\n"
        "Cannot remove employee. There is no employee with name Selin.\n\n"
        "Cannot show employee. There is no employee with name Robert.\n"
        "Ceren, Research Scientist, 0 issue(s).\n\n"
        "Employees in the system:\n"
        "Ceren, Research Scientist, 0 issue(s).\n"
        "Efe, Product Manager, 0 issue(s).\n\n"
        "Cannot add employee. Employee with name Ceren already exists.\n"
        "Added employee Hakan.\n"
        "Added employee Yusuf.\n"
        "Added employee Raymond.\n"
        "Added employee Sergen.\n\n"
        "Removed employee Hakan.\n"
        "Cannot remove employee. There is no employee with name Selin.\n"
        "Removed employee Ceren.\n"
        "Removed employee Efe.\n"
        "Removed employee Sergen.\n\n"
        "Raymond, Product Manager, 0 issue(s).\n"
        "Cannot show employee. There is no employee with name Selin.\n\n"
        "Employees in the system:\n"
        "Yusuf, Research Scientist, 0 issue(s).\n"
        "Raymond, Product Manager, 0 issue(s).\n";


    testing::internal::CaptureStdout();

    //--------------------------------------------------------------------
    IssueTrackingSystem ITS;

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Robert", "Research Scientist");
    ITS.addEmployee("Ceren", "Research Scientist");
    ITS.addEmployee("Efe", "Product Manager");
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.removeEmployee("Robert");
    ITS.removeEmployee("Selin");
    std::cout << '\n';

    ITS.showEmployee("Robert");
    ITS.showEmployee("Ceren");
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Ceren", "Software Engineer");
    ITS.addEmployee("Hakan", "ML Engineer");
    ITS.addEmployee("Yusuf", "Research Scientist");
    ITS.addEmployee("Raymond", "Product Manager");
    ITS.addEmployee("Sergen", "Research Scientist");
    std::cout << '\n';

    ITS.removeEmployee("Hakan");
    ITS.removeEmployee("Selin");
    ITS.removeEmployee("Ceren");
    ITS.removeEmployee("Efe");
    ITS.removeEmployee("Sergen");
    std::cout << '\n';

    ITS.showEmployee("Raymond");
    ITS.showEmployee("Selin");
    std::cout << '\n';

    ITS.showAllEmployees();
    //--------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, AddIssue) {
    const std::string expectedOutput = "Issues in the system:\n"
        "None\n\n"
        "Employees in the system:\n"
        "None\n\n"
        "Added employee Robert.\n"
        "Added employee Ceren.\n"
        "Added employee Efe.\n"
        "Cannot add employee. Employee with name Robert already exists.\n"
        "Added employee Merve.\n"
        "Added employee Batuhan.\n\n"
        "Employees in the system:\n"
        "Robert, Research Scientist, 0 issue(s).\n"
        "Ceren, Software Engineer, 0 issue(s).\n"
        "Efe, Product Manager, 0 issue(s).\n"
        "Merve, Research Scientist, 0 issue(s).\n"
        "Batuhan, Data Engineer, 0 issue(s).\n\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Added issue 5.\n"
        "Cannot add issue. There is no employee with name Jonathan.\n"
        "Added issue 7.\n"
        "Added issue 8.\n"
        "Added issue 9.\n"
        "Added issue 10.\n"
        "Cannot add issue. Issue with ID 8 already exists.\n"
        "Cannot add issue. There is no employee with name Jonathan.\n"
        "Cannot add issue. Issue with ID 10 already exists.\n\n"
        "Employees in the system:\n"
        "Robert, Research Scientist, 2 issue(s).\n"
        "Ceren, Software Engineer, 2 issue(s).\n"
        "Efe, Product Manager, 1 issue(s).\n"
        "Merve, Research Scientist, 2 issue(s).\n"
        "Batuhan, Data Engineer, 2 issue(s).\n\n"
        "Issues in the system:\n"
        "2, Create a new prediction algorithm for protein secondary structure using only amino acid sequence, Robert.\n"
        "10, Mine drug-target interaction data from web, Robert.\n"
        "3, Create a new Naive Bayes based language model for protein sequences, Ceren.\n"
        "9, Fix 406 Not Acceptable Error, Ceren.\n"
        "7, Code logout page, Efe.\n"
        "4, Create a novel DNA sequencing method, Merve.\n"
        "5, Plot results of the latest research experiment, Merve.\n"
        "1, Code login page, Batuhan.\n"
        "8, Fix 405 Method Not Allowed Error, Batuhan.\n\n"
        "1, Code login page, Batuhan.\n"
        "4, Create a novel DNA sequencing method, Merve.\n"
        "Cannot show issue. There is no issue with ID 6.\n";

    testing::internal::CaptureStdout();

    //--------------------------------------------------------------------
    IssueTrackingSystem ITS;

    ITS.showAllIssues();
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Robert", "Research Scientist");
    ITS.addEmployee("Ceren", "Software Engineer");
    ITS.addEmployee("Efe", "Product Manager");
    ITS.addEmployee("Robert", "Software Engineer");
    ITS.addEmployee("Merve", "Research Scientist");
    ITS.addEmployee("Batuhan", "Data Engineer");
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addIssue(1, "Code login page", "Batuhan");
    ITS.addIssue(2, "Create a new prediction algorithm for protein secondary structure using only amino acid sequence", "Robert");
    ITS.addIssue(3, "Create a new Naive Bayes based language model for protein sequences", "Ceren");
    ITS.addIssue(4, "Create a novel DNA sequencing method", "Merve");
    ITS.addIssue(5, "Plot results of the latest research experiment", "Merve");
    ITS.addIssue(6, "Fix 403 Forbidden Error", "Jonathan");
    ITS.addIssue(7, "Code logout page", "Efe");
    ITS.addIssue(8, "Fix 405 Method Not Allowed Error", "Batuhan");
    ITS.addIssue(9, "Fix 406 Not Acceptable Error", "Ceren");
    ITS.addIssue(10, "Mine drug-target interaction data from web", "Robert");
    ITS.addIssue(8, "Fix 409 Conflict", "Robert");
    ITS.addIssue(9, "Fix 410 Gone Error", "Jonathan");
    ITS.addIssue(10, "Fix 411 Length Required Error", "Robert");
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.showAllIssues();
    std::cout << '\n';

    ITS.showIssue(1);
    ITS.showIssue(4);
    ITS.showIssue(6);
    //--------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, RemoveIssue) {
    const std::string expectedOutput = "Issues in the system:\n"
        "None\n\n"
        "Employees in the system:\n"
        "None\n\n"
        "Added employee Hakan.\n"
        "Added employee Efe.\n"
        "Added employee Yusuf.\n"
        "Added employee Michael.\n"
        "Added employee Timothy.\n"
        "Added employee Alperen.\n"
        "Added employee Elif.\n"
        "Added employee Beyza.\n\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Added issue 5.\n"
        "Added issue 6.\n"
        "Added issue 7.\n"
        "Added issue 8.\n"
        "Added issue 9.\n"
        "Added issue 10.\n\n"
        "5, Deploy the app to cloud, Alperen.\n"
        "10, Present the demo to customers, Yusuf.\n\n"
        "Alperen, Software Engineer II, 2 issue(s).\n"
        "Elif, Software Engineer I, 1 issue(s).\n\n"
        "Removed issue 1.\n"
        "Removed issue 4.\n"
        "Removed issue 7.\n"
        "Removed issue 10.\n"
        "Cannot remove issue. There is no issue with ID 1.\n"
        "Cannot remove issue. There is no issue with ID 11.\n\n"
        "Cannot show issue. There is no issue with ID 0.\n"
        "Cannot show issue. There is no issue with ID 1.\n"
        "2, Code profile page, Timothy.\n"
        "3, Code search page, Beyza.\n"
        "Cannot show issue. There is no issue with ID 4.\n"
        "5, Deploy the app to cloud, Alperen.\n\n"
        "Issues in the system:\n"
        "9, Write API documentation, Efe.\n"
        "8, Code view user property, Yusuf.\n"
        "2, Code profile page, Timothy.\n"
        "6, Code browser extension, Timothy.\n"
        "5, Deploy the app to cloud, Alperen.\n"
        "3, Code search page, Beyza.\n\n"
        "Employees in the system:\n"
        "Hakan, Software Engineer II, 0 issue(s).\n"
        "Efe, Software Engineer I, 1 issue(s).\n"
        "Yusuf, Software Engineer I, 1 issue(s).\n"
        "Michael, Software Engineer I, 0 issue(s).\n"
        "Timothy, Software Engineer I, 2 issue(s).\n"
        "Alperen, Software Engineer II, 1 issue(s).\n"
        "Elif, Software Engineer I, 0 issue(s).\n"
        "Beyza, Software Engineer II, 1 issue(s).\n";

    testing::internal::CaptureStdout();

    //--------------------------------------------------------------------
    IssueTrackingSystem ITS;

    ITS.showAllIssues();
    std::cout << '\n';
    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Hakan", "Software Engineer II");
    ITS.addEmployee("Efe", "Software Engineer I");
    ITS.addEmployee("Yusuf", "Software Engineer I");
    ITS.addEmployee("Michael", "Software Engineer I");
    ITS.addEmployee("Timothy", "Software Engineer I");
    ITS.addEmployee("Alperen", "Software Engineer II");
    ITS.addEmployee("Elif", "Software Engineer I");
    ITS.addEmployee("Beyza", "Software Engineer II");
    std::cout << '\n';

    ITS.addIssue(1, "Code search page", "Elif");
    ITS.addIssue(2, "Code profile page", "Timothy");
    ITS.addIssue(3, "Code search page", "Beyza");
    ITS.addIssue(4, "Code direct messaging", "Alperen");
    ITS.addIssue(5, "Deploy the app to cloud", "Alperen");
    ITS.addIssue(6, "Code browser extension", "Timothy");
    ITS.addIssue(7, "Code mobile app", "Timothy");
    ITS.addIssue(8, "Code view user property", "Yusuf");
    ITS.addIssue(9, "Write API documentation", "Efe");
    ITS.addIssue(10, "Present the demo to customers", "Yusuf");
    std::cout << '\n';

    ITS.showIssue(5);
    ITS.showIssue(10);
    std::cout << '\n';

    ITS.showEmployee("Alperen");
    ITS.showEmployee("Elif");
    std::cout << '\n';

    ITS.removeIssue(1);
    ITS.removeIssue(4);
    ITS.removeIssue(7);
    ITS.removeIssue(10);
    ITS.removeIssue(1);
    ITS.removeIssue(11);
    std::cout << '\n';

    ITS.showIssue(0);
    ITS.showIssue(1);
    ITS.showIssue(2);
    ITS.showIssue(3);
    ITS.showIssue(4);
    ITS.showIssue(5);
    std::cout << '\n';

    ITS.showAllIssues();
    std::cout << '\n';

    ITS.showAllEmployees();
    //--------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, AllInOne) {
    const std::string expectedOutput = "Employees in the system:\n"
        "None\n\n"
        "Added employee Alper.\n"
        "Added employee Enes.\n"
        "Added employee Ayse.\n"
        "Added employee Salih.\n"
        "Cannot add employee. Employee with name Salih already exists.\n"
        "Added employee Fatma.\n"
        "Added employee Yusuf.\n"
        "Cannot remove employee. There is no employee with name Kamil.\n"
        "Removed employee Enes.\n"
        "Added employee Merve.\n"
        "Added employee Ali.\n"
        "Removed employee Ali.\n\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Added issue 5.\n"
        "Added issue 6.\n"
        "Added issue 7.\n"
        "Cannot add issue. Issue with ID 1 already exists.\n"
        "Cannot add issue. Issue with ID 2 already exists.\n"
        "Cannot remove issue. There is no issue with ID 8.\n"
        "Removed issue 1.\n\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Salih's issues are transferred to Fatma.\n"
        "Removed employee Salih.\n"
        "Cannot remove employee. Fatma has assigned issues.\n"
        "Removed issue 4.\n"
        "Removed employee Ayse.\n\n"
        "Employees in the system:\n"
        "Alper, Software Engineer, 2 issue(s).\n"
        "Fatma, Software Engineer, 2 issue(s).\n"
        "Yusuf, Cook, 0 issue(s).\n"
        "Merve, Researcher, 1 issue(s).\n\n"
        "Fatma, Software Engineer, 2 issue(s).\n\n"
        "Cannot show employee. There is no employee with name John.\n\n"
        "Issues in the system:\n"
        "6, Create robots.txt to inform crawlers, Alper.\n"
        "7, Code profile pages, Alper.\n"
        "3, Code logout page, Fatma.\n"
        "2, Code login page, Fatma.\n"
        "5, Create algorithm for new recommendation engine, Merve.\n\n"
        "Cannot show issue. There is no issue with ID 1.\n\n"
        "3, Code logout page, Fatma.\n";

    testing::internal::CaptureStdout();

    //--------------------------------------------------------------------
    IssueTrackingSystem ITS;

    ITS.showAllEmployees();
    std::cout << '\n';

    ITS.addEmployee("Alper", "Software Engineer");
    ITS.addEmployee("Enes", "Software Engineer");
    ITS.addEmployee("Ayse", "Software Engineer");
    ITS.addEmployee("Salih", "Software Engineer");
    ITS.addEmployee("Salih", "ML Engineer");
    ITS.addEmployee("Fatma", "Software Engineer");
    ITS.addEmployee("Yusuf", "Cook");
    ITS.removeEmployee("Kamil");
    ITS.removeEmployee("Enes");
    ITS.addEmployee("Merve", "Researcher");
    ITS.addEmployee("Ali", "DevOps Engineer");
    ITS.removeEmployee("Ali");
    std::cout << '\n';

    ITS.addIssue(1, "Code payment module", "Ayse");
    ITS.addIssue(2, "Code login page", "Salih");
    ITS.addIssue(3, "Code logout page", "Fatma");
    ITS.addIssue(4, "Code search engine", "Ayse");
    ITS.addIssue(5, "Create algorithm for new recommendation engine", "Merve");
    ITS.addIssue(6, "Create robots.txt to inform crawlers", "Alper");
    ITS.addIssue(7, "Code profile pages", "Alper");
    ITS.addIssue(1, "Fix image not found bug", "Merve");
    ITS.addIssue(2, "Fix login bug", "Salih");
    ITS.removeIssue(8);
    ITS.removeIssue(1);
    std::cout << '\n';

    ITS.changeAssignee("Hasan", "Huseyin");
    ITS.changeAssignee("Hasan", "Salih");
    ITS.changeAssignee("Salih", "Fatma");
    ITS.removeEmployee("Salih");
    ITS.removeEmployee("Fatma");
    ITS.removeIssue(4);
    ITS.removeEmployee("Ayse");
    std::cout << '\n';

    ITS.showAllEmployees();
    std::cout << '\n';
    ITS.showEmployee("Fatma");
    std::cout << '\n';
    ITS.showEmployee("John");
    std::cout << '\n';
    ITS.showAllIssues();
    std::cout << '\n';
    ITS.showIssue(1);
    std::cout << '\n';
    ITS.showIssue(3);
    //--------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}
