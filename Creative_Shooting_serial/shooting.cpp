#include <math.h>
#include "DxLib.h"
#include "resource.h"
#include "define.h"
#include "prototype.h"
#include "dataload.h"


// キーの入力状態を更新する
int gpUpdateKey()
{
  char tmpKey[256]; // 現在のキーの入力状態を格納する
  GetHitKeyStateAll( tmpKey ); // 全てのキーの入力状態を得る
  for( int i=0; i<256; i++ ){ 
    if( tmpKey[i] != 0 ){ // i番のキーコードに対応するキーが押されていたら
            Key[i]++;     // 加算
    } else {              // 押されていなければ
            Key[i] = 0;   // 0にする
    }
  }
  return 0;
}

//自機情報格納用構造体
typedef struct{
	double x, y; //位置情報
	int hp, flg, Damageflg;
}PLEYER;

PLEYER Player;

//敵機情報格納用構造体
typedef struct{
	double x, y;//位置情報
	int hp, flag;
}ENEMY;

ENEMY Enemy,Enemy_1,Enemy_2,Enemy_3,Enemy_4,Enemy_5;

//自機弾丸情報格納用構造体
typedef struct{ 
	double x, y; //プレイヤー弾丸の位置
	double vx,vy;
	int Flag;     //プレイヤー弾丸フラグ
}PBULLET;

PBULLET pBullet[PBULLET_X][PBULLET_Y],pBullet_1[PBULLET_X][PBULLET_Y],pBullet_2[PBULLET_X][PBULLET_Y];

