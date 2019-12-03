//��Ÿ -  Bitmap  -  DC -  RECT  - bool  - int  - char  - �Լ� 
 
//��2�� ���ٰ� ��1�� ���ư��� ���� �ִ� ���� �� 1���� �� �Ҹ�Ǿ �ٽ� ������ ����. �� 2�� �� �Ŀ� R�� ������ ����. 
 
#define WINVER 0x0501
#define MAXSTAGE 3
#define PI 3.141592


#include <windows.h>
#include <wingdi.h>
HWND hWndMain;
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include "resource.h" 

//#pragma comment ( lib, "Msimg32.lib" )



LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="For Supo";

//���� 
HDC MemDC,hdc,DrawDC;

HBITMAP CharacterBitmap,TileBitmap,TitleBitmap,BidulgiBitmap,BulletBitmap,MenuBitmap,OldBitmap,BackBitmap;
HBITMAP DragonBitmap,ItemBitmap,TextBoxBitmap,NPCBitmap,MonsterBitmap,MonsterBitmap2;
HBITMAP bkBlackBitmap,bkMoonBitmap,bkFogBitmap,bkSeaBitmap;


//�̵� & ���� 
bool bjump=false;
bool bGoRight=true;
bool bRmove;
bool bLmove;
int accmove=0;
int gravity=0;

//�þ� 
int mapmoving=0;
int ymoving=0;
int sight=0; // �� ������ ���� ���°�  
int nPlayermoving=0; 
 
 
//��Ʈ�� �׸��� 
void DrawBitmap(HDC MemDC,int drawx,int drawy,int sizex,int sizey,int startx,int starty,HBITMAP hBit);
void StretchDrawBitmap(HDC MemDC,int Stretchdrawx,int Stretchdrawy,int Stretchsizex,int Stretchsizey,HBITMAP hBit,int drawx ,int drawy,int sizex,int sizey);
void PTBackGround();



//�÷��̾� 
RECT Player_rt; // �÷��̾� ��ǥ 
int fpx=0; // ���������� ù��° �÷��̾� ��ǥ 
int fpy=0; 
int nPlayeranimate=1;
char cPlayerstate; 

void Playermove();

//�÷��̾�-���� 
bool bPlayerdie = false;

bool bAttack = false;
bool bAttackable = true;

bool bKnockl = false;
bool bKnockr = false;
bool bZhonya = false;

int Dmg = 15;
int Playerhealth = 100;
int MaxPlayerhealth= 100;
int combo=0;
int comboI=0;


char cNumweapon=1;

//�� ���Ÿ����� 
RECT Bulletrt[16]; 
bool bBulletRight[16];
bool bBulletAK[16];
int MXakl[16];
char cBulletstate[16];
void CreateSAK();
void SAK();

//���Ÿ����� 
POINT Functionpt;
bool bFptready = false; 
bool bFungoright;  //�¿� 

int nWeapontype=0; 
int nLinestand = 3; //���� 








RECT Function4rt[500];//���� ��

RECT Turretrt;
bool bFunction4continue = false;  //���Լ� �������϶� 
bool bFunction4atk; //���ĸ±� ���� 
bool bFun4go=false;
int nMaxFun4= 500; //�Ÿ� �ִ�ġ 
int nFunctioncount4 = 4;
int nFun4count=0;
void Fourthfunction();
void Fourthfunctionset();

POINT Functionpt4;
bool bFpt4ready = false;
bool bFun4goright = true;

RECT Function3rt[1366*1/4];//���� ��
RECT Function3linert;
 
bool bFunction3continue = false;  //�����Լ� �������϶�
bool bFunction3ready = false; 
int nFunctioncount3 = 4;
int nFun3=0;
int nFun3end = 0;
void Thirdfunction();
void Thirdfunctionset();


RECT Function2rt[500];//���� ��
bool bFunction2continue = false;  // �Լ� �������϶� 
bool bFunction2atk; //���ĸ±� ���� 
bool bCharge =false; //���.... 
int nMaxFun2= 500 ; //�Ÿ� �ִ�ġ 
int nFunctioncount2 = 4;
int nFunctioncount2real=0;
void Secondfunction();
void Secondfunctionset();
void Realsecondfunction();


RECT Function1rt[500]; //�� ���� 
bool bFunction1continue = false; // �Լ� �������϶� 
bool bFunction1atk; // ���ĸ±� ���� 
int nMaxFun1 = 250; //�Ÿ� �ִ�ġ 
int nFunctioncount1 = 4;
void Firstfunction();
void Firstfunctionset();



//���׶��
HRGN Guardrgn,Guarddrawrgn;
int nShieldcount = 0;
bool bGuardon = false; 
void Shield();
void Shielddraw();


//���â 

RECT Funbackrt;
void Printfun();
void Readyfun();







//�������� ����
//�� 
RECT rt;// �� 
RECT Exitrt; //�ⱸ 
int nNumstage; //�������� ��ȣ                    
int ** currentstage;//���� �������� ���� 
int nScreen;  //ȭ��ũ��
int mapx,mapy; // �� �ִ� x��ǥ y��ǥ 
void Scanmap(); // �� �ҷ����� 
void DrawScreen(HDC MemDC); //�ʱ׸��� 
void Getstage(); 

void MapMoving();  //�� �� �̵� 
 

//�浹�� 
RECT ** Hitrt;  // ���� 

RECT ** Siderrt;  //������  
RECT ** Sidelrt;



void Hitbywall();  //�����浹 
bool RightCollision; // ���������� �ɾ �� 
bool LeftCollision; // �������� �ɾ ��  
bool UpCollision; // ���� ���� �� 
bool DownCollision; // ������ �� 
void Hitbyrgn();
HRGN **St1rgn , **St2rgn , **St3rgn , **St4rgn , **St5rgn , **St6rgn , **St7rgn , **St8rgn;
HRGN Stairrgn(int nStairnum,  int nLeft,  int nBottom);
POINT **Stairpt1,**Stairpt2,**Stairpt3,**Stairpt4,**Stairpt5,**Stairpt6,**Stairpt7,**Stairpt8;
bool bInrgn;

//UI
void DrawUI(); 






//�� �̵� ���� �ǰ� ���  - ������. 
RECT Goort[128];
RECT Mobfindrt[128];
RECT Mobbulletrt[128][16];
bool bMobatkright[128][16];
bool bMobdie[128];
bool bmgoright[128]={false};
bool bMobatk[128]={false};
bool bMobatkwait[128]={false};
bool bMobbulletfly[128][16]={false};
int Mobhealth[128];
int Mobdmg = 8;
int Mobgravity[128]={0};
int Mobakl[128][16];
int Mobanimate/*[�����Ӱ���]*/[128]={0};
char mobnum4040=0;
void Killgoo();
void Mobatk();
void Mobatkhelp();
void Mobmove();



RECT Dragonrt;
RECT Dragonfindrt;
bool bDragonable = false;
bool bDragondie = false; 
bool bDragonatk = false;
bool bDragongoright = false;
int  Dragonhealth  = 1000;
int Dragondmg = 15; 
void Dragonangry();

void Dragonmove();
int Dcount=1;
int DcountI=0;
int Dlcount=1;
int DlcountI=0;

void Playermobwork();



RECT atkrt;
RECT Mobrt[128];
     //bool bMobdie[128]={true};
bool bNum5right[128]={false};
bool bNum6right[128]={false};
bool bNum7right[128]={false};
int Animatenum5[128]={0};
int Animatenum6[128]={0};
int Animatenum7[128]={0};
void Mobangry();





//���� ���� 
POINT Zeropt;
HRGN Widingrgn;
HRGN OldWidingrgn;
bool bGridonoff=false;
int nRgncount = 0;
void Skillgrid();



 

//���̵��ξƿ� 
POINT ZeroptI;
HRGN WidingrgnI;
HRGN Bkrgn;
HRGN OldWidingrgnI;
bool bFadeonoffI=false;
bool bFading = false;
int Fadecount;
int RgncountI = 0;
void Fadein(int nValue);
void Fadedraw();












//---------------------------//


// ���� ���� ��(?)
bool bPlaygame;
char cKeystate; //���� ���� ����  
char cSelectstate=0;  // ���� ���� ������ �����ϴ� ���� ���� ��  
void DrawMenu(); 
void DrawTitle();
void TransBitBlt(HDC hdc, int x, int y, int width,int height,HDC MemDC,int mx,int my, COLORREF clrMask);
int nAdjustsight=0;
bool bSightright=true;
void DrawESC();
RECT NPCrt[16];
int nNPCnum;

//��...��? 
TCHAR *Sentencestr;
HFONT hFont,OldFont;
bool bText=false;
bool bTextnext=false;  
int nTextcount = 0;
void DrawText();
void DrawTexthelp();


int num3=0;
int num4=0;
int num5=0;
int num6=0;
int num7=0;







//�����̵� 
  
  bool bSettomove = false;
  bool bAmoving = false;
  int nMcount = 0;
  void Automove(RECT Mrt ,bool bRight, int nRange);


//���� 
void Soundout();



//�������� ���Ǹ� ���� 
void testmode();



// �ڵ�κ� --------------------------- // 

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
   


    /* 
	hWnd=CreateWindow(lpszClass,lpszClass,WS_MAXIMIZE,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	*/	
	
// ȭ�� ũ�� ���� 
    hWnd = CreateWindow(lpszClass, lpszClass, WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 
        GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, (HMENU)NULL, hInstance, NULL);
      	
	ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0))
    {
	 TranslateMessage(&Message);
	 DispatchMessage(&Message);
	}
	return Message.wParam;
}
  
        



LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{

    

	PAINTSTRUCT ps;


 	switch(iMessage){
 	
  
    
    
     case WM_CREATE:
         hWndMain=hWnd;
       
         hdc=GetDC(hWndMain); 
         
         
         CharacterBitmap=LoadBitmap(g_hInst,MAKEINTRESOURCE(Character));
         TileBitmap=LoadBitmap(g_hInst,MAKEINTRESOURCE(Tile3));
         TitleBitmap=LoadBitmap(g_hInst,MAKEINTRESOURCE(Title));
         BidulgiBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(Bidulgi));
         BulletBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(Bullet));
         bkBlackBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(bkBlack));
         bkSeaBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(bkSea));
         bkMoonBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(bkMoon));
         DragonBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(Dragon));
    //     ItemBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(Item));
    //     NPCBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(NPC));
         TextBoxBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(TextBox));
         MenuBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(Menu));
       
         bkFogBitmap= LoadBitmap(g_hInst,MAKEINTRESOURCE(bkFog));
  //       MonsterBitmap = LoadBitmap(g_hInst,MAKEINTRESOURCE(Earthshaker));
  //       MonsterBitmap2 = LoadBitmap(g_hInst,MAKEINTRESOURCE(ShadowBat));
               
         bPlaygame=false;
         cKeystate=0;
         
         nNumstage=0;
		 Getstage();
		 
         SetTimer(hWnd,1,25,NULL);

         SetTimer(hWnd,21,500,NULL);
 	    
         
          return 0;

 	     
 	case WM_TIMER: //����� ��ȣ 0,1,2,21,22,31. 
      
      // ȭ�� ũ�� ����
    
      nScreen=(1366/3)+(1366%3);
      
      TransparentBlt(MemDC,1366,768,1024,768,DrawDC,20,40,10,20,RGB(0,0,0));
      
          if(!bPlaygame)
          {    
              switch(cKeystate)
              {
                  
                  case 0:  //Ÿ��Ʋ 
                       if(cSelectstate==0) //�����ϱ� 
                       {
                         if(GetKeyState('D')&0x8000)
                         {
                           bPlaygame=true;
                         
                         }
                       }
                       
                       else if(cSelectstate==1) //�̾��ϱ�
                       {
                        
                       }
                       
                       else if(cSelectstate==2)  //���� 
                       {
                         if(GetKeyState('D')&0x8000)
                         {
                           PostQuitMessage(0);
                           return 0;
                         }
                       }
                       
                        
                      break;
                  
                  
                  case 1: //�κ��丮 
                       
                       break;
                       
                  case 2:  //NPC�� ���ɶ� 
                  
                       break;
                  
                  case 3:  // ���������� ESC
                       
                       
                        
                       
                       break;
              }
          }      
                               
            
      
          else if(bPlaygame)
          {  
           switch(wParam)
           {
                 case 1: //���� ���� 
             if(bText)
             {
              DrawTexthelp();
           
                    
             }                
             if(!bText)
             {       
               
                             //�������� ������ 
                        if(!bFading&&!bAmoving&&!bPlayerdie&&!(GetKeyState(VK_RIGHT)&0x8000)&&(GetKeyState(VK_LEFT)&0x8000))
                        {
                                   
                             bGoRight=false;
                             nPlayeranimate--;
                            cPlayerstate=1;
                             
                             
                              if(accmove>-3)
                              accmove--;
                            
                           
                              bLmove  = true;
                              if(bLmove)
                              {
                               Player_rt.left+=accmove*2;
                               Player_rt.right = Player_rt.left+40;
                              }
                           }
                            
                            //���������� ������ 
                            if(!bFading&&!bAmoving&&!bPlayerdie&&(GetKeyState(VK_RIGHT)&0x8000)&&!(GetKeyState(VK_LEFT)&0x8000))
                            {
                                                                                      
                              bGoRight=true;
                              nPlayeranimate++;
                              cPlayerstate=2; 
                             
                            
                               if(accmove<3)
                                accmove++; 
                               
                             
                               bRmove = true;
                               if(bRmove)
                               {
                                Player_rt.left+=accmove*2;
                                 Player_rt.right = Player_rt.left+40;
                                }
                             }
                            
                          /*   if(!bPlayerdie&&!(GetKeyState(VK_RIGHT)&0x8000)&&!(GetKeyState(VK_LEFT)&0x8000)){
                              
                              if(accmove<0)
                              accmove++;
                              
                              if(accmove>0)
                              accmove--;
                              
                              }*/
                             
                      
                     
                      //���� ���� 
                            if(!bPlayerdie&& (GetAsyncKeyState('W')&0x0001) )
                            {
                               if( nLinestand>0 && !bFunction1continue && !bFunction2continue && !bFunction3continue && !bFunction4continue )
                               {
                                nLinestand--;
                               }                                   
                            } 
                            if(!bPlayerdie&& (GetAsyncKeyState('Q')&0x0001) )
                            {
                               if( nLinestand<5 && !bFunction1continue && !bFunction2continue && !bFunction3continue &&  !bFunction4continue )
                               {
                                nLinestand++; 
                               }
                            }
                            
                            
                             //��Ű 
                             if(!bPlayerdie&&GetAsyncKeyState(VK_UP)&0x0001)
                             {
                             
                             
                             
                             //�ⱸ 
                              RECT wastert;//�ӽ� 
                              if(IntersectRect(&wastert, &Player_rt, &Exitrt))
                              { 
                               nNumstage++;
                               PlaySound(NULL,NULL,0);
                               Getstage();
                               }                             
                          
                             }  
                             
                             
                             if(!bPlayerdie&&GetKeyState(VK_UP)&0x8000)
                             {
                               cPlayerstate=3;
                             
                             }
                             
                             //�Ʒ�Ű 
                             if(!bPlayerdie&&GetKeyState(VK_DOWN)&0x8000)
                             {
                                                                            
                                                                         
                                                                         
                                                                         
                                                                         
                                                                         
                                                                         
                                                                         
                                                                         
                              if(gravity!=0)
                              cPlayerstate=4;
                             }
                             
                             
                            
                              
                             
                             
                            // �� �� ��� Ű 
                            
                            
                             
                             //�����Ѵ�  ����.
                           
                         
                             if( (GetKeyState('E')&0x8000) && (nWeapontype==1) && !bFunction2continue  && !bFunction3continue  )
                             {
                               bFunction3ready = false;                     
                               Firstfunctionset();
                               Firstfunction();
                                                 
                             }
                          
                             
                             
                             if(!(GetKeyState('E')&0x8000))
                             {
                              
                              nFunctioncount1=nMaxFun1-10;      
                                            
                             }
                                     //�Ÿ� ����. 
                           if(bFunction1continue)
                            {   
                               if(nFunctioncount1<nMaxFun1)
                               {
                                 nFunctioncount1+=40;      
                               }
                            } 
                            
                           if(nFunctioncount1>=nMaxFun1) 
                           {
                                
                             bFunction1continue = false;
                             nFunctioncount1=0;
                             bFptready = false;
                             for(int num=0;num<500;num++)
                             SetRect(&Function1rt[num],-1000,-1000,-1000,-1000);
                             bFunction1atk = false;
                            }    
      
                             
                             
                             
                           
                             //������ 
                          
                                
                             if( (GetKeyState('E')&0x8000) && (nWeapontype==2) && !bFunction1continue && !bFunction3continue )
                             {
                                
                                Secondfunctionset();
                                Secondfunction();
                                Realsecondfunction();
                               
                             }
                             
                              if(!(GetKeyState('E')&0x8000) )
                             {
                              
                              nFunctioncount2=nMaxFun2;      
                                            
                             }
                             
                          /*     
                             
                            */
                             
                             //�Ÿ� ����         
                           if(bFunction2continue)
                            {   
                               if(nFunctioncount2<nMaxFun2)
                               {
                                 nFunctioncount2+=30;  
                                 nFunctioncount2real+=30;   
                               }
                               
                            } 
                            
                            
                            
                           if(nFunctioncount2>=nMaxFun2) 
                           {
                             
                             bFunction2continue = false;
                             nFunctioncount2=0;
                             bFptready = false;
                             for(int num=0;num<500;num++)
                             SetRect(&Function2rt[num],-1000,-1000,-1000,-1000);
                             bFunction2atk = false;
                             
                            }    
                             
                             
                             
                             
                             
                             //���� 
                           if(  (nWeapontype==3) && !bFunction1continue && !bFunction2continue )
                           {
                                 
                                Thirdfunctionset();
                                Thirdfunction();
                               
                           }  
                             
                             
                             if(nWeapontype !=3 && !bFunction3continue)
                             bFunction3ready = false;
                             else if(nWeapontype==3 || bFunction3continue)
                             bFunction3ready = true; 
                            
                            if(bFunction3continue)
                            {
                             nFun3end++;
                            }
                             if((GetKeyState('E')&0x8000) &&  bFunction3continue)
                             {
                              nFun3++;
                             }
                               SetRect(&Function3linert,1366*3/4+1366*1/4*nFun3/40,0,1366*3/4+1366*1/4*nFun3/40+1,100);      
                             
                             
                                
                            // ����Ÿ�̹� �����ϱ� 
                             
                             
                             if(nFun3end>40 )
                             {
                                             
                              Dmg+=nFun3;
                              Playerhealth-=nFun3;
                              nFun3=0;
                              nFun3end = 0;
                              
                              for(int a=0;a<1366/4;a++)
                               SetRect(&Function3rt[a],-1000,-1000,-1000,-1000);
                              bFunction3continue = false;
                              bFunction3ready = false;
                              
                             }
                             
                             
                             //���� 
                              
                             
                           /*  if( (GetKeyState('E')&0x8000) && (nWeapontype==4) && !bFunction1continue && !bFunction2continue && !bFunction3continue )
                             {
                                 
                                Fourthfunctionset();
                                Fourthfunction();
                                
                             }  */
                         //   
                          if(bFun4go)
                          {
                            Fourthfunctionset();
                            Fourthfunction(); 
                            bFunction3ready = false;
                          }
                             
                        
                          
                          
                         
                          
                          
                          
                          
                          
                          
                             
                             
                             
                             
                             
                             //���� 
                              if( !bFading && !bAmoving && !bPlayerdie && bAttackable && (GetKeyState('D')&0x8000) && !(GetKeyState('S')&0x8000) )
                              {
                               bAttack = true;
                               bAttackable=false;      
                              }
                              //���Ÿ� 
                              if( !bFading && bAttackable && !bPlayerdie && (GetKeyState('S')&0x8000) && !(GetKeyState('D')&0x8000) )
                              {
                               cNumweapon=2;
                               bAttack = true;
                               bAttackable=false;
                              
                               CreateSAK();    
                              }
                              SAK();
                             
                             
                             
                              //���� 
                             
                 if(!bFading&&!bPlayerdie&&GetKeyState(VK_SPACE)&0x8000)
                 {
                               
                               
                               if(!bAmoving&&!bjump)
                               { 
                                 bjump=true;
                                 gravity=190;
                                // gravity=120;  
                               } 
          
                 } 
                              
                              bjump = true;
                              Player_rt.top -= (gravity / 10); 
                              Player_rt.bottom = Player_rt.top+40;
                               
                               if(gravity>-300  && gravity<=300)
                                gravity -=10; 
                                         // gravity�� 190�� �� 10 12�� �� 5              
                              
                        
                                    //
                             if(bKnockr)   
                             {
                             
                                        
                               if(accmove<3)
                               accmove++;
                              Player_rt.right = Player_rt.left +40;
                                      
                             
                              gravity = 50;
                              bKnockr = false; 
                              SetTimer(hWnd,31,700,FALSE);           
                             }
                             if(bKnockl)   
                             {
                                       
                                           
                               if(accmove<-3)
                               accmove--;
                              Player_rt.right = Player_rt.left +40;
                              
                              
                              gravity = 50;       
                              bKnockl = false;   
                              SetTimer(hWnd,31,500,FALSE);            
                             }   
                                
        
                                
                                //NPC �浹  
                                for(int num=0;num<nNPCnum;num++)
                                {
                                    RECT frt;    
                                    if(IntersectRect(&frt,&NPCrt[num],&Player_rt))
                                    {
                                        if(GetKeyState('D')&0x8000)
                                        {   
                                            bText=true;
                                            bTextnext=true;
                                     
                                        }
                                    }
                                }                    
                                
               
               if(comboI>=3)
               {
                combo++;
                comboI=0;
               }
               //Mobangry();
                Dragonmove();
                Dragonangry();  
              
              
                     Player_rt.right=Player_rt.left+40;
                     Player_rt.bottom=Player_rt.top+40; 
              
              
              
      //����        
        if(!bPlayerdie && bGridonoff)
        {      
         nRgncount+=40/4;
         Widingrgn  = CreateEllipticRgn(Zeropt.x-nRgncount-mapmoving-sight,Zeropt.y-nRgncount,Zeropt.x+nRgncount-mapmoving-sight,Zeropt.y+nRgncount); 
        } 
     
     
     
     //���̵��� 
       Fadedraw();
           
              
          
           
                               
               Shield();  
               Soundout();
               Mobmove();
               Hitbyrgn();
               Hitbywall();
               Killgoo();
               Mobatk();
               Mobatkhelp();        
               MapMoving(); 
         
             
              
         } //!bText       
                   
         InvalidateRect(hWnd,NULL,FALSE);
        
        break;
        
      
        
        
        
        
        
        
        case 2: // �ؽ�Ʈ ��� 
        bTextnext=true;
        KillTimer(hWnd,2);
        break;
        
        
        
        
          case 21: // �� ��׷� ���� 
          RECT wastert;
         for(int mob=0;mob<128;mob++)
         {  
           
           if(!IntersectRect(&wastert,&Mobfindrt[mob],&Player_rt)) 
           {
          
          
            bMobatk[mob] = false; 
         
            //KillTimer(hWnd,21);
           }
         }
         break;


       case 22: //�� ���� ���ð� 
       
       for(int mob=0;mob<128;mob++)
       bMobatkwait[mob] = true;
       
       
       KillTimer(hWnd,22);     
       break;
        
        
         
       case 31: //�����ð� 
      
       bZhonya = false;    //������ 
       KillTimer(hWnd,31);
       break;
        
        
        
        
        
        
        } //wParam
     
          
        }  //bPlaygame
        InvalidateRect(hWnd,NULL,FALSE);
         break;
         return 0;
  
