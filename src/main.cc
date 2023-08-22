#include <array>
#include <iostream>
#include <string>

#include "encryption_tool.h"
#include "gflags/gflags.h"

DEFINE_string(crypto, "simple_xor",
              "Select the encryption algorithm type, include [simple_xor]");
DEFINE_bool(encode, true, "Is encode or decode");
DEFINE_string(seed, "_seed_", "Encryption algorithm seed");
DEFINE_string(input, "", "The raw string what need encode or decode");

int main(int argc, char* argv[]) {
  gflags :: SetUsageMessage ( "Usage : Encryption Tool " ) ;
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (FLAGS_seed.empty() || FLAGS_input.empty()) {
    std::cout << "seed or source can't empty" << std::endl;
    return 1;
  }

  auto handler = et::CryptoFactory<const std::string&>::GetCryptoHandler(
      FLAGS_crypto, FLAGS_seed);
  std::string out;

  if (FLAGS_encode) {
    auto code = handler->Encode(FLAGS_input, &out);
    if (code == et::Code::SUCCESS) {
      std::cout << "===================== Encode String ===================\n"
                << out << std::endl;
    } else {
      std::cout << "encode failed" << std::endl;
      return 2;
    }
  } else {
    auto code = handler->Decode(FLAGS_input, &out);
    if (code == et::Code::SUCCESS) {
      std::cout << "===================== Decode String ===================\n"
                << out << std::endl;
    } else {
      std::cout << "decode failed" << std::endl;
      return 2;
    }
  }
  return 0;
}