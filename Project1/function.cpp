#include"global.h"
#include"function.h"

//一维数字转换为二维数组
void state_toArc(int e, board se)
{
	for (int i = 3; i >= 1; i--)
		for (int j = 3; j >= 1; j--)
		{
			se[i][j] = e % 10;
			e /= 10;
		}//写for循环不加{}biss嗷
}
//将二维数组转换为一维数字
int arc_toState(const board& se) {//注意e 一定要加上&,不然不能改变e的值
	int e = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			e = e * 10 + se[i][j];
	return e;

}
//返回Snode的F值
int F(const Snode& e) {
	return e.g + e.h;
}


bool success(const int& cur, const int& tar) {
	return(H1(cur, tar) == 0);
}

bool checkvalid(const int& cur, const int& tar) {
	int cur_n = 0, tar_n = 0;
	board curr, tarr;
	state_toArc(cur, curr);
	state_toArc(tar, tarr);

	/*如果硬要在3*3矩阵上遍历比较一个结点和对多个结点的相对关系（可能是值大小的关系，也可能是位置的相对关系）
	对于for循环中i与j标的取值有点讲究
	(1).
	   通常i 和 j 对应的是矩阵的row 和 clumn值，这是一般的逻辑，本函数要找当前元素后面和前面的元素，那么这段代码就会写成
	/*for(int i=1;i<=3;i++)
	   for(int j=1;j<=3;j++)
		 /*接下来对每一个元素cur[i][j]、tar[i][j]，寻找它后面的所有元素要考虑它本身的位置，比如[2,2] 和[2,3]情况下，
		 显然它下一个位置分别是[2,3] 和[3,1],那么对i 的取值就不同,这种分类讨论显然太烦琐了
	(2).
	   在这种情况下，通常遍历时，i取0-8的范围，就是位置值，j取i+1,意思是下一个位置的元素的位置值
	   那么就写成了下面的函数情况。
	   那么位置值0-8怎么映射成矩阵中的下标位置对（x,y)呢？

	/*其实这个的实质就是，我给你一个一维的下标值位置值，你能不能找出对应下标位置值在矩阵中的位置
	|3 2 1|  如图矩阵，3 2 1  4 5 6 7 8 9元素对应的位置值是1 2 3 4 5 6 7 8 9，我们检索的时候，
	|4 5 6|  row=位置值/n,cloumn=位置值%n
	|7 8 9|
	*/

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < i; j++)//找第i+1个元素后面所有的非0元素，如果元素比它小，那就对应逆序数+1
		{

			if ((curr[i / 3 + 1][i % 3 + 1] != 0) && (curr[j / 3 + 1][j % 3 + 1] != 0) && (curr[i / 3 + 1][i % 3 + 1] < curr[j / 3 + 1][j % 3 + 1])) cur_n++;
			if ((tarr[i / 3 + 1][i % 3 + 1] != 0) && (tarr[j / 3 + 1][j % 3 + 1] != 0) && (tarr[i / 3 + 1][i % 3 + 1] < tarr[j / 3 + 1][j % 3 + 1])) tar_n++;
		}
	}

	// 一维数组实现，不需要预先把所有的值赋给数组，而是在比较过程中代入，但也需要比较访问读取具体位置处的值
	/*
	int c[9],t[9];
	for(int i=0;i<9;i++)
	{
	c[i]=cur%10;t[i]=tar%10;

	if (c[i] != 0 && i != 0)
	{
		for (int j = i - 1; j >= 0; j--)
			if (c[j] > c[i]) cur_n++;
	}
	 if (t[i] != 0 && i != 0)
	 {
		 for (int j = i - 1; j >= 0; j--)
			 if (t[j] > t[i]) tar_n++;
	 }
	}
	*/


	return  (cur_n & 1) == (tar_n & 1);
}

