//#include "BVH.h"
//#include <algorithm>
//
//BVHNode::BVHNode() : left(nullptr), right(nullptr), pig(nullptr) {}
//BVHNode::BVHNode(Pig* pig) : left(nullptr), right(nullptr), pig(pig)
//{
//	if (pig)
//		bounds = pig->sprite.getGlobalBounds();
//}
//
//BVH::BVH() : root(nullptr) {}
//
//BVH::~BVH()
//{
//	clear();
//}
//
//void BVH::clear()
//{
//	delete root;
//	root = nullptr;
//}
//
//void BVH::build(std::vector<Pig*>& pigs)
//{
//	clear();
//}
//
//bool BVHNode::isLeaf() const
//{
//	return left == nullptr && right == nullptr;
//}// check if left and right are empty
//
//static sf::FloatRect combineBounds(const sf::FloatRect& a, const sf::FloatRect& b)
//{
//	float left = std::min(a.left, b.left);
//	float right = std::max(a.left + a.width, b.left + b.width);
//	float top = std::min(a.top, b.top);
//	float bottom = std::max(a.top + a.height, b.top + b.height);
//
//	return sf::FloatRect(left, top, right - left, bottom - top);
//
//}// create rectnagle to cover pigs
//
//static BVHNode* buildRecursive(std::vector<Pig*>& pigs, int start, int end)
//{
//	if (start >= end)
//		return nullptr;
//	//if no pigs between start and end then stop
//
//	if (end - start == 1)
//	{
//		return new BVHNode(pigs[start]);
//	}//if only one pig, make node holding pig
//
//	int mid = (start + end) / 2; //divide pigs in groups if two pigs
//
//	BVHNode* node = new BVHNode();
//	node->left = buildRecursive(pigs, start, mid);
//	node->right = buildRecursive(pigs, mid, end);
//	// build left and right side
//
//	if (node->left && node->right)
//		node->bounds = combineBounds(node->left->bounds, node->right->bounds); // if both exist combine bounds
//	else if (node->right)
//		node->bounds = node->left->bounds;
//	else if (node->right)
//		node->bounds = node->right->bounds;// if only one side exists use its bounds
//
//	return node;
//}
//
//void BVH::build(std::vector<Pig*>& pigs)
//{
//	clear();
//	root = buildRecursive(pigs, 0, pigs.size());
//}


