#ifndef MiniData_JSON_Included
#define MiniData_JSON_Included

#include <memory>
#include <istream>
#include <ostream>
#include <vector>
#include <map>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace MiniData_JSONImpl {
  struct NullTag    {};
  struct BoolTag    {};
  struct IntegerTag {};
  struct DoubleTag  {};
  struct StringTag  {};
  struct ArrayTag   {};
  struct MapTag     {};

  template <typename T> struct IsJSONConvertible;
  template <typename T> struct IsString;
  
  class BaseJSON;
  class JSONSource;
}

/* 表示 JSON 格式值的类型。 */
class JSON {
public:
    /* 将指定值包装为 JSON 对象。此构造函数可接受
     * 接受以下任意类型作为输入：
     *
     *   nullptr_t
     *   bool
     *   任意整数类型
     *   任意浮点类型
     *   原始 C 字符串
     *   std::string
     *   数组
     *   任意由可转换为 JSON 的项目组成的顺序容器
     *   任何键类型可转换为 string、值类型可转换为 JSON 的关联容器
     */
    template <
      typename T,
      typename = typename std::enable_if<MiniData_JSONImpl::IsJSONConvertible<T>::value>::type
    > JSON(const T& value);

    /* 将一段文本解析为 JSON 格式。预期输入
     * 由完整 JSON 构成，且不含其他内容。若只读取一个 JSON 对象
     * 若要从流中读取，请使用 operator>>。
     */
    inline static JSON parse(std::istream& input);
    inline static JSON parse(const std::string& input);

    /* 构建数组或对象。 */
    inline static JSON array (std::initializer_list<JSON> elems = {});
    template <typename... T> static JSON array(const T&... args);
    
    inline static JSON object(std::initializer_list<std::pair<const std::string, JSON>> elems = {});

    /* 表示此对象类型的枚举。 */
    enum class Type {
        OBJECT,
        ARRAY,
        STRING,
        NUMBER,
        BOOLEAN,
        NULLPTR_T
    };

    /* 返回此对象的类型。 */
    inline Type type() const;

    /* 访问器。若底层类型不符合要求，所有这些函数都会抛出 JSONException
     * 不正确。
     */
    inline double         asDouble()  const;
    inline std::int64_t   asInteger() const;
    inline bool           asBoolean() const;
    inline std::nullptr_t asNull()    const;
    inline std::string    asString()  const;

    /* 数组访问器。同样，若底层类型不符合要求，则会抛出 JSONException
     * 不正确。
     */
    inline JSON operator[] (std::size_t index) const;

    /* 对象访问器。与往常一样，若底层类型不符合要求，则会抛出 JSONException
     * 不正确。
     */
    inline JSON operator[] (const std::string& field) const;

    /* 可转换为 string 的对象。 */
    template <
      typename String,
      typename = typename std::enable_if<MiniData_JSONImpl::IsString<String>::value>::type
    >
    JSON operator[] (const String& field) const {
      return (*this)[std::string(field)];
    }
    inline bool contains(const std::string& fieldName) const;
    
    /* 通用访问器。若包装的 JSON 对象是数字，则查找该索引处的元素，
     * 假定这是数组。若包装的 JSON 对象是字符串，则查找以下索引的元素：
     * 该键，假定这是一个对象。
     *
     * 使用包装的 double 调用此函数时要小心；任何舍入误差都会导致
     * 问题！
     */
    inline JSON operator[] (JSON key) const;

    /* 数组与对象共用。 */
    inline std::size_t size() const;

    /* 对于数组，遍历元素；对于对象，将键作为 JSON 字符串遍历。
     * 对于所有其他类型，报告错误。
     */
    class const_iterator;
    inline const_iterator begin()  const;
    inline const_iterator end()    const;
    inline const_iterator cbegin() const;
    inline const_iterator cend()   const;
    
    inline friend std::ostream& operator<< (std::ostream& out, JSON json);
    inline friend std::istream& operator>> (std::istream& in,  JSON& json);

private:
    friend class MiniData_JSONImpl::BaseJSON;
    std::shared_ptr<MiniData_JSONImpl::BaseJSON> mImpl;

    struct ConstructorTag {};
    inline JSON(std::shared_ptr<MiniData_JSONImpl::BaseJSON> impl, ConstructorTag);

    /* 根据相应类型的对象构造 JSON 对象。 */
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromNull(std::nullptr_t value);
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromDouble(double value);
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromInteger(std::int64_t value);
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromBoolean(bool value);
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromString(const std::string& value);

    /* 根据 JSON 对象列表构造 JSON 数组。 */
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromArray(const std::vector<JSON>& elems);

