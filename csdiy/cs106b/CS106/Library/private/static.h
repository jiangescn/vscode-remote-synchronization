/*
 * 文件：static.h
 * --------------
 * 此文件提供若干用于声明静态变量和函数的宏
 * 采用在 C++ 静态初始化阶段安全的方式。
 * 应使用这些宏声明所有不在函数内部的静态数据
 * 供库使用，因为许多库代码会在
 * 静态初始化阶段。
 *
 * @version 2017/10/05
 * - 添加 STATIC_VARIABLE_NAMESPACE
 */

#ifndef _static_h
#define _static_h

// 用于连接两个宏的宏
#ifndef CONCAT_IMPL
#define MACRO_CONCAT(a, ...) PRIMITIVE_CONCAT(a, __VA_ARGS__)
#define PRIMITIVE_CONCAT(a, ...) a ## __VA_ARGS__
#define MACRO_IDENT(x) x
#endif // CONCAT_IMPL

// 声明 static 变量/函数并赋予给定值
#define STATIC_VARIABLE_DECLARE(type, name, value) \
    static type & s_##name() { \
        static type __##name = (value); \
        return __##name; \
    }

// 声明但不赋值（使用类型默认值）
#define STATIC_VARIABLE_DECLARE_BLANK(type, name) \
    static type & s_##name() { \
        static type __##name; \
        return __##name; \
    }

// 声明 static const 变量/函数并赋予给定值
#define STATIC_CONST_VARIABLE_DECLARE(type, name, value) \
    static const type & s_##name() { \
        static const type __##name = (value); \
        return __##name; \
    }

// 声明 static 变量/函数集合并赋予给定元素
// （这些似乎不适用于 Map<K, V> 这样的多模板集合 :-/
//  但它们适用于 Vector<E> 这样的单模板集合）
#define STATIC_VARIABLE_DECLARE_COLLECTION(type, name, ...) \
    static type & s_##name() { \
        static type __##name = { __VA_ARGS__ }; \
        return __##name; \
    }

// 声明 static 变量/函数集合并保持为空
#define STATIC_VARIABLE_DECLARE_COLLECTION_EMPTY(type, name) \
    static type & s_##name() { \
        static type __##name; \
        return __##name; \
    }

#define STATIC_VARIABLE_DECLARE_MAP_EMPTY(maptype, keytype, valuetype, name) \
    static maptype < keytype , valuetype > & s_##name() { \
        static maptype < keytype , valuetype > __##name; \
        return __##name; \
    }

// 声明 static const 变量/函数集合并赋予给定元素
#define STATIC_CONST_VARIABLE_DECLARE_COLLECTION(type, name, ...) \
    static const type & s_##name() { \
        static const type __##name { __VA_ARGS__ }; \
        return __##name; \
    }

// 查找给定静态变量的值（通过调用其静态 s_ 函数）
#define STATIC_VARIABLE(name) \
    (s_##name())

// 在另一个命名空间中查找给定静态变量的值
#define STATIC_VARIABLE_NAMESPACE(namespacename, name) \
    (namespacename::s_##name())

#endif // _static_h
