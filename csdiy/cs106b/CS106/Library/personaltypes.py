# ############################################################################
# #
# # 版权所有 (C) 2016 The Qt Company Ltd.
# # 联系方式：https://www.qt.io/licensing/
# #
# # 此文件是 Qt Creator 的一部分。
# #
# # 商业许可证使用方式
# # 持有有效 Qt 商业许可证的被许可方可以根据以下方式使用此文件：
# # 请遵循随附的商业许可协议
# # 软件，或者依据其中包含的条款
# # 你与 Qt Company 之间的书面协议。有关许可条款，
# # 条款和条件请参阅 https://www.qt.io/terms-conditions。更多
# # 如需更多信息，请使用 https://www.qt.io/contact-us 上的联系表单。
# #
# # GNU 通用公共许可证使用方式
# # 或者，此文件也可以依据 GNU 的条款使用
# # 自由软件基金会发布的 GNU 通用公共许可证第 3 版
# # 基金会发布的版本，但包含 LICENSE.GPL3-EXCEPT 文件中所示的例外
# # 包含在此文件的打包内容中。请查看以下
# # 信息，以确保满足 GNU 通用公共许可证的要求
# # 必须满足：https://www.gnu.org/licenses/gpl-3.0.html。
# #
# ############################################################################

# # 此处可添加用于测试的自定义转储器。
# # 此处的任何内容都会由 GDB、LLDB 和 CDB 根据
# # 自动用于 Qt Creator 中的调试。

# # 注意：更新 Qt Creator 时，此文件将被覆盖。
# #
# # 若要添加不会被覆盖的转储器，请将此文件复制到此处
# # 复制到 Qt Creator 安装目录之外的安全位置，并
# # 使用“调试器”> 使 Qt Creator 知晓此位置
# # “局部变量和表达式”>“额外调试帮助程序”设置。

# # 显示简单类型的示例
# # template<typename U, typename V> struct MapNode
# # {
# #     U key;
# #     V data;
# # }
# #
# # def qdump__MapNode(d, value):
# #    d.putValue("这是值列的内容")
# #    d.putNumChild(2)
# #    if d.isExpanded():
# #        with Children(d):
# #            # 紧凑的简单情况。
# #            d.putSubItem("key", value["key"])
# #            # 效果相同，但提供更多自定义可能性。
# #            with SubItem(d, "data")
# #                d.putItem("data", value["data"])

# # 请查看 http://doc.qt.io/qtcreator/creator-debugging-helpers.html
# # 了解更多详细信息，或查看 qttypes.py、stdtypes.py、boosttypes.py
# # 了解更复杂的示例。

import dumper
from dumper import Children, SubItem

# ######################## 在下方编写你的代码 #######################

# @author Jeremy Barenholtz 2020
#
# CS106B 类（Vector、Stack、Set、Map 等）的调试帮助程序
# 部分代码采用自 Qt Creator 分发的 stdtypes.py
# Julie Zelenski 为 2020 年秋季学期做了部分调整

from functools import partial

#############################
# 元素显示函数 #
#############################

# 这些名为 `add_<type>_elem` 的函数控制每个
# 类在调试窗口中显示。
#
# 只有希望更改显示效果时，才应调整这些函数
# 格式。要理解相关代码，请启动调试器查看你的
# 所需类，并查看此处相关的添加元素函数；你应当
# 能够看出代码与所显示内容之间的对应关系。


def add_map_elem(d, i, key, value):
    """Adds an element of a map to the debugger display."""

    d.putPairItem(None, (key, value), 'key', 'value')


def add_set_elem(d, i, key, value):
    """Adds an element of a set to the debugger display."""

    # Set 使用键值对映射存储，其中值始终为 true
    # 忽略此值且不显示
    d.putSubItem('-', key)


# 当前仅由 Vector 使用
def add_indexed_elem(d, i, size, value):
    """Adds an element of an indexed container to the debugger display."""

    d.putSubItem(i, value)


