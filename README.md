# 南京航空航天大学数据结构课程设计（2022-2023学年）
南京航空航天大学数据结构课程设计（2022-2023学年）  
* 极为不建议抄袭，可以查看代码思路！若被查验自行承担后果！！！
## 课程设计题目
### 一、 必做题
#### 1、菜鸟智慧系统（必做）（线性表）

[问题描述]
使用双向链表模拟快递驿站的系统运作：
+ 假设快递驿站的货架分小、中、大3种类型，容量分别为500、100、50个包裹；该快递站关联的社区人员为MAX_PERSON人（例如，限定为30人，每人唯一手机号）。
+ 驿站每天都会来一批新的包裹。包裹根据大小类型分别上对应的货架，加入对应链表表尾，并使用该货架当前可用的最小编号。用N[1]、N[2]、N[3]分别表示每天随机来的大、中、小包裹数量，保证N[i]在货架的承受能力之内。
+ 包裹信息包括：包裹编号（生成的取件码，分别为1-x(小)，2-x（中）, 3-x（大））、取件人姓名、取件人手机号、包裹大小（小1、中2、大3）、到达日期。
+ 包裹上架时，按照包裹编号从小到大的顺序排列。 
+ 包裹取出后就从对应链表中删除。用M表示每天随机来取包裹的人数，且M≤MAX_PERSON。
+ 包裹最多在驿站存放两天，逾期则退还寄件人（从货架上清除）。
+ 当一人来取包裹时，可通过提供其任一取件码或手机号查询包裹并取出该人员所有关联的包裹。
+ 设计相应的分析、统计功能（自定义），例如当天收包裹数量最多的人，当天有包裹人的平均包裹数量，一周内与其被退回的包裹数量等。
+ 可根据需要做功能拓展，使得模拟系统更接近实用或在现有商用快递系统的基础上有针对性的创新（*）
+ 该问题需有较好的展示性，能够演示快递收发过程。
[基本要求]
（1）	所有事件均随机生成
（2）	用文件存储货架状态，所有变更均应反应在文件中。存储形式自行设计，但务必清晰、直观


#### 2、算术表达式求值 (必做)（栈）
[问题描述]
一个算术表达式是由操作数(operand)、运算符(operator)和界限符(delimiter)组成的。假设操作数是正实数，运算符只含加减乘除等四种运算符，界限符有左右括号和表达式起始、结束符“#”，如：#6+15*（21-8/4）#。引入表达式起始、结束符是为了方便。编程利用“运算符优先法”求算术表达式的值。
[基本要求]
+ 从键盘或文件读入一个合法的算术表达式，输出正确的结果。
+ 显示输入序列和栈的变化过程。
+ 考虑算法的健壮性，当表达式错误时，要给出错误原因的提示。
+ 实现非整数的处理（*）。


#### 3、特殊路径统计（必做)（树和图）
[问题描述]
给定一颗有N个节点（编号为1-N）的树。
两个节点a，b（a<b）之间的简单路径上若所有节点编号i均在a，b之间（a≤i≤b），则该路径可标记为特殊路径。
试统计树上一共有多少条特殊路径。
[输入格式]
+ 第一行包含一个整数N，代表节点数
+ 第二行包含N个整数p1，p2，…，pn，代表每个节点的父节点编号。若pi=0，则该节点为树的根节点
[输出数据]
输出树上一共有多少条特殊路径
[补充说明]
+ 0≤pi≤N
+ 有且仅有一个pi=0
+ 输入的图是一棵树
[样例1]  
输入：
7  
0 5 5 1 4 1 4  
输出：  
10  
[样例2]  
输入：  
5  
2 3 0 2 2  
输出：  
7  

#### 4、【4】公交线路提示 (必做)（图）
[问题描述]
根据真实南京公交线路图，建立南京主要公交线路图的存储结构。  
[基本要求]  
+ 输入任意两站点，给出转车次数最少的乘车路线。  
+ 输入任意两站点，给出经过站点最少的乘车路线。


#### 5、Huffman编码与解码（必做）（Huffman编码、二叉树）
[问题描述]  
对一篇不少于5000字符的英文文章（source.txt），统计各字符出现的次数，实现Huffman编码(code.dat)，以及对编码结果的解码(recode.txt)。  
[基本要求]  
+ 输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
+ 在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，编码结果必须是二进制形式，即0 1的信息用比特位表示，不能用字符‘0’和‘1’表示（*）。
+ 实现解码功能。


#### 6、排序算法比较（必做）（排序）
[问题描述]  
利用随机函数产生10个样本，每个样本有50000个随机整数（并使第一个样本是正序，第二个样本是逆序），利用直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序8种排序方法进行排序（结果为由小到大的顺序），并统计每一种排序算法对不同样本所耗费的时间。  
 [基本要求]  
+ 原始数据存在文件中，用相同样本对不同算法进行测试；
+ 屏幕显示每种排序算法对不同样本所花的时间；

