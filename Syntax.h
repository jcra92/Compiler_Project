#ifndef Syntax_H
#define Syntax_H
#include "lexic.h"
#include "Code_Generator.h"
#include <stdlib.h>
#include <ctype.h>

using namespace std;

//Class
class Syntax{
	void programa (void);
	void bloque (void);
	void sentencia (void);
	void otra_sentencia (void);
	void asignacion(void);
	void lectura (void);
	void escritura(void);
	void condicional(void);
	void comparacion(void);
	void variable(void);
	void expresion(void);
	void termino(void);
	void mas_terminos(void);
	void factor(void);
	void mas_factores(void);
	void constant(void);
	void errores (int codigo);
	void loop(void);
	
	Lexic lexic; 
	Code_Generator code_Generator;

	public:
	int inter = 0;
	Syntax(const char *fuente, const char *objeto, int traza);
	~Syntax(void);
};

Syntax::Syntax(const char *fuente, const char *objeto,int traza):lexic(fuente, traza), code_Generator(objeto){
	if (lexic.existeTraza())
		cout<<"INICIO DE Syntax Analysis"<<endl;
	programa();
}

Syntax::~Syntax(void){
	if (lexic.existeTraza())
	{
		cout<<"End of Syntax Analysis"<<endl;
		cout<<"End of Compilation"<<endl;
	}
}

//Functions
void Syntax::programa(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <PROGRAMA>"<<endl;
	token=lexic.siguienteToken();
	if (token=='M')
	{
		cout<<"M";
		code_Generator.code();
	}
	else 
		errores(8);
	token=lexic.siguienteToken();
	if (token!='{') errores(9);
		bloque();
	token=lexic.siguienteToken();
	cout<<token;
	if (token=='}')
	{
		cout<<"}";
		code_Generator.end();
	}
		else errores(2);
	}

void Syntax::bloque(void){
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <BLOQUE>"<<endl;
	sentencia();
	otra_sentencia();
}

void Syntax::otra_sentencia(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <OTRA_SENTENCIA>"<<endl;
	token=lexic.siguienteToken();
	if (token==';')
	{
		sentencia();
		otra_sentencia();
	}
	else 
		lexic.devuelveToken(token); 
}

void Syntax::sentencia(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <SENTENCIA>"<<endl;
	token=lexic.siguienteToken();
	if ((token>='a') && (token<='z'))
		{
		lexic.devuelveToken(token);
		asignacion();
		}
	else if (token=='R') 
		lectura();
	else if (token=='W') 
		escritura();
	else if (token=='I') //Condicional
		condicional();
	else if (token=='}') 
	{
		lexic.devuelveToken(token);
		return;
	}
		else errores(6);
	}

void Syntax::asignacion(){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <ASIGNACION>"<<endl;
	variable();
	token=lexic.siguienteToken();
	if (token!='=') errores(3);
		expresion();
	code_Generator.store();
}

void Syntax::variable(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <VARIABLE>"<<endl;
	token=lexic.siguienteToken();
	if ((token>='a') && (token<='z')) 
	{
		code_Generator.pusha(token);
	}
	else 
		errores(5);
}

void Syntax::expresion(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <EXPRESION>"<<endl;
	termino();
	if (token != '?') 
		mas_terminos();
	else 
		lexic.devuelveToken(token);
}

void Syntax::termino(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <TERMINO>"<<endl;
	factor();
	if (token != ',') 
		mas_factores();
	else 
		lexic.devuelveToken(token);
}

void Syntax::mas_terminos(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <MAS_TERMINOS>"<<endl;
	token=lexic.siguienteToken();
	if (token=='+')
	{
		termino();
		code_Generator.add();
		mas_terminos();
	}
	else if (token =='-')
	{
		termino();
		code_Generator.neg();
		code_Generator.add();
		mas_terminos();
	}
	else 
		lexic.devuelveToken(token);
	}

