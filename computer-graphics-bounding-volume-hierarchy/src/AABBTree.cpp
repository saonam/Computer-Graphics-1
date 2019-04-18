#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  int num_objects = objects.size();

  if(num_objects == 0){
    this->left = NULL;
    this->right = NULL;
    return;
  }
  if(num_objects == 1){
    this->left = objects[0];
    this->right = NULL;
    insert_box_into_box(this->left->box, this->box);
    return;
  }
  if(num_objects == 2){
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(this->left->box, this->box);
    insert_box_into_box(this->right->box, this->box);
    return;
  }
  double min_x = this->box.min_corner(0);
  double min_y = this->box.min_corner(1);
  double min_z = this->box.min_corner(2);
  double max_x = this->box.max_corner(0);
  double max_y = this->box.max_corner(1);
  double max_z = this->box.max_corner(2);
  for(int i=0; i<num_objects; i++){
    min_x = std::min(min_x, objects[i]->box.min_corner(0));
    min_y = std::min(min_y, objects[i]->box.min_corner(1));
    min_z = std::min(min_z, objects[i]->box.min_corner(2));
    max_x = std::max(max_x, objects[i]->box.max_corner(0));
    max_y = std::max(max_y, objects[i]->box.max_corner(1));
    max_z = std::max(max_z, objects[i]->box.max_corner(2));
  }
  this->box.min_corner(0) = min_x;
  this->box.min_corner(1) = min_y;
  this->box.min_corner(2) = min_z;
  this->box.max_corner(0) = max_x;
  this->box.max_corner(1) = max_y;
  this->box.max_corner(2) = max_z;

  double x_length = max_x - min_x;
  double y_length = max_y - min_y;
  double z_length = max_z - min_z;

  double longest_one = std::max(std::max(x_length, y_length), z_length);

  int longest_axis;
  if(longest_one == x_length){
    longest_axis = 0;
  }
  if(longest_one == y_length){
    longest_axis = 1;
  }
  if(longest_one == z_length){
    longest_axis = 2;
  }
  // printf("%d\n", longest_axis);
  Eigen::RowVector3d mmm = this->box.center();
  
  std::vector<std::shared_ptr<Object>> left_,right_;
  for(int i=0; i<num_objects; i++){
    // if (i%100==0)
    //   printf("%f  %f   %f  %f\n",objects[i]->box.min_corner(1),objects[i]->box.max_corner(1), objects[i]->box.center()(longest_axis),mmm(longest_axis));
    if(objects[i]->box.center()(longest_axis)<mmm(longest_axis)){
      left_.push_back(objects[i]);
    }
    else
      right_.push_back(objects[i]);
  }
  if(left_.size()==0 && right_.size()!=0){
    left_.push_back(right_.back());
    right_.pop_back();
  }
  else if(left_.size()!=0 && right_.size()==0){
    right_.push_back(left_.back());
    left_.pop_back();
  }

  this->left = std::make_shared<AABBTree>(left_,a_depth+1);
  this->right = std::make_shared<AABBTree>(right_,a_depth+1);
}

// struct AABBTree : public Object, public std::enable_shared_from_this<AABBTree>
// {
//   // Pointers to left and right subtree branches. These could be another
//   // AABBTree (internal node) or a leaf (primitive Object like MeshTriangle, or
//   // CloudPoint)
//   std::shared_ptr<Object> left;
//   std::shared_ptr<Object> right;
//   // For debugging, keep track of the depth (root has depth == 0)
//   int depth;
//   // For debugging, keep track of the number leaf, descendants 
//   int num_leaves;
//   // Construct a axis-aligned bounding box tree given a list of objects. Use the
//   // midpoint along the longest axis of the box containing the given objects to
//   // determine the left-right split.
//   //
//   // Inputs:
//   //   objects  list of objects to store in this AABBTree
//   //   Optional inputs:
//   //     depth  depth of this tree (usually set by constructor of parent as
//   //       their depth+1)
//   // Side effects: num_leaves is set to objects.size() and left/right pointers
//   // set to subtrees or leaf Objects accordingly.
//   AABBTree(
//     const std::vector<std::shared_ptr<Object> > & objects, 
//     int depth=0);
//   // Object implementations (see Object.h)
//   bool ray_intersect(
//     const Ray& ray,
//     const double min_t,
//     const double max_t,
//     double & t,
//     std::shared_ptr<Object> & descendant) const override;
//   bool point_squared_distance(
//     const Eigen::RowVector3d & query,
//     const double min_sqrd,
//     const double max_sqrd,
//     double & sqrd,
//     std::shared_ptr<Object> & descendant) const override
//   {
//     assert(false && "Do not use recursive DFS for AABBTree distance");
//     return false;
//   }
// };

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool if_intersect_box = ray_intersect_box(ray, this->box, min_t, max_t);
  if(!if_intersect_box){
    return false;
  }
  else{

    bool left_hit = false;
    bool right_hit = false;

    std::shared_ptr<Object> left_children, right_children;
    double left_hit_time;
    double right_hit_time;

    if(this->left != NULL){
      bool temp_l = this->left->ray_intersect(ray, min_t, max_t, left_hit_time, left_children);
      if(temp_l){
        left_hit = true;
      }
    }
    if(this->right != NULL){
      bool temp_r = this->right->ray_intersect(ray, min_t, max_t, right_hit_time, right_children);
      if(temp_r){
        right_hit = true;
      }
    }

    if(left_hit && !left_children){
      left_children = left;
    }
    if(right_hit && !right_children){
      right_children = right;
    }

    if (left_hit && right_hit) {
        if (left_hit_time < right_hit_time) {
            t = left_hit_time;
            descendant = left_children;
        } else {
            t = right_hit_time;
            descendant = right_children;
        }
        return true;
    } 
    else if (left_hit) {
        t = left_hit_time;
        descendant = left_children;
        return true;
    } 
    else if (right_hit) {
        t = right_hit_time;
        descendant = right_children;
        return true;
    } 
    else {
        return false;
    }
  }
}


