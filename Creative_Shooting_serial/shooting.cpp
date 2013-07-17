#include <math.h>
#include "DxLib.h"
#include "resource.h"
#include "define.h"
#include "prototype.h"
#include "dataload.h"


// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey()
{
  char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
  GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
  for( int i=0; i<256; i++ ){ 
    if( tmpKey[i] != 0 ){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            Key[i]++;     // ���Z
    } else {              // ������Ă��Ȃ����
            Key[i] = 0;   // 0�ɂ���
    }
  }
  return 0;
}

//���@���i�[�p�\����
typedef struct{
	double x, y; //�ʒu���
	int hp, flg, Damageflg;
}PLEYER;

PLEYER Player;

//�G�@���i�[�p�\����
typedef struct{
	double x, y;//�ʒu���
	int hp, flag;
}ENEMY;

ENEMY Enemy,Enemy_1,Enemy_2,Enemy_3,Enemy_4,Enemy_5;

//���@�e�ۏ��i�[�p�\����
typedef struct{ 
	double x, y; //�v���C���[�e�ۂ̈ʒu
	double vx,vy;
	int Flag;     //�v���C���[�e�ۃt���O
}PBULLET;

PBULLET pBullet[PBULLET_X][PBULLET_Y],pBullet_1[PBULLET_X][PBULLET_Y],pBullet_2[PBULLET_X][PBULLET_Y];

//�G�@�e�ۗp���i�[�p�\����
typedef struct{
	double x, y; //�G�e�ۂ̈ʒu
	int Flag; //�G�e�ۃt���O
	double vx,vy;//�e���x
}EBULLET;

EBULLET eBullet[PBULLET_X][PBULLET_Y],eBullet_2[PBULLET_X][PBULLET_Y],eBullet_3[PBULLET_X][PBULLET_Y],eBullet_4[PBULLET_X][PBULLET_Y],eBullet_5[PBULLET_X][PBULLET_Y];
EBULLET eBullet_6[PBULLET_X][PBULLET_Y],eBullet_7[PBULLET_X][PBULLET_Y];

typedef struct{
	int x,y;
	char name[128];
}Menu_t;

typedef struct{
	int x,y,flag;
}ITEM;

ITEM Item1;

//�e�\���̏��̏�����
void Position()
{
	int i;
	Player.x = (WNDW-130)/2;
	Player.y = WNDH-30;
	Player.hp = 5;
	Player.Damageflg=0;
	Enemy.flag=0;
	Enemy_1.flag=0;
	Enemy_2.flag=0;
	Enemy_3.flag=0;
	Enemy_4.flag=0;
	Enemy_5.flag=0;
	Item1.flag=0;

	SelectNum=0;
	CSelctNum = 0;
	Score = 0;
	stageflg=0;
	Mflg=0;
	Cflg=0;
	Iflg=0;
	counter=0;

	RemainingTime=15;
	StageTime=0;
	StopTime=0; //�^�C�����Ă������v����
	Stage1RemainingTime=0; //�X�e�[�W�N���A�ɂ�����������
	Stage2RemainingTime=0;

	//�e�ۃt���O�̏�����
	for(i=0;i<PBULLET_Y;i++){
		pBullet[0][i].x=0;
		pBullet[0][i].y=0;
		pBullet_1[0][i].x=0;
		pBullet_1[0][i].y=0;
		pBullet_1[0][i].vx=0;
		pBullet_1[0][i].vy=0;
		pBullet_2[0][i].x=0;
		pBullet_2[0][i].y=0;
		pBullet_2[0][i].vx=0;
		pBullet_2[0][i].vy=0;
		pBullet[0][i].Flag = 0;
		pBullet_1[0][i].Flag = 0;
		pBullet_2[0][i].Flag = 0;
		eBullet[0][i].Flag = 0;
		eBullet[0][i].x=0;
		eBullet[0][i].y=0;
		eBullet[0][i].vx=0;
		eBullet[0][i].vy=0;
		eBullet_2[0][i].Flag = 0;
		eBullet_2[0][i].x=0;
		eBullet_2[0][i].y=0;
		eBullet_2[0][i].vx=0;
		eBullet_2[0][i].vy=0;
		eBullet_3[0][i].Flag = 0;
		eBullet_3[0][i].x=0;
		eBullet_3[0][i].y=0;
		eBullet_3[0][i].vx=0;
		eBullet_3[0][i].vy=0;
		eBullet_4[0][i].Flag = 0;
		eBullet_4[0][i].x=0;
		eBullet_4[0][i].y=0;
		eBullet_4[0][i].vx=0;
		eBullet_4[0][i].vy=0;
		eBullet_5[0][i].Flag = 0;
		eBullet_5[0][i].x=0;
		eBullet_5[0][i].y=0;
		eBullet_5[0][i].vx=0;
		eBullet_5[0][i].vy=0;
		eBullet_6[0][i].Flag = 0;
		eBullet_6[0][i].x=0;
		eBullet_6[0][i].y=0;
		eBullet_6[0][i].vx=0;
		eBullet_6[0][i].vy=0;
		eBullet_7[0][i].Flag = 0;
		eBullet_7[0][i].x=0;
		eBullet_7[0][i].y=0;
		eBullet_7[0][i].vx=0;
		eBullet_7[0][i].vy=0;
	}
	return;
}

