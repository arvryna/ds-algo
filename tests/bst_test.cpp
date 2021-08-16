#include <iostream>
#include <string>

#include "../lib/containers/binary_search_tree.cpp"

void Tester(std::string title, std::string expected, std::string got) {
    if (expected == got) {
        std::cout << title << ": Passed ✅" << std::endl;
    } else {
        std::cout << title << ": Failed ❌" << std::endl;
        std::cout << "expected :" << expected << "got: " << got << std::endl;
    }
}

void BstUnitTest() {
    BinaryTree<int> tree;
    printf("\n*** Delete leaf node ***\n");
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Erase(5);
    Tester("1) Deleting leaf node(Left)", "10,15,", tree.GetTreeAsString());
    tree.Insert(5);
    tree.Erase(15);
    Tester("2) Deleting leaf node(Right)", "5,10,", tree.GetTreeAsString());
    tree.Erase(5);

    tree.Clear();
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Erase(10);
    Tester("2.2) Deleting root node", "5,15,", tree.GetTreeAsString());

    tree.Clear();
    tree.Insert(10);
    tree.Insert(15);
    tree.Insert(16);
    tree.Erase(10);
    Tester("2.2) Deleting root node", "15,16,", tree.GetTreeAsString());

    printf("\n*** Delete node with one child ***\n");
    tree.Clear();
    tree.Insert(10);
    tree.Insert(9);
    tree.Insert(5);
    tree.Erase(9);
    Tester("3) Deleting a left node with 1 left-child and parent", "5,10,", tree.GetTreeAsString());
    tree.Clear();
    tree.Insert(10);
    tree.Insert(12);
    tree.Insert(13);
    tree.Erase(12);
    Tester("4) Deleting a right node with 1 right-child and parent", "10,13,",
           tree.GetTreeAsString());

    printf("\n Deleting node with two childs");
    tree.Clear();
    tree.Insert(15);
    tree.Insert(9);
    tree.Insert(8);
    tree.Insert(11);
    tree.Erase(9);
    Tester("5) Deleting a left node with 1 left-child, 1 right-child and parent", "8,11,15,",
           tree.GetTreeAsString());

    tree.Clear();
    tree.Insert(15);
    tree.Insert(9);
    tree.Insert(8);
    tree.Insert(11);
    tree.Insert(12);
    tree.Erase(9);
    Tester(
        "6) Deleting a left node with 1 left-child, 1 right-child(+ 1 right grand child) and "
        "parent",
        "8,11,12,15,", tree.GetTreeAsString());

    tree.Clear();
    tree.Insert(15);
    tree.Insert(20);
    tree.Insert(18);
    tree.Insert(25);
    tree.Erase(20);
    Tester("7) Deleting a right node with a right child and a left child", "15,18,25,",
           tree.GetTreeAsString());

    tree.Clear();
    tree.Insert(15);
    tree.Insert(22);
    tree.Insert(18);
    tree.Insert(25);
    tree.Insert(21);
    tree.Insert(19);
    tree.Insert(20);
    tree.Erase(22);
    Tester("8) balacing: right successor with left child", "15,18,19,20,21,25,",
           tree.GetTreeAsString());

    tree.Clear();
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);
    tree.Insert(25);
    tree.Insert(35);
    tree.Insert(27);
    tree.Insert(28);
    tree.Erase(20);
    Tester("9) balacing: Left successor with right child", "10,25,27,28,30,35,",
           tree.GetTreeAsString());
}

int main() {
    BstUnitTest();
    return 0;
}