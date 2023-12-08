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

TEST(IssueTrackingSystem, Random1) {
    const std::string expectedOutput = "Added employee employee9.\n"
        "Added employee employee14.\n"
        "Added employee employee13.\n"
        "Added employee employee6.\n"
        "Cannot add employee. Employee with name employee6 already exists.\n"
        "Added employee employee10.\n"
        "Added employee employee1.\n"
        "Added employee employee11.\n"
        "Added employee employee5.\n"
        "Added employee employee7.\n"
        "Added employee employee4.\n"
        "Cannot add employee. Employee with name employee5 already exists.\n"
        "Employees in the system:\n"
        "employee9, Software Engineer, 0 issue(s).\n"
        "employee14, Product Manager, 0 issue(s).\n"
        "employee13, Product Manager, 0 issue(s).\n"
        "employee6, Human Resources Specialist, 0 issue(s).\n"
        "employee10, ML Engineer, 0 issue(s).\n"
        "employee1, UX Researcher, 0 issue(s).\n"
        "employee11, Human Resources Specialist, 0 issue(s).\n"
        "employee5, UX Researcher, 0 issue(s).\n"
        "employee7, Human Resources Specialist, 0 issue(s).\n"
        "employee4, Product Manager, 0 issue(s).\n\n"
        "Cannot remove employee. There is no employee with name employee12.\n"
        "Cannot remove employee. There is no employee with name employee8.\n"
        "Removed employee employee7.\n"
        "Added issue 0.\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Cannot add issue. There is no employee with name employee2.\n"
        "Cannot add issue. There is no employee with name employee8.\n"
        "Added issue 5.\n"
        "Cannot add issue. There is no employee with name employee0.\n"
        "Added issue 7.\n"
        "Added issue 8.\n"
        "Added issue 9.\n"
        "Cannot add issue. There is no employee with name employee2.\n"
        "Added issue 11.\n"
        "Cannot add issue. There is no employee with name employee12.\n"
        "Added issue 13.\n"
        "Cannot add issue. There is no employee with name employee12.\n"
        "Cannot add issue. There is no employee with name employee12.\n"
        "Added issue 16.\n"
        "Cannot add issue. There is no employee with name employee12.\n"
        "Added issue 18.\n"
        "Added issue 19.\n"
        "Issues in the system:\n"
        "1, description1, employee9.\n"
        "13, description13, employee9.\n"
        "5, description5, employee14.\n"
        "9, description9, employee14.\n"
        "11, description11, employee14.\n"
        "7, description7, employee13.\n"
        "2, description2, employee6.\n"
        "8, description8, employee6.\n"
        "16, description16, employee6.\n"
        "18, description18, employee6.\n"
        "19, description19, employee6.\n"
        "0, description0, employee5.\n\n"
        "Removed issue 0.\n"
        "Removed issue 1.\n"
        "Removed issue 2.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "employee14's issues are transferred to employee4.\n"
        "Cannot remove employee. employee4 has assigned issues.\n"
        "Removed employee employee1.\n"
        "Removed employee employee10.\n"
        "Cannot remove employee. There is no employee with name employee3.\n"
        "Cannot remove employee. There is no employee with name employee12.\n"
        "Cannot remove employee. There is no employee with name employee3.\n"
        "Removed employee employee11.\n"
        "Cannot remove employee. employee9 has assigned issues.\n"
        "Cannot remove employee. There is no employee with name employee10.\n"
        "Cannot remove employee. employee6 has assigned issues.\n"
        "Cannot remove employee. employee4 has assigned issues.\n"
        "Removed employee employee5.\n"
        "Cannot remove employee. There is no employee with name employee1.\n"
        "Cannot remove employee. There is no employee with name employee12.\n"
        "Cannot remove employee. There is no employee with name employee0.\n"
        "Employees in the system:\n"
        "employee9, Software Engineer, 1 issue(s).\n"
        "employee14, Product Manager, 0 issue(s).\n"
        "employee13, Product Manager, 1 issue(s).\n"
        "employee6, Human Resources Specialist, 4 issue(s).\n"
        "employee4, Product Manager, 3 issue(s).\n\n"
        "Issues in the system:\n"
        "13, description13, employee9.\n"
        "7, description7, employee13.\n"
        "8, description8, employee6.\n"
        "16, description16, employee6.\n"
        "18, description18, employee6.\n"
        "19, description19, employee6.\n"
        "5, description5, employee4.\n"
        "9, description9, employee4.\n"
        "11, description11, employee4.\n";

    // --------------------------------------------------------------------

    testing::internal::CaptureStdout();

    IssueTrackingSystem ITS;
	ITS.addEmployee("employee9", "Software Engineer");
	ITS.addEmployee("employee14", "Product Manager");
	ITS.addEmployee("employee13", "Product Manager");
	ITS.addEmployee("employee6", "Human Resources Specialist");
	ITS.addEmployee("employee6", "Research Scientist");
	ITS.addEmployee("employee10", "ML Engineer");
	ITS.addEmployee("employee1", "UX Researcher");
	ITS.addEmployee("employee11", "Human Resources Specialist");
	ITS.addEmployee("employee5", "UX Researcher");
	ITS.addEmployee("employee7", "Human Resources Specialist");
	ITS.addEmployee("employee4", "Product Manager");
	ITS.addEmployee("employee5", "UX Researcher");
	ITS.showAllEmployees();
	std::cout << std::endl;
	ITS.removeEmployee("employee12");
	ITS.removeEmployee("employee8");
	ITS.removeEmployee("employee7");
	ITS.addIssue(0, "description0", "employee5");
	ITS.addIssue(1, "description1", "employee9");
	ITS.addIssue(2, "description2", "employee6");
	ITS.addIssue(3, "description3", "employee2");
	ITS.addIssue(4, "description4", "employee8");
	ITS.addIssue(5, "description5", "employee14");
	ITS.addIssue(6, "description6", "employee0");
	ITS.addIssue(7, "description7", "employee13");
	ITS.addIssue(8, "description8", "employee6");
	ITS.addIssue(9, "description9", "employee14");
	ITS.addIssue(10, "description10", "employee2");
	ITS.addIssue(11, "description11", "employee14");
	ITS.addIssue(12, "description12", "employee12");
	ITS.addIssue(13, "description13", "employee9");
	ITS.addIssue(14, "description14", "employee12");
	ITS.addIssue(15, "description15", "employee12");
	ITS.addIssue(16, "description16", "employee6");
	ITS.addIssue(17, "description17", "employee12");
	ITS.addIssue(18, "description18", "employee6");
	ITS.addIssue(19, "description19", "employee6");
	ITS.showAllIssues();
	std::cout << std::endl;
	ITS.removeIssue(0);
	ITS.removeIssue(1);
	ITS.removeIssue(2);
	ITS.changeAssignee("employee0", "employee1");
	ITS.changeAssignee("employee14", "employee4");
	ITS.removeEmployee("employee4");
	ITS.removeEmployee("employee1");
	ITS.removeEmployee("employee10");
	ITS.removeEmployee("employee3");
	ITS.removeEmployee("employee12");
	ITS.removeEmployee("employee3");
	ITS.removeEmployee("employee11");
	ITS.removeEmployee("employee9");
	ITS.removeEmployee("employee10");
	ITS.removeEmployee("employee6");
	ITS.removeEmployee("employee4");
	ITS.removeEmployee("employee5");
	ITS.removeEmployee("employee1");
	ITS.removeEmployee("employee12");
	ITS.removeEmployee("employee0");
	ITS.showAllEmployees();
	std::cout << std::endl;
	ITS.showAllIssues();

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, Random2) {
    const std::string expectedOutput = "Added employee employee11.\n"
        "Added employee employee6.\n"
        "Added employee employee1.\n"
        "Added employee employee10.\n"
        "Added employee employee3.\n"
        "Added employee employee2.\n"
        "Cannot add employee. Employee with name employee11 already exists.\n"
        "Added employee employee7.\n"
        "Cannot add employee. Employee with name employee1 already exists.\n"
        "Added employee employee4.\n"
        "Cannot add employee. Employee with name employee2 already exists.\n"
        "Added employee employee14.\n"
        "Cannot add employee. Employee with name employee1 already exists.\n"
        "Added employee employee5.\n"
        "Added employee employee8.\n"
        "Cannot add employee. Employee with name employee5 already exists.\n"
        "Cannot add employee. Employee with name employee2 already exists.\n"
        "Cannot add employee. Employee with name employee5 already exists.\n"
        "Employees in the system:\n"
        "employee11, Human Resources Specialist, 0 issue(s).\n"
        "employee6, Product Manager, 0 issue(s).\n"
        "employee1, ML Engineer, 0 issue(s).\n"
        "employee10, Research Scientist, 0 issue(s).\n"
        "employee3, Research Scientist, 0 issue(s).\n"
        "employee2, Human Resources Specialist, 0 issue(s).\n"
        "employee7, UX Researcher, 0 issue(s).\n"
        "employee4, Human Resources Specialist, 0 issue(s).\n"
        "employee14, UX Researcher, 0 issue(s).\n"
        "employee5, Human Resources Specialist, 0 issue(s).\n"
        "employee8, Research Scientist, 0 issue(s).\n\n"
        "Cannot remove employee. There is no employee with name employee12.\n"
        "Removed employee employee8.\n"
        "Cannot remove employee. There is no employee with name employee9.\n"
        "Cannot add issue. There is no employee with name employee13.\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Cannot add issue. There is no employee with name employee0.\n"
        "Added issue 6.\n"
        "Added issue 7.\n"
        "Cannot add issue. There is no employee with name employee12.\n"
        "Added issue 9.\n"
        "Added issue 10.\n"
        "Added issue 11.\n"
        "Added issue 12.\n"
        "Cannot add issue. There is no employee with name employee9.\n"
        "Added issue 14.\n"
        "Added issue 15.\n"
        "Cannot add issue. There is no employee with name employee12.\n"
        "Added issue 17.\n"
        "Added issue 18.\n"
        "Added issue 19.\n"
        "Issues in the system:\n"
        "7, description7, employee11.\n"
        "9, description9, employee11.\n"
        "1, description1, employee6.\n"
        "10, description10, employee6.\n"
        "11, description11, employee6.\n"
        "19, description19, employee1.\n"
        "2, description2, employee10.\n"
        "12, description12, employee10.\n"
        "18, description18, employee10.\n"
        "3, description3, employee3.\n"
        "17, description17, employee2.\n"
        "4, description4, employee7.\n"
        "15, description15, employee4.\n"
        "6, description6, employee14.\n"
        "14, description14, employee14.\n\n"
        "Cannot remove issue. There is no issue with ID 0.\n"
        "Removed issue 1.\n"
        "Removed issue 2.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "employee14's issues are transferred to employee1.\n"
        "employee10's issues are transferred to employee1.\n"
        "employee14's issues are transferred to employee1.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "employee3's issues are transferred to employee1.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "employee4's issues are transferred to employee1.\n"
        "employee11's issues are transferred to employee1.\n"
        "employee6's issues are transferred to employee1.\n"
        "employee5's issues are transferred to employee1.\n"
        "employee14's issues are transferred to employee1.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "employee3's issues are transferred to employee1.\n"
        "employee10's issues are transferred to employee1.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Removed employee employee5.\n"
        "Cannot remove employee. There is no employee with name employee8.\n"
        "Cannot remove employee. There is no employee with name employee13.\n"
        "Cannot remove employee. employee7 has assigned issues.\n"
        "Removed employee employee14.\n"
        "Cannot remove employee. employee7 has assigned issues.\n"
        "Cannot remove employee. employee2 has assigned issues.\n"
        "Cannot remove employee. There is no employee with name employee8.\n"
        "Removed employee employee3.\n"
        "Cannot remove employee. There is no employee with name employee8.\n"
        "Cannot remove employee. There is no employee with name employee13.\n"
        "Cannot remove employee. There is no employee with name employee14.\n"
        "Cannot remove employee. There is no employee with name employee14.\n"
        "Removed employee employee6.\n"
        "Cannot remove employee. There is no employee with name employee6.\n"
        "Cannot remove employee. There is no employee with name employee13.\n"
        "Removed employee employee10.\n"
        "Cannot remove employee. There is no employee with name employee13.\n"
        "Cannot remove employee. employee2 has assigned issues.\n"
        "Cannot remove employee. employee2 has assigned issues.\n"
        "Employees in the system:\n"
        "employee11, Human Resources Specialist, 0 issue(s).\n"
        "employee1, ML Engineer, 11 issue(s).\n"
        "employee2, Human Resources Specialist, 1 issue(s).\n"
        "employee7, UX Researcher, 1 issue(s).\n"
        "employee4, Human Resources Specialist, 0 issue(s).\n\n"
        "Issues in the system:\n"
        "19, description19, employee1.\n"
        "6, description6, employee1.\n"
        "14, description14, employee1.\n"
        "12, description12, employee1.\n"
        "18, description18, employee1.\n"
        "3, description3, employee1.\n"
        "15, description15, employee1.\n"
        "7, description7, employee1.\n"
        "9, description9, employee1.\n"
        "10, description10, employee1.\n"
        "11, description11, employee1.\n"
        "17, description17, employee2.\n"
        "4, description4, employee7.\n\n"
        "7, description7, employee1.\n"
        "18, description18, employee1.\n"
        "6, description6, employee1.\n"
        "19, description19, employee1.\n\n"
        "Cannot show employee. There is no employee with name employee0.\n"
        "employee1, ML Engineer, 11 issue(s).\n"
        "employee2, Human Resources Specialist, 1 issue(s).\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    IssueTrackingSystem ITS;
	ITS.addEmployee("employee11", "Human Resources Specialist");
	ITS.addEmployee("employee6", "Product Manager");
	ITS.addEmployee("employee1", "ML Engineer");
	ITS.addEmployee("employee10", "Research Scientist");
	ITS.addEmployee("employee3", "Research Scientist");
	ITS.addEmployee("employee2", "Human Resources Specialist");
	ITS.addEmployee("employee11", "Product Manager");
	ITS.addEmployee("employee7", "UX Researcher");
	ITS.addEmployee("employee1", "Human Resources Specialist");
	ITS.addEmployee("employee4", "Human Resources Specialist");
	ITS.addEmployee("employee2", "Software Engineer");
	ITS.addEmployee("employee14", "UX Researcher");
	ITS.addEmployee("employee1", "Research Scientist");
	ITS.addEmployee("employee5", "Human Resources Specialist");
	ITS.addEmployee("employee8", "Research Scientist");
	ITS.addEmployee("employee5", "Research Scientist");
	ITS.addEmployee("employee2", "Human Resources Specialist");
	ITS.addEmployee("employee5", "UX Researcher");
	ITS.showAllEmployees();
	std::cout << std::endl;
	ITS.removeEmployee("employee12");
	ITS.removeEmployee("employee8");
	ITS.removeEmployee("employee9");
	ITS.addIssue(0, "description0", "employee13");
	ITS.addIssue(1, "description1", "employee6");
	ITS.addIssue(2, "description2", "employee10");
	ITS.addIssue(3, "description3", "employee3");
	ITS.addIssue(4, "description4", "employee7");
	ITS.addIssue(5, "description5", "employee0");
	ITS.addIssue(6, "description6", "employee14");
	ITS.addIssue(7, "description7", "employee11");
	ITS.addIssue(8, "description8", "employee12");
	ITS.addIssue(9, "description9", "employee11");
	ITS.addIssue(10, "description10", "employee6");
	ITS.addIssue(11, "description11", "employee6");
	ITS.addIssue(12, "description12", "employee10");
	ITS.addIssue(13, "description13", "employee9");
	ITS.addIssue(14, "description14", "employee14");
	ITS.addIssue(15, "description15", "employee4");
	ITS.addIssue(16, "description16", "employee12");
	ITS.addIssue(17, "description17", "employee2");
	ITS.addIssue(18, "description18", "employee10");
	ITS.addIssue(19, "description19", "employee1");
	ITS.showAllIssues();
	std::cout << std::endl;
	ITS.removeIssue(0);
	ITS.removeIssue(1);
	ITS.removeIssue(2);
	ITS.changeAssignee("employee5", "employee0");
	ITS.changeAssignee("employee14", "employee1");
	ITS.changeAssignee("employee10", "employee1");
	ITS.changeAssignee("employee14", "employee1");
	ITS.changeAssignee("employee6", "employee0");
	ITS.changeAssignee("employee13", "employee1");
	ITS.changeAssignee("employee3", "employee1");
	ITS.changeAssignee("employee12", "employee1");
	ITS.changeAssignee("employee4", "employee1");
	ITS.changeAssignee("employee11", "employee1");
	ITS.changeAssignee("employee6", "employee1");
	ITS.changeAssignee("employee5", "employee1");
	ITS.changeAssignee("employee14", "employee1");
	ITS.changeAssignee("employee0", "employee1");
	ITS.changeAssignee("employee3", "employee1");
	ITS.changeAssignee("employee10", "employee1");
	ITS.changeAssignee("employee10", "employee0");
	ITS.changeAssignee("employee0", "employee1");
	ITS.changeAssignee("employee8", "employee0");
	ITS.changeAssignee("employee5", "employee0");
	ITS.removeEmployee("employee5");
	ITS.removeEmployee("employee8");
	ITS.removeEmployee("employee13");
	ITS.removeEmployee("employee7");
	ITS.removeEmployee("employee14");
	ITS.removeEmployee("employee7");
	ITS.removeEmployee("employee2");
	ITS.removeEmployee("employee8");
	ITS.removeEmployee("employee3");
	ITS.removeEmployee("employee8");
	ITS.removeEmployee("employee13");
	ITS.removeEmployee("employee14");
	ITS.removeEmployee("employee14");
	ITS.removeEmployee("employee6");
	ITS.removeEmployee("employee6");
	ITS.removeEmployee("employee13");
	ITS.removeEmployee("employee10");
	ITS.removeEmployee("employee13");
	ITS.removeEmployee("employee2");
	ITS.removeEmployee("employee2");
	ITS.showAllEmployees();
	std::cout << std::endl;
	ITS.showAllIssues();
	std::cout << std::endl;
	ITS.showIssue(7);
	ITS.showIssue(18);
	ITS.showIssue(6);
	ITS.showIssue(19);
	std::cout << std::endl;
	ITS.showEmployee("employee0");
	ITS.showEmployee("employee1");
	ITS.showEmployee("employee2");

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, Mixed5) {
    const std::string expectedOutput = "\nAdded employee Employee1.\n"
        "Added employee Employee2.\n"
        "Added employee Employee3.\n"
        "Added employee Employee4.\n"
        "Added employee Employee5.\n"
        "Added employee Employee6.\n"
        "Added employee Employee7.\n"
        "Added employee Employee8.\n"
        "Added employee Employee9.\n"
        "Added employee Employee10.\n"
        "Cannot add employee. Employee with name Employee5 already exists.\n"
        "Cannot add employee. Employee with name Employee8 already exists.\n"
        "Cannot add employee. Employee with name Employee1 already exists.\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Added issue 5.\n"
        "Added issue 6.\n"
        "Added issue 7.\n"
        "Added issue 8.\n"
        "Added issue 9.\n"
        "Added issue 10.\n"
        "Added issue 11.\n"
        "Added issue 12.\n"
        "Added issue 13.\n"
        "Added issue 14.\n"
        "Added issue 15.\n"
        "Added issue 16.\n"
        "Added issue 17.\n"
        "Added issue 18.\n"
        "Added issue 19.\n"
        "Added issue 20.\n"
        "Added issue 21.\n"
        "Added issue 22.\n"
        "Added issue 23.\n"
        "Added issue 24.\n"
        "Added issue 25.\n"
        "Added issue 26.\n"
        "Added issue 27.\n"
        "Added issue 28.\n"
        "Added issue 29.\n"
        "Added issue 30.\n"
        "Added issue 31.\n"
        "Added issue 32.\n"
        "Added issue 33.\n"
        "Added issue 34.\n"
        "Added issue 35.\n"
        "Added issue 36.\n"
        "Added issue 37.\n"
        "Added issue 38.\n"
        "Added issue 39.\n"
        "Added issue 40.\n"
        "Added issue 41.\n"
        "Added issue 42.\n"
        "Added issue 43.\n"
        "Added issue 44.\n"
        "Added issue 45.\n"
        "Added issue 46.\n"
        "Added issue 47.\n"
        "Added issue 48.\n"
        "Added issue 49.\n"
        "Added issue 50.\n"
        "Cannot remove employee. Employee10 has assigned issues.\n"
        "Employee1's issues are transferred to Employee2.\n"
        "Employee2's issues are transferred to Employee3.\n"
        "Employee3's issues are transferred to Employee4.\n"
        "Employee4's issues are transferred to Employee5.\n"
        "Employee5's issues are transferred to Employee6.\n"
        "Employee6's issues are transferred to Employee7.\n"
        "Employee7's issues are transferred to Employee8.\n"
        "Employee8's issues are transferred to Employee9.\n"
        "Employee9's issues are transferred to Employee1.\n"
        "Employee1's issues are transferred to Employee2.\n"
        "Employee2's issues are transferred to Employee3.\n"
        "Employee3's issues are transferred to Employee4.\n"
        "Employee4's issues are transferred to Employee5.\n"
        "Employee5's issues are transferred to Employee6.\n"
        "Employee6's issues are transferred to Employee7.\n"
        "Employee7's issues are transferred to Employee8.\n"
        "Employee8's issues are transferred to Employee9.\n"
        "Employee9's issues are transferred to Employee1.\n"
        "Employee1's issues are transferred to Employee2.\n"
        "Employee2's issues are transferred to Employee3.\n"
        "Employee3's issues are transferred to Employee4.\n"
        "Employee4's issues are transferred to Employee5.\n"
        "Employee5's issues are transferred to Employee6.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 0 issue(s).\n"
        "Employee2, Title2, 0 issue(s).\n"
        "Employee3, Title1, 0 issue(s).\n"
        "Employee4, Title2, 0 issue(s).\n"
        "Employee5, Title2, 0 issue(s).\n"
        "Employee6, Title1, 45 issue(s).\n"
        "Employee7, Title2, 0 issue(s).\n"
        "Employee8, Title2, 0 issue(s).\n"
        "Employee9, Title2, 0 issue(s).\n"
        "Employee10, Title2, 5 issue(s).\n\n"
        "Issues in the system:\n"
        "41, Description41, Employee6.\n"
        "42, Description42, Employee6.\n"
        "43, Description43, Employee6.\n"
        "44, Description44, Employee6.\n"
        "45, Description45, Employee6.\n"
        "36, Description36, Employee6.\n"
        "37, Description37, Employee6.\n"
        "38, Description38, Employee6.\n"
        "39, Description39, Employee6.\n"
        "40, Description40, Employee6.\n"
        "31, Description31, Employee6.\n"
        "32, Description32, Employee6.\n"
        "33, Description33, Employee6.\n"
        "34, Description34, Employee6.\n"
        "35, Description35, Employee6.\n"
        "26, Description26, Employee6.\n"
        "27, Description27, Employee6.\n"
        "28, Description28, Employee6.\n"
        "29, Description29, Employee6.\n"
        "30, Description30, Employee6.\n"
        "21, Description21, Employee6.\n"
        "22, Description22, Employee6.\n"
        "23, Description23, Employee6.\n"
        "24, Description24, Employee6.\n"
        "25, Description25, Employee6.\n"
        "16, Description16, Employee6.\n"
        "17, Description17, Employee6.\n"
        "18, Description18, Employee6.\n"
        "19, Description19, Employee6.\n"
        "20, Description20, Employee6.\n"
        "11, Description11, Employee6.\n"
        "12, Description12, Employee6.\n"
        "13, Description13, Employee6.\n"
        "14, Description14, Employee6.\n"
        "15, Description15, Employee6.\n"
        "6, Description6, Employee6.\n"
        "7, Description7, Employee6.\n"
        "8, Description8, Employee6.\n"
        "9, Description9, Employee6.\n"
        "10, Description10, Employee6.\n"
        "1, Description1, Employee6.\n"
        "2, Description2, Employee6.\n"
        "3, Description3, Employee6.\n"
        "4, Description4, Employee6.\n"
        "5, Description5, Employee6.\n"
        "46, Description46, Employee10.\n"
        "47, Description47, Employee10.\n"
        "48, Description48, Employee10.\n"
        "49, Description49, Employee10.\n"
        "50, Description50, Employee10.\n\n"
        "Removed employee Employee8.\n"
        "Removed employee Employee5.\n"
        "Removed employee Employee3.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 0 issue(s).\n"
        "Employee2, Title2, 0 issue(s).\n"
        "Employee4, Title2, 0 issue(s).\n"
        "Employee6, Title1, 45 issue(s).\n"
        "Employee7, Title2, 0 issue(s).\n"
        "Employee9, Title2, 0 issue(s).\n"
        "Employee10, Title2, 5 issue(s).\n\n";


    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    IssueTrackingSystem ITS;

    std::cout << std::endl;

    ITS.addEmployee("Employee1", "Title1");
    ITS.addEmployee("Employee2", "Title2");
    ITS.addEmployee("Employee3", "Title1");
    ITS.addEmployee("Employee4", "Title2");
    ITS.addEmployee("Employee5", "Title2");
    ITS.addEmployee("Employee6", "Title1");
    ITS.addEmployee("Employee7", "Title2");
    ITS.addEmployee("Employee8", "Title2");
    ITS.addEmployee("Employee9", "Title2");
    ITS.addEmployee("Employee10", "Title2");

    ITS.addEmployee("Employee5", "Title2");
    ITS.addEmployee("Employee8", "Title2");
    ITS.addEmployee("Employee1", "Title2");

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 5; j++)
        {
            int id = (i * 5) + 1 + j;
            std::string id_as_string = std::to_string(id);

            ITS.addIssue(id, "Description" + id_as_string, "Employee" + std::to_string(i + 1));
        }

    ITS.removeEmployee("Employee10");

    for (int i = 1; i <= 23; i++)
    {
        int id = i % 9;
        if (id == 0) id=9;

        std::string employee_str = "Employee" + std::to_string(id);

        int following_id = (i + 1) % 9;
        if (following_id == 0) following_id=9;

        std::string next_employee_str = "Employee" + std::to_string(following_id);
        ITS.changeAssignee(employee_str, next_employee_str);
    }

    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();
    std::cout << std::endl;

    ITS.removeEmployee("Employee8");
    ITS.removeEmployee("Employee5");
    ITS.removeEmployee("Employee3");

    ITS.showAllEmployees();
    std::cout << std::endl;

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, Mixed6) {
    const std::string expectedOutput = "\nAdded employee Employee1.\n"
        "Added employee Employee2.\n"
        "Added employee Employee3.\n"
        "Added employee Employee4.\n"
        "Added employee Employee5.\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Added issue 5.\n"
        "Added issue 6.\n"
        "Added issue 7.\n"
        "Added issue 8.\n"
        "Added issue 9.\n"
        "Added issue 10.\n"
        "Added issue 11.\n"
        "Added issue 12.\n"
        "Added issue 13.\n"
        "Added issue 14.\n"
        "Added issue 15.\n"
        "Added issue 16.\n"
        "Added issue 17.\n"
        "Added issue 18.\n"
        "Added issue 19.\n"
        "Added issue 20.\n"
        "Added issue 21.\n"
        "Added issue 22.\n"
        "Added issue 23.\n"
        "Added issue 24.\n"
        "Added issue 25.\n"
        "Removed issue 13.\n"
        "Removed issue 12.\n"
        "Removed issue 11.\n"
        "Employee3, Title1, 2 issue(s).\n"
        "Removed issue 14.\n"
        "Removed issue 15.\n"
        "Removed employee Employee3.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 5 issue(s).\n"
        "Employee2, Title2, 5 issue(s).\n"
        "Employee4, Title2, 5 issue(s).\n"
        "Employee5, Title2, 5 issue(s).\n\n"
        "Issues in the system:\n"
        "1, Description1, Employee1.\n"
        "2, Description2, Employee1.\n"
        "3, Description3, Employee1.\n"
        "4, Description4, Employee1.\n"
        "5, Description5, Employee1.\n"
        "6, Description6, Employee2.\n"
        "7, Description7, Employee2.\n"
        "8, Description8, Employee2.\n"
        "9, Description9, Employee2.\n"
        "10, Description10, Employee2.\n"
        "16, Description16, Employee4.\n"
        "17, Description17, Employee4.\n"
        "18, Description18, Employee4.\n"
        "19, Description19, Employee4.\n"
        "20, Description20, Employee4.\n"
        "21, Description21, Employee5.\n"
        "22, Description22, Employee5.\n"
        "23, Description23, Employee5.\n"
        "24, Description24, Employee5.\n"
        "25, Description25, Employee5.\n\n"
        "Removed issue 18.\n"
        "Removed issue 17.\n"
        "Removed issue 16.\n"
        "Removed issue 19.\n"
        "Employee4, Title2, 1 issue(s).\n"
        "Removed issue 20.\n"
        "Removed employee Employee4.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 5 issue(s).\n"
        "Employee2, Title2, 5 issue(s).\n"
        "Employee5, Title2, 5 issue(s).\n\n"
        "Issues in the system:\n"
        "1, Description1, Employee1.\n"
        "2, Description2, Employee1.\n"
        "3, Description3, Employee1.\n"
        "4, Description4, Employee1.\n"
        "5, Description5, Employee1.\n"
        "6, Description6, Employee2.\n"
        "7, Description7, Employee2.\n"
        "8, Description8, Employee2.\n"
        "9, Description9, Employee2.\n"
        "10, Description10, Employee2.\n"
        "21, Description21, Employee5.\n"
        "22, Description22, Employee5.\n"
        "23, Description23, Employee5.\n"
        "24, Description24, Employee5.\n"
        "25, Description25, Employee5.\n\n"
        "Cannot change assignee. Previous or/and new assignee does not exist.\n"
        "Removed issue 8.\n"
        "Employee2, Title2, 4 issue(s).\n"
        "Removed issue 7.\n"
        "Removed issue 6.\n"
        "Removed issue 9.\n"
        "Removed issue 10.\n"
        "Removed employee Employee2.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 5 issue(s).\n"
        "Employee5, Title2, 5 issue(s).\n\n"
        "Issues in the system:\n"
        "1, Description1, Employee1.\n"
        "2, Description2, Employee1.\n"
        "3, Description3, Employee1.\n"
        "4, Description4, Employee1.\n"
        "5, Description5, Employee1.\n"
        "21, Description21, Employee5.\n"
        "22, Description22, Employee5.\n"
        "23, Description23, Employee5.\n"
        "24, Description24, Employee5.\n"
        "25, Description25, Employee5.\n\n"
        "Employee5's issues are transferred to Employee1.\n"
        "Removed issue 23.\n"
        "Removed issue 22.\n"
        "Removed issue 21.\n"
        "Removed issue 24.\n"
        "Removed issue 25.\n"
        "Employee5, Title2, 0 issue(s).\n"
        "Removed employee Employee5.\n"
        "Cannot show employee. There is no employee with name Employee5.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 5 issue(s).\n\n"
        "Issues in the system:\n"
        "1, Description1, Employee1.\n"
        "2, Description2, Employee1.\n"
        "3, Description3, Employee1.\n"
        "4, Description4, Employee1.\n"
        "5, Description5, Employee1.\n\n"
        "Removed issue 2.\n"
        "Employee1, Title1, 4 issue(s).\n"
        "Removed issue 1.\n"
        "Removed issue 3.\n"
        "Removed issue 5.\n"
        "Removed issue 4.\n"
        "Removed employee Employee1.\n"
        "Cannot show employee. There is no employee with name Employee1.\n"
        "Employees in the system:\n"
        "None\n\n"
        "Issues in the system:\n"
        "None\n\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    IssueTrackingSystem ITS;

    std::cout << std::endl;

    ITS.addEmployee("Employee1", "Title1");
    ITS.addEmployee("Employee2", "Title2");
    ITS.addEmployee("Employee3", "Title1");
    ITS.addEmployee("Employee4", "Title2");
    ITS.addEmployee("Employee5", "Title2");

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            int id = (i * 5) + 1 + j;
            std::string id_as_string = std::to_string(id);
            ITS.addIssue(id, "Description" + id_as_string, "Employee" + std::to_string(i+1));
        }

    ITS.removeIssue(13);
    ITS.removeIssue(12);
    ITS.removeIssue(11);
    ITS.showEmployee("Employee3");
    ITS.removeIssue(14);
    ITS.removeIssue(15);
    ITS.removeEmployee("Employee3");
    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();
    std::cout << std::endl;

    ITS.removeIssue(18);
    ITS.removeIssue(17);
    ITS.removeIssue(16);
    ITS.removeIssue(19);
    ITS.showEmployee("Employee4");
    ITS.removeIssue(20);
    ITS.removeEmployee("Employee4");
    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();
    std::cout << std::endl;

    ITS.changeAssignee("Employee2", "Employee4");

    ITS.removeIssue(8);
    ITS.showEmployee("Employee2");
    ITS.removeIssue(7);
    ITS.removeIssue(6);
    ITS.removeIssue(9);
    ITS.removeIssue(10);
    ITS.removeEmployee("Employee2");
    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();
    std::cout << std::endl;

    ITS.changeAssignee("Employee5", "Employee1");

    ITS.removeIssue(23);
    ITS.removeIssue(22);
    ITS.removeIssue(21);
    ITS.removeIssue(24);
    ITS.removeIssue(25);
    ITS.showEmployee("Employee5");
    ITS.removeEmployee("Employee5");
    ITS.showEmployee("Employee5");
    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();
    std::cout << std::endl;

    ITS.removeIssue(2);
    ITS.showEmployee("Employee1");
    ITS.removeIssue(1);
    ITS.removeIssue(3);
    ITS.removeIssue(5);
    ITS.removeIssue(4);
    ITS.removeEmployee("Employee1");
    ITS.showEmployee("Employee1");

    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();
    std::cout << std::endl;

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}

