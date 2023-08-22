#pragma once
#ifndef ET_SRC_SIMPLE_H_
#define ET_SRC_SIMPLE_H_
#include "handler.h"
namespace et {
class SimpleXOR : public CryptoHandler,
                  public RegistHelper<SimpleXOR, const std::string&> {
 public:
  SimpleXOR(const std::string& seed);
  virtual Code Encode(const std::string& key, std::string* out) override;
  virtual Code Decode(const std::string& key, std::string* out) override;

 private:
  unsigned char xor_seed_;
};
}  // namespace et
#endif  // ET_SRC_SIMPLE_H_