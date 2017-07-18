/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file: active_set_qp_solver.h
 * @brief: wrapper class for active set method in qpOases
 **/
#ifndef MODULES_PLANNING_MATH_QP_SOLVER_ACTIVE_SET_QP_SOLVER_H_
#define MODULES_PLANNING_MATH_QP_SOLVER_ACTIVE_SET_QP_SOLVER_H_

#include "include/qpOASES.hpp"

#include "modules/planning/math/qp_solver/qp_solver.h"

namespace apollo {
namespace planning {

class ActiveSetQPSolver : public QPSolver {
 public:
  ActiveSetQPSolver(const Eigen::MatrixXd& kernel_matrix,
                    const Eigen::MatrixXd& offset,
                    const Eigen::MatrixXd& affine_inequality_matrix,
                    const Eigen::MatrixXd& affine_inequality_boundary,
                    const Eigen::MatrixXd& affine_equality_matrix,
                    const Eigen::MatrixXd& affine_equality_boundary);

  bool solve() override;

  void set_qp_eps_num(const double eps);
  void set_qp_eps_den(const double eps);
  void set_qp_eps_iter_ref(const double eps);
  void set_debug_info(const bool enable);
  void set_max_iteration(const int max_iter);

  void set_l_lower_bound(const double l_lower_bound);
  void set_l_upper_bound(const double l_upper_bound);
  void set_constraint_upper_bound(const double la_upper_bound);

  double qp_eps_num() const;
  double qp_eps_den() const;
  double qp_eps_iter_ref() const;
  bool debug_info() const;
  int max_iteration() const;

  double l_lower_bound() const;
  double l_upper_bound() const;
  double constraint_upper_bound() const;

 private:
  bool sanity_check() override;

 private:
  // equality constriant + inequality constraint
  int num_constraint_;
  // number of parameters
  int num_param_;

  double qp_eps_num_;
  double qp_eps_den_;
  double qp_eps_iter_ref_;
  bool debug_info_;

  // parameter search bound
  double l_lower_bound_ = -1e10;
  double l_upper_bound_ = 1e10;

  // constraint search upper bound
  double constraint_upper_bound_ = 1e10;
  int max_iteration_ = 1000;
};

}  // namespace planning
}  // namespace apollo
#endif  // MODULES_PLANNING_MATH_QP_SOLVER_ACTIVE_SET_QP_SOLVER_H_
