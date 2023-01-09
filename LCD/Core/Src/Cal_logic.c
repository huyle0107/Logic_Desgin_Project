#include "Cal_logic.h"
#include "LCD.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char final[16];
unsigned long long result1 = 0;
double result2 = 0;

int logicCal(char str1[16], char str2[16], char cal, int check2, int temp, int i, int j)
{
	int num1 = 0, num2 = 0, count1 = 0, count2 = 0, count3 = 0, check1 = 0;

	if (temp == 2)
	{
		i = 0;
		while (final[count3] != '\0')
		{
			if (final[count3] == '.')
			{
				if (final[count3 + 1] == '0')
					if (final[count3 + 2] == '0')
						if (final[count3 + 3] == '0')
							if (final[count3 + 4] == '0')
								if (final[count3 + 5] == '0')
									if (final[count3 + 6] == '0') break;
				check1 = 1;
			}
			str1[count3] = final[count3];
			final[count3] = '\0';
			i++; count3++;
		}
		LCD_Clear();
	}

	if (check2 == 1)
	{
		for (int l = 0; l < 16; l++) final[l] = '\0';
	}

	while (count1 < i)
	{
		if (check1 == 1)
		{
			count1 = 1;
			break;
		}
		if (str1[count1] == '-')
	    {
			if (i > 10)
			{
				LCD_Put_Cur(1, 7);
				LCD_Send_String("OUT RANGE");
				return 0;
			}
			count1++;
			while (count1 < i)
			{
				int temp1 = (int)str1[count1] - 48;
				num1 = num1 * 10 + temp1;
				count1++;
			}
			num1 *= -1;
			break;
	    }
	    if (i > 9)
		{
	    	LCD_Put_Cur(1, 7);
			LCD_Send_String("OUT RANGE");
			return 0;
		}
	    int temp1 = (int)str1[count1] - 48;
	    num1 = num1 * 10 + temp1;
	    count1++;
	}
	while (count2 < j)
	{
		if (str2[count2] == '-' )
		{
	    	if (j > 10)
			{
	    		LCD_Put_Cur(1, 7);
				LCD_Send_String("OUT RANGE");
				return 0;
			}
			count2++;
	    	while (count2 < j)
	    	{
	    		int temp2 = (int)str2[count2] - 48;
	    		num2 = num2 * 10 + temp2;
	    		count2++;
	    	}
	    	num2 *= -1;
	    	break;
	    }
	    if (j > 9)
		{
	    	LCD_Put_Cur(1, 7);
			LCD_Send_String("OUT RANGE");
			return 0;
		}
	    int temp2 = (int)str2[count2] - 48;
	    num2 = num2 * 10 + temp2;
	    count2++;
	}

	if (cal == '\0')
	{
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
	    return 0;
	}
	else if (count1 == 0)
	{
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
		return 0;
	}
	else if (count2 == 0)
	{
		LCD_Put_Cur(1, 11);
		LCD_Send_String("error");
		return 0;
	}

	switch(cal)
	{
		case '+':
			if (check1 == 1) result2 += (double)num2;
			else result1 = num1 + num2;
	        break;
	    case '-':
	    	if (check1 == 1) result2 -= (double)num2;
	    	else result1 = num1 - num2;
	        break;
	    case 'x':
	    	if (check1 == 1) result2 *= (double)num2;
	    	else result1 = num1 * num2;
	    	if ((result2 * (double)num2) < -2147483648 && (result2 * (double)num2) > 2147483648)
	    	{
				LCD_Put_Cur(1, 6);
				LCD_Send_String("math error");
				return 0;
	    	}
	    	else if (num1*num2 < -2147483648 && num1*num2 > 2147483648)
	        {
	        	LCD_Put_Cur(1, 6);
	        	LCD_Send_String("math error");
	        	return 0;
	        }
	        break;
	    case '/':
	    	if(num2 == 0)
	        {
	        	LCD_Put_Cur(1, 11);
	        	LCD_Send_String("error");
	        	return 0;
	        }
	    	else if (check1 == 1)
	    	{
	    		result2 /= (double)num2;
	    	}
	        else
	        {
	        	check1 = 1;
	            result2 = (double)num1/num2;
	        }
	        break;
	}
	if (check1 == 0)
	{
		sprintf(final, "%d", result1);
	}
	else
	{
		sprintf(final, "%.6f", result2);
	}
	int tmpcount = 0;
	for(int z = 0; z < 16; z++)
	{
		LCD_Put_Cur(1, tmpcount);
		LCD_Send_Data(' ');
		tmpcount++;
	}
	count3 = 0;
	while (final[count3] != '\0') count3++;
	LCD_Put_Cur(1, 16 - count3);
	for(int y = 0; y < 16; y++) LCD_Send_Data(final[y]);
	return 1;
}
