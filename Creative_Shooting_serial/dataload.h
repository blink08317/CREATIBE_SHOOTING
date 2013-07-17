//カウンタ
int counter=0; 

//残り時間保存
int RemainingTime=15;
int StageTime;
int StopTimeBegin=0;//タイム開始時の時間
int StopTimeEnd=0; //タイム終了時の時間
int StopTime=0; //タイムしていた合計時間
int Stage1RemainingTime=0; //ステージクリアにかかった時間
int Stage2RemainingTime=0;

//スコア保存
int Score = 0;

// メニュ―関数
int Mflg = 0; 
int SelectNum = 0;//現在選択している番号

// コンフィグ関連
int Cflg = 0;
int CSelctNum = 0;

//ステージフラグ
int stageflg=0, restartflg=0;

//アイテムフラグ
int Iflg=0;

int Key[256]; // キーが押されているフレーム数を格納する
double difficult=1.0; //難易度(初期はNormal)

//シリアル通信関連
char In[1];
DWORD lRead;
int  itemp;
int Ret;
HANDLE hPort;

/*
char SndBuf[32];
char RcvBuf[32];
DWORD dwSize;
*/

//データハンドル格納用変数
int hPlayer;  //自機のデータハンドル
int hEnemy;
int hEnemy_1;//敵機のデータハンドル
int hEnemy_2;
int hEnemy_3;
int hEnemy_4;
int hEnemy_5;
int hpBullet[2]; //自機の弾丸用データハンドル
int heBullet[2]; //敵機の弾丸用データハンドル
int heBullet_2[2];
int heBullet_3[2];
int heBullet_4[2];
int heBullet_5[2];
int Effect[6];//被弾フェクト用データハンドル
int EffectMusic;//効果音
int hBGM; //BGM
int hOP;//OP音楽
int hBossBGM;
int Select;
int hSTAGE, hSTAGE1; //背景
int hHelp; //ヘルプ用
int hItem;

void DataLoad()
{
	// 画像のロード
	hPlayer = LoadGraph( "画像/player00.png" ); //自機の画像取り込み
	hEnemy = LoadGraph( "画像/enemy00.png" ); //敵機の画像取り込み 横移動
	hEnemy_1 = LoadGraph("画像/sculler.png"); //ドクロちゃん
	hEnemy_2 = LoadGraph("画像/enemy03.png"); //螺旋
	//hEnemy_3 = LoadGraph("画像/sculler.png");
	hEnemy_4 = LoadGraph("画像/enemy01.png"); //ロックオン
	hEnemy_5 = LoadGraph("画像/enemy04.png"); //ラスボス+72
	hpBullet[0] = LoadGraph( "画像/弾00.png"); //　自機の弾の取り込み
	heBullet[0] = LoadGraph( "画像/弾00.png"); //　敵機の弾の取り込み
	heBullet_2[0] = LoadGraph( "画像/弾00.png");
	heBullet_4[0] = LoadGraph( "画像/弾00.png");
	LoadDivGraph( "画像/Explosion.png" , 7, 7 , 1 , 40 , 40 , Effect );//爆発エフェクト取り込み
	hSTAGE = LoadGraph( "画像/stage_green.png" ); // 背景取り込み
	hSTAGE1 = LoadGraph( "画像/stage_universe.png" );
	hHelp = LoadGraph("画像/help.png");
	hItem = LoadGraph("画像/item_heart.png");
	//音楽のロード
	EffectMusic = LoadSoundMem("サウンド/1up.wav");
	hBGM = LoadSoundMem("サウンド/play.mp3");
	hBossBGM = LoadSoundMem("サウンド/boss.mp3");
	hOP = LoadSoundMem("サウンド/op.mp3");
	Select = LoadSoundMem("サウンド/beam1.wav");
	return;
}