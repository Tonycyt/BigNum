upd-2023年7月26日 18:16:24：将所有 int 改为 signed 以防止 #define int long long 导致出现 bug  
upd-2023年8月4日 19:29:09：添加使用指南

#### 调用方法：  
##### 初始化：
- 无参数构造。
- 用已有 BigNum 构造。
- 用一个 deque<int> 和一个 int 构造（deque<int> 代表数值，int 代表符号：-1 或 1）。
- 用 string 构造。
- 用一个 string 和一个 int 构造。
- 用一个任意整形构造。

##### 运算：
- 直接调用
- 调用 / /= % %= 时除数或模数为 $0$ 会直接 RE。
- pow() 可以直接用，也可以带模数。
- pow() 底数为 $0$ 是会直接 RE。

##### 输入输出：
- std::cin std::cout 均可，但是效率不高。
- 快读快写：getBigNum() putBigNum(const BigNum&)。