//敵機弾丸用情報格納用構造体
typedef struct{
	double x, y; //敵弾丸の位置
	int Flag; //敵弾丸フラグ
	double vx,vy;//弾速度
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

//各構造体情報の初期化
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
	StopTime=0; //タイムしていた合計時間
	Stage1RemainingTime=0; //ステージクリアにかかった時間
	Stage2RemainingTime=0;

	//弾丸フラグの初期化
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

//自機の操作
void PlayerControl()
{
	int j;
	static int eflg=0, i=0, dTime=0;

	//計算フェーズ
	if(Player.hp > 0){ //自機が消えているときはキー入力を無効
		if(Player.flg>=1){
			Player.flg=0;
		}
		
		//出力
		if( Key[ KEY_INPUT_RIGHT ] >= 1 && Player.x < (WNDW-130)-30 ){ // 右ボタンが押された時右へ移動　※Player.x < 750 は画面外に出ないための処理
			Player.x += 6;
			if( Key[ KEY_INPUT_LSHIFT ] >= 1) Player.x -=3 ; //Shiftキーでスローコマンド
		}
		if( Key[ KEY_INPUT_LEFT  ] >= 1/*strcmp(In, "NO\n")*/ && Player.x > 0){
			Player.x -= 6;
			if( Key[ KEY_INPUT_LSHIFT ] >= 1) Player.x += 3;
		}
		if( Key[ KEY_INPUT_DOWN  ] >= 1 && Player.y < WNDH-30){	//以下同様の条件
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
		//敵の本体に当たったら自機のＨＰを減らす
		if(Player.Damageflg<=0){
			dTime = GetNowCount(); //プレイヤーがダメージを受けた時間の取得
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
			//敵弾丸に被弾したらＨＰ減少
			for(j=0; j<PBULLET_Y; j++){
				if(eBullet[0][j].x+5 > Player.x-5 && eBullet[0][j].x-5 < Player.x+5 && eBullet[0][j].y+5 > Player.y-5 && eBullet[0][j].y-5 < Player.y+5 && Enemy.hp>0){
					eflg=1;
					Player.hp--;
					Player.Damageflg=1;;
					break;//ここでループを抜けないと一回の被弾で死亡
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
		DrawRotaGraph( (int)Player.x, (int)Player.y-60, 2.5, 0.0, Effect[i], TRUE ); //被弾エフェクト
		i++;
		if(i>=6){
			i=0;
			eflg=0;//被弾エフェクトフラグを折る
		}
	}
	//ダメージを受けてから無敵時間が3秒以上続いたら解除
	if(Player.Damageflg>=1 && GetNowCount()-dTime >= 2*1e3){
		Player.Damageflg=0;
	}
	//HPが０になったら座標を初期位置へ
	if(Player.hp == 0){
		Player.x = (WNDW-130)/2;
		Player.y = WNDH-30;
		Player.Damageflg=0;
	}
	//描画フェーズ
	if(Player.hp>0){
		if(Player.Damageflg>=1){//ダメージ後の無敵状態の描画
			SetDrawBlendMode( DX_BLENDMODE_ALPHA,  128 );
			DrawRotaGraph( (int)Player.x, (int)Player.y, 1.0, 0.0, hPlayer, TRUE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND,  0 );
		}else if(Player.Damageflg<=0){
			DrawRotaGraph( (int)Player.x, (int)Player.y, 1.0, 0.0, hPlayer, TRUE );
		}
	}
	return;
}

//自機弾丸制御
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

	if(Key[ KEY_INPUT_Z	] == 1 && Player.hp>0){ //Zキーが押されかつ、HPが残っていたら
		PlaySoundMem(EffectMusic, DX_PLAYTYPE_BACK); //効果音
		for(j=0; j<PBULLET_Y; j++){
			if(pBullet[0][j].Flag == 0){
					pBullet[0][j].Flag = 1;			//フラグを立てる
					pBullet[0][j].x = Player.x; // 自機の場所と弾の出る位置を同期
					pBullet[0][j].y = Player.y;
					break;
			}
		}
	}
	for(j=0; j<PBULLET_Y; j++){
		if(pBullet[0][j].Flag == 1){
			pBullet[0][j].y -= 10; //弾丸を移動させる
			if(pBullet[0][j].y < 0){	
				pBullet[0][j].Flag = 0;	//画面外に弾丸が出たらフラグを折る
			}
		}
	}
	//スコアに応じて自機弾丸の追加
	if((ScoreShow() >= 7000) && Key[ KEY_INPUT_Z] == 1 && Player.hp>0){
		PlaySoundMem(EffectMusic, DX_PLAYTYPE_BACK); //効果音
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

//自機弾丸描画
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

//敵機操作
void EnemyControl()
{
	int j, flg=0, flg2=1;
	static int i=0 ,eflg=0, dflg=0, x=0, y=0, k=0;

	//計算フェーズ
	if(Enemy.hp > 0 && Enemy.flag > 0){
		Enemy.x =  ((WNDW-130))/2 - ((WNDW-130)-77)/2*sin(PI / 120 * counter);
		for(j=0; j<PBULLET_Y; j++){
			if(Enemy.y>=10){
				//敵機に自機弾丸が命中したら敵機HPを減らす
				if(Enemy.x+10 > pBullet[0][j].x-10 && Enemy.x-10 < pBullet[0][j].x+10 && Enemy.y+5 > pBullet[0][j].y-5 && Enemy.y-5 < pBullet[0][j].y+5){
					Enemy.hp--;
					eflg=1;//被弾エフェクトフラグ
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
					break;	//一度ダメージを受けたらループを抜ける
				}
				if(Enemy.x+10 > pBullet_1[0][j].x-10 && Enemy.x-10 < pBullet_1[0][j].x+10 && Enemy.y+5 > pBullet_1[0][j].y-5 && Enemy.y-5 < pBullet_1[0][j].y+5){
					Enemy.hp--;
					eflg=1;//被弾エフェクトフラグ
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
					break;	//一度ダメージを受けたらループを抜ける
				}
				if(Enemy.x+10 > pBullet_2[0][j].x-10 && Enemy.x-10 < pBullet_2[0][j].x+10 && Enemy.y+5 > pBullet_2[0][j].y-5 && Enemy.y-5 < pBullet_2[0][j].y+5){
					Enemy.hp--;
					eflg=1;//被弾エフェクトフラグ
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
					break;	//一度ダメージを受けたらループを抜ける
				}
			}
		}
		if(eflg>=1 /*&& Enemy.x>0 && Enemy.y>0*/){
			DrawRotaGraph( (int)Enemy.x, (int)Enemy.y+60, 2.5, 0.0, Effect[i], TRUE ); //被弾エフェクト
			i++;
			if(i>=6){
				i=0;
				eflg=0;//被弾エフェクトフラグを折る
			}
		}
		if(dflg>=1 /*&& Enemy.flag<=0*/){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //消滅エフェクト
			}
			dflg=0;
			/*k++;
			if(k>=6){
				k=0;
				dflg=0;//被弾エフェクトフラグを折る
			}*/
		}
	}
	
	//敵機描画
	if(Enemy.flag){//敵機のHPが残っていたら描画　Enemy.xの乱数はデバッグ用
		DrawRotaGraph( (int)Enemy.x, (int)Enemy.y, 1.2, 0.0, hEnemy, TRUE );
	}
	/*if(Enemy.flag<=0){
		Enemy.x=0;
		Enemy.y=0;
	}*/
 
	return;
}

//雑魚敵制御()
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
			DrawRotaGraph( (int)Enemy_1.x, (int)Enemy_1.y+60, 2.5, 0.0, /*hEnemy_4*/Effect[j], TRUE ); //被弾エフェクト
			j++;
			if(j>=6){
				j=0;
				eflg=0;//被弾エフェクトフラグを折る
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
					Enemy_2.hp = -1; //スコア加算上の考慮
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
					Enemy_2.hp = -1; //スコア加算上の考慮
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
					Enemy_2.hp = -1; //スコア加算上の考慮
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
			DrawRotaGraph( (int)Enemy_2.x, (int)Enemy_2.y+60, 2.5, 0.0, Effect[j], TRUE ); //被弾エフェクト
			j++;
			if(j>=6){
				j=0;
				eflg=0;//被弾エフェクトフラグを折る
			}
		}
		if(dflg>=1){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //消滅エフェクト
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
			DrawRotaGraph( (int)Enemy_4.x, (int)Enemy_4.y+60, 2.5, 0.0, Effect[j], TRUE ); //被弾エフェクト
			j++;
			if(j>=6){
				j=0;
				eflg=0;//被弾エフェクトフラグを折る
			}
		}
		if(dflg>=1){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //消滅エフェクト
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
			DrawRotaGraph( (int)Enemy_5.x, (int)Enemy_5.y+60, 2.5, 0.0, Effect[j], TRUE ); //被弾エフェクト
			j++;
			if(j>=6){
				j=0;
				eflg=0;//被弾エフェクトフラグを折る
			}
		}
		if(dflg>=1){
			for(k=0; k<6; k++){
				DrawRotaGraph( x, y, 2.5, 0.0, Effect[k], TRUE ); //消滅エフェクト
			}
			dflg=0;
		}
	}
	return;
}

//回復アイテム制御
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

//敵機弾丸制御
void eBulletControl()
{
	int j, flg=1;//敵が消滅したときに弾丸を生成させないためのフラグ

	for(j=0; j<PBULLET_Y; j++){
		//５周期で弾丸を発射
		double Ans1 = (7.0/difficult);
		int Ans2 = (int)Ans1;
		if(counter%Ans2== 0){
			if(Enemy.hp > 0 && flg && Enemy.flag){
				if(eBullet[0][j].Flag == 0){
					eBullet[0][j].Flag = 1;
					eBullet[0][j].x = Enemy.x; //位置情報同期
					eBullet[0][j].y = Enemy.y;
					break; //修正後のbreakの位置
				}
			}
			//break; ←ここでbreakすると単発発射だけになる
		}
	}
	for(j=0; j<PBULLET_Y; j++){
		if(eBullet[0][j].Flag == 1){
			eBullet[0][j].y += 10; //弾丸を移動させる
			if(eBullet[0][j].y > WNDH){	
				eBullet[0][j].Flag = 0;	//画面外に弾丸が出たらフラグを折る
			}
		}
	}
		
	return;
}

//螺旋ショット
void eBulletControl_1()
{
	int j;//今まで何発撃ったかを格納
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

//ロックオン
void eBulletControl_2(){
	int j;
	double s;

	if(Enemy_4.hp > 0 && Enemy_4.y > 200){
		for(j=0; j<PBULLET_Y; j++){
			if((Enemy_4.hp > 0) /*||*/&& Enemy_4.flag == 1){
				if(eBullet_4[0][j].Flag == 0){
					eBullet_4[0][j].Flag = 1;
					s = atan((Enemy_4.y - Player.y)/(Enemy_4.x - Player.x));//角度計算
					//	if(Enemy_4.x > Player.x) s = atan((Enemy_4.y - Player.y)/(-Enemy_4.x + Player.x));
					if(Enemy_4.x == Player.x) s = 0;
					eBullet_4[0][j].vx = (10*difficult)*cos(s);
					eBullet_4[0][j].vy = (10*difficult)*sin(s);//速度
					eBullet_4[0][j].x = Enemy_4.x ;
					eBullet_4[0][j].y = Enemy_4.y + 10;
					if(Enemy_4.x > Player.x){
						eBullet_4[0][j].vx = -(10*difficult)*cos(s);
						eBullet_4[0][j].vy = -(10*difficult)*sin(s);//速度
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

//ボス球その1
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
					s = atan((Enemy_5.y - Player.y)/(Enemy_5.x - Player.x));//角度計算
					if(Enemy_5.x == Player.x) s = 0;
					eBullet_6[0][i].vx = (10*difficult)*cos(s);
					eBullet_6[0][i].vy = (10*difficult)*sin(s);//速度
					eBullet_6[0][i].x = Enemy_5.x + 30;
					eBullet_6[0][i].y = Enemy_5.y + 10;
					if(Enemy_5.x > Player.x){
						eBullet_6[0][i].vx = -(10*difficult)*cos(s);
						eBullet_6[0][i].vy = -(10*difficult)*sin(s);//速度
					}
				}
				
				if(eBullet_7[0][i].Flag == 0){
					eBullet_7[0][i].Flag = 1;
					s = atan((Enemy_5.y - Player.y)/(Enemy_5.x - Player.x));//角度計算
					if(Enemy_5.x == Player.x) s = 0;
					eBullet_7[0][i].vx = (10*difficult)*cos(s);
					eBullet_7[0][i].vy = (10*difficult)*sin(s);//速度
					eBullet_7[0][i].x = Enemy_5.x;
					eBullet_7[0][i].y = Enemy_5.y + 10;
					if(Enemy_5.x > Player.x){
						eBullet_7[0][i].vx = -(10*difficult)*cos(s);
						eBullet_7[0][i].vy = -(10*difficult)*sin(s);//速度
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

//その2
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
				eBullet_5[0][i].y += 10; //弾丸を移動させる
				if(eBullet_5[0][i].y > 600 || eBullet_5[0][i].x > WNDW-135 || eBullet_5[0][i].x < 0 || eBullet_5[0][i].y < 0){	
					eBullet_5[0][i].Flag = 0;	//画面外に弾丸が出たらフラグを折る
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

//敵機弾丸描画
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

//FPS表示関数(奈良作)
void FpsTimeFunction()
{
	static int FpsTime[2]={0,},FpsTime_i = 0;
	static double Fps = 0.0;
	int Red = GetColor(255,0,0);

	if(FpsTime_i == 0) {
		FpsTime[0] = GetNowCount();	/* Fpsを測定 */
	}
	if(FpsTime_i == 59){							/*Fpsを測定*/
			FpsTime[1] = GetNowCount();
			Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 60.0f); /* Fpsの計算 */
			FpsTime_i = 0;
	}else{
		FpsTime_i++;
	}
	if(Fps != 0){
		DrawFormatString(730,580,Red,"FPS %.1f",Fps);// 表示
	}

	return ;
}

//カウントダウン
void CountFunction(int OldTime){
	int Time, NowTime; //残り時間保存用
	int Red = GetColor(255,0,0);

		Time = GetNowCount();//現在の時間取得
		NowTime = Time - OldTime; // 何フレーム経過したか時間を得る
		if(stageflg>=1){
			RemainingTime = (int)((StageTime2-NowTime/*-StopTime-Stage1RemainingTime*/+StopTime+(Stage1RemainingTime*1e3))/1e3);
		}else{
			RemainingTime = (int)((StageTime1-(NowTime-StopTime))/1e3);
		}
		SetFontSize( 24 ) ; //フォントサイズ変更
		DrawFormatString(670,550,Red,"Time %ds", RemainingTime);//出力

		if(RemainingTime>=1 && restartflg==1){
			restartflg=0;
		}
	return;
}

//スコア表示(奈良作)
int ScoreShow()
{
	static int flg = 1,flg_1 = 1,flg_2 = 1; //生きてる間 1 しんだら 0
	static int flg_4 = 1,flg_5 = 1;
	if(Enemy.hp > 0) flg = 1;
	if(Enemy.hp < 0 && flg == 1){
		Score += 1000;
		flg = 0; //倒されたとき加算
	}
	if(Enemy_1.hp > 0) flg_1 = 1;
	if(Enemy_1.hp < 0 && flg_1 == 1){
		Score += 1000;
		flg_1 = 0; //倒されたとき加算
	}
	if(Enemy_2.hp > 0) flg_2 = 1;
	if(Enemy_2.hp < 0 && flg_2 == 1){
		Score += 1000;
		flg_2 = 0; //倒されたとき加算
	}
	if(Enemy_4.hp > 0) flg_4 = 1;
	if(Enemy_4.hp < 0 && flg_4 == 1){
		Score += 1000;
		flg_4 = 0; //倒されたとき加算
	}
	if(Enemy_5.hp > 0) flg_5 = 1;
	if(Enemy_5.hp < 0 && flg_5 == 1){
		Score += 1000;
		flg_5 = 0; //倒されたとき加算
	}
	SetFontSize( 20 ) ; //フォントサイズ変更
	DrawFormatString(675,580,RGB(0,0,255),"Score %5d",Score);
	return Score;
}

//HP表示(奈良作)
void ShowMyHp()
{
	if(stageflg<=0){
		SetFontSize( 36 ) ; //フォントサイズ変更
		DrawFormatString(670,10,RGB(0,0,255),"StageⅠ");
	}else if(stageflg>=1){
		SetFontSize( 36 ) ; //フォントサイズ変更
		DrawFormatString(670,10,RGB(0,0,255),"StageⅡ");
	}
	SetFontSize( 36 ) ; //フォントサイズ変更
	DrawFormatString(700,350,RGB(0,0,255),"HP %d",Player.hp);	
	return ;
}

//メニュー計算
int MenuCreate()
{
	//メニュー項目
	Menu_t MenuType[5] = {
		{ 100,250,""},
		{ 100,300,"Play"},
		{ 100,350,"Config"},
		{ 100,400,"Hlep"},
		{ 100,450,"Exit"},
	};

	if(Key[KEY_INPUT_DOWN] == 1 ){ //下が押された時だけ
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
		SelectNum = (SelectNum + 1)%5;
		if(SelectNum==0){
			SelectNum=1;
		}
	}
	if(Key[KEY_INPUT_UP] == 1){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
		SelectNum = (SelectNum + 4)%5;
		if(SelectNum==0){
			SelectNum=4;
		}
	}
	if(Key[KEY_INPUT_RETURN/*SPACE*/] == 1 && SelectNum != 0){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
		return SelectNum;
	}

	for(int i=0;i<5;i++){//メニューの項目数のループ

		if(i == SelectNum){ //処理内容が選択番号と同じか調べる
			MenuType[i].x = 100;
		}else{
			MenuType[i].x = 150;
		}
	}
	SetFontSize( 90 ) ; //フォントサイズ変更
	DrawFormatString(200,50,RGB(0,0,255),"Shooting");
	for(int i=0;i<5;i++){
		SetFontSize( 36 ) ; //フォントサイズ変更
		DrawFormatString(MenuType[i].x,MenuType[i].y,GetColor(255,255,255),MenuType[i].name);
	}	
	return -1;
}

//コンフィグ処理
int Config()
{
	Menu_t ConfigType[5] = {
		{ 300,250,""},
		{ 300,300,"easy"},
		{ 300,350,"normal"},
		{ 300,400,"hard"},
		{ 300,450,"Return to tile"},
	};
	if(Key[KEY_INPUT_DOWN] == 1 ){ //下が押された時だけ
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
		CSelctNum = (CSelctNum + 1)%5;
		if(CSelctNum==0){
			CSelctNum=1;
		}
	}
	if(Key[KEY_INPUT_UP] == 1){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
		CSelctNum = (CSelctNum + 4)%5;
		if(CSelctNum==0){
			CSelctNum=4;
		}
	}
	if(Key[KEY_INPUT_RETURN] == 1 && CSelctNum != 0){
		PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
		return CSelctNum;
	}

	for(int i=0;i<5;i++){//メニューの項目数のループ
		if(i == CSelctNum){ //処理内容が選択番号と同じか調べる
			ConfigType[i].x = 100;
		}else{
			ConfigType[i].x = 150;
		}
	}
	SetFontSize( 90 ) ; //フォントサイズ変更
	DrawFormatString(200,50,RGB(0,0,255),"Shooting");
	for(int i=0;i<5;i++){
		SetFontSize( 36 ) ; //フォントサイズ変更
		DrawFormatString(ConfigType[i].x,ConfigType[i].y,GetColor(255,255,255),ConfigType[i].name);
	}	
	return -1;
}

// タイトルBGM
static void OpningMusic(int Flg)
{ 
	if(Flg == 0) PlaySoundMem(hOP, DX_PLAYTYPE_LOOP,FALSE);//BGM再生
	else{ 
		StopSoundMem(hOP);
	}
}

static void StageBgm(int flg)
{ //ゲーム中BGM
	if(flg >= 1 && (Enemy_2.flag<=0 || Enemy_5.flag<=0)){
		if(CheckSoundMem(hBossBGM)){
			StopSoundMem(hBossBGM);
		}
		PlaySoundMem(hBGM, DX_PLAYTYPE_LOOP,FALSE);//BGM再生
	}
	if(flg >= 1 && (Enemy_2.flag>=1 || Enemy_5.flag>=1)){
		if(CheckSoundMem(hBGM)){
			StopSoundMem(hBGM);
		}
		PlaySoundMem(hBossBGM, DX_PLAYTYPE_LOOP,FALSE);
	}
}

//ステージ制御部
void StageControl()
{
	static int StageGraph;//ロードした画像
	static int bossflg1=-1, bossflg2=-1, flg1=0, flg2=0;
	static char chStr[128], chStr2[128], chStr3[128], chStr4[128];

	//ステージ情報切り替え
	if(stageflg<=0){
		StageGraph = hSTAGE;
	}else if(stageflg==1){
		StageGraph = hSTAGE1;
		stageflg=2;
	}

	//アイテム出現制御
	if(Player.hp<5 && counter%500==0 && Item1.flag<=0){
		Item1.flag=1;
		Item1.x = GetRand(WNDW-160);
		Item1.y = 10;
		Iflg=0;
	}

	//敵機出現制御
	switch(counter%150){
		case 30:
			if(Enemy.flag<=0 && Enemy_5.flag<=0 && Enemy_2.flag<=0){//横移動
				Enemy.flag=1;
				Enemy.x = (WNDW-130)/2;
				Enemy.y = 50;
				Enemy.hp = 5;
				break;
			}
		case 80:
			if(Enemy_1.flag<=0 && Enemy_5.flag<=0 && Enemy_2.flag<=0){ //ドクロ
				Enemy_1.flag=1;
				Enemy_1.x = 10;
				Enemy_1.y = 20;
				Enemy_1.hp = 20;
				break;
			}
		case 130: //ステージ２で追加
			if(stageflg>=1 && Enemy_2.flag <= 0 && Enemy_4.flag<=0 && Enemy_5.flag<=0){//ロックオン
				Enemy_4.flag = 1;
				Enemy_4.x = GetRand(WNDW-160);
				Enemy_4.y = 0;
				Enemy_4.hp = 20;
				break;
			}
	}

	//ボスの出現処理
	if(Enemy_2.flag<=0 && Score>=5000 && stageflg<=0 && bossflg1<=-1){ //ステージ１のボス(螺旋)
		Enemy.flag=0;
		Enemy_1.flag=0;
		Enemy_4.flag=0;
		Enemy_2.flag=1;
		Enemy_2.x = 100;
		Enemy_2.y = 0;
		Enemy_2.hp = 50;
		bossflg1=0;
	}
	if(Enemy_5.flag<=0 && stageflg>=1 && Score>=12000 && bossflg2<=-1){//ステージ２のボス(ボス玉)
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

	if(bossflg1==0 && Enemy_2.hp<=0){ //ステージ１のボスを倒した後の処理
		Stage1RemainingTime = (int)(StageTime1-RemainingTime);
		bossflg1=1;
	}
	if(bossflg2==0 && Enemy_5.hp<=0){ //ステージ２のボスを倒した後の処理
		//通知処理
		Stage2RemainingTime = (int)((StageTime2/1e3)-RemainingTime);
		SetFontSize( 24 ) ; //フォントサイズ変更
		wsprintf(chStr2,"ステージⅠクリアタイム：%ds",Stage1RemainingTime);
		wsprintf(chStr3,"ステージⅡクリアタイム：%ds",Stage2RemainingTime);
		wsprintf(chStr4,"ゲームクリアタイム：%ds", Stage2RemainingTime+Stage1RemainingTime);
		ClearDrawScreen(); //画面クリア
		DrawFormatString(310,200,RGB(0,0,255),"ゲームクリア");
		DrawFormatString(230,250,RGB(0,0,255),chStr2);
		DrawFormatString(230,300,RGB(0,0,255),chStr3);
		DrawFormatString(260,350,RGB(0,0,255),chStr4);
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				break ;	// エラーが発生したらループを抜ける
			}
		}
		ClearDrawScreen(); //画面クリア
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
		restartflg=1;//各フラグ処理
		Player.flg=1;
		Player.hp=0;
		bossflg1=-1;
		bossflg2=-1;
		flg1=0;
		flg2=0;
		Position(); //←ここですべての状態をリセット
		if(restartflg>=1 || Player.flg>=1){//BGMの切り替え
			if(CheckSoundMem(hBGM)){
				StopSoundMem(hBGM);
			}else if(CheckSoundMem(hBossBGM)){
				StopSoundMem(hBossBGM);
			}
		}
	}

	SetDrawArea(0, 0, WNDW-130, WNDH); //描画領域制限
	//画像１枚を上下２枚連続で描画してスクロール
	DrawGraph(0, counter%STAGEH-STAGEH, StageGraph, FALSE);//上
	DrawGraph(0, counter%STAGEH,        StageGraph, FALSE);//下
	SetDrawArea(0, 0, WNDW, WNDH);

	//ステージクリアの処理
	if(bossflg1>=1 && stageflg<=0){//ボスを倒したら次のステージ
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
		//通知処理
		StopTimeBegin = GetNowCount();
		ClearDrawScreen(); //画面クリア
		SetFontSize( 24 ) ; //フォントサイズ変更
		DrawFormatString(300,300,RGB(0,0,255),"ステージⅠクリア");
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				break ;	// エラーが発生したらループを抜ける
			}
		}
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
		Stage1RemainingTime = (int)((StageTime1/1e3)-RemainingTime);
		stageflg=1;
	}
	//ゲームオーバー時の処理
	if((RemainingTime<=0 || (Player.hp<=0 && Player.flg<=0)) && restartflg<=0){
		restartflg=1;//各フラグ処理
		Player.flg=1;
		Player.hp=0;
		bossflg1=-1;
		bossflg2=-1;
		flg1=0;
		flg2=0;
		Position(); //←ここですべての状態をリセット
		//通知処理
		StopTimeBegin = GetNowCount();
		ClearDrawScreen(); //画面クリア
		SetFontSize( 24 ) ; //フォントサイズ変更
		DrawFormatString(320,250,RGB(0,0,255),"ゲームオーバー");
		DrawFormatString(300,300,RGB(0,0,255),"Push the enter key");
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				break ;	// エラーが発生したらループを抜ける
			}
		}
		ClearDrawScreen(); //画面クリア
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
		if(restartflg>=1 || Player.flg>=1){//BGMの切り替え
			if(CheckSoundMem(hBGM)){
				StopSoundMem(hBGM);
			}else if(CheckSoundMem(hBossBGM)){
				StopSoundMem(hBossBGM);
			}
		}
	}

	//タイムした時の処理
	if(Key[KEY_INPUT_SPACE]==1){
		StopTimeBegin = GetNowCount();
		ClearDrawScreen(); //画面クリア
		SetFontSize( 24 ) ; //フォントサイズ変更
		DrawFormatString(300,300,RGB(0,0,255),"再開はエンターキー");
		while(CheckHitKey(KEY_INPUT_RETURN) == 0){
			// メッセージ処理
			if( ProcessMessage() == -1 )
			{
				break ;	// エラーが発生したらループを抜ける
			}
		}
		StopTimeEnd = GetNowCount();
		StopTime += StopTimeEnd-StopTimeBegin;
	}

	return;
}

//メイン関数
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	int RefreshTime; //現在の時間

	ChangeWindowMode(TRUE); //ウィンドウモードに設定
	SetGraphMode(WNDW, WNDH, 32); //ウィンドウサイズ800*600に設定
	SetMainWindowText("Shooting"); //タイトル
	SetWindowIconID(IDI_ICON0); //アイコン
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に設定
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;	// エラーが起きたら直ちに終了
	}
	//フォントロード
	LPCSTR font_path = "Font/mofuji.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	} else {
		// フォント読込エラー処理
		MessageBox(NULL,"フォント読込失敗","",MB_OK);
	}
	
	DataLoad(); //各データ読み込み
	Position(); //各構造体値の初期化

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

	//while(メッセージ処理, キーの入力状態を更新する)
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

		ClearDrawScreen(); //画面クリア
		//ChangeFont("モフ字"); //フォント変更
		if(Cflg>=1){
			switch(Config()){
				case 1:
					difficult=0.5;
					StageBgm(Mflg);
					OpningMusic(Mflg); //タイトルBGM
					break;
				case 2:
					difficult=1.0;
					StageBgm(Mflg);
					OpningMusic(Mflg); //タイトルBGM
					break;
				case 3:
					difficult=2.0;
					StageBgm(Mflg);
					OpningMusic(Mflg); //タイトルBGM
					break;
				case 4://設定を保存しタイトルへ戻る
					Position();
					break;
			}
		}else if(Mflg <= 0 && Cflg<=0){
			OpningMusic(Mflg);
			switch(MenuCreate()){
				case 1: //ゲーム開始
					RefreshTime = GetNowCount(); //起動した時間を取得
					Mflg = 1;
					StageBgm(Mflg);
					OpningMusic(Mflg); //タイトルBGM
					break;
				case 2: //コンフィグ
					if(Cflg<1){
						Cflg=1;
					}
					break;
				case 3: //ヘルプ
					ClearDrawScreen(); //画面クリア
					//ヘルプ画面の描画
					DrawGraph(0, 0, hHelp, TRUE);
					while(CheckHitKey(KEY_INPUT_ESCAPE) == 0){
						// メッセージ処理
						if( ProcessMessage() == -1 )
						{
							break ;	// エラーが発生したらループを抜ける
						}
					}
					Mflg=0;
					PlaySoundMem(Select,DX_PLAYTYPE_BACK);//効果音再生
					break;
				case 4: //終了
					DxLib_End();
					return 0;
			}
		}else if(Mflg>=1 && Cflg<=0){

				OpningMusic(Mflg);
				StageBgm(Mflg);

				StageControl(); //ステージ描画
		
				PlayerControl();	//自機制御

				pBulletControl();	//自機弾丸制御

				pBulletDraw();	//自機弾丸描画

				EnemyControl();	//敵機制御

				EnemyControl_1();

				EnemyControl_2();

				EnemyControl_3();

				EnemyControl_4();
	
				eBulletControl();	//敵機弾丸制御

				eBulletControl_1();

				eBulletControl_2();

				eBulletControl_3();

				eBulletControl_4();

				eBulletDraw();	//敵機弾丸描画

				eBulletDraw_1();

				eBulletDraw_2();

				eBulletDraw_3();

				eBulletDraw_4();

				eBulletDraw_5();

				ItemControl();
			//	FpsTimeFunction();	//FPS表示

				CountFunction(RefreshTime);	//カウントダウン表示

				ScoreShow(); //スコア表示

				ShowMyHp(); //HP表示

				counter++; //カウンター更新
		}

		ScreenFlip(); //裏画面を表画面に反映

		if(Key[KEY_INPUT_ESCAPE]==1){
			Position();//←ここですべての状態をリセット
			restartflg=1;//各フラグ処理
			if(restartflg>=1 || Player.flg>=1){//BGMの切り替え
				if(CheckSoundMem(hBGM)){
					StopSoundMem(hBGM);
				}else if(CheckSoundMem(hBossBGM)){
					StopSoundMem(hBossBGM);
				}
			}
		}

	}
  DxLib_End();    // DXライブラリ終了処理
  return 0;
}