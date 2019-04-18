#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include "point_box_squared_distance.h"


typedef std::pair<double, std::shared_ptr<AABBTree>> queue_distance;


bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  // initialize a queue prioritized by minimum distance
  // d_r ← distance to root's box
  // Q.insert(d_r, root)
  // // initialize minimum distance seen so far
  // d ← ∞
  // while Q not empty 
  //   // d_s: distance from query to subtree's bounding box
  //   (d_s, subtree) ← Q.pop
  //   if d_s < d
  //     if subtree is a leaf
  //       d ← min[ d , distance from query to leaf object ]
  //     else
  //       d_l ← distance to left's box
  //       Q.insert(d_l ,subtree.left)
  //       d_r ← distance to right's box
  //       Q.insert(d_r ,subtree.right)

  sqrd = std::numeric_limits<double>::infinity();

  // initialize a queue prioritized by minimum distance
  std::priority_queue<queue_distance,std::vector<queue_distance>, std::greater<queue_distance>> frontier;
  // d_r ← distance to root's box
  queue_distance pair(point_box_squared_distance(query, root->box), root);
  // Q.insert(d_r, root)
  frontier.push(pair);
  // while Q not empty 
  while (!frontier.empty()){
    //   d_s: distance from query to subtree's bounding box
    //   (d_s, subtree) ← Q.pop
    queue_distance pop_out = frontier.top();
    double d_s = pop_out.first;
    std::shared_ptr<AABBTree> subtree = pop_out.second;
    // C++ pop doesn't return anything, only removes elements. 
    frontier.pop();

    if (d_s<sqrd){
      // if subtree is a leaf since   num_leaves(objects.size())
      if (subtree->num_leaves<=2){
      //not reach terminals
        // d ← min[ d , distance from query to leaf object ]
        double d_s_;
        double d_s_right;
        std::shared_ptr<Object> left_children;
        std::shared_ptr<Object> right_children;

        if(subtree->left){
          if(subtree->left->point_squared_distance(query, min_sqrd, max_sqrd, d_s_, left_children)){
            if (d_s_<sqrd){
              sqrd = d_s_;
              descendant = subtree->left;
            }
          }
        }
        if(subtree->right){
          if(subtree->right->point_squared_distance(query, min_sqrd, max_sqrd, d_s_, right_children)){
            if (d_s_<sqrd){
              sqrd = d_s_;
              descendant = subtree->right;
            }
          }
        }
      }
      //else
      //       d_l ← distance to left's box
      //       Q.insert(d_l ,subtree.left)
      //       d_r ← distance to right's box
      //       Q.insert(d_r ,subtree.right)
      else{
        queue_distance left_node (point_box_squared_distance(query,subtree->left->box), std::static_pointer_cast<AABBTree>(subtree->left));
        frontier.push(left_node);
        queue_distance right_node (point_box_squared_distance(query,subtree->right->box), std::static_pointer_cast<AABBTree>(subtree->right));
        frontier.push(right_node);
      //leaves
      }
    }
  }
  return descendant!=NULL;
  ////////////////////////////////////////////////////////////////////////////
}