### 二、选做题
#### 7、【1】火车购票 (选做)（线性表）
[问题描述]  
请实现一个铁路购票系统的简单座位分配算法，来处理一节车厢的座位分配。
假设一节车厢有20排、每一排5个座位。为方便起见，我们用1到100来给所有的座位编号，第一排是1到5号，第二排是6到10号，依次类推，第20排是96到100号。
购票时，一个人可能购一张或多张票，最多不超过5张。如果这几张票可以安排在同一排编号相邻的座位，则应该安排在编号最小的相邻座位。否则应该安排在编号最小的几个空座位中（不考虑是否相邻）。
假设初始时车票全部未被购买，现在给了一些购票指令，请你处理这些指令。
[输入格式]  
对于所有评测用例，1 ≤ n ≤ 100，所有购票数量之和不超过100。
输入的第一行包含一个整数n，表示购票指令的数量。
第二行包含n个整数，每个整数p在1到5之间，表示要购入的票数，相邻的两个数之间使用一个空格分隔。  
[输出格式]    
输出n行，每行对应一条指令的处理结果。
对于购票指令p，输出p张车票的编号，按从小到大排序。
[样例]  
输入：  
4  
2 5 4 2  
输出：  
1 2  
6 7 8 9 10  
11 12 13 14  
3 4  
#### 9、【3】通信管理系统（选做）（图）
[问题描述]
你负责管理一个计算机通信系统。
有n台计算机接入了该系统，编号为1~n，它们之间可以互相发送数据。
由于设备条件限制，机器之间不能任意多地发送数据。每两台机器之间均有一个“每日可用额度”的限制，单位为MB/day，表示这两台机器每日可以互相发送的数据量（双方各自向对方发送的数据量之和）的最大值。
最初，任意两台机器的每日可用额度均为0。为了能发送数据，机器管理者需要向你申请额度。每个申请形如u v x y的格式，表示机器u和v的每日可用额度增大x MB/day，持续y天（即从申请当天开始至申请后第y-1天内有效，从第y天开始失效）。不同申请的效果是可以叠加的。
定义每台机器的“通信主要对象”为当前时刻与该机器的每日可用额度最大的机器（如果有并列，则取其中编号最小的机器）；如果一台机器与任何机器的每日可用额度均为0，则称其为“通信孤岛”，并认为其没有“通信主要对象”；如果两台机器x和y互为“通信主要对象”，则称它们是一个“通信对”。
每天开始时，你都会先接受若干个额度申请，你需要依次处理这些申请；而后，你将接收到若干个查询某台机器的“通信主要对象”的请求；最后，你可能还希望求出此时的“通信孤岛”和“通信对”各有多少。
请你编写一段程序来实现上述任务。
[输入格式]
第一行：2个正整数n，m，表示机器数和天数。
接下来3m行，每两行描述一天中的事件，格式如下：
+ 第1行：首先是一个非负整数ki，表示当天额度申请的数量。接下来有4ki个非负整数，依次描述每一个额度申请，格式如题面中所述。
+ 第2行：首先是一个非负整数li，表示当天查询“通信主要对象”的数量。接下来有li个正整数，依次表示查询的机器编号，保证编号在[1，n]范围内。
+ 第3行：2个整数pi，qi，取值均为0或1，分别表示当天是否要查询“通信孤岛”和“通信对”的数量。其中pi=1表示需要查询“通信孤岛”的数量，pi=0表示不需要查询；qi的含义同理。  
[输出格式]  
对于每个查询分别输出一行，一个非负整数表示该查询的答案。
查询按照天数顺序输出，对于同一天内的查询，先按照输入顺序输出所有查询“通信主要对象”的答案，再依次输出查询“通信孤岛”和“通信对”的答案（如果当天需要查询的话）。
如果某台被查询“通信主要对象”的机器是“通信孤岛”，认为查询结果为0。
[样例]
输入：
3 3  
2 1 2 2 3 1 3 3 2  
1 1  
0 0  
1 2 3 3 1  
2 1 2  
0 1  
0  
2 1 3  
1 1  
输出：  
3  
3  
3  
1  
2  
0  
1  
1  

#### 12、【2】连连看（选做）（图）
[问题描述]  
建立一个10*20的矩形方格图，其中有10种不同的图案，每种图案个数为偶数，填满矩形方格图。  
[基本要求]  
（1）随机产生原始数据；  
（2）输入两个位置，如果两者图案相同，并且可以用小于等于3条直线相连，即可消除该两个图案。  


#### 15、【2】迷宫问题（选做）（栈与队列）  
[问题描述]  
利用栈操作实现迷宫问题求解。  
[基本要求]  
（1）从文件中读取数据，生成模拟迷宫地图，不少于20行20列。  
（2）给出任意入口和出口，显示输出迷宫路线。  

#### 20、【4】平衡二叉树操作的演示（选做）（查找）
[问题描述]  
利用平衡二叉树实现一个动态查找表。
[基本要求]  
（1）从文件读取数据  
（2）实现动态查找表的三种基本功能：查找、插入和删除。  
（3）以可验证的方式输出结果  






