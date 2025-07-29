# Red Black Tree Algorithm in C++ #
## Authors: Kylie Griffiths, Jee Choi (UO) ##

Red Black trees are a type of binary search tree that use rules to maintain balance. The four rules are:

1. Either node of the tree is either red or black.
2. The root of the tree is always black.
3. Red nodes cannot have red children.
4. Every path from a node to its sentinel leaves has the same number of blacks.
5. All leaves (sentinels) are black.

This program runs through the typical operations of a Red Black tree. First, it inserts the nodes in the tree, rotating and changing the color as the process runs. After insertion, the algorithm finds the min and max of the tree and their color. Additionally, it runs a BST walk test (walking through the tree in min to max order) and identifies each node's successor (using the right child successor rule). Then, a deletion algorithm is run, deleting nodes until there are five left in the tree. 

To run the program, download the files and navigate into the folder. Flags:

* -s: Refers to the seed. Changing this number changes the input keys.
* -t: Refers to the number of nodes. Changing this number changes the number of input keys.
* (optional) -i: Refers to an input file.
* (optional) -o: Refers to an output file. 

To run:
### ./rbt -s {arg} -t {arg}

Ex:
### ./rbt -s 1 -t 10