    /* 根据映射构造 JSON 对象。 */
    inline static std::shared_ptr<MiniData_JSONImpl::BaseJSON> fromMap(const std::map<std::string, JSON>& elems);

    /* 分派构造函数。 */
    template <typename T> JSON(MiniData_JSONImpl::NullTag,    const T& value) : mImpl(fromNull(value)) {}
    template <typename T> JSON(MiniData_JSONImpl::BoolTag,    const T& value) : mImpl(fromBoolean(value)) {}
    template <typename T> JSON(MiniData_JSONImpl::IntegerTag, const T& value) : mImpl(fromInteger(value)) {}
    template <typename T> JSON(MiniData_JSONImpl::DoubleTag,  const T& value) : mImpl(fromDouble(value)) {}
    template <typename T> JSON(MiniData_JSONImpl::StringTag,  const T& value) : mImpl(fromString(value)) {}
    template <typename T> JSON(MiniData_JSONImpl::ArrayTag,   const T& value) : 
      mImpl(fromArray(std::vector<JSON>(std::begin(value), std::end(value)))) {}
    template <typename T> JSON(MiniData_JSONImpl::MapTag,     const T& value) : 
      mImpl(fromMap(std::map<std::string, JSON>(std::begin(value), std::end(value)))) {}
};

class JSON::const_iterator {
public:
    /* 迭代器类型定义。 */
    typedef std::ptrdiff_t          difference_type;
    typedef const JSON              value_type;
    typedef const JSON*             pointer;
    typedef const JSON&             reference;
    typedef std::input_iterator_tag iterator_category;

    inline const_iterator();
    
    inline bool operator== (const_iterator rhs) const;
    inline bool operator!= (const_iterator rhs) const;
    
    inline const_iterator& operator++ ();
    inline const const_iterator operator++ (int);
    
    inline const JSON& operator* () const;
    inline const JSON* operator->() const;

private:
    friend class MiniData_JSONImpl::JSONSource;
    std::shared_ptr<MiniData_JSONImpl::JSONSource> mImpl;
    
    inline const_iterator(std::shared_ptr<MiniData_JSONImpl::JSONSource>);
};

/* 发生错误时抛出的异常类型。 */
class JSONException: public std::logic_error {
public:
    inline JSONException(const std::string& reason);
};

/***** 私有实现细节 *****/
namespace MiniData_JSONImpl {
  /* 用于确定某对象最佳表示类型的 traits 类型。 */

  /* 这是空指针吗？ */
  template <typename T> struct IsNull {
    static const bool value = std::is_same<typename std::remove_cv<T>::type, std::nullptr_t>::value;
  };

  /* 这是布尔值吗？ */
  template <typename T> struct IsBool {
    static const bool value = std::is_same<typename std::remove_cv<T>::type, bool>::value;
  };

  /* 这是整数吗？ */
  template <typename T> struct IsInteger {
    /* 需要显式排除 bool。 */
    static const bool value = !IsBool<T>::value && std::is_integral<T>::value;
  };

  /* 这是 double 吗？ */
  template <typename T> struct IsDouble {
    static const bool value = std::is_floating_point<T>::value;
  };

  /* 这是 C 风格字符串吗？ */
  template <typename T> struct IsString {
    static const bool value = std::is_convertible<T, std::string>::value;
  };
  /* 这是 JSON 数组吗？ */
  template <typename T> struct IsArray {
    /* std::begin 是否返回可转换为 JSON 的对象？ */
    template <typename U> static std::true_type  evaluate(int, typename std::enable_if<std::is_convertible<typename U::value_type, JSON>::value>::type* = nullptr);
    template <typename U> static std::false_type evaluate(...);

    static const bool value = std::is_same<decltype(evaluate<T>(0)), std::true_type>::value;
  }; 
  template <size_t N> struct IsArray<JSON [N]> {
    static const bool value = true;
  };
  template <size_t N> struct IsArray<const JSON [N]> {
    static const bool value = true;
  };

  /* 这是 JSON 映射吗？ */
  template <typename T> struct IsMap {
    /* std::begin 是否返回一种对象，其 .first 可转换为字符串，并且
     * .second 是否可以转换为 JSON？
     */
    template <typename U> using value_type = typename U::value_type;
    template <typename U> using k_type   = decltype(std::declval<value_type<U>>().first);
    template <typename U> using v_type = decltype(std::declval<value_type<U>>().second);
    template <typename U> static std::true_type  evaluate(int,
                                                          typename std::enable_if<IsString<k_type<U>>::value>* = nullptr,
                                                          typename std::enable_if<std::is_convertible<v_type<U>, JSON>::value>::type* = nullptr);
    template <typename U> static std::false_type evaluate(...);

    static const bool value = std::is_same<decltype(evaluate<T>(0)), std::true_type>::value;
  };

