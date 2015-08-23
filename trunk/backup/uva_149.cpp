#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <cctype>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <stack>

using namespace std;

#define DEBUG 1

struct Point {
	int x;
	int y;
};

struct Tree {
	struct Point co;
	enum position {
		TOPLEFT, TOPRIGHT, BOTTOMLEFT, BOTTOMRIGHT, LEFT, RIGHT, TOP, BOTTOM
	};
	enum position po;
	Tree(int x, int y, enum position p) {
		co.x = x;
		co.y = y;
		po = p;
	}
};

bool isObscured(struct Point & eye, struct Point & p0, struct Point & p1, int & dia) {
	const float fRad = ((float) (180)) / (3.1415926535);
	const float fMax = 0.99999998476912904932780850903444f;
	float disEyeP0 = sqrt((float) (pow(p0.x - eye.x, 2) + pow(p0.y - eye.y, 2)));
	float disEyeP1 = sqrt((float) (pow(p1.x - eye.x, 2) + pow(p1.y - eye.y, 2)));
	float disP0P1 = sqrt((float) (pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2)));
	float arcEyeP0P1 = (pow(disEyeP0, 2) + pow(disEyeP1, 2) - pow(disP0P1, 2)) / (2 * disEyeP0 * disEyeP1);
	if (arcEyeP0P1 >= fMax)
		return true;
	float angleEyeP0P1 = acos(arcEyeP0P1) * fRad;
	float angleEyeP0 = asin(((float) dia) / 2.0f / disEyeP0) * fRad;
	float angleEyeP1 = asin(((float) dia) / 2.0f / disEyeP1) * fRad;
	if (angleEyeP0P1 - angleEyeP0 - angleEyeP1 <= 0.01f) {
		return true;
	} else {
		return false;
	}
}

int main(int argc, char * argv[]) {
	float diaIn, xIn, yIn;
	struct Point eye;
	while (true) {
		cin >> diaIn;
		cin >> xIn;
		cin >> yIn;
		if (diaIn == 0 && xIn == 0 && yIn == 0)
			break;
		int dia = (int) (diaIn * 100 + 0.5);
		eye.x = (int) (xIn * 100 + 0.5);
		eye.y = (int) (yIn * 100 + 0.5);
		vector<struct Tree> done;
		vector<struct Tree> curr;
		int seeNum = 0;
		curr.push_back(Tree(0, 0, Tree::BOTTOMLEFT));
		curr.push_back(Tree(100, 0, Tree::BOTTOMRIGHT));
		curr.push_back(Tree(100, 100, Tree::TOPRIGHT));
		curr.push_back(Tree(0, 100, Tree::TOPLEFT));
		int noSee = 0;
		while (true) {
			int notSeeNum = 0;
			for (int i = 0; i < curr.size(); i++) {
				bool see = true;
				for (int j = 0; j < done.size(); j++) {
					if (isObscured(eye, curr[i].co, done[j].co, dia)) {
						see = false;
						break;
					}
				}
				if (see) {
					++seeNum;
				} else {
					++notSeeNum;
				}
			}
			if (DEBUG) {
				cout << "seeNum: " << seeNum << ", done.size: " << done.size() << ", " << "curr.size: " << curr.size() << ", notSeeNum: " << notSeeNum << endl;
			}

			if (notSeeNum == curr.size()) {
				++noSee;
				if (noSee > 2)
					break;
			}

			vector<struct Tree> v;
			for (int i = 0; i < curr.size(); i++) {
				if (curr[i].po == Tree::BOTTOMLEFT) {
					v.push_back(Tree(curr[i].co.x - 100, curr[i].co.y - 100, Tree::BOTTOMLEFT));
					v.push_back(Tree(curr[i].co.x, curr[i].co.y - 100, Tree::BOTTOM));
					v.push_back(Tree(curr[i].co.x - 100, curr[i].co.y, Tree::LEFT));
				} else if (curr[i].po == Tree::BOTTOM) {
					v.push_back(Tree(curr[i].co.x, curr[i].co.y - 100, Tree::BOTTOM));
				} else if (curr[i].po == Tree::BOTTOMRIGHT) {
					v.push_back(Tree(curr[i].co.x + 100, curr[i].co.y - 100, Tree::BOTTOMRIGHT));
					v.push_back(Tree(curr[i].co.x, curr[i].co.y - 100, Tree::BOTTOM));
					v.push_back(Tree(curr[i].co.x + 100, curr[i].co.y, Tree::RIGHT));
				} else if (curr[i].po == Tree::RIGHT) {
					v.push_back(Tree(curr[i].co.x + 100, curr[i].co.y, Tree::RIGHT));
				} else if (curr[i].po == Tree::TOPRIGHT) {
					v.push_back(Tree(curr[i].co.x + 100, curr[i].co.y + 100, Tree::TOPRIGHT));
					v.push_back(Tree(curr[i].co.x + 100, curr[i].co.y, Tree::RIGHT));
					v.push_back(Tree(curr[i].co.x, curr[i].co.y + 100, Tree::TOP));
				} else if (curr[i].po == Tree::TOP) {
					v.push_back(Tree(curr[i].co.x, curr[i].co.y + 100, Tree::TOP));
				} else if (curr[i].po == Tree::TOPLEFT) {
					v.push_back(Tree(curr[i].co.x - 100, curr[i].co.y + 100, Tree::TOPLEFT));
					v.push_back(Tree(curr[i].co.x, curr[i].co.y + 100, Tree::TOP));
					v.push_back(Tree(curr[i].co.x - 100, curr[i].co.y, Tree::LEFT));
				} else if (curr[i].po == Tree::LEFT) {
					v.push_back(Tree(curr[i].co.x - 100, curr[i].co.y, Tree::LEFT));
				}
			}

			for (int i = 0; i < curr.size(); i++) {
				done.push_back(curr[i]);
			}
			curr.clear();
			for (int i = 0; i < v.size(); i++) {
				curr.push_back(v[i]);
			}
		}
		cout << seeNum << endl;
	}
	return 0;
}

