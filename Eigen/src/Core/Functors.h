// This file is part of Eigen, a lightweight C++ template library
// for linear algebra. Eigen itself is part of the KDE project.
//
// Copyright (C) 2008 Gael Guennebaud <g.gael@free.fr>
//
// Eigen is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// Eigen is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// Eigen. If not, see <http://www.gnu.org/licenses/>.

#ifndef EIGEN_FUNCTORS_H
#define EIGEN_FUNCTORS_H

// associative functors:

/** \internal
  * \brief Template functor to compute the sum of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::operator+, class PartialRedux, MatrixBase::sum()
  */
template<typename Scalar> struct ei_scalar_sum_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a, const Scalar& b) const { return a + b; }
  template<typename PacketScalar>
  inline const PacketScalar packetOp(const PacketScalar& a, const PacketScalar& b) const
  { return ei_padd(a,b); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_sum_op<Scalar> > {
  enum {
    Cost = NumTraits<Scalar>::AddCost,
    PacketAccess = ei_packet_traits<Scalar>::size>1
  };
};

/** \internal
  * \brief Template functor to compute the product of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::cwiseProduct(), class PartialRedux, MatrixBase::redux()
  */
template<typename Scalar> struct ei_scalar_product_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a, const Scalar& b) const { return a * b; }
  template<typename PacketScalar>
  inline const PacketScalar packetOp(const PacketScalar& a, const PacketScalar& b) const
  { return ei_pmul(a,b); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_product_op<Scalar> > {
  enum {
    Cost = NumTraits<Scalar>::MulCost,
    PacketAccess = ei_packet_traits<Scalar>::size>1
  };
};

/** \internal
  * \brief Template functor to compute the min of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::cwiseMin, class PartialRedux, MatrixBase::minCoeff()
  */
template<typename Scalar> struct ei_scalar_min_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a, const Scalar& b) const { return std::min(a, b); }
  template<typename PacketScalar>
  inline const PacketScalar packetOp(const PacketScalar& a, const PacketScalar& b) const
  { return ei_pmin(a,b); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_min_op<Scalar> > {
  enum {
    Cost = NumTraits<Scalar>::AddCost,
    PacketAccess = ei_packet_traits<Scalar>::size>1
  };
};

/** \internal
  * \brief Template functor to compute the max of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::cwiseMax, class PartialRedux, MatrixBase::maxCoeff()
  */
template<typename Scalar> struct ei_scalar_max_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a, const Scalar& b) const { return std::max(a, b); }
  template<typename PacketScalar>
  inline const PacketScalar packetOp(const PacketScalar& a, const PacketScalar& b) const
  { return ei_pmax(a,b); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_max_op<Scalar> > {
  enum {
    Cost = NumTraits<Scalar>::AddCost,
    PacketAccess = ei_packet_traits<Scalar>::size>1
  };
};


// other binary functors:

/** \internal
  * \brief Template functor to compute the difference of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::operator-
  */
template<typename Scalar> struct ei_scalar_difference_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a, const Scalar& b) const { return a - b; }
  template<typename PacketScalar>
  inline const PacketScalar packetOp(const PacketScalar& a, const PacketScalar& b) const
  { return ei_psub(a,b); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_difference_op<Scalar> > {
  enum {
    Cost = NumTraits<Scalar>::AddCost,
    PacketAccess = ei_packet_traits<Scalar>::size>1
  };
};

/** \internal
  * \brief Template functor to compute the quotient of two scalars
  *
  * \sa class CwiseBinaryOp, MatrixBase::cwiseQuotient()
  */
template<typename Scalar> struct ei_scalar_quotient_op EIGEN_EMPTY_STRUCT {
    inline const Scalar operator() (const Scalar& a, const Scalar& b) const { return a / b; }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_quotient_op<Scalar> >
{ enum { Cost = 2 * NumTraits<Scalar>::MulCost, PacketAccess = false }; };


// unary functors:

/** \internal
  * \brief Template functor to compute the opposite of a scalar
  *
  * \sa class CwiseUnaryOp, MatrixBase::operator-
  */
template<typename Scalar> struct ei_scalar_opposite_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a) const { return -a; }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_opposite_op<Scalar> >
{ enum { Cost = NumTraits<Scalar>::AddCost, PacketAccess = false }; };

/** \internal
  * \brief Template functor to compute the absolute value of a scalar
  *
  * \sa class CwiseUnaryOp, MatrixBase::cwiseAbs
  */
template<typename Scalar> struct ei_scalar_abs_op EIGEN_EMPTY_STRUCT {
  typedef typename NumTraits<Scalar>::Real result_type;
  inline const result_type operator() (const Scalar& a) const { return ei_abs(a); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_abs_op<Scalar> >
{ enum { Cost = NumTraits<Scalar>::AddCost, PacketAccess = false }; };

/** \internal
  * \brief Template functor to compute the squared absolute value of a scalar
  *
  * \sa class CwiseUnaryOp, MatrixBase::cwiseAbs2
  */
template<typename Scalar> struct ei_scalar_abs2_op EIGEN_EMPTY_STRUCT {
  typedef typename NumTraits<Scalar>::Real result_type;
  inline const result_type operator() (const Scalar& a) const { return ei_abs2(a); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_abs2_op<Scalar> >
{ enum { Cost = NumTraits<Scalar>::MulCost, PacketAccess = false }; };

/** \internal
  * \brief Template functor to compute the conjugate of a complex value
  *
  * \sa class CwiseUnaryOp, MatrixBase::conjugate()
  */
template<typename Scalar> struct ei_scalar_conjugate_op EIGEN_EMPTY_STRUCT {
  inline const Scalar operator() (const Scalar& a) const { return ei_conj(a); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_conjugate_op<Scalar> >
{ enum { Cost = NumTraits<Scalar>::IsComplex ? NumTraits<Scalar>::AddCost : 0, PacketAccess = false }; };

/** \internal
  * \brief Template functor to cast a scalar to another type
  *
  * \sa class CwiseUnaryOp, MatrixBase::cast()
  */
template<typename Scalar, typename NewType>
struct ei_scalar_cast_op EIGEN_EMPTY_STRUCT {
  typedef NewType result_type;
  inline const NewType operator() (const Scalar& a) const { return static_cast<NewType>(a); }
};
template<typename Scalar, typename NewType>
struct ei_functor_traits<ei_scalar_cast_op<Scalar,NewType> >
{ enum { Cost = ei_is_same_type<Scalar, NewType>::ret ? 0 : NumTraits<NewType>::AddCost, PacketAccess = false }; };

/** \internal
  * \brief Template functor to extract the real part of a complex
  *
  * \sa class CwiseUnaryOp, MatrixBase::real()
  */
template<typename Scalar>
struct ei_scalar_real_op EIGEN_EMPTY_STRUCT {
  typedef typename NumTraits<Scalar>::Real result_type;
  inline result_type operator() (const Scalar& a) const { return ei_real(a); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_real_op<Scalar> >
{ enum { Cost =  0, PacketAccess = false }; };

/** \internal
  * \brief Template functor to multiply a scalar by a fixed other one
  *
  * \sa class CwiseUnaryOp, MatrixBase::operator*, MatrixBase::operator/
  */
template<typename Scalar, bool PacketAccess = (int(ei_packet_traits<Scalar>::size)>1?true:false) > struct ei_scalar_multiple_op;

template<typename Scalar>
struct ei_scalar_multiple_op<Scalar,true> {
  typedef typename ei_packet_traits<Scalar>::type PacketScalar;
  inline ei_scalar_multiple_op(const Scalar& other) : m_other(ei_pset1(other)) { }
  inline Scalar operator() (const Scalar& a) const { return a * ei_pfirst(m_other); }
  inline const PacketScalar packetOp(const PacketScalar& a) const
  { return ei_pmul(a, m_other); }
  const PacketScalar m_other;
};
template<typename Scalar>
struct ei_scalar_multiple_op<Scalar,false> {
  inline ei_scalar_multiple_op(const Scalar& other) : m_other(other) { }
  inline Scalar operator() (const Scalar& a) const { return a * m_other; }
  const Scalar m_other;
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_multiple_op<Scalar> >
{ enum { Cost = NumTraits<Scalar>::MulCost, PacketAccess = ei_packet_traits<Scalar>::size>1 }; };

template<typename Scalar, bool HasFloatingPoint>
struct ei_scalar_quotient1_impl {
  inline ei_scalar_quotient1_impl(const Scalar& other) : m_other(static_cast<Scalar>(1) / other) {}
  inline Scalar operator() (const Scalar& a) const { return a * m_other; }
  const Scalar m_other;
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_quotient1_impl<Scalar,true> >
{ enum { Cost = NumTraits<Scalar>::MulCost, PacketAccess = false }; };

template<typename Scalar>
struct ei_scalar_quotient1_impl<Scalar,false> {
  inline ei_scalar_quotient1_impl(const Scalar& other) : m_other(other) {}
  inline Scalar operator() (const Scalar& a) const { return a / m_other; }
  const Scalar m_other;
  enum { Cost = 2 * NumTraits<Scalar>::MulCost };
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_quotient1_impl<Scalar,false> >
{ enum { Cost = 2 * NumTraits<Scalar>::MulCost, PacketAccess = false }; };

/** \internal
  * \brief Template functor to divide a scalar by a fixed other one
  *
  * This functor is used to implement the quotient of a matrix by
  * a scalar where the scalar type is not a floating point type.
  *
  * \sa class CwiseUnaryOp, MatrixBase::operator/
  */
template<typename Scalar>
struct ei_scalar_quotient1_op : ei_scalar_quotient1_impl<Scalar, NumTraits<Scalar>::HasFloatingPoint > {
  inline ei_scalar_quotient1_op(const Scalar& other)
    : ei_scalar_quotient1_impl<Scalar, NumTraits<Scalar>::HasFloatingPoint >(other) {}
};

// nullary functors

template<typename Scalar, bool PacketAccess = (int(ei_packet_traits<Scalar>::size)>1?true:false) > struct ei_scalar_constant_op;

template<typename Scalar>
struct ei_scalar_constant_op<Scalar,true> {
  typedef typename ei_packet_traits<Scalar>::type PacketScalar;
  inline ei_scalar_constant_op(const Scalar& other) : m_other(ei_pset1(other)) { }
  inline const Scalar operator() (int, int) const { return ei_pfirst(m_other); }
  inline const PacketScalar packetOp() const
  { return m_other; }
  const PacketScalar m_other;
};
template<typename Scalar>
struct ei_scalar_constant_op<Scalar,false> {
  inline ei_scalar_constant_op(const Scalar& other) : m_other(other) { }
  inline const Scalar operator() (int, int) const { return m_other; }
  const Scalar m_other;
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_constant_op<Scalar> >
{ enum { Cost = 1, PacketAccess = ei_packet_traits<Scalar>::size>1, IsRepeatable = true }; };

template<typename Scalar> struct ei_scalar_identity_op EIGEN_EMPTY_STRUCT {
  inline ei_scalar_identity_op(void) {}
  inline const Scalar operator() (int row, int col) const { return row==col ? Scalar(1) : Scalar(0); }
};
template<typename Scalar>
struct ei_functor_traits<ei_scalar_identity_op<Scalar> >
{ enum { Cost = NumTraits<Scalar>::AddCost, PacketAccess = false, IsRepeatable = true }; };

#endif // EIGEN_FUNCTORS_H
