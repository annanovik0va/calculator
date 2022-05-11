/*
 ===============================================================================
 Name        : cal.c
 Author      : Novikova Anna
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Данная программа реализует арифметические операции(+(сложение),
             |-(вычитание), /(деление), *(произведение), !(факториал числа),
             |p(возведение числа в степень p))над двумя числами, введеными пользователем,
             |+(сложение векторов), -(разность векторов), *(скалярное произведение
             |векторов)),то есть мы получаем мини-калькулятор!
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
/*Переменные a и b хранят вещественные числа, введенные пользователем.
  Указатели *q,*r,*rslt хранят адрес значений, введынных пользователем.
  Переменная p хранит целую степень числа, введенную пользователем.
  Перменная size хранит размерность векторов, введенную пользователем.
  Переменные c, ci хранятт знак операции, а переменные y и ys отвечает за
  продолжение работы с калькулятором после предыдущей операции.
  Если пользователь выберет "y", то работа с калькулятором продолжится,
  иначе при выборе "n" работа с калькулятором прекратиться.
*/
   float a,b,*q,*r,*rslt,s;
   int p,size;
   char c,ci,g,y,ys;
   FILE *input, *output;
   unsigned long int res = 1;
   do{
	   char input_name[259],output_name[259];
	   //Имя файла, из которого будут читаться операции в данном случае "input.txt".
   	   printf("Введите имя файла, из которого будут читаться операции.\n");
   	   scanf("%s",input_name);
   	   //Имя файла, в который будут записываться результаты в данном случае "output.txt".
   	   printf("Введите имя файла, в который будут записываться результаты.\n");
   	   scanf("%s",output_name);
   	   input=fopen(input_name,"r");
   	   output=fopen(output_name,"w");
   	   do{
		   s=0;
		   fscanf(input," %c",&g);
		   if(g=='v'){
			   fscanf(input," %c",&ci);
			   switch(ci){
			   case '+':
					fscanf(input,"%i",&size);
					q=malloc(size*sizeof(double));
					r=malloc(size*sizeof(double));
					rslt=malloc(size*sizeof(double));
					for(int i=0;i<size;i++)
					fscanf(input,"%f",&q[i]);
					for(int i=0;i<size;i++)
					fscanf(input,"%f",&r[i]);
					for(int i=0;i<size;i++)
					fprintf(output,"%f",q[i]+r[i]);
					free(q);
					free(r);
					free(rslt);
				   break;
			   case '-':
				   fscanf(input,"%i",&size);
				   q=malloc(size*sizeof(double));
				   r=malloc(size*sizeof(double));
				   rslt=malloc(size*sizeof(double));
				   for(int i=0;i<size;i++)
				   fscanf(input,"%f",&q[i]);
				   for(int i=0;i<size;i++)
				   fscanf(input,"%f",&r[i]);
				   for(int i=0;i<size;i++)
				   fprintf(output,"%f",q[i]-r[i]);
				   free(q);
				   free(r);
				   free(rslt);
				  break;
			   case '*':
				   fscanf(input,"%i",&size);
				   q=malloc(size*sizeof(double));
				   r=malloc(size*sizeof(double));
				   rslt=malloc(size*sizeof(double));
				   for(int i=0;i<size;i++)
				   fscanf(input,"%f",&q[i]);
				   for(int i=0;i<size;i++)
				   fscanf(input,"%f",&r[i]);
				   for(int i=0;i<size;i++){
		//Переменная s будет хранить результат скалярного произведения векторов.
						s+=q[i]*r[i];
					}
					fprintf(output,"%f",s);
					free(q);
					free(r);
					free(rslt);
				 break;
			   }
		   }
		   else{
			   fscanf(input,"%f",&a);
			   fscanf(input," %c",&c);
			   switch(c){
			   case '!':
					if(a > 0){
						for (int  i = 1; i <= a; i++) {
		//Переменная res будет хранит результат факториала.
							res *=i;
						}
						fprintf(output,"%f!=%lu\n",a,res);
					}else{
						fprintf(output,"1");
					}
					break;
			   case 'p':
				   fscanf(input,"%i",&p);
				   double result = 1;
				   if (p < 0)
						{
						for (int i=1; i<=p; i++)
							{
		//Переменная result будет хранить результат возведения числа в степень.
						result = result * a;
						}
						result = (1/result);
						fprintf(output,"%f",result);}
				   else
						{
						for (int i=1; i<=p; i++)
							{
							result = result * a;
							}
						fprintf(output,"%f",result);
						}
					   break;
			   default:
				   fscanf(input,"%f",&b);
				   switch(c){
				   case '+':
						 fprintf(output,"%f+%f=%f\n",a,b,a+b);
						 break;
				   case '-':
						 fprintf(output,"%f+%f=%f\n",a,b,a-b);
						 break;
				   case '/':
						 fprintf(output,"%f+%f=%f\n",a,b,a/b);
						  break;
				   case '*':
						 fprintf(output,"%f+%f=%f\n",a,b,a*b);
						  break;
				   }break;
			   }
		   }
			   fscanf(input," %c",&y);
   	   	   	   }while (y=='y');
	   fclose(input);
	   fclose(output);
	   printf("Работа с файлом завершена!\n");
	   printf("Хотите продолжить работу?(y/n)\n");
	   scanf(" %c",&ys);
   }while(ys=='y');
   return 0;
}