case WM_KEYDOWN:
     
     
    
    
     
    if(bPlaygame) 
    {
     if(wParam=='1')
     {
      nWeapontype=1;
     }  
     if(wParam== '2')
     {
      nWeapontype=2;
     }
     if(wParam=='3')
     {
      nWeapontype=3;
     }
     
     if(wParam=='4')
     {
      nWeapontype=4;
     }
     
     
    
   if( (wParam=='E') && (nWeapontype==4) ) 
   {
     bFun4go = true;      
   }  
    
     
     
    }
    
    if(!bPlaygame)
    { 
                  switch(cKeystate)
                  {
                      case 0:// Ÿ��Ʋ 
                       if(wParam==VK_UP)
                       {
                        if(cSelectstate!=0)
                        {
                         cSelectstate--;
                          PlaySound("Sounds/button.wav" , NULL , SND_ASYNC  | SND_FILENAME | SND_NODEFAULT );    
                        }
                        else if(cSelectstate==0)
                        {
                         cSelectstate=2;
                         PlaySound("Sounds/button.wav" , NULL , SND_ASYNC  | SND_FILENAME | SND_NODEFAULT );  
                        }
                       }
                       
                       if(wParam==VK_DOWN)
                       {
                          if(cSelectstate!=2)
                          {
                           cSelectstate++;
                           PlaySound("Sounds/button.wav" , NULL , SND_ASYNC  | SND_FILENAME | SND_NODEFAULT );  
                          }
                         else if(cSelectstate==2)
                         {
                          cSelectstate=0;
                          PlaySound("Sounds/button.wav" , NULL , SND_ASYNC  | SND_FILENAME | SND_NODEFAULT );  
                         }
                  } 
                  break;
                    
                    case 1:
                       if(wParam==VK_UP)
                       {
                        if(cSelectstate!=0)
                        cSelectstate--;
                        else if(cSelectstate==0)
                        cSelectstate=4;
                       }
                       
                       if(wParam==VK_DOWN)
                       {
                          if(cSelectstate!=4)
                         cSelectstate++;
                         else if(cSelectstate==4)
                         cSelectstate=0;
                       } 
                       break;
                         
                    case 2:
                         break;
                         
                    case 3:
                         
                         break;
                    
                    }         
    }
    break;
    
    
    
    return 0;     

case WM_KEYUP:
              
         if(!bPlaygame)
         { 
           switch(cKeystate)
           {
               case 0:  // Ÿ��Ʋ  
                    break;
                
               case 1: // �κ��丮 
                    if(wParam==VK_ESCAPE || wParam=='I')
                       {
                        bPlaygame=true;
                        cSelectstate=0;
                       }
                    break; 
              
              case 2:
                   break;
             
             case 3:
                  if(wParam==VK_F1)
                   PostQuitMessage(0);
                  if(wParam==VK_ESCAPE)
                  {
                    bPlaygame=true;
                  }                 
                         return 0;
                  break;                       
           }            
              
         }         
         
         else if(bPlaygame)
         {    
           if(bText)
           {
             if(bTextnext)
             {
               if(wParam=='D')
              {
               bTextnext=false;
               SetTimer(hWnd,2,2,NULL);
               
               if((lstrlen(Sentencestr) <= nTextcount)||cSelectstate==0)
               {
               cSelectstate++;
                nTextcount = 0;
               }
              else 
              nTextcount = lstrlen(Sentencestr);
                         
              } 
             }
           }
            
            else if(!bText)
             { 
                 
                 if(wParam=='T')
               {
                  do{            
                  if(bGridonoff)
                  {
                   bGridonoff=false;
                   nRgncount = 0;
                   break;
                  }
                  if(!bGridonoff)
                  {
                   bGridonoff=true;
                   nRgncount =0;
                  }
               }while(false);   // ���� ����ü �� do while �� ���� �ų� ��¼�� �ѹ� ���� �ҰŸ� �ƿ� ������ ����?? 
             }                  // Answer : �׳��� ���� ��ư����������� �˰��� ¥���� �����ؾ� �ϳİ� �����ϱ� ����Ŵ� ��ž� 
                
   
   
                //�ӽ÷� y��ư�� �־����. 
           
                
                
                 if(wParam=='Y')
               {
                  do{            
                  if(bFadeonoffI)
                  {
                   bFadeonoffI=false;
                   RgncountI = 0;
                   break;
                  }
                  if(!bFadeonoffI)
                  {
                   bFadeonoffI=true;
                   RgncountI =0;
                  }
               }while(false);
            }
                  
                      
      
                 
                 
                 
            
                 
                 
                 
               if(wParam==VK_RIGHT)
               {
                accmove=0;
              
               }
                  
                  if(wParam==VK_LEFT)
              {
              accmove=0;
                  
              }
                  
              
              if(wParam=='D')
              { 
                             bAttackable = true;
              }
                             
              if(wParam=='S')
              { 
                             bAttackable = true;
              }
              
              if(!bPlayerdie && wParam=='I')
              {
                   bPlaygame=false;                                     
                   cKeystate=1;
                   cSelectstate=0;
              }
              
              if(wParam==VK_ESCAPE)
                            {
                              bPlaygame=false;
                              cKeystate=3;
                            }
                  
              
               if(wParam=='R')
               {              
                              
                              bPlayerdie = false;
                              bGoRight=true;
                              nNumstage=0;
                              PlaySound(NULL,NULL,SND_ASYNC);
                              gravity = 0;
                             
                             
                           
                              Getstage();
                               
                              Playerhealth = 100;
                              Dmg =15;
                              combo =0;
                              comboI=0;
                              
                              
                              bDragongoright = false;
                              bDragonatk = false;
                              Dragonhealth=1000;
                              bDragonable = false;
              
                              
                            
                              
                              bZhonya = false;
                              Player_rt.left=fpx;
                              Player_rt.top=fpy;
                              CharacterBitmap=LoadBitmap(g_hInst,MAKEINTRESOURCE(Character));
                              nRgncount=0;
                              RgncountI = 0;
                              bGridonoff = false;
                              bFadeonoffI = false;//?! 
                              SetRect(&Dragonrt,0,0,0,0);
                              if(Player_rt.left>=nScreen)
                              {
                                mapmoving=Player_rt.left-nScreen; 
                                sight=Player_rt.left-nScreen;
                              }
                                   
               }
             } // bText  
         }
         
         break;

     return 0;      
     
   /*  // ȭ�� ũ�� ���� 
case WM_GETMINMAXINFO :
  ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 640;
  ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 320; 
  ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 640; 
  ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 320; 

return FALSE;             
     */   
         
         
 	case WM_PAINT:
          
          
          hdc=BeginPaint(hWnd,&ps);
          
           
          GetClientRect(hWnd,&rt);
            
         MemDC=CreateCompatibleDC(hdc);
         
         SetMapMode(hdc,MM_ANISOTROPIC);
         SetMapMode(MemDC,MM_ANISOTROPIC );
         SetWindowExtEx(hdc,1366,768,NULL);   
         SetWindowExtEx(MemDC,1366,768,NULL);
         SetViewportExtEx(hdc,rt.right,rt.bottom,NULL);  
         SetViewportExtEx(MemDC,rt.right,rt.bottom,NULL);  


         BackBitmap=CreateCompatibleBitmap(hdc,rt.right,rt.bottom);
         
         OldBitmap=(HBITMAP)SelectObject(MemDC,BackBitmap);
         
         SetBkMode(MemDC,TRANSPARENT); 
        
       
         FillRect(MemDC,&rt,GetSysColorBrush(COLOR_WINDOW));
                 
      
         
         
         
      if(!bPlaygame)
      {
          switch(cKeystate)
          {
                   case 0:
                        DrawTitle();
                        break;
                   
                   case 1:
                        DrawMenu();
                        //�κ��丮
                        break;
                        
                   case 2:
                        
                        // NPC���ɱ�
                        break;
                   
                  case 3:
                       DrawESC();
                       //��������
                       
                       break;
          }
      }   
         
         
if(bPlaygame)
{
                       
         // SetROP2(MemDC,R2_MERGEPEN);                          
         PTBackGround();  // ��� 
         
         DrawScreen(MemDC);  // ���� 
        
        DrawUI();   //UI
          
           
         DrawDC=CreateCompatibleDC(hdc);
         
       
      //�Լ��� 
       Printfun();
     
     
    
       
         
           if(GetKeyState('P')&0x8000)
           {
             testmode();
           }
          
        if(!bPlayerdie && bGridonoff)
              {
                                                                        
              Skillgrid(); 
                        
              }  
              
           if(!bPlayerdie && bFadeonoffI)
              {
                Fadein(3);          
                          
              }
             
             
             Shielddraw();    
       
       
       
       //��Ŀ� 
         /* SelectObject(DrawDC,MonsterBitmap);
          TransBitBlt(MemDC,1050,450,180,160,DrawDC,1340,270,RGB(0,95,130));
         
          SelectObject(DrawDC,EffectBitmap);
          TransBitBlt(MemDC,600,360,260,260,DrawDC,500,1020,RGB(50,150,200));
          TransBitBlt(MemDC,700,400,250,240,DrawDC,250,1440,RGB(50,150,200));
          */
        
          
     
        if(!bPlayerdie)
        {
                       
         Playermove();
         
        }
         
         
         
         
         
         
      
         
         
         
         
  
          
          //��ѱ�  
          for(int arnum=0;arnum<mobnum4040;arnum++)
          {
                                                            
          if(!bMobdie[arnum]){
          if(Goort[arnum].left-mapmoving-sight>=-40 && Goort[arnum].left-mapmoving-sight<=1406)       
          DrawBitmap(MemDC,Goort[arnum].left-mapmoving-sight,Goort[arnum].top-ymoving,40,40,0,0,BidulgiBitmap);
          }
                   
                   
                   
                                                            
          else if(bMobdie[arnum]){
          if(Goort[arnum].left-mapmoving-sight>=-40 && Goort[arnum].left-mapmoving-sight<=1406)      
          DrawBitmap(MemDC,Goort[arnum].left-mapmoving-sight,Goort[arnum].top-ymoving,40,40,0,0,NULL);
          }
                                                            
                                                            
          }
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          for(int mobnum=0; mobnum<num5; mobnum++)
          {
            if(!bMobdie[num3+mobnum])
            {
              if(!bNum5right[num3+mobnum])
              {
               if(Animatenum5[num3+mobnum]==0)                           
               {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,0,0,MonsterBitmap);
               Animatenum5[num3+mobnum]++;
               }
               else if(Animatenum5[num3+mobnum]==1)
               {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,110,0,MonsterBitmap);
               Animatenum5[num3+mobnum]++;                               
               }                               
               else if(Animatenum5[num3+mobnum]==2)
               {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,220,0,MonsterBitmap);                               
               Animatenum5[num3+mobnum]=0;
               }
              }
              
             
              if(bNum5right[num3+mobnum])
              {
               if(Animatenum5[num3+mobnum]==0)                           
               {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,0,70,MonsterBitmap);
               Animatenum5[num3+mobnum]++;
               }
               else if(Animatenum5[num3+mobnum]==1)
               {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,110,70,MonsterBitmap);
               Animatenum5[num3+mobnum]++;                               
               }                               
               else if(Animatenum5[num3+mobnum]==2)
               {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,220,70,MonsterBitmap);                               
               Animatenum5[num3+mobnum]=0;
               }
              }
             }
            
            else if(bMobdie[num3+mobnum])
            {
               DrawBitmap(MemDC,Mobrt[mobnum].left-mapmoving-sight,Mobrt[mobnum].top-ymoving,110,70,0,0,NULL);
            }   
                     
          }
          
          for(int mobnum=0; mobnum<num6; mobnum++)
          {
            
            if(!bMobdie[num3+num5+mobnum])
            {
              if(!bNum5right[num3+num5+mobnum])
              {
               if(Animatenum5[num3+num5+mobnum]==0)                           
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,82,73,430,0,MonsterBitmap);
               Animatenum5[num3+num5+mobnum]++;
               }
               else if(Animatenum5[num3+num5+mobnum]==1)
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,83,73,512,0,MonsterBitmap);
               Animatenum5[num3+num5+mobnum]++;                               
               }                               
               else if(Animatenum5[num3+num5+mobnum]==2)
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,80,73,595,0,MonsterBitmap);                               
               Animatenum5[num3+num5+mobnum]++;
               }
               else if(Animatenum5[num3+num5+mobnum]==3)
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,80,73,675,0,MonsterBitmap);                               
               Animatenum5[num3+num5+mobnum]=0;
               }
               
              }
              
             
              if(bNum5right[num3+num5+mobnum])
              {
               if(Animatenum5[num3+num5+mobnum]==0)                           
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,82,73,430,73,MonsterBitmap);
               Animatenum5[num3+num5+mobnum]++;
               }
               else if(Animatenum5[num3+num5+mobnum]==1)
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,83,73,512,73,MonsterBitmap);
               Animatenum5[num3+num5+mobnum]++;                               
               }                               
               else if(Animatenum5[num3+num5+mobnum]==2)
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,80,73,595,73,MonsterBitmap);                               
               Animatenum5[num3+num5+mobnum]++;
               }
               else if(Animatenum5[num3+num5+mobnum]==3)
               {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,80,73,675,73,MonsterBitmap);                               
               Animatenum5[num3+num5+mobnum]=0;
               }
              }
              }
            
            else if(bMobdie[num3+num5+mobnum])
            {
               DrawBitmap(MemDC,Mobrt[num5+mobnum].left-mapmoving-sight,Mobrt[num5+mobnum].top-ymoving,110,70,0,0,NULL);
            }            
          
          }        
          
          
          for(int mobnum=0; mobnum<num6; mobnum++)
          {
            
            if(!bMobdie[num3+num5+num6+mobnum])
            {
              if(!bNum5right[num3+num5+num6+mobnum])
              {
               if(Animatenum5[num3+num5+num6+mobnum]==0)                           
               {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,100,80,20,152,MonsterBitmap);
               Animatenum5[num3+num5+num6+mobnum]++;
               }
               else if(Animatenum5[num3+num5+num6+mobnum]==1)
               {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,100,80,120,152,MonsterBitmap);
               Animatenum5[num3+num5+num6+mobnum]++;                               
               }                               
               else if(Animatenum5[num3+num5+num6+mobnum]==2)
               {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,100,80,220,152,MonsterBitmap);                               
               Animatenum5[num3+num5+num6+mobnum]++;
               }
               
               
              }
              
             
              if(bNum5right[num3+num5+num6+mobnum])
              {
               if(Animatenum5[num3+num5+num6+mobnum]==0)                           
               {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,112,80,8,240,MonsterBitmap);
               Animatenum5[num3+num5+num6+mobnum]++;
               }
               else if(Animatenum5[num3+num5+num6+mobnum]==1)
               {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,100,80,120,240,MonsterBitmap);
               Animatenum5[num3+num5+num6+mobnum]++;                               
               }                               
               else if(Animatenum5[num3+num5+num6+mobnum]==2)
               {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,100,80,220,240,MonsterBitmap);                               
               Animatenum5[num3+num5+num6+mobnum]++;
               }
            
              }
              }
            
            else if(bMobdie[num3+num5+num6+mobnum])
            {
               DrawBitmap(MemDC,Mobrt[num5+num6+mobnum].left-mapmoving-sight,Mobrt[num5+num6+mobnum].top-ymoving,110,70,0,0,NULL);
            }            
          
          }
          
          //��?
          if(bDragonable&&!bDragondie)
          {
          SelectObject(DrawDC,DragonBitmap);
          
          
          if(bDragongoright)
            {if(Dcount==0)
              Dcount=1;
            if(Dcount>3*4)
              Dcount=1;
                            
          if(Dcount==1||Dcount==2||Dcount==3||Dcount==4) 
          {
          
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top+20-ymoving,170,185,DrawDC,0,240,RGB(0,0,0));//��               
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight+10,Dragonrt.top-20-ymoving,190,180,DrawDC,10,590,RGB(0,0,0));//�Ӹ� 
         
          }
          if(Dcount==5||Dcount==6||Dcount==7||Dcount==8)
          {
                       
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top+20-ymoving,170,185,DrawDC,170,240,RGB(0,0,0));             
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight+10,Dragonrt.top-20-ymoving,190,180,DrawDC,10,590,RGB(0,0,0));//�Ӹ� 
          //TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight+10,Dragonrt.top-5,30,30,DrawDC,10,110,RGB(0,0,0));
          
          }
          if(Dcount==9||Dcount==10||Dcount==11||Dcount==12)
          {
                       
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top+20-ymoving,170,185,DrawDC,340,240,RGB(0,0,0));             
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight+10,Dragonrt.top-20-ymoving,190,180,DrawDC,10,590,RGB(0,0,0));//�Ӹ� 
          //TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight+10,Dragonrt.top-5,30,30,DrawDC,10,110,RGB(0,0,0));
     //   Dcount =0;
          }
            } 
            
  //                   ���� x ��ǥ                 ���� y ��ǥ       �׸� ũ��,   �׸� ���� ��ġ 
            
          if(!bDragongoright)
            { if(Dlcount<=0)
              Dlcount=1;
              if(Dlcount>3*4)
              Dlcount=1;               
                             
          if(Dlcount==1||Dlcount==2||Dlcount==3||Dlcount==4) 
          {
                         
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-ymoving,170,220,DrawDC,0,0,RGB(0,0,0));               
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-10-ymoving,140,175,DrawDC,0,425,RGB(0,0,0)); //�Ӹ� 
         
          }
          if(Dlcount==5||Dlcount==6||Dlcount==7||Dlcount==8)
          {
                        
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-ymoving,170,220,DrawDC,170,0,RGB(0,0,0));              
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-10-ymoving,140,175,DrawDC,0,425,RGB(0,0,0)); //�Ӹ� 
          //TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-5,30,30,DrawDC,0,80,RGB(0,0,0));
         
          }
          if(Dlcount==9||Dlcount==10||Dlcount==11||Dlcount==12)
          {
                        
           TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-ymoving,170,220,DrawDC,340,0,RGB(0,0,0));              
          TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-10-ymoving,140,175,DrawDC,0,425,RGB(0,0,0)); //�Ӹ� 
          //TransBitBlt(MemDC,Dragonrt.left-mapmoving-sight,Dragonrt.top-5,30,30,DrawDC,0,80,RGB(0,0,0));
         
          //   Dlcount = 0;    
          }
            } 
               
}   
          
          
          
          
          
          
          //���ݳ����°�
         
          if(cNumweapon==1)
          {     
            if(bAttack&&bGoRight)
            {
                  
             SelectObject(DrawDC,BulletBitmap);     
             TransBitBlt(MemDC,Player_rt.left+40-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,0,0,RGB(0,0,0));       
              bAttack = false;
       
             }
                              
              
         
            if(bAttack&&!bGoRight)
            {
              SelectObject(DrawDC,BulletBitmap);   
             TransBitBlt(MemDC,Player_rt.left-40-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,0,0,RGB(0,0,0));       
              bAttack = false;                      
                               
            }
          }    
         
         
         
            
        if(bText)
        {
          hFont=CreateFont(48,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,TEXT("���"));
         OldFont=(HFONT)SelectObject(MemDC,hFont);         
         DrawText();   
        }    
             
              
        
        hFont=(HFONT)SelectObject(MemDC,OldFont);  
        Playermobwork(); 
         
         
      
         
         
         
         
         
         
         
         
         //�� ź��ü. 
            SelectObject(DrawDC,BulletBitmap);
         for(int mob=0;mob<128;mob++)
         {
          for(int shoot=0;shoot<16;shoot++)
          {       
           if(bMobatk[mob])
           if(bMobbulletfly[mob][shoot])       
           TransBitBlt(MemDC,Mobbulletrt[mob][shoot].left-mapmoving-sight,Mobbulletrt[mob][shoot].top-ymoving,14,16,DrawDC,66,0,RGB(0,0,0));
          }
         }        
         //
         
             
             for(int shoot=0;shoot<16;shoot++)
             {
                     
                     
                     
                     if(bBulletAK[shoot])
                     {          
                     
                                
                    SelectObject(DrawDC,BulletBitmap);
                    if(Bulletrt[shoot].left-mapmoving-sight>=-40 && Bulletrt[shoot].left-mapmoving-sight<=1406)
                    if(cBulletstate[shoot]==1)
                    TransBitBlt(MemDC,Bulletrt[shoot].left-mapmoving-sight,Bulletrt[shoot].top-ymoving,14,16,DrawDC,66,0,RGB(0,0,0));
                    
                    if(cBulletstate[shoot]==3)
                    TransBitBlt(MemDC,Bulletrt[shoot].left-mapmoving-sight,Bulletrt[shoot].top-ymoving,8,16,DrawDC,84,0,RGB(0,0,0));
                    
                    if(cBulletstate[shoot]==2) 
                    TransBitBlt(MemDC,Bulletrt[shoot].left-mapmoving-sight,Bulletrt[shoot].top-ymoving,16,16,DrawDC,96,0,RGB(0,0,0));
                    
                    if(cBulletstate[shoot]==4)
                    TransBitBlt(MemDC,Bulletrt[shoot].left-mapmoving-sight,Bulletrt[shoot].top-ymoving,8,16,DrawDC,116,0,RGB(0,0,0));
                    //TransBitBlt(MemDC,Bulletrt[shoot].left-mapmoving-sight,Bulletrt[shoot].top,40,40,DrawDC,0,0,RGB(0,0,0));
                    //StretchBlt(MemDC,Stretchdrawx,Stretchdrawy,Stretchsizex,Stretchsizey,BackGroundDC,drawx,drawy,sizex,sizey,SRCCOPY)
                     //StretchDrawBitmap(MemDC,0,0,mapx*40,mapy*40,BackGroundBitmap,0,0,1024,768);
                    //TransparentBlt(MemDC,Bulletrt[shoot].left-mapmoving-sight,Bulletrt[shoot].top,Bulletrt[shoot].right-mapmoving-sight,Bulletrt[shoot].bottom,DrawDC,0,0,40,40,RGB(0,0,0));
                    
                    }
             }
    
         DeleteDC(DrawDC);
        
         
    }  //bplaygame
    Rectangle(hdc,20,20,20,40);
        BitBlt(hdc,0,0,1366,768,MemDC,0,0,SRCCOPY);
        
         SelectObject(MemDC,OldBitmap);
         DeleteObject(BackBitmap);
		 DeleteDC(MemDC);
        SelectObject(MemDC,OldFont);
         EndPaint(hWnd,&ps);       
 	
 	     return 0;
 	
 	

	case WM_DESTROY:
         
		PostQuitMessage(0);
	  KillTimer(hWnd,1);
	  KillTimer(hWnd,21);
	  free(currentstage);
	  free(Hitrt);
	  free(Siderrt);
	  free(Sidelrt);
	  free(St1rgn);
	  free(St2rgn);
	  free(St3rgn);
	  free(St4rgn);
	  free(St5rgn);
	  free(St6rgn);
	  free(St7rgn);
	  free(St8rgn);
      free(Stairpt1);
      free(Stairpt2);
      free(Stairpt3);
      free(Stairpt4);
      free(Stairpt5);
      free(Stairpt6);
      free(Stairpt7);
      free(Stairpt8);
     
      DeleteObject(CharacterBitmap);
      DeleteObject(TileBitmap);
      DeleteObject(ItemBitmap);
      DeleteObject(TextBoxBitmap);
      DeleteObject(TitleBitmap);
      DeleteObject(MenuBitmap);
      DeleteObject(BulletBitmap);
      DeleteObject(BidulgiBitmap);
      DeleteObject(bkBlackBitmap);
      DeleteObject(MonsterBitmap);
      DeleteObject(bkFogBitmap);
      DeleteObject(bkSeaBitmap);
      DeleteObject(bkMoonBitmap);
      DeleteObject(DragonBitmap);
      DeleteObject(NPCBitmap);
   
      DeleteObject(Widingrgn);
      ReleaseDC(hWnd,hdc);        
      
         
		return 0;
}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}



