#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

/*struct student{
	char name[32];
	int age;
	int classid;
	bool sex;
};

bool cmpEql(student a, student b){
	return a.age == b.age;
}

bool cmpEqlname(student a, student b){
	return strcmp(a.name, b.name) ? false : true;
}

bool cmpEqlSex(student a, student b){
	return ! (a.sex ^ b.sex);
}

int countS(student *st, int n, student value, bool(*cmp)(student, student)){
	int i;
	int count = 0;
	for (i = 0; i < n; i++){
		if (cmp(st[i], value)){
			count++;
		}
	}
	return count;
}

	
int main(){

	student st[] = { { "caixukun", 18, 1, true }, 
	                 { "qiaobiluo", 18, 1, false }, 
	                 { "wuyifan", 20, 2, true }, 
	                 { "luhan", 22, 2, true }, 
	                 { "lubenwei", 22, 2, true },
	                 { "caixukun", 18, 1, true }, 
	                 {"yangchaoyue",18,2,false} };

	student test = { "caixukun", 18, 1, true };

	cout << countS(st, 7, test,cmpEqlSex) << endl;

	system("pause");
	return 0;
}*/

enum{
	SPADES,//黑桃
	HEARTS,//红桃
	CLUBS,//梅花
	DIAMONDS,//方片
	JOKER,//大小王
};

//全局变量g_,局部静态变量s_,成员变量m_；

class Poker{
	unsigned char m_type;
	int m_point;
public :
	void makePoker(int type, int point){
		m_type = type;
		m_point = point;
		if (m_type == JOKER){
			m_point += 13;
		}
	}

	void outputpoker(){
		char * type[5] = { "黑桃", "红桃", "梅花", "方片", "" };
		char * point[16] = { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "小王", "大王" };

		printf("%s%s", type[m_type], point[m_point]);
	}

	bool cmppoker(Poker tmp){
		return (m_point < tmp.m_point) ||
			(m_point == tmp.m_point && m_type > tmp.m_point);
	}

	bool isEff(){
		if (m_type == JOKER && (m_point == 14 || m_point == 15)){
			return true;
		}

		if ((unsigned char)m_type > 3 || (unsigned int)m_point - 1 > 13){
			return false;
		}
		return true;
	}
};

class Player{
	Poker m_HandCard[18];
	int m_size;
public:
	Player() :m_size(0){

	}

	void getCard(Poker newCard){
		//Poker tmp = newCard;

		int i;
		for (i = m_size; i > 0 && m_HandCard[i - 1].cmppoker(newCard); i--){
			m_HandCard[i] = m_HandCard[i - 1];
		}

		m_HandCard[i] = newCard;
		m_size++;
	}
	void showCard(){
		for (auto &i : m_HandCard){
			i.outputpoker();
			putchar(' ');
		}
		putchar('\n');
	}



};

//int main(){
//
//	srand((unsigned)time(NULL));
//	Player p1;
//	Poker tmp;
//
//	int i;
//	for (i = 0; i < 18; i++){
//		tmp.makePoker(rand() % 4, rand() % 13 + 1);
//		p1.getCard(tmp);
//	}
//
//	p1.showCard();
//
//	system("pause");
//	return 0;
//}

int randnum(Poker * cardHeap){
	int tmp = rand() % 54;
	while (1){
		if (cardHeap[tmp].isEff()){
			
			return tmp;
		}
		else{
			tmp++;
			if (tmp == 54){
				tmp = 0;
			}
		}
		
	}

}

int main(){

	Poker tmp[54];
	int j = 0;
	Player ayi;
	Player laoye;
	Player miao17;


	for (auto &i : tmp){
		i.makePoker(j / 13, j % 13 + 1);
		j++;
	}
	srand((unsigned)time(NULL));

	int delcard;

	int i;
	for (i = 0; i < 18; i++){
		delcard = randnum(tmp);
		ayi.getCard(tmp[delcard]); 
		tmp[delcard].makePoker(-1, -1);

		delcard = randnum(tmp);
		laoye.getCard(tmp[delcard]);
		tmp[delcard].makePoker(-1, -1);

		delcard = randnum(tmp);
		miao17.getCard(tmp[delcard]);
		tmp[delcard].makePoker(-1, -1);

	}
	ayi.showCard();
	laoye.showCard();
	miao17.showCard();


	system("pause");
	return 0;
}