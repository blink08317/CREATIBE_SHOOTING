//�J�E���^
int counter=0; 

//�c�莞�ԕۑ�
int RemainingTime=15;
int StageTime;
int StopTimeBegin=0;//�^�C���J�n���̎���
int StopTimeEnd=0; //�^�C���I�����̎���
int StopTime=0; //�^�C�����Ă������v����
int Stage1RemainingTime=0; //�X�e�[�W�N���A�ɂ�����������
int Stage2RemainingTime=0;

//�X�R�A�ۑ�
int Score = 0;

// ���j���\�֐�
int Mflg = 0; 
int SelectNum = 0;//���ݑI�����Ă���ԍ�

// �R���t�B�O�֘A
int Cflg = 0;
int CSelctNum = 0;

//�X�e�[�W�t���O
int stageflg=0, restartflg=0;

//�A�C�e���t���O
int Iflg=0;

int Key[256]; // �L�[��������Ă���t���[�������i�[����
double difficult=1.0; //��Փx(������Normal)

//�V���A���ʐM�֘A
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

//�f�[�^�n���h���i�[�p�ϐ�
int hPlayer;  //���@�̃f�[�^�n���h��
int hEnemy;
int hEnemy_1;//�G�@�̃f�[�^�n���h��
int hEnemy_2;
int hEnemy_3;
int hEnemy_4;
int hEnemy_5;
int hpBullet[2]; //���@�̒e�ۗp�f�[�^�n���h��
int heBullet[2]; //�G�@�̒e�ۗp�f�[�^�n���h��
int heBullet_2[2];
int heBullet_3[2];
int heBullet_4[2];
int heBullet_5[2];
int Effect[6];//��e�t�F�N�g�p�f�[�^�n���h��
int EffectMusic;//���ʉ�
int hBGM; //BGM
int hOP;//OP���y
int hBossBGM;
int Select;
int hSTAGE, hSTAGE1; //�w�i
int hHelp; //�w���v�p
int hItem;

void DataLoad()
{
	// �摜�̃��[�h
	hPlayer = LoadGraph( "�摜/player00.png" ); //���@�̉摜��荞��
	hEnemy = LoadGraph( "�摜/enemy00.png" ); //�G�@�̉摜��荞�� ���ړ�
	hEnemy_1 = LoadGraph("�摜/sculler.png"); //�h�N�������
	hEnemy_2 = LoadGraph("�摜/enemy03.png"); //����
	//hEnemy_3 = LoadGraph("�摜/sculler.png");
	hEnemy_4 = LoadGraph("�摜/enemy01.png"); //���b�N�I��
	hEnemy_5 = LoadGraph("�摜/enemy04.png"); //���X�{�X+72
	hpBullet[0] = LoadGraph( "�摜/�e00.png"); //�@���@�̒e�̎�荞��
	heBullet[0] = LoadGraph( "�摜/�e00.png"); //�@�G�@�̒e�̎�荞��
	heBullet_2[0] = LoadGraph( "�摜/�e00.png");
	heBullet_4[0] = LoadGraph( "�摜/�e00.png");
	LoadDivGraph( "�摜/Explosion.png" , 7, 7 , 1 , 40 , 40 , Effect );//�����G�t�F�N�g��荞��
	hSTAGE = LoadGraph( "�摜/stage_green.png" ); // �w�i��荞��
	hSTAGE1 = LoadGraph( "�摜/stage_universe.png" );
	hHelp = LoadGraph("�摜/help.png");
	hItem = LoadGraph("�摜/item_heart.png");
	//���y�̃��[�h
	EffectMusic = LoadSoundMem("�T�E���h/1up.wav");
	hBGM = LoadSoundMem("�T�E���h/play.mp3");
	hBossBGM = LoadSoundMem("�T�E���h/boss.mp3");
	hOP = LoadSoundMem("�T�E���h/op.mp3");
	Select = LoadSoundMem("�T�E���h/beam1.wav");
	return;
}