//���@�̑���
void PlayerControl()
{
	int j;
	static int eflg=0, i=0, dTime=0;

	//�v�Z�t�F�[�Y
	if(Player.hp > 0){ //���@�������Ă���Ƃ��̓L�[���͂𖳌�
		if(Player.flg>=1){
			Player.flg=0;
		}
		
		//�o��
		if( Key[ KEY_INPUT_RIGHT ] >= 1 && Player.x < (WNDW-130)-30 ){ // �E�{�^���������ꂽ���E�ֈړ��@��Player.x < 750 �͉�ʊO�ɏo�Ȃ����߂̏���
			Player.x += 6;
			if( Key[ KEY_INPUT_LSHIFT ] >= 1) Player.x -=3 ; //Shift�L�[�ŃX���[�R�}���h
		}
		if( Key[ KEY_INPUT_LEFT  ] >= 1/*strcmp(In, "NO\n")*/ && Player.x > 0){
			Player.x -= 6;
			if( Key[ KEY_INPUT_LSHIFT ] >= 1) Player.x += 3;
		}
		if( Key[ KEY_INPUT_DOWN  ] >= 1 && Player.y < WNDH-30){	//�ȉ����l�̏���
			Player.y += 6;
			if( Key[ KEY_INPUT_LSHIFT ] >= 1) Player.y -= 3;
		}
		if( Key[ KEY_INPUT_UP    ] >= 1 &&  Player.y > 30){
			Player.y -= 6;
			if( Key[ KEY_INPUT_LSHIFT ] >= 1) Player.y += 3;
		}
		if(Item1.x+10 >= Player.x-10 && Item1.x-10 <= Player.x+10 && Item1.y+10 >= Player.y-10 && Item1.y-10 < Player.y+10 && Iflg<=0 && Item1.flag>=1){
			Player.hp++;
			Player.Damageflg=1;
			Iflg=1;
		}
		//�G�̖{�̂ɓ��������玩�@�̂g�o�����炷
		if(Player.Damageflg<=0){
			dTime = GetNowCount(); //�v���C���[���_���[�W���󂯂����Ԃ̎擾
			if(Enemy.x+10 >= Player.x-10 && Enemy.x-10 <= Player.x+10 && Enemy.y+10 >= Player.y-10 && Enemy.y-10 < Player.y+10 && Enemy.hp>0){
				eflg=1;
				Player.hp--;
				Player.Damageflg=1;
			}
			if(Enemy_1.x+10 >= Player.x-10 && Enemy_1.x-10 <= Player.x+10 && Enemy_1.y+10 >= Player.y-10 && Enemy_1.y-10 < Player.y+10 && Enemy_1.hp>0){
				eflg=1;
				Player.hp--;
				Player.Damageflg=1;
			}
			if(Enemy_2.x+10 >= Player.x-10 && Enemy_2.x-10 <= Player.x+10 && Enemy_2.y+10 >= Player.y-10 && Enemy_2.y-10 < Player.y+10 && Enemy_2.hp>0){
				eflg=1;
				Player.hp--;
				Player.Damageflg=1;
			}
			if(Enemy_4.x+10 >= Player.x-10 && Enemy_4.x-10 <= Player.x+10 && Enemy_4.y+10 >= Player.y-10 && Enemy_4.y-10 < Player.y+10 && Enemy_4.hp>0){
				eflg=1;
				Player.hp--;
				Player.Damageflg=1;
			}
			if(Enemy_5.x+10 >= Player.x-10 && Enemy_5.x-10 <= Player.x+10 && Enemy_5.y+10 >= Player.y-10 && Enemy_5.y-10 < Player.y+10 && Enemy_5.hp>0){
				eflg=1;
				Player.hp--;
				Player.Damageflg=1;
			}
			//�G�e�ۂɔ�e������g�o����
			for(j=0; j<PBULLET_Y; j++){
				if(eBullet[0][j].x+5 > Player.x-5 && eBullet[0][j].x-5 < Player.x+5 && eBullet[0][j].y+5 > Player.y-5 && eBullet[0][j].y-5 < Player.y+5 && Enemy.hp>0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;;
					break;//�����Ń��[�v�𔲂��Ȃ��ƈ��̔�e�Ŏ��S
				}else if(eBullet_2[0][j].x+5 > Player.x-5 && eBullet_2[0][j].x-5 < Player.x+5 && eBullet_2[0][j].y+5 > Player.y-5 && eBullet_2[0][j].y-5 < Player.y+5 && Enemy_2.hp > 0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;
					break;
				}else if(eBullet_4[0][j].x+5 > Player.x-5 && eBullet_4[0][j].x-5 < Player.x+5 && eBullet_4[0][j].y+5 > Player.y-5 && eBullet_4[0][j].y-5 < Player.y+5 && Enemy_4.hp > 0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;
					break;
				}else if(eBullet_5[0][j].x+5 > Player.x-5 && eBullet_5[0][j].x-5 < Player.x+5 && eBullet_5[0][j].y+5 > Player.y-5 && eBullet_5[0][j].y-5 < Player.y+5 && Enemy_5.hp > 0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;
					break;
				}else if(eBullet_6[0][j].x+5 > Player.x-5 && eBullet_6[0][j].x-5 < Player.x+5 && eBullet_6[0][j].y+5 > Player.y-5 && eBullet_6[0][j].y-5 < Player.y+5 && Enemy_5.hp > 0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;
					break;
				}else if(eBullet_7[0][j].x+5 > Player.x-5 && eBullet_7[0][j].x-5 < Player.x+5 && eBullet_7[0][j].y+5 > Player.y-5 && eBullet_7[0][j].y-5 < Player.y+5 && Enemy_5.hp > 0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;
					break;
				}
			}
		}//if(Player.Damageflg<=0)
	}//if(Player.hp > 0)

	if(eflg>=1){
		DrawRotaGraph( (int)Player.x, (int)Player.y-60, 2.5, 0.0, Effect[i], TRUE ); //��e�G�t�F�N�g
		i++;
		if(i>=6){
			i=0;
			eflg=0;//��e�G�t�F�N�g�t���O��܂�
		}
	}
	//�_���[�W���󂯂Ă��疳�G���Ԃ�3�b�ȏ㑱���������
	if(Player.Damageflg>=1 && GetNowCount()-dTime >= 2*1e3){
		Player.Damageflg=0;
	}
	//HP���O�ɂȂ�������W�������ʒu��
	if(Player.hp == 0){
		Player.x = (WNDW-130)/2;
		Player.y = WNDH-30;
		Player.Damageflg=0;
	}
	//�`��t�F�[�Y
	if(Player.hp>0){
		if(Player.Damageflg>=1){//�_���[�W��̖��G��Ԃ̕`��
			SetDrawBlendMode( DX_BLENDMODE_ALPHA,  128 );
			DrawRotaGraph( (int)Player.x, (int)Player.y, 1.0, 0.0, hPlayer, TRUE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND,  0 );
		}else if(Player.Damageflg<=0){
			DrawRotaGraph( (int)Player.x, (int)Player.y, 1.0, 0.0, hPlayer, TRUE );
		}
	}
	return;
}

//���@�e�ې���
void pBulletControl()
{
	int j;
	static int cn=0;

	DrawFormatString(670,500,RGB(0,0,255),"In=%s", In);

	if( (strcmp(In, "1") == 0) ) {
		cn++;
		//if(cn % 5 == 0)
			Key[ KEY_INPUT_Z ] = 1;
	}

	if(Key[ KEY_INPUT_Z	] == 1 && Player.hp>0){ //Z�L�[�������ꂩ�AHP���c���Ă�����
		PlaySoundMem(EffectMusic, DX_PLAYTYPE_BACK); //���ʉ�
		for(j=0; j<PBULLET_Y; j++){
			if(pBullet[0][j].Flag == 0){
					pBullet[0][j].Flag = 1;			//�t���O�𗧂Ă�
					pBullet[0][j].x = Player.x; // ���@�̏ꏊ�ƒe�̏o��ʒu�𓯊�
					pBullet[0][j].y = Player.y;
					break;
			}
		}
	}
	for(j=0; j<PBULLET_Y; j++){
		if(pBullet[0][j].Flag == 1){
			pBullet[0][j].y -= 10; //�e�ۂ��ړ�������
			if(pBullet[0][j].y < 0){	
				pBullet[0][j].Flag = 0;	//��ʊO�ɒe�ۂ��o����t���O��܂�
			}
		}
	}
	//�X�R�A�ɉ����Ď��@�e�ۂ̒ǉ�
	if((ScoreShow() >= 7000) && Key[ KEY_INPUT_Z] == 1 && Player.hp>0){
		PlaySoundMem(EffectMusic, DX_PLAYTYPE_BACK); //���ʉ�
		for(j=0; j<PBULLET_Y; j++){
			if(pBullet_1[0][j].Flag == 0){
				pBullet_1[0][j].Flag = 1;
				pBullet_1[0][j].vx = 5;
				pBullet_1[0][j].vy = -10;
				pBullet_1[0][j].x = Player.x;
				pBullet_1[0][j].y = Player.y;
			}
			if(pBullet_2[0][j].Flag == 0){
				pBullet_2[0][j].Flag = 1;
				pBullet_2[0][j].vx = -5;
				pBullet_2[0][j].vy = -10;
				pBullet_2[0][j].x = Player.x;
				pBullet_2[0][j].y = Player.y;
				break;
			}
		}
	}
	for(j=0; j<PBULLET_Y; j++){
		if(pBullet_1[0][j].Flag == 1){
			pBullet_1[0][j].x += pBullet_1[0][j].vx;
			pBullet_1[0][j].y += pBullet_1[0][j].vy;
			if(pBullet_1[0][j].x >= WNDW-130 || pBullet_1[0][j].y <=0){
				pBullet_1[0][j].Flag = 0;
			}
		}
		if(pBullet_2[0][j].Flag == 1){
			pBullet_2[0][j].x += pBullet_2[0][j].vx;
			pBullet_2[0][j].y += pBullet_2[0][j].vy;
			if(pBullet_2[0][j].x <= 0 || pBullet_2[0][j].y <=0){
				pBullet_2[0][j].Flag = 0;
			}
		}
		if(Player.hp <= 0){
			pBullet[0][j].x = 0;
			pBullet_1[0][j].x = 0;
			pBullet_2[0][j].x = 0;
			pBullet[0][j].y = 10000;
			pBullet_1[0][j].y = 10000;
			pBullet_2[0][j].y = 10000;
		}
	}
	
	return;
}

//���@�e�ە`��
void pBulletDraw()
{
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(pBullet[0][j].Flag == 1){
			DrawRotaGraph((int)pBullet[0][j].x, (int)pBullet[0][j].y, 0.5, 0.0, hpBullet[0], TRUE, 0);	
			
		}
		if(pBullet_1[0][j].Flag == 1){
			DrawRotaGraph((int)pBullet_1[0][j].x, (int)pBullet_1[0][j].y, 0.5, 0.0, hpBullet[0], TRUE, 0);
		}
		if(pBullet_2[0][j].Flag == 1){
			DrawRotaGraph((int)pBullet_2[0][j].x, (int)pBullet_2[0][j].y, 0.5, 0.0, hpBullet[0], TRUE, 0);
		}
	}
	return;
}