  template <typename T> struct TagFor {
    using type = typename std::conditional<IsNull<T>::value, NullTag,
                  typename std::conditional<IsBool<T>::value, BoolTag,
                    typename std::conditional<IsInteger<T>::value, IntegerTag,
                      typename std::conditional<IsDouble<T>::value, DoubleTag,
                        typename std::conditional<IsString<T>::value, StringTag,
                          typename std::conditional<IsArray<T>::value, ArrayTag,
                            typename std::conditional<IsMap<T>::value, MapTag, void>::type
                          >::type
                        >::type
                      >::type
                    >::type
                  >::type
                >::type;
  };

  template <typename T> struct IsJSONConvertible {
    static const bool value = !std::is_same<typename TagFor<T>::type, void>::value;
  };
}

/* 将参数转发给正确的构造函数。 */
template <typename T, typename> JSON::JSON(const T& value) : JSON(typename MiniData_JSONImpl::TagFor<T>::type(), value) {

}

/* 可变参数函数会转换为初始化列表。 */
template <typename... T> JSON JSON::array(const T&... args) {
  return array({ args... });
}

#include "Unicode.h"
#include <map>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <iomanip>
#include <string>
#include <iterator>

/* 用于报告错误的实用函数。 */
namespace MiniData_JSONImpl {
    [[ noreturn ]] inline void jsonError(const std::string& message) {
        throw JSONException(message);
    }
    
    /* JSON 对象的内部基类型。 */
    class BaseJSON {
    public:
        virtual ~BaseJSON() = default;

        /* 返回此对象的类型。 */
        inline JSON::Type type() const;

        /* 将此对象输出到流。 */
        virtual void print(std::ostream& out) const = 0;

        /* 从 BaseJSON 直接构造 JSON 的后门路径。此路径用于
         * 因为 BaseJSON 是 JSON 的友元，所以可以调用其内部
         * 构造函数。
         */
        template <typename Type, typename... Args>
        static JSON make(Args&&... args) {
            return JSON(std::make_shared<Type>(std::forward<Args>(args)...), JSON::ConstructorTag());
        }

    protected:
        inline BaseJSON(JSON::Type type);

    private:
        JSON::Type mType;
    };

    /* 迭代器支持。此生成器类型用于以流的方式生成元素。 */
    class JSONSource {
    public:
        virtual ~JSONSource() = default;
        
        virtual void advance() = 0;
        virtual bool finished() const = 0;
        
        virtual const JSON& current() const = 0;
        
        /* 从 shared_ptr 构造 const_iterator。 */
        static JSON::const_iterator make(std::shared_ptr<JSONSource> impl) {
            return impl;
        }
    };

    /* 表示 null 的类型。 */
    class NullJSON: public BaseJSON {
    public:
        inline NullJSON(std::nullptr_t value);
        inline std::nullptr_t value() const;
        
        inline void print(std::ostream& out) const override;
    };

    /* 表示布尔值的类型。 */
    class BoolJSON: public BaseJSON {
    public:
        inline BoolJSON(bool value);
        inline bool value() const;
        
        inline void print(std::ostream& out) const override;

    private:
        bool mValue;
    };

    /* 表示某种数值的类型。 */
    class NumberJSON: public BaseJSON {
    public:
        inline NumberJSON();

        virtual double       asDouble() const  = 0;
        virtual std::int64_t asInteger() const = 0;
    };

    /* 整数和 double 的数字特化。 */
    template <typename NumericType> class NumericValueJSON: public NumberJSON {
    public:
        NumericValueJSON(NumericType value);
        
        inline double       asDouble()  const override;
        inline std::int64_t asInteger() const override;

        inline void print(std::ostream& out) const override;
        
    private:
        NumericType mValue;
    };

    /* 表示字符串的类型。 */
    class StringJSON: public BaseJSON {
    public:
        inline StringJSON(const std::string& value);
        inline std::string value() const;
        
        inline void print(std::ostream& out) const override;

    private:
        std::string mValue;
    };

    /* 表示可迭代对象的中间类型。 */
    class IterableJSON: public BaseJSON {
    public:
        inline IterableJSON(JSON::Type type);

        virtual std::size_t size() const = 0;
        virtual std::shared_ptr<JSONSource> source() const = 0;
    };

