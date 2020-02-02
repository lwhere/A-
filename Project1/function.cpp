#include"global.h"
#include"function.h"

//һά����ת��Ϊ��ά����
void state_toArc(int e, board se)
{
	for (int i = 3; i >= 1; i--)
		for (int j = 3; j >= 1; j--)
		{
			se[i][j] = e % 10;
			e /= 10;
		}//дforѭ������{}biss�
}
//����ά����ת��Ϊһά����
int arc_toState(const board& se) {//ע��e һ��Ҫ����&,��Ȼ���ܸı�e��ֵ
	int e = 0;
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			e = e * 10 + se[i][j];
	return e;

}
//����Snode��Fֵ
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

	/*���ӲҪ��3*3�����ϱ����Ƚ�һ�����ͶԶ��������Թ�ϵ��������ֵ��С�Ĺ�ϵ��Ҳ������λ�õ���Թ�ϵ��
	����forѭ����i��j���ȡֵ�е㽲��
	(1).
	   ͨ��i �� j ��Ӧ���Ǿ����row �� clumnֵ������һ����߼���������Ҫ�ҵ�ǰԪ�غ����ǰ���Ԫ�أ���ô��δ���ͻ�д��
	/*for(int i=1;i<=3;i++)
	   for(int j=1;j<=3;j++)
		 /*��������ÿһ��Ԫ��cur[i][j]��tar[i][j]��Ѱ�������������Ԫ��Ҫ�����������λ�ã�����[2,2] ��[2,3]����£�
		 ��Ȼ����һ��λ�÷ֱ���[2,3] ��[3,1],��ô��i ��ȡֵ�Ͳ�ͬ,���ַ���������Ȼ̫������
	(2).
	   ����������£�ͨ������ʱ��iȡ0-8�ķ�Χ������λ��ֵ��jȡi+1,��˼����һ��λ�õ�Ԫ�ص�λ��ֵ
	   ��ô��д��������ĺ��������
	   ��ôλ��ֵ0-8��ôӳ��ɾ����е��±�λ�öԣ�x,y)�أ�

	/*��ʵ�����ʵ�ʾ��ǣ��Ҹ���һ��һά���±�ֵλ��ֵ�����ܲ����ҳ���Ӧ�±�λ��ֵ�ھ����е�λ��
	|3 2 1|  ��ͼ����3 2 1  4 5 6 7 8 9Ԫ�ض�Ӧ��λ��ֵ��1 2 3 4 5 6 7 8 9�����Ǽ�����ʱ��
	|4 5 6|  row=λ��ֵ/n,cloumn=λ��ֵ%n
	|7 8 9|
	*/

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < i; j++)//�ҵ�i+1��Ԫ�غ������еķ�0Ԫ�أ����Ԫ�ر���С���ǾͶ�Ӧ������+1
		{

			if ((curr[i / 3 + 1][i % 3 + 1] != 0) && (curr[j / 3 + 1][j % 3 + 1] != 0) && (curr[i / 3 + 1][i % 3 + 1] < curr[j / 3 + 1][j % 3 + 1])) cur_n++;
			if ((tarr[i / 3 + 1][i % 3 + 1] != 0) && (tarr[j / 3 + 1][j % 3 + 1] != 0) && (tarr[i / 3 + 1][i % 3 + 1] < tarr[j / 3 + 1][j % 3 + 1])) tar_n++;
		}
	}

	// һά����ʵ�֣�����ҪԤ�Ȱ����е�ֵ�������飬�����ڱȽϹ����д��룬��Ҳ��Ҫ�ȽϷ��ʶ�ȡ����λ�ô���ֵ
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

