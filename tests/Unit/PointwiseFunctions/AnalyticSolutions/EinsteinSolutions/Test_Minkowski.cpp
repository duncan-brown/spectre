// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "PointwiseFunctions/AnalyticSolutions/EinsteinSolutions/Minkowski.hpp"
#include "tests/Unit/TestCreation.hpp"
#include "tests/Unit/TestHelpers.hpp"
#include "tests/Unit/TestingFramework.hpp"

namespace {
template <size_t Dim, typename T>
void test_minkowski(const T& value) {
  EinsteinSolutions::Minkowski<Dim> minkowski{};

  const tnsr::I<T, Dim> x{value};
  const double t = 1.2;

  const auto one = make_with_value<T>(value, 1.);
  const auto zero = make_with_value<T>(value, 0.);

  const auto lapse =
      get<gr::Tags::Lapse<Dim, Frame::Inertial, T>>(minkowski.variables(
          x, t, tmpl::list<gr::Tags::Lapse<Dim, Frame::Inertial, T>>{}));
  const auto dt_lapse = get<Tags::dt<gr::Tags::Lapse<Dim, Frame::Inertial, T>>>(
      minkowski.variables(
          x, t,
          tmpl::list<Tags::dt<gr::Tags::Lapse<Dim, Frame::Inertial, T>>>{}));
  const auto d_lapse = get<Tags::deriv<gr::Tags::Lapse<Dim, Frame::Inertial, T>,
                                       tmpl::size_t<Dim>, Frame::Inertial>>(
      minkowski.variables(
          x, t,
          tmpl::list<Tags::deriv<gr::Tags::Lapse<Dim, Frame::Inertial, T>,
                                 tmpl::size_t<Dim>, Frame::Inertial>>{}));
  const auto shift =
      get<gr::Tags::Shift<Dim, Frame::Inertial, T>>(minkowski.variables(
          x, t, tmpl::list<gr::Tags::Shift<Dim, Frame::Inertial, T>>{}));
  const auto dt_shift = get<Tags::dt<gr::Tags::Shift<Dim, Frame::Inertial, T>>>(
      minkowski.variables(
          x, t,
          tmpl::list<Tags::dt<gr::Tags::Shift<Dim, Frame::Inertial, T>>>{}));
  const auto d_shift = get<Tags::deriv<gr::Tags::Shift<Dim, Frame::Inertial, T>,
                                       tmpl::size_t<Dim>, Frame::Inertial>>(
      minkowski.variables(
          x, t,
          tmpl::list<Tags::deriv<gr::Tags::Shift<Dim, Frame::Inertial, T>,
                                 tmpl::size_t<Dim>, Frame::Inertial>>{}));
  const auto g =
      get<gr::Tags::SpatialMetric<Dim, Frame::Inertial, T>>(minkowski.variables(
          x, t,
          tmpl::list<gr::Tags::SpatialMetric<Dim, Frame::Inertial, T>>{}));
  const auto dt_g =
      get<Tags::dt<gr::Tags::SpatialMetric<Dim, Frame::Inertial, T>>>(
          minkowski.variables(
              x, t,
              tmpl::list<Tags::dt<
                  gr::Tags::SpatialMetric<Dim, Frame::Inertial, T>>>{}));
  const auto d_g =
      get<Tags::deriv<gr::Tags::SpatialMetric<Dim, Frame::Inertial, T>,
                      tmpl::size_t<Dim>, Frame::Inertial>>(
          minkowski.variables(
              x, t,
              tmpl::list<
                  Tags::deriv<gr::Tags::SpatialMetric<Dim, Frame::Inertial, T>,
                              tmpl::size_t<Dim>, Frame::Inertial>>{}));
  const auto inv_g =
      get<gr::Tags::InverseSpatialMetric<Dim, Frame::Inertial, T>>(
          minkowski.variables(
              x, t,
              tmpl::list<
                  gr::Tags::InverseSpatialMetric<Dim, Frame::Inertial, T>>{}));
  const auto extrinsic_curvature = get<
      gr::Tags::ExtrinsicCurvature<Dim, Frame::Inertial, T>>(
      minkowski.variables(
          x, t,
          tmpl::list<gr::Tags::ExtrinsicCurvature<Dim, Frame::Inertial, T>>{}));
  const auto det_g =
      get<gr::Tags::SqrtDetSpatialMetric<Dim, Frame::Inertial, T>>(
          minkowski.variables(
              x, t,
              tmpl::list<
                  gr::Tags::SqrtDetSpatialMetric<Dim, Frame::Inertial, T>>{}));
  const auto dt_det_g =
      get<Tags::dt<gr::Tags::SqrtDetSpatialMetric<Dim, Frame::Inertial, T>>>(
          minkowski.variables(
              x, t,
              tmpl::list<Tags::dt<
                  gr::Tags::SqrtDetSpatialMetric<Dim, Frame::Inertial, T>>>{}));

  CHECK(lapse.get() == one);
  CHECK(dt_lapse.get() == zero);
  CHECK(det_g.get() == one);
  for (size_t i = 0; i < Dim; ++i) {
    CHECK(shift.get(i) == zero);
    CHECK(dt_shift.get(i) == zero);
    CHECK(d_lapse.get(i) == zero);
    CHECK(g.get(i, i) == one);
    CHECK(inv_g.get(i, i) == one);
    for (size_t j = 0; j < i; ++j) {
      CHECK(g.get(i, j) == zero);
      CHECK(inv_g.get(i, j) == zero);
    }
    for (size_t j = 0; j < Dim; ++j) {
      CHECK(dt_g.get(i, j) == zero);
      CHECK(extrinsic_curvature.get(i, j) == zero);
      for (size_t k = 0; k < Dim; ++k) {
        CHECK(d_g.get(i, j, k) == zero);
      }
    }
  }
  test_serialization(minkowski);
  // test operator !=
  CHECK_FALSE(minkowski != minkowski);
}

template <size_t Dim>
void test_option_creation() {
  test_creation<EinsteinSolutions::Minkowski<Dim>>("");
}
}  // namespace

SPECTRE_TEST_CASE(
    "Unit.PointwiseFunctions.AnalyticSolutions.EinsteinSolution.Minkowski",
    "[PointwiseFunctions][Unit]") {
  const double x = 1.2;
  const DataVector x_dv{1., 2., 3.};

  test_minkowski<1>(x);
  test_minkowski<1>(x_dv);
  test_minkowski<2>(x);
  test_minkowski<2>(x_dv);
  test_minkowski<3>(x);
  test_minkowski<3>(x_dv);

  test_option_creation<1>();
  test_option_creation<2>();
  test_option_creation<3>();
}
