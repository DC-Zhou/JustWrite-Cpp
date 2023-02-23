# Compile Time String Operation
## From:[C++性能优化实践](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=MzIxMzY5MzY4MQ==&action=getalbum&album_id=2000858933619458052&scene=173&from_msgid=2247484292&from_itemidx=1&count=3&nolastread=1#wechat_redirect)

### 文章一：数字转字符串的编译期写法

代码：num_to_string.cpp

### 文章二：FixedString 的编译期写法

这部分参看FaceBook的folly库的[头文件](https://github.com/facebook/folly/blob/main/folly/FixedString.h)。东西有点过多了，而且似乎直接拆出来缺少变量；

### 文章三：如何在非Constexpr环境中使用编译期计算

代码：compile_in_non_constexpr.cpp

### 文章四：把String放在Stack上

代码：pmr_string.cpp