//�G�@����
void EnemyControl()
{
	int j, flg=0, flg2=1;
	static int i=0 ,eflg=0, dflg=0, x=0, y=0, k=0;

	//�v�Z�t�F�[�Y
	if(Enemy.hp > 0 && Enemy.flag > 0){
		Enemy.x =  ((WNDW-130))/2 - ((WNDW-130)-77)/2*sin(PI / 120 * counter);
		for(j=0; j<PBULLET_Y; j++){
			if(Enemy.y>=10){
				//�G�@�Ɏ��@�e�ۂ�����������G�@HP�����炷
				if(Enemy.x+10 > pBullet[0][j].x-10 && Enemy.x-10 < pBullet[0][j].x+10 && Enemy.y+5 > pBullet[0][j].y-5 && Enemy.y-5 < pBullet[0][j].y+5){
					Enemy.hp--;
					eflg=1;//��e�G�t�F�N�g�t���O
					if(Enemy.hp <= 0 && Enemy.flag){
						dflg=1;
						x=(int)Enemy.x;
						y=(int)Enemy.y;
						Enemy.flag = 0;
						Enemy.hp = -1;
						Enemy.x = 0;
						Enemy.y = 0;
						eflg=0;
						i=0;
					}
					break;	//��x�_���[�W���󂯂��烋�[�v�𔲂���
				}
				if(Enemy.x+10 > pBullet_1[0][j].x-10 && Enemy.x-10 < pBullet_1[0][j].x+10 && Enemy.y+5 > pBullet_1[0][j].y-5 && Enemy.y-5 < pBullet_1[0][j].y+5){
					Enemy.hp--;
					eflg=1;//��e�G�t�F�N�g�t���O
					if(Enemy.hp <= 0 && Enemy.flag){
						dflg=1;
						x=(int)Enemy.x;
						y=(int)Enemy.y;
						Enemy.flag = 0;
						Enemy.hp = -1;
						Enemy.x = 0;
						Enemy.y = 0;
						eflg=0;
						i=0;
					}
					break;	//��x�_���[�W���󂯂��烋�[�v�𔲂���
				}
				if(Enemy.x+10 > pBullet_2[0][j].x-10 && Enemy.x-10 < pBullet_2[0][j].x+10 && Enemy.y+5 > pBullet_2[0][j].y-5 && Enemy.y-5 < pBullet_2[0][j].y+5){
					Enemy.hp--;
					eflg=1;//��e�G�t�F�N�g�t���O
					if(Enemy.hp <= 0 && Enemy.flag){
						dflg=1;
						x=(int)Enemy.x;
						y=(int)Enemy.y;
						Enemy.flag = 0;
						Enemy.hp = -1;
						Enemy.x = 0;
						Enemy.y = 0;
						eflg=0;
						i=0;
					}
					break;	//��x�_���[�W���󂯂��烋�[�v�𔲂���
				}
			}
		}
		if(eflg>=1 /*&& Enemy.x>0 && Enemy.y>0*/){
			DrawRotaGraph( (int)Enemy.x, (int)Enemy.y+60, 2.5, 0.0, Effect[i], TRUE ); //��e�G�t�F�N�g
			i++;
			if(i>=6){
				i=0;
				eflg=0;//��e�G�t�F�N�g�t���O��܂�
			}
		}
		if(dflg>=1 /*&& Enemy.flag<=0*/){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //���ŃG�t�F�N�g
			}
			dflg=0;
			/*k++;
			if(k>=6){
				k=0;
				dflg=0;//��e�G�t�F�N�g�t���O��܂�
			}*/
		}
	}
	
	//�G�@�`��
	if(Enemy.flag){//�G�@��HP���c���Ă�����`��@Enemy.x�̗����̓f�o�b�O�p
		DrawRotaGraph( (int)Enemy.x, (int)Enemy.y, 1.2, 0.0, hEnemy, TRUE );
	}
	/*if(Enemy.flag<=0){
		Enemy.x=0;
		Enemy.y=0;
	}*/
 
	return;
}

//�G���G����()
void EnemyControl_1(){
	int flag=0,i;
	static int eflg=0, dflg=0, j=0, k=0, x, y;

	if(Enemy_1.hp > 0 && Enemy_1.flag){
		Enemy_1.x = (WNDW-130)/2+300*sin(PI/200*counter);
		Enemy_1.y += 1;
		for(i = 0;i<PBULLET_Y;i++){
			if(Enemy_1.y>=10){
				if(Enemy_1.x+20 > pBullet[0][i].x-10 && Enemy_1.x-20 < pBullet[0][i].x+10 && Enemy_1.y+15 > pBullet[0][i].y-15 && Enemy_1.y-5< pBullet[0][i].y+5){
					Enemy_1.hp--;
					if(Enemy_1.hp <= 0){
						dflg=1;
						x=(int)Enemy_1.x;
						y=(int)Enemy_1.y;
						Enemy_1.flag = 0;
						Enemy_1.hp = -1;
						Enemy_1.x = 0;
						Enemy_1.y = 0;
						eflg=0;
						j=0;
					}
					eflg=1;
					break;
				}
				if(Enemy_1.x+20 > pBullet_1[0][i].x-10 && Enemy_1.x-20 < pBullet_1[0][i].x+10 && Enemy_1.y+15 > pBullet_1[0][i].y-15 && Enemy_1.y-5< pBullet_1[0][i].y+5){
					Enemy_1.hp--;
					if(Enemy_1.hp <= 0){
						dflg=1;
						x=(int)Enemy_1.x;
						y=(int)Enemy_1.y;
						Enemy_1.flag = 0;
						Enemy_1.hp = -1;
						Enemy_1.x = 0;
						Enemy_1.y = 0;
						eflg=0;
						j=0;
					}
					eflg=1;
					break;
				}
				if(Enemy_1.x+20 > pBullet_2[0][i].x-10 && Enemy_1.x-20 < pBullet_2[0][i].x+10 && Enemy_1.y+15 > pBullet_2[0][i].y-15 && Enemy_1.y-5< pBullet_2[0][i].y+5){
					Enemy_1.hp--;
					if(Enemy_1.hp <= 0){
						dflg=1;
						x=(int)Enemy_1.x;
						y=(int)Enemy_1.y;
						Enemy_1.flag = 0;
						Enemy_1.hp = -1;
						Enemy_1.x = 0;
						Enemy_1.y = 0;
						eflg=0;
						j=0;
					}
					eflg=1;
					break;
				}
			}
			if(Enemy_1.flag){
				DrawRotaGraph( (int)Enemy_1.x, (int)Enemy_1.y, 0.25, 0.0, hEnemy_1, TRUE );
			}
		}

		if(Enemy_1.y > WNDH){
			Enemy_1.y = 20;
		}
		if(eflg>=1){
			DrawRotaGraph( (int)Enemy_1.x, (int)Enemy_1.y+60, 2.5, 0.0, /*hEnemy_4*/Effect[j], TRUE ); //��e�G�t�F�N�g
			j++;
			if(j>=6){
				j=0;
				eflg=0;//��e�G�t�F�N�g�t���O��܂�
			}
		}
	}
	return;
}

