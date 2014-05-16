#include<reg51.h>	// header file

sbit p=P3^0;        // to increase hours
sbit q=P3^1;        // to decrease minutes
sbit r=P3^2;        // to decrease hours
sbit l=P3^4;        // to buzzer to indicate hour
sbit bu=P3^3;       // to increase minutes
sbit t=P3^5;        // to increase date
sbit u=P3^6;        // to decrease date
sbit w=P3^7;        // to increase month
sbit rs=P2^1;       // LCD command pin for select the resistor inside the lcd
sbit rw=P2^2;		// LCD command pin for write the information on lcd
sbit en=P2^3;       // LCD command pin used to latch information presented to it’s data pins
sfr lcddata=0×90; 	// P2= LCD data pin
/*************************************DELAY FUNCTION*************************************************/
void delay(unsigned char n)
	{
		unsigned char i,j;
		for(i=0;i<n;i++)
		for(j=0;j<125;j++);

	}
/**********************************LCD COMMAND FUNCTION*********************************************/

void command(unsigned char s)
	{
		lcddata=s;  	//put the value on pin
		rs=0;			
		rw=0;			
		en=1;           //strobe the enable pin
		delay(40);
		en=0;
	}
/****************************************LCD DISPLAY FUNCTION*****************************************/

void lcddisplaydata(unsigned char s)
	{
		lcddata=s;      //put the value on pin
		rs=1;
		rw=0;
		en=1; 			//strobe the enable pin
		delay(40);
		en=0;
	}
/****************************************MAIN program*************************************************/

void main()
	{
		int h,m,s,y,mo,d,y1,y2,y3,y4,mo1,mo2,d1,d2,h1,h2,m1,m2,s1,s2,i,j,k;
		unsigned char array[]={’0′,’1′,’2′,’3′,’4′,’5′,’6′,’7′,’8′,’9′};
		command(0×38);		// LCD command code for 2 lines and 5*7 matrix
		command(0x0c);
		command(0×06);      // LCD command code for increment cursors(shift cursor to right)
		while(1)
	{
		y=2012;				//starting from year 2012
		while(y>=2012)
			{
				for(mo=1;mo<=12;mo++)
			{
		if(mo==1)  			//condition for month january
			{
				d=31;
			}
		else if(mo==2)		//condition for month february
		{
			if((y%4)==0)	//condition for leap year
		{
			d=29;
		}
			else
		{
			d=28;
		}
	}
	else if(mo==3)			//condition for month march
		{
			d=31;
		}
	else if(mo==4)          //condition for month april
		{
			d=30;
		}
	else if(mo==5)          //condition for month may
		{
			d=31;
		}		
	else if(mo==6)          //condition for month june
		{
			d=30;
		}
	else if(mo==7)          //condition for month july
		{
			d=31;
		}
	else if(mo==8)          //condition for month august
		{
			d=31;
		}
	else if(mo==9)          //condition for month september
		{
			d=30;
		}
	else if(mo==10)         //condition for month october
		{
			d=31;
		}
	else if(mo==11)         //condition for month november
		{
			d=30;
		}
	else                    //condition for month december
		{
			d=31;
		}
			for(i=1;i<=d;i++)
		{
			for(h=0;h<=23;h++)		//condition for hours in a day
		{
			for(m=0;m<=59;m++)      //condition for minutes in a hour
		{
			for(s=0;s<=59;s++)      //condition for second in minute
		{
y1=y/1000;
j=y%1000;                           //code for disply year
y2=j/100;
k=j%100;
y3=k/10;
y4=k%10;
mo1=mo/10;                          //code for display month
mo2=mo%10;
d1=i/10;
d2=i%10;                            //code for display day
h1=h/10;
h2=h%10;                            // code for display hour
m1=m/10;                            //code for display minute
m2=m%10 ;
s1=s/10;                            //code for disply second
s2=s%10;
command(0×80);                      // LCD command for first position of first line
lcddisplaydata(array[d1]);
lcddisplaydata(array[d2]);
command(0×84);                      // LCD command for fifth position of first line
lcddisplaydata(‘-’);
command(0×86);                      // LCD command for seventh position of first line
lcddisplaydata(array[mo1]);
lcddisplaydata(array[mo2]);
command(0×89);                      // LCD command for tenth position of first line
lcddisplaydata(‘-’);
command(0x8b);                      // LCD command for twelveth position of first line
lcddisplaydata(array[y1]);
lcddisplaydata(array[y2]);
lcddisplaydata(array[y3]);
lcddisplaydata(array[y4]);

command(0xc0);                      // LCD command for first position of second line
lcddisplaydata(array[h1]);
lcddisplaydata(array[h2]);
command(0xc4);                      // LCD command for fourth position of second line
lcddisplaydata(‘:’);
command(0xc6);                      // LCD command for sixth position of second line
lcddisplaydata(array[m1]);
lcddisplaydata(array[m2]);
command(0xca);                      // LCD command for eleventh position of second line
lcddisplaydata(‘:’);
command(0xcc);                      // LCD command for thirteenth position of second line
lcddisplaydata(array[s1]);
lcddisplaydata(array[s2]);
delay(100);
if(p==0)                            // switch for increasing Hours
{
		h++;                        // condition to set hours
		s=-1;                       // second reset to Zero after release H++ switch
if(h==24)                           // if h=24 then hours is start to Zero
	{
		h=0;
		s=-1;
	}
}
else if(q==0)                       // switch for decreasing Minutes
{
		if(m>0)                     // if minute is greater then zero
	{
		m–;                         // minute is decrease till zero
		s=-1;                       // after releasing minute decrease button seconds initialize from zero
	}
}
else if(r==0)                       // switch for decreasing hours
{
		if(h>0)                     // if hour is greater than zero
	{
		h–;                         // hour is decrease till zero
		s=-1;                       // after releasing hour decrease button seconds initialize from zero
	}
}
else if(l==0)						// switch for increasing minutes
{
		m++;
		s=-1;						
if(m>60)                            // if increased minutes are above than 60 than it again start from zero
	{
		m=0;
		s=-1;
	}
}
else if(t==0)						// switch for increasing days
{
		i++;
		if(i>31)                    // if increased days are above than 31 than it again start from zero
	{
		i=0;
	}
}
else if(u==0)     					// switch for decreasing days
{
		if(i>0)                     // it decrease days till zero
	{
		i–;
	}
}
else if(w==0)                       // switch for increasing months
{
		mo++;
		if(mo>12)                   // if increased months are above than 12 than it again start from zero
	{
		mo=0;
	}
}
else
{
		h=h;
		m=m;
		i=i;
		mo=mo;
}
if(m==59)                            // conditin for switching the buzzer
{
		bu=1;                        // buzzer ON
}
else
	{
		bu=0;                        // buzzer OFF
		}
		command(0×82);               // to start LCD from 3rd position of first line
		command(0×06);               // to set LCD in entry mode
		}
	   }
      }
     }
    } 
   }
  }
}