#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  // // initialize list of candidate leaf pairs


// leaf_pairs ← {}
	std::list<std::pair<std::shared_ptr<AABBTree>,std::shared_ptr<AABBTree> > > frontier;
// if root_A.box intersects root_B.box
	if(box_box_intersect(rootA->box, rootB->box)){
		// Q.insert( root_A, root_B )
		frontier.emplace_back(rootA, rootB);
	}
//   
// while Q not empty
	while (!frontier.empty()) {
//   {nodeA,nodeB} ← Q.pop
		std::shared_ptr<AABBTree> nodeA = frontier.front().first;
        std::shared_ptr<AABBTree> nodeB = frontier.front().second;
        frontier.pop_front();
//   if nodeA and nodeB are leaves
        if(nodeA->num_leaves<=2 && nodeB->num_leaves<=2){
        	// Need consider four cases. Two trees may intersect with left/left
        	if (nodeA->left && nodeB->left){
        		if(box_box_intersect(nodeA->left->box, nodeB->left->box)) {
        			//     leaf_pairs.insert( node_A, node_B )
                	leaf_pairs.emplace_back(nodeA->left, nodeB->left);
            	}
        	} 
        	// left/right
        	if (nodeA->left && nodeB->right){
        		if(box_box_intersect(nodeA->left->box, nodeB->right->box)) {
        			//     leaf_pairs.insert( node_A, node_B )
                	leaf_pairs.emplace_back(nodeA->left, nodeB->right);
            	}
        	} 
        	// right/left
        	if (nodeA->right && nodeB->left){
        		if(box_box_intersect(nodeA->right->box, nodeB->left->box)) {
        			//     leaf_pairs.insert( node_A, node_B )
                	leaf_pairs.emplace_back(nodeA->right, nodeB->left);
            	}
        	} 
        	// right/right
        	if (nodeA->right && nodeB->right){
        		if(box_box_intersect(nodeA->right->box, nodeB->right->box)) {
        			//     leaf_pairs.insert( node_A, node_B )
                	leaf_pairs.emplace_back(nodeA->right, nodeB->right);
            	}
        	} 
        }

        //   else if node_A is a leaf
        else if(nodeA->num_leaves <= 2){
        	//     if node_A.box intersects node_B.left.box
        	if(box_box_intersect(nodeA->box, nodeB->left->box)){
        		//       Q.insert( node_A, node_B.left )
        		frontier.emplace_back(nodeA, std::static_pointer_cast<AABBTree>(nodeB->left));
        	}
        	//     if node_A.box intersects node_B.right.box
        	if(box_box_intersect(nodeA->box, nodeB->right->box)){
        		//       Q.insert( node_A, node_B.right )
        		frontier.emplace_back(nodeA, std::static_pointer_cast<AABBTree>(nodeB->right));
        	}
        }
        //   else if node_B is a leaf
        else if((nodeB->num_leaves <= 2)){
        	//     if node_A.left.box intersects node_B.box
        	if(box_box_intersect(nodeA->left->box, nodeB->box)){
        		//       Q.insert( node_A.left, node_B)
        		frontier.emplace_back(std::static_pointer_cast<AABBTree>(nodeA->left), nodeB);
        	}
        	//     if node_A.right.box intersects node_B.box
        	if(box_box_intersect(nodeA->right->box, nodeB->box)){
        		//       Q.insert( node_A.right, node_B)
        		frontier.emplace_back(std::static_pointer_cast<AABBTree>(nodeA->right), nodeB);
        	}
        }
        else{
        	//     if node_A.left.box intersects node_B.left.box
        	if(box_box_intersect(nodeA->left->box, nodeB->left->box)){
        		//       Q.insert( node_A.left, node_B.left)
        		frontier.emplace_back(std::static_pointer_cast<AABBTree>(nodeA->left), std::static_pointer_cast<AABBTree>(nodeB->left));
			}
			//     if node_A.left.box intersects node_B.right.box
        	if(box_box_intersect(nodeA->left->box, nodeB->right->box)){
        		///       Q.insert( node_A.left, node_B.right )
        		frontier.emplace_back(std::static_pointer_cast<AABBTree>(nodeA->left), std::static_pointer_cast<AABBTree>(nodeB->right));
			}
			//     if node_A.right.box intersects node_B.right.box
        	if(box_box_intersect(nodeA->right->box, nodeB->right->box)){
        		//       Q.insert( node_A.left, node_B.left)
        		frontier.emplace_back(std::static_pointer_cast<AABBTree>(nodeA->right), std::static_pointer_cast<AABBTree>(nodeB->right));
			}
			//     if node_A.right.box intersects node_B.left.box
        	if(box_box_intersect(nodeA->right->box, nodeB->left->box)){
        		//       Q.insert( node_A.right, node_B.left)
        		frontier.emplace_back(std::static_pointer_cast<AABBTree>(nodeA->right), std::static_pointer_cast<AABBTree>(nodeB->left));
			}
        }
	}
}