void EnemyControl_2(){
	int flag=0,i;
	static int eflg=0, dflg=0, j=0, k=0, x, y;

	if(Enemy_2.hp > 0 && Enemy_2.flag){
		if(Enemy_2.y <= 200){
			Enemy_2.x = 200;
			Enemy_2.y += 5;
		}
		for(i = 0;i<PBULLET_Y;i++){
			if(Enemy_2.x+20 > pBullet[0][i].x-10 && Enemy_2.x-20 < pBullet[0][i].x+10 && Enemy_2.y+15 > pBullet[0][i].y-15 && Enemy_2.y-5< pBullet[0][i].y+5){
				Enemy_2.hp--;
				if(Enemy_2.hp <= 0 && Enemy_2.flag == 1){
					dflg=1;
					x=(int)Enemy_2.x;
					y=(int)Enemy_2.y;
					Enemy_2.flag = 0;
					Enemy_2.hp = -1; //�X�R�A���Z��̍l��
					Enemy_2.x = 0;
					Enemy_2.y = 0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}
			if(Enemy_2.x+20 > pBullet_1[0][i].x-10 && Enemy_2.x-20 < pBullet_1[0][i].x+10 && Enemy_2.y+15 > pBullet_1[0][i].y-15 && Enemy_2.y-5< pBullet_1[0][i].y+5){
				Enemy_2.hp--;
				if(Enemy_2.hp <= 0 && Enemy_2.flag == 1){
					dflg=1;
					x=(int)Enemy_2.x;
					y=(int)Enemy_2.y;
					Enemy_2.flag = 0;
					Enemy_2.hp = -1; //�X�R�A���Z��̍l��
					Enemy_2.x = 0;
					Enemy_2.y = 0;
					eflg=0;
					j=0;;
				}
				eflg=1;
				break;
			}
			if(Enemy_2.x+20 > pBullet_2[0][i].x-10 && Enemy_2.x-20 < pBullet_2[0][i].x+10 && Enemy_2.y+15 > pBullet_1[0][i].y-15 && Enemy_2.y-5< pBullet_2[0][i].y+5){
				Enemy_2.hp--;
				if(Enemy_2.hp <= 0 && Enemy_2.flag == 1){
					dflg=1;
					x=(int)Enemy_2.x;
					y=(int)Enemy_2.y;
					Enemy_2.flag = 0;
					Enemy_2.hp = -1; //�X�R�A���Z��̍l��
					Enemy_2.x = 0;
					Enemy_2.y = 0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}

			if(Enemy_2.flag){
				DrawRotaGraph( (int)Enemy_2.x, (int)Enemy_2.y, 1.0, 0.0, hEnemy_2, TRUE );
			}
		}
		if(eflg>=1 && Enemy_2.x!=0 && Enemy_2.y!=0){
			DrawRotaGraph( (int)Enemy_2.x, (int)Enemy_2.y+60, 2.5, 0.0, Effect[j], TRUE ); //��e�G�t�F�N�g
			j++;
			if(j>=6){
				j=0;
				eflg=0;//��e�G�t�F�N�g�t���O��܂�
			}
		}
		if(dflg>=1){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //���ŃG�t�F�N�g
			}
			dflg=0;
		}
	}
	return;
}

void EnemyControl_3(){
	int flag=0,i;
	static int eflg=0, dflg=0, j=0, k=0, x, y;

	if(Enemy_4.hp > 0 && Enemy_4.flag){
		if(Enemy_4.y <= 200){
			Enemy_4.y += 5;
		}
		for(i = 0;i<PBULLET_Y;i++){
			if(Enemy_4.x+20 > pBullet[0][i].x-10 && Enemy_4.x-20 < pBullet[0][i].x+10 && Enemy_4.y+15 > pBullet[0][i].y-15 && Enemy_4.y-5< pBullet[0][i].y+5){
				Enemy_4.hp--;
				if(Enemy_4.hp <= 0 && Enemy_4.flag == 1){
					dflg=1;
					x=(int)Enemy_4.x;
					y=(int)Enemy_4.y;
					Enemy_4.flag = 0;
					Enemy_4.hp = -1;
					Enemy_4.x = 0;
					Enemy_4.y =0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}
			if(Enemy_4.x+20 > pBullet_1[0][i].x-10 && Enemy_4.x-20 < pBullet_1[0][i].x+10 && Enemy_4.y+15 > pBullet_1[0][i].y-15 && Enemy_4.y-5< pBullet_1[0][i].y+5){
				Enemy_4.hp--;
				if(Enemy_4.hp <= 0 && Enemy_4.flag == 1){
					dflg=1;
					x=(int)Enemy_4.x;
					y=(int)Enemy_4.y;
					Enemy_4.flag = 0;
					Enemy_4.hp = -1;
					Enemy_4.x = 0;
					Enemy_4.y =0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}
			if(Enemy_4.x+20 > pBullet_2[0][i].x-10 && Enemy_4.x-20 < pBullet_2[0][i].x+10 && Enemy_4.y+15 > pBullet_2[0][i].y-15 && Enemy_4.y-5< pBullet_2[0][i].y+5){
				Enemy_4.hp--;
				if(Enemy_4.hp <= 0 && Enemy_4.flag == 1){
					dflg=1;
					x=(int)Enemy_4.x;
					y=(int)Enemy_4.y;
					Enemy_4.flag = 0;
					Enemy_4.hp = -1;
					Enemy_4.x = 0;
					Enemy_4.y =0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}
			if(Enemy_4.flag){
				DrawRotaGraph( (int)Enemy_4.x, (int)Enemy_4.y, 1.0, 0.0, hEnemy_4, TRUE );
			}
		}
		if(eflg>=1 && Enemy_4.x!=0 && Enemy_4.y!=0){
			DrawRotaGraph( (int)Enemy_4.x, (int)Enemy_4.y+60, 2.5, 0.0, Effect[j], TRUE ); //��e�G�t�F�N�g
			j++;
			if(j>=6){
				j=0;
				eflg=0;//��e�G�t�F�N�g�t���O��܂�
			}
		}
		if(dflg>=1){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //���ŃG�t�F�N�g
			}
			dflg=0;
		}
	}
	return;
}

//Boss
void EnemyControl_4(){
	int flag=0,i;
	static int eflg=0, dflg=0, j=0, k=0, x, y;

	if(Enemy_5.hp > 0 && Enemy_5.flag){
		if(Enemy_5.y <= 200){
			Enemy_5.x = 250;
			Enemy_5.y += 5;
		}
		for(i = 0;i<PBULLET_Y;i++){
			if(Enemy_5.y >= 200 && Enemy_5.flag){
				Enemy_5.x = ((WNDW-130))/2 - ((WNDW-130)-77)/2*sin(PI / 120 * counter);
			}
			if(Enemy_5.x+20 > pBullet[0][i].x-10 && Enemy_5.x-20 < pBullet[0][i].x+10 && Enemy_5.y+15 > pBullet[0][i].y-15 && Enemy_5.y-5< pBullet[0][i].y+5){
				Enemy_5.hp--;
				if(Enemy_5.hp <= 0 && Enemy_5.flag ){
					dflg=1;
					x=(int)Enemy_5.x;
					y=(int)Enemy_5.y;
					Enemy_5.flag = 0;
					Enemy_5.hp = -1;
					Enemy_5.x = 0;
					Enemy_5.y = 0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}
			if(Enemy_5.x+20 > pBullet_1[0][i].x-10 && Enemy_5.x-20 < pBullet_1[0][i].x+10 && Enemy_5.y+15 > pBullet_1[0][i].y-15 && Enemy_5.y-5< pBullet_1[0][i].y+5){
				Enemy_5.hp--;
				if(Enemy_5.hp <= 0 && Enemy_5.flag ){
					dflg=1;
					x=(int)Enemy_5.x;
					y=(int)Enemy_5.y;
					Enemy_5.flag = 0;
					Enemy_5.hp = -1;
					Enemy_5.x = 0;
					Enemy_5.y = 0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}
			if(Enemy_5.x+20 > pBullet_2[0][i].x-10 && Enemy_5.x-20 < pBullet_2[0][i].x+10 && Enemy_5.y+15 > pBullet_2[0][i].y-15 && Enemy_5.y-5< pBullet_2[0][i].y+5){
				Enemy_5.hp--;
				if(Enemy_5.hp <= 0 && Enemy_5.flag ){
					dflg=1;
					x=(int)Enemy_5.x;
					y=(int)Enemy_5.y;
					Enemy_5.flag = 0;
					Enemy_5.hp = -1;
					Enemy_5.x = 0;
					Enemy_5.y = 0;
					eflg=0;
					j=0;
				}
				eflg=1;
				break;
			}

			if(Enemy_5.flag){
				DrawRotaGraph( (int)Enemy_5.x, (int)Enemy_5.y, 1.0, 0.0, hEnemy_5, TRUE );
			}
		}
		if(eflg>=1 && Enemy_5.x!=0 && Enemy_5.y!=0){
			DrawRotaGraph( (int)Enemy_5.x, (int)Enemy_5.y+60, 2.5, 0.0, Effect[j], TRUE ); //��e�G�t�F�N�g
			j++;
			if(j>=6){
				j=0;
				eflg=0;//��e�G�t�F�N�g�t���O��܂�
			}
		}
		if(dflg>=1){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //���ŃG�t�F�N�g
			}
			dflg=0;
		}
	}
	return;
}

//�񕜃A�C�e������
void ItemControl()
{
	if(Item1.flag>=1){
		DrawRotaGraph( Item1.x, Item1.y, 1.0, 0.0, hItem, TRUE );
	}
	if(Item1.y>WNDH){
		Item1.flag=0;
		Item1.x=0;
		Item1.y=0;
	}
	Item1.y += 5;
}

//�G�@�e�ې���
void eBulletControl()
{
	int j, flg=1;//�G�����ł����Ƃ��ɒe�ۂ𐶐������Ȃ����߂̃t���O

	for(j=0; j<PBULLET_Y; j++){
		//�T�����Œe�ۂ𔭎�
		double Ans1 = (7.0/difficult);
		int Ans2 = (int)Ans1;
		if(counter%Ans2== 0){
			if(Enemy.hp > 0 && flg && Enemy.flag){
				if(eBullet[0][j].Flag == 0){
					eBullet[0][j].Flag = 1;
					eBullet[0][j].x = Enemy.x; //�ʒu��񓯊�
					eBullet[0][j].y = Enemy.y;
					break; //�C�����break�̈ʒu
				}
			}
			//break; ��������break����ƒP�����˂����ɂȂ�
		}
	}
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet[0][j].Flag == 1){
			eBullet[0][j].y += 10; //�e�ۂ��ړ�������
			if(eBullet[0][j].y > WNDH){	
				eBullet[0][j].Flag = 0;	//��ʊO�ɒe�ۂ��o����t���O��܂�
			}
		}
	}
		
	return;
}

//�����V���b�g
void eBulletControl_1()
{
	int j;//���܂ŉ��������������i�[
	static int Bt = 0;

	if(Enemy_2.hp > 0 && Enemy_2.y > 200){
		for(j=0; j<PBULLET_Y; j++){
			if(Enemy_2.hp > 0){
				if(eBullet_2[0][j].Flag == 0){
					eBullet_2[0][j].Flag = 1;
					eBullet_2[0][j].vx = (5*difficult)*cos(PI*Bt/8);
					eBullet_2[0][j].vy = (5*difficult)*sin(PI*Bt/8);
					eBullet_2[0][j].x = Enemy_2.x + 50*cos(PI*Bt/8);
					eBullet_2[0][j].y = Enemy_2.y + 50*sin(PI*Bt/8);
					Bt++;
				}
				if(eBullet_2[0][j].y > 600 || eBullet_2[0][j].x > WNDW-135 || eBullet_2[0][j].x < 0 || eBullet_2[0][j].y < 0){
					eBullet_2[0][j].Flag = 0;
				}
				if(eBullet_2[0][j].Flag == 1){
					eBullet_2[0][j].x += eBullet_2[0][j].vx;
					eBullet_2[0][j].y += eBullet_2[0][j].vy;
				}
			}
		}
	}
	if(Enemy_2.hp <= 0 || Enemy_2.flag<=0){
		for(j=0; j<PBULLET_Y; j++){
			eBullet_2[0][j].Flag = 0;
			eBullet_2[0][j].vx = 0;
			eBullet_2[0][j].vy = 0;
			eBullet_2[0][j].x = 0;
			eBullet_2[0][j].y = 0;
		}
	}
	return;
}

//���b�N�I��
void eBulletControl_2(){
	int j;
	double s;

	if(Enemy_4.hp > 0 && Enemy_4.y > 200){
		for(j=0; j<PBULLET_Y; j++){
			if((Enemy_4.hp > 0) /*||*/&& Enemy_4.flag == 1){
				if(eBullet_4[0][j].Flag == 0){
					eBullet_4[0][j].Flag = 1;
					s = atan((Enemy_4.y - Player.y)/(Enemy_4.x - Player.x));//�p�x�v�Z
					//	if(Enemy_4.x > Player.x) s = atan((Enemy_4.y - Player.y)/(-Enemy_4.x + Player.x));
					if(Enemy_4.x == Player.x) s = 0;
					eBullet_4[0][j].vx = (10*difficult)*cos(s);
					eBullet_4[0][j].vy = (10*difficult)*sin(s);//���x
					eBullet_4[0][j].x = Enemy_4.x ;
					eBullet_4[0][j].y = Enemy_4.y + 10;
					if(Enemy_4.x > Player.x){
						eBullet_4[0][j].vx = -(10*difficult)*cos(s);
						eBullet_4[0][j].vy = -(10*difficult)*sin(s);//���x
					}
				}
			}
		}
	}
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet_4[0][j].y > 600 || eBullet_4[0][j].x > WNDW-135 || eBullet_4[0][j].x < 0 || eBullet_4[0][j].y < 0){
			eBullet_4[0][j].Flag = 0;
		}
		if(eBullet_4[0][j].Flag == 1){
			eBullet_4[0][j].x += eBullet_4[0][j].vx;
			eBullet_4[0][j].y += eBullet_4[0][j].vy;
		}
	}
	return;
}

