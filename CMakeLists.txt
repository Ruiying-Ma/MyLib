cmake_minimum_required(VERSION 3.21)
project(my_lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_lib main.cpp vector/vector.h vector/vector.cpp _share/util.h _share/release.h list/list.cpp stack/infix_expression.cpp bintree/binnode.cpp bintree/binnode_avl_macro.h bintree/binnode_basic_macro.h bintree/bintree.cpp bst/bst.cpp avl/avl.cpp avl/avl_macro.h stack/stack_list.h list/list.h list/listnode.h stack/stack_vector.h queue/queue.h entry/entry.h bst/bst.h bintree/binnode.h bintree/bintree.h avl/avl.h splay/splay.h splay/splay.cpp btree/btnode.h btree/btree.h btree/btree.cpp redblack/redblack.h redblack/redblack.cpp bintree/binnode_redblack_macro.h pq/pq.h pq/pq_completeheap.h pq/qp_completeheap.cpp pq/pq_completeheap_macro.h pq/pq_leftheap.h pq/pq_leftheap.cpp)