void Getstage()
{
     int getx,gety;
     combo=0;
     comboI=0;
     Dmg=15;
     mobnum4040=0; //  �� ���� �ʱ�ȭ �ϱ� ���ο�� ���ö� ���� 
     gravity=0;
     Scanmap();
//     memcpy(currentstage,Gamestage[nNumstage],sizeof(currentstage));
     
     for(gety=0;gety<mapy;gety++)
     {
            for(getx=0;getx<mapx;getx++)
            {
                    if(currentstage[gety][getx]==1)
                    { 
                         Player_rt.left=getx*40;
                         Player_rt.top=gety*40;
                        
                         fpx=getx*40;
                         fpy=gety*40;
                    }
                    
                                                                
                                      
                    //�� ��ѱ� 
                  if(currentstage[gety][getx]==3)
                    {
                             if(num3<128){                      
                             SetRect(&Goort[num3],getx*40,gety*40,getx*40+40,gety*40+40);
                             SetRect(&Mobfindrt[num3],getx*40-400,gety*40-200,getx*40+40+400,gety*40+40+200);
                             bMobdie[num3]=false;
                             Mobhealth[num3]=10;
                             num3++;
                             }
                             mobnum4040++;
                    }
                     
                     
                             
                      
                    if(currentstage[gety][getx]==4) //npc
                    {
                       if(num4<16)
                       {          
                       SetRect(&NPCrt[num4],getx*40,gety*40,getx*40+40,gety*40+40);
                       num4++;
                       
                       }
                       nNPCnum++; 
                    }                                        
                     
                     if(currentstage[gety][getx]==5)  //�ڳ��� 
                     {
                      if(num5<128)
                      {
                        SetRect(&Mobrt[num5],getx*40,gety*40,getx*40+110,gety*40+70);
                        
                        bMobdie[num3+num5]=false;
                       Mobhealth[num3+num5]=100;
                       num5++;
                      }  
                     }
                     
                     
                     if(currentstage[gety][getx]==6)  //���� 
                     {
                      if(num6<128)
                      {
                        SetRect(&Mobrt[num5+num6],getx*40,gety*40,getx*40+85,gety*40+70);
                        
                        bMobdie[num3+num5+num6]=false;
                       Mobhealth[num3+num5+num6]=60;
                       num6++;
                      }  
                     }
                     
                     if(currentstage[gety][getx]==7)  //���ƴٴϴ� ����? 
                     {
                      if(num7<128)
                      {
                        SetRect(&Mobrt[num5+num6+num7],getx*40,gety*40,getx*40+70,gety*40+65);
                        
                        bMobdie[num3+num5+num6+num7]=false;
                       Mobhealth[num3+num5+num6+num7]=80;
                       num7++;
                      }  
                     }
                     
                             
                             
                      //�ⱸ       
                    if(currentstage[gety][getx]==36)
                    {
                     SetRect(&Exitrt,getx*40,gety*40,getx*40+40,gety*40+40);                            
                    }
                    
                    //��
                    if(currentstage[gety][getx]==99)         
                     {     
                              
                 
                       
                          SetRect(&Dragonrt,getx*40,gety*40,getx*40+180,gety*40+250);                  
                            bDragonable = true;
                            Dragonhealth = 1000;                
                                                 
                             
                             
                             
                      }
                    
                    
                    
                    
                         
            }
     }
     
     if(Player_rt.left>=nScreen)
     {
     mapmoving=Player_rt.left-nScreen;
     
     sight=Player_rt.left-nScreen;
     }
     
}        



void DrawScreen(HDC MemDC)
{
     int stagex,stagey;

    
     for(stagey=ymoving/40;stagey<20+ymoving/40;stagey++)
     {
                       for(stagex=(mapmoving+sight)/40;stagex<(mapmoving+sight)/40+35;stagex++)
                       {
                                                        switch(currentstage[stagey][stagex])
                                                        {
													
                                                        case 2:
                                                            
                                                                 
                                                                 DrawBitmap(MemDC,stagex*40-mapmoving-sight,stagey*40-ymoving,40,40,120,0,TileBitmap);
                                                            
                                                        
                                                             break;
                                                        
                                                        case 9: 
                                                        DrawBitmap(MemDC,stagex*40-mapmoving-sight,stagey*40-ymoving,40,40,160,0,TileBitmap);
                                                            
                                                        
                                                             break;
                                                        
                                                        case 36:
                                                             
                                                             DrawBitmap(MemDC,stagex*40-mapmoving-sight,stagey*40-ymoving-40,40,80,0,80,TileBitmap);
                                                             
                                                             break;
                                                             
                                                        
                                                             
                                                        case 4:
                                                            
                                                            DrawBitmap(MemDC,stagex*40-mapmoving-sight,stagey*40-ymoving,50,44,73,12,NPCBitmap);
                                                             
                                                             break;
                                                                  
                                                             }
                                                        }
                                     }
                                     
	 //DrawBitmap(MemDC,Player_rt.left*40-mapmoving,Player_rt.top*40,40,40,CharacterBitmap);

}



void DrawBitmap(HDC MemDC,int drawx,int drawy,int sizex,int sizey,int startx,int starty, HBITMAP hBit)
{ 
     
      HDC BackGroundDC;
      HBITMAP OldBitmap;
      BackGroundDC=CreateCompatibleDC(hdc);
     
      OldBitmap=(HBITMAP)SelectObject(BackGroundDC,hBit);
      TransBitBlt(MemDC,drawx,drawy,sizex,sizey,BackGroundDC,startx,starty,RGB(0,0,0));//�μ� 4,5���� ���� �ؾߵ� �׸��� �°�  7,8 �� 
      SelectObject(BackGroundDC ,OldBitmap);
      DeleteDC(BackGroundDC);

}


void StretchDrawBitmap(HDC MemDC,int Stretchdrawx,int Stretchdrawy,int Stretchsizex,int Stretchsizey,HBITMAP hBit,int drawx ,int drawy,int sizex,int sizey)
{
     
      HDC BackGroundDC;
      HBITMAP OldBitmap;
      BackGroundDC=CreateCompatibleDC(hdc);
     
      OldBitmap=(HBITMAP)SelectObject(BackGroundDC,hBit);
      StretchBlt(MemDC,Stretchdrawx,Stretchdrawy,Stretchsizex,Stretchsizey,BackGroundDC,drawx,drawy,sizex,sizey,SRCCOPY);//�μ� 4,5���� ���� �ؾߵ� �׸��� �°�  7,8 �� 
      SelectObject(BackGroundDC ,OldBitmap);
      DeleteDC(BackGroundDC);
     
}



