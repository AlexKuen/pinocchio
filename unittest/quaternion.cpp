//
// Copyright (c) 2019 INRIA
//

#include <pinocchio/math/quaternion.hpp>
#include <pinocchio/spatial/se3.hpp>

#include <boost/variant.hpp> // to avoid C99 warnings

#include <boost/test/unit_test.hpp>
#include <boost/utility/binary.hpp>

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

BOOST_AUTO_TEST_CASE(test_assignQuaternion)
{
  using namespace pinocchio;
  const int max_tests = 1e5;
  for(int k = 0; k < max_tests; ++k)
  {
    const SE3 M(SE3::Random());
    SE3::Quaternion quat_ref(M.rotation());
    
    SE3::Quaternion quat;
    quaternion::assignQuaternion(quat,M.rotation());
    
    BOOST_CHECK(quat.coeffs().isApprox(quat_ref.coeffs()));
  }
}

BOOST_AUTO_TEST_CASE(test_uniformRandom)
{
  srand(0);

  using namespace pinocchio;
  Eigen::Quaternion<double> q;

  for (int i = 0; i < (1 << 10); ++i) {
    quaternion::uniformRandom(q);
    BOOST_CHECK_MESSAGE((q.coeffs().array().abs() <= 1).all(),
        "Quaternion coeffs out of bounds: " << i << ' ' << q.coeffs().transpose());
  }
}

BOOST_AUTO_TEST_SUITE_END()