void Syntax::factor(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <FACTOR>"<<endl;
	token=lexic.siguienteToken();
	if ((token>='0') && (token<='9'))
	{
		lexic.devuelveToken(token);
		constant();
	}
	else if (token=='(')
	{
		expresion();
		token=lexic.siguienteToken();
	if (token!=')') 
		errores(4);
	}
	else
	{
		lexic.devuelveToken(token);
		variable();
		code_Generator.load();
	}
}

void Syntax::mas_factores(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <MAS_FACTORES>"<<endl;
	token=lexic.siguienteToken();
	switch (token)
	{
		case '*':factor();
		code_Generator.mul();
		mas_factores();
		break;
		
		case '/':factor();
		code_Generator.div();
		mas_factores();
		break;
		
		case '%':factor();
		code_Generator.mod();
		mas_factores();
		break;
		
		default:
		lexic.devuelveToken(token);
	}
}

void Syntax::lectura(void){
	char token;
	token=lexic.siguienteToken();
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <LECTURA> "<<token<<endl;
	if((token<'a')||(token>'z')) errores(5);
		code_Generator.input(token);
}

void Syntax::escritura(void){
	char token;
	token=lexic.siguienteToken();
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <ESCRITURA> "<<token<<endl;
	if ((token<'a') || (token>'z')) errores(5);
		code_Generator.output(token);
}

void Syntax::condicional(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <CONDICIONAL>"<<endl;
	inter=0;
	comparacion();
	token=lexic.siguienteToken();
	if ((token!='?')) 
		errores(13);
	asignacion();
	code_Generator.etiqueta();
	token=lexic.siguienteToken();
	sentencia();
	code_Generator.etiqueta2();
}

void Syntax::loop(void){
char token;
if (lexic.existeTraza())
cout<<"ANALISIS SINTACTICO: <LOOP>"<<endl;
inter=1;
comparacion();
token=lexic.siguienteToken();
if ((token!=',')) errores(13);
sentencia();
code_Generator.etiqueta3();
}


void Syntax::comparacion(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <COMPARACION>"<<endl;
	token=lexic.siguienteToken();
	if ((token>='a') && (token<='z')) 
	{
		code_Generator.cond1(token);
	}
	else 
		errores(5);

	token=lexic.siguienteToken();
	if ((token=='=') || (token=='<')|| (token=='>')) {
		code_Generator.cond2(token);
	token=lexic.siguienteToken();
	if (((token>='0') && (token<='9')) || ((token>='a') && (token<='Z')) || (token='.')) {
		if (inter == 0){ 
			code_Generator.cond3(token);
			}
		if (inter == 1){ 
			code_Generator.cond4(token);
		}
	}
	}
	else 
		errores(12);
	}

void Syntax::constant(void){
	char token;
	if (lexic.existeTraza())
		cout<<"Syntax Analysis: <Constant> "<<endl;
	token=lexic.siguienteToken();
	if (((token>='0') && (token<='9')) || ((token>='a') && (token<='Z')) || (token='.')) 
	{
		code_Generator.pushc(token);
	}
	else errores(7);
}

void Syntax::errores(int codigo){
	int x;
	cout<<"Line: "<<lexic.lineaActual();
	cout<<" SYNTAX ERROR "<<codigo;
	switch (codigo)
	{
		case 1 :cout<<" :Expected ';'"<<endl;break;
		case 2 :cout<<" :Expected '}'"<<endl;break;
		case 3 :cout<<" :Expected '='"<<endl;break;
		case 4 :cout<<" :Expected ')'"<<endl;break;
		case 5 :cout<<" :Expected "<<endl;break;
		case 6 :cout<<" :Unknown Instruction"<<endl;break;
		case 7 :cout<<" :Expected ','"<<endl;break;
		case 8 :cout<<" :Expected an 'M' at the beginning of the program"<<endl;break;
		case 9 :cout<<" :Expected '{'"<<endl;break;
		case 11:cout<<" :Expected \' "<<endl;break;
		case 12:cout<<" :Expected operantor' "<<endl;break;
		case 13:cout<<" :Expected ','"<<endl;break;
		default:
		cout<<" :No information about this error"<<endl;
	}
	cin>>x;
	exit(-(codigo+100));
}

#endif
