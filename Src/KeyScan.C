#include "CPU.H"
#include "ADC.H"
#include "Ks0108.H"
extern void Delayms(U16 Ms);

/*
*****************************************************************************
* KeyScan - 键盘扫描函数
* DESCRIPTION: -
* 判4个按键那个有按下
* @Param void:
* @Return :有按键 返回键值 无按键 返回false 因此键值定义不能为false
* ----
*****************************************************************************
*/
//uint16_t ADC_Result;
long temp, temp1;
uint16_t ADC_Temp, left = 0, right = 0;

void ADC_got(void)
{
  ADC_getValue(); 
  
  if(ADC_Temp!=ADC_Result)                                                  // 如果两次不等才需要更新
      {
        ADC_Temp = ADC_Result;
        temp = ADC_Temp;
        temp *= 330;
        temp /= 40960;
        temp /= 2; //可以10步
        if(temp<temp1) right = 1;//右
        if(temp>temp1) left = 1;//左        
        temp1 = temp;  
      }
}

U8 KeyScan(void)
{
    ADC_got(); 
    if(right)
    {
      right = 0;
     // GUI_Clear();
      return Key_Right;
    }
    if(left)
    {
      left = 0;
     // GUI_Clear();
      return Key_Left;
    }
    if((P1IN & BIT7)==0)
        {
           while(!(P1IN & BIT7));
        //   GUI_Clear();
           return Key_Down;
        }
    if((P2IN & BIT2)==0)
        {
           while(!(P2IN & BIT2));
          // GUI_Clear();
           return Key_Up;
        }
    
    return false;
/*    Key0 = 1;
    Key1 = 1;
    Key2 = 1;
    Key3 = 1;
    if((Key0==0)||(Key1==0)||(Key2==0)||(Key3==0)){
        Delayms(20);
        if((Key0==0)||(Key1==0)||(Key2==0)||(Key3==0)){
            if((Key0==0)&&(Key1==1)&&(Key2==1)&&(Key3==1)){      //Key0
                return Key_Up;
            }else if((Key0==1)&&(Key1==0)&&(Key2==1)&&(Key3==1)){//Key1
                return Key_Right;
            }else if((Key0==1)&&(Key1==1)&&(Key2==0)&&(Key3==1)){//Key2
                return Key_Left;
            }else if((Key0==1)&&(Key1==1)&&(Key2==1)&&(Key3==0)){//Key3
                return Key_Down;
            }else{
                return false;
            }

        }else {
            return false;
        }//no key press
    }else{
        return false;
    }
 */
}
#if 0
/*
*****************************************************************************
* WaitKey - 死等一个有效按键输入
* DESCRIPTION: -
*
* @Param void:
* @Return : 按键键值
* ----
*****************************************************************************
*/
U8 WaitKey(void)
{

while(1){
    switch(KeyScan()){
        case Key_Up:{
            return Key_Up;
            break;
        }
        case Key_Down:{
            return Key_Down;
            break;
        }
        case Key_Left:{
            return Key_Left;
            break;
        }
        case Key_Right:{
            return Key_Right;
            break;
        }
        default:
            break;
    }
}

}
#endif
