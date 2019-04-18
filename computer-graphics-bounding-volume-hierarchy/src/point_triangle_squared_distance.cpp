#include "point_triangle_squared_distance.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

// #ifndef POINT_TRIANGLE_SQUARED_DISTANCE_H
// #define POINT_TRIANGLE_SQUARED_DISTANCE_H
// #include <Eigen/Core>
// // Compute the squared distance of a query point to a triangle, output the
// // closest point on the triangle in barycentric coordinates.
// //
// // Inputs:
// //   query  3D position of query point
// //   A  first corner position of the triangle
// //   B  second corner position of the triangle
// //   C  third corner position of the triangle
// // Outputs:
// //   bary  3-vector so that the closest point on the triangle to the query is
// //     given as A*bary(0) + B*bary(1) + C*bary(2)
// // Returns squared distance of query to closest point on triangle
// double point_triangle_squared_distance(
//   const Eigen::RowVector3d & query,
//   const Eigen::RowVector3d & A,
//   const Eigen::RowVector3d & B,
//   const Eigen::RowVector3d & C,
//   Eigen::RowVector3d & bary);
// #endif



void bary_solver(const Eigen::RowVector3d A, 
                const Eigen::RowVector3d B, 
                const Eigen::RowVector3d C, 
                double & alpha, 
                double & beta, 
                double & gamma, 
                Eigen::RowVector3d project){
    double a = A[0];
    double b = A[1];
    double c = A[2];

    double d = B[0];
    double e = B[1];
    double f = B[2];

    double g = C[0];
    double h = C[1];
    double i = C[2];

    double j = project[0];
    double k = project[1];
    double l = project[2];

    double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

    alpha = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
    beta = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
    gamma = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;
}



double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
    Eigen::RowVector3d first_column = A - B;
    Eigen::RowVector3d second_column = A - C;
    Eigen::RowVector3d normal = (first_column.cross(second_column)).normalized();

    // perpendicular distance from query point to plane spanned by triangle. 
    double perpendicular = (query-A).dot(normal);
    Eigen::RowVector3d proj = query-perpendicular*normal;

    double alpha, beta, gamma; 

    bary_solver(A, B, C, alpha, beta, gamma, proj);

    
    // in triangle
    if (alpha>=0 && alpha<=1 && beta>=0 && beta<=1 && gamma>=0 && gamma <=1) {
        bary = {alpha, beta, gamma};
        double distance = pow(query(0)-proj(0), 2)+pow(query(1)-proj(1), 2)+pow(query(2)-proj(2), 2);
        return distance;
    }
    
    // project onto AB
    double t1 = fmin(1, fmax(0, (B-A).dot(proj-A)));
    Eigen::RowVector3d temp_1 = A+t1*(B-A);
    
    // project onto AC
    double t2 = fmin(1, fmax(0, (C-A).dot(proj-A)));
    Eigen::RowVector3d temp_2 = A+t2*(C-A);
    
    // project onto BC
    double t3 = fmin(1, fmax(0, (C-B).dot(proj-B)));
    Eigen::RowVector3d temp_3 = B+t3*(C-B);
    
    Eigen::RowVector3d distances;
    distances(0) = pow(query(0)-temp_1(0), 2)+pow(query(1)-temp_1(1), 2)+pow(query(2)-temp_1(2), 2);
    distances(1) = pow(query(0)-temp_2(0), 2)+pow(query(1)-temp_2(1), 2)+pow(query(2)-temp_2(2), 2);
    distances(2) = pow(query(0)-temp_3(0), 2)+pow(query(1)-temp_3(1), 2)+pow(query(2)-temp_3(2), 2);
    
    // closest point
    int result;
    distances.minCoeff(&result);
    Eigen::RowVector3d best;
    if (result==0)
        best = temp_1;
    if (result ==1)
        best = temp_2;
    if (result ==2)
        best = temp_3;
    
    bary_solver(A, B, C, alpha, beta, gamma,best);
    bary = {alpha, beta, gamma};
    return pow(query(0)-best(0), 2)+pow(query(1)-best(1), 2)+pow(query(2)-best(2), 2);
}