void Hitbywall()
{
 int hitx;
 int hity;
 int hitnx;
 int hitny;
 
 int nAdhitx=0;
 int nAdhity=0;
 int mob=0;
 
 RECT Wastert;
 


      
      
      HDC hdc;
      HDC MemDC;
      
        
        switch(accmove)
        {
           
           case 0:
                nPlayermoving=0;
                break; 
          
           case 3:
                if(Player_rt.left<mapx*40-(rt.right-nScreen) && Player_rt.left>nScreen+10)    
                nPlayermoving=-96;
                else
                nPlayermoving=0; 
                break;
                
          
           case -3:
                if(Player_rt.left<mapx*40-(rt.right-nScreen) && Player_rt.left>nScreen+10)
                nPlayermoving=96;
                else
                nPlayermoving=0;
                break;
          
        }  
       
       //�Ѿ� �浹 
       for(int shoot=0;shoot<16;shoot++)
       {
          if(bBulletAK[shoot])
          {     
           if(Bulletrt[shoot].left%40<20)
           nAdhitx=(Bulletrt[shoot].left-(Bulletrt[shoot].left%40))/40;
           else if(Bulletrt[shoot].left%40>=20)
           nAdhitx=(Bulletrt[shoot].left+40-(Bulletrt[shoot].left%40))/40;
           
           if(Bulletrt[shoot].top%40<20)
           nAdhity=(Bulletrt[shoot].top-(Bulletrt[shoot].top%40))/40;
           else if(Bulletrt[shoot].top%40>=20)
           nAdhity=(Bulletrt[shoot].top+40-(Bulletrt[shoot].top%40))/40;
          }
          
          else if(!bBulletAK[shoot])
          {
               continue;
               
          } 
          
    
          if(!( nAdhity<=0 ||  nAdhity>=mapy-1)) 
          {  
           for(hity=nAdhity-1;hity<=nAdhity+1;hity++)
             for(hitx=nAdhitx-1;hitx<=nAdhitx+1;hitx++)
             
             {
                           if(IntersectRect(&Wastert,&Hitrt[hity][hitx],&Bulletrt[shoot]))
                           {
                                bBulletAK[shoot]=false;
                           }                          
                                                       
                 /*                                      
                  if(hity==nAdhity-1 && hitx==nAdhitx-1)//(0,0)
                                                  {                          
                                            
                                                                
                  
                                                                
                                                              if(cBulletstate[shoot]==1 && Bulletrt[shoot].left < Hitrt[hity][hitx].right && Bulletrt[shoot].left> Hitrt[hity][hitx].left &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                   
                                                                   Bulletrt[shoot].left = Hitrt[hity][hitx].right;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                                    bBulletAK[shoot]=false;
                                                              }
                                                              
                                                              //�� �� �浹 
                                                            if(cBulletstate[shoot]==3 && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left && Bulletrt[shoot].left < Hitrt[hity][hitx].right &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top > Hitrt[hity][hitx].top)                 
                                                            {
                                                                                     
                                                                                                                                                                                 
                                                                    Bulletrt[shoot].top=Hitrt[hity][hitx].bottom;
                                                                    Bulletrt[shoot].bottom=Bulletrt[shoot].top+40;
                                                                 bBulletAK[shoot]=false;
                                                                    
                                                                             
                                                            }
                                                              
                                                            
                                                              
                                                              
                                                     }  
                      
                      
                      
                      
                                     
                                      if(hity==nAdhity-1 && hitx==nAdhitx)
                                      {
                                                          //�� �� �浹 
                                                            if(cBulletstate[shoot]==3 && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left && Bulletrt[shoot].left < Hitrt[hity][hitx].right &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top > Hitrt[hity][hitx].top)                 
                                                            {
                                                                                     
                                                                                                                                                                                 
                                                                    Bulletrt[shoot].top=Hitrt[hity][hitx].bottom;
                                                                    Bulletrt[shoot].bottom=Bulletrt[shoot].top+40;
                                                              bBulletAK[shoot]=false;
                                                                    
                                                                             
                                                                              }
                                                         
                                      }
                             
                             
                             
                                      
                                      if(hity==nAdhity-1 && hitx==nAdhitx+1)
                                      {

                                                                
                                                                //�� ���� �浹
                                                                
                                                             if(cBulletstate[shoot]==2 && Bulletrt[shoot].left+40 < Hitrt[hity][hitx].right && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                         
                                                                   Bulletrt[shoot].left = Hitrt[hity][hitx].left-40;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                              bBulletAK[shoot]=false;
                                                                   
                                                                   }
                                                              
                                                              //�� �� �浹 
                                                            if(cBulletstate[shoot]==3 && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left && Bulletrt[shoot].left < Hitrt[hity][hitx].right &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top > Hitrt[hity][hitx].top)                 
                                                            {
                                                                                     
                                                                                                                                                                                 
                                                                    Bulletrt[shoot].top=Hitrt[hity][hitx].bottom;
                                                                    Bulletrt[shoot].bottom=Bulletrt[shoot].top+40;
                                                                bBulletAK[shoot]=false;
                                                                    
                                                                             
                                                                              } 
                                                                 
                                      }             
                             
                             
                             
                             
                                      
                                      if(hity==nAdhity && hitx==nAdhitx-1)
                                      {
                                        
                                                                
                                                              //�� ���� �浹
                                                                
                                                              if(cBulletstate[shoot]==1 && Bulletrt[shoot].left < Hitrt[hity][hitx].right && Bulletrt[shoot].left> Hitrt[hity][hitx].left &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                   
                                                                   Bulletrt[shoot].left = Hitrt[hity][hitx].right;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                              bBulletAK[shoot]=false;
                                                              }
                                                             
                                                              
                                                              
                                        }
                                        
                                      if(hity==nAdhity && hitx==nAdhitx)
                                      {
                                                       
                                                       
                                      }                
                                                       
                                      if(hity==nAdhity && hitx==nAdhitx+1)
                                      {
                                        
                                                                
                                                                //�� ���� �浹
                                                                
                                                             if(cBulletstate[shoot]==2 && Bulletrt[shoot].left+40 < Hitrt[hity][hitx].right && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                         
                                                                   Bulletrt[shoot].left = Hitrt[hity][hitx].left-40;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                              bBulletAK[shoot]=false;
                                                                   
                                                                   }

                                                                                                                             
                                                             
                                      } 
                                      
                                      if(hity==nAdhity+1 && hitx==nAdhitx-1)
                                      {
                                         //�� ���� �浹
                                                                
                                                              if(cBulletstate[shoot]==1 && Bulletrt[shoot].left < Hitrt[hity][hitx].right && Bulletrt[shoot].left> Hitrt[hity][hitx].left &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                   
                                                                   Bulletrt[shoot].left = Hitrt[hity][hitx].right;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                                    bBulletAK[shoot]=false;
                                                              }
                                                              
                                                              //�� �� �浹 
                                                            if(cBulletstate[shoot]==4 && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left && Bulletrt[shoot].left < Hitrt[hity][hitx].right && Bulletrt[shoot].top >= Hitrt[hity][hitx].top-40 && Bulletrt[shoot].top < Hitrt[hity][hitx].top)
                                                              {
                                                                   
                                                                                           
                                                                     //gravity += 20;
                                                                   //  Player_rt.top += (gravity / 10);

                                                                   Bulletrt[shoot].top=Hitrt[hity][hitx].top-40;
                                                                   Bulletrt[shoot].bottom=Bulletrt[shoot].top+40;
                                                                  bBulletAK[shoot]=false;
                                                                                                                      
                                                                                     }
                                                              
                                                             
                                        }                 
                                                         
                                                         
                                                         
                                      if(hity==nAdhity+1 && hitx==nAdhitx)
                                      {
                                 
                                                            //�� �� �浹 
                                                            if(cBulletstate[shoot]==4 && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left && Bulletrt[shoot].left < Hitrt[hity][hitx].right && Bulletrt[shoot].top >= Hitrt[hity][hitx].top-40 && Bulletrt[shoot].top < Hitrt[hity][hitx].top)
                                                              {
                                                                   
                                                              
                                                                   Bulletrt[shoot].top=Hitrt[hity][hitx].top-40;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                                bBulletAK[shoot]=false;
                                                                                                                      
                                                                                     }
                                                              
                                                               
                                        
                                                                              
                                      }
                                      
                                      
                                      
                                      
                                        
                                      if(hity==nAdhity+1 && hitx==nAdhitx+1)
                                      {
                                        
                                                              //�� ���� �浹
                                                                
                                                             if(cBulletstate[shoot]==2 && Bulletrt[shoot].right < Hitrt[hity][hitx].right && Bulletrt[shoot].right > Hitrt[hity][hitx].left &&  Bulletrt[shoot].top < Hitrt[hity][hitx].bottom && Bulletrt[shoot].bottom > Hitrt[hity][hitx].top)          
                                                              {
                                                                         
                                                                   Bulletrt[shoot].left = Hitrt[hity][hitx].left-40;
                                                                   Bulletrt[shoot].right = Bulletrt[shoot].left+40;
                                                                    bBulletAK[shoot]=false;
                                                                   
                                                                   }

                                                                  
                                                              
                                                              
                                                              //�� �� �浹 
                                                            if(cBulletstate[shoot]==4 && Bulletrt[shoot].left+40 > Hitrt[hity][hitx].left && Bulletrt[shoot].left < Hitrt[hity][hitx].right && Bulletrt[shoot].top >= Hitrt[hity][hitx].top-40 && Bulletrt[shoot].top < Hitrt[hity][hitx].top)
                                                              {
                                                               
                                                                   Bulletrt[shoot].top=Hitrt[hity][hitx].top-40;
                                                                   Bulletrt[shoot].bottom=Bulletrt[shoot].top+40;
                                                                    bBulletAK[shoot]=false;
                                                                    
                                                                                                                      
                                                                                     }                                                 
                                                            
                                                                                                                           *
                                                               }
*/
                                                               }  
       }
 }                                      
       
       
       
       
       
       
      
      
       
      for(int mob=0;mob<mobnum4040;mob++)                       
       { 
         if(Goort[mob].left%40<20)
         nAdhitx=(Goort[mob].left-(Goort[mob].left%40))/40;
         else if(Goort[mob].left%40>=20)
         nAdhitx=(Goort[mob].left+40-(Goort[mob].left%40))/40;
       
         if(Mobgravity[mob]<0)
         nAdhity=(Goort[mob].top-(Goort[mob].top%40))/40;
         else if(Mobgravity[mob]>=0)
         nAdhity=(Goort[mob].top+40-(Goort[mob].top%40))/40;  
         
 
 
          if(!( nAdhity<=0 ||  nAdhity-1 >= mapy+1))
          {
            for(hity=nAdhity-1;hity<=nAdhity+1;hity++)
            {
              for(hitx=nAdhitx-1;hitx<=nAdhitx+1;hitx++)
              {                         
                                
                                                  if(hity==nAdhity-1 && hitx==nAdhitx-1)//(0,0)
                                                  {                          
                                            
                                                                
                                                                //�� ���� �浹
                                                                
                                                              if( !bmgoright[mob] && Goort[mob].left < Hitrt[hity][hitx].right && Goort[mob].left> Hitrt[hity][hitx].left &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                   
                                                                   Goort[mob].left = Hitrt[hity][hitx].right;
                                                                   bmgoright[mob] = true; 
                                                              }
                                                              
                                                              //�� �� �浹 
                                                            if(Mobgravity[mob]>0 && Goort[mob].left+40 > Hitrt[hity][hitx].left && Goort[mob].left < Hitrt[hity][hitx].right &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top > Hitrt[hity][hitx].top)                 
                                                            {
                                                                                     
                                                                                                                                                                                 
                                                                    Goort[mob].top=Hitrt[hity][hitx].bottom;
                                                                    Mobgravity[mob]=0;
                                                                    
                                                                             
                                                            }
                                                              
                                                             // SetRect(&Player_rt, Player_rt.left+cAdpositionx , Player_rt.top+cAdpositiony , Player_rt.right+cAdpositionx , Player_rt.bottom+cAdpositionx);
                                                              
                                                              
                                                     }  
                      
                      
                      
                      
                                     
                                      if(hity==nAdhity-1 && hitx==nAdhitx)
                                      {
                                                          //�� �� �浹 
                                                            if(Mobgravity[mob]>0 && Goort[mob].left+40 > Hitrt[hity][hitx].left && Goort[mob].left < Hitrt[hity][hitx].right &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top > Hitrt[hity][hitx].top)                 
                                                            {
                                                                                     
                                                                                                                                                                                 
                                                                    Goort[mob].top=Hitrt[hity][hitx].bottom;
                                                                    Mobgravity[mob]=0;
                                                                    
                                                                             
                                                                              }
                                                         
                                      }
                             
                             
                             
                                      
                                      if(hity==nAdhity-1 && hitx==nAdhitx+1)
                                      {

                                                                
                                                                //�� ���� �浹
                                                                
                                                             if( bmgoright[mob] && Goort[mob].left+40 < Hitrt[hity][hitx].right && Goort[mob].left+40 > Hitrt[hity][hitx].left &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                         
                                                                   Goort[mob].left = Hitrt[hity][hitx].left-40;
                                                                   bmgoright[mob] = false; 
                                                                   
                                                                   }
                                                              
                                                              //�� �� �浹 
                                                            if(Mobgravity[mob]>0 && Goort[mob].left+40 > Hitrt[hity][hitx].left && Goort[mob].left < Hitrt[hity][hitx].right &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top > Hitrt[hity][hitx].top)                 
                                                            {
                                                                                     
                                                                                                                                                                                 
                                                                    Goort[mob].top=Hitrt[hity][hitx].bottom;
                                                                    Mobgravity[mob]=0;
                                                                    
                                                                             
                                                                              } 
                                                                 
                                      }             
                             
                             
                             
                             
                                      
                                      if(hity==nAdhity && hitx==nAdhitx-1)
                                      {
                                        
                                                                
                                                              //�� ���� �浹
                                                                
                                                              if( !bmgoright[mob] && Goort[mob].left < Hitrt[hity][hitx].right && Goort[mob].left> Hitrt[hity][hitx].left &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                   
                                                                   Goort[mob].left = Hitrt[hity][hitx].right;
                                                                   bmgoright[mob] = true; 
                                                              }
                                                             
                                                              
                                                              
                                        }
                                        
                                      if(hity==nAdhity && hitx==nAdhitx)
                                      {
                                                       
                                                       
                                      }                
                                                       
                                      if(hity==nAdhity && hitx==nAdhitx+1)
                                      {
                                        
                                                                
                                                                //�� ���� �浹
                                                                
                                                             if( bmgoright[mob] && Goort[mob].left+40 < Hitrt[hity][hitx].right && Goort[mob].left+40 > Hitrt[hity][hitx].left &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                         
                                                                   Goort[mob].left = Hitrt[hity][hitx].left-40;
                                                                   bmgoright[mob] = false; 
                                                                   
                                                                   }

                                                                                                                             
                                                             
                                      } 
                                      
                                      if(hity==nAdhity+1 && hitx==nAdhitx-1)
                                      {
                                         //�� ���� �浹
                                                                
                                                              if( !bmgoright[mob] && Goort[mob].left < Hitrt[hity][hitx].right && Goort[mob].left> Hitrt[hity][hitx].left &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].top+35 > Hitrt[hity][hitx].top)          
                                                              {
                                                                   
                                                                   Goort[mob].left = Hitrt[hity][hitx].right;
                                                                   bmgoright[mob] = true; 
                                                              }
                                                              
                                                              //�� �� �浹 
                                                            if(Mobgravity[mob]<0 && Goort[mob].left+40 > Hitrt[hity][hitx].left && Goort[mob].left < Hitrt[hity][hitx].right && Goort[mob].top >= Hitrt[hity][hitx].top-40 && Goort[mob].top < Hitrt[hity][hitx].top)
                                                              {
                                                                    Goort[mob].top=Hitrt[hity][hitx].top-40;
                                                                    Mobgravity[mob]=0;
                                                               }
                                                              
                                                             
                                        }                 
                                                         
                                                         
                                                         
                                      if(hity==nAdhity+1 && hitx==nAdhitx)
                                      {
                                 
                                                            //�� �� �浹 
                                                            if(Mobgravity[mob]<0 && Goort[mob].left+40 > Hitrt[hity][hitx].left && Goort[mob].left < Hitrt[hity][hitx].right && Goort[mob].top >= Hitrt[hity][hitx].top-40 && Goort[mob].top < Hitrt[hity][hitx].top)
                                                              {
                                                                   
                                                              
                                                                   Goort[mob].top=Hitrt[hity][hitx].top-40;
                                                                    Mobgravity[mob]=0;
                                                                                                                      
                                                                                     }
                                                              
                                                               
                                        
                                                                              
                                      }
                                      
                                      
                                      
                                      
                                        
                                      if(hity==nAdhity+1 && hitx==nAdhitx+1)
                                      {
                                        
                                                              //�� ���� �浹
                                                                
                                                             if( bmgoright[mob] && Goort[mob].right < Hitrt[hity][hitx].right && Goort[mob].right > Hitrt[hity][hitx].left &&  Goort[mob].top < Hitrt[hity][hitx].bottom && Goort[mob].bottom > Hitrt[hity][hitx].top)          
                                                              {
                                                                         
                                                                   Goort[mob].left = Hitrt[hity][hitx].left-40;
                                                                   bmgoright[mob] = false; 
                                                                   
                                                                   }

                                                                  
                                                              
                                                              
                                                              //�� �� �浹 
                                                            if(Mobgravity[mob]<0 && Goort[mob].left+40 > Hitrt[hity][hitx].left && Goort[mob].left < Hitrt[hity][hitx].right && Goort[mob].top >= Hitrt[hity][hitx].top-40 && Goort[mob].top < Hitrt[hity][hitx].top)
                                                              {
                                                               
                                                                   Goort[mob].top=Hitrt[hity][hitx].top-40;
                                                                    Mobgravity[mob]=0;
                                                                                                                      
                                                                                     }                                                 
                                                               
                                                               }
      
      
      
      
      
                        }
              }
              }         
      }

 
 
      if(Player_rt.left%40 < 20)
       nAdhitx=(Player_rt.left-(Player_rt.left%40))/40;
 
      if(Player_rt.left%40 >= 20)
       nAdhitx=(Player_rt.left+40-(Player_rt.left%40))/40;
       
         
       if(gravity <= 0)
       nAdhity=(Player_rt.top-(Player_rt.top%40))/40;
       if(gravity > 0)
        nAdhity=(Player_rt.top+40-(Player_rt.top%40))/40;
       
       
       RightCollision=false;
       LeftCollision=false;
       UpCollision=false;
       DownCollision=false;
       
       if(!(nAdhity < 0 || nAdhity-1 >= mapy+1))
       {
                                                          
                              
                                                             
                                   if(nAdhity-1>=0)
                                   {                          

                                   //�� �浹 + �� �Ӹ� �� �浹 
                                      if(gravity>0 && Player_rt.left+40-mapmoving-sight > Hitrt[nAdhity-1][nAdhitx].left-mapmoving-sight && Player_rt.left-mapmoving-sight < Hitrt[nAdhity-1][nAdhitx].right-mapmoving-sight &&  Player_rt.top-ymoving < Hitrt[nAdhity-1][nAdhitx].bottom-ymoving && Player_rt.top-ymoving > Hitrt[nAdhity-1][nAdhitx].top-ymoving)                 
                                      {
                                       DownCollision=true;     
                                      }
                                   }
                             
                             
                                      
                                       //����  ���� �� �� �浹 + �� �浹 
                                                                
                                       if( accmove<0 && Player_rt.left-mapmoving-sight < Hitrt[nAdhity][nAdhitx-1].right-mapmoving-sight && Player_rt.left-mapmoving-sight> Hitrt[nAdhity][nAdhitx-1].left-mapmoving-sight &&  Player_rt.top-ymoving < Hitrt[nAdhity][nAdhitx-1].bottom-ymoving && Player_rt.top+35-ymoving > Hitrt[nAdhity][nAdhitx-1].top-ymoving)          
                                       {        
                                           nPlayermoving=0;            
                                         LeftCollision=true;              
                                       }
                                           
                                        //���� ������ �� �� �浹 + ���� �浹
                                                                
                                                               if( accmove>0 && Player_rt.left+40-mapmoving-sight < Hitrt[nAdhity][nAdhitx+1].right-mapmoving-sight && Player_rt.left+40-mapmoving-sight > Hitrt[nAdhity][nAdhitx+1].left-mapmoving-sight &&  Player_rt.top-ymoving < Hitrt[nAdhity][nAdhitx+1].bottom-ymoving && Player_rt.top+40-ymoving > Hitrt[nAdhity][nAdhitx+1].top-ymoving)          
                                                               {
                                                                           nPlayermoving=0;
                                                                          RightCollision=true;            
                                                               }
                                                               
                                  
                              
                              if(nAdhity+1<mapy)
                               {       

                                       //�� �Ʒ� �浹 �� �浹 
                                                            if(gravity<=0 && Player_rt.left+40-mapmoving-sight > Hitrt[nAdhity+1][nAdhitx].left-mapmoving-sight && Player_rt.left-mapmoving-sight < Hitrt[nAdhity+1][nAdhitx].right-mapmoving-sight && Player_rt.top-ymoving > Hitrt[nAdhity+1][nAdhitx].top-40-ymoving && Player_rt.top-ymoving < Hitrt[nAdhity+1][nAdhitx].top-ymoving)
                                                              {
                                                                
                                                            if(bGoRight)
                                                             cPlayerstate=2;
                                                             else if(!bGoRight)
                                                             cPlayerstate=1;

                                                                   UpCollision=true;
       
                                                                }                                   
                                 }                                                        
                                       
                          
                            

                             if(LeftCollision)                                  
                             {
                               Player_rt.left=Player_rt.left+(40-Player_rt.left%40);
                               Player_rt.right=Player_rt.left+40;
                              
                             }
                             
                             else if(RightCollision)
                             {
                               Player_rt.left=Player_rt.left-Player_rt.left%40;
                               Player_rt.right=Player_rt.left+40;
                             }
                                       
                             if(UpCollision)
                             {
                               Player_rt.top=Player_rt.top-Player_rt.top%40;
                               Player_rt.bottom=Player_rt.top+40;
                                gravity=0;
                                   bjump=false;
                             } 
                             else if(DownCollision)
                             {
                                
                               Player_rt.top=Player_rt.top+(40-Player_rt.top%40);
                               Player_rt.bottom=Player_rt.top+40;
                               bjump=true;                  
                               gravity=0;
                             }
                             }                
}












