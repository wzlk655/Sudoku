@[TOC](软件工程：数独开发)
## 项目地址
数独程序：<https://github.com/wzlk655/Sudoku>
数独GUI：<https://github.com/wzlk655/SudokuGUI>
## 博客更新
1. 2019.12.20 创建，解题思路编写
2. 2019.12.27 设计部分编写
3. 2020.1.2 性能分析部分编写
4. 2020.1.10 测试部分编写，设计部分完善
5. 2020.1.15 代码质量分析，GUI部分更新
6. 2020.1.16 博客优化，测试部分完善
## PSP表格
|PSP2.1|Personal Software Process Stages|预估耗时（分钟）|实际耗时（分钟）|
|:---:|:---:|:---:|:---:|
|Planning|计划|20|30|
|Estimate|估计这个任务需要多少时间|20|5|
|Development|开发|730|900|
|Analysis|需求分析|30|60|
|Design Spec|生成设计文档|60|120|
|Design Review|设计复审|20|20|
|Coding Standard|代码规范|60|30|
|Design|具体设计|60|120|
|Coding|具体编码|600|300|
|Code Review|代码复审|30|30|
|Test|测试|300|480|
|Reporting|报告|40|40|
|Test Report|测试报告|60|20|
|Size Measurement|计算工作量|10|10|
|Postmortem & Process Improvement Plan|事后总结, 并提出过程改进计划|30|30|
|Total|总计|1300|2195|
## 需求
实现一个命令行程序，程序能：  
1. 生成不重复的数独终局至文件。
2. 读取文件内的数独问题，求解并将结果输出到文件。
## 需求分析
需求比较明确，所以直接开始建模。
### 数据建模
主要的实体就是数独，为了方便数独的生成和变换，将数独分解为9个3x3的子Block，另外，由于详细的需求说明中提到了要求固定生成数独的左上角为某个数字，所以额外给数独一个左上角数字属性。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200102005019829.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 功能建模
由于软件本身逻辑并不复杂，功能也较简单，所以只将数据流图分解到1层。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200102005436284.jpg)
1层数据流图区分了具体的指令，生成和求解分别处理。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020010200554844.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 行为建模
主要有处理生成请求，处理求解请求和用户参数出错三个状态。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200102005833772.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
## 解题思路
### 数独生成
一开始完全没有头绪，于是求助百度，找到了[这篇博客](https://www.jianshu.com/p/4b0d08e19e93)，在研究其算法后，发现满足需求，但是想采用更加面向对象的方法进行开发。在参考[这篇博客](https://blog.csdn.net/silentic/article/details/78031364)后，阅读相关书籍，发现了如下算法：  
1. 将9\*9的数独划分为9个3\*3的方格。
2. 使用1-9的排列来按顺序填充一个方格，将方格按照一定顺序变换，可以获得另外8个方格，组成新的数独。
3. 通过三行/列一组，组内行/列交换获得更多数独。

其中，如何生成数据的排列参考了[这篇博客](https://www.cnblogs.com/kiritozhj/p/10501470.html)和[这篇博客](https://blog.csdn.net/hhmy77/article/details/84193646)，虽然C++数学库中有类似代码，但是处于数据格式和方便随机生成的考虑自己参考算法实现了排列生成。详见下。
#### 思路说明：
步骤2中首先生成中间的方格，然后按照如下图对应变换行、列获得其它位置的方格，如图可见生成的结果符合数独要求。周围的小方格都可以由中间的方格交换行列变换而来。
![数独模板](https://img-blog.csdnimg.cn/20200102003642921.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70 )  
步骤3中行列交换是一整行一整列（9个）元素的交换，为了使得交换后的数独仍然是合法的，我们限定交换只发生组内，这样可以证明，交换涉及的行/列和3*3块都仍然是合法的。
非严格证明：经过步骤3交换后生成的数独不重复：
1. 如果是由同一个步骤2中生成的数独变换而成，则显然被交换的行/列分别和原本不一样，又因为只交换两行/列，所以双方对应行/列也相互区别。
2. 如果是由不同步骤2中生成的数独变换而成，显然每次至少有三个（一行/一列）方格不一样，对应的是双方都没有交换的那一组行/列方格。
### 数独求解：
暴力搜索-->剪枝--->启发式搜索  
考虑代码的可理解性和可维护性，参考了[这篇博客](https://blog.csdn.net/m0_37590629/article/details/79902552)以及[这篇博客](https://blog.csdn.net/qq_41759198/article/details/89291514)中的回溯和DFS思路，决定采用回溯法求数独。将解空间定义为所有解的空格的所有0-9的所有组合。依次尝试每个空格的1-9的所有取值，看能否生成合法的数独，这样算法的复杂度为$n^9$，n为数独中的空格数目。显然改算式仍然有很大的改进空间，有待后续优化。
优化：参考上述博客，在填空进入下一层搜索前，先判断是否是合法数独，如果不合法直接跳过，这样可以有效剪枝。但是需要使得判断数独合法算法能够处理数独不完整时的情况。已经实施。
时间原因未尝试实施的优化思路：记录当前行号，尝试数字时快速跳过本行已有的数字；按照数字在空格中出现的比例来顺序尝试，但是需要额外的数据结构和计算比例。
## 设计实现
由于使用了C++中的面向对象机制，所以尝试了以下使用UML进行建模。但是由于软件本身的功能和之前的系统设计，并不是很方便，所以只画了用例图和类图。
### UML图
#### 用例图
识别参与者为玩家和（计算机文件）系统。主要用例为生成数独和求解数独。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200102010403321.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
#### 类图
主要为3个类，数独Sudoku，数独的子模块Block和求解数独的工具SudokuSolver，相互关系如下图。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020010201052511.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 详细设计及代码实现
由于软件较简单，而且需求分析阶段已经进行了比较明确的建模，所以直接给出部分详细设计并给出部分代码实现。
#### 排列生成函数permutation
由于生成数独需要首先生成3\*3的方格，所以需要对方格的9个位置使用1-9不重复地进行填充。等价于寻找到1个1-9数字的排列。由于需求中要求数独不重复，因此必须有能够生成确定的排列的函数。采用递归思想设计函数，流程图如下。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020011017182573.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
源代码及注释如下：

```cpp
int permutation(int *x, int *values, int length, int& seed)
{
 /*
 x：生成的排列存放的数组
 values：排列的所有元素
 length：x，values中的元素个数
 seed：排列的种子，范围为1-(length!)，和具体的排列一一对应
 */
 if (length == 1) //1个数的排列直接是自身
 {
  x[0] = values[0];
  seed--;  //找到一个排列
  return seed;  //如果seed==0，表示找到seed对应的排列，搜索终止
 }
 int* n_values = new int[length - 1];
 for (int i = 0; i < length; ++i)  //尝试在第一个位置填上values的某个值
 {
  x[0] = values[i];
  for (int j = 0; j < length - 1; ++j)  //新的values中排除该值
  {
   n_values[j] = values[(i + j + 1) % length];
  }
  if (!permutation(x + 1, n_values, length - 1, seed))  //在之前基础上对之后的数再生成排列
  {
   delete[] n_values;
   return 0;  //表示已经找到seed对应的排列了，搜索终止
  }
 }
 delete[] n_values;
 return 1;  //搜索还没有结束
}
```

Block类主要成员
- int nums[9]：含有9个元素的数组
- int seed：用于生成格子内数字的seed
- Block(int _seed=1)：根据seed生成排列的构造函数
- Block(int _seed, int _id)：固定最后一个数，生成其它排列的构造函数
- void swapColumns(int i, int j)：交换两行的方法
- void swapRows(int I, int j)：交换两列的方法
#### Sudoku类主要成员
- Block blocks[9]：9个对应的3\*3方格Block
- int seed：构建中心Block的seed
- int id：构建中心Block的id
- Sudoku swapRows(int x, int i, int j)：交换行的方法
- Sudoku swapColumns(int y, int i, int j)：交换列方法
- Sudoku changeState(int* seed)：根据一个6个元素的数组做行列变换生成新的数独的方法
源代码及注释如下，主要是对seed种的6个元素调用permutation生成对应的排列后做行列变换，难点是如何根据排列来变化行、列使达到对应的顺序：
流程图如下，但是实现过程中直接枚举seed中元素，没有使用循环，逻辑略有不同：
![changeState()](https://img-blog.csdnimg.cn/20200119112338780.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
```cpp
Sudoku Sudoku::changeState(int* seed)
{
 Sudoku new_sudoku(*this);
 
 //六种变换依次进行
 int seed0 = seed[0]%2;
 if (seed0)
  new_sudoku.swapRows(0, 1, 2);
 int seed3 = seed[3]%2;
 if (seed3)
  new_sudoku.swapColumns(0, 1, 2);

 //不能直接用seed[i]，因为会更改值
 int seed1 = seed[1] % 6 + 1;//6为3阶乘
 int x1[3] = { 0 }, y1[3] = { 0,1,2 };
 permutation(x1, y1, 3, seed1);
 for (int i = 0; i < 3; ++i)
 {
  int j = 0;
  for (; y1[j] != x1[i]; ++j);//查找原来序列中对应该位置的内容在哪里
  new_sudoku.swapRows(1, i, j);
  int tmp = y1[j];//交换y中数据，便于后续查找
  y1[j] = y1[i];
  y1[i] = tmp;
 }

 int seed2 = seed[2] % 6 + 1;//不能直接用seed[i]，因为会更改值
 int x2[3] = { 0 }, y2[3] = { 0,1,2 };
 permutation(x2, y2, 3, seed2);
 for (int i = 0; i < 3; ++i)
 {
  int j = 0;
  for (; y2[j] != x2[i]; ++j);//查找原来序列中对应该位置的内容在哪里
  new_sudoku.swapRows(2, i, j);
  int tmp = y2[j];//交换y中数据，便于后续查找
  y2[j] = y2[i];
  y2[i] = tmp;
 }

 int seed4 = seed[4] % 6 + 1;//不能直接用seed[i]，因为会更改值
 int x4[3] = { 0 }, y4[3] = { 0,1,2 };
 permutation(x4, y4, 3, seed4);
 for (int i = 0; i < 3; ++i)
 {
  int j = 0;
  for (; y4[j] != x4[i]; ++j);//查找原来序列中对应该位置的内容在哪里
  new_sudoku.swapColumns(1, i, j);
  int tmp = y4[j];//交换y中数据，便于后续查找
  y4[j] = y4[i];
  y4[i] = tmp;
 }

 int seed5 = seed[5] % 6 + 1;//不能直接用seed[i]，因为会更改值
 int x5[3] = { 0 }, y5[3] = { 0,1,2 };
 permutation(x5, y5, 3, seed5);
 for (int i = 0; i < 3; ++i)
 {
  int j = 0;
  for (; y5[j] != x5[i]; ++j);//查找原来序列中对应该位置的内容在哪里
  new_sudoku.swapColumns(2, i, j);
  int tmp = y5[j];//交换y中数据，便于后续查找
  y5[j] = y5[i];
  y5[i] = tmp;
 }
 return new_sudoku;
 }
```

- void toFile(FILE *f)：输出到文件相关操作
#### SudokuSolver类的主要成员
- int sudoku[81]：存储数独内容的数组。
- int _backtrackSolve(int holder)：输入空格位置的递归求解数独函数。
流程图如下：
![_backtrackSolve()](https://img-blog.csdnimg.cn/20200119112225528.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
源代码及注释如下，核心是递归调用，进入下一层之前预先判断合法性实现剪枝：

```cpp
int SudokuSolver::_backtrackSolve(int holder)
{
 if (holder == -1)//所有空格都填上了
  return 1;
 for (int i = 1; i <= 9; ++i)
 {
  sudoku[holder] = i;
  if (this->_isLegal(holder))
  {
   int n_holder = _find_next_empty(sudoku, 81);
   if (_backtrackSolve(n_holder))//找到解了
    return 1;
   //否则，该值无解，尝试下一个数字
  }
  //否则，该值不合法，尝试下一个解
 }
 sudoku[holder] = 0;//还原现场
 return 0;
}
```

- bool _isLegal(int pos)：判断数独是否合法的函数。
- static int _find_next_empty(int *map, int size)：寻找下一个空格的函数。
- int solve(std::string method = "backtrack")：求解方法
- void print()：输出方法
#### main.cpp中的函数
- 若干打印参数错误的函数
- void handleCreate(string amount)：处理生成数独
源代码及注释如下：
```cpp
void handleCreate(string amount)
{
 int num;
 stringstream ss_num(amount);
 FILE* f = fopen("sudoku.txt", "w");
 if (ss_num >> num)
 {
  //TODO:将种子更新变为定向，避免两次随机结果一样
  int seed = rand() % SEED_MAX + 1;
  while (true)
  {
   Sudoku sudoku(seed, ID);
   int seeds[6] = { 0 };//控制一个基本数独的变换
   bool flag = false;//是否达到数量
   for (seeds[0] = 0; seeds[0] < 2; ++seeds[0])//变换23行
   {
    for (seeds[1] = 0; seeds[1] < 6; ++seeds[1])//变换456行
    {
     for (seeds[2] = 0; seeds[2] < 6; ++seeds[2])//变换789行
     {
      for (seeds[3] = 0; seeds[3] < 2; ++seeds[3])//变换23列
      {
       for (seeds[4] = 0; seeds[4] < 6; ++seeds[4])//变换456列
       {
        for (seeds[5] = 0; seeds[5] < 6; ++seeds[5])//变换789列
        {
         Sudoku n_sudoku(sudoku.changeState(seeds));
         if (!(--num))//生成指定数量
         {
          n_sudoku.toFile(f);
          flag = true;
          break;
         }
         else
         {
          n_sudoku.toFile(f);
          n_sudoku.appendLine(f);
         }
         if (flag)
          break;
        }
        if (flag)
         break;
       }
       if (flag)
        break;
      }
      if (flag)
       break;
     }
     if (flag)
      break;
    }
    if (flag)
     break;
   }
   if (flag)
    break;
  }
 }
 else//输入不是数字
  paramError();
 fclose(f);
 return;
}
```

- handleSolve(string filename)：处理求解数独
源代码及注释如下：
```cpp
void handleSolve(string filename)
{
 FILE *fp;
 int prob[81];
 if (fp = fopen(filename.data(), "r"))
 {
  for (int i = 0; i < 81; ++i)
   fscanf(fp, "%d", &prob[i]);
  SudokuSolver solver(prob);
  solver.solve();
  solver.print();
 }
 else
 {
  fileNotFound();
 }
 return;
}
```
## 测试
### 创建测试项目
使用Visual Studio自带的测试项目模板，关联Sudoku项目进行测试。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200110161758728.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 单元测试设计
由于Visual Studio Community版本没有覆盖率查看功能，因此只能采用人工方式分析覆盖率。经验证，所有测试用例设计都满足判定/条件覆盖，覆盖率为100%。
#### permutation
该函数根据种子seed生成对应的1-9的排列，种子范围为1-9!。函数涉及递归，采用黑盒白盒思想均可，由于实现覆盖较容易，因此设计seed取值最大，最小，最大值偏小，最小值偏大，中间等多个测试用例，全部通过。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200110162404143.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
#### Block
需要测试block直接根据种子生成以及通过指定id（为了实现数独左上角数字固定）情况下能否获得需要的block，另外需要测试swapRaw和swapColumn能否对行列进行所需交换。主要检查block中包含的九元素数组。经过测试符合要求。以下是部分测试设计。
|编号|内容|成功|
|:---:|:---:|:---:|
|1|seed=1,3,5643,...生成|成功|
|2|seed=1,46,3 id=1..9生成|成功|
|3|交换0，1行|成功|
|4|交换0，1列|成功|
#### Sudoku
需要测试能否创建和固定左上角创建所需数独，另外需要测试行列交换以及利用行列交换变异生成新数独功能是否正常。经过测试符合要求。以下是部分测试设计。
|编号|内容|成功|
|:---:|:---:|:---:|
|1|seed=1,4,63 id=1..9生成|成功|
|2|交换12行,34行...|成功|
|3|交换12列,34列...|成功|
|4|改变状态，seed=000000,000001...|成功|
#### 
#### SudokuSolver
需要测试求解出的数独结果是否合法，以及求解时间是否合适等。经测试符合要求。以下是部分测试设计。
|编号|内容|成功|
|:---:|:---:|:---:|
|1|装入手动设计的各种数独查看对象是否正常|成功|
|2|装入各种数独测试判断数独合法的函数|成功|
|3|测试递归求解的函数处理过程和返回值是否正确|成功|
|4|人为设置空格测试寻找空格的函数是否正确|成功|
|5|生成数独题目测试求解结果是否正确|成功|
|6|求解数独测试打印是否显示正确|成功|
### 单元测试结果
主要按照类型设计各种测试Method，尝试各种输入，尝试结果最终版程序未发现问题。但开发过程中测试对发现问题起到了重大帮助。一部分测试由于Visual Studio技术问题无法通过代码反映，但大部分都已经反映在2020.1.16的commit中。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200116171401255.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 进一步测试
通过命令行执行程序，对得到的结果进行验证。测试程序在各种情况下的执行情况。
|编号|命令行参数|结果|
|:---:|:---:|:---:|
|1|-c 1|生成正确|
|2|-c 100|生成正确|
|3|-c 1000000|生成正确|
|4|-c 1000001|输出“请输入1-1000000的数字！”|
|5|-c 0|输出“请输入1-1000000的数字！”|
|6|-cc 12|输出“输入不合法，请使用 ‘suodoku.exe -c 数字’ 或 ‘sudoku.exe -s 文件名’ 格式输入。”|
|7|-c x|输出“请检查-c参数是否为数字。”|
|8|-s sudoku.txt|正确求解|
|9|-s illegalsudoku.txt|输出“该数独无法求解！”|
|10|-s unexistfile.txt|输出“请检查-s参数文件是否存在。”|
另外比较关键的是验证生成数独的不重复和求解数独的正确性。
测试不重复性的代码（Python脚本）：

```python
with open("sudoku.txt", "r") as f:
	sudoku=f.read()sudoku=sudoku.split("\n\n")
print(len(set(sudoku)))
```
|生成个数|预期输出|实际输出|
|:---:|:---:|:---:|
|1|1|1|
|20|20|20|
|100|100|100|
|1000|1000|1000|
|1000000|1000000|1000000|
测试求解准确性的代码参考GUI中的验证。
|编号|预期输出|实际输出|
|:---:|:---:|:---:|
|1|正确|正确|
|2|正确|正确|
|3|正确|正确|
|4|正确|正确|
|5|正确|正确|
## 性能分析与提升
### 创建
使用VisualStudio自带的性能分析分析C++代码的执行情况。由于初次版本下发现创建1000个数独就花费了2秒以上，这样生成1000000个数独就需要半个小时以上的时间，感觉有些慢，所以针对创建1000个数独的情况进行了性能分析。结果如下图。
![性能分析界面](https://img-blog.csdnimg.cn/20200102225856239.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
![性能分析界面](https://img-blog.csdnimg.cn/20200102225905159.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
![handleCreate函数执行情况](https://img-blog.csdnimg.cn/2020010223203290.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
![toFile函数的性能分析](https://img-blog.csdnimg.cn/20200102232332732.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
可以发现IO操作和生成操作几乎一样费时。每次生成数独都进行了文件读写情况下，读写几乎占用了CPU2/3的性能，而其中两个文件相关函数（appendLine，toFile）中最费时间的是文件的打开关闭，以toFile函数为例，其中文件的打开关闭就占了绝大部分的CPU使用。因此对读写逻辑进行优化，直接接收已经打开的文件，避免频繁操作。经过改进后不再频繁打开文件，结果可见文件操作占用时间大大减少，性能显著提升，10000个数独只占用5秒，符合之前IO操作约占2/3时间的分析，突破了性能瓶颈。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020010223502525.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200102234702895.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
这次改进反映在2020年1月2号的commit中。
### 求解数独
人为创建了432个数独题目，每个挖去30个空，运行了5秒以上。性能分析如下。
![解题性能0](https://img-blog.csdnimg.cn/20200116221641446.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
可见文件操作（包括标准输入输出）占了大量的时间，去掉printf后，5184个数独在1.7秒完成。性能有较大提升，分析图如下。
![解题性能1](https://img-blog.csdnimg.cn/2020011622214987.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 性能分析总结
主要是发现文件相关操作，包括标准输入输出耗费资源都非常大。改进后主要的性能瓶颈是生成数独时的changeState()，或者说是它调用的交换行列swapRows()和swapColumns()；还有暂时保留的求解数独中文件读取fscanf()，的判断数独合法函数isLegal()以及递归函数_backtrackSolve()。由于之前算法设计的时候这些算法已经做了各种优化，所以算法方面暂时没有大动作，从性能分析可以看出，在创建数独的时候更快捷地进行行列交换是目前性能关键，求解数独中一次性读取和改变判断数独的合法性的逻辑可能是之后比较容易的一个性能提升点，目前使用的是控制结构+位操作实现，未来可以尝试用更高效的统一的位操作来改进。
## 代码质量分析
尝试使用微软的CppCoreCheck工具进行代码质量分析。
![添加库](https://img-blog.csdnimg.cn/20200115034751503.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)暂时有6个警告需要消除。
![警告](https://img-blog.csdnimg.cn/20200115034836702.jpg)
消除警告后生成。
![生成](https://img-blog.csdnimg.cn/20200115040609656.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
![无警告](https://img-blog.csdnimg.cn/20200115040634930.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
## GUI界面
### 项目结构和思路
按照要求将UI界面和之前的生成求解器独立为两个项目。方便起见，UI界面采用Python编写，使用tkinter库开发。为了避免Python调用C++的繁琐工作，将之前C++项目得到的.exe文件放在该项目目录下作为依赖，使用文件相互通讯，大大简化了编码工作。其中思路部分参考了[这篇博客](https://blog.csdn.net/oDaHaiTaoTao/article/details/52424974)，但是代码由我个人独立完成。
### 面向对象分析设计
#### 用例图
![用例图](https://img-blog.csdnimg.cn/20200118004801742.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
#### 类图
只有两个类，ChooseNumber对象中生成SudokuGUI的一个对象。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200118010109768.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
#### 状态图
由于系统比较简单，这里直接给出了整个系统的状态图。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200118004917874.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
### 设计说明
1. 首先创建输入数独数量的界面，然后根据用户输入判断合法性后再生成实际的数独界面。
2. 通过system调用Sudoku.exe文件执行-c创建任意数量数独，GUI程序读取生成文件，依次显示加载到界面上。注：详细了解需求后，SudokuGUI类中维护了所有数独的列表。
3. 将Entry和SudokuGUI类的内部列表相关联，用于显示数独题目和获取用户解答。
4. 将读取的数独进行挖空，按照每个3x3至少两个，总体不少于30个不多于60个的约束随机挖空，通过9x9个Entry控件显示数独界面，将没有挖空的Entry设置为只读。
5. 加入检查机制，如果用户输入非法，未输入，结果错误等都有相应的提示。如果用户解答正确，也有相应的说明。
### 界面设计
#### 输入数字界面
![输入数字](https://img-blog.csdnimg.cn/20200118010224240.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
功能比较直观
#### 数独界面
![界面](https://img-blog.csdnimg.cn/20200118011128320.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
整体使用Pack来组织，数独部分采用Grid来构造界面。最上方为当前题号，用户在上方的9x9方格的空格中填写数字，点击提交则程序对结果进行检验，点击下一个则进入一个新的题目，点击上一个则返回上一题，**之前填写的会被保留**。
### 实现（部分核心函数）
数独界面初始化相关核心代码如下：

```python
    def __init__(self, num):        
    	self.num = num
    	
        window =Tk()        
        window.geometry('480x300')        
        window.title("数独游戏")
        
        self.identry = Entry(window, justify='center', textvariable=StringVar())        
        self.identry["state"]=DISABLED        
        self.identry.pack()
        
        frame =Frame(window)        
        frame.pack()        # frame.grid(row=0,column=0,sticky=NSEW)
        self.cells=[] #数独空缺口        
        for i in range(9):            
        	self.cells.append([])            
        	for j in range(9):                
        		self.cells[i].append(StringVar())
        
        self.entries=[]        
        for i in range(9):            
        	self.entries.append([])            
        	for j in range(9):
        		entry=Entry(frame,width=2,justify=RIGHT,textvariable=self.cells[i][j])                
        		entry.grid(row=i,column=j,sticky=NSEW)                
        		self.entries[i].append(entry)        
        Button(window,text="上一个",command=self.prev).pack(fill=X)        
        Button(window,text="提交",command=self.validate).pack(fill=X)        
        Button(window,text="下一个",command=self.next).pack(fill=X)        
        # Button(window,text="上一个",command=self.validate).grid(row=1,column=0,sticky=NS)        
        # Button(window,text="验证",command=self.validate).grid(row=2,column=0,sticky=NS)        
        # Button(window,text="下一个",command=self.validate).grid(row=3,column=0,sticky=NS)
        
        # 生成数独        
        os.system("sudoku.exe -c "+str(self.num))        
        with open("sudoku.txt", "r") as f:             
        	sudokus=f.read()        
        sudokus=sudokus.split("\n\n")        
        # print(sudokus)        
        sudokus=[sudoku.split("\n") for sudoku in sudokus]  # 注意列表推导式的顺序        
        # print(sudokus)        
        for i in range(len(sudokus)):            
        	sudokus[i] = [x.split(" ") for x in sudokus[i]]        
        # print(sudokus)        
        self.sudokus = sudokus        
        for sudoku in self.sudokus:            
        	# 挖空            
        	for block in range(9):                
        		row=block//3                
        		column=block%3                
        		sp=random.sample(range(0,9),2)                
        		for pos in range(9):                    
        			if pos in sp:                        
        				bias_x=pos//3                        
        				bias_y=pos%3                        
        				sudoku[row*3+bias_x][column*3+bias_y]=""
            
            	space=random.sample(range(81),random.randint(30,42))            
            	for i in range(81):                
            		if(i in space):                    
            			sudoku[i//9][i%9]=""        
        self.raw_sudokus=copy.deepcopy(sudokus)  #用来确定哪些格子只读
        
        self.index=-1        
        self.next()        
        window.mainloop()
```
验证数独解答的函数代码如下
![验证函数代码](https://img-blog.csdnimg.cn/20200118013007190.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
该程序首先检查所有输入是否都是1-9的整数，如果不是则给出相应的提示，通过检查后，就可以直接通过枚举每行每列没格3\*3小方格中是否出现了9种数来判断数独是否合法了。
### 测试
由于程序本身的代码结构比较简单，主要是GUI界面的测试，因此直接进行系统测试。对应结果如下。
|编号|操作|预期反馈|实际反馈|通过|
|:---:|:---:|:---:|:---:|:---:|
|1|生成个数为1|进入数独界面|进入数独界面|通过|
|2|生成个数为1000000|弹出错误提示框|弹出错误提示框|通过|
|3|生成个数为0|弹出错误提示框|弹出错误提示框|通过|
|4|生成个数为1000001|弹出错误提示框|弹出错误提示框|通过|
|5|页间跳转|成功跳转|成功跳转|通过|
|6|部分解答来回跳转|保留输入|保留输入|通过|
|7|正确解答提交|弹窗提示回答正确|弹窗提示回答正确|通过|
|8|非法字符提交|弹窗提示非法字符|弹窗提示非法字符|通过|
|9|空白格解答提交|弹窗提示空白|弹窗提示回答空白|通过|
|10|数字超范围解答提交|弹窗提示超范围|弹窗提示超范围|通过|
|11|错误解答提交|弹窗提示回答错误|弹窗提示回答错误|通过|

### 结果演示
#### 生成并显示数独
见上图界面设计。
#### 解答输入结果
由于为了实现生成任意数量数独，最终界面有更改，此处是最初版本的界面
![解答过程](https://img-blog.csdnimg.cn/20200115204033527.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
#### 验证结果
空值或非法输入。此处后方是最初版本的界面。
![未填](https://img-blog.csdnimg.cn/20200115204355190.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
特别地，如果不是1-9范围内的数字。此处后方是最初版本的界面。
![范围约束](https://img-blog.csdnimg.cn/20200115204435851.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)
如果解答有问题（结果不满足数独条件）。此处后方是最初版本的界面。
![错误解答](https://img-blog.csdnimg.cn/2020011520450667.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)如果回答正确。此处后方是最初版本的界面。
![正确](https://img-blog.csdnimg.cn/20200115204528250.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjkzOTUyOQ==,size_16,color_FFFFFF,t_70)

