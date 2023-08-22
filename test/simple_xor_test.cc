#include "simple_xor.h"

#include "encryption_tool.h"
#include "gtest/gtest.h"

TEST(Simple_XOR, encode) {
  std::string crypto_name = "simple_xor";
  std::string seed = "_seed_";
  auto handler = std::dynamic_pointer_cast<et::SimpleXOR>(
      et::CryptoFactory<const std::string&>::GetCryptoHandler(crypto_name,
                                                              seed));
  ASSERT_NE(nullptr, handler);
  std::string out;
  std::string raw_string = "abcdefghijklmnopqrstuvwxyz";
  auto code = handler->Encode(raw_string, &out);
  EXPECT_EQ(et::Code::SUCCESS, code);
  EXPECT_EQ("91817161514131B1A1@1?1>1=1<1;1*1)1(1'1&1%1$1#1211101", out);

  raw_string = "0123456789";
  code = handler->Encode(raw_string, &out);
  EXPECT_EQ(et::Code::SUCCESS, code);
  EXPECT_EQ("H0G0F0E0D0C0B0A0P0O0", out);

  raw_string = "`~!@#$%^&*()_+-={}[]|\\:\";'<>,./?";
  code = handler->Encode(raw_string, &out);
  EXPECT_EQ(et::Code::SUCCESS, code);
  EXPECT_EQ(":1,1W0x0U0T0S0j0R0^0`0_0i0]0[0K0/1-1m0k0.1l0N0V0M0Q0L0J0\\0Z0Y0I0",
            out);
}

TEST(Simple_XOR, decode) {
  std::string crypto_name = "simple_xor";
  std::string seed = "_seed_";
  auto handler = std::dynamic_pointer_cast<et::SimpleXOR>(
      et::CryptoFactory<const std::string&>::GetCryptoHandler(crypto_name,
                                                              seed));
  ASSERT_NE(nullptr, handler);
  std::string out;
  std::string raw_string =
      "91817161514131B1A1@1?1>1=1<1;1*1)1(1'1&1%1$1#1211101";
  auto code = handler->Decode(raw_string, &out);
  EXPECT_EQ(et::Code::SUCCESS, code);
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", out);

  raw_string = "H0G0F0E0D0C0B0A0P0O0";
  code = handler->Decode(raw_string, &out);
  EXPECT_EQ(et::Code::SUCCESS, code);
  EXPECT_EQ("0123456789", out);

  raw_string =
      ":1,1W0x0U0T0S0j0R0^0`0_0i0]0[0K0/1-1m0k0.1l0N0V0M0Q0L0J0\\0Z0Y0I0";
  code = handler->Decode(raw_string, &out);
  EXPECT_EQ(et::Code::SUCCESS, code);
  EXPECT_EQ("`~!@#$%^&*()_+-={}[]|\\:\";'<>,./?", out);
}