//启发函数1  
int H1(int curState, int tarState)
{
	//找当前状态与目标状态的位置不同的非0数字个数
	int num = 0;
	for (int i = 0; i < 9; i++) {
		if ((curState % 10 != tarState % 10)) ++num;

		curState /= 10;
		tarState /= 10;

	}
	return num;
}
//启发函数2
int H2(int curState, int tarState) {
	//找当前状态要移动到目标的最短路径，返回所有状态的最短路径之和
	int num = 0;
	//求位置移动的算法，时间复杂度过高，甚至要n^4
	/*
	Arc curr,tarr;
	state_toArc(cur,curr);
	state_toArc(tar,tarr);
	for(int i=1;i<=3;i++)
		for (int j = 1; j <= 3; j++) {
			if (curr[i][j] == tarr[i][j]) continue;
			else {
				int tmpi, tmpj;
				for (tmpi = 1; tmpi <= 3; tmpj++) {
					for (tmpj = 1; tmpj <= 3; tmpj++)
						if (tarr[tmpi][tmpj] == curr[i][j]) break;
				}
				num += abs(tmpi-i)+abs(tmpj-j);
			}
		}
		*/

		//引入一种新的数组，这个数组的下标值代表的是元素（即key值代表的是value),value值代表的是位置值。
	int cu[9], ta[9];
	int cur = curState, tar = tarState;
	for (int i = 8; i >= 0; i--) {
		cu[cur % 10] = ta[tar % 10] = i;
		cur /= 10;
		tar /= 10;
	}
	//含义是，数字1-8的状态序列到目的序列，它们不同的位置值之差，cu[i] i代表是哪个数字，值代表的是它的位置值0-8。
	//位置值之间的移动的最小步骤不是简单相减，而是要根据它在矩阵上的结构特点，比如位置值0和3，实际上移动过去只需要一步
	//位置值0-8在3*3矩阵上具体的(x,y)的反映上面已经讲过，位置移动值应该是 |xc-xt|+|yc-yt|
	for (int i = 1; i <= 8; i++) {
		num += abs(cu[i] / 3 - ta[i] / 3) + abs(cu[i] % 3 - ta[i] % 3);
	}

	return num;
}
//启发函数3
int H3(int curState)
{   //返回逆序数目*3
	int num = 0;
	board curr;
	state_toArc(curState, curr);
	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 9; j++)
		{
			if ((curr[i / 3 + 1][i % 3 + 1] != 0) && (curr[j / 3 + 1][j % 3 + 1] != 0) && (curr[i / 3 + 1][i % 3 + 1] > curr[j / 3 + 1][j % 3 + 1]))
				++num;
		}
	}

	return num * 3;
}
//启发函数4
int H4(int curState, int tarState) {
	//综合H1与H3
	return (H1(curState, tarState) + H3(curState));
}


