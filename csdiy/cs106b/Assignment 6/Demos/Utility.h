#pragma once

/**
 * 宏：DISALLOW_COPYING_OF(Type)
 *
 * 禁止指定类型的复制/赋值。
 */
#define DISALLOW_COPYING_OF(Type)                                           \
    Type(const Type &) = delete;                                            \
    Type(Type &&) = delete;                                                 \
    void operator= (Type) = delete
