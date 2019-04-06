// 智能分词

// 分词是指将一个字符串分割成词语序列，其中所有词语都来自事先指定的词汇表。例如：
// 有字符串"github"，以及词汇表["git", "hub"]，那么分词方式为:"git hub"。

// 分词可能有多重方式，例如字符串"asdfjkl"，以及词汇表["as", "asd", "df", "fjkl", "jkl"]，可能有两种分词方法:"as df jkl"、"asd fjkl"。先定义每种分词方法的合理性得分为：分词方案中每个单词长度的平方和。例如上述两种分词方案的得分分别为 2^2 + 2^2 + 3^2 = 17，以及 3^2 + 4^2 = 25。

// 现给出词汇表（均为小写字母，单词最长50字符，最多10个万单词），以及一句话（均为小写字母，最长10万字符），找出最合理的分词方案。若有多种得分相同的最合理方案，输出长词尽量靠前的方案。例如"ab cdef"与"abcd ef"这两种最优方案得分相同，输出"abcd ef"。

// 编译器版本: gcc 4.8.4
// 请使用标准输入输出(stdin，stdout) ；请把所有程序写在一个文件里，勿使用已禁用图形、文件、网络、系统相关的头文件和操作，如sys/stat.h , unistd.h , curl/curl.h , process.h
// 时间限制: 3S (C/C++以外的语言为: 5 S)   内存限制: 128M (C/C++以外的语言为: 640 M)
// 输入:
// 第一行为待分语句；第二行为词汇表中的单词数量N；接下来N行，每行一个单词。
// 输出:
// 一行，分隔后的语句，以空格分隔各个单词。
// 输入范例:
// asdfjkl
// 5
// as
// asd
// df
// fjkl
// jkl
// 输出范例:
// asd fjkl



// 在一个分布式Key-Value存储系统中，我们会将所有的Key排序后切割成多个连续的分片，称为分区(Partition), 为了保证分布式系统中的高可用特性，需要将每个分区复制多个副本(Replica)，分布放置到多台节点上。为了保证整个系统的每个节点负载是均衡的，需要保持每个节点上的所有分区的总数据大小大致均等。

// 在各个节点上分配Partition要遵循一定的规则：

// - 一个节点不能有相同的Partition Replica
// - 每个节点的Partition数据大小总量与平均数据量(total size/N)差距绝对值小于(D)。


// 现在假设数据一共划分了M个Partition，编号为(0,1,2…M-1)，同时有一个大小为M的数组partition_size_array描述每个分片的大小，比如[100,110,120,130]，表示P0.size=100,P1.size=110； 每个Partition有3个副本，现在随机分配到有N(N>3)个节点上，有一个整数二维数组node_replica_table(size=N)描述当前每个节点分配的Partition编号:
// node_replica_table[0] = {0, 1, 5} ; // node0放置了partition0, partition1, partition5; 
// node_replica_table[1] = {1, 2, 3}; // node1放置了partition1, partition2, partition3;
// ..
// node_repliac_table[N-1] = {…}; 


// 要求编写一个函数，计算要达到负载均衡所需的最小迁移步骤(每次可以移动一个partition从一个节点到另一个节点)，如果本身是负载均衡，那么返回0，如果无法满足，返回-1.

// 编译器版本: gcc 4.8.4
// 请使用标准输入输出(stdin，stdout) ；请把所有程序写在一个文件里，勿使用已禁用图形、文件、网络、系统相关的头文件和操作，如sys/stat.h , unistd.h , curl/curl.h , process.h
// 时间限制: 3S (C/C++以外的语言为: 5 S)   内存限制: 128M (C/C++以外的语言为: 640 M)
// 输入:
// 输入数据包含N+2行：
// 第一行为 N M D 
// 第二行为 partition_size_array, 大小replica个数M(M>N)
// 剩余M行为node_replica_table，每一行表示一个node上的replia数组，大小为小于M+1的任意整数，第一个数是数组的大小，后面每个数组的元素是副本的编号，也就是partition_size_array的下标
// 输出:
// 最小迁移步骤
// 输入范例:
// 5 6 100
// 100 110 120 130 140 150
// 6 0 1 2 3 4 5
// 5 0 1 2 3 4
// 4 0 2 4 5
// 2 1 5
// 1 3
// 输出范例:
// 2

main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