    /* 表示数组的类型。 */
    class ArrayJSON: public IterableJSON {
    public:
        inline ArrayJSON(const std::vector<JSON>& elems);

        inline std::size_t size() const override;
        inline JSON operator[] (std::size_t index) const;
        
        inline void print(std::ostream& out) const override;
        inline std::shared_ptr<JSONSource> source() const override;

    private:
        std::vector<JSON> mElems;
    };

    /* 表示对象的类型。 */
    class ObjectJSON: public IterableJSON {
    public:
        inline ObjectJSON(const std::map<std::string, JSON>& elems);

        inline bool contains(const std::string& key) const;
        inline JSON operator[] (const std::string& key) const;
        inline std::size_t size() const override;
        
        inline void print(std::ostream& out) const override;
        inline std::shared_ptr<JSONSource> source() const override;

    private:
        std::map<std::string, JSON> mElems;
    };

/***************************************************************************/
/***********          各个子类型的实现            ***********/
/***************************************************************************/

    /* 用于输出字符串的实用例程。 */
    inline void printString(std::ostream& out, const std::string& str) {
        out << '"';
    
        std::istringstream extractor(str);
        while (extractor.peek() != EOF) {
            char32_t ch = readChar(extractor);
            
            /* 确定该字符需要怎样编码。 */
            if      (ch == '"')  out << "\\\"";
            else if (ch == '\\') out << "\\\\";
            else if (ch == '/')  out << "\\/";
            else if (ch == '\b') out << "\\b";
            else if (ch == '\n') out << "\\n";
            else if (ch == '\r') out << "\\r";
            else if (ch == '\t') out << "\\t";
            else if (ch >= 0x20 && ch <= 0x7F) out << char(ch);
            else out << utf16EscapeFor(ch);
        }
        
        out << '"';
    }

    inline BaseJSON::BaseJSON(JSON::Type type) : mType(type) {

    }
    inline JSON::Type BaseJSON::type() const {
        return mType;
    }

    inline NullJSON::NullJSON(std::nullptr_t) : BaseJSON(JSON::Type::NULLPTR_T) {

    }

    inline std::nullptr_t NullJSON::value() const {
        return nullptr;
    }

    inline void NullJSON::print(std::ostream& out) const {
        out << "null";
    }

    inline StringJSON::StringJSON(const std::string& value) : BaseJSON(JSON::Type::STRING), mValue(value) {

    }

    inline std::string StringJSON::value() const {
        return mValue;
    }

    inline void StringJSON::print(std::ostream& out) const {
        printString(out, mValue);
    }

    inline NumberJSON::NumberJSON() : BaseJSON(JSON::Type::NUMBER) {

    }

    template <typename NumericType>
    NumericValueJSON<NumericType>::NumericValueJSON(NumericType value) : mValue(value) {

    }

    template <typename NumericType>
    double NumericValueJSON<NumericType>::asDouble() const {
        return static_cast<double>(mValue);
    }

    template <typename NumericType>
    int64_t NumericValueJSON<NumericType>::asInteger() const {
        return static_cast<int64_t>(mValue);
    }

    template <typename NumericType>
    void NumericValueJSON<NumericType>::print(std::ostream& out) const {
        out << mValue;
    }

    inline BoolJSON::BoolJSON(bool value) : BaseJSON(JSON::Type::BOOLEAN), mValue(value) {

    }

    inline bool BoolJSON::value() const {
        return mValue;
    }

    inline void BoolJSON::print(std::ostream& out) const {
        out << (mValue? "true" : "false");
    }

    inline IterableJSON::IterableJSON(JSON::Type type) : BaseJSON(type) {

    }

    inline ArrayJSON::ArrayJSON(const std::vector<JSON>& elems) : IterableJSON(JSON::Type::ARRAY), mElems(elems) {

    }

    inline std::size_t ArrayJSON::size() const {
        return mElems.size();
    }

    inline std::shared_ptr<JSONSource> ArrayJSON::source() const {
        /* Source 只包装一对迭代器。 */
        class VectorJSONSource: public JSONSource {
        public:
            VectorJSONSource(std::vector<JSON>::const_iterator curr, std::vector<JSON>::const_iterator end)
              : mCurr(curr), mEnd(end) {
              
            }
            
            void advance() override {
                ++mCurr;
            }
            bool finished() const override {
                return mCurr == mEnd;
            }
        
            const JSON& current() const override {
                return *mCurr;
            }
        
        private:
            std::vector<JSON>::const_iterator mCurr, mEnd;
        };
        
        return std::make_shared<VectorJSONSource>(mElems.begin(), mElems.end());
    }

