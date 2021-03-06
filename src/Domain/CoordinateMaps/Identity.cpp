// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "Domain/CoordinateMaps/Identity.hpp"

#include "DataStructures/Tensor/Identity.hpp"
#include "DataStructures/Tensor/Tensor.hpp"
#include "ErrorHandling/Assert.hpp"
#include "Utilities/DereferenceWrapper.hpp"
#include "Utilities/GenerateInstantiations.hpp"
#include "Utilities/MakeWithValue.hpp"

namespace CoordinateMaps {

template <size_t Dim>
template <typename T>
std::array<tt::remove_cvref_wrap_t<T>, Dim> Identity<Dim>::operator()(
    const std::array<T, Dim>& source_coords) const noexcept {
  return make_array<tt::remove_cvref_wrap_t<T>, Dim>(source_coords);
}

template <size_t Dim>
template <typename T>
std::array<tt::remove_cvref_wrap_t<T>, Dim> Identity<Dim>::inverse(
    const std::array<T, Dim>& target_coords) const noexcept {
  return make_array<tt::remove_cvref_wrap_t<T>, Dim>(target_coords);
}

template <size_t Dim>
template <typename T>
tnsr::Ij<tt::remove_cvref_wrap_t<T>, Dim, Frame::NoFrame>
Identity<Dim>::jacobian(const std::array<T, Dim>& source_coords) const
    noexcept {
  return identity<Dim>(dereference_wrapper(source_coords[0]));
}

template <size_t Dim>
template <typename T>
tnsr::Ij<tt::remove_cvref_wrap_t<T>, Dim, Frame::NoFrame>
Identity<Dim>::inv_jacobian(const std::array<T, Dim>& source_coords) const
    noexcept {
  return identity<Dim>(dereference_wrapper(source_coords[0]));
}

template class Identity<1>;
template class Identity<2>;
// Identity should only be used in ProductMaps if a particular dimension is
// unaffected.  So if the largest dim we do is 3, then you should never use
// Identity<3>

// Explicit instantiations
/// \cond
#define DIM(data) BOOST_PP_TUPLE_ELEM(0, data)
#define DTYPE(data) BOOST_PP_TUPLE_ELEM(1, data)

#define INSTANTIATE(_, data)                                                   \
  template std::array<tt::remove_cvref_wrap_t<DTYPE(data)>, DIM(data)>         \
  Identity<DIM(data)>::operator()(                                             \
      const std::array<DTYPE(data), DIM(data)>& source_coords) const noexcept; \
  template std::array<tt::remove_cvref_wrap_t<DTYPE(data)>, DIM(data)>         \
  Identity<DIM(data)>::inverse(                                                \
      const std::array<DTYPE(data), DIM(data)>& target_coords) const noexcept; \
  template tnsr::Ij<tt::remove_cvref_wrap_t<DTYPE(data)>, DIM(data),           \
                    Frame::NoFrame>                                            \
  Identity<DIM(data)>::jacobian(                                               \
      const std::array<DTYPE(data), DIM(data)>& source_coords) const noexcept; \
  template tnsr::Ij<tt::remove_cvref_wrap_t<DTYPE(data)>, DIM(data),           \
                    Frame::NoFrame>                                            \
  Identity<DIM(data)>::inv_jacobian(                                           \
      const std::array<DTYPE(data), DIM(data)>& source_coords) const noexcept;

GENERATE_INSTANTIATIONS(INSTANTIATE, (1, 2),
                        (double, DataVector,
                         std::reference_wrapper<const double>,
                         std::reference_wrapper<const DataVector>))

#undef DIM
#undef DTYPE
#undef INSTANTIATE
/// \endcond

}  // namespace CoordinateMaps
