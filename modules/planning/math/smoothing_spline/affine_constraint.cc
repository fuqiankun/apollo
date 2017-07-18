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
 * @file : affine_constraint.cc
 **/

#include "modules/planning/math/smoothing_spline/affine_constraint.h"
#include "glog/logging.h"

namespace apollo {
namespace planning {

AffineConstraint::AffineConstraint(const bool is_equality)
    : is_equality_(is_equality) {}

AffineConstraint::AffineConstraint(const Eigen::MatrixXd& constraint_matrix,
                                   const Eigen::MatrixXd& constraint_boundary,
                                   const bool is_equality)
    : constraint_matrix_(constraint_matrix),
      constraint_boundary_(constraint_boundary),
      is_equality_(is_equality) {
  CHECK(constraint_boundary.rows() == constraint_matrix.rows());
}

void AffineConstraint::set_is_equality(const double is_equality) {
  is_equality_ = is_equality;
}

const Eigen::MatrixXd& AffineConstraint::constraint_matrix() const {
  return constraint_matrix_;
}

const Eigen::MatrixXd& AffineConstraint::constraint_boundary() const {
  return constraint_boundary_;
}

bool AffineConstraint::is_equality() const { return is_equality_; }

bool AffineConstraint::add_constraint(
    const Eigen::MatrixXd& constraint_matrix,
    const Eigen::MatrixXd& constraint_boundary) {
  if (constraint_matrix.rows() != constraint_boundary.rows()) {
    return false;
  }

  if (constraint_matrix_.rows() == 0) {
    constraint_matrix_ = constraint_matrix;
    constraint_boundary_ = constraint_boundary;
    return true;
  }

  if (constraint_matrix_.cols() != constraint_matrix.cols() ||
      constraint_boundary.cols() != 1) {
    return false;
  }
  Eigen::MatrixXd n_matrix(constraint_matrix_.rows() + constraint_matrix.rows(),
                           constraint_matrix_.cols());
  Eigen::MatrixXd n_boundary(
      constraint_boundary_.rows() + constraint_boundary.rows(), 1);

  n_matrix << constraint_matrix_, constraint_matrix;
  n_boundary << constraint_boundary_, constraint_boundary;
  constraint_matrix_ = n_matrix;
  constraint_boundary_ = n_boundary;
  return true;
}

}  // namespace planning
}  // namespace apollo
