#include "simple_xor.h"

#include <sstream>
#include <vector>
namespace et {
const bool simple_xor_registered = []() {
  return SimpleXOR::Register("simple_xor");
}();

SimpleXOR::SimpleXOR(const std::string& seed) : CryptoHandler(seed) {
  xor_seed_ = 0;
  for (auto& c : seed) {
    xor_seed_ ^= c;
  }
}
Code SimpleXOR::Encode(const std::string& key, std::string* out) {
  if (seed_.empty()) {
    return Code::INVALID_PARAMETER;
  }
  std::stringstream ss;
  for (auto& c : key) {
    unsigned char tmp = c ^ xor_seed_;
    int i = tmp / 94;
    char char_value = tmp % 94+33;
    ss << char_value << i;
  }
  *out = ss.str();
  return Code::SUCCESS;
}
Code SimpleXOR::Decode(const std::string& key, std::string* out) {
  if (seed_.empty()) {
    return Code::INVALID_PARAMETER;
  }
  if (key.size() % 2 != 0) {
    return Code::UNABLE_PARSE;
  }
  std::stringstream ss;
  for (size_t i = 0; i < key.size(); i += 2) {
    unsigned char c =  key[i] - 33 + (key[i + 1] - 48) * 94;
    char value = c ^ xor_seed_;
    ss << value;
  }
  *out = ss.str();
  return Code::SUCCESS;
}

}  // namespace et