void Hitbyrgn()
{ 
    
 int hitx;
 int hity;
 
 
 int hitnx;
 int hitny;
 
 int nAdhitx=0;
 int nAdhity=0;

 
 RECT Wastert;
 
 
      if(Player_rt.left%40 < 20)
       nAdhitx=(Player_rt.left-(Player_rt.left%40))/40;
 
      if(Player_rt.left%40 >= 20)
       nAdhitx=(Player_rt.left+40-(Player_rt.left%40))/40;
       
         
       if(gravity <= 0)
       nAdhity=(Player_rt.top-(Player_rt.top%40))/40;
       if(gravity > 0)
        nAdhity=(Player_rt.top+40-(Player_rt.top%40))/40;
       
     
     
     
 for(hity=0;hity<mapy;hity++)
 {
  for(hitx=0;hitx<mapx;hitx++)         
   {  
     //�̰ž����� ���߿��� 2��������. 
    // if( !(RectInRegion(St1rgn[hity][hitx],&Player_rt)||RectInRegion(St2rgn[hity][hitx],&Player_rt)||RectInRegion(St3rgn[hity][hitx],&Player_rt)||RectInRegion(St4rgn[hity][hitx],&Player_rt)||RectInRegion(St5rgn[hity][hitx],&Player_rt)||RectInRegion(St6rgn[hity][hitx],&Player_rt)||RectInRegion(St7rgn[hity][hitx],&Player_rt)||RectInRegion(St8rgn[hity][hitx],&Player_rt))  )
    // bjump = true;
     
     
          //����浹  1. 
  if(RectInRegion(St1rgn[hity][hitx],&Player_rt)&& Player_rt.bottom > Stairpt1[hity][hitx].y && Player_rt.top > Stairpt1[hity][hitx].y-15)
  {
    
     
     gravity =0;
     bjump = true;
     Player_rt.top = Stairpt1[hity][hitx].y;
     Player_rt.bottom = Player_rt.top+40;
     

  }
   
     
       
 //�߶��� �浹 1������. 
 if( RectInRegion(St1rgn[hity][hitx],&Player_rt) && Player_rt.bottom < Stairpt1[hity][hitx].y && Player_rt.right > Stairpt1[hity][hitx].x && Player_rt.right < Stairpt1[hity][hitx].x+40)
 {
   bjump = false;
   gravity = 0;
   bInrgn = true;
   
   if(!(GetKeyState(VK_SPACE)&0x8000))
   {
    while(RectInRegion(St1rgn[hity][hitx],&Player_rt))
    Player_rt.bottom -=1;
    Player_rt.top = Player_rt.bottom-40;  
       
   }
        
 }
 
 //�߶��� �浹 �÷��� 1.
 if(RectInRegion(St1rgn[hity][hitx],&Player_rt) && Player_rt.right >= Stairpt1[hity][hitx].x+40 && Player_rt.bottom < Stairpt1[hity][hitx].y-10)    
 {
  bjump = false;
   gravity = 0;
   bInrgn = true;
   if(!(GetKeyState(VK_SPACE)&0x8000))   
  {
   Player_rt.bottom = -3 + Stairpt1[hity][hitx].y-15;
   Player_rt.top =  Player_rt.bottom-40;    
  }    
 }


 

 //�����̵��� �浹 1
  
 if(RectInRegion(St1rgn[hity][hitx],&Player_rt) && Player_rt.left < Stairpt1[hity][hitx].x && Player_rt.right > Stairpt1[hity][hitx].x && Player_rt.bottom > Stairpt1[hity][hitx].y ) 
 {
  if(accmove>0)
  {
  Player_rt.right = Stairpt1[hity][hitx].x;
  Player_rt.left = Stairpt1[hity][hitx].x-40;                                

  } 
 }
  
 
 //�����̵��� �浹 1������ .  
 if(RectInRegion(St1rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt1[hity][hitx].x+40 && Player_rt.bottom > Stairpt1[hity][hitx].y-15 )
 {
   if(accmove<0)
   {
    Player_rt.left = Stairpt1[hity][hitx].x+40 ;
    Player_rt.right = Player_rt.left + 40;
   
   }
                                 
 }
 
 
 
 
     
     
     
     
      
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
    //����浹  2 . 
  if( RectInRegion(St2rgn[hity][hitx],&Player_rt) && Player_rt.bottom > Stairpt2[hity][hitx].y && Player_rt.top < Stairpt2[hity][hitx].y && Player_rt.top > Stairpt2[hity][hitx].y-3 )
  {
    
     
     gravity =0;
     bjump = true;
     Player_rt.top = Stairpt2[hity][hitx].y;
     Player_rt.bottom = Player_rt.top+40;
     

  }
   
     
          
 //�߶��� �浹 2������. 
 if( RectInRegion(St2rgn[hity][hitx],&Player_rt) && Player_rt.bottom < Stairpt2[hity][hitx].y && Player_rt.right > Stairpt2[hity][hitx].x && Player_rt.right<Stairpt2[hity][hitx].x+40)
 {
   bjump = false;
   gravity = 0;
   bInrgn = true;
   
   if(!(GetKeyState(VK_SPACE)&0x8000))
   {
     while(RectInRegion(St2rgn[hity][hitx],&Player_rt))
     Player_rt.bottom -=1;
     Player_rt.top = Player_rt.bottom-40;  
       
   }
  
  
   
         
 }
 
 
 //�߶��� �浹 �÷��� 2.
 if(RectInRegion(St2rgn[hity][hitx],&Player_rt) && Player_rt.right >= Stairpt2[hity][hitx].x+40 && Player_rt.bottom < Stairpt2[hity][hitx].y-20)    
 {
  bjump = false;
   gravity = 0;
   bInrgn = true;
   if(!(GetKeyState(VK_SPACE)&0x8000))   
  {
   gravity = 0;
   Player_rt.bottom =1+ Stairpt2[hity][hitx].y-40;
   Player_rt.top =  Player_rt.bottom-40;;    
  }    
 }


 

 //�����̵��� �浹 2. 
 if( RectInRegion(St2rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt2[hity][hitx].x && Player_rt.left < Stairpt2[hity][hitx].x && Player_rt.bottom > Stairpt2[hity][hitx].y-20) 
 {
  if(accmove>0)
  {
  Player_rt.right = Stairpt2[hity][hitx].x;
  Player_rt.left = Player_rt.right-40;                               
 
  } 
 }
 
 
 //�����̵��� �浹 2������ . 
 if( RectInRegion(St2rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt2[hity][hitx].x+40 && Player_rt.left < Stairpt2[hity][hitx].x+40)
 {
  if(accmove<0)
  {
  Player_rt.left = Stairpt2[hity][hitx].x+40;
  Player_rt.right = Player_rt.left+40;
  }
                                 
 }
 
 
 
 
 
 




























  //����浹  3 . 
  if( RectInRegion(St3rgn[hity][hitx],&Player_rt) && Player_rt.bottom > Stairpt3[hity][hitx].y && Player_rt.top > Stairpt3[hity][hitx].y-15 )
  {
      
     
     gravity =0;
     bjump = true;
     Player_rt.top = Stairpt3[hity][hitx].y;
     Player_rt.bottom = Player_rt.top+40;
     
     

  }



   
          
 //�߶��� �浹 3������. 
 if( RectInRegion(St3rgn[hity][hitx],&Player_rt) && Player_rt.bottom <= Stairpt3[hity][hitx].y - 20 && Player_rt.right >= Stairpt3[hity][hitx].x && Player_rt.left <= Stairpt3[hity][hitx].x+40 )
 {
   bjump = false;
   gravity = 0;
   bInrgn = true;
   
   if(!(GetKeyState(VK_SPACE)&0x8000))
   {
    while(RectInRegion(St3rgn[hity][hitx],&Player_rt))
    Player_rt.bottom -=1;
    Player_rt.top = Player_rt.bottom-40;  
     
   }
  
 }
 
  //�߶��� �浹 �÷��� 3.
  
 if(RectInRegion(St3rgn[hity][hitx],&Player_rt) && Player_rt.left < Stairpt3[hity][hitx].x && Player_rt.right > Stairpt3[hity][hitx].x && Player_rt.bottom < Stairpt3[hity][hitx].y-10 )    
  {
  bjump = false;
   gravity = 0;
   bInrgn = true;
   
   if(!(GetKeyState(VK_SPACE)&0x8000))   
  {
                                         
   gravity = 0;
   Player_rt.bottom =1+ Stairpt3[hity][hitx].y-40;
   Player_rt.top =  Player_rt.bottom-40;
   
  
  }    
 }
 
 
 
 
 
 // �����̵��� �浹 3
  if(RectInRegion(St3rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt3[hity][hitx].x+40 && Player_rt.left < Stairpt3[hity][hitx].x+40 && Player_rt.bottom > Stairpt3[hity][hitx].y-20  )
  {
   if(accmove<0)
    {
     Player_rt.left = Stairpt3[hity][hitx].x+40;
     Player_rt.right = Player_rt.left+40;
      
    
    }
   } 
 
 
 


 // �����̵��� �浹 3
  if( RectInRegion(St3rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt3[hity][hitx].x && Player_rt.left < Stairpt3[hity][hitx].x && Player_rt.bottom > Stairpt3[hity][hitx].y-40 ) 
 {
     
   if(accmove>0)
   {
    Player_rt.right = Stairpt3[hity][hitx].x;
    Player_rt.left = Player_rt.right-40;            
   
   }
 
 }
 
 
 
 
 
 

















 // ����浹 4. 
  if( RectInRegion(St4rgn[hity][hitx],&Player_rt) && Player_rt.top < Stairpt4[hity][hitx].y && Player_rt.bottom > Stairpt4[hity][hitx].y && gravity>0 )  
   {
                                    
    Player_rt.top = Stairpt4[hity][hitx].y;
    Player_rt.bottom = Player_rt.top+40;
    bjump = true;
    gravity =0;       
    bInrgn = true;                        
   }


 //�߶����浹 4ȣ.
  if( RectInRegion(St4rgn[hity][hitx],&Player_rt) && Player_rt.bottom < Stairpt4[hity][hitx].y && Player_rt.left > Stairpt4[hity][hitx].x && Player_rt.left < Stairpt4[hity][hitx].x+40 )
  {
    bjump = false;
    gravity=0;
    
   if(!(GetKeyState(VK_SPACE)&0x8000))
   {   
    while(RectInRegion(St4rgn[hity][hitx],&Player_rt))
    Player_rt.bottom -=1;
    Player_rt.top = Player_rt.bottom-40;
   }  
      
      
  }
  
  
  //�߶����浹 �÷���4. 
  
   if(RectInRegion(St4rgn[hity][hitx],&Player_rt) && Player_rt.left <= Stairpt4[hity][hitx].x && Player_rt.bottom < Stairpt4[hity][hitx].y-10)    
 {
  bjump = false;
   gravity = 0;
   bInrgn = true;
   if(!(GetKeyState(VK_SPACE)&0x8000))   
  {
   Player_rt.bottom =  Stairpt4[hity][hitx].y-20;
   Player_rt.top =  Player_rt.bottom-40;    
  }    
 }
 
 
 
 
 


 // �����̵��� �浹4������ 
 
 if( RectInRegion(St4rgn[hity][hitx],&Player_rt)&& Player_rt.left < Stairpt4[hity][hitx].x && Player_rt.bottom > Stairpt4[hity][hitx].y-15  ) 
 { 

   if(accmove>0)
   {
   Player_rt.right = Stairpt4[hity][hitx].x;   
   Player_rt.left  = Player_rt.right-40;   
   }   
     
     
 } 
  

 // �����̵��� �浹 4. 
 if( RectInRegion(St4rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt4[hity][hitx].x+40 && Player_rt.bottom > Stairpt4[hity][hitx].y  ) 
 {
     
    if(accmove<0) 
    {
     Player_rt.left = Stairpt4[hity][hitx].x+40;
     Player_rt.right = Player_rt.left+40;               
    } 
     
     
 }
















 //�������5.
 if( RectInRegion(St5rgn[hity][hitx],&Player_rt) && Player_rt.top < Stairpt5[hity][hitx].y+20 && gravity>0)
 {
  bjump = true;
  gravity=0;
  
  while(RectInRegion(St5rgn[hity][hitx],&Player_rt))
  Player_rt.top+=1;
  
 
  Player_rt.bottom = Player_rt.top+40;   
     
     
     
     
     
     
     
 }                                     




 //�߶��浹5.
 if( RectInRegion(St5rgn[hity][hitx],&Player_rt) && Player_rt.bottom > Stairpt5[hity][hitx].y && Player_rt.top < Stairpt5[hity][hitx].y-20   )
 { 
   gravity = 0;
   bjump = false;
   Player_rt.bottom = Stairpt5[hity][hitx].y;
   Player_rt.top = Player_rt.bottom-40;  
     
 }
 
 
 //�����̵����浹5.
 if( RectInRegion(St5rgn[hity][hitx],&Player_rt) && Player_rt.left < Stairpt5[hity][hitx].x+40 && Player_rt.right > Stairpt5[hity][hitx].x+40 )
 {
   if(accmove<0)
   {
    Player_rt.left = Stairpt5[hity][hitx].x+40;             
    Player_rt.right = Player_rt.left+40;            
   }  
     
 }
 
 
 
 //�����̵����浹5 
 if( RectInRegion(St5rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt5[hity][hitx].x && Player_rt.left < Stairpt5[hity][hitx].x  )
 {
   if(accmove>0) 
   {
    Player_rt.right = Stairpt5[hity][hitx].x;
    Player_rt.left = Player_rt.right-40;
                
   }   
     
     
     
 }
 
 
 
 
 
 
 
 
 
 
 
//����浹 6. 
 if( RectInRegion(St6rgn[hity][hitx],&Player_rt) && Player_rt.top < Stairpt6[hity][hitx].y+20 && gravity>0)
 {
  bjump = true;
  gravity=0;
  
  while(RectInRegion(St6rgn[hity][hitx],&Player_rt))
  Player_rt.top+=1;
  
 
  Player_rt.bottom = Player_rt.top+40;   
     
      
 
 }
 
 
 
 
  //�߶��� �浹 6. 
  if( RectInRegion(St6rgn[hity][hitx],&Player_rt) && Player_rt.bottom > Stairpt6[hity][hitx].y-20 && Player_rt.top < Stairpt6[hity][hitx].y-20-20 ) 
 {
   gravity=0;
   bjump = false;
   Player_rt.bottom = Stairpt6[hity][hitx].y-20;
   Player_rt.top = Player_rt.bottom-40;
      
      
 }
 
 
 
 //���� 6
 if( RectInRegion(St6rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt6[hity][hitx].x+40 && Player_rt.left < Stairpt6[hity][hitx].x+40  ) 
 {
  if(accmove<0)
  {   
   Player_rt.left= Stairpt6[hity][hitx].x+40;
   Player_rt.right = Player_rt.left+40;    
  }   
     
 }
 
 //�����̵��� 6�� 
 if( RectInRegion(St6rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt6[hity][hitx].x && Player_rt.left < Stairpt6[hity][hitx].x && Player_rt.top < Stairpt6[hity][hitx].y )
 {
  if(accmove>0)
  {
   Player_rt.right = Stairpt6[hity][hitx].x;
   Player_rt.left  = Player_rt.right-40; 
               
  }   
     
 }
 
 
 
 











//����浹 7. 
 if( RectInRegion(St7rgn[hity][hitx],&Player_rt) && Player_rt.top < Stairpt7[hity][hitx].y+20 && gravity>0)
 {
  bjump = true;
  gravity=0;
  
  while(RectInRegion(St7rgn[hity][hitx],&Player_rt))
  Player_rt.top+=1;
  
 
  Player_rt.bottom = Player_rt.top+40;   
     
      
 
 }
 
 
 
 
  //�߶��� �浹7��. 
  if( RectInRegion(St7rgn[hity][hitx],&Player_rt) && Player_rt.bottom > Stairpt7[hity][hitx].y-40 && Player_rt.top < Stairpt7[hity][hitx].y-40-20 ) 
 {
   gravity=0;
   bjump = false;
   Player_rt.bottom = Stairpt7[hity][hitx].y-40;
   Player_rt.top = Player_rt.bottom-40;
      
      
 }


 //�����̵��� �浹 7
 if( RectInRegion(St7rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt7[hity][hitx].x+40 && Player_rt.left < Stairpt7[hity][hitx].x+40 && Player_rt.top < Stairpt7[hity][hitx].y-25 ) 
 {
   if(accmove<0)  
   {
    Player_rt.left = Stairpt7[hity][hitx].x+40;
    Player_rt.right = Player_rt.left+40;              
                  
   }  
     
     
     
 }
  //�����̵� �浹 7
  if( RectInRegion(St7rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt7[hity][hitx].x && Player_rt.left < Stairpt7[hity][hitx].x )
  {
      
    if(accmove>0)  
    {
     Player_rt.right = Stairpt7[hity][hitx].x;
     Player_rt.left = Player_rt.right-40;              
                   
    }  
      
      
      
      
      
  } 




























 //����浹 8. 
 if( RectInRegion(St8rgn[hity][hitx],&Player_rt) && Player_rt.top < Stairpt8[hity][hitx].y+20 && gravity>0)
 {
  bjump = true;
  gravity=0;
  
  while(RectInRegion(St8rgn[hity][hitx],&Player_rt))
  Player_rt.top+=1;
  
 
  Player_rt.bottom = Player_rt.top+40;   
     
      
 
 }
 
 
 
 
  //�߶��� �浹8��. 
  if( RectInRegion(St8rgn[hity][hitx],&Player_rt) && Player_rt.bottom > Stairpt8[hity][hitx].y-25 && Player_rt.top < Stairpt8[hity][hitx].y-45 ) 
 {
   gravity=0;
   bjump = false;
   Player_rt.bottom = Stairpt8[hity][hitx].y-20;
   Player_rt.top = Player_rt.bottom-40;
      
      
 }


  //�����̵� 8ȣ 
 if( RectInRegion(St8rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt8[hity][hitx].x+40 && Player_rt.left < Stairpt8[hity][hitx].x+40 && Player_rt.top < Stairpt8[hity][hitx].y-20 )
 {
  if(accmove<0)
  {
   Player_rt.left = Stairpt8[hity][hitx].x+40;
   Player_rt.right = Player_rt.left +40;
                
  }   
     
 }
 
  
 //�����̵� 8������ �ణ�� �� 
 if( RectInRegion(St8rgn[hity][hitx],&Player_rt) && Player_rt.right > Stairpt8[hity][hitx].x && Player_rt.left < Stairpt8[hity][hitx].x && Player_rt.top > Stairpt8[hity][hitx].y-20-10 )
 {
   if(accmove>0)  
   {
    Player_rt.right = Stairpt8[hity][hitx].x;
    Player_rt.left = Player_rt.right-40;
    
   }  
     
 }










  }
 }

}







HRGN Stairrgn(int nStairnum,  int nLeft,  int nBottom)
{ 
     HRGN Targetrgn;
     
  POINT Firstpt[] = {{nLeft,nBottom},{nLeft+40,nBottom},{nLeft+40,nBottom-20},{nLeft,nBottom}};
  POINT Secondpt[]= {{nLeft,nBottom},{nLeft+40,nBottom},{nLeft+40,nBottom-40},{nLeft,nBottom-20},{nLeft,nBottom}};     
  POINT Thirdpt[]=  {{nLeft,nBottom},{nLeft+40,nBottom},{nLeft+40,nBottom-20},{nLeft,nBottom-40},{nLeft,nBottom}};    
  POINT Fourthpt[]= {{nLeft,nBottom},{nLeft+40,nBottom},{nLeft,nBottom-20},{nLeft,nBottom}};    
  POINT Fifthpt[]=  {{nLeft,nBottom-40},{nLeft+40,nBottom-20},{nLeft+40,nBottom-40},{nLeft,nBottom-40}};    
  POINT Sixthpt[]=  {{nLeft,nBottom-20},{nLeft+40,nBottom},{nLeft+40,nBottom-40},{nLeft,nBottom-40},{nLeft,nBottom-20}};     
  POINT Seventhpt[]={{nLeft,nBottom},{nLeft+40,nBottom-20},{nLeft+40,nBottom-40},{nLeft,nBottom-40},{nLeft,nBottom}};     
  POINT Eighthpt[]= {{nLeft,nBottom-20},{nLeft+40,nBottom-40},{nLeft,nBottom-40},{nLeft,nBottom-20}};     
     
     
   
 
 
  switch(nStairnum)  
  {
     case 1:                              
             
     Targetrgn = CreatePolygonRgn(Firstpt,4,WINDING);
  
     return Targetrgn;  
     break;        
             
     
     case 2:
     
     Targetrgn = CreatePolygonRgn(Secondpt,5,WINDING);
     
     return Targetrgn;    
     break;          
             
             
     
     case 3:
     
     Targetrgn = CreatePolygonRgn(Thirdpt,5,WINDING);
     
     return Targetrgn;   
     break;  
     
     
     case 4:
     
     Targetrgn = CreatePolygonRgn(Fourthpt,4,WINDING);
    
     return Targetrgn;  
     break;  
     
     
     case 5:
     
     Targetrgn = CreatePolygonRgn(Fifthpt,4,WINDING);
    
     return Targetrgn; 
     break;  
     
     
     case 6:
     
     Targetrgn = CreatePolygonRgn(Sixthpt,5,WINDING);
    
     return Targetrgn; 
     break;  
     
     
     case 7:
     
     Targetrgn = CreatePolygonRgn(Seventhpt,5,WINDING);
     
     return Targetrgn;   
     break;  
     
     
     case 8:
     
     Targetrgn = CreatePolygonRgn(Eighthpt,4,WINDING);
     
     return Targetrgn;
     break;  
     
     default:
     return false;
     break;     
             
             
             
   }   
     
     
     
     
     
     
     
     
     
}




























void MapMoving()
{
     
            
                     
                     
                     
           if(bGoRight)
                {
                                
                           
                         
                                           
                                 if(Player_rt.left<mapx*40-(rt.right-nScreen))
                                  mapmoving=Player_rt.left-nScreen;  
                                   else
                                 mapmoving=mapx*40-rt.right;
                
                            
                           
                           if(bSightright)
                           {
                              bSightright=false;
                              nAdjustsight=-40;
                           }
                            
                           
                            
                            if((accmove==0 && nPlayermoving<0))
                             {
                                nPlayermoving+=4;
                             }
                             
                             if(accmove>=0 && sight>nPlayermoving)
                             {            
                                sight-=accmove*1;
                             }
                             
                             
                             
                            if(sight>nPlayermoving && sight<5+nPlayermoving){
                               sight=nPlayermoving;
                                }
                            
                            
                                   
           if(sight<0+nPlayermoving)
          {                              
              if(Player_rt.left<mapx*40-(rt.right-nScreen) || sight<nPlayermoving)
              {
                if(nAdjustsight<=70)
                {                                           
                 sight+=(nAdjustsight/10);
                 nAdjustsight+=10;          
                }
                else
                sight+=8;                
              }
               if(sight>=nPlayermoving-5 && sight<=nPlayermoving)
               sight=nPlayermoving;             
          } 
                           
                           
          
     
                           
    
                         
 }
                             
                             
                     
                             
                             
            if(!bGoRight)
            {                
                             
                        
                                
                              if(Player_rt.left<mapx*40-(rt.right-nScreen))
                                  mapmoving=Player_rt.left-nScreen;
                                   else
                                 mapmoving=mapx*40-rt.right;
                                 
                                 if(Player_rt.left-mapmoving<=nScreen)
                              {
                               mapmoving-=nScreen-(Player_rt.left-mapmoving);
                               }
            
                                                         
                             if(!bSightright)
                           {
                              bSightright=true;
                              nAdjustsight=40;
                           }
                              

                             // ��  ���� ���� 
                               if(accmove==0 && nPlayermoving>0)
                             {
                                nPlayermoving-=4;
                             }
                             
                             if(accmove<=0 && sight<-nScreen+nPlayermoving  )
                             {            
                                sight-=accmove*1;
                                   
                             }
                             
                             
                             
                            if(sight>-nScreen+nPlayermoving && sight<-(nScreen-5)+nPlayermoving){
                               sight=-nScreen+nPlayermoving;
                                }
                                
                               if(sight>=-(nScreen-5)+nPlayermoving)
                               {
                                             
                                                                                                                                 
                                      if(Player_rt.left+sight>(nScreen))
                                       {
                                         if(Player_rt.left<mapx*40-(nScreen*3/2))
                                         {
                                         
                                          if(nAdjustsight>=-70)
                                          {
                                           sight+=(nAdjustsight/10);
                                           nAdjustsight-=10;
                                          }
                                          else
                                          sight-=8;
                                           
                                         }
                                    
                                         
                                         
                                       }
                               }
                              
                               
                               
                               
                                
                                        
                                      if(Player_rt.left+sight<=(nScreen+10) )
                                      {
                                        sight+=nScreen-(Player_rt.left+sight);
                                     
                                      }
                                     
                                    
                                     if(Player_rt.left+sight<nScreen){
                                      sight-=accmove*2;
                                     
                                     }
                                     
                           
                                    
                                        
                                           
                                            
                            
                             
           }
           
            if(sight<-nScreen)
           sight=-nScreen;
           
           if(sight>0)
          {
              sight=0;
          }
            
           if(Player_rt.left<=nScreen){
                            
                             mapmoving=0;
                             sight=0;
                             }
         

if(Player_rt.top<=560)
{
   ymoving=0;
}
else if(Player_rt.top>=mapy*40-208)
{
    ymoving=mapy*40-768;
}//560
else
{
    ymoving=Player_rt.top-560;
}   

}


//�� ���� 
void Killgoo()
{
     HWND hWnd;
     RECT frt;  //���ǹ� 
      //RECT atkrt;  // �ٰŸ� ���� ���� ���� 
      RECT satkrt[16]={0}; // ���Ÿ� ���� ���� ���� 
      int rtnum=0;
      int hity,hitx; 
     
     
     
     for(int num=0;num<500;num++)//�����Լ��� 
     {
           if(IntersectRect(&frt,&Function1rt[num],&Dragonrt) && !bFunction1atk )    
           {
             Dragonhealth-=Dmg; 
             bFunction1atk = true;
           } 
             
             
             
             
             
             for(rtnum=0;rtnum<mobnum4040;rtnum++)
             {
                if(IntersectRect(&frt,&Function1rt[num],&Goort[rtnum]) && !bFunction1atk )                                  
                {
                  Mobhealth[rtnum]-=Dmg;                                 
                  bFunction1atk = true;  
                }                                 
             }
             
     }
     
     
     
     
     
     
     switch(cNumweapon)
     {
                       
        case 1:               
                       
      
     if(bGoRight&&bAttack) 
     SetRect(&atkrt,Player_rt.right,Player_rt.top,Player_rt.right+40,Player_rt.bottom);
     else if(!bGoRight&&bAttack)
     SetRect(&atkrt,Player_rt.left-40,Player_rt.top,Player_rt.left,Player_rt.bottom);
     else if(!bAttack)
     SetRectEmpty(&atkrt);
     
     
      //���ݰ����浹 

                       
                        // 4040 ��  
                        
                        
                          for(rtnum=0;rtnum<mobnum4040;rtnum++){          
                          if((IntersectRect(&frt,&Goort[rtnum],&atkrt) )){
                                   Mobhealth[rtnum]-=(Dmg+combo);
                                   comboI++;
                          
                                   }
                          //��
                          if(IntersectRect(&frt,&Dragonrt,&atkrt))         
                          {
                              Dragonhealth-=(Dmg+combo);
                                            
                              SetRectEmpty(&atkrt);                   
                                                 
                                                 }         
                                   
                                   }
                                   
                                   
                                                                                             
                             
     break;
     
     case 2:
          
          
          
          for(int shoot=0;shoot<16; shoot++)
          {
             for(rtnum=0;rtnum<mobnum4040;rtnum++)
             {          
                 if((IntersectRect(&frt,&Goort[rtnum],&Bulletrt[shoot]) && bBulletAK[shoot]))
                 {
                   Mobhealth[rtnum]-=(Dmg+combo);
                    bBulletAK[shoot]=false;
                   SetRectEmpty(&Bulletrt[shoot]);
                 }
                                   
                                   
                                   
                                   
             }
                                  
                  if(IntersectRect(&frt,&Dragonrt,&Bulletrt[shoot]) && bBulletAK[shoot])                           
                   {
                      Dragonhealth-=(Dmg+combo);   
                      bBulletAK[shoot]=false;
                      SetRectEmpty(&Bulletrt[shoot]);
                               
                   } 
                                   
                                   
            }
                                   
      
           
     
    break; //������ ����� �̰ſ־Ƚ��;    *�Ƚᵵ�ǳ�? 
      }
               //������ʹ� ������ 
       for(rtnum=0;rtnum<mobnum4040;rtnum++)
       {
                 if((IntersectRect(&frt,&Goort[rtnum],&Player_rt)&&!bMobdie[rtnum])&&!bZhonya)
                 {         
                     Playerhealth -=Mobdmg;
                                    
                                    
                      if((Player_rt.left>Goort[rtnum].left))
                      bKnockl  = true;
                      if((Player_rt.left<Goort[rtnum].left)) 
                      bKnockr = true; 
                       
                       bZhonya = true;        
                  }    
                                             
                                             
                                             
                                             
                                             
                                             
                                             
                                             
                                             
                                             
                                                                                         
        }

         if(IntersectRect(&frt,&Dragonrt,&Player_rt)&&!bDragondie&&!bZhonya)
         {
                                Playerhealth -= Dragondmg;
                                
                                
                               if((Player_rt.left>Dragonrt.left))
                                    bKnockl  = true;
                                    if((Player_rt.left<Dragonrt.left)) 
                                    bKnockr = true; 
                                
                                bZhonya = true;
                                
                                }
                                
         for(int mob=0; mob<128; mob++)   
          {                                    
              for(int shoot=0; shoot<3; shoot++)
               {                      
                   if( IntersectRect(&frt,&Player_rt,&Mobbulletrt[mob][shoot]) && !bZhonya )             
                     {
                                                                              
                      Playerhealth-=Mobdmg;
                      SetRect(&Mobbulletrt[mob][shoot],-1000,-1000,-1000,-1000);
                      bZhonya = true;
                      if((Player_rt.left>Mobbulletrt[mob][shoot].left))
                      bKnockl  = true;
                      if((Player_rt.right<Mobbulletrt[mob][shoot].right)) 
                      bKnockr = true; 
                                  
                        
                        
                      }           
                 //  if( RectInRegion(Guardrgn,&Mobbulletrt[mob][shoot]) )
                  // SetRect(&Mobbulletrt[mob][shoot],-1000,-1000,-1000,-1000);  
                     
                          
               }          
           }
                                
                                
                                
                                
                                
                                
                                
                                
                                

}


void Mobatk()
{
  RECT wastert;    
  HWND hWnd;    
  for(int mob=0; mob<128; mob++)   
  {
      if(IntersectRect(&wastert,&Player_rt,&Mobfindrt[mob]) && !bMobdie[mob])   
      {
       bMobatk[mob] = true;
      }
   
   for(int shoot=0; shoot<3; shoot++)
   {
    if(bMobatk[mob])   
    {
    // if(&Mobbulletrt[mob][shoot]==ũ�� 0)                 
     {
       //���������� �����Ѵ�                 
      if(Player_rt.right > Goort[mob].right)
      {
      // bmgoright[mob] = true;
      
       if( !bMobbulletfly[mob][shoot] && !bMobatkwait[mob] )
       {   
       Mobakl[mob][shoot]=Goort[mob].left + 300;   
       SetRect(&Mobbulletrt[mob][shoot],Goort[mob].left+40,Goort[mob].top+10,Goort[mob].right+40,Goort[mob].bottom-10);
       SetTimer(hWnd,22,1000,NULL);
       bMobatkright[mob][shoot] = true;
       bMobbulletfly[mob][shoot] = true;         
       }
         
      } 
      
      //�������ε� �߸� �����ȴ�
      if(Player_rt.right < Goort[mob].right)               
      {               
      // bmgoright[mob] = false;
     
       if( !bMobbulletfly[mob][shoot] && !bMobatkwait[mob] )
       {
       Mobakl[mob][shoot]=Goort[mob].right - 300;         
       SetRect(&Mobbulletrt[mob][shoot],Goort[mob].left-40,Goort[mob].top+10,Goort[mob].right-40,Goort[mob].bottom-10);
       SetTimer(hWnd,22,1000,NULL);
       bMobatkright[mob][shoot] = false;  
       bMobbulletfly[mob][shoot] = true;
       }
     
      }
     }
     
     
                                                        
                                                       
                                                            
                                                        
                                                        
      
      
      
    } 
      
                        
  } 
     
     
     
     
     
     
     
     
     
  }   
}


void Mobatkhelp()
{
     
  for(int mob=0; mob<128; mob++)   
  { 
      for(int shoot=0; shoot<3; shoot++)   
      {
                                         //���� ���� ���󰡶� 
                                         if( (Mobakl[mob][shoot]<Mobbulletrt[mob][shoot].left) && !bMobatkright[mob][shoot] && bMobbulletfly[mob][shoot] )
                                         {
                                          Mobbulletrt[mob][shoot].left-=30/2;
                                          Mobbulletrt[mob][shoot].right-=30/2;
                                         }
                                         if(Mobakl[mob][shoot]>=Mobbulletrt[mob][shoot].left && !bMobatkright[mob][shoot])
                                         {
                                          bMobbulletfly[mob][shoot] = false;
                                            SetRect(&Mobbulletrt[mob][shoot],-1000,-1000,-1000,-1000);
                                         }
                                                             
                                         //�����ʵ� ����...             
                                         if((Mobakl[mob][shoot]>Mobbulletrt[mob][shoot].right) && bMobatkright[mob][shoot] && bMobbulletfly[mob][shoot] )
                                         {
                                          Mobbulletrt[mob][shoot].left+=30/2;
                                          Mobbulletrt[mob][shoot].right+=30/2;
                                         }
                                         if(Mobakl[mob][shoot]<=Mobbulletrt[mob][shoot].right && bMobatkright[mob][shoot])
                                         {
                                          bMobbulletfly[mob][shoot] = false;                                                    
                                            SetRect(&Mobbulletrt[mob][shoot],-1000,-1000,-1000,-1000);
                                         }
                                                        
      }
  }
     
}



























void Playermobwork()//ü��ǥ�� 
{
     
     TCHAR health[128];
	TCHAR mhealth[128];
	
    wsprintf(health,TEXT("%d"),Playerhealth);
   
     
     
     //���״°�����                   
                                      for(int wff=0;wff<mobnum4040;wff++)
                                      {         
                                      if(Mobhealth[wff]<=0){
                                                     bMobdie[wff] = true;
                                                     SetRect(&Goort[wff],10000,10000,10000,10000);
                                                     }
                                                     else
                                                     bMobdie[wff] = false;
                                      }  
                                      
                                  //�뵵 �׽��ϴ�.                 
     
     
                                      if(Dragonhealth<=0){
                                                     bDragondie = true;
                                                     SetRect(&Dragonrt,10000,10000,10000,10000);     
                                                          
                                                          
                                                          }
                                                        else
                                                        bDragondie = false;  
                                                                
                                      
                                      
                                      
                                      
                                      
                                      
                                      
                                      
                                      
                                                                
                             //���� �״°� ���� 
                                      if(Playerhealth<=0) {
                                           Playerhealth = 0;
                                           bPlayerdie = true;
                                           CharacterBitmap = NULL;
                                          SetRect(&Player_rt,-1000,-1000,-1000,-1000);
                                           }
                                           else
                                           bPlayerdie = false;
                                                         
     
     
     
     //ü�� ���̰� 
       
       TCHAR ascreen[128];  //ȭ�� 
wsprintf(ascreen,TEXT("%d"),rt.right);
TextOut(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-100-ymoving,ascreen,lstrlen(ascreen)); 
       
       TCHAR Mapmoving[128]; TCHAR Sight[128]; // mapmoving  ,sight
        if(UpCollision)
        wsprintf(Mapmoving,TEXT("1"));
        else if(!UpCollision)
        wsprintf(Mapmoving,TEXT("0"));
        
        TextOut(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-80-ymoving,Mapmoving,lstrlen(Mapmoving));
        
        wsprintf(Sight,TEXT("%d"),Player_rt.top);
        TextOut(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-60-ymoving,Sight,lstrlen(Sight)); 
       
        //TextOut(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-20-ymoving,health,lstrlen(health)); 
    
       for(int wff=0;wff<mobnum4040;wff++){
       wsprintf(mhealth,TEXT("%d"),Mobhealth[wff]);  
        TextOut(MemDC,Goort[wff].left-mapmoving-sight,Goort[wff].top-20-ymoving,mhealth,lstrlen(mhealth)); 
        }
        
    TCHAR dragonhealth[128];
        wsprintf(dragonhealth,TEXT("%d"),Dragonhealth-ymoving);
        
       if(nNumstage==2)
       {
       SetTextColor(MemDC,RGB(255,255,0));               
       TextOut(MemDC,(Dragonrt.left+Dragonrt.right)/2-mapmoving-sight,Dragonrt.top-60-ymoving,dragonhealth,lstrlen(dragonhealth));
       
       }
       else
       {} 
    
     TCHAR istrue[128];
     wsprintf(istrue,TEXT("%d"),  bFunction3ready);
       TextOut(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-120-ymoving,istrue,lstrlen(istrue));  
     
     
 }
 
 
 
//  ��� ���
void PTBackGround()
{
     if(nNumstage==0)
     {
           StretchDrawBitmap(MemDC,0,0,1366,768,bkSeaBitmap,0,0,320,240);          
     }
     
     if(nNumstage==1)
     {
         
           StretchDrawBitmap(MemDC,0,0,1366,768,bkMoonBitmap,0,0,320,240);
     }
     
     if(nNumstage==2)
     {
           StretchDrawBitmap(MemDC,0,0,1366,768,bkMoonBitmap,0,0,320,240);
     }               
    //  else
      //  bDragonable = false;
}
 


void Scanmap()
{
     free(currentstage);
	  free(Hitrt);
      free(Siderrt);
      free(Sidelrt);
       free(St1rgn);
       free(St2rgn);
       free(St3rgn);
       free(St4rgn);
       free(St5rgn);
       free(St6rgn);
       free(St7rgn);
       free(St8rgn); 
     free(Stairpt1);
     free(Stairpt2);
     free(Stairpt3);
     free(Stairpt4);
     free(Stairpt5);
     free(Stairpt6);
     free(Stairpt7);
     free(Stairpt8);
     
     
     
     
     
     int i,j;
     if(nNumstage==0)
     {
        FILE *Map=fopen("Map0001.txt", "r");            
        mapx=100;
        mapy=24;               
        
        currentstage=(int**)malloc(sizeof(int *)*mapy);
        for(i=0;i<mapy;i++)
        {
           currentstage[i]=(int *)malloc(sizeof(int)*mapx);
        }
        
        for(j=0;j<mapy;j++)
        {
          for(i=0;i<mapx;i++)
           {
             fscanf(Map,"%d",&currentstage[j][i]);
           }
        }
        
      fclose(Map);  
     }

    
    if(nNumstage==1)
     {
        FILE *Map=fopen("Map0002.txt", "r");            
        mapx=100;
        mapy=20;               
        currentstage=(int**)malloc(sizeof(int *)*mapy);
        for(i=0;i<mapy;i++)
        {
           currentstage[i]=(int *)malloc(sizeof(int)*mapx);
        }
        
        for(j=0;j<mapy;j++)
        {
          for(i=0;i<mapx;i++)
           {
             fscanf(Map,"%d",&currentstage[j][i]);
           }
        }
        
      fclose(Map);  
     }
     
     if(nNumstage==2)
     {
        FILE *Map=fopen("Map0003.txt", "r");            
        mapx=100;
        mapy=20;               
        currentstage=(int**)malloc(sizeof(int *)*mapy);
        for(i=0;i<mapy;i++)
        {
           currentstage[i]=(int *)malloc(sizeof(int)*mapx);
        }
        
        for(j=0;j<mapy;j++)
        {
          for(i=0;i<mapx;i++)
           {
             fscanf(Map,"%d",&currentstage[j][i]);
           }
        }
        
      fclose(Map);  
     }
     
     Hitrt=(RECT**)malloc(sizeof(RECT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Hitrt[hity]=(RECT *)malloc(sizeof(RECT)*mapx);
        }
     
     
     
     
     Siderrt=(RECT**)malloc(sizeof(RECT *)*mapy);
       for(int hity=0;hity<mapy;hity++)
       {
            Siderrt[hity]=(RECT *)malloc(sizeof(RECT)*mapx);
        }
        
        Sidelrt=(RECT**)malloc(sizeof(RECT *)*mapy);
       for(int hity=0;hity<mapy;hity++)
       {
            Sidelrt[hity]=(RECT *)malloc(sizeof(RECT)*mapx);
        }

      

       St1rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St1rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }
        
       St2rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St2rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }
       
        St3rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St3rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }

        St4rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St4rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }  

        St5rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St5rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }

        St6rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St6rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }        

        St7rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St7rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }

        St8rgn=(HRGN**)malloc(sizeof(HRGN *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           St8rgn[hity]=(HRGN *)malloc(sizeof(HRGN)*mapx);
        }
 
        
        Stairpt1=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt1[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 

       
        Stairpt2=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt2[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 
        
      
        Stairpt3=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt3[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 

        Stairpt4=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt4[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 

        
        Stairpt5=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt5[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 

       
        Stairpt6=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt6[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 

       
        Stairpt7=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt7[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 
 
       
        Stairpt8=(POINT**)malloc(sizeof(POINT *)*mapy);
        for(int hity=0;hity<mapy;hity++)
        {
           Stairpt8[hity]=(POINT *)malloc(sizeof(POINT)*mapx);
        } 













      // �浹���� ���� 
     for(int hity=0;hity<mapy;hity++)
      {
       for(int hitx=0;hitx<mapx;hitx++)
         {
           if(currentstage[hity][hitx]==2)
           SetRect(&Hitrt[hity][hitx],hitx*40,hity*40,hitx*40+40,hity*40+40);
           else
           SetRectEmpty(&Hitrt[hity][hitx]);   
               
           if((currentstage[hity][hitx]==2)&&(currentstage[hity][hitx+1]==0))                      
            SetRect(&Siderrt[hity][hitx],hitx*40+40,hity*40-40,hitx*40+80,hity*40);           
           else
            SetRectEmpty(&Siderrt[hity][hitx]);
                      
             if((currentstage[hity][hitx]==2)&&(currentstage[hity][hitx-1]==0))                      
            SetRect(&Sidelrt[hity][hitx],hitx*40-40,hity*40-40,hitx*40,hity*40);                    
             else
             SetRectEmpty(&Sidelrt[hity][hitx]);      
           
           
         
           //������ʹ� �浹����  
           if(currentstage[hity][hitx]==11) 
           {  
           St1rgn[hity][hitx] = Stairrgn(1,hitx*40,hity*40);  
           Stairpt1[hity][hitx].x = hitx*40; Stairpt1[hity][hitx].y = hity*40;
           }
          
            
           if(currentstage[hity][hitx]==12)   
           {
           St2rgn[hity][hitx] = Stairrgn(2,hitx*40,hity*40);
           Stairpt2[hity][hitx].x = hitx*40; Stairpt2[hity][hitx].y = hity*40;   
           }
      
           
           if(currentstage[hity][hitx]==13)   
           {
           St3rgn[hity][hitx] = Stairrgn(3,hitx*40,hity*40);  
           Stairpt3[hity][hitx].x = hitx*40; Stairpt3[hity][hitx].y = hity*40;   
           }
          
             
           if(currentstage[hity][hitx]==14)   
           {
           St4rgn[hity][hitx] = Stairrgn(4,hitx*40,hity*40); 
           Stairpt4[hity][hitx].x = hitx*40; Stairpt4[hity][hitx].y = hity*40;     
           }
          
           
           if(currentstage[hity][hitx]==15)   
           {
           St5rgn[hity][hitx] = Stairrgn(5,hitx*40,hity*40);  
           Stairpt5[hity][hitx].x = hitx*40; Stairpt5[hity][hitx].y = hity*40-40;   
           }
          
           
           if(currentstage[hity][hitx]==16)   
           {
           St6rgn[hity][hitx] = Stairrgn(6,hitx*40,hity*40);  
           Stairpt6[hity][hitx].x = hitx*40; Stairpt6[hity][hitx].y =hity*40-20;   
           }
          
            
           if(currentstage[hity][hitx]==17)   
           {
           St7rgn[hity][hitx] = Stairrgn(7,hitx*40,hity*40);  
           Stairpt7[hity][hitx].x = hitx*40; Stairpt7[hity][hitx].y = hity*40;    
           }
         
         
           if(currentstage[hity][hitx]==18)   
           {
           St8rgn[hity][hitx] = Stairrgn(8,hitx*40,hity*40);  
           Stairpt8[hity][hitx].x = hitx*40; Stairpt8[hity][hitx].y = hity*40-20;   
           }
        
           
           
           
           
           
           
           
           
           
                           
                                             }
                                           }
     
     

     
}



//�� �̵� 
void Dragonmove()
{    
            RECT frt;             
                      
                      
                
                                
               DcountI++;
               DlcountI++;
               if(bDragongoright)
               {
                                 
                if(DcountI>=4)
                {
                Dcount++;
                DcountI=0;
                }
               }
               if(!bDragongoright)
               {
                                     
                if(DlcountI>=4)
                {
                Dlcount++;
                DlcountI=0;
                }
               }            
                      
                      
                      
                      
                        
                                //������̴°� 
              if(bDragonable&&!bDragondie&&(Dragonrt.right>(mapx*40)))                
                  bDragongoright = false; 
              if(bDragonable&&!bDragondie&&(Dragonrt.left<0))                
                  bDragongoright = true;             
                                
                                
                        
               if(bDragonable&&!bDragondie&&bDragongoright)
               {                 
                 
                                 
                SetRect(&Dragonrt,Dragonrt.left+5/4,Dragonrt.top,Dragonrt.right+5/4,Dragonrt.top+230);                                
                SetRect(&Dragonfindrt,Dragonrt.left-300,Dragonrt.top-300,Dragonrt.right+300,Dragonrt.bottom+300);
            
          
            
               
               }
             
             if(bDragonable&&!bDragondie&&!bDragongoright)
             {
                                                          
               SetRect(&Dragonrt,Dragonrt.left-5/3,Dragonrt.top,Dragonrt.right-5/3,Dragonrt.top+230);                  
               SetRect(&Dragonfindrt,Dragonrt.left-300,Dragonrt.top-300,Dragonrt.right+300,Dragonrt.bottom+300);

             }
            

     
}


void Dragonangry()
{
     RECT frt;
     
     if(Dragonhealth<1000){
     bDragonatk = true;
     
     }
     
     if(bDragonatk)
     {
       if(IntersectRect(&frt,&Dragonfindrt,&Player_rt)&&(Dragonrt.right>Player_rt.right)&&bDragongoright)
       {
                                                                                                         
         bDragongoright = false;
          
         if((Dragonrt.top<Player_rt.top)) 
         {
                                                                        
          Dragonrt.top+=5;
          
          }
         if((Dragonrt.top>Player_rt.top)) 
          {
                                          
          Dragonrt.top-=5; 
          
          }
          
          
                                                        
       }  
      else if(!IntersectRect(&frt,&Dragonfindrt,&Player_rt))
      {
      bDragonatk = false;
      //if(Dragonhealth>=900)
      //Dragonhealth=1000;
      //else          
      //Dragonhealth+=100;              
      }      
       if(IntersectRect(&frt,&Dragonfindrt,&Player_rt)&&(Dragonrt.right<Player_rt.right)&&!bDragongoright)
       {                                                                                             
                                                                                                          
                                                                                                   
         bDragongoright = true;
                  
                  
         if((Dragonrt.top<Player_rt.top)) 
          Dragonrt.top+=5;         
          if((Dragonrt.top>Player_rt.top))
          Dragonrt.top-=5;           
                                                       
       }           
       else if(!IntersectRect(&frt,&Dragonfindrt,&Player_rt))
      {
      bDragonatk = false; 
    
      if(Dragonhealth>=990)
      Dragonhealth=1000;
      else          
      Dragonhealth+=5;            
      
      
      }
     }
       
     
}






void Mobangry()
{
     
     RECT frt;
     
     for(int mobnum=0;mobnum<num5;mobnum++)
     {
             for(int shoot=0;shoot<16;shoot++)
             {
              if(IntersectRect(&frt,&Mobrt[mobnum],&atkrt) || IntersectRect(&frt,&Mobrt[mobnum],&Bulletrt[shoot]))
               {
                if(Player_rt.left<Mobrt[mobnum].left)
                bNum5right[mobnum]=false;
                if(Player_rt.left>Mobrt[mobnum].left)
                bNum5right[mobnum]=true;
                                                             
              }
     }
}    
     for(int mobnum=num5;mobnum<num5+num6;mobnum++)
     {
             for(int shoot=0;shoot<16;shoot++)
             {
              if(IntersectRect(&frt,&Mobrt[mobnum],&atkrt) || IntersectRect(&frt,&Mobrt[mobnum],&Bulletrt[shoot]))
               {
                if(Player_rt.left<Mobrt[mobnum].left)
                bNum6right[mobnum]=false;
                if(Player_rt.left>Mobrt[mobnum].left)
                bNum6right[mobnum]=true;
                                                             
              }
     }
}    
     for(int mobnum=num5+num6;mobnum<num5+num6+num7;mobnum++)
     {
             for(int shoot=0;shoot<16;shoot++)
             {
              if(IntersectRect(&frt,&Mobrt[mobnum],&atkrt) || IntersectRect(&frt,&Mobrt[mobnum],&Bulletrt[shoot]))
               {
                if(Player_rt.left<Mobrt[mobnum].left)
                bNum7right[mobnum]=false;
                if(Player_rt.left>Mobrt[mobnum].left)
                bNum7right[mobnum]=true;
                                                             
              }
     }         
}          
          
}



 






void Mobmove() // �� �̵��Ÿ� 
{
     RECT brt;
      
      
      
      
                                 //�������̴°� 
          for(int Mobnum=0;Mobnum<128;Mobnum++)
          { 
            if(!bMobdie[Mobnum]&&bmgoright[Mobnum])
             {
             SetRect(&Goort[Mobnum],Goort[Mobnum].left+5,Goort[Mobnum].top,Goort[Mobnum].right+5,Goort[Mobnum].top+40);                                
            
             }
             
             if(!bMobdie[Mobnum]&&!bmgoright[Mobnum])
             {
             SetRect(&Goort[Mobnum],Goort[Mobnum].left-5,Goort[Mobnum].top,Goort[Mobnum].right-5,Goort[Mobnum].top+40);                                
             }
             
             
               SetRect(&Mobfindrt[Mobnum],Goort[Mobnum].left-400,Goort[Mobnum].top-200,Goort[Mobnum].right+40+400,Goort[Mobnum].bottom+40+200);
             
             
           /*  // num 5
             if(!bMobdie[num3+Mobnum]&&bNum5right[Mobnum])
             {
             SetRect(&Mobrt[Mobnum],Mobrt[Mobnum].left+5,Mobrt[Mobnum].top,Mobrt[Mobnum].right+5,Mobrt[Mobnum].bottom);                                
            
             }
             
             if(!bMobdie[num3+Mobnum]&&!bNum5right[Mobnum])
             {
             SetRect(&Mobrt[Mobnum],Mobrt[Mobnum].left-5,Mobrt[Mobnum].top,Mobrt[Mobnum].right-5,Mobrt[Mobnum].bottom);                                
             }

             //num6
              if(!bMobdie[num3+num5+Mobnum]&&bNum6right[Mobnum])
             {
             SetRect(&Mobrt[num5+Mobnum],Mobrt[num5+Mobnum].left+5,Mobrt[num5+Mobnum].top,Mobrt[num5+Mobnum].right+5,Mobrt[num5+Mobnum].top+40);                                
            
             }
             
             if(!bMobdie[num3+num5+Mobnum]&&!bNum6right[Mobnum])
             {
             SetRect(&Mobrt[num5+Mobnum],Mobrt[num5+Mobnum].left-5,Mobrt[num5+Mobnum].top,Mobrt[num5+Mobnum].right-5,Mobrt[num5+Mobnum].top+40);                                
             }
             
             //num7
             if(!bMobdie[num3+num5+num6+Mobnum]&&bNum7right[Mobnum])
             {
             SetRect(&Mobrt[num5+num6+Mobnum],Mobrt[num5+num6+Mobnum].left+5,Mobrt[num5+num6+Mobnum].top,Mobrt[num5+num6+Mobnum].right+5,Mobrt[num5+num6+Mobnum].top+40);                                
            
             }
             
             if(!bMobdie[num3+num5+num6+Mobnum]&&!bNum7right[Mobnum])
             {
             SetRect(&Mobrt[num5+num6+Mobnum],Mobrt[num5+num6+Mobnum].left-5,Mobrt[num5+num6+Mobnum].top,Mobrt[num5+num6+Mobnum].right-5,Mobrt[num5+num6+Mobnum].top+40);                                
             }
           */
           }
           
                     
          
          
          
                                
                                //�� �߷� 
                               for(int uhb=0;uhb<128;uhb++)
                               {
                                 if(!bMobdie[uhb]) 
                                 { 
                                  Goort[uhb].top -= (Mobgravity[uhb] / 10);
                               
                                  if( Mobgravity[uhb]>-300  && Mobgravity[uhb]<=300)
                                  {
                                  Mobgravity[uhb] -= 20;
                                  }
                                  
                                  
                                 }
                               }  
      
      
     for(int bidulgi=0;bidulgi<mobnum4040;bidulgi++)
     {
             for(int hity=0;hity<mapy;hity++)
             {
               for(int hitx=0;hitx<mapx;hitx++)
               { 
                  if(!bmgoright[bidulgi])
                  {
                        
                         if(IntersectRect(&brt,&Sidelrt[hity][hitx],&Goort[bidulgi]))
                         {
                          bmgoright[bidulgi]=true;
                          SetRect(&Goort[bidulgi],Sidelrt[hity][hitx].right,Sidelrt[hity][hitx].top,Sidelrt[hity][hitx].right+40,Sidelrt[hity][hitx].bottom);
                         }           
                  }     
                       
                            
                 if( bmgoright[bidulgi] )
                 {
                   if(IntersectRect(&brt,&Siderrt[hity][hitx],&Goort[bidulgi]))
                   {
                   bmgoright[bidulgi]=false;
                   SetRect(&Goort[bidulgi],Siderrt[hity][hitx].left-40,Siderrt[hity][hitx].top,Siderrt[hity][hitx].left,Siderrt[hity][hitx].bottom);
                   }
                 }
             
                  
                  
                  
                  
                  
                  
                  
                  
                  
                  
               }
             }
     }
     
}




void Playermove() // �÷��̾� �̵��� �ִϸ��̼� 
{ 
  SelectObject(DrawDC,CharacterBitmap);
     
      if(!bPlayerdie)
   {
       
       //TransparentBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top,40,40,DrawDC,0,0,16,16,RGB(0,0,0));
       //StretchBlt(MemDC,Stretchdrawx,Stretchdrawy,Stretchsizex,Stretchsizey,BackGroundDC,drawx,drawy,sizex,sizey,SRCCOPY);
            if(bGoRight)
          {
                  TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,0,40,RGB(0,0,0));
                   
            switch(nPlayeranimate)//��� �����Ӵ��� �ִϸ��̼�. 
            {
              case 1: case 2: case 3: case 4:                    
               SelectObject(DrawDC, CharacterBitmap);
               nPlayeranimate++; 
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,0,40,RGB(0,0,0));
              break;
                             
                             
              case 5: case 6: case 7: case 8: 
               SelectObject(DrawDC,CharacterBitmap);
               nPlayeranimate++; 
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,40,40,RGB(0,0,0));
              break;      
                        
                            
              case 9: case 10: case 11: case 12:
               SelectObject(DrawDC,CharacterBitmap);
               nPlayeranimate++; 
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,80,40,RGB(0,0,0));
              break;
                        
              case 13: case 14: case 15: case 16:
               SelectObject(DrawDC,CharacterBitmap);
               nPlayeranimate++; 
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,120,40,RGB(0,0,0));
              break;                   
             }    
             
           if(nPlayeranimate>17)
            {
              nPlayeranimate=1;             
            }
     }

       if(!bGoRight)
        {
                    TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,0,0,RGB(0,0,0));
               
            switch(nPlayeranimate)
            {
              case 1 :case 2: case 3: case 4:
               SelectObject(DrawDC, CharacterBitmap);
        
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,0,0,RGB(0,0,0));
               nPlayeranimate=17; 
              break;
                 
              case 5: case 6: case 7: case 8:
               SelectObject(DrawDC,CharacterBitmap);
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,40,0,RGB(0,0,0));
               nPlayeranimate--; 
              break;
                    
              case 9: case 10: case 11: case 12:
               SelectObject(DrawDC,CharacterBitmap);             
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,80,0,RGB(0,0,0));
               nPlayeranimate--;    
              break;
                   
              case 13: case 14: case 15: case 16:     
               SelectObject(DrawDC,CharacterBitmap);     
               TransBitBlt(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-ymoving,40,40,DrawDC,120,0,RGB(0,0,0));
               nPlayeranimate--; 
              break;
            }
                        
                 if(nPlayeranimate<1)
                 {
                  nPlayeranimate=17;
                                      
                 }                            
                                  
                                  
               
               
               
               
               
               
               
               
               
               
               
               
               
         }
       }
     
 }







 
void CreateSAK() // �Ѿ� ���� 
{
     
        for(int shoot=0; shoot<3; shoot++){

                if(cPlayerstate==2){
                if(!bBulletAK[shoot]){
                                      cBulletstate[shoot]=cPlayerstate;
                                      bBulletAK[shoot]=true;
                                      MXakl[shoot]=Player_rt.right+(nScreen*3)/2;
                                      SetRect(&Bulletrt[shoot],Player_rt.left,Player_rt.top+15,Player_rt.right,Player_rt.bottom-15);
                                      
                                      break;
                                      }
                                      }
                                      
                                      
                                      
                else if(cPlayerstate==1){
                        if(!bBulletAK[shoot]){
                                      cBulletstate[shoot]=cPlayerstate;
                                      
                                      bBulletAK[shoot]=true;
                                      MXakl[shoot]=Player_rt.left-40-(nScreen*3)/2;
                                      SetRect(&Bulletrt[shoot],Player_rt.left,Player_rt.top+15,Player_rt.right,Player_rt.bottom-15);
                                      break;
                                      }
                                    
                                      
                                      
                                      }    
                
                else if(cPlayerstate==3){
                      if(!bBulletAK[shoot]){
                                      cBulletstate[shoot]=cPlayerstate;
                                      
                                      bBulletAK[shoot]=true;
                                      MXakl[shoot]=Player_rt.top-(nScreen*3)/2;
                                      SetRect(&Bulletrt[shoot],Player_rt.left+15,Player_rt.top,Player_rt.right-15,Player_rt.bottom);
                                      break;
                                      }
                
                    }
                    
                    
               else if(cPlayerstate==4){
                      if(!bBulletAK[shoot]){
                                      cBulletstate[shoot]=cPlayerstate;
                                      
                                      bBulletAK[shoot]=true;
                                      MXakl[shoot]=Player_rt.bottom+(nScreen*3)/2;
                                      SetRect(&Bulletrt[shoot],Player_rt.left+15,Player_rt.top,Player_rt.right-15,Player_rt.bottom);
                                      break;
                                      }
                
                    }      
                     
                                                       
                                      
             }

}

void SAK() //�Ѿ˺��� 
{
    RECT  wastert;
     
     
     for(int shoot=0;shoot<16;shoot++){
                                   if(bBulletAK[shoot]){
                                                        if(cBulletstate[shoot]==2)
                                                        {
                                                            if(MXakl[shoot]>Bulletrt[shoot].left){                   
                                                            Bulletrt[shoot].left+=30/2;
                                                            Bulletrt[shoot].right+=30/2;
                                                            }
                                                            else if(MXakl[shoot]<=Bulletrt[shoot].left){
                                                            bBulletAK[shoot]=false;
                                                            SetRectEmpty(&Bulletrt[shoot]);
                                                            }
                                                            
                                                             
                                                             
                                                        
                                                        }
                                                        
                                                        else if(cBulletstate[shoot]==1)
                                                        {
                                                             if(MXakl[shoot]<Bulletrt[shoot].left){
                                                             Bulletrt[shoot].left-=30/2;
                                                             Bulletrt[shoot].right-=30/2;
                                                             }
                                                             else if(MXakl[shoot]>=Bulletrt[shoot].left){
                                                             bBulletAK[shoot]=false;
                                                             SetRectEmpty(&Bulletrt[shoot]);
                                                             }
                                                        }
                                                        
                                                        
                                                        else if(cBulletstate[shoot]==3)
                                                        {
                                                             if(MXakl[shoot]<Bulletrt[shoot].top){
                                                             Bulletrt[shoot].top-=30/3;
                                                             Bulletrt[shoot].bottom-=30/3;
                                                             }
                                                             else if(MXakl[shoot]>=Bulletrt[shoot].top){
                                                             bBulletAK[shoot]=false;
                                                             SetRectEmpty(&Bulletrt[shoot]);
                                                             }
                                                        
                                                        }
                                                        
                                                        
                                                        else if(cBulletstate[shoot]==4)
                                                        {
                                                             if(MXakl[shoot]>Bulletrt[shoot].bottom){
                                                             Bulletrt[shoot].top+=30/3;
                                                             Bulletrt[shoot].bottom+=30/3;
                                                             }
                                                             else if(MXakl[shoot]<=Bulletrt[shoot].bottom){
                                                             bBulletAK[shoot]=false;
                                                             SetRectEmpty(&Bulletrt[shoot]);
                                                             }
                                                        
                                                        }
                                                        
                                                        
 
                                                        
                                                        
                                                        
                                   }
     }
}                                      




void Printfun()
{
   RECT Drt[500];  
     
     SetRect(&Funbackrt,1366*3/4,0,1366,100);
     FillRect(MemDC,&Funbackrt,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
     FrameRect(MemDC,&Funbackrt,(HBRUSH)GetStockObject(BLACK_BRUSH));
     FillRect(MemDC,&Function3linert,(HBRUSH)GetStockObject(WHITE_BRUSH));     
    //�׸� 
    for(int a=0;a<500;a++)
     { 
    
      TransBitBlt(MemDC,Function1rt[a].left-mapmoving-sight+10,Function1rt[a].top-20-ymoving,10,10,DrawDC,10,590,RGB(0,0,0));
     }
     
     for(int a=0;a<500;a++)
     { 
    
      TransBitBlt(MemDC,Function2rt[a].left-mapmoving-sight+10,Function2rt[a].top-20-ymoving,10,10,DrawDC,10,590,RGB(0,0,0));
     }
      for(int a=0;a<500;a++)
     { 
    
      TransBitBlt(MemDC,Function4rt[a].left-mapmoving-sight+10,Function4rt[a].top-20-ymoving,10,10,DrawDC,10,590,RGB(0,0,0));
     }
      TransBitBlt(MemDC,Turretrt.left-mapmoving-sight+10,Turretrt.top-20-ymoving,10,10,DrawDC,10,590,RGB(0,0,0));
     
     
     for(int a=0;a<1366*1/4;a++)
     { 
      if(bFunction3ready)
      TransBitBlt(MemDC,Function3rt[a].left+10,Function3rt[a].top-20,10,10,DrawDC,10,590,RGB(0,0,0));
     }
   
  //���⺰ ������� 
   for(int a=0;a<500;a++)
   {                 
     
     switch(nWeapontype)
     {
      
       case 1:
       if(!bFunction3continue && !bFunction2continue)
       {     
       if(nLinestand!=0) 
        SetRect(&Drt[a], 1366*3/4+a  ,100-(a/(6-nLinestand))-10 ,1366*3/4+10+a  ,100+10-(a/(6-nLinestand))-10 );        
       if(nLinestand==0)
        SetRect(&Drt[a], 1366*3/4+a  ,100-10 ,1366*3/4+10+a  ,100+10-10 );        
       
        FillRect(MemDC,&Drt[a],(HBRUSH)GetStockObject(BLACK_BRUSH));   
       }
       break;  
       
       case 2:
       break;
       
       case 3:
       break;
       
       case 4:
       break;
                      
     }                  
                       
    }                   
                       
                       
                       
                      
                       
                       
    








}

void Readyfun()
{
     
     
     
}








void Firstfunctionset() //�����Լ� ������ 
{
    
     
   
    if(!bFptready)
    {
      if(bGoRight)             
      {
       Functionpt.x = Player_rt.right;
       bFungoright = true;
      }
      if(!bGoRight)
      {
       Functionpt.x = Player_rt.left;
       bFungoright = false;
      }
       Functionpt.y = Player_rt.top;
       bFptready = true;
    }
     
     
}


void Firstfunction()  //�����Լ� ���� ���� 
{
     
  if(bFptready && !bFunction1continue)   
  { 
   bFunction1continue = true;
    nFunctioncount2=nMaxFun2;
    nFunctioncount4=nMaxFun4;
    
  }   
  
  for(int num=0;num<nFunctioncount1;num++) 
  {
   if(bFungoright)       
   SetRect(&Function1rt[num],Functionpt.x+num,Functionpt.y-(num*nLinestand)/2,Functionpt.x+10+num,Functionpt.y+10-(num*nLinestand)/2);   
   if(!bFungoright)          
   SetRect(&Function1rt[num],Functionpt.x-num,Functionpt.y-(num*nLinestand)/2,Functionpt.x+10-num,Functionpt.y+10-(num*nLinestand)/2);   
  }  
     
      
}




void Secondfunctionset() //�����Լ� ������ 
{
    
     
   
    if(!bFptready)
    {
      if(bGoRight)             
      {
       Functionpt.x = Player_rt.right;
       bFungoright = true;
      }
      if(!bGoRight)
      {
       Functionpt.x = Player_rt.left;
       bFungoright = false;
      }
       Functionpt.y = Player_rt.top;
       bFptready = true;
    }
     
     
}

void Secondfunction()
{
     
   if(bFptready && !bFunction2continue)   
  { 
   bFunction2continue = true;
   nFunctioncount1=nMaxFun1;
   nFunctioncount4=nMaxFun4;
   
   }   
  
  for(int num=0;num<nFunctioncount2/2;num++) 
  {
     if(bFungoright)       //���ʺ��� ���� 
     {
                           
     if(nLinestand==0)
     nLinestand=1;
     
      SetRect(&Function2rt[num],Functionpt.x+num-250,Functionpt.y-((num/nLinestand-250)*(num/nLinestand-250))/400,Functionpt.x+10+num-250,Functionpt.y-((num/nLinestand-250)*(num/nLinestand-250))/400+10 ); 
    
    
     }
 


     if(!bFungoright)          //�����ʺ��� ���� 
     {
                               
     if(nLinestand==0)
     nLinestand=1;
     
      SetRect(&Function2rt[num],Functionpt.x-num+250,Functionpt.y-((num/nLinestand-250)*(num/nLinestand-250))/400,Functionpt.x+10-num+250,Functionpt.y-((num/nLinestand-250)*(num/nLinestand-250))/400+10 ); 
     
     
     } 
     
  }  
    
}

void Realsecondfunction()
{
  
 if(nLinestand==0)
 {
  nLinestand=1;                 
 }   
  for(int num=0;num<nFunctioncount2real/2;num++) 
  {
     if(bFungoright) //�� 
     {
      SetRect(&Function2rt[num],Functionpt.x+num,Functionpt.y- (num)*(num)/400/nLinestand,Functionpt.x+10+num,Functionpt.y- (num)*(num) /400/nLinestand+10 );   
     }
     
     if(!bFungoright) //�� 
     {
      SetRect(&Function2rt[num] ,Functionpt.x-num ,Functionpt.y- (num)*(num) /400/nLinestand ,Functionpt.x+10-num ,Functionpt.y- (num)*(num) /400/nLinestand+10 );   
     }
  }
  
}




void Fourthfunctionset()
{
     
    if(!bFpt4ready)
    {
      if(bGoRight)             
      {
       Functionpt4.x = Player_rt.right;
       bFun4goright = true;
      }
      if(!bGoRight)
      {
       Functionpt4.x = Player_rt.left;
       bFun4goright = false;
      }
       Functionpt4.y = Player_rt.top;
       bFpt4ready = true;
    }
     
}






void Fourthfunction()
{
   if(bFpt4ready && !bFunction4continue)   
  { 
     bFunction4continue = true;
    //nFunctioncount1=nMaxFun1;
   // nFunctioncount2=nMaxFun2;
  }  
     
     SetRect(&Turretrt,Functionpt4.x,Functionpt4.y,Functionpt4.x+10,Functionpt4.y+10);
    
    if(bFunction4continue)
    {
     for(int num=0;num<nFunctioncount4;num++)
     {
      if(bFun4goright)       
      SetRect(&Function4rt[num],Turretrt.left+num,Turretrt.top-(int)sqrt((double)num*100),Turretrt.left+num+10,Turretrt.top-(int)sqrt((double)num*100)+10);
      if(!bFun4goright)
      SetRect(&Function4rt[num],Turretrt.left-num,Turretrt.top-(int)sqrt((double)num*100),Turretrt.left-num-10,Turretrt.top-(int)sqrt((double)num*100)+10);
      
     }
    }
     
     
     
     
     
     
          
                           if(bFunction4continue)
                           {  
                               if(nFunctioncount4<nMaxFun4)
                               {
                                 nFunctioncount4+=30;
                               }
                           
                           
                              if(nFunctioncount4>=nMaxFun4 && bFunction4continue) 
                              {
                                nFun4count++;
                               
                                nFunctioncount4=0;
                              
                               for(int num=0;num<500;num++)
                               SetRect(&Function4rt[num],-1000,-1000,-1000,-1000);
                             
                              } 
                           }   
                           
                           if(nFun4count>10 && bFunction4continue)
                           {
                            bFunction4continue = false;
                            
                             for(int num=0;num<500;num++)
                              SetRect(&Function4rt[num],-1000,-1000,-1000,-1000);
                              SetRect(&Turretrt,-1000,-1000,-1000,-1000);
                            bFpt4ready = false;
                            bFunction4atk = false;
                            nFun4count=0;
                            bFun4go = false;
                           }
     
     
     
     
}









void Thirdfunctionset() //�ʿ����. 
{
}



void Thirdfunction()
{
  if(!bFunction3continue)   
  { 
   if(GetKeyState('E')&0x8000)
   {
    bFunction3continue = true;
    
   }
   nFunctioncount1=nMaxFun1;
   nFunctioncount2=nMaxFun2;
  }   
  
  for(int num=-1366/8;num<1366/8;num++) 
  { //1366*3/4,0,1366,100
   
      if(num<0)
     SetRect(&Function3rt[num+1366/8], 1366*3/4+num+1366/8, 60- (int)(pow(num,-1)*60) , 1366*3/4+num+1366/8+1 , 60- (int)(pow(num,-1)*60) );   //
     
   
     
     if(num>0)
     SetRect(&Function3rt[num+1366/8], 1366*3/4+num+1366/8, 60-(int)(pow(num,-1)*60) , 1366*3/4+num+1366/8+1 , 60-(int)(pow(num,-1)*60) );   // 
   
 
  }  
     
}















void Shield()
{
       
  if( (GetKeyState('G')&0x8000) && nShieldcount==0  )
  {
    bGuardon = true;
    nShieldcount=30;      
  }   
  
  
  
  if(bGuardon)
  {
    if(nShieldcount>0)          
    nShieldcount--;          
  
    if(nShieldcount==0)
    bGuardon = false;
  
    Guardrgn = CreateEllipticRgn( Player_rt.left-5 , Player_rt.top-5 , Player_rt.right+5 , Player_rt.bottom+5 );
    Guarddrawrgn = CreateEllipticRgn( Player_rt.left-mapmoving-sight-5 , Player_rt.top-ymoving-5 , Player_rt.right-mapmoving-sight+5 , Player_rt.bottom-ymoving+5 );
    
  }

}



void Shielddraw()
{    
     if(bGuardon)
     FrameRgn(MemDC,Guarddrawrgn,(HBRUSH)GetStockObject(LTGRAY_BRUSH),3,3);
     
}



















void Fadein(int nValue)// ���̵���. 
{
   
     
   switch(nValue)
   {
     case 1: 
     
          
      Fadecount = 1;
      break;
          
     case 2:
       Fadecount = 2;
      break;    
          
     case 3:
       Fadecount = 3;
      break;    
          
     case 4:
       Fadecount = 4;
      break;    
          
     case 5:  
        Fadecount = 5;
      break;                  
      }          
              
                 
        ZeroptI.x = Player_rt.left;                
        ZeroptI.y = Player_rt.bottom;           
                 
                 
              Bkrgn = CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
        CombineRgn(Bkrgn,Bkrgn,WidingrgnI,RGN_DIFF);
        FillRgn(MemDC,Bkrgn,(HBRUSH)GetStockObject(BLACK_BRUSH));            
     
     
     
     
     
     
}


void Fadedraw() // ���̵���. 
{    
     
     
     
     if(RgncountI>1366)
    {
    bFading = false;
    bFadeonoffI =false;
    } 
     
     
     
  if(!bPlayerdie && bFadeonoffI)
  {   RgncountI += 20;
     switch(Fadecount)
     {
      
                     
     case 1:  //�÷��̾�� 
     if(RgncountI<1600) 
     {                  
     WidingrgnI = CreateEllipticRgn(ZeroptI.x-RgncountI-mapmoving-sight,ZeroptI.y-RgncountI,ZeroptI.x+RgncountI-mapmoving-sight,ZeroptI.y+RgncountI); 
     bFading = true;
     
     }
     break;
     
     
     
     case 2://���ʿ��� 
     if(RgncountI<1600)
     {
     WidingrgnI = CreateRectRgn(rt.left,rt.top,RgncountI,rt.bottom);
      bFading = true;
      
      }    
     break;
     
     
     
     
     
     case 3://���ʿ��� 
     if(RgncountI<1600)
     {
     WidingrgnI = CreateRectRgn(rt.left-mapmoving-sight,rt.top,rt.right-mapmoving-sight,RgncountI);     
      bFading = true;
      
      
      }    
     break;
        
        
        
        
               
     case 4://�����ʿ��� 
     if(RgncountI<1600)
     { 
     WidingrgnI = CreateRectRgn(rt.right-RgncountI-mapmoving-sight,rt.top,rt.right-mapmoving-sight,rt.bottom);     
      bFading = true;
      
      }    
     break;
     
     
     
     
     
     case 5://�Ʒ��ʿ��� 
     if(RgncountI<1600)
     {
        WidingrgnI = CreateRectRgn(rt.left-mapmoving-sight,rt.bottom-RgncountI,rt.right,rt.bottom);     
     bFading = true;
     
     
     }    
     break;
    

    
      }
}




}








void Skillgrid()
{
     HPEN Crosspen,Oldpen;
     HDC RgnDC;
     HBITMAP BackBitmap; 
     RgnDC=CreateCompatibleDC(hdc);  
     TCHAR gridcount[128];
     POINT Mapilne[mapx]; 
  
               
         BackBitmap=CreateCompatibleBitmap(hdc,rt.right,rt.bottom);
         
         OldBitmap=(HBITMAP)SelectObject(RgnDC,BackBitmap);     
        // if(bPlaygame)
         PatBlt(RgnDC,0,0,1366,768,WHITENESS);
              
                    Zeropt.x = Player_rt.left;                
                    Zeropt.y = Player_rt.bottom;
                    
              
              
              
    //���ڱ߱�      
       Crosspen = CreatePen(PS_SOLID,20,RGB(255,0,255));
       Oldpen = (HPEN)SelectObject(RgnDC,Crosspen);
    MoveToEx(RgnDC,mapx*40/2-mapmoving-sight,0,NULL);
    LineTo(RgnDC,mapx*40/2-mapmoving-sight,mapy*40);
    MoveToEx(RgnDC,0,768/2+15-40,NULL);
    LineTo(RgnDC,mapx*40,768/2+15-40);
    SelectObject(RgnDC,Oldpen);
    DeleteObject(Crosspen);
    
    
        OldWidingrgn=(HRGN)SelectClipRgn(RgnDC,Widingrgn);
        
        
      //��ǥ��  
         for(int i=0;i<mapx*40;i+=40) 
         {
            MoveToEx(RgnDC,i-mapmoving-sight,0,NULL); 
            LineTo(RgnDC,i-mapmoving-sight,mapy*40);     
               
               
                  if(i!=0) { 
                 wsprintf(gridcount,TEXT("%d"),i/40-mapx/2);                 
                 TextOut(RgnDC,i-mapmoving-sight,745,gridcount,lstrlen(gridcount)); 
                          
                           }
          }
              
          for(int i=0;i<mapy*40;i+=40) 
          {
            MoveToEx(RgnDC,0,i,NULL);
            LineTo(RgnDC,mapx*40,i);
             wsprintf(gridcount,TEXT("%d"),i/40-mapy/2);     
             TextOut(RgnDC,0,745-i+mapy,gridcount,lstrlen(gridcount));                 
          }
       
         SelectClipRgn(RgnDC,OldWidingrgn);
         BitBlt(MemDC,0,0,1366,768,RgnDC,0,0,MERGEPAINT);
         
         SelectObject(RgnDC,OldBitmap);
         DeleteObject(BackBitmap);
		 DeleteDC(RgnDC);

     
     
     
 }




void Soundout()//����� ���. 
{
  if(bPlaygame)
  {   
    switch(nNumstage)
    {
       case 0:                     
        
        PlaySound("Sounds/Stage1.wav" , NULL , SND_ASYNC | SND_LOOP | SND_FILENAME | SND_NODEFAULT | SND_NOSTOP );      
       break; 
       case 1:
            
        PlaySound("Sounds/Stage2.wav" , NULL , SND_ASYNC | SND_LOOP | SND_FILENAME | SND_NODEFAULT | SND_NOSTOP );     
       break;     
     
     
     }    
  } 
}














void Automove(RECT Mrt ,bool bRight, int nRange) // ���� �ڵ��̵�. ȿ�뼺�� �������� �𸣰���. 
{   
 

  
  
    if(nMcount > nRange/5)
    {
          bAmoving = false;
          bSettomove = false; 
    }
  
  
  if(!bSettomove&&(nMcount < nRange/5))
  {
   bSettomove = true;               
  }
  
  
  if(bSettomove && bRight)   
  {
       bAmoving = true;    
      Player_rt.right +=5;     
      Player_rt.left +=5;  
      nMcount++;
      bGoRight=true;
      //if(Mrt==Player_rt)
       nPlayeranimate++; 
       accmove=1;         
  }
            
  if(bSettomove && !bRight)
  {
          bAmoving = true;  
         Player_rt.right -=5;     
         Player_rt.left -=5;
         nMcount++; 
         bGoRight = false;
        // if(Mrt==Player_rt)
          nPlayeranimate--;
          accmove=-1;                 
   }   

}    




void DrawTitle() // ó��ȭ�� 
{
     StretchDrawBitmap(MemDC,0,0,1366,768,TitleBitmap,0,0,1366,768);
     DrawBitmap(MemDC,700,360,315,70,7,90,TextBoxBitmap);
     DrawBitmap(MemDC,700,460,320,70,330,90,TextBoxBitmap);
     DrawBitmap(MemDC,700,580,255,75,7,160,TextBoxBitmap);
     if(cSelectstate==0)  
     DrawBitmap(MemDC,640,380,60,40,300,180,TextBoxBitmap);
     else if(cSelectstate==1)
     DrawBitmap(MemDC,640,480,60,40,300,180,TextBoxBitmap);
     else if(cSelectstate==2)
     DrawBitmap(MemDC,640,600,60,40,300,180,TextBoxBitmap);
} 


void DrawMenu() // I
{
    StretchDrawBitmap(MemDC,0,0,1366,768,MenuBitmap,0,0,640,480);
    if(cSelectstate==0)  
     DrawBitmap(MemDC,600,290,60,40,300,180,TextBoxBitmap);
     else if(cSelectstate==1)
     DrawBitmap(MemDC,700,340,60,40,300,180,TextBoxBitmap);
     else if(cSelectstate==2)
     DrawBitmap(MemDC,675,420,60,40,300,180,TextBoxBitmap);
     else if(cSelectstate==3)
     DrawBitmap(MemDC,550,420,60,40,300,180,TextBoxBitmap);
     else if(cSelectstate==4)
     DrawBitmap(MemDC,525,340,60,40,300,180,TextBoxBitmap);
       
     if(cSelectstate==1 && GetKeyState('D')&0x80000)  
     {
      
     }  
       
}



void DrawESC() //�ⱸ �����.  ���� ���� �ʿ䰡 �ֳ�? �ٸ��Ŷ� ���ĳ����� ����. 
{
   StretchDrawBitmap(MemDC,0,0,1366,768,bkBlackBitmap,0,0,10,10);
   DrawBitmap(MemDC,230,350,940,70,400,160,TextBoxBitmap);
   
}



  //                DC      X Y ������   ��� ����   ��� ����  DC       ��Ʈ�ʿ��� XY     ���� ���� 
void TransBitBlt(HDC hdc, int x, int y, int width,int height,HDC MemDC,int mx,int my, COLORREF clrMask)
{
COLORREF cColor;
HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
HDC	hdcMem, hdcBack, hdcObject, hdcSave;

hdcBack = CreateCompatibleDC(hdc);
hdcObject = CreateCompatibleDC(hdc);
hdcMem = CreateCompatibleDC(hdc);
hdcSave = CreateCompatibleDC(hdc);

bmAndBack = CreateBitmap(width, height, 1, 1, NULL);
bmAndObject = CreateBitmap(width, height, 1, 1, NULL);
bmAndMem = CreateCompatibleBitmap(hdc, width, height);
bmSave = CreateCompatibleBitmap(hdc, width, height);

bmBackOld = (HBITMAP) SelectObject(hdcBack, bmAndBack);
bmObjectOld = (HBITMAP) SelectObject(hdcObject, bmAndObject);
bmMemOld = (HBITMAP) SelectObject(hdcMem, bmAndMem);
bmSaveOld = (HBITMAP) SelectObject(hdcSave, bmSave);

SetMapMode(MemDC, GetMapMode(hdc));

BitBlt(hdcSave, 0, 0, width, height, MemDC, mx, my, SRCCOPY);

cColor = SetBkColor(MemDC, clrMask);

BitBlt(hdcObject, 0, 0, width, height, MemDC, mx , my, SRCCOPY);

SetBkColor(MemDC, cColor);

BitBlt(hdcBack, 0, 0, width, height , hdcObject, 0, 0, NOTSRCCOPY);
BitBlt(hdcMem , 0, 0, width, height , hdc , x, y, SRCCOPY);
BitBlt(hdcMem , 0, 0, width, height , hdcObject, 0, 0, SRCAND);
BitBlt(MemDC , mx, my, width, height , hdcBack , 0, 0, SRCAND);
BitBlt(hdcMem , 0, 0, width, height, MemDC , mx, my, SRCPAINT);
BitBlt(hdc , x, y, width, height, hdcMem , 0, 0, SRCCOPY);
BitBlt(MemDC , mx, my, width, height, hdcSave , 0, 0, SRCCOPY);

DeleteObject(SelectObject(hdcBack, bmBackOld));
DeleteObject(SelectObject(hdcObject, bmObjectOld));
DeleteObject(SelectObject(hdcMem, bmMemOld));
DeleteObject(SelectObject(hdcSave, bmSaveOld));

DeleteDC(hdcMem);
DeleteDC(hdcBack);
DeleteDC(hdcObject);
DeleteDC(hdcSave);


}






void DrawText() //���� ���.  �̰͵� �� �պ����ҵ�. 
{

     
    
    
     if(cSelectstate==1)
     {
   
       Sentencestr=TEXT("�� �����̾߱⿡�� �״´�.");
       DrawBitmap(MemDC,0,585,1364,188,4,572,TextBoxBitmap);
       TextOut(MemDC,50,650,Sentencestr,nTextcount);
      
     }
     
     if(cSelectstate==2)
     {
  
        Sentencestr=TEXT("�����Ӥ���");//�ùٷ��� 
       DrawBitmap(MemDC,0,585,1364,188,4,572,TextBoxBitmap); 
       TextOut(MemDC,50,650,Sentencestr,nTextcount);
       
         
     }                
     
     if(cSelectstate==3)
     {
                  
       bText=false;
       cSelectstate=0;
       
     }  
     
       
}

void DrawTexthelp() // ���� ��� 
{ 
     if(nTextcount<lstrlen(Sentencestr))
      nTextcount++;        
}

void DrawUI()
{    
     DrawBitmap(MemDC,10,10,80,50,650,390,TextBoxBitmap);
    
     // TextOut(MemDC,Player_rt.left-mapmoving-sight,Player_rt.top-20-ymoving,health,lstrlen(health));
     DrawBitmap(MemDC,100,10,Playerhealth,45,20,5,TextBoxBitmap);
     //StretchDrawBitmap(MemDC,30,10,30,90,TextBoxBitmap,0,0,660,50);
}    




void testmode() // ������ �������? PRESS P! 
{ 
     
     FillRect(MemDC,&Player_rt,(HBRUSH)GetStockObject(WHITE_BRUSH));
     
     
     
     
     
     
     for(int hity=0; hity<mapy; hity++)
     { for(int hitx=0; hitx<mapx; hitx++)
       {   
        FillRgn(MemDC, St1rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St2rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St3rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St4rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St5rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St6rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St7rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
        FillRgn(MemDC, St8rgn[hity][hitx], (HBRUSH)GetStockObject(WHITE_BRUSH));  
 
        
        
        
        
        
        
              
            } 
             }
     
     
     
     
     
     
     for(int mob=0; mob<128; mob++)
    {
      FillRect(MemDC,&Goort[mob],(HBRUSH)GetStockObject(GRAY_BRUSH));     
      
      for(int shoot=0; shoot<3; shoot++)
      {
       FillRect(MemDC,&Mobbulletrt[mob][shoot],(HBRUSH)GetStockObject(LTGRAY_BRUSH));        
      }
        
        
    }









}









//����  ���� �浹�� �ణ , �÷��̾� �̵� �ִϸ��̼� �Լ�ȭ , �� ������. Q��ư. 
             
