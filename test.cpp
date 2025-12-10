#include <iostream>
#include "interval-tree/interval_tree.hpp"

void testIntervalTree() {
	lib_interval_tree::interval_tree_t<long> tree;

	tree.insert({ 0,5 });
	tree.insert({ 5,10 });
	tree.insert({ 13,16 });

	if (tree.overlap_find({ 8,10 }, false) == std::end(tree)) // Expected "Overlap Found!"
		std::cout << "Did not find overlap!" << std::endl;
	else
		std::cout << "Overlap Found! " << std::endl;

	if (tree.overlap_find({ 18,20 }, false) == std::end(tree)) // Expected "Did not find overlap!"
		std::cout << "Did not find overlap!" << std::endl;
	else
		std::cout << "Overlap Found! " << std::endl;

	if (tree.overlap_find({ 1,1 }, false) == std::end(tree)) // Expected "Overlap Found!"
		std::cout << "Did not find overlap!" << std::endl;
	else
		std::cout << "Overlap Found! " << std::endl;

	if (tree.overlap_find({ 11,12 }, false) == std::end(tree)) // Expected "Did not find overlap"
		std::cout << "Did not find overlap!" << std::endl;
	else
		std::cout << "Overlap Found! " << std::endl;

	tree.erase(tree.find({ 5,10 }));

	if (tree.overlap_find({ 7, 9 }, false) == std::end(tree)) // Expected "Did not find overlap"
		std::cout << "Did not find overlap!" << std::endl;
	else
		std::cout << "Overlap Found! " << std::endl;

	tree.insert({ 5,10 });
	if (tree.overlap_find({ 7, 9 }, false) == std::end(tree)) // Expected "Overlap Found!"
		std::cout << "Did not find overlap!" << std::endl;
	else
		std::cout << "Overlap Found! " << std::endl;
}

int test(){
	testIntervalTree();
	return 0;
}