////用于存储坐标的结构体
//struct POINT {
//	int x;
//	int y;
//};
////主函数
//int main(void) {
//	//dRad为180/pi，用于弧度到角度的转换，
//	const float fRad = 57.295779513082320876798154814105f;
//	//dMax为cos(0.01)，任何大于此值的参数都不能进行acos
//	const float fMax = 0.99999998476912904932780850903444f;
//	//循环处理每一组输入的数据，d为直径，x和y为观查者坐标
//	for (float d, x, y; cin >> d >> x >> y && d != 0;) {
//		//将所有值放大100倍并取整，一可加快运算，二可保证精度
//		POINT Eye = { int(x * 100 + 0.5), int(y * 100 + 0.5) };
//		int nDiam = (int) (d * 100 + 0.5), nCnt = 0;
//		//依次由里圈向外层层遍例每棵树，检查是否被里面的树遮挡
//		for (int iBeg = 0, iEnd = 100; iEnd <= 1000; iBeg -= 100, iEnd += 100) {
//			//遍例外面这一圈的树
//			for (int i = 0; i < iEnd - iBeg; i += 100) {
//				POINT Out[4] = {//一圈分别为左边、上边
//						{ iBeg, iBeg + i }, { iBeg + i, iEnd },
//						//右边和下边
//								{ iEnd, iEnd - i }, { iEnd - i, iBeg } };
//				//遍例四条边上的树
//				for (int j = 0; j < 4; j++) {
//					//遍例圈里面所有的树，In为树的坐标
//					POINT In = { iBeg + 100, iBeg + 100 };
//					for (; In.y <= iEnd - 100; In.y += 100) {
//						for (In.x = iBeg + 100; In.x <= iEnd - 100; In.x += 100) {//以下算法判定两棵树是否遮挡
//							//分别建立里面树和处面树与眼睛坐标的向量
//							POINT NVec = { In.x - Eye.x, In.y - Eye.y };
//							POINT FVec = { Out[j].x - Eye.x, Out[j].y - Eye.y };
//							//两个向量求内积
//							int nProd = NVec.x * FVec.x + NVec.y * FVec.y;
//							//求两个向量的模
//							float fNMod = sqrt((float) (NVec.x * NVec.x + NVec.y * NVec.y));
//							float fFMod = sqrt((float) (FVec.x * FVec.x + FVec.y * FVec.y));
//							//内积公式求夹角
//							float fACOS = nProd / (fNMod * fFMod);
//							if (fACOS >= fMax) { //夹角不能大于cos(0.01)
//								break;
//							}
//							//求出夹角角度
//							float fAng = acos(fACOS) * fRad;
//							//分别计算两棵树干自身与眼睛形成的的夹角
//							fNMod = asin((float) nDiam / 2.0f / fNMod) * fRad;
//							fFMod = asin((float) nDiam / 2.0f / fFMod) * fRad;
//							//判断是否遮挡，如果有则跳出循环
//							if (fAng - fNMod - fFMod <= 0.01f) {
//								break;
//							}
//						}
//						//未完成内循环，说明存在遮挡，继续向外跳出
//						if (In.x <= iEnd - 100) {
//							break;
//						}
//					}
//					//累计可见树的个数
//					nCnt += (In.y > iEnd - 100);
//				}
//			}
//		}
//		//输出结果
//		cout << nCnt << endl;
//	}
//	return 0;
//}
