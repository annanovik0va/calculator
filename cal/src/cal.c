/*
 ===============================================================================
 Name        : cal.c
 Author      : Novikova Anna
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Данная программа реализует арифметические операции(+(сложение),
             |-(вычитание), /(деление), *(произведение), !(факториал числа),
             |p(возведение числа в степень p))над двумя числами, введеными пользователем,
             |(+)(сложение векторов), (-)(разность векторов), (*)(скалярное произведение
             |векторов)),то есть мы получаем мини-калькулятор!
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
/*Переменные a и b хранят вещественные числа, введенные пользователем.
  Переменная p хранит целую степень числа, введенную пользователем.
  Переменная c хранит знак операции, а переменная y отвечает за
  продолжение работы с калькулятором после предыдущей операции.
  Если пользователь выберет "y", то работа с калькулятором продолжится,
  иначе при выборе "n" работа с калькулятором прекратиться.
 */
   float a,b;
   int p;
   char c,g,y;
   unsigned long int res = 1;
   do{
	   printf("Вы хотите работать с числами или веткорами?(n/v)\n");
	   scanf("%c",&g);
	   if(g=='v'){
	   		   printf("t");
	   }
	   else{
		   printf("Введите первое число\n");
		   scanf("%f",&a);
		   printf("Выберите операцию(+ - / * ! p)\n");
		   scanf("\n%c",&c);
		   switch(c){
		   case '!':
				if(a > 0){
					for (int  i = 1; i <= a; i++) {
	//Переменная res будет хранит результат факториала.
						res *=i;
					}
					printf("%lu\n",res);
				}else{
					printf("1\n");
				}
				break;
				printf("Хотите продолжить работу с калькулятором?(y/n)\n");
		   case 'p':
			   printf("Введите степень числа\n");
			   scanf("%i",&p);
			   double result = 1;
			   if (p < 0)
					{
					for (int i=1; i<=p; i++)
						{
	//Переменная result будет хранить результат возведения числа в степень.
					result = result * a;
					}
					result = (1/result);
					printf("%f\n",result);}
			   else
					{
					for (int i=1; i<=p; i++)
						{
						result = result * a;
						}
					printf("%f\n",result);
					}
				   break;
				   printf("Хотите продолжить работу с калькулятором?(y/n)\n");
		   default:
			   printf("Введите второе число\n");
			   scanf("%f",&b);
			   switch(c){
			   case '+':
					 printf("%f+%f=%f\n",a,b,a+b);
					 break;
			   case '-':
					 printf("%f-%f=%f\n",a,b,a-b);
					 break;
			   case '/':
					  printf("%f/%f=%f\n",a,b,a/b);
					  break;
			   case '*':
					  printf("%f*%f=%f\n",a,b,a*b);
					  break;
			   case '!':
					  printf("%f*%f=%f\n",a,b,a*b);
					  break;
			   }break;
	       }
	   }
		   printf("Хотите продолжить работу с калькулятором?(y/n)\n");
				   scanf("\n%c",&y);
			  }while (y=='y');
	  return 0;
}