    inline JSON ArrayJSON::operator[] (std::size_t index) const {
        if (index >= mElems.size()) {
            jsonError("Index out of range: " + std::to_string(index) + ", but size is " + std::to_string(size()));
        }
        return mElems[index];
    }

    inline void ArrayJSON::print(std::ostream& out) const {
        out << '[';
        for (size_t i = 0; i < mElems.size(); i++) {
            out << mElems[i] << (i + 1 == mElems.size()? "" : ",");
        }
        out << ']';
    }

    inline ObjectJSON::ObjectJSON(const std::map<std::string, JSON>& elems) : IterableJSON(JSON::Type::OBJECT), mElems(elems) {

    }

    inline bool ObjectJSON::contains(const std::string& key) const {
        return mElems.count(key);
    }

    inline JSON ObjectJSON::operator[](const std::string& key) const {
        if (!contains(key)) {
            jsonError("Key " + key + " does not exist.");
        }
        return mElems.at(key);
    }

    inline std::size_t ObjectJSON::size() const {
        return mElems.size();
    }

    inline void ObjectJSON::print(std::ostream& out) const {
        out << '{';
        for (auto itr = mElems.begin(); itr != mElems.end(); ++itr) {
            printString(out, itr->first);
            out << ":" << itr->second;
            if (next(itr) != mElems.end()) {
                out << ",";
            }
        }
        out << '}';
    }

    inline std::shared_ptr<JSONSource> ObjectJSON::source() const {
        /* Source 包装一对迭代器，并保存表示以下内容的 JSON 对象：
         * 当前字符串。
         */
        class MapJSONSource: public JSONSource {
        public:
            MapJSONSource(std::map<std::string, JSON>::const_iterator curr,
                          std::map<std::string, JSON>::const_iterator end)
              : mCurr(curr), mEnd(end), mStaged(nullptr) {
                if (mCurr != mEnd) {
                    mStaged = JSON(mCurr->first);
                }
            }
            
            void advance() override {
                ++mCurr;
                if (mCurr != mEnd) {
                    mStaged = JSON(mCurr->first);
                }
            }
            bool finished() const override {
                return mCurr == mEnd;
            }
        
            const JSON& current() const override {
                return mStaged;
            }
        
        private:
            std::map<std::string, JSON>::const_iterator mCurr, mEnd;
            JSON mStaged;
        };
        
        return std::make_shared<MapJSONSource>(mElems.begin(), mElems.end());
    }

/***************************************************************************/
/***********          JSON 访问器的实现           ***********/
/***************************************************************************/

    /* 安全地向下转换底层指针类型。 */
    template <typename Target> std::shared_ptr<Target> as(std::shared_ptr<BaseJSON> base) {
        auto result = std::dynamic_pointer_cast<Target>(base);
        if (!result) {
            std::ostringstream result;
            auto& baseObj = *base.get(); // 抑制 Mac 编译器针对 typeid 的警告
            (void) baseObj;              // 抑制 Linux 编译器警告
            result << "Wrong JSON type. Actual type is " << typeid(baseObj).name()
                   << ", which can't be converted to " << typeid(Target).name();
            jsonError(result.str());
        }
        return result;
    }
}

inline JSON::JSON(std::shared_ptr<MiniData_JSONImpl::BaseJSON> impl, ConstructorTag) : mImpl(impl) {

}
inline JSON::Type JSON::type() const {
    return mImpl->type();
}
inline std::nullptr_t JSON::asNull() const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::NullJSON>(mImpl)->value();
}
inline bool JSON::asBoolean() const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::BoolJSON>(mImpl)->value();
}
inline double JSON::asDouble() const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::NumberJSON>(mImpl)->asDouble();
}
inline std::int64_t JSON::asInteger() const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::NumberJSON>(mImpl)->asInteger();
}
inline std::string JSON::asString() const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::StringJSON>(mImpl)->value();
}
inline JSON JSON::operator [](std::size_t index) const {
    return (*MiniData_JSONImpl::as<MiniData_JSONImpl::ArrayJSON>(mImpl))[index];
}
inline std::size_t JSON::size() const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::IterableJSON>(mImpl)->size();
}
inline JSON JSON::operator [](const std::string& key) const {
    return (*MiniData_JSONImpl::as<MiniData_JSONImpl::ObjectJSON>(mImpl))[key];
}
inline bool JSON::contains(const std::string& key) const {
    return MiniData_JSONImpl::as<MiniData_JSONImpl::ObjectJSON>(mImpl)->contains(key);
}

