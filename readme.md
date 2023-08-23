# encryption tool
加解密工具，可以通过命令行将密码进行加密或进行解密，并支持通过lib库的方式引入项目中对文本进行加解密。
### 命令行使用方法
```shell
./encryption_tool --help

encryption_tool: Usage : Encryption Tool
    -crypto (Select the encryption algorithm type, include [simple_xor])
      type: string default: "simple_xor"
    -encode (Is encode or decode) type: bool default: true
    -input (The raw string what need encode or decode) type: string default: ""
    -seed (Encryption algorithm seed) type: string default: "_seed_"
```
例如加密 `abcdefg` 
```shell
./encryption_tool --input="abcdefg" 

===================== Encode String ===================
91817161514131
```
对生成的密码进行解密
```shell
./encryption_tool --input="91817161514131" --noencode

===================== Decode String ===================
abcdefg
```

### 库使用方式
```c++
//get ptr of crypto handler
std::string crypto_type = "simple_xor";
std::string seed = "_seed_";
auto handler = et::CryptoFactory<const std::string&>::GetCryptoHandler(crypto_type, seed);

std::string out;
//encode 
std::string raw_string = "abcdefg";
auto code = handler->Encode(raw_string, &out);
if (code == et::Code::SUCCESS) {
    //success
} else {
    //failed
}

//decode
std::string encode_string = "91817161514131";
code = handler->Decode(, &out);
if (code == et::Code::SUCCESS) {
    //success
} else {
    //failed
}

```

### 扩展加密算法
新加扩展方法需要继承 CryptoHandler 与 RegistHelper类 
```c++
class SomeAlgorithm : public CryptoHandler,public RegistHelper<SomeAlgorithm, construct Args Type...> 
{
};
```
实现加密与解密方法
```c++
Code Encode(const std::string& key, std::string* out);
Code Decode(const std::string& key, std::string* out);
```
进行注册
```c++
const bool some_algorithm_registered = []() {
  return SomeAlgorithm::Register("algorithm_name");
}();
```
