void sum(float *q,*r,*res,int size){
	printf("Введите размерность векторов: ");
	scanf('%i',&size);
	q=malloc(size*sizeof(int));
	r=malloc(size*sizeof(int));
	res=malloc(size*sizeof(int));
	printf("Введите значение первого вектора: ");
	for(int i=0;i<size;i++)
	scanf('%f',&q[i]);
	printf("Введите значение второго вектора: ");
	for(int i=0;i<size;i++)
	scanf('%f',&r[i]);
	printf("Результат сложения: ");
	for(int i=0;i<size;i++)
	printf("%f",q[i]+r[i]);
	free(q);
	free(r);
	free(res);
}