def add_pq_elem(d, i, size, raw):
    """Adds an element of a priority queue to the debugger display."""

    priority = raw['priority']
    value = raw['value']
    d.putPairItem(None, (value, priority), 'value', 'priority')


def add_stack_elem(d, i, size, value):
    """Adds an element of a stack to the debugger display."""

    if size == 1:
        name = 'bottom/top'
    elif i == 0:
        name = 'bottom'
    elif i == size - 1:
        name = 'top'
    else:
        name = '-'

    d.putSubItem(name, value)


def add_queue_elem(d, i, size, value):
    """Adds an element of a queue to the debugger display."""

    if size == 1:
        name = 'front/back'
    elif i == 0:
        name = 'front'
    elif i == size - 1:
        name = 'back'
    else:
        name = '-'

    d.putSubItem(name, value)


# 此函数接收额外的 `cols` 参数。请查看 `qdump__Grid` 以了解
# 展示如何向这些函数添加参数的示例。
def add_grid_elem(d, i, size, value, cols):
    """Adds an element of a grid to the debugger display."""

    name = '[%d, %d]' % (i // cols, i % cols)
    d.putSubItem(name, value)


#####################################
# Stanford 库转储函数 #
#####################################

# 这些名为 `qdump__<class>` 的函数会接收底层数据
# 用于相应类型的变量。
#
# 可以使用 `d.putBetterType('<new_type>')` 更改显示类型。请参阅
# 可参考 `qdump__stanfordcpplib__collections__GenericSet` 的示例。
# 元素的所有格式都应使用添加元素函数设置
# 上方。


def qdump__Set(d, value):
    """Display Stanford Set on debugger."""

    # 从 Set > MapType > std::map 中获取内部数据
    value = value['_map']['_elements']
    map_helper(d, value, elem_fn=add_set_elem)


def qdump__stanfordcpplib__collections__GenericSet(d, value):
    """Display Stanford Set or HashSet when dumped as GenericSet (Windows)."""

    # 从 Set > MapType > std::map 中获取内部数据
    # 或用于 HashSet 的 std::unordered_map

    value = value['_map']['_elements']
    if "unordered" in value.type.name:
        unordered_map_helper(d, value, elem_fn=add_set_elem)
        cls = "HashSet"
    else:
        map_helper(d, value, elem_fn=add_set_elem)
        cls = "Set"

    inner_type = value.type[0].name
    d.putBetterType('%s<%s>' % (cls, inner_type))


def qdump__Stack(d, value):
    """Display Stanford Stack on debugger."""

    # 从 Stack > Vector > std::{vector, deque} 中获取内部数据
    value = value['_elements']['_elements']
    vector_or_deque_helper(d, value, elem_fn=add_stack_elem)


def qdump__Queue(d, value):
    """Display Stanford Queue on debugger."""

    # 从 Queue > Deque > std::deque 中获取内部数据
    value = value['_elements']['_elements']
    deque_helper(d, value, elem_fn=add_queue_elem)


def qdump__PriorityQueue(d, value):
    """Display Stanford PriorityQueue on debugger."""

    # 从 PriorityQueue > Vector > std::vector 中获取内部数据
    value = value['_heap']['_elements']
    vector_helper(d, value, elem_fn=add_pq_elem)


def qdump__Deque(d, value):
    """Display Stanford Deque on debugger."""

    # 从 Deque > std::deque 获取内部数据
    value = value['_elements']
    deque_helper(d, value, elem_fn=add_queue_elem)


def qdump__Map(d, value):
    """Display Stanford Map on debugger."""

    # 从 Map > std::map 中获取内部数据
    value = value['_elements']
    map_helper(d, value, elem_fn=add_map_elem)


def qdump__Vector(d, value):
    """Display Stanford Vector on debugger."""

    # 从 Vector > std::vector 中获取内部数据
    value = value['_elements']
    vector_or_deque_helper(d, value, elem_fn=add_indexed_elem)


def qdump__Grid(d, value):
    """Display Stanford Grid on debugger."""

    rows = value['_rowCount'].integer()
    cols = value['_columnCount'].integer()

    # 从 Grid > Vector > std::vector 中获取内部数据
    value = value['_elements']['_elements']
    vector_or_deque_helper(d, value, elem_fn=partial(add_grid_elem, cols=cols))


def qdump__HashMap(d, value):
    """Display Stanford HashMap on debugger."""

    # 从 HashMap 获取内部映射 > std::unordered_map
    value = value['_elements']
    unordered_map_helper(d, value, elem_fn=add_map_elem)


def qdump__HashSet(d, value):
    """Display Stanford HashSet on debugger."""

    # 从 HashMap 获取内部映射 > std::unordered_map
    value = value['_map']['_elements']
    unordered_map_helper(d, value, elem_fn=add_set_elem)


####################
# 辅助函数 #
####################


def vector_or_deque_helper(d, value, elem_fn):
    """Wrapper for dumping vectors or deque in the bool case."""

    # 如果内部类型是 bool，容器实际为 std::deque，而不是 vector
    inner_type = value.type[0]
    if inner_type.name == 'bool':
        deque_helper(d, value, elem_fn)
    else:
        vector_helper(d, value, elem_fn)


def vector_helper(d, value, elem_fn):
    """Dumps the internal vector for Vector, Stack, PriorityQueue, and Grid."""

    inner_type = value.type[0]
    is_bool = inner_type.name == 'bool'

    # 检查是否使用 libstdc++ 或 libc++ 编译
    class_is_lib_cpp = is_lib_cpp(value)

    if is_bool:
        if class_is_lib_cpp:
            start = value["__begin_"].pointer()
            size = value["__size_"].integer()  # JDZ：提取整数值
            alloc = size
        else:
            start = value["_M_start"]["_M_p"].pointer()
            soffset = value["_M_start"]["_M_offset"].integer()
            finish = value["_M_finish"]["_M_p"].pointer()
            foffset = value["_M_finish"]["_M_offset"].integer()
            alloc = value["_M_end_of_storage"].pointer()
            size = (finish - start) * 8 + foffset - soffset  # 8 是 CHAR_BIT。
    else:
        if class_is_lib_cpp:
            start = value["__begin_"].pointer()
            finish = value["__end_"].pointer()
            alloc = value["__end_cap_"].pointer()
        else:
            start = value["_M_start"].pointer()
            finish = value["_M_finish"].pointer()
            alloc = value["_M_end_of_storage"].pointer()
        size = int((finish - start) / inner_type.size())
        d.check(finish <= alloc)
        if size > 0:
            d.checkPointer(start)
            d.checkPointer(finish)
            d.checkPointer(alloc)

    d.check(0 <= size and size <= 1000 * 1000 * 1000)
    d.putItemCount(size)
    if d.isExpanded():
        if is_bool:
            if d.isExpanded():
                with dumper.Children(d, size, maxNumChild=10000,
                        childType=inner_type):
                    for i in d.childRange():
                        q = start + int(i / 8)
                        with dumper.SubItem(d, i):
                            # std::vector<bool> 以特殊形式存储元素
                            # 位数组，因此我们读取每个位并从以下形式转换：
                            # {0, 1} -> {false, true}
                            val = (int(d.extractPointer(q)) >> (i % 8)) & 1
                            d.putValue(val != 0)
        else:
            max_num_child = 1000 * 1000
            d.checkIntType(start)
            d.checkIntType(size)
            addr_base = start
            inner_size = inner_type.size()
            d.putNumChild(size)
            with dumper.Children(d, size, inner_type, None, max_num_child,
                      addrBase=addr_base, addrStep=inner_size):
                for i in d.childRange():
                    value = d.createValue(addr_base + i * inner_size,
                                          inner_type)
                    elem_fn(d, i, size, value)


def deque_helper(d, value, elem_fn):
    """Wrapper for dumping deques."""

    # 检查是否使用 libstdc++ 或 libc++ 编译
    if is_lib_cpp(value):
        deque_helper_libcpp(d, value, elem_fn)
    else:
        deque_helper_libstd(d, value, elem_fn)


def deque_helper_libcpp(d, value, elem_fn):
    """Dumps the deque for containers of bools or Queue for libc++."""

    inner_type = value.type[0]
    inner_size = inner_type.size()
    mptr, mfirst, mbegin, mend, start, size = value.split("pppptt")
    d.check(0 <= size and size <= 1000 * 1000 * 1000)
    d.putItemCount(size)
    if d.isExpanded():
        ptr_size = d.ptrSize()
        buf_size = (4096 // inner_size) if inner_size < 256 else 16
        with dumper.Children(d, size, maxNumChild=2000, childType=inner_type):
            for i in d.childRange():
                k, j = divmod(start + i, buf_size)
                base = d.extractPointer(mfirst + k * ptr_size)
                value = d.createValue(base + j * inner_size, inner_type)
                elem_fn(d, i, size, value)


def deque_helper_libstd(d, value, elem_fn):
    """Dumps the deque for containers of bools or Queue for libstdc++."""

    inner_type = value.type[0]
    inner_size = inner_type.size()
    buf_size = 1
    if inner_size < 512:
        buf_size = 512 // inner_size

    (mptr, msize, start_cur, start_first, start_last, start_node, finish_cur,
     finish_first, finish_last, finish_node) = value.split("pppppppppp")

    size = buf_size * ((finish_node - start_node) // d.ptrSize() - 1)
    size += (finish_cur - finish_first) // inner_size
    size += (start_last - start_cur) // inner_size

    d.check(0 <= size and size <= 1000 * 1000 * 1000)
    d.putItemCount(size)
    if d.isExpanded():
        with dumper.Children(d, size, maxNumChild=2000, childType=inner_type):
            pcur = start_cur
            plast = start_last
            pnode = start_node
            for i in d.childRange():
                value = d.createValue(pcur, inner_type)
                elem_fn(d, i, size, value)
                pcur += inner_size
                if pcur == plast:
                    newnode = pnode + d.ptrSize()
                    pfirst = d.extractPointer(newnode)
                    plast = pfirst + buf_size * d.ptrSize()
                    pcur = pfirst
                    pnode = newnode


def unordered_map_helper(d, value, elem_fn):
    """Wrapper for dumping unordered maps."""

    if is_lib_cpp(value):
        unordered_map_helper_libcpp(d, value, elem_fn)
    else:
        unordered_map_helper_libstd(d, value, elem_fn)


def unordered_map_helper_libcpp(d, value, elem_fn):
    """Dumps the unordered_map for HashSet and HashMap for libc++."""

    (size, _) = value["__table_"]["__p2_"].split("pp")
    d.putItemCount(size)

    key_type = value.type[0]
    value_type = value.type[1]
    pair_type = value.type[4][0]

    if d.isExpanded():
        curr = value["__table_"]["__p1_"].split("pp")[0]

        def traverse_list(node):
            while node:
                (next_, _, pad, pair) = d.split("pp@{%s}" % (pair_type.name), node)
                yield pair.split("{%s}@{%s}" % (key_type.name, value_type.name))[::2]
                node = next_

        with dumper.Children(d, size, childType=value.type[0], maxNumChild=1000):
            for (i, pair) in zip(d.childRange(), traverse_list(curr)):
                elem_fn(d, i, pair[0], pair[1])


def unordered_map_helper_libstd(d, value, elem_fn):
    """Dumps the unordered_map for HashSet and HashMap for libstdc++."""

    try:
        # gcc 约为 4.7
        size = value["_M_element_count"].integer()
        start = value["_M_before_begin"]["_M_nxt"]
    except:
        try:
            # libc++（Mac？）
            size = value["_M_h"]["_M_element_count"].integer()
            start = value["_M_h"]["_M_bbegin"]["_M_node"]["_M_nxt"]
        except:
            try:
                # gcc 4.9.1
                size = value["_M_h"]["_M_element_count"].integer()
                start = value["_M_h"]["_M_before_begin"]["_M_nxt"]
            except:
                # gcc 4.6.2
                size = value["_M_element_count"].integer()
                start = value["_M_buckets"].dereference()
                # FIXME：按指针对齐？
                d.putItemCount(size)
                # 我们不知道数据位于何处
                d.putNumChild(0)
                return

    d.putItemCount(size)
    if d.isExpanded():
        key_type = value.type[0]
        value_type = value.type[1]
        type_code = 'p@{%s}@{%s}' % (key_type.name, value_type.name)
        p = start.pointer()
        with Children(d, size):
            for i in d.childRange():
                p, pad, key, pad, val = d.split(type_code, p)
                elem_fn(d, i, key, val)


def map_helper(d, value, elem_fn):
    """Wrapper for dumping maps."""

    if is_lib_cpp(value):
        map_helper_libcpp(d, value, elem_fn)
    else:
        map_helper_libstd(d, value, elem_fn)


def map_helper_libcpp(d, value, elem_fn):
    """Dumps the internal map for Set or Map for libc++."""

    try:
        (proxy, head, size) = value.split("ppp")
        d.check(0 <= size and size <= 100 * 1000 * 1000)

    # JEB：有时开头会有额外数据（？）
    except RuntimeError:
        (junk, proxy, head, size) = value.split("pppp")
        d.check(0 <= size and size <= 100 * 1000 * 1000)

    d.putItemCount(size)

    if d.isExpanded():
        key_type = value.type[0]
        value_type = value.type[1]
        pair_type = value.type[3][0]

        def in_order_traversal(node):
            (left, right, parent,
             color, pad, pair) = d.split("pppB@{%s}" % (pair_type.name), node)

            if left:
                for res in in_order_traversal(left):
                    yield res

            yield pair.split("{%s}@{%s}" %
                             (key_type.name, value_type.name))[::2]

            if right:
                for res in in_order_traversal(right):
                    yield res

        with dumper.Children(d, size, maxNumChild=1000):
            for (i, pair) in zip(d.childRange(), in_order_traversal(head)):
                elem_fn(d, i, pair[0], pair[1])


def map_helper_libstd(d, value, elem_fn):
    """Dumps the internal map for Set or Map for libstdc++."""

    # 实际内容是带 'I@' 的 (color, pad)，但我们可以节省周期
    (compare, stuff, parent, left, right) = value.split('ppppp')
    size = value["_M_t"]["_M_impl"]["_M_node_count"].integer()
    d.check(0 <= size and size <= 100 * 1000 * 1000)
    d.putItemCount(size)

    if d.isExpanded():
        key_type = value.type[0]
        value_type = value.type[1]
        with Children(d, size, maxNumChild=1000):
            node = value["_M_t"]["_M_impl"]["_M_header"]["_M_left"]
            node_size = node.dereference().type.size()
            type_code = "@{%s}@{%s}" % (key_type.name, value_type.name)
            for i in d.childRange():
                (pad1, key, pad2, value) = d.split(type_code, node.pointer()
                                                              + node_size)
                elem_fn(d, i, key, value)

                if node["_M_right"].pointer() == 0:
                    parent = node["_M_parent"]
                    while True:
                        if node.pointer() != parent["_M_right"].pointer():
                            break
                        node = parent
                        parent = parent["_M_parent"]
                    if node["_M_right"] != parent:
                        node = parent
                else:
                    node = node["_M_right"]
                    while True:
                        if node["_M_left"].pointer() == 0:
                            break
                        node = node["_M_left"]


def is_lib_cpp(value):
    """Returns whether the class is from libc++."""

    return value.type.name.startswith('std::__1')