inline JSON JSON::operator [](JSON key) const {
    /* 按需转发。 */
    if (key.type() == JSON::Type::NUMBER) return (*this)[key.asInteger()];
    if (key.type() == JSON::Type::STRING) return (*this)[key.asString()];
    
    MiniData_JSONImpl::jsonError("Cannot use this JSON object as a key.");
}

inline std::ostream& operator<< (std::ostream& out, JSON json) {
    json.mImpl->print(out);
    return out;
}

/***************************************************************************/
/***********       JSON 构造辅助函数的实现         ***********/
/***************************************************************************/
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromNull(std::nullptr_t) {
  return std::make_shared<MiniData_JSONImpl::NullJSON>(nullptr);
}
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromBoolean(bool value) {
  return std::make_shared<MiniData_JSONImpl::BoolJSON>(value);
}
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromDouble(double value) {
  return std::make_shared<MiniData_JSONImpl::NumericValueJSON<double>>(value);
}
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromInteger(std::int64_t value) {
  return std::make_shared<MiniData_JSONImpl::NumericValueJSON<int64_t>>(value);
}
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromString(const std::string& value) {
  return std::make_shared<MiniData_JSONImpl::StringJSON>(value);
}
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromArray(const std::vector<JSON>& elems) {
  return std::make_shared<MiniData_JSONImpl::ArrayJSON>(elems);
}
inline std::shared_ptr<MiniData_JSONImpl::BaseJSON> JSON::fromMap(const std::map<std::string, JSON>& elems) {
  return std::make_shared<MiniData_JSONImpl::ObjectJSON>(elems);
}

inline JSON JSON::array(std::initializer_list<JSON> elems) {
  return JSON(std::vector<JSON>(elems));
}
inline JSON JSON::object(std::initializer_list<std::pair<const std::string, JSON>> elems) {
  return JSON(std::map<std::string, JSON>(elems));
}

/***************************************************************************/
/***********       JSON::const_iterator 的实现     ***********/
/***************************************************************************/
inline JSON::const_iterator::const_iterator() {
    // 保持 mImpl 未初始化
}
inline JSON::const_iterator::const_iterator(std::shared_ptr<MiniData_JSONImpl::JSONSource> source) : mImpl(source) {

}

/* 支持最小化的相等性比较：任意迭代器都与自身相等
 * 范围末尾的任意两个迭代器比较结果都相等。
 */
inline bool JSON::const_iterator::operator== (const_iterator rhs) const {
    /* 情况 1：两个迭代器都为空。 */
    if (!mImpl && !rhs.mImpl) return true;
    
    /* 情况 2：当前迭代器为空，对方不为空。 */
    else if (!mImpl) return rhs.mImpl->finished();
    
    /* 情况 3：对方为空，当前迭代器不为空。 */
    else if (!rhs.mImpl) return mImpl->finished();
    
    /* 情况 4：两者都不为空。 */
    return mImpl == rhs.mImpl;
}

inline bool JSON::const_iterator::operator!= (const_iterator rhs) const {
    return !(*this == rhs);
}
    
inline JSON::const_iterator& JSON::const_iterator::operator++ () {
    mImpl->advance();
    return *this;
}

inline const JSON::const_iterator JSON::const_iterator::operator++ (int) {
    auto result = *this;
    ++*this;
    return result;
}

inline const JSON& JSON::const_iterator::operator* () const {
    return mImpl->current();
}
    
inline const JSON* JSON::const_iterator::operator-> () const {
    return &**this;
}

inline JSON::const_iterator JSON::begin() const {
    return MiniData_JSONImpl::JSONSource::make(MiniData_JSONImpl::as<MiniData_JSONImpl::IterableJSON>(mImpl)->source());
}
inline JSON::const_iterator JSON::end() const {
    return {};
}
inline JSON::const_iterator JSON::cbegin() const {
    return begin();
}
inline JSON::const_iterator JSON::cend() const {
    return end();
}

/***************************************************************************/
/***********          解析例程的实现              ***********/
/***************************************************************************/

/* 字符串解析只是将内容包装为 istringstream 并转发调用。 */
inline JSON JSON::parse(const std::string& input) {
    std::istringstream converter(input);
    return parse(converter);
}

namespace MiniData_JSONImpl {
    /* 用于报告解析错误的实用函数。 */
    [[ noreturn ]] inline void parseError(const std::string& reason) {
        jsonError("JSON Parse Error: " + reason);
    }

    /* 用于确认下一个字符与指定值匹配的实用函数。 */
    inline void expect(std::istream& input, char32_t ch) {
        char32_t found = readChar(input);
        if (found != ch) parseError("Expected " + toUTF8(ch) + ", got " + toUTF8(found));
    }
    
