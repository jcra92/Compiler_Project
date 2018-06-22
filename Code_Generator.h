#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>

//Class
class Code_Generator{
	char *nombreFichero; // Nombre del fichero objeto de salida
	FILE *salida; // Fichero objeto de salida
	public:
	int contador = 1;
	int contetiqueta = 1;
	
	Code_Generator(const char *unNombreFichero);
	~Code_Generator();
	void code();
	void pushc(const char constante);
	void pusha(const char direccion);
	void load();
	void store();
	void neg();
	void add();
	void mul();
	void div();
	void mod();
	void input(const char direccion);
	void output(const char direccion);
	void end();
	void cond1(const char direccion);
	void cond2(const char direccion);
	void cond3(const char direccion);
	void cond4(const char direccion);
	void etiqueta();
	void etiqueta2();
	void etiqueta3();
};

Code_Generator::Code_Generator(const char *unNombreFichero){
	if ((salida=fopen(unNombreFichero,"w"))==NULL)
	{
		cout<<"No se puede crear el fichero"<<unNombreFichero<<endl;
		exit(-3);
	}
}

Code_Generator::~Code_Generator(void){
fclose(salida);
}

//Functions
void Code_Generator::code(){
cout<<".CODE"<<endl;
fputs(".CODE\n",salida);
}

void Code_Generator::pushc(const char constante){
cout<<"PUSHC "<<constante<<endl;
fputs("PUSHC ",salida);
fputc(constante,salida);
fputc('\n',salida);
}

void Code_Generator::pusha(char direccion){
cout<<"PUSHA "<<direccion<<endl;
fputs("PUSHA ",salida);
fputc(direccion,salida);
fputc('\n',salida);
}

void Code_Generator::load(){
cout<<"LOAD"<<endl;
fputs("LOAD\n",salida);
}
 
void Code_Generator::store(){
	cout<<"STORE"<<endl;
	fputs("STORE\n",salida);
}

void Code_Generator::neg(){
cout<<"NEG"<<endl;
fputs("NEG\n",salida);
}

void Code_Generator::add(){
cout<<"ADD"<<endl;
fputs("ADD\n",salida);
}

void Code_Generator::mul(){
cout<<"MUL"<<endl;
fputs("MUL\n",salida);
}

void Code_Generator::div(){
cout<<"DIV"<<endl;
fputs("DIV\n",salida);
}

void Code_Generator::mod(){
cout<<"MOD"<<endl;
fputs("MOD\n",salida);
}

void Code_Generator::input(const char direccion){
cout<<"INPUT "<<direccion<<endl;
fputs("INPUT ",salida);
fputc(direccion,salida);
fputc('\n',salida);
}

void Code_Generator::output(const char direccion){
cout<<"OUTPUT "<<direccion<<endl;
fputs("OUTPUT ",salida);
fputc(direccion,salida);
fputc('\n',salida);
}

void Code_Generator::cond1(const char caracter){
fputs("T",salida);
fprintf(salida, "%d", contador);
fputs(" = (",salida);
fputc(caracter, salida);
}

void Code_Generator::cond2(const char caracter){
fputc(caracter,salida);
}

void Code_Generator::cond3(const char caracter){
fputc(caracter, salida);
fputs(")\n",salida);
cout<< "IF T"<<contador<<" GOTO L"<<contetiqueta<< endl;
fputs("IF T",salida);
fprintf(salida, "%d", contador);
fputs(" GOTO L",salida);
fprintf(salida, "%d", contetiqueta);
fputc('\n',salida);
cout<< "GOTO L"<<contetiqueta+1<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta+1);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contador++;
}

void Code_Generator::cond4(const char caracter)
{
fputc(caracter, salida);
fputs(")\n",salida);
cout<< "L"<<(contetiqueta-1)<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta-1);
fputs(":\n",salida);
cout<< "IF T"<<contador<<" GOTO L"<<contetiqueta<< endl;
fputs("IF T",salida);
fprintf(salida, "%d", contador);
fputs(" GOTO L",salida);
fprintf(salida, "%d", contetiqueta);
fputc('\n',salida);
cout<< "GOTO L"<<contetiqueta+1<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta+1);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contador++;
}

void Code_Generator::etiqueta(){
contetiqueta++;
cout<< "GOTO L"<<contetiqueta+1<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta+1);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
}

void Code_Generator::etiqueta2(){
contetiqueta++;
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contetiqueta++;
}

void Code_Generator::etiqueta3()
{
contetiqueta++;
cout<< "GOTO L"<<contetiqueta-2<< endl;
fputs("GOTO L",salida);
fprintf(salida, "%d", contetiqueta-2);
fputc('\n',salida);
cout<< "L"<<contetiqueta<< endl;
fputs("L",salida);
fprintf(salida, "%d", contetiqueta);
fputs(":\n",salida);
contetiqueta++;
}

void Code_Generator::end(){
cout<<"END"<<endl;
fputs("END\n",salida);
}