//�{�X������1
void eBulletControl_3(){
	int i;
	double s;

	if(Enemy_5.hp <= 0|| Enemy_5.flag == 0){
		for(i=0;i<PBULLET_Y;i++){
			eBullet_6[0][i].Flag = 0;
			eBullet_7[0][i].Flag = 0;
		}
	}
	if(Enemy_5.hp > 0 && Enemy_5.y > 200){
		for(i=0;i<PBULLET_Y;i++){
			if((Enemy_5.hp > 0) || Enemy_5.flag == 1){				
				if(eBullet_6[0][i].Flag == 0){
					eBullet_6[0][i].Flag = 1;
					s = atan((Enemy_5.y - Player.y)/(Enemy_5.x - Player.x));//�p�x�v�Z
					if(Enemy_5.x == Player.x) s = 0;
					eBullet_6[0][i].vx = (10*difficult)*cos(s);
					eBullet_6[0][i].vy = (10*difficult)*sin(s);//���x
					eBullet_6[0][i].x = Enemy_5.x + 30;
					eBullet_6[0][i].y = Enemy_5.y + 10;
					if(Enemy_5.x > Player.x){
						eBullet_6[0][i].vx = -(10*difficult)*cos(s);
						eBullet_6[0][i].vy = -(10*difficult)*sin(s);//���x
					}
				}
				
				if(eBullet_7[0][i].Flag == 0){
					eBullet_7[0][i].Flag = 1;
					s = atan((Enemy_5.y - Player.y)/(Enemy_5.x - Player.x));//�p�x�v�Z
					if(Enemy_5.x == Player.x) s = 0;
					eBullet_7[0][i].vx = (10*difficult)*cos(s);
					eBullet_7[0][i].vy = (10*difficult)*sin(s);//���x
					eBullet_7[0][i].x = Enemy_5.x;
					eBullet_7[0][i].y = Enemy_5.y + 10;
					if(Enemy_5.x > Player.x){
						eBullet_7[0][i].vx = -(10*difficult)*cos(s);
						eBullet_7[0][i].vy = -(10*difficult)*sin(s);//���x
					}
				}
				if(eBullet_6[0][i].y > 600 || eBullet_6[0][i].x > WNDW-135 || eBullet_6[0][i].x < 0 || eBullet_6[0][i].y < 0){
					eBullet_6[0][i].Flag = 0;
				}
				if(eBullet_7[0][i].y > 600 || eBullet_7[0][i].x > WNDW-135 || eBullet_7[0][i].x < 0 || eBullet_7[0][i].y < 0){
					eBullet_7[0][i].Flag = 0;
				}
				
				if(eBullet_6[0][i].Flag == 1){
					eBullet_6[0][i].x += eBullet_6[0][i].vx;
					eBullet_6[0][i].y += eBullet_6[0][i].vy;
				}
				if(eBullet_7[0][i].Flag == 1){
					eBullet_7[0][i].x += eBullet_7[0][i].vx;
					eBullet_7[0][i].y += eBullet_7[0][i].vy;
				}
			}
		}
	}
	if(Enemy_5.hp <= 0 || Enemy_5.flag == 0){
		for(i=0;i<PBULLET_Y;i++){
			eBullet_6[0][i].Flag = 0;
			eBullet_7[0][i].Flag = 0;
			eBullet_6[0][i].x = 0;
			eBullet_7[0][i].x = 0;
			eBullet_6[0][i].y = 0;
			eBullet_7[0][i].y = 0;
		}
	}
	return;
}