TEST(IssueTrackingSystem, CircularChange) {
    const std::string expectedOutput = "\nAdded employee Employee1.\n"
        "Added employee Employee2.\n"
        "Added issue 1.\n"
        "Added issue 2.\n"
        "Added issue 3.\n"
        "Added issue 4.\n"
        "Added issue 5.\n"
        "Added issue 6.\n"
        "Added issue 113.\n"
        "Employee1's issues are transferred to Employee2.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 0 issue(s).\n"
        "Employee2, Title2, 7 issue(s).\n\n"
        "Employee2's issues are transferred to Employee1.\n"
        "Employees in the system:\n"
        "Employee1, Title1, 7 issue(s).\n"
        "Employee2, Title2, 0 issue(s).\n\n"
        "Employee1's issues are transferred to Employee2.\n"
        "Employee2's issues are transferred to Employee1.\n"
        "Removed issue 1.\n"
        "Removed issue 3.\n"
        "Cannot remove issue. There is no issue with ID 7.\n"
        "Employee1's issues are transferred to Employee2.\n"
        "Removed employee Employee1.\n"
        "Cannot remove employee. Employee2 has assigned issues.\n"
        "Employees in the system:\n"
        "Employee2, Title2, 5 issue(s).\n\n"
        "Issues in the system:\n"
        "4, d4, Employee2.\n"
        "5, d5, Employee2.\n"
        "6, d6, Employee2.\n"
        "2, d2, Employee2.\n"
        "113, Description113, Employee2.\n";

    testing::internal::CaptureStdout();

    // --------------------------------------------------------------------

    IssueTrackingSystem ITS;

    std::cout << std::endl;

    ITS.addEmployee("Employee1", "Title1");
    ITS.addEmployee("Employee2", "Title2");

    ITS.addIssue(1,"d1","Employee1");
    ITS.addIssue(2,"d2","Employee1");
    ITS.addIssue(3,"d3","Employee1");

    ITS.addIssue(4,"d4","Employee2");
    ITS.addIssue(5,"d5","Employee2");
    ITS.addIssue(6,"d6","Employee2");

    ITS.addIssue(113, "Description113", "Employee1");


    ITS.changeAssignee("Employee1", "Employee2");
    ITS.showAllEmployees();
    std::cout << std::endl;

    ITS.changeAssignee("Employee2", "Employee1");
    ITS.showAllEmployees();
    std::cout << std::endl;

    ITS.changeAssignee("Employee1", "Employee2");
    ITS.changeAssignee("Employee2", "Employee1");

    ITS.removeIssue(1);
    ITS.removeIssue(3);
    ITS.removeIssue(7);

    ITS.changeAssignee("Employee1", "Employee2");

    ITS.removeEmployee("Employee1");
    ITS.removeEmployee("Employee2");

    ITS.showAllEmployees();
    std::cout << std::endl;
    ITS.showAllIssues();

    // --------------------------------------------------------------------

    EXPECT_EQ(testing::internal::GetCapturedStdout(), expectedOutput);
}
