#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <math.h>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	// Compute the nearest neighbor for a query in the set of $n$ points
// (rows of `points`). This should be a **_slow reference implementation_**. Aim
// for a computational complexity of $O(n)$ but focus on correctness. 
//
// Inputs:
//   points  #points by 3 list of points to search within
//   query  3D position fo the query
// Outputs:
//   I  index into points of closest point
//   sqrD  corresponding squared distance
//

	sqrD = std::numeric_limits<double>::infinity();
	for (int i=0; i<points.rows(); i++) {
        // RowVector3d temp = query-points.row(i);
        double a = query(0)-points.row(i)(0);
        double b = query(1)-points.row(i)(1);
        double c = query(2)-points.row(i)(2);
        double temp_sqrD = a*a + b*b + c*c;
        if (temp_sqrD < sqrD) {
            sqrD = temp_sqrD;
            I = i;
        }
    }
  ////////////////////////////////////////////////////////////////////////////
}