//����2
void eBulletControl_4(){
	int i;
	double Ans1 = (5.0/difficult);
		int Ans2 = (int)Ans1;

	if(Enemy_5.hp <= 0|| Enemy_5.flag == 0){
		for(i=0;i<PBULLET_Y;i++){
			eBullet_5[0][i].Flag = 0;
		}
	}
	if(Enemy_5.hp > 0 && Enemy_5.y > 200){
		for(i=0;i<PBULLET_Y;i++){
			if(counter%Ans2 == 0){
				if((Enemy_5.hp > 0) || Enemy_5.flag == 1){
					if(eBullet_5[0][i].Flag == 0){
							eBullet_5[0][i].Flag = 1;
							eBullet_5[0][i].x = Enemy_5.x; 
							eBullet_5[0][i].y = Enemy_5.y;
							break; 
					}
				}
			}
		}
		for(i=0;i<PBULLET_Y;i++){
			if(eBullet_5[0][i].Flag == 1){
				eBullet_5[0][i].y += 10; //�e�ۂ��ړ�������
				if(eBullet_5[0][i].y > 600 || eBullet_5[0][i].x > WNDW-135 || eBullet_5[0][i].x < 0 || eBullet_5[0][i].y < 0){	
					eBullet_5[0][i].Flag = 0;	//��ʊO�ɒe�ۂ��o����t���O��܂�
				}
			}
		}
	}
	if(Enemy_5.hp <= 0 || Enemy_5.flag == 0){
		for(i=0;i<PBULLET_Y;i++){
			eBullet_5[0][i].Flag = 0;
			eBullet_5[0][i].x = 0;
			eBullet_5[0][i].y = 0;
		}
	}
	return;
}

//�G�@�e�ە`��
void eBulletDraw()
{
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet[0][j].Flag == 1 /*&& Enemy.flag*/){
			DrawRotaGraph((int)eBullet[0][j].x, (int)eBullet[0][j].y+50, 0.5, 0.0, heBullet[0], TRUE, 0);
		}
	}
	return;
}

void eBulletDraw_1()
{
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet_2[0][j].Flag == 1){
			DrawRotaGraph((int)eBullet_2[0][j].x, (int)eBullet_2[0][j].y, 0.5, 0.0, heBullet_2[0], TRUE, 0);
		}
	}
	return;
}

void eBulletDraw_2(){
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet_4[0][j].Flag == 1){
			DrawRotaGraph((int)eBullet_4[0][j].x, (int)eBullet_4[0][j].y, 0.5, 0.0, heBullet_4[0], TRUE, 0);
		}
	}
	return;
}

void eBulletDraw_3(){
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet_5[0][j].Flag == 1){
			DrawRotaGraph((int)eBullet_5[0][j].x, (int)eBullet_5[0][j].y, 0.5, 0.0, heBullet_4[0], TRUE, 0);
		}
	}
	return;
}

void eBulletDraw_4(){
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet_6[0][j].Flag == 1){
			DrawRotaGraph((int)eBullet_6[0][j].x, (int)eBullet_6[0][j].y, 0.5, 0.0, heBullet_4[0], TRUE, 0);
		}
	}
	return;
}

void eBulletDraw_5(){
	int j;
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet_7[0][j].Flag == 1){
			DrawRotaGraph((int)eBullet_7[0][j].x, (int)eBullet_7[0][j].y, 0.5, 0.0, heBullet_4[0], TRUE, 0);
		}
	}
	return;
}

//FPS�\���֐�(�ޗǍ�)
void FpsTimeFunction()
{
	static int FpsTime[2]={0,},FpsTime_i = 0;
	static double Fps = 0.0;
	int Red = GetColor(255,0,0);

	if(FpsTime_i == 0) {
		FpsTime[0] = GetNowCount();	/* Fps�𑪒� */
	}
	if(FpsTime_i == 59){							/*Fps�𑪒�*/
			FpsTime[1] = GetNowCount();
			Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 60.0f); /* Fps�̌v�Z */
			FpsTime_i = 0;
	}else{
		FpsTime_i++;
	}
	if(Fps != 0){
		DrawFormatString(730,580,Red,"FPS %.1f",Fps);// �\��
	}

	return ;
}

