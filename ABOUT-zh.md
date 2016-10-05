##关于这个库子

可以写写缘由跟原理的

第一次听说 LowPoly, 感觉这就是又一种马赛克啊！

听说这个 LowPoly 用 JNI 实现处理速度可以飞啊！

到 github 一搜，有好多人都已经写过并开源了，各种语言的，连 ~~.so 语言~~的都有！

本来是打算把 Java 版的 [LowPolyAndroid](https://github.com/zzhoujay/LowPolyAndroid) 用 c 实现一遍，
但自己复刻来的算法运行时各种错误，只有 [sobel](https://en.wikipedia.org/wiki/Sobel_operator) 边缘检测可以用。

（图片经边缘检测处理得到的点集再绘制出来跟个沙画差不多，后来我就把这个中间产物给抛了个接口出来。）

放弃了用c实现人家 Java 版的想法，只保留了 [sobel](./xlowpoly/src/main/cpp/sobel.c) 边缘检测，其余都删掉自己来。

LowPoly 的原理好简单啊：

第一步，边缘检测获取点集

第二步，稀释点集

第三步，三角剖分

在沙画的基础上，三步走的第二步是把点变少同时还要保留大致的轮廓，我把处理这件事的 c 命名为 [dilution.c](./xlowpoly/src/main/cpp/dilution.c)/.h,
万幸，我竟然想到了两种方法来进行这个稀释的操作：

最开始想到的是采用类似带通滤波的想法做的，但是并不是线性的也很难控制输出的点数。

于是有了第二种，采用抽签点名的方法，这种缺点是有可能抽到相同的点，也就是说需要在结果集中去重([delup](./xlowpoly/src/main/cpp/dedup.c))，
这虽然最后得到点会比指定的点数要少一些，但还是要比带通滤波的方法好。

最后一步是 delaunay 三角剖分。我感觉 LowPolyAndroid 里的 delaunay 三角剖分好牛*啊，仅用了二百多行的 Java 居然就可以运行,
但我并没有看懂 =.=

主要参考的百度百科的 [Delaunay三角剖分算法](http://baike.baidu.com/view/1691145.htm)，
维基百科的 [Delaunay triangulation](https://en.wikipedia.org/wiki/Delaunay_triangulation) 也有帮助。

看百度百科的三角剖分算法介绍原理也很简单，但我实现这个算法却没有那么顺利。

最让我感慨的是检测点是否在三角形外接圆的方法，我总想用机智点的方法判断，希望尽量减少运算，在一开始我就是拒绝用确定圆心半径比较大小的，
到最后却发现，问题都出在所谓的这个机智判断方法上，最后还是用的这个最开始就被放弃了的`确定圆心半径比较大小`。呵呵。

在设计这个三角剖分的数据结构的时候，我坚持着一个很重要的原则：`空间复杂度要小！` Bitmap 本来就很占内存啊！

但伟大先贤~~孟子~~说过啥来着？`空间复杂度和时间复杂度不可兼得！`

现在用于三角剖分数据结构是：
```c
typedef struct Arc_ {
    //vector:<nock --> arrow>, nock_index > arrow_index
    int nock_vertex;
    int arrow_vertex;
    struct Arc_ *next;
} Arc;

typedef struct Triangle_ {
    Arc *subtense;
    struct Triangle_ *next;
} Triangle;

typedef struct {
    const Point *vertices;
    //arcs linked lists heads array
    Arc **arcs_heads;
    //triangles linked lists heads array
    Triangle **triangles_heads;
    //array.length = vertices.length = size_vertices + 4 (super-square)
    int length;
} TriNet;

```
这个数据结构的前一版本，Arc是不存储 nock_vertex 的，是通过遍历 TriNet 的 arcs_heads 计算得到，但是啊，就是这个计算，时间复杂度到了不能用的程度。（但比那个
 Java 版的快一点 :)

这里以空间换时间还是比较值得的：跟类似的JNI实现在产生相同三角形个数条件下比了一次，`XLowPoly` 快了几十毫秒呢 :)

我打算用某种特别的方式来纪念一下那个判断点是不是在三角形圆内的方法：
 ```c
 bool in_circumcircle(const int target_point_index, const int vertex, const Arc *arc,
                      const TriNet *net) {
     int arrow = arc->arrow_vertex;
     int nock = arc->nock_vertex;
     const Point p = net->vertices[target_point_index];
     const Point v1 = net->vertices[vertex];
     const Point v2 = net->vertices[arrow];
     const Point v3 = net->vertices[nock];

     float w = 2 * (v2.x - v1.x);
     float h = 2 * (v2.y - v1.y);
     float a = 2 * (v3.x - v2.x);
     float t = 2 * (v3.y - v2.y);
     float f = powf(v2.x, 2.0f) + powf(v2.y, 2.0f);
     float f_ = powf(v1.x, 2.0f) + powf(v1.y, 2.0f) - f;
     float f__ = f - powf(v3.x, 2.0f) - powf(v3.y, 2.0f);
     float u = (f__ * h - f_ * t) / (t * w - h * a);
     float c = (w * f__ - a * f_) / (a * h - w * t);
     float k = powf(v1.x - u, 2.0f) + powf(v1.y - c, 2.0f);

     return powf(p.x - u, 2.0f) + powf(p.y - c, 2.0f) < k;
 }
 ```

最后，这个[三角剖分算法](./xlowpoly/src/main/cpp/delaunay.c)并没有实现 LOP(Local Optimization Procedure), 得到的三角剖分不是最好的。

>
我写完这个库子，
问一个妹子：“这个像不像沙画？”
>
妹子很诚实，回说：“不像。”

╮(￣▽￣)╭