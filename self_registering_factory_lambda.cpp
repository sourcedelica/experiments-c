#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <functional>

// From http://www.bfilipek.com/2018/02/factory-selfregister.html

class ZipCompression;
class BZCompression;

class ICompressionMethod
{
public:
    ICompressionMethod() = default;
    virtual ~ICompressionMethod() = default;

    virtual void Compress() = 0;
};

class ZipCompression : virtual public ICompressionMethod
{
public:
    ZipCompression() = default;
    virtual ~ZipCompression() = default;

    virtual void Compress() override {
        std::cout << "Using ZIP compression\n";
    };

private:
    static bool s_registered;
};

class BZCompression : virtual public ICompressionMethod
{
public:
    BZCompression() = default;
    virtual ~BZCompression() = default;

    virtual void Compress() override {
        std::cout << "Using BZ compression\n";
    };

private:
    static bool s_registered;
};

class CompressionMethodFactory {
public:
    using TCreateMethod = std::function<std::unique_ptr<ICompressionMethod>()>;

    CompressionMethodFactory() = default;
    virtual ~CompressionMethodFactory() = default;

    static std::unique_ptr<ICompressionMethod>
    Create(const std::string& fileName)
    {
        auto extension = GetExtension(fileName);
        auto it = s_methods.find(extension);
        if (it != s_methods.end()) {
            return it->second(); // call the createFunc
        }

        return nullptr;
    }

    static std::string
    GetExtension(const std::string& fileName)
    {
        size_t dot_pos = fileName.rfind('.');
        return std::string(fileName, dot_pos+1, fileName.length() - dot_pos-1);
    }

    static bool
    Register(const std::string name, TCreateMethod funcCreate) {
        auto it = s_methods.find(name);
        if (it == s_methods.end()) { 
            s_methods[name] = funcCreate;
            return true;
        }
        return false;
    }
    template <typename T>
    static bool
    Register(const std::string name) {
        auto it = s_methods.find(name);
        if (it == s_methods.end())
        {
            s_methods[name] = []() -> std::unique_ptr<ICompressionMethod> {return std::make_unique<T>(); };
            return true;
        }
        return false;
    }
private:
    static std::map<std::string, TCreateMethod> s_methods;
};

std::map<std::string, CompressionMethodFactory::TCreateMethod> CompressionMethodFactory::s_methods;

bool ZipCompression::s_registered =
        CompressionMethodFactory::Register<ZipCompression>("zip");

bool BZCompression::s_registered =
        CompressionMethodFactory::Register("bz", []() -> std::unique_ptr<ICompressionMethod> {return std::make_unique<BZCompression>();});

int main(int argc, char const *argv[]) {
    std::vector<std::string> files{"archive.zip", "archive.bz", "archive.tar"};

    for(auto file: files) {
        auto compression = CompressionMethodFactory::Create(file);
        if(static_cast<bool>(compression)) {
            compression->Compress();
        }
        else {
            std::cerr << "No compression method registered for " << file << std::endl;
        }
    }

    return 0;
}
