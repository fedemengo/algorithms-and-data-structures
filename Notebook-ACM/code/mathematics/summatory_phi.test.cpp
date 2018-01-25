void test() {
  ll mod = 1000000007;
  sieve();
  assert_equal(0LL, sumphi(0)%mod);
  assert_equal(1LL, sumphi(1)%mod);
  assert_equal(2LL, sumphi(2)%mod);
  assert_equal(136415389LL, sumphi(468934026)%mod);
  assert_equal(4950106LL, sumphi(4035)%mod);
  assert_equal(16715094LL, sumphi(7415)%mod);
  assert_equal(767394854LL, sumphi(436405898)%mod);
  assert_equal(538772852LL, sumphi(306252504)%mod);
  assert_equal(830504330LL, sumphi(5986315)%mod);
  assert_equal(322542318LL, sumphi(282399104)%mod);
  assert_equal(26934956LL, sumphi(313615971)%mod);
  assert_equal(25908444LL, sumphi(9232)%mod);
  assert_equal(875833396LL, sumphi(823404011)%mod);
  assert_equal(19445022LL, sumphi(7998)%mod);
  assert_equal(14935782LL, sumphi(7009)%mod);
  assert_equal(429630492LL, sumphi(663092807)%mod);
  assert_equal(136080706LL, sumphi(97761937)%mod);
  assert_equal(29501538LL, sumphi(9851)%mod);
  assert_equal(471526669LL, sumphi(97855063)%mod);
  assert_equal(473402546LL, sumphi(655967237)%mod);
  assert_equal(124522231LL, sumphi(75014346)%mod);
  assert_equal(11385300LL, sumphi(6120)%mod);
  assert_equal(747109978LL, sumphi(876798774)%mod);
  assert_equal(589997937LL, sumphi(15157285)%mod);
  assert_equal(11422LL, sumphi(193)%mod);
  assert_equal(26153850LL, sumphi(9276)%mod);
  assert_equal(451314620LL, sumphi(416613497)%mod);
  assert_equal(663057837LL, sumphi(170289002)%mod);
  assert_equal(667342LL, sumphi(1481)%mod);
  assert_equal(239601848LL, sumphi(405598578)%mod);
  assert_equal(884176LL, sumphi(1705)%mod);
  assert_equal(782683770LL, sumphi(32888478)%mod);
  assert_equal(905152095LL, sumphi(223714457)%mod);
  assert_equal(32LL, sumphi(10)%mod);
  assert_equal(3044LL, sumphi(100)%mod);
  assert_equal(304192LL, sumphi(1000)%mod);
  assert_equal(30397486LL, sumphi(10000)%mod);
  assert_equal(3039650754LL, sumphi(100000));
  assert_equal(303963551173008414LL, sumphi(1000000000));
}