//�J�E���g�_�E��
void CountFunction(int OldTime){
	int Time, NowTime; //�c�莞�ԕۑ��p
	int Red = GetColor(255,0,0);

		Time = GetNowCount();//���݂̎��Ԏ擾
		NowTime = Time - OldTime; // ���t���[���o�߂��������Ԃ𓾂�
		if(stageflg>=1){
			RemainingTime = (int)((StageTime2-NowTime/*-StopTime-Stage1RemainingTime*/+StopTime+(Stage1RemainingTime*1e3))/1e3);
		}else{
			RemainingTime = (int)((StageTime1-(NowTime-StopTime))/1e3);
		}
		SetFontSize( 24 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(670,550,Red,"Time %ds", RemainingTime);//�o��

		if(RemainingTime>=1 && restartflg==1){
			restartflg=0;
		}
	return;
}

//�X�R�A�\��(�ޗǍ�)
int ScoreShow()
{
	static int flg = 1,flg_1 = 1,flg_2 = 1; //�����Ă�� 1 ���񂾂� 0
	static int flg_4 = 1,flg_5 = 1;
	if(Enemy.hp > 0) flg = 1;
	if(Enemy.hp < 0 && flg == 1){
		Score += 1000;
		flg = 0; //�|���ꂽ�Ƃ����Z
	}
	if(Enemy_1.hp > 0) flg_1 = 1;
	if(Enemy_1.hp < 0 && flg_1 == 1){
		Score += 1000;
		flg_1 = 0; //�|���ꂽ�Ƃ����Z
	}
	if(Enemy_2.hp > 0) flg_2 = 1;
	if(Enemy_2.hp < 0 && flg_2 == 1){
		Score += 1000;
		flg_2 = 0; //�|���ꂽ�Ƃ����Z
	}
	if(Enemy_4.hp > 0) flg_4 = 1;
	if(Enemy_4.hp < 0 && flg_4 == 1){
		Score += 1000;
		flg_4 = 0; //�|���ꂽ�Ƃ����Z
	}
	if(Enemy_5.hp > 0) flg_5 = 1;
	if(Enemy_5.hp < 0 && flg_5 == 1){
		Score += 1000;
		flg_5 = 0; //�|���ꂽ�Ƃ����Z
	}
	SetFontSize( 20 ) ; //�t�H���g�T�C�Y�ύX
	DrawFormatString(675,580,RGB(0,0,255),"Score %5d",Score);
	return Score;
}

//HP�\��(�ޗǍ�)
void ShowMyHp()
{
	if(stageflg<=0){
		SetFontSize( 36 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(670,10,RGB(0,0,255),"Stage�T");
	}else if(stageflg>=1){
		SetFontSize( 36 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(670,10,RGB(0,0,255),"Stage�U");
	}
	SetFontSize( 36 ) ; //�t�H���g�T�C�Y�ύX
	DrawFormatString(700,350,RGB(0,0,255),"HP %d",Player.hp);	
	return ;
}

//���j���[�v�Z
int MenuCreate()
{
	//���j���[����
	Menu_t MenuType[5] = {
		{ 100,250,""},
		{ 100,300,"Play"},
		{ 100,350,"Config"},
		{ 100,400,"Hlep"},
		{ 100,450,"Exit"},
	};

	if(Key[KEY_INPUT_DOWN] == 1 ){ //���������ꂽ������
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
		SelectNum = (SelectNum + 1)%5;
		if(SelectNum==0){
			SelectNum=1;
		}
	}
	if(Key[KEY_INPUT_UP] == 1){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
		SelectNum = (SelectNum + 4)%5;
		if(SelectNum==0){
			SelectNum=4;
		}
	}
	if(Key[KEY_INPUT_RETURN/*SPACE*/] == 1 && SelectNum != 0){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
		return SelectNum;
	}

	for(int i=0;i<5;i++){//���j���[�̍��ڐ��̃��[�v

		if(i == SelectNum){ //�������e���I��ԍ��Ɠ��������ׂ�
			MenuType[i].x = 100;
		}else{
			MenuType[i].x = 150;
		}
	}
	SetFontSize( 90 ) ; //�t�H���g�T�C�Y�ύX
	DrawFormatString(200,50,RGB(0,0,255),"Shooting");
	for(int i=0;i<5;i++){
		SetFontSize( 36 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(MenuType[i].x,MenuType[i].y,GetColor(255,255,255),MenuType[i].name);
	}	
	return -1;
}

//�R���t�B�O����
int Config()
{
	Menu_t ConfigType[5] = {
		{ 300,250,""},
		{ 300,300,"easy"},
		{ 300,350,"normal"},
		{ 300,400,"hard"},
		{ 300,450,"Return to tile"},
	};
	if(Key[KEY_INPUT_DOWN] == 1 ){ //���������ꂽ������
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
		CSelctNum = (CSelctNum + 1)%5;
		if(CSelctNum==0){
			CSelctNum=1;
		}
	}
	if(Key[KEY_INPUT_UP] == 1){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
		CSelctNum = (CSelctNum + 4)%5;
		if(CSelctNum==0){
			CSelctNum=4;
		}
	}
	if(Key[KEY_INPUT_RETURN] == 1 && CSelctNum != 0){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
		return CSelctNum;
	}

	for(int i=0;i<5;i++){//���j���[�̍��ڐ��̃��[�v
		if(i == CSelctNum){ //�������e���I��ԍ��Ɠ��������ׂ�
			ConfigType[i].x = 100;
		}else{
			ConfigType[i].x = 150;
		}
	}
	SetFontSize( 90 ) ; //�t�H���g�T�C�Y�ύX
	DrawFormatString(200,50,RGB(0,0,255),"Shooting");
	for(int i=0;i<5;i++){
		SetFontSize( 36 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(ConfigType[i].x,ConfigType[i].y,GetColor(255,255,255),ConfigType[i].name);
	}	
	return -1;
}

// �^�C�g��BGM
static void OpningMusic(int Flg)
{ 
	if(Flg == 0) PlaySoundMem(hOP, DX_PLAYTYPE_LOOP,FALSE);//BGM�Đ�
	else{ 
		StopSoundMem(hOP);
	}
}

static void StageBgm(int flg)
{ //�Q�[����BGM
	if(flg >= 1 && (Enemy_2.flag<=0 || Enemy_5.flag<=0)){
		if(CheckSoundMem(hBossBGM)){
			StopSoundMem(hBossBGM);
		}
		PlaySoundMem(hBGM, DX_PLAYTYPE_LOOP,FALSE);//BGM�Đ�
	}
	if(flg >= 1 && (Enemy_2.flag>=1 || Enemy_5.flag>=1)){
		if(CheckSoundMem(hBGM)){
			StopSoundMem(hBGM);
		}
		PlaySoundMem(hBossBGM, DX_PLAYTYPE_LOOP,FALSE);
	}
}

//�X�e�[�W���䕔
void StageControl()
{
	static int StageGraph;//���[�h�����摜
	static int bossflg1=-1, bossflg2=-1, flg1=0, flg2=0;
	static char chStr[128], chStr2[128], chStr3[128], chStr4[128];

	//�X�e�[�W���؂�ւ�
	if(stageflg<=0){
		StageGraph = hSTAGE;
	}else if(stageflg==1){
		StageGraph = hSTAGE1;
		stageflg=2;
	}

	//�A�C�e���o������
	if(Player.hp<5 && counter%500==0 && Item1.flag<=0){
		Item1.flag=1;
		Item1.x = GetRand(WNDW-160);
		Item1.y = 10;
		Iflg=0;
	}

	//�G�@�o������
	switch(counter%150){
		case 30:
			if(Enemy.flag<=0 && Enemy_5.flag<=0 && Enemy_2.flag<=0){//���ړ�
				Enemy.flag=1;
				Enemy.x = (WNDW-130)/2;
				Enemy.y = 50;
				Enemy.hp = 5;
				break;
			}
		case 80:
			if(Enemy_1.flag<=0 && Enemy_5.flag<=0 && Enemy_2.flag<=0){ //�h�N��
				Enemy_1.flag=1;
				Enemy_1.x = 10;
				Enemy_1.y = 20;
				Enemy_1.hp = 20;
				break;
			}
		case 130: //�X�e�[�W�Q�Œǉ�
			if(stageflg>=1 && Enemy_2.flag <= 0 && Enemy_4.flag<=0 && Enemy_5.flag<=0){//���b�N�I��
				Enemy_4.flag = 1;
				Enemy_4.x = GetRand(WNDW-160);
				Enemy_4.y = 0;
				Enemy_4.hp = 20;
				break;
			}
	}

	//�{�X�̏o������
	if(Enemy_2.flag<=0 && Score>=5000 && stageflg<=0 && bossflg1<=-1){ //�X�e�[�W�P�̃{�X(����)
		Enemy.flag=0;
		Enemy_1.flag=0;
		Enemy_4.flag=0;
		Enemy_2.flag=1;
		Enemy_2.x = 100;
		Enemy_2.y = 0;
		Enemy_2.hp = 50;
		bossflg1=0;
	}
	if(Enemy_5.flag<=0 && stageflg>=1 && Score>=12000 && bossflg2<=-1){//�X�e�[�W�Q�̃{�X(�{�X��)
		Enemy.flag=0;
		Enemy.hp=0;
		Enemy_1.flag=0;
		Enemy_1.hp=0;
		Enemy_4.flag = 0;
		Enemy_4.hp=0;
		Enemy_5.flag = 1;
		Enemy_5.x = 400;
		Enemy_5.y = 20;
		Enemy_5.hp = 30;
		bossflg2=0;
	}

	if(bossflg1==0 && Enemy_2.hp<=0){ //�X�e�[�W�P�̃{�X��|������̏���
		Stage1RemainingTime = (int)(StageTime1-RemainingTime);
		bossflg1=1;
	}
	if(bossflg2==0 && Enemy_5.hp<=0){ //�X�e�[�W�Q�̃{�X��|������̏���
		//�ʒm����
		Stage2RemainingTime = (int)((StageTime2/1e3)-RemainingTime);
		SetFontSize( 24 ) ; //�t�H���g�T�C�Y�ύX
		wsprintf(chStr2,"�X�e�[�W�T�N���A�^�C���F%ds",Stage1RemainingTime);
		wsprintf(chStr3,"�X�e�[�W�U�N���A�^�C���F%ds",Stage2RemainingTime);
		wsprintf(chStr4,"�Q�[���N���A�^�C���F%ds", Stage2RemainingTime+Stage1RemainingTime);
		ClearDrawScreen(); //��ʃN���A
		DrawFormatString(310,200,RGB(0,0,255),"�Q�[���N���A");
		DrawFormatString(230,250,RGB(0,0,255),chStr2);
		DrawFormatString(230,300,RGB(0,0,255),chStr3);
		DrawFormatString(260,350,RGB(0,0,255),chStr4);
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// ���b�Z�[�W����
			if( ProcessMessage() == -1 )
			{
				break ;	// �G���[�����������烋�[�v�𔲂���
			}
		}
		ClearDrawScreen(); //��ʃN���A
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
		restartflg=1;//�e�t���O����
		Player.flg=1;
		Player.hp=0;
		bossflg1=-1;
		bossflg2=-1;
		flg1=0;
		flg2=0;
		Position(); //�������ł��ׂĂ̏�Ԃ����Z�b�g
		if(restartflg>=1 || Player.flg>=1){//BGM�̐؂�ւ�
			if(CheckSoundMem(hBGM)){
				StopSoundMem(hBGM);
			}else if(CheckSoundMem(hBossBGM)){
				StopSoundMem(hBossBGM);
			}
		}
	}

	SetDrawArea(0, 0, WNDW-130, WNDH); //�`��̈搧��
	//�摜�P�����㉺�Q���A���ŕ`�悵�ăX�N���[��
	DrawGraph(0, counter%STAGEH-STAGEH, StageGraph, FALSE);//��
	DrawGraph(0, counter%STAGEH,        StageGraph, FALSE);//��
	SetDrawArea(0, 0, WNDW, WNDH);

	//�X�e�[�W�N���A�̏���
	if(bossflg1>=1 && stageflg<=0){//�{�X��|�����玟�̃X�e�[�W
		for(int i=0; i<PBULLET_Y; i++){
			pBullet[0][i].x=0;
			pBullet[0][i].y=0;
			pBullet_1[0][i].x=0;
			pBullet_1[0][i].y=0;
			pBullet_1[0][i].vx=0;
			pBullet_1[0][i].vy=0;
			pBullet_2[0][i].x=0;
			pBullet_2[0][i].y=0;
			pBullet_2[0][i].vx=0;
			pBullet_2[0][i].vy=0;
		}
		Enemy.flag=0;
		Enemy_1.flag=0;
		Enemy_2.flag=0;
		Enemy_3.flag=0;
		Enemy_4.flag=0;
		Enemy_5.flag=0;
		Item1.flag=0;
		Item1.x=0;
		Item1.y=0;
		Iflg=0;
		//�ʒm����
		StopTimeBegin = GetNowCount();
		ClearDrawScreen(); //��ʃN���A
		SetFontSize( 24 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(300,300,RGB(0,0,255),"�X�e�[�W�T�N���A");
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// ���b�Z�[�W����
			if( ProcessMessage() == -1 )
			{
				break ;	// �G���[�����������烋�[�v�𔲂���
			}
		}
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
		Stage1RemainingTime = (int)((StageTime1/1e3)-RemainingTime);
		stageflg=1;
	}
	//�Q�[���I�[�o�[���̏���
	if((RemainingTime<=0 || (Player.hp<=0 && Player.flg<=0)) && restartflg<=0){
		restartflg=1;//�e�t���O����
		Player.flg=1;
		Player.hp=0;
		bossflg1=-1;
		bossflg2=-1;
		flg1=0;
		flg2=0;
		Position(); //�������ł��ׂĂ̏�Ԃ����Z�b�g
		//�ʒm����
		StopTimeBegin = GetNowCount();
		ClearDrawScreen(); //��ʃN���A
		SetFontSize( 24 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(320,250,RGB(0,0,255),"�Q�[���I�[�o�[");
		DrawFormatString(300,300,RGB(0,0,255),"Push the enter key");
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// ���b�Z�[�W����
			if( ProcessMessage() == -1 )
			{
				break ;	// �G���[�����������烋�[�v�𔲂���
			}
		}
		ClearDrawScreen(); //��ʃN���A
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
		if(restartflg>=1 || Player.flg>=1){//BGM�̐؂�ւ�
			if(CheckSoundMem(hBGM)){
				StopSoundMem(hBGM);
			}else if(CheckSoundMem(hBossBGM)){
				StopSoundMem(hBossBGM);
			}
		}
	}

	//�^�C���������̏���
	if(Key[KEY_INPUT_SPACE]==1){
		StopTimeBegin = GetNowCount();
		ClearDrawScreen(); //��ʃN���A
		SetFontSize( 24 ) ; //�t�H���g�T�C�Y�ύX
		DrawFormatString(300,300,RGB(0,0,255),"�ĊJ�̓G���^�[�L�[");
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// ���b�Z�[�W����
			if( ProcessMessage() == -1 )
			{
				break ;	// �G���[�����������烋�[�v�𔲂���
			}
		}
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
	}

	return;
}

//���C���֐�
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	int RefreshTime; //���݂̎���

	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(WNDW, WNDH, 32); //�E�B���h�E�T�C�Y800*600�ɐݒ�
	SetMainWindowText("Shooting"); //�^�C�g��
	SetWindowIconID(IDI_ICON0); //�A�C�R��
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂɐݒ�
	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		 return -1;	// �G���[���N�����璼���ɏI��
	}
	//�t�H���g���[�h
	LPCSTR font_path = "Font/mofuji.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	} else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL,"�t�H���g�Ǎ����s","",MB_OK);
	}
	
	DataLoad(); //�e�f�[�^�ǂݍ���
	Position(); //�e�\���̒l�̏�����

	hPort = CreateFile(
					"COM3",
					GENERIC_READ|GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL
				);
				if(hPort == INVALID_HANDLE_VALUE)
				{
					MessageBox(NULL,"Port could not open.\n","",MB_OK);
					exit(0);
				}

	//while(���b�Z�[�W����, �L�[�̓��͏�Ԃ��X�V����)
	while(ProcessMessage()==0 && gpUpdateKey()==0 ){

		

				Ret = SetupComm(
					hPort,
					1024,
					1024
				);

				if(Ret == FALSE)
				{
					MessageBox(NULL,"SetupComm failed.\n","",MB_OK);
					CloseHandle(hPort);
					exit(0);
				}

				Ret = PurgeComm(
					hPort,
					PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR
				);
				                                              
				if(Ret == FALSE)
				{
					MessageBox(NULL,"PurgeComm failed.\n","",MB_OK);
					CloseHandle(hPort);
					exit(0);
				}

				Ret = EscapeCommFunction(
					hPort,
					SETRTS
				);

				if(Ret == FALSE)
				{
					MessageBox(NULL,"EscapeCommFunction failed.\n","",MB_OK);
					CloseHandle(hPort);
					exit(0);
				}

				Ret = ReadFile( 
					hPort,
					In,
					1,
					&lRead,
					NULL 
				);
				if( Ret == FALSE ) 
				{
					MessageBox(NULL,"ReadFile failed. \n","",MB_OK);
					CloseHandle(hPort);
					exit(0);
				}

			//	CloseHandle(
			//		hPort
			//	);

		ClearDrawScreen(); //��ʃN���A
		//ChangeFont("���t��"); //�t�H���g�ύX
		if(Cflg>=1){
			switch(Config()){
				case 1:
					difficult=0.5;
					StageBgm(Mflg);
					OpningMusic(Mflg); //�^�C�g��BGM
					break;
				case 2:
					difficult=1.0;
					StageBgm(Mflg);
					OpningMusic(Mflg); //�^�C�g��BGM
					break;
				case 3:
					difficult=2.0;
					StageBgm(Mflg);
					OpningMusic(Mflg); //�^�C�g��BGM
					break;
				case 4://�ݒ��ۑ����^�C�g���֖߂�
					Position();
					break;
			}
		}else if(Mflg <= 0 && Cflg<=0){
			OpningMusic(Mflg);
			switch(MenuCreate()){
				case 1: //�Q�[���J�n
					RefreshTime = GetNowCount(); //�N���������Ԃ��擾
					Mflg = 1;
					StageBgm(Mflg);
					OpningMusic(Mflg); //�^�C�g��BGM
					break;
				case 2: //�R���t�B�O
					if(Cflg<1){
						Cflg=1;
					}
					break;
				case 3: //�w���v
					ClearDrawScreen(); //��ʃN���A
					//�w���v��ʂ̕`��
					DrawGraph(0, 0, hHelp, TRUE);
					while(CheckHitKey(KEY_INPUT_ESCAPE) == 0){
						// ���b�Z�[�W����
						if( ProcessMessage() == -1 )
						{
							break ;	// �G���[�����������烋�[�v�𔲂���
						}
					}
					Mflg=0;
					PlaySoundMem(Select,DX_PLAYTYPE_BACK);//���ʉ��Đ�
					break;
				case 4: //�I��
					DxLib_End();
					return 0;
			}
		}else if(Mflg>=1 && Cflg<=0){

				OpningMusic(Mflg);
				StageBgm(Mflg);

				StageControl(); //�X�e�[�W�`��
		
				PlayerControl();	//���@����

				pBulletControl();	//���@�e�ې���

				pBulletDraw();	//���@�e�ە`��

				EnemyControl();	//�G�@����

				EnemyControl_1();

				EnemyControl_2();

				EnemyControl_3();

				EnemyControl_4();
	
				eBulletControl();	//�G�@�e�ې���

				eBulletControl_1();

				eBulletControl_2();

				eBulletControl_3();

				eBulletControl_4();

				eBulletDraw();	//�G�@�e�ە`��

				eBulletDraw_1();

				eBulletDraw_2();

				eBulletDraw_3();

				eBulletDraw_4();

				eBulletDraw_5();

				ItemControl();
			//	FpsTimeFunction();	//FPS�\��

				CountFunction(RefreshTime);	//�J�E���g�_�E���\��

				ScoreShow(); //�X�R�A�\��

				ShowMyHp(); //HP�\��

				counter++; //�J�E���^�[�X�V
		}

		ScreenFlip(); //����ʂ�\��ʂɔ��f

		if(Key[KEY_INPUT_ESCAPE]==1){
			Position();//�������ł��ׂĂ̏�Ԃ����Z�b�g
			restartflg=1;//�e�t���O����
			if(restartflg>=1 || Player.flg>=1){//BGM�̐؂�ւ�
				if(CheckSoundMem(hBGM)){
					StopSoundMem(hBGM);
				}else if(CheckSoundMem(hBossBGM)){
					StopSoundMem(hBossBGM);
				}
			}
		}

	}
  DxLib_End();    // DX���C�u�����I������
  return 0;
}