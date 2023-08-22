#pragma once
#ifndef ET_SRC_HANDLER_H_
#define ET_SRC_HANDLER_H_
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace et {
enum Code { SUCCESS = 0, INVALID_PARAMETER, UNABLE_PARSE, INTERNAL_ERROR };

class CryptoHandler : public std::enable_shared_from_this<CryptoHandler> {
 public:
  explicit CryptoHandler(const std::string& seed) : seed_(seed){};
  void SetSeed(const std::string& seed) { seed_ = seed; }
  std::string GetSeed() { return seed_; }
  virtual Code Encode(const std::string& key, std::string* out) = 0;
  virtual Code Decode(const std::string& key, std::string* out) = 0;

 protected:
  std::string seed_;
};

template <typename... Args>
class CryptoHelper {
 public:
  static CryptoHelper& Instance() {
    static CryptoHelper<Args...> helper_;
    return helper_;
  }

  virtual ~CryptoHelper(){};

  bool Regist(
      const std::string& name,
      std::function<std::shared_ptr<CryptoHandler>(Args&&... args)> func) {
    if (nullptr == func) {
      return (false);
    }
    bool reg = createor_mapping_.emplace(name, func).second;
    return (reg);
  }

  std::shared_ptr<CryptoHandler> Create(const std::string& name,
                                        Args&&... args) {
    auto iter = createor_mapping_.find(name.data());
    if (iter == createor_mapping_.end()) {
      return (nullptr);
    } else {
      return (iter->second(std::forward<Args>(args)...));
    }
  }

 private:
  CryptoHelper(){};

  std::unordered_map<std::string, std::function<std::shared_ptr<CryptoHandler>(
                                      Args&&... args)>>
      createor_mapping_;
};
template <typename... Args>
class CryptoFactory {
 public:
  static std::shared_ptr<CryptoHandler> GetCryptoHandler(
      const std::string& name, Args&&... args) {
    return CryptoHelper<Args...>::Instance().Create(
        name, std::forward<Args>(args)...);
  }
};

template <typename T, typename... Args>
class RegistHelper {
 public:
  static bool Register(const std::string& name) {
    // #ifndef _MSC_VER
    //     std::cout << "register " << name << " Args is " <<
    //     __PRETTY_FUNCTION__
    //               << std::endl;
    // #else
    //     std::cout << "register " << name << " Args is " << __FUNCSIG__ <<
    //     std::endl;
    // #endif
    return CryptoHelper<Args...>::Instance().Regist(name, CreateObject);
  }
  RegistHelper() {}
  virtual ~RegistHelper(){};

  static std::shared_ptr<T> CreateObject(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
};

}  // namespace et
#endif  // ET_SRC_HANDLER_H_