//运行open算法，返回值取最短路径的step值
//运行open算法，返回值取最短路径的step值
int run(const int& st, const int& ed) {
	if (!checkvalid(st, ed)) return -1;//检测是否可达，这样可以提高运行效率
	//清理上一次程序运行时产生的数据。
	open_key.clear();
	open_value.clear();
	closed.clear();
	path.clear();
	/*将初始结点放入open表中*/
	int index = 0;//递增的序号值，唯一标识，便于查询pre路径
	Snode start(st, 0, H2(st, ed), index++, -1);//初始化初始结点start的值,其前驱路径的标号是-1，代表不存在
	open_key.insert(make_pair<int, Snode>(int(H2(st, ed)), Snode(start)));//将初始结点放入open_key表中
	open_value.insert(make_pair<Snode, int>(Snode(start), int(H2(st, ed))));//将初始结点放入open_value表中
	//cout << open_key.begin()->first;
	//if (success(target, target)) cout << "1" << endl;
	/*对后续结点进行启发式搜索*/
	while (open_key.size())
	{
		Snode mixNode = open_key.begin()->second;//取出open的第一个元素(该元素也是f值最小的结点)进行扩展
		open_key.erase(open_key.begin());                   //从open表中清除
		open_value.erase(open_value.lower_bound(mixNode));  //从open表中清除
		closed.insert(make_pair<int, bool>(int(mixNode.state), bool(true)));  //将序列放入closed表中，具体的结构值放入path中
		path.push_back(mixNode);//将结点的具体结构放入path中

		//如果是已经到达目标路径，返回最短路径值step
		if (success(mixNode.state, ed)) {
			//cout << "1" << endl;
			return mixNode.g;
		}
		//cout << mixNode.state << endl;
		//outPut(mixNode.state);

		/*对取出的结点进行移动操作，生成新的子节点。*/

		//寻找空格的位置
		int cx = -1, cy = -1;
		board tmp;
		int tmps;
		state_toArc(mixNode.state, tmp);
		//cx，cy代表空格的坐标[cx,cy]
		for (int i = 1; i <= 3; i++) {
			if (cx != -1) break;
			for (int j = 1; j <= 3; j++) {

				if (tmp[i][j] == 0)
				{
					cx = i;
					cy = j;
					break;
				}
			}
		}
		//移动生成子结点
		for (int k = 0; k < 4; k++) {
			int nx = cx + move_x[k];
			int ny = cy + move_y[k];
			if (nx >= 1 && nx <= 3 && ny >= 1 && ny <= 3)//保证移动后的空格不越界
			{
				swap(tmp[cx][cy], tmp[nx][ny]);//将原来空格和移动后的空格应在的位置的元素，交换顺序
				tmps = arc_toState(tmp);  //提取出新生成的状态序列state值
				swap(tmp[cx][cy], tmp[nx][ny]);//还原序列，用于空格其他方向的移动


				/*对新生成的子节点进行判定，是否入open表中*/
				Snode newNode(tmps, mixNode.g + 1, H2(tmps, ed), index++, mixNode.cur);//初始化新生成的子节点
				//新生成的子节点的state是tmps,深度是父节点mixNode的深度+1,h用判定函数h（x)求得,序列号按序+1，父节点序列号是mixNode的序列号cur
				int newF = F(newNode);//保存新结点的F值

				//查找新生成结点的state是否在closed表中
				if (!closed.count(tmps))//如果不在closed表中，执行以下操作
				{
					//查找新生成结点的state是否在open表中

					/*因为open表的两个元素并没有直接表示state值的选项，所以count函数不能用，查找元素的时候，就要自己重写一个查找算法
					/按照传统的查找，必然是遍历每个元素，看open表中是否有元素的state值跟新结点的state值相同，这时候搜索效率就有点大，这就体现出来双map表的优势了
					/双map表，key-value,value-key，在查找元素的时候，不用遍历，直接利用low_bound()函数找value-key表中的的first值value
					/在value-key表中，first值value的从小到大的排列顺序是新类型Snode的比较大小的过程，在定义的时候已经定义，若Snode a==Snode b,必然是它们俩的序列值state值相同，<号也是state值相比较的
					*/
					map<Snode, int>::iterator it_v = open_value.lower_bound(newNode);
					//itv指针指向state值>=newNode的迭代器元素，如果该元素的first值恰好=newNode,说明newNode的序列值state在open表中存在，这就是查找的办法了。

					map<int, Snode>::iterator it_k;//创建指向key-value表迭代器的指针it_k
					//如果在open表中
					if (it_v != open_value.end() && it_v->first == newNode) {
						//如果新生成的结点是相对于原open表中结点的最优解
						if (newF < F(it_v->first)) {
							for (it_k = open_key.lower_bound(F(it_v->first)); it_k != open_key.upper_bound(F(it_v->first)); ++it_k)
								if (it_k->second == newNode) break;
							//删除原有open表中结点
							open_key.erase(it_k);
							open_value.erase(it_v);
							//将新结点加入open表中
							open_key.insert(make_pair<int, Snode>(int(newF), Snode(newNode)));
							open_value.insert(make_pair<Snode, int>(Snode(newNode), int(newF)));
						}
						//不是最优解，放弃新生成的结点
					}
					//既不在open表中，也不在closed表中
					else {
						//将新结点加入open表中
						open_key.insert(make_pair<int, Snode>(int(newF), Snode(newNode)));
						open_value.insert(make_pair<Snode, int>(Snode(newNode), int(newF)));
					}
				}

				else if (closed.count(tmps))  //如果在closed表中，执行以下操作
				{
					//不用判断是否在open表中，因为想先入closed表必须先入open表，想插入一个结点到open表时，如果它已经在closed表中，是不会把它放到open表里的

					//查找到closed表里的具体结构path中保存的旧Snode，比较f值，看是否新结点是更优解
					int locate;
					for (locate = 0; locate < path.size(); locate++) {
						if (path[locate] == newNode) break;//Snode类型的==号代表state值相同
					}
					//如果是更优解
					if (newF < F(path[locate]) && (path[locate].state == tmps)) {
						//将原closed表中的元素删除，将新结点放入open表中。新结点的路径在新结点初始化时就已经保存，新结点的f值在加入open表时进行保存
						closed.erase(closed.lower_bound(newNode.state));
						path.erase(path.begin() + locate);
						//将新结点加入open表中
						open_key.insert(make_pair<int, Snode>(int(newF), Snode(newNode)));
						open_value.insert(make_pair<Snode, int>(Snode(newNode), int(newF)));
					}
					//如果不是更优解，舍弃新生成的结点newNode
				}
				/*对新生成的子节点进行判定，是否入open表中的判定结束*/
			}
		}/*对移动生成的新结点的整个操作结束*/

	}
	//函数走到这里，代表open表为空，则无解，返回步骤-1
	return -1;
}
void inPut(board s) {
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> s[i][j];
		}
	}
}
void outPut(const int& e) {

	board tmp;
	state_toArc(e, tmp);
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j)
			cout << tmp[i][j] << " ";
		puts("");
	}

}
//要从后向前找到最优解的路径，采取的是后序遍历，那必然传递参数有pre,有step(第几步），由于查找时是查找path上的路径，path是依次进栈的方法加入元素
//故pre元素必定在子元素的前面
void findPath(int pre, int size, int step) {
	if (step == -1) {
		return;

	}
	else if (step == 0) {
		cout << "Step-->" << step << endl;
		cout << endl;
		outPut(path[size].state);
		cout << endl;
		return;
	}
	for (int i = size; i >= 0; i--) {
		//找到path中原结点的pre结点，递归调用函数，输出结果
		if (path[i].cur == pre) findPath(path[i].pre, i, step - 1);
	}
	cout << "Step--> " << step << endl;
	cout << endl;
	outPut(path[size].state);
	cout << endl;

}

//非要写个这个调用函数，而不是直接在main函数中调用，是因为在main函数中，它提示我path的iterator越界，我也不知道为什么，可能跟这个变量跨cpp文件有关吧
void isOk(int step) {
	findPath((path.end() - 1)->pre, path.size() - 1, step);
}