    /* 此实现每次处理一个字符，因此仅适用于基础 ASCII 字符串。 */
    inline void expect(std::istream& input, const std::string& str) {
        for (char ch: str) {
            expect(input, ch);
        }
    }

    /* 所有这些解析例程都使用 JSON 网站上规定的语法
     * （https://www.json.org/）。这是一个自顶向下的递归下降解析器。
     */
    inline JSON readObject(std::istream& input);
    inline JSON readElement(std::istream& input);
    inline JSON readArray(std::istream& input);
    inline JSON readNumber(std::istream& input);
    inline std::string readString(std::istream& input);

    inline std::nullptr_t readNull(std::istream& input) {
        expect(input, "null");
        return nullptr;
    }

    inline bool readBoolean(std::istream& input) {
        if (peekChar(input) == 't') {
            expect(input, "true");
            return true;
        } else if (peekChar(input) == 'f') {
            expect(input, "false");
            return false;
        } else {
            parseError("Can't parse a boolean starting with " + toUTF8(peekChar(input)));
        }
    }
    
    inline bool isDigit(char32_t ch) {
        return ch >= '0' && ch <= '9';
    }

    inline std::string readDigits(std::istream& input) {
        std::ostringstream result;

        /* 至少必须有一位数字。 */
        char32_t digit = readChar(input);
        if (!isDigit(digit)) {
            parseError("Expected a digit, got " + std::string(1, digit));
        }

        result << toUTF8(digit);

        /* 不断读取字符，直到遇到非数字字符。 */
        while (isDigit(peekChar(input))) {
            result << toUTF8(readChar(input));
        }

        return result.str();
    }

    inline std::string readInt(std::istream& input) {
        std::ostringstream result;

        /* 前面可能有负号。 */
        if (peekChar(input) == '-') {
            result << toUTF8(readChar(input));
        }

        /* 这里有两种可能。第一种是正在读取数字 0，此时
         * 情况是刚刚读取了一个 0。其后不允许出现任何内容。其次，也可能
         * 正在读取多位数，此时继续执行相应处理。
         */
        if (peekChar(input) == '0') { // 只有一个零
            result << toUTF8(readChar(input));
        } else {
            result << readDigits(input);
        }
        return result.str();
    }

    inline std::string readFrac(std::istream& input) {
        /* 若下一个字符不是小数点，则没有内容可读。 */
        if (peekChar(input) != '.') return "";

        /* 否则，应当看到一个小数点，然后是一串数字。 */
        std::ostringstream result;
        result << toUTF8(readChar(input));
        result << readDigits(input);
        return result.str();
    }

    inline std::string readExp(std::istream& input) {
        /* 若下一个字符不是 e 或 E，则没有内容可读。 */
        if (peekChar(input) != 'E' && peekChar(input) != 'e') return "";

        std::ostringstream result;
        result << toUTF8(readChar(input));

        /* 可以选择带正负号。 */
        if (peekChar(input) == '+' || peekChar(input) == '-') {
            result << toUTF8(readChar(input));
        }

        /* 现在读取一些数字。 */
        result << readDigits(input);

        return result.str();
    }
    
    /* 尝试将字符串解析为某种数值格式。成功时返回
     * true。失败时返回 false，且不修改输出参数。
     */
    template <typename T> bool parseValue(const std::string& str, T& result) {
        /* 尝试读取一个值；若连值都无法读取，则失败。 */
        std::istringstream extractor(str);
        T readValue;
        
        if (extractor >> readValue, !extractor) return false;
        
        /* 检查是否存在剩余内容。 */
        char leftover;
        if (extractor >> leftover) return false;
        
        result = readValue;
        return true;
    }

    inline JSON readNumber(std::istream& input) {
        auto intPart  = readInt(input);
        auto fracPart = readFrac(input);
        auto expPart  = readExp(input);
        
        /* 组装表示该数字的字符串。 */
        std::string numericString = intPart + fracPart + expPart;
        
        /* 先尝试将其组装为整数。 */
        std::int64_t integerValue;
        if (parseValue(numericString, integerValue)) {
            return BaseJSON::make<NumericValueJSON<std::int64_t>>(integerValue);
        }
        
        /* 否则，尝试将其作为 double 处理。 */
        double doubleValue;
        if (parseValue(numericString, doubleValue)) {
            return BaseJSON::make<NumericValueJSON<double>>(doubleValue);
        }
        
        /* 否则，放弃！ */
        parseError("Cannot parse number " + numericString + " as either an integer or a double.");
    }