//��������1  
int H1(int curState, int tarState)
{
	//�ҵ�ǰ״̬��Ŀ��״̬��λ�ò�ͬ�ķ�0���ָ���
	int num = 0;
	for (int i = 0; i < 9; i++) {
		if ((curState % 10 != tarState % 10)) ++num;

		curState /= 10;
		tarState /= 10;

	}
	return num;
}
//��������2
int H2(int curState, int tarState) {
	//�ҵ�ǰ״̬Ҫ�ƶ���Ŀ������·������������״̬�����·��֮��
	int num = 0;
	//��λ���ƶ����㷨��ʱ�临�Ӷȹ��ߣ�����Ҫn^4
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

		//����һ���µ����飬���������±�ֵ�������Ԫ�أ���keyֵ�������value),valueֵ�������λ��ֵ��
	int cu[9], ta[9];
	int cur = curState, tar = tarState;
	for (int i = 8; i >= 0; i--) {
		cu[cur % 10] = ta[tar % 10] = i;
		cur /= 10;
		tar /= 10;
	}
	//�����ǣ�����1-8��״̬���е�Ŀ�����У����ǲ�ͬ��λ��ֵ֮�cu[i] i�������ĸ����֣�ֵ�����������λ��ֵ0-8��
	//λ��ֵ֮����ƶ�����С���費�Ǽ����������Ҫ�������ھ����ϵĽṹ�ص㣬����λ��ֵ0��3��ʵ�����ƶ���ȥֻ��Ҫһ��
	//λ��ֵ0-8��3*3�����Ͼ����(x,y)�ķ�ӳ�����Ѿ�������λ���ƶ�ֵӦ���� |xc-xt|+|yc-yt|
	for (int i = 1; i <= 8; i++) {
		num += abs(cu[i] / 3 - ta[i] / 3) + abs(cu[i] % 3 - ta[i] % 3);
	}

	return num;
}
//��������3
int H3(int curState)
{   //����������Ŀ*3
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
//��������4
int H4(int curState, int tarState) {
	//�ۺ�H1��H3
	return (H1(curState, tarState) + H3(curState));
}


//����open�㷨������ֵȡ���·����stepֵ
//����open�㷨������ֵȡ���·����stepֵ
int run(const int& st, const int& ed) {
	if (!checkvalid(st, ed)) return -1;//����Ƿ�ɴ���������������Ч��
	//������һ�γ�������ʱ���������ݡ�
	open_key.clear();
	open_value.clear();
	closed.clear();
	path.clear();
	/*����ʼ������open����*/
	int index = 0;//���������ֵ��Ψһ��ʶ�����ڲ�ѯpre·��
	Snode start(st, 0, H2(st, ed), index++, -1);//��ʼ����ʼ���start��ֵ,��ǰ��·���ı����-1����������
	open_key.insert(make_pair<int, Snode>(int(H2(st, ed)), Snode(start)));//����ʼ������open_key����
	open_value.insert(make_pair<Snode, int>(Snode(start), int(H2(st, ed))));//����ʼ������open_value����
	//cout << open_key.begin()->first;
	//if (success(target, target)) cout << "1" << endl;
	/*�Ժ�������������ʽ����*/
	while (open_key.size())
	{
		Snode mixNode = open_key.begin()->second;//ȡ��open�ĵ�һ��Ԫ��(��Ԫ��Ҳ��fֵ��С�Ľ��)������չ
		open_key.erase(open_key.begin());                   //��open�������
		open_value.erase(open_value.lower_bound(mixNode));  //��open�������
		closed.insert(make_pair<int, bool>(int(mixNode.state), bool(true)));  //�����з���closed���У�����Ľṹֵ����path��
		path.push_back(mixNode);//�����ľ���ṹ����path��

		//������Ѿ�����Ŀ��·�����������·��ֵstep
		if (success(mixNode.state, ed)) {
			//cout << "1" << endl;
			return mixNode.g;
		}
		//cout << mixNode.state << endl;
		//outPut(mixNode.state);

		/*��ȡ���Ľ������ƶ������������µ��ӽڵ㡣*/

		//Ѱ�ҿո��λ��
		int cx = -1, cy = -1;
		board tmp;
		int tmps;
		state_toArc(mixNode.state, tmp);
		//cx��cy����ո������[cx,cy]
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
		//�ƶ������ӽ��
		for (int k = 0; k < 4; k++) {
			int nx = cx + move_x[k];
			int ny = cy + move_y[k];
			if (nx >= 1 && nx <= 3 && ny >= 1 && ny <= 3)//��֤�ƶ���Ŀո�Խ��
			{
				swap(tmp[cx][cy], tmp[nx][ny]);//��ԭ���ո���ƶ���Ŀո�Ӧ�ڵ�λ�õ�Ԫ�أ�����˳��
				tmps = arc_toState(tmp);  //��ȡ�������ɵ�״̬����stateֵ
				swap(tmp[cx][cy], tmp[nx][ny]);//��ԭ���У����ڿո�����������ƶ�


				/*�������ɵ��ӽڵ�����ж����Ƿ���open����*/
				Snode newNode(tmps, mixNode.g + 1, H2(tmps, ed), index++, mixNode.cur);//��ʼ�������ɵ��ӽڵ�
				//�����ɵ��ӽڵ��state��tmps,����Ǹ��ڵ�mixNode�����+1,h���ж�����h��x)���,���кŰ���+1�����ڵ����к���mixNode�����к�cur
				int newF = F(newNode);//�����½���Fֵ

				//���������ɽ���state�Ƿ���closed����
				if (!closed.count(tmps))//�������closed���У�ִ�����²���
				{
					//���������ɽ���state�Ƿ���open����

					/*��Ϊopen�������Ԫ�ز�û��ֱ�ӱ�ʾstateֵ��ѡ�����count���������ã�����Ԫ�ص�ʱ�򣬾�Ҫ�Լ���дһ�������㷨
					/���մ�ͳ�Ĳ��ң���Ȼ�Ǳ���ÿ��Ԫ�أ���open�����Ƿ���Ԫ�ص�stateֵ���½���stateֵ��ͬ����ʱ������Ч�ʾ��е��������ֳ���˫map���������
					/˫map��key-value,value-key���ڲ���Ԫ�ص�ʱ�򣬲��ñ�����ֱ������low_bound()������value-key���еĵ�firstֵvalue
					/��value-key���У�firstֵvalue�Ĵ�С���������˳����������Snode�ıȽϴ�С�Ĺ��̣��ڶ����ʱ���Ѿ����壬��Snode a==Snode b,��Ȼ��������������ֵstateֵ��ͬ��<��Ҳ��stateֵ��Ƚϵ�
					*/
					map<Snode, int>::iterator it_v = open_value.lower_bound(newNode);
					//itvָ��ָ��stateֵ>=newNode�ĵ�����Ԫ�أ������Ԫ�ص�firstֵǡ��=newNode,˵��newNode������ֵstate��open���д��ڣ�����ǲ��ҵİ취�ˡ�

					map<int, Snode>::iterator it_k;//����ָ��key-value���������ָ��it_k
					//�����open����
					if (it_v != open_value.end() && it_v->first == newNode) {
						//��������ɵĽ���������ԭopen���н������Ž�
						if (newF < F(it_v->first)) {
							for (it_k = open_key.lower_bound(F(it_v->first)); it_k != open_key.upper_bound(F(it_v->first)); ++it_k)
								if (it_k->second == newNode) break;
							//ɾ��ԭ��open���н��
							open_key.erase(it_k);
							open_value.erase(it_v);
							//���½�����open����
							open_key.insert(make_pair<int, Snode>(int(newF), Snode(newNode)));
							open_value.insert(make_pair<Snode, int>(Snode(newNode), int(newF)));
						}
						//�������Ž⣬���������ɵĽ��
					}
					//�Ȳ���open���У�Ҳ����closed����
					else {
						//���½�����open����
						open_key.insert(make_pair<int, Snode>(int(newF), Snode(newNode)));
						open_value.insert(make_pair<Snode, int>(Snode(newNode), int(newF)));
					}
				}

				else if (closed.count(tmps))  //�����closed���У�ִ�����²���
				{
					//�����ж��Ƿ���open���У���Ϊ������closed���������open�������һ����㵽open��ʱ��������Ѿ���closed���У��ǲ�������ŵ�open�����

					//���ҵ�closed����ľ���ṹpath�б���ľ�Snode���Ƚ�fֵ�����Ƿ��½���Ǹ��Ž�
					int locate;
					for (locate = 0; locate < path.size(); locate++) {
						if (path[locate] == newNode) break;//Snode���͵�==�Ŵ���stateֵ��ͬ
					}
					//����Ǹ��Ž�
					if (newF < F(path[locate]) && (path[locate].state == tmps)) {
						//��ԭclosed���е�Ԫ��ɾ�������½�����open���С��½���·�����½���ʼ��ʱ���Ѿ����棬�½���fֵ�ڼ���open��ʱ���б���
						closed.erase(closed.lower_bound(newNode.state));
						path.erase(path.begin() + locate);
						//���½�����open����
						open_key.insert(make_pair<int, Snode>(int(newF), Snode(newNode)));
						open_value.insert(make_pair<Snode, int>(Snode(newNode), int(newF)));
					}
					//������Ǹ��Ž⣬���������ɵĽ��newNode
				}
				/*�������ɵ��ӽڵ�����ж����Ƿ���open���е��ж�����*/
			}
		}/*���ƶ����ɵ��½���������������*/

	}
	//�����ߵ��������open��Ϊ�գ����޽⣬���ز���-1
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
//Ҫ�Ӻ���ǰ�ҵ����Ž��·������ȡ���Ǻ���������Ǳ�Ȼ���ݲ�����pre,��step(�ڼ����������ڲ���ʱ�ǲ���path�ϵ�·����path�����ν�ջ�ķ�������Ԫ��
//��preԪ�رض�����Ԫ�ص�ǰ��
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
		//�ҵ�path��ԭ����pre��㣬�ݹ���ú�����������
		if (path[i].cur == pre) findPath(path[i].pre, i, step - 1);
	}
	cout << "Step--> " << step << endl;
	cout << endl;
	outPut(path[size].state);
	cout << endl;

}

//��Ҫд��������ú�����������ֱ����main�����е��ã�����Ϊ��main�����У�����ʾ��path��iteratorԽ�磬��Ҳ��֪��Ϊʲô�����ܸ����������cpp�ļ��йذ�
void isOk(int step) {
	findPath((path.end() - 1)->pre, path.size() - 1, step);
}