    inline JSON readValue(std::istream& input) {
        /* 根据下一个输入字符决定要读取的内容。 */
        char32_t next = peekChar(input);

        if (next == '{') return readObject(input);
        if (next == '[') return readArray(input);
        if (next == '"') return JSON(readString(input));
        if (next == '-' || isdigit(next)) return readNumber(input); // TODO：isdigit 是否假定 ASCII？
        if (next == 't' || next == 'f') return JSON(readBoolean(input));
        if (next == 'n') return JSON(readNull(input));

        parseError("Not sure how to handle value starting with character " + toUTF8(next));
    }

    inline std::string readString(std::istream& input) {
        std::string result;

        expect(input, '"');

        /* 不断读取找到的字符。 */
        while (true) {
            char32_t next = readChar(input);
            
            /* 只有特定字符范围有效。 */
            if (next < 0x20 || next > 0x10FFFF) parseError("Illegal character: " + toUTF8(next));

            /* 若这是右引号，则处理完成。 */
            if (next == '"') return result;

            /* 若这不是转义序列，则直接追加。 */
            if (next != '\\') result += toUTF8(next);

            /* 否则，将其作为转义序列读取。 */
            else {
                char32_t escaped = readChar(input);
                if      (escaped == '"')  result += '"';
                else if (escaped == '\\') result += '\\';
                else if (escaped == '/')  result += '/';
                else if (escaped == 'b')  result += '\b';
                else if (escaped == 'n')  result += '\n';
                else if (escaped == 'r')  result += '\r';
                else if (escaped == 't')  result += '\t';
                else if (escaped == 'u') {
                    input.unget();
                    input.unget();
                    result += toUTF8(readUTF16EscapedChar(input));
                } else parseError("Unknown escape sequence: \\" + toUTF8(escaped));
            }
        }
    }

    using Member = std::map<std::string, JSON>::value_type;
    inline Member readMember(std::istream& input) {
        input >> std::ws;
        auto key = readString(input);
        input >> std::ws;

        expect(input, ':');

        auto value = readElement(input);

        return { key, value };
    }

    inline JSON readArray(std::istream& input) {
        expect(input, '[');

        std::vector<JSON> elems;

        /* 边界情况：这可能是空数组。 */
        input >> std::ws;
        if (peekChar(input) == ']') {
            readChar(input); // 读取并跳过 ']'
            return JSON(elems);
        }

        /* 否则，这是非空列表。 */
        while (true) {
            elems.push_back(readElement(input));

            /* 下一个字符应为逗号或右方括号。遇到以下内容时停止：
             * 遇到右方括号时停止，遇到逗号时继续。
             */
            char32_t next = readChar(input);
            if (next == ']') return JSON(elems);
            if (next != ',') parseError("Expected , or ], got " + toUTF8(next));
        }
    }

    inline JSON readObject(std::istream& input) {
        expect(input, '{');

        std::map<std::string, JSON> elems;

        /* 边界情况：这可能是空对象。 */
        input >> std::ws;
        if (peekChar(input) == '}') {
            readChar(input); // 读取并跳过 '}'
            return JSON(elems);
        }

        /* 否则，这是非空对象。 */
        while (true) {
            auto result = elems.insert(readMember(input));
            if (!result.second) parseError("Duplicate key: " + result.first->first);

            /* 下一个字符应为逗号或右花括号。遇到以下内容时停止：
             * 遇到右花括号时停止，遇到逗号时继续。
             */
            char32_t next = readChar(input);
            if (next == '}') return JSON(elems);
            if (next != ',') parseError("Expected , or }, got " + toUTF8(next));
        }
    }

    inline JSON readElement(std::istream& input) {
        input >> std::ws;
        auto result = readValue(input);
        input >> std::ws;
        return result;
    }
}

/* 主解析例程。 */
inline JSON JSON::parse(std::istream& input) {
    auto result = MiniData_JSONImpl::readElement(input);

    /* 确认流中没有剩余内容。 */
    char leftover;
    input >> leftover;
    if (input) MiniData_JSONImpl::parseError("Unexpected character found at end of stream: " + std::string(1, leftover));

    return result;
}

/* 流提取会接入主解析例程。 */
inline std::istream& operator>> (std::istream& in, JSON& j) {
    if (std::istream::sentry(in)) {
        try {
            auto result = MiniData_JSONImpl::readElement(in);
            j = std::move(result);
        } catch (const JSONException &) {
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}

/***************************************************************************/
/***********          异常类型的实现              ***********/
/***************************************************************************/
inline JSONException::JSONException(const std::string& reason): logic_error(reason) {
    // 已在初始化列表中处